#include <stdio.h>
#include "LPC11xx.h"
#include "ssd1963.h"
#include <rt_misc.h>
#include <stdlib.h>     /* malloc, free, rand */
#include <string.h>

#define SSD1963_PIN_RD	(1 << 4)
#define SSD1963_PIN_WR	(1 << 9)
#define SSD1963_PIN_RST	(1 << 5)
#define SSD1963_PIN_DC	(1 << 8)

extern void SER_init(void);
extern int getkey(void);
volatile char hr = 0, min = 0,sec = 0;
void configureGPIO()
{
	//Convert I2C to GPIO?
	/*
	LPC_SYSCON->SYSAHBCLKCTRL |= (0x1UL << 16);  // enable clock for IOCON
	LPC_IOCON->PIO0_4 &= ~(1<<1) & ~(1<<0);   
	LPC_IOCON->PIO0_4 |= (1<<8);
  LPC_IOCON->PIO0_5 &= ~(1<<1) & ~(1<<0);  
	LPC_IOCON->PIO0_5 |= (1<<8);
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(0x1UL << 16);  // disable clock for IOCON      */
	
	//1 to 8 as output or 0xF
	LPC_SYSCON->SYSAHBCLKCTRL |= 1 << 9 | 1 << 8;
	LPC_GPIO0->DIR = 0x1FE;
	//4 5 9 8
	LPC_GPIO1->DIR |= SSD1963_PIN_RD | SSD1963_PIN_WR | SSD1963_PIN_RST | SSD1963_PIN_DC;
}

unsigned char SSD1963_ReadData(){
	unsigned char result;
	LPC_GPIO1->DATA  |= SSD1963_PIN_WR | SSD1963_PIN_DC;
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_RD] = ~SSD1963_PIN_WR;
	result = (LPC_GPIO0->DATA >> 1) & 0xFF;
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_RD]  = SSD1963_PIN_RD;
	return result;
}

__inline void configGPIOread(){
	LPC_GPIO0->DIR = 0x00;
}

__inline void configGPIOwrite(){
	LPC_GPIO0->DIR = 0x1E;
}

void SSD1963_WriteCommand(unsigned int commandToWrite){
//	LPC_GPIO0->DATA = (commandToWrite << 1) | (LPC_GPIO0->DATA & 0x1);
	LPC_GPIO0->MASKED_ACCESS[0x1FE] = commandToWrite<<1;
	//LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_RD] = SSD1963_PIN_RD ;
	LPC_GPIO1->DATA &= ~SSD1963_PIN_DC & ~SSD1963_PIN_WR;
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_WR]  = SSD1963_PIN_WR;
}

void SSD1963_WriteData(unsigned int dataToWrite){
	LPC_GPIO0->DATA = (dataToWrite << 1) | (LPC_GPIO0->DATA & 0x1);
	//LPC_GPIO1->DATA  |= SSD1963_PIN_RD | SSD1963_PIN_DC;
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_DC]  = SSD1963_PIN_DC;
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_WR]  = ~SSD1963_PIN_WR;
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_WR]  = SSD1963_PIN_WR;
}

