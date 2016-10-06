#include <stdio.h>
#include "LPC11xx.h"
#include "ssd1963.h"
#include <rt_misc.h>

#define SSD1963_PIN_RD	(1 << 4)
#define SSD1963_PIN_WR	(1 << 9)
#define SSD1963_PIN_RST	(1 << 5)
#define SSD1963_PIN_DC	(1 << 8)
//#define LPC_GPIO0 SSD1963_DATA
//#define LPC_GPIO1 SSD1963_CMD
//#define SSD1963_PIN_CS	(1 << )
//#define SSD1963_PIN_A0	(1 << )

extern void SER_init(void);
void configureGPIO()
{
	//Convert I2C to GPIO?
	LPC_SYSCON->SYSAHBCLKCTRL |= (0x1UL << 16);  /* enable clock for IOCON      */

	LPC_IOCON->PIO0_4 &= ~(1<<1) & ~(1<<0);   
	LPC_IOCON->PIO0_4 |= (1<<8);
  LPC_IOCON->PIO0_5 &= ~(1<<1) & ~(1<<0);  
	LPC_IOCON->PIO0_5 |= (1<<8);
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(0x1UL << 16);  /* disable clock for IOCON      */
	//1 to 8 as output or 0xF
	LPC_GPIO0->DIR = 0x1FE;
	//4 5 9 8
	LPC_GPIO1->DIR |= SSD1963_PIN_RD | SSD1963_PIN_WR | SSD1963_PIN_RST | SSD1963_PIN_DC;
//	LPC_GPIO1->DATA = 0x000;
//	LPC_GPIO0->DATA = 0x000;
}

void configGPIOread(){
	LPC_GPIO0->DIR = 0x00;

}

void ledOn()
{
	LPC_GPIO0->DATA &= ~(1<<7);
}

void ledOff()
{						 
	LPC_GPIO0->DATA |= (1<<7);
}

void SSD1963_WriteCommand(unsigned int commandToWrite){
	LPC_GPIO0->DATA = (commandToWrite << 1) | (LPC_GPIO0->DATA & 0x1);
	LPC_GPIO1 ->DATA |= SSD1963_PIN_RD ;
	LPC_GPIO1->DATA &= ~SSD1963_PIN_DC /*&~SSD1963_PIN_CS*/ & ~SSD1963_PIN_WR;
	__asm{
			nop
	}
	
	LPC_GPIO1 ->DATA |= /*SSD1963_PIN_DC |SSD1963_PIN_CS |*/ SSD1963_PIN_WR;
}


void SSD1963_WriteData(unsigned int dataToWrite)
{
	LPC_GPIO0->DATA = (dataToWrite << 1) | (LPC_GPIO0->DATA & 0x1);
	if (((dataToWrite >>3) & 0x1) == 1)
			LPC_GPIO0->DATA |= 1 << 9;
	else
			LPC_GPIO0->DATA &= ~(1<<9);
	/*int i;
	for (i = 1; i < 9; i++)
	{
		if (dataToWrite >> (i-1) &0x1)
			LPC_GPIO0->DATA |= 1 << i;
		else
			LPC_GPIO0->DATA &= ~1<<i;
	}*/
	LPC_GPIO1->DATA  |= SSD1963_PIN_RD | SSD1963_PIN_DC;
	LPC_GPIO1-> DATA &= /*SSD1963_PIN_CS |*/ ~SSD1963_PIN_WR;
	__asm{
			nop
	}

	LPC_GPIO1->DATA  |= /*SSD1963_PIN_CS |*/ SSD1963_PIN_WR;
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
	//PIXEL CLOCK IS CURRENTLY WRONG!
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

int main()
{
	int i;
	//SER_init();
	configureGPIO();
	//configGPIOread();
	//LPC_GPIO0->DATA |= 0xFF;
	/*
	//This test is used for checking if SSD1963 is responding by setting tear status
	
	SSD1963_WriteData(0x00);
	SSD1963_WriteCommand(SSD1963_GET_TEAR_EFFECT_STATUS);
	__asm{
		nop
	}
	configGPIOread();
	LPC_GPIO1 ->DATA &= ~SSD1963_PIN_RD ;
	LPC_GPIO1 ->DATA |= SSD1963_PIN_DC ;
	*/
	//SSD1963_WriteCommand(SSD1963_SET_TEAR_OFF);
	//SSD1963_WriteCommand(SSD1963_ENTER_INVERT_MODE);
	SSD1963_Init();
	SSD1963_FillArea(0,300,0,300,0x292929);
	
	while (1)
	{
		//ledOn();
		//char val[20];
		//printf("Testing\n");
		//scanf("%s",val);
		for (i = 0; i < 0x0007FFFF; i++)
		{
		}
		//printf("Value entered: %s\n",val);
		//ledOff();
		for (i = 0; i < 0x0007FFFF; i++)
		{
		}
		
	}
}
