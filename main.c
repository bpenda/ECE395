#include <stdio.h>
#include "LPC11xx.h"
#include "ssd1963.h"
#include <rt_misc.h>
#include <stdlib.h>     /* malloc, free, rand */
#include <string.h>
#include "font_rom.h"

extern void SER_init(void);
extern int getkey(void);
volatile char hr = 11, min = 58,sec = 0;
volatile long int ms = 0;
void configureGPIO(){
	//Enable clock for timer
	LPC_SYSCON->SYSAHBCLKCTRL |= 1 << 9 | 1 << 8;
	//1 to 8 as output or 0xFE
	LPC_GPIO0->DIR = 0x1FE;
	//4 5 9 8
	LPC_GPIO1->DIR |= SSD1963_PIN_RD | SSD1963_PIN_WR | SSD1963_PIN_RST | SSD1963_PIN_DC;
}


void fast_draw_init(int sx, int ex, int sy, int ey){
	SSD1963_SetArea(sx,ex,sy,ey);
	SSD1963_WriteCommand(SSD1963_WRITE_MEMORY_START);
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_DC]  = SSD1963_PIN_DC;
}

void fast_draw(uint32_t color){
	uint8_t R,G,B;
	R = (color >> 16);
	//LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_DC]  = SSD1963_PIN_DC;
	LPC_GPIO0->MASKED_ACCESS[0x1FE] = R << 1;
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_WR]  = ~SSD1963_PIN_WR;
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_WR]  = SSD1963_PIN_WR;
	G = ((color >> 8) & 0xFF);	
	LPC_GPIO0->MASKED_ACCESS[0x1FE] = G << 1;
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_WR]  = ~SSD1963_PIN_WR;
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_WR]  = SSD1963_PIN_WR;
	B = (color & 0xFF); 	
	LPC_GPIO0->MASKED_ACCESS[0x1FE] = B << 1;
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_WR]  = ~SSD1963_PIN_WR;
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_WR]  = SSD1963_PIN_WR;
		
}

void draw_circle(uint8_t rad, uint8_t border, uint16_t center_x, uint16_t center_y, uint32_t color, uint32_t bgcolor){
	int i,j;
	int bound = rad*rad;
	int bound2 = (rad-border)*(rad-border);
	//char flag = 0;
	//SSD1963_SetArea(center_x-rad, center_x+rad-1, center_y-rad, center_y+rad-1);
	//SSD1963_WriteCommand(SSD1963_WRITE_MEMORY_START);
	fast_draw_init(center_x-rad, center_x+rad-1, center_y-rad, center_y+rad-1);
	for (i = 0; i < rad*2; i++){
		for (j = 0; j < rad*2; j++){
			int distance = abs(i-rad)*abs(i-rad) + abs(j-rad)*abs(j-rad);
			if (distance <= bound && distance >= bound2){
				fast_draw(color);
			}
			else{
				fast_draw(bgcolor);
			}		
		}
	}
}

void draw_letter(unsigned char c, uint32_t color, uint16_t size, uint16_t start_x, uint16_t start_y){
	int32_t i,j;
	int offset = (c - ' ')*16;
	if (c < ' ')
		return;
	if (start_x + size*8 > 799 || start_y + size*16 > 479)
		return;
	fast_draw_init(start_x, start_x+8*size-1, start_y, start_y+16*size -1);

	for (j = 0; j < 16*size; j++){
		for (i = 8*size-1 ; i >= 0; i--){
			if (((font_rom[j/size+offset]>>i/size) & 0x1) == 1){
				fast_draw(color);
			}
			else{
				fast_draw(0xFFFFFF);
			}
		}
	}
}	
	
void draw_letter_90(unsigned char c, uint32_t color, uint8_t size, uint8_t div_size,uint16_t start_x, uint16_t start_y){
	int i, j;
	int offset = (c - ' ')*16;
	int ratio = 8*size/div_size;
	if (c < ' ')
		return;
	if (start_x + size*16/div_size > 799 || start_y + size*8/div_size > 479)
		return;
	fast_draw_init(start_x, start_x+2*ratio-1, start_y, start_y+ ratio -1);
	for (i = 0 ; i < ratio; i++){
		for (j = 0; j < 2*ratio; j++){
			if ((font_rom[j*div_size/size+offset]>>i*div_size/size & 0x1) == 1)
				fast_draw(color);
			else
				fast_draw(0x000000);
		}
	}
}

void temp(unsigned char c, uint32_t color, float size,uint16_t start_x, uint16_t start_y){
	int i,j;
	int offset = (c - ' ')*16;
	int lim = (int)(8*size);
	if ((c < ' ') || (start_x + lim*2 > 799 || start_y + lim > 479))
		return;
	fast_draw_init(start_x, start_x+2*lim-(int)(size)-1, start_y, start_y+ lim-1);
	for (i = 0 ; i < lim; i++){
		for (j = 0; j < 2*lim-(int)(size); j++){
			if ((font_rom[j*8/lim+offset]>> i*8/lim & 0x1) == 1)
				fast_draw(color);
			else
				fast_draw(0x000000);
		}
	}
}