void SSD1963_Init (void)
{
	
	volatile unsigned int dly;
	LPC_GPIO1->DATA &= ~SSD1963_PIN_RST;	
	for(dly = 0; dly < 0x3FFFF; dly++);
	LPC_GPIO1->DATA |= SSD1963_PIN_RST;
	for(dly = 0; dly < 0x3FFFF; dly++);
	SSD1963_WriteCommand(SSD1963_SOFT_RESET);
	for(dly = 0; dly < 0x0FFFF; dly++);
	
	SSD1963_WriteCommand(SSD1963_SET_PLL_MN);
	//SET DLL ; Refclock should be 10MHz Oscilator
	/*SSD1963_WriteData(49);	// PLLclk = REFclk * 50 (500MHz)
	SSD1963_WriteData(4);	// SYSclk = PLLclk / 5  (100MHz)
	SSD1963_WriteData(4);  // dummy
	*/
	SSD1963_WriteData(0x23);
	SSD1963_WriteData(0x2);
	SSD1963_WriteData(0x4);
	//LOCK PLL
	SSD1963_WriteCommand(SSD1963_SET_PLL);
	SSD1963_WriteData(0x01);
	for(dly = 0; dly < 0x3FFFF; dly++);
	SSD1963_WriteCommand(SSD1963_SET_PLL);
	SSD1963_WriteData(0x03);
	SSD1963_WriteCommand(SSD1963_SOFT_RESET);
	for(dly = 0; dly < 0x0FFFF; dly++);
	//FINISH LOCK PLL
	
	//set pixel clock by 30Mhz
	// Pclock = PLL clock* value_written /2^20
	SSD1963_WriteCommand(SSD1963_SET_LSHIFT_FREQ); 
	/*
	SSD1963_WriteData((LCD_FPR >> 16) & 0xFF);
	SSD1963_WriteData((LCD_FPR >> 8) & 0xFF);
	SSD1963_WriteData(LCD_FPR & 0xFF);
	*/
	SSD1963_WriteData(0x03);
	SSD1963_WriteData(0xff);
	SSD1963_WriteData(0xff);
	
	
	//SET LCD MODE
	SSD1963_WriteCommand(SSD1963_SET_LCD_MODE); 
	//vert+horiz sync active low
	//data latch in rising edge + enable TFT FRC disable TFT dithering
	SSD1963_WriteData(0x0C);			
	//TFT mode in bit 5+6
	SSD1963_WriteData(0x00);			
	//SET dimensions 800 * 480
	SSD1963_WriteData(mHIGH((TFT_WIDTH-1)));
	SSD1963_WriteData(mLOW((TFT_WIDTH-1)));
	SSD1963_WriteData(mHIGH((TFT_HEIGHT-1)));
	SSD1963_WriteData(mLOW((TFT_HEIGHT-1)));
	//Send in sequence RGB
	SSD1963_WriteData(0x00);
	
	//set pixel data by 8 bit * 3 times
	SSD1963_WriteCommand(SSD1963_SET_PIXEL_DATA_INTERFACE);
	SSD1963_WriteData(SSD1963_PDI_8BIT);

	SSD1963_WriteCommand(SSD1963_SET_HORI_PERIOD);
	SSD1963_WriteData(((928>>8) &0x0FF));
	SSD1963_WriteData(((928) &0x0FF));
	SSD1963_WriteData(((46>>8) &0x0FF));
	SSD1963_WriteData(((46) &0x0FF));
	SSD1963_WriteData(((48) &0x0FF));
	SSD1963_WriteData(((15>>8) &0x0FF));
	SSD1963_WriteData(((15) &0x0FF));
	SSD1963_WriteData(0x00);			
	
	SSD1963_WriteCommand(SSD1963_SET_VERT_PERIOD);
	SSD1963_WriteData(((525>>8) &0x0FF));
	SSD1963_WriteData(((525) &0x0FF));
	SSD1963_WriteData(((16>>8) &0x0FF));
	SSD1963_WriteData(((16) &0x0FF));
	SSD1963_WriteData(((16) &0x0FF));
	SSD1963_WriteData(((8>>8) &0x0FF));
	SSD1963_WriteData(((8) &0x0FF));
	//SSD1963_WriteData(0x00);			
	
	
	/*
	//Total period
	SSD1963_WriteData(mHIGH(TFT_HSYNC_PERIOD));
	SSD1963_WriteData(mLOW(TFT_HSYNC_PERIOD));
	//non display period
	SSD1963_WriteData(mHIGH((TFT_HSYNC_PULSE + TFT_HSYNC_BACK_PORCH)));
	SSD1963_WriteData(mLOW((TFT_HSYNC_PULSE + TFT_HSYNC_BACK_PORCH)));
	//horiz pulse width
	SSD1963_WriteData(TFT_HSYNC_PULSE);
	//start location in pix clock
	SSD1963_WriteData(0x00);			
	
	
	SSD1963_WriteCommand(SSD1963_SET_VERT_PERIOD); 		
	SSD1963_WriteData(mHIGH(TFT_VSYNC_PERIOD));
	SSD1963_WriteData(mLOW(TFT_VSYNC_PERIOD));
	SSD1963_WriteData(mHIGH((TFT_VSYNC_PULSE + TFT_VSYNC_BACK_PORCH)));
	SSD1963_WriteData(mLOW((TFT_VSYNC_PULSE + TFT_VSYNC_BACK_PORCH)));
	SSD1963_WriteData(TFT_VSYNC_PULSE);
	SSD1963_WriteData(0x00);			
	SSD1963_WriteData(0x00);
	*/
	SSD1963_WriteCommand(SSD1963_SET_DISPLAY_ON);		//SET display on
}

