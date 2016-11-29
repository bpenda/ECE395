#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

//This function create a pallete for the 256 color BMP from filename 
//and return pointer to 756 bytes of memory

unsigned char* read256BMPpallet(char* filename){
	FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
	
    // extract image height and width from header
    unsigned char pallet[1024];
	fread(pallet, sizeof(unsigned char), 1024, f); // read the 54-byte header
    fclose(f);
	
	unsigned char *cpallet = malloc(sizeof(unsigned char)*768);
	int i;
	for (i = 0; i < 1024; i+=4){
		cpallet[i*3/4] = pallet[i+2];
		cpallet[i*3/4+1] = pallet[i+1];
		cpallet[i*3/4+2] = pallet[i];
		//printf("%d %d %d\n", pallet[i], pallet[i+1],pallet[i+2] );
		//4 bytes for pallet entry, ignore 1st byte
	}
	//unsigned char *data = malloc(sizeof(unsigned char)*size); // allocate 3 bytes per pixel
	
	return cpallet;	
	return NULL;
}



//The pixel data in forms of index to the pallete of 256 color BMP
unsigned char* read256BMPdata(char* filename){
	FILE* f = fopen(filename, "rb");
    unsigned char info[1078];
    fread(info, sizeof(unsigned char), 1078, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
	int size = width*height;
	unsigned char *data = malloc(sizeof(unsigned char)*size);
	fread(data, sizeof(unsigned char), size, f); // read the 54-byte header
    fclose(f);
	
	return data;
}	


//This read 24bit BMP for max resolution, but slow
unsigned char* readBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = 3 * width * height;
	//int size = width*height;
    unsigned char* data = malloc(sizeof(unsigned char)*size); // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	//printf("%d %d\n", width, height);
    fclose(f);
	/*
	unsigned char* bitmap = malloc(sizeof(unsigned char) * width*height);
	
    for(i = 0; i < size; i += 3)
    {
		if (data[i] + data[i+1]+data[2+i] < 500)
			bitmap[i/3] = 1;
		else
			bitmap[i/3] = 0;
        unsigned char tmp = data[i];
        data[i] = data[i+2];
        data[i+2] = tmp;
    }
	for(i = 0; i < width*height; i+=8){
		if (i % width == 0){}
			//printf("\n");
		int j;
		unsigned char temp = 0;
		for (j = 0; j < 8; j++)
			temp |= bitmap[i+j] << (7-j);
		//printf("0x%02x, ",temp);
	}
	
	free(bitmap);	
	*/
    return data;
}
//return width of image
int filewidth(char* filename){
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
    // extract image height and width from header
    int width = *(int*)&info[18];
	fclose(f);
	return width;
}
//return height of image
int fileheight(char*filename){
	FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
	int height = *(int*)&info[22];
	fclose(f);
	return height;
}

//run length encoding to shorten data sent 
int encode(const unsigned char* data, int len, unsigned char * res) {
	/*unsigned char * */
	int i,j = 0;
	for (i = 0; i < len; i++){
		res[j] = data[i];
		j++;
		res[j]++;
		while(i+1< len && data[i] == data[i+1] && res[j] < 0xCF){
			//Note: 0xCF is set to the max repeat index since only 8 bits + write pixel takes time,
			// so any faster may cause UART reading errors
		  res[j]++;
		  i++;
		}
		j++;
	}
	if (len < j)
		printf("Run length inefficient!\n");
	else
		printf("%d vs %d",j,len);
	
	/*for (i = 0; i < j; i+=2){
		printf("0x%x- %u ", res[i], res[i+1]);
		if (i % 10 == 0)
			printf("\n");
	}*/
	//free(res);
	return j;
}
 