void print_string(char* str, uint32_t color, uint16_t size,uint16_t start_x, uint16_t start_y){
	unsigned int len = strlen(str);
	unsigned int i,x,y;
	x = start_x;
	y = start_y;
	for (i = 0; i < len; i++){
		if (str[i] != ' '){
			draw_letter(str[i],color, size, x, y);
			x += 8*size+1;
		}
		else
			x += size*4;
		if (x >= 780){
			x = 0;
			y+= 16*size;
		}		
	}
	return;
}

void print_string_90(const char* str, uint32_t color, float size, uint16_t start_x, uint16_t start_y, uint8_t format){
	unsigned int len = strlen(str);
	int i,x,y,r;
	r = (int)(8*size);
	x = start_x;
	y = start_y;
	for (i = len-1; i >= 0; i--){
		if (str[i] != ' '){
			temp(str[i],color, size, x, y);		// ~ 1% more efficient
			//draw_letter_90(str[i],color, size, div_size, x, y);
			y += r;
		}
		else
			y += r >> 1;
		if (y +r >= 479){
			y = start_y;
			x+= r << 1;
		}		
	}
	//UNDERLINE
	
	if ((format & 0x1) == 1){
		SSD1963_SetArea(start_x+r-3, start_x+16*size-1, start_y, start_y+y);
		SSD1963_WriteCommand(SSD1963_WRITE_MEMORY_START);
		for (i = 0; i < len*24*size;i++){
				SSD1963_WriteData(color >> 16);
				SSD1963_WriteData((color >> 8)&0xFF);	
				SSD1963_WriteData(color & 0xFF);
		}
	}
	
	return;
}

//Trigger interrupt every 1 milliseconds
void timer_init(){	
	LPC_TMR32B0->TCR = 0x02;		/* reset timer */
  LPC_TMR32B0->PR  = 0x00;		/* set prescaler to zero */
  LPC_TMR32B0->MR0 = 1 * ((SystemCoreClock/(LPC_TMR32B0->PR+1)) / 1000);
  LPC_TMR32B0->IR  = 0xff;		/* reset all interrrupts */
  LPC_TMR32B0->MCR = 0x03;		/* stop timer on match */
  LPC_TMR32B0->TCR = 0x01;		/* start timer */
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
}

void timer_delay(int msdelay){
	LPC_TMR32B1->TCR = 0x02;		/* reset timer */
  LPC_TMR32B1->PR  = 0x00;		/* set prescaler to zero */
  LPC_TMR32B1->MR0 = msdelay * ((SystemCoreClock/(LPC_TMR32B0->PR+1)) / 1000);
  LPC_TMR32B1->IR  = 0xff;		/* reset all interrrupts */
  LPC_TMR32B1->MCR = 0x04;		/* stop timer on match */
  LPC_TMR32B1->TCR = 0x01;		/* start timer */  
   /* wait until delay time has elapsed */
  while (LPC_TMR32B1->TCR & 0x01);
}

void read_string_from_UART(char* str2, int size){
	int i = 0;
	char temp;
	while(1){
		temp = getkey();
		str2[i] = temp;
		i++;
		if (i == size || temp == '\r'){
			i = 0;
			break;
		}	
	}
	return;
}

void TIMER32_0_IRQHandler(void){
	//sec+= 1;
	ms+=1;
	/*
	if (sec >= 60){
		sec = 0; min+=1;
	}
	if (min >= 60){
		min = 0; hr+=1;
	}
	if (hr > 23)
		hr = 0;
	*/
	LPC_TMR32B0->IR = 1;                /* clear interrupt flag */
}

void recv_img_24bmp(){
	uint8_t data1, data2, data3;
	uint32_t col;
	int width, height;
	int count = 0;
	data1 = getkey();
	data2 = getkey();
	data3 = getkey();
	width = (data1-'0')*100 + (data2-'0')*10 + data3-'0';
	data1 = getkey();
	data2 = getkey();
	data3 = getkey();
	height = (data1-'0')*100 + (data2-'0')*10 + data3-'0';
	fast_draw_init(0,width -1, 0, height-1);
	//SSD1963_SetArea(470,width+469,0,height-1);
	//SSD1963_WriteCommand(SSD1963_WRITE_MEMORY_START);
	//timer_init();
	while (count < width * height)
	{
		data1 = getkey();
		data2 = getkey();
		data3 = getkey();
		count++;
		col = (data1 << 16) | (data2 << 8) | (data3);
		//if (data1 == 'e' && data2 == 'n' && data3 == 'd'){
		//	
		//}
		fast_draw(col);
		
	}
}

