#include "LPC11xx.h"
#include <stdio.h>
#include <rt_misc.h>

/* Import external functions from Serial.c file                               */
extern void SER_init (void);

#define SSD1963_PIN_RD	(1 << 4)
#define SSD1963_PIN_WR	(1 << 9)
#define SSD1963_PIN_CS	(1 << )
#define SSD1963_PIN_A0	(1 << )
#define SSD1963_PIN_RST	(1 << )

#define LPC_GPIO0 SSD1963_DATA
#define LPC_GPIO1 SSD1963_CMD

void configureGPIO()
{
    LPC_GPIO0->DIR |= (1<<1);

}
1 - 
void SSD1963_WriteCommand(unsigned int commandToWrite){
	SSD1963_DATA->DATA = (commandToWrite << 1) | (SSD1963_DATA & 0x1);
	SSD1963_CMD ->DATA |= SSD1963_PIN_RD 
	
	SSD1963_CMD ->DATA &= /*~SSD1963_PIN_A0 &~SSD1963_PIN_CS &*/ ~SSD1963_PIN_WR;
	asm('nop')	
	SSD1963_CMD ->DATA |= /*SSD1963_PIN_A0 |SSD1963_PIN_CS |*/ SSD1963_PIN_WR;
}


void SSD1963_WriteData(unsigned int dataToWrite)
{
	SSD1963_DATA->DATA = (dataToWrite << 1) | (SSD1963_DATA & 0x1);
	//set bit 0,3
	SSD1963_CMD->DATA  |= SSD1963_PIN_RD /*| SSD1963_PIN_A0*/;
	//clear bit 2,1
	SSD1963_CMD-> DATA &= /*SSD1963_PIN_CS |*/ ~SSD1963_PIN_WR;
	asm("nop");
	//set bit 2,1
	SSD1963_CMD->DATA  |= /*SSD1963_PIN_CS |*/ SSD1963_PIN_WR;
}


int main()
{
	configureGPIO();
	while (1)
	{
		
	}
}