//Below is USB send code for Windows, not LINUX
int main()
{
    // Define the five bytes to send ("hello")
 
    // Declare variables and structures
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
         
    // Open the highest available serial port number
    fprintf(stderr, "Opening serial port...");
    hSerial = CreateFile(
                "\\\\.\\COM4", GENERIC_READ|GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    if (hSerial == INVALID_HANDLE_VALUE)
    {
            fprintf(stderr, "Error\n");
            return 1;
    }
    else fprintf(stderr, "OK\n");
     
    // Set device parameters (38400 baud, 1 start bit,
    // 1 stop bit, no parity)
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (GetCommState(hSerial, &dcbSerialParams) == 0)
    {
        fprintf(stderr, "Error getting device state\n");
        CloseHandle(hSerial);
        return 1;
    }
     
    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if(SetCommState(hSerial, &dcbSerialParams) == 0)
    {
        fprintf(stderr, "Error setting device parameters\n");
        CloseHandle(hSerial);
        return 1;
    }
 
    // Set COM port timeout settings
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if(SetCommTimeouts(hSerial, &timeouts) == 0)
    {
        fprintf(stderr, "Error setting timeouts\n");
        CloseHandle(hSerial);
        return 1;
    }
 
    // Send specified text (remaining command line arguments)
    DWORD bytes_written, total_bytes_written = 0;
    fprintf(stderr, "Sending bytes...");
    
	char buffer[50] = "./sampui.bmp";
	DWORD bytes_to_read = 50;
	//unsigned char *pic_ptr = readBMP(buffer);
	unsigned char *pal_ptr = read256BMPpallet(buffer);
	unsigned char *pic_ptr2 = read256BMPdata(buffer);
	
	/*do {
		ReadFile(hSerial, buffer, sizeof(buffer), &bytes_to_read , NULL);
		printf("Read from USB:%s\n", buffer);
	} while (1);*/
	
	int width = filewidth(buffer);	//800 -3 char
	int height = fileheight(buffer);	//480 -3 char
	
	char start[3];
	sprintf(start,"%03d", width);
	if(!WriteFile(hSerial, &start, 3, &bytes_written, NULL))
	{
		fprintf(stderr, "Error\n");
		CloseHandle(hSerial);
		return 1;
	}
	sprintf(start,"%03d", height);
	if(!WriteFile(hSerial, &start, 3, &bytes_written, NULL))
	{
		fprintf(stderr, "Error\n");
		CloseHandle(hSerial);
		return 1;
	}
	/*
	if(!WriteFile(hSerial, pic_ptr, width*height*3, &bytes_written, NULL))
	{
		fprintf(stderr, "Error\n");
		CloseHandle(hSerial);
		return 1;
	} 
	
	int o;
	for (o=0; o < width*height; o++){
		printf("0x%x ", pic_ptr2[o]);
		if (o %width == 0)
			printf("\n");
		
	}
	*/
	unsigned char *shortpic = malloc(sizeof(unsigned char)*(width*height*2));
	memset(shortpic,0,(width*height*2)*sizeof(unsigned char));
	
	int len = encode(pic_ptr2, width*height, shortpic);
	printf("%x-%x-%x-%x", shortpic[0], pal_ptr[shortpic[1]], pal_ptr[shortpic[1]+1], pal_ptr[shortpic[1]+2]);
	WriteFile(hSerial, pal_ptr, 768, &bytes_written, NULL);
	Sleep(5);
	WriteFile(hSerial, shortpic, len, &bytes_written, NULL);
	//WriteFile(hSerial, pic_ptr2, width*height, &bytes_written, NULL);
	free(shortpic);
	
	/*
	char termmi[3] = "end";
	if(!WriteFile(hSerial, &termmi, 3, &bytes_written, NULL))
	{
		fprintf(stderr, "Error\n");
		CloseHandle(hSerial);
		return 1;
	} 
	*/
	//free(pic_ptr2);
	free(pal_ptr);
    // Close serial port
    fprintf(stderr, "Closing serial port...");
    if (CloseHandle(hSerial) == 0)
    {
        fprintf(stderr, "Error\n");
        return 1;
    }
    fprintf(stderr, "OK\n");
    // exit normally
    return 0;
}