void recv_bitmap(){
	uint8_t data1, data2, data3;
	int width, height;
	data1 = getkey();
	data2 = getkey();
	data3 = getkey();
	width = (data1-'0')*100 + (data2-'0')*10 + data3-'0';
	data1 = getkey();
	data2 = getkey();
	data3 = getkey();
	height = (data1-'0')*100 + (data2-'0')*10 + data3-'0';
	SSD1963_SetArea(0,width,0,height-1);
	SSD1963_WriteCommand(SSD1963_WRITE_MEMORY_START);
	while(1){
		data1 = getkey();
		if (data1 == 'e')
			break;
		if (data1 == 0){
			SSD1963_WriteData(0xFF);
			SSD1963_WriteData(0xFF);
			SSD1963_WriteData(0xFF);
		}
		else{
			SSD1963_WriteData(0x00);
			SSD1963_WriteData(0x00);
			SSD1963_WriteData(0xFF);
		}
	}
}


int main()
{
	int i,j,k,l;
	char temperature = 52;
	char humidity = 70;
	char str2[100];
	
	char date[25];
	char time[25];
	char weather[25];
	//char temp[25];
	char news1[25];
	char news2[25];
	char news3[25];

	configureGPIO();
	SER_init();
	
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_RD] = SSD1963_PIN_RD ;


	SSD1963_Init();
	
	//CLEAR SCREEN
	//SSD1963_FillArea(0,799,0,479,0xFF00FF);
	//timer_delay(100);
	SSD1963_FillArea(1,799,0,479,0x000000);
	//print_string_90("THIS IS A VERY LONG LINE OF TEXT", 0xFFFFFF,9,2,100,20,0x0);
	//EXECUTION DOWN HERE
	//SPECIAL NOTE!; ENTER IN PUTTY is '\r' not '\n'
	/recv_bitmap();
	//sprintf(str2,"Ms:%ld", ms);
	
	
	while(1){
		read_string_from_UART(date, 100); 
		read_string_from_UART(time, 100); 
		read_string_from_UART(weather, 100);
		read_string_from_UART(temp, 100);		
		read_string_from_UART(news1, 100);
		read_string_from_UART(news2, 100);
		read_string_from_UART(news3, 100);		
		

		print_string_90(date, 0xFFFFFF,2,1,20,20,0x0);
		print_string_90(time,0xFFFFFF, 6,1, 52,20,0x0);
		print_string_90(weather,0xFFFFFF, 2,1, 227,67,0x0);
		print_string_90(temp,0xFFFFFF, 3,2, 267,20,0x0);
		print_string_90(news1,0xFFFFFF,3,2, 362,20,0x0);
		print_string_90(news2,0xFFFFFF, 3,2, 394,20,0x0);
		print_string_90(news3,0xFFFFFF, 3,2, 426,20,0x0);
		
	
	//print_string_90("Wednesday, Oct 26", 0xFFFFFF,2,1,20,20,0x0);
	
	//print_string_90("Good afternoon, Neo", 0xFFFFFF,2,1,120,180,0x0);
	
	print_string_90("Weather today",0xFFFFFF,2,1,185,20,0x1);
	//draw icon
	
	SSD1963_SetArea(220, 267, 20, 67);
	SSD1963_WriteCommand(SSD1963_WRITE_MEMORY_START);
	for (j = 0; j < 288; j++){
		for (i = 7 ; i >= 0; i--){
			if (((sun[j]>>i) & 0x1) == 1){
				SSD1963_WriteData(0x00);	
				SSD1963_WriteData(0x00);	
				SSD1963_WriteData(0x00);
			}
			else{
				SSD1963_WriteData(0xFF);SSD1963_WriteData(0xFF);SSD1963_WriteData(0xFF);
			}
		}
	}
	
	//print_string_90("Stormy ",0xFFFFFF, 2,1, 227,67,0x0);
	
	//sprintf(str2,"Temp: %d*F  Humidity: %d%%",temperature,humidity);
	//print_string_90(str2,0xFFFFFF, 3,2, 267,20,0x0);
	
	
	print_string_90("Notifications:",0xFFFFFF, 2,1, 330,20,0x1);
	//print_string_90("Feed the dogs",0xFFFFFF, 3,2, 362,20,0x0);
	//print_string_90("Run away from responsibilites",0xFFFFFF, 3,2, 394,20,0x0);
	//print_string_90("Avoid existential crisis",0xFFFFFF, 3,2, 426,20,0x0);

	}
	
	/*
	timer_init();
	while(1){
		if (hr < 12)
			sprintf(str2,"%02d:%02d am",hr,min);
		else{
			if (hr == 12)
				sprintf(str2,"%02d:%02d pm",hr,min);
			else
				sprintf(str2,"%02d:%02d pm",hr-12,min);
		}
		print_string_90(str2,0xFFFFFF, 6,1, 52,20,0x0);
	}
	*/
}