void SSD1963_SetArea(unsigned int sx, unsigned int ex, unsigned int sy, unsigned int ey)
{
	SSD1963_WriteCommand(SSD1963_SET_COLUMN_ADDRESS);	
	SSD1963_WriteData((sx >> 8) & 0xFF);
	SSD1963_WriteData((sx >> 0) & 0xFF);
	SSD1963_WriteData((ex >> 8) & 0xFF);
	SSD1963_WriteData((ex >> 0) & 0xFF);

	SSD1963_WriteCommand(SSD1963_SET_PAGE_ADDRESS);	
	SSD1963_WriteData((sy >> 8) & 0xFF);
	SSD1963_WriteData((sy >> 0) & 0xFF);
	SSD1963_WriteData((ey >> 8) & 0xFF);
	SSD1963_WriteData((ey >> 0) & 0xFF);
}

void SSD1963_FillArea(unsigned int sx, unsigned int ex, unsigned int sy, unsigned int ey, int color)
{
int i;
SSD1963_SetArea(sx, ex, sy, ey);
SSD1963_WriteCommand(SSD1963_WRITE_MEMORY_START);
for(i = 0; i < ((ex-sx+1)*(ey-sy+1)); i++)
	{
		SSD1963_WriteData(color >> 16);
		SSD1963_WriteData((color >> 8)&0xFF);
		SSD1963_WriteData(color & 0xFF);
	}
}
void GLCD_SetPixel(int x, int y, int color)
{
	SSD1963_FillArea(x, x, y, y,color);
/*	SSD1963_WriteCommand(0x2c);
	SSD1963_WriteData(color >> 16);
	SSD1963_WriteData((color >> 8)&0xFF);
	SSD1963_WriteData(color & 0xFF);SSD1963_WriteCommand(0x0);*/
}
volatile uint32_t color = 0x0FFF0F;

void draw_circle(uint8_t rad, uint8_t border, uint16_t center_x, uint16_t center_y, uint32_t color, uint32_t bgcolor){
	int i,j;
	int bound = rad*rad;
	int bound2 = (rad-border)*(rad-border);
	//char flag = 0;
	SSD1963_SetArea(center_x-rad, center_x+rad-1, center_y-rad, center_y+rad-1);
	SSD1963_WriteCommand(SSD1963_WRITE_MEMORY_START);
	for (i = 0; i < rad*2; i++){
		for (j = 0; j < rad*2; j++){
			int distance = abs(i-rad)*abs(i-rad) + abs(j-rad)*abs(j-rad);
			if (distance <= bound && distance >= bound2){
				SSD1963_WriteData(color >> 16);
				SSD1963_WriteData((color >> 8)&0xFF);
				SSD1963_WriteData(color & 0xFF);
			}
			else{
				//if (flag == 0)
				//	flag = 1;
				
				SSD1963_WriteData(bgcolor >> 16);
				SSD1963_WriteData((bgcolor >> 8)&0xFF);
				SSD1963_WriteData(bgcolor & 0xFF);
			}
			
		}
	}
}

void draw_letter(unsigned char c, uint32_t color, uint16_t size, uint16_t start_x, uint16_t start_y){
	int32_t i,j;
	int offset = (c - ' ')*16;
	if (c < ' ')
		return;
	if (start_x + size*8 > 799 || start_y + size*8 > 479)
		return;
	SSD1963_SetArea(start_x, start_x+8*size-1, start_y, start_y+16*size -1);
	SSD1963_WriteCommand(SSD1963_WRITE_MEMORY_START);
	for (j = 0; j < 16*size; j++){
		for (i = 8*size-1 ; i >= 0; i--){
			if (((font_rom[j/size+offset]>>i/size) & 0x1) == 1){
				SSD1963_WriteData(color >> 16);
				SSD1963_WriteData((color >> 8)&0xFF);
				SSD1963_WriteData(color & 0xFF);
				//SSD1963_FillArea(start_y+(7-i)*size,start_y+(8-i)*size,start_x+(j-1)*size,start_x+j*size, color);
			}
			else{
				SSD1963_WriteData(0xFF);
				SSD1963_WriteData(0xFF);
				SSD1963_WriteData(0xFF);
				//SSD1963_FillArea(start_y+(7-i)*size,start_y+(8-i)*size,start_x+(j-1)*size,start_x+j*size, 0xFFFFFF);
			}
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
			x += 8*size+1;}
		else{
			x += size*4;
		}
		if (x >= 780){
			x = 0;
			y+= 16*size;
		}		
	}
	return;
}
	//Trigger interrupt every 1 seconds
void timer_init(){	
	LPC_TMR32B0->TCR = 0x02;		/* reset timer */
  LPC_TMR32B0->PR  = 0x00;		/* set prescaler to zero */
  LPC_TMR32B0->MR0 = 1000 * ((SystemCoreClock/(LPC_TMR32B0->PR+1)) / 1000);
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

void read_string_from_UART(char* str2){
	int i = 0;
	char temp;
	while(1){
		temp = getkey();
		str2[i] = temp;
		i++;
		if (i == sizeof(str2) || temp == '\r'){
			i = 0;
			break;
		}	
	}
	return;
}

void TIMER32_0_IRQHandler(void){
	sec+= 1;
	if (sec >= 60){
		sec = 0; min+=1;
	}
	if (min >= 60){
		min = 0; hr+=1;
	}
	if (hr > 23)
		hr = 0;
	LPC_TMR32B0->IR = 1;                /* clear interrupt flag */
}

int main()
{
	int i = 0;
	//int j = 0;
	//int cx = 60;
	//int cy = 240;
	
	char str[20], str2[20];
	configureGPIO();
	SER_init();
	
	LPC_GPIO1->MASKED_ACCESS[SSD1963_PIN_RD] = SSD1963_PIN_RD ;

	SSD1963_Init();
	//CLEAR SCREEN
	SSD1963_FillArea(0,799,0,479,0xFFFFFF);
	print_string("abcde", 0xFF0000, 3,50,50);
	timer_init();
	//SPECIAL NOTE!; ENTER IN PUTTY is '\r' not '\n'
	while (1)
	{
		
		read_string_from_UART(str2);
		
		//sprintf(str, "%02d:%02d:%02d", hr,min,sec);
		//j++;
		print_string(str2,0xFF0000, 3,50,50);
		printf("ECHO: %s\n", str2);
		//print_string(str2, 0xFF0000, 3, 50,100);
		//timer_delay(100);
		
		
	//	printf("Testing\n");
		
	//	scanf("%s", str);
	//	printf("Echo: %s\n", str);
		/*
		for (i =0; i< 0x3ffff; i++);
		for (i =0; i< 0x3ffff; i++);
		for (i =0; i< 0x3ffff; i++);
		for (i =0; i< 0x3ffff; i++);
		for (i =0; i< 0x3ffff; i++);
		*/
		//print_string(str, 0xFF0000,2, 20,20);
		//SSD1963_WriteCommand(SSD1963_EXIT_INVERT_MODE);		
		//SSD1963_WriteCommand(SSD1963_SET_DISPLAY_ON);		
		
	}
}


