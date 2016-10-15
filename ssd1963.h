#define TFT_FPS 30ULL
/*
#ifdef TFTCUSTOM
	#define TFT_WIDTH				0ULL
	#define TFT_HSYNC_BACK_PORCH	0ULL
	#define TFT_HSYNC_FRONT_PORCH	0ULL
	#define TFT_HSYNC_PULSE			0ULL
	
	#define TFT_HEIGHT				0ULL
	#define TFT_VSYNC_BACK_PORCH	0ULL
	#define TFT_VSYNC_FRONT_PORCH	0ULL
	#define TFT_VSYNC_PULSE			0ULL
#endif

#ifdef TFT320240
	#define TFT_WIDTH				320ULL
	#define TFT_HSYNC_BACK_PORCH	40ULL
	#define TFT_HSYNC_FRONT_PORCH	20ULL
	#define TFT_HSYNC_PULSE			28ULL
	
	#define TFT_HEIGHT				240ULL
	#define TFT_VSYNC_BACK_PORCH	17ULL
	#define TFT_VSYNC_FRONT_PORCH	4ULL
	#define TFT_VSYNC_PULSE			3ULL
#endif

#ifdef TFT800480
*/
	#define TFT_WIDTH				800ULL
	#define TFT_HSYNC_BACK_PORCH	30LL
	#define TFT_HSYNC_FRONT_PORCH	0ULL
	#define TFT_HSYNC_PULSE			0ULL
	
	#define TFT_HEIGHT				480ULL
	#define TFT_VSYNC_BACK_PORCH	10ULL
	#define TFT_VSYNC_FRONT_PORCH	0ULL
	#define TFT_VSYNC_PULSE			0ULL
/*
#endif

#ifdef TFT640480

	#define TFT_WIDTH				640ULL
	#define TFT_HSYNC_BACK_PORCH	56ULL
	#define TFT_HSYNC_FRONT_PORCH	8ULL
	#define TFT_HSYNC_PULSE			96ULL

	#define TFT_HEIGHT				480ULL
	#define TFT_VSYNC_BACK_PORCH	41ULL
	#define TFT_VSYNC_FRONT_PORCH	2ULL
	#define TFT_VSYNC_PULSE			2ULL
#endif

*/

#define	TFT_HSYNC_PERIOD	(TFT_HSYNC_PULSE + TFT_HSYNC_BACK_PORCH + TFT_WIDTH  + TFT_HSYNC_FRONT_PORCH)
#define	TFT_VSYNC_PERIOD	(TFT_VSYNC_PULSE + TFT_VSYNC_BACK_PORCH + TFT_HEIGHT + TFT_VSYNC_FRONT_PORCH)

#define TFT_PCLK	(TFT_HSYNC_PERIOD * TFT_VSYNC_PERIOD * TFT_FPS)
//#define TFT_PCLK (928 * 525 * 60)
#define LCD_FPR		((TFT_PCLK * 1048576)/100000000)

#define mHIGH(x) (x >> 8)
#define mLOW(x) (x & 0xFF)
//=============================================================================
// SSD1963 commands
//=============================================================================
#define SSD1963_NOP						0x00
#define SSD1963_SOFT_RESET  			0x01
#define SSD1963_GET_POWER_MODE 			0x0A
#define SSD1963_GET_ADDRESS_MODE		0x0B
#define SSD1963_GET_DISPLAY_MODE		0x0D
#define SSD1963_GET_TEAR_EFFECT_STATUS 	0x0E
#define SSD1963_ENTER_SLEEP_MODE		0x10
#define SSD1963_EXIT_SLEEP_MODE			0x11
#define SSD1963_ENTER_PARTIAL_MODE		0x12
#define SSD1963_ENTER_NORMAL_MODE		0x13
#define SSD1963_EXIT_INVERT_MODE		0x20
#define SSD1963_ENTER_INVERT_MODE		0x21
#define SSD1963_SET_GAMMA_CURVE			0x26
#define SSD1963_SET_DISPLAY_OFF			0x28
#define SSD1963_SET_DISPLAY_ON			0x29
#define SSD1963_SET_COLUMN_ADDRESS		0x2A
#define SSD1963_SET_PAGE_ADDRESS		0x2B
#define SSD1963_WRITE_MEMORY_START		0x2C
#define SSD1963_READ_MEMORY_START		0x2E
#define SSD1963_SET_PARTIAL_AREA		0x30
#define SSD1963_SET_SCROLL_AREA			0x33
#define SSD1963_SET_TEAR_OFF			0x34
#define SSD1963_SET_TEAR_ON				0x35
#define SSD1963_SET_ADDRESS_MODE		0x36
#define SSD1963_SET_SCROLL_START		0x37
#define SSD1963_EXIT_IDLE_MODE			0x38
#define SSD1963_ENTER_IDLE_MODE			0x39
#define SSD1963_WRITE_MEMORY_CONTINUE	0x3C
#define SSD1963_READ_MEMORY_CONTINUE	0x3E
#define SSD1963_SET_TEAR_SCANLINE		0x44
#define SSD1963_GET_SCANLINE			0x45
#define SSD1963_READ_DDB				0xA1
#define SSD1963_SET_LCD_MODE			0xB0
#define SSD1963_GET_LCD_MODE			0xB1
#define SSD1963_SET_HORI_PERIOD			0xB4
#define SSD1963_GET_HORI_PERIOD			0xB5
#define SSD1963_SET_VERT_PERIOD			0xB6
#define SSD1963_GET_VERT_PERIOD			0xB7
#define SSD1963_SET_GPIO_CONF			0xB8
#define SSD1963_GET_GPIO_CONF			0xB9
#define SSD1963_SET_GPIO_VALUE			0xBA
#define SSD1963_GET_GPIO_STATUS			0xBB
#define SSD1963_SET_POST_PROC			0xBC
#define SSD1963_GET_POST_PROC			0xBD
#define SSD1963_SET_PWM_CONF			0xBE
#define SSD1963_GET_PWM_CONF			0xBF
#define SSD1963_GET_LCD_GEN0			0xC0
#define SSD1963_SET_LCD_GEN0			0xC1
#define SSD1963_GET_LCD_GEN1			0xC2
#define SSD1963_SET_LCD_GEN1			0xC3
#define SSD1963_GET_LCD_GEN2			0xC4
#define SSD1963_SET_LCD_GEN2			0xC5
#define SSD1963_GET_LCD_GEN3			0xC6
#define SSD1963_SET_LCD_GEN3			0xC7
#define SSD1963_SET_GPIO0_ROP			0xC8
#define SSD1963_GET_GPIO0_ROP			0xC9
#define SSD1963_SET_GPIO1_ROP			0xCA
#define SSD1963_GET_GPIO1_ROP			0xCB
#define SSD1963_SET_GPIO2_ROP			0xCC
#define SSD1963_GET_GPIO2_ROP			0xCD
#define SSD1963_SET_GPIO3_ROP			0xCE
#define SSD1963_GET_GPIO3_ROP			0xCF
#define SSD1963_SET_DBC_CONF			0xD0
#define SSD1963_GET_DBC_CONF			0xD1
#define SSD1963_SET_DBC_TH				0xD4
#define SSD1963_GET_DBC_TH				0xD5
#define SSD1963_SET_PLL					0xE0
#define SSD1963_SET_PLL_MN				0xE2
#define SSD1963_GET_PLL_MN				0xE3
#define SSD1963_GET_PLL_STATUS			0xE4
#define SSD1963_SET_DEEP_SLEEP			0xE5
#define SSD1963_SET_LSHIFT_FREQ			0xE6
#define SSD1963_GET_LSHIFT_FREQ			0xE7
#define SSD1963_SET_PIXEL_DATA_INTERFACE 0xF0
	#define SSD1963_PDI_8BIT			0
	#define SSD1963_PDI_12BIT			1
	#define SSD1963_PDI_16BIT			2
	#define SSD1963_PDI_16BIT565		3
	#define SSD1963_PDI_18BIT			4
	#define SSD1963_PDI_24BIT			5
	#define SSD1963_PDI_9BIT			6
#define SSD1963_GET_PIXEL_DATA_INTERFACE 0xF1
#define arr_size 162000ULL


static unsigned char font_rom[1600] = {
				// code x20
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x00, // 5
        0x00, // 6
        0x00, // 7
        0x00, // 8
        0x00, // 9
        0x00, // a
        0x00, // b
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x21
        0x00, // 0
        0x00, // 1
        0x18, // 2    **
        0x3C, // 3   ****
        0x3C, // 4   ****
        0x3C, // 5   ****
        0x18, // 6    **
        0x18, // 7    **
        0x18, // 8    **
        0x00, // 9
        0x18, // a    **
        0x18, // b    **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x22
        0x00, // 0
        0x66, // 1  **  **
        0x66, // 2  **  **
        0x66, // 3  **  **
        0x24, // 4   *  *
        0x00, // 5
        0x00, // 6
        0x00, // 7
        0x00, // 8
        0x00, // 9
        0x00, // a
        0x00, // b
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x23
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x6C, // 3  ** **
        0x6C, // 4  ** **
        0xFE, // 5 *******
        0x6C, // 6  ** **
        0x6C, // 7  ** **
        0x6C, // 8  ** **
        0xFE, // 9 *******
        0x6C, // a  ** **
        0x6C, // b  ** **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x24
        0x18, // 0     **
        0x18, // 1     **
        0x7C, // 2   *****
        0xC6, // 3  **   **
        0xC2, // 4  **    *
        0xC0, // 5  **
        0x7C, // 6   *****
        0x06, // 7       **
        0x06, // 8       **
        0x86, // 9  *    **
        0xC6, // a  **   **
        0x7C, // b   *****
        0x18, // c     **
        0x18, // d     **
        0x00, // e
        0x00, // f
         // code x25
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0xC2, // 4 **    *
        0xC6, // 5 **   **
        0x0C, // 6     **
        0x18, // 7    **
        0x30, // 8   **
        0x60, // 9  **
        0xC6, // a **   **
        0x86, // b *    **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x26
        0x00, // 0
        0x00, // 1
        0x38, // 2   ***
        0x6C, // 3  ** **
        0x6C, // 4  ** **
        0x38, // 5   ***
        0x76, // 6  *** **
        0xDC, // 7 ** ***
        0xCC, // 8 **  **
        0xCC, // 9 **  **
        0xCC, // a **  **
        0x76, // b  *** **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x27
        0x00, // 0
        0x30, // 1   **
        0x30, // 2   **
        0x30, // 3   **
        0x60, // 4  **
        0x00, // 5
        0x00, // 6
        0x00, // 7
        0x00, // 8
        0x00, // 9
        0x00, // a
        0x00, // b
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x28
        0x00, // 0
        0x00, // 1
        0x0C, // 2     **
        0x18, // 3    **
        0x30, // 4   **
        0x30, // 5   **
        0x30, // 6   **
        0x30, // 7   **
        0x30, // 8   **
        0x30, // 9   **
        0x18, // a    **
        0x0C, // b     **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x29
        0x00, // 0
        0x00, // 1
        0x30, // 2   **
        0x18, // 3    **
        0x0C, // 4     **
        0x0C, // 5     **
        0x0C, // 6     **
        0x0C, // 7     **
        0x0C, // 8     **
        0x0C, // 9     **
        0x18, // a    **
        0x30, // b   **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x2a
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x66, // 5  **  **
        0x3C, // 6   ****
        0xFF, // 7 ********
        0x3C, // 8   ****
        0x66, // 9  **  **
        0x00, // a
        0x00, // b
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x2b
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x18, // 5    **
        0x18, // 6    **
        0x7E, // 7  ******
        0x18, // 8    **
        0x18, // 9    **
        0x00, // a
        0x00, // b
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x2c
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x00, // 5
        0x00, // 6
        0x00, // 7
        0x00, // 8
        0x18, // 9    **
        0x18, // a    **
        0x18, // b    **
        0x30, // c   **
        0x00, // d
        0x00, // e
        0x00, // f
         // code x2d
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x00, // 5
        0x00, // 6
        0x7E, // 7  ******
        0x00, // 8
        0x00, // 9
        0x00, // a
        0x00, // b
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x2e
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x00, // 5
        0x00, // 6
        0x00, // 7
        0x00, // 8
        0x00, // 9
        0x18, // a    **
        0x18, // b    **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x2f
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x02, // 4       *
        0x06, // 5      **
        0x0C, // 6     **
        0x18, // 7    **
        0x30, // 8   **
        0x60, // 9  **
        0xC0, // a **
        0x80, // b *
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x30
        0x00, // 0
        0x00, // 1
        0x7C, // 2  *****
        0xC6, // 3 **   **
        0xC6, // 4 **   **
        0xCE, // 5 **  ***
        0xDE, // 6 ** ****
        0xF6, // 7 **** **
        0xE6, // 8 ***  **
        0xC6, // 9 **   **
        0xC6, // a **   **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x31
        0x00, // 0
        0x00, // 1
        0x18, // 2
        0x38, // 3
        0x78, // 4    **
        0x18, // 5   ***
        0x18, // 6  ****
        0x18, // 7    **
        0x18, // 8    **
        0x18, // 9    **
        0x18, // a    **
        0x7E, // b    **
        0x00, // c    **
        0x00, // d  ******
        0x00, // e
        0x00, // f
         // code x32
        0x00, // 0
        0x00, // 1
        0x7C, // 2  *****
        0xC6, // 3 **   **
        0x06, // 4      **
        0x0C, // 5     **
        0x18, // 6    **
        0x30, // 7   **
        0x60, // 8  **
        0xC0, // 9 **
        0xC6, // a **   **
        0xFE, // b *******
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x33
        0x00, // 0
        0x00, // 1
        0x7C, // 2  *****
        0xC6, // 3 **   **
        0x06, // 4      **
        0x06, // 5      **
        0x3C, // 6   ****
        0x06, // 7      **
        0x06, // 8      **
        0x06, // 9      **
        0xC6, // a **   **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x34
        0x00, // 0
        0x00, // 1
        0x0C, // 2     **
        0x1C, // 3    ***
        0x3C, // 4   ****
        0x6C, // 5  ** **
        0xCC, // 6 **  **
        0xFE, // 7 *******
        0x0C, // 8     **
        0x0C, // 9     **
        0x0C, // a     **
        0x1E, // b    ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x35
        0x00, // 0
        0x00, // 1
        0xFE, // 2 *******
        0xC0, // 3 **
        0xC0, // 4 **
        0xC0, // 5 **
        0xFC, // 6 ******
        0x06, // 7      **
        0x06, // 8      **
        0x06, // 9      **
        0xC6, // a **   **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x36
        0x00, // 0
        0x00, // 1
        0x38, // 2   ***
        0x60, // 3  **
        0xC0, // 4 **
        0xC0, // 5 **
        0xFC, // 6 ******
        0xC6, // 7 **   **
        0xC6, // 8 **   **
        0xC6, // 9 **   **
        0xC6, // a **   **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x37
        0x00, // 0
        0x00, // 1
        0xFE, // 2 *******
        0xC6, // 3 **   **
        0x06, // 4      **
        0x06, // 5      **
        0x0C, // 6     **
        0x18, // 7    **
        0x30, // 8   **
        0x30, // 9   **
        0x30, // a   **
        0x30, // b   **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x38
        0x00, // 0
        0x00, // 1
        0x7C, // 2  *****
        0xC6, // 3 **   **
        0xC6, // 4 **   **
        0xC6, // 5 **   **
        0x7C, // 6  *****
        0xC6, // 7 **   **
        0xC6, // 8 **   **
        0xC6, // 9 **   **
        0xC6, // a **   **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x39
        0x00, // 0
        0x00, // 1
        0x7C, // 2  *****
        0xC6, // 3 **   **
        0xC6, // 4 **   **
        0xC6, // 5 **   **
        0x7E, // 6  ******
        0x06, // 7      **
        0x06, // 8      **
        0x06, // 9      **
        0x0C, // a     **
        0x78, // b  ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x3a
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x18, // 4    **
        0x18, // 5    **
        0x00, // 6
        0x00, // 7
        0x00, // 8
        0x18, // 9    **
        0x18, // a    **
        0x00, // b
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x3b
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x18, // 4    **
        0x18, // 5    **
        0x00, // 6
        0x00, // 7
        0x00, // 8
        0x18, // 9    **
        0x18, // a    **
        0x30, // b   **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x3c
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x06, // 3      **
        0x0C, // 4     **
        0x18, // 5    **
        0x30, // 6   **
        0x60, // 7  **
        0x30, // 8   **
        0x18, // 9    **
        0x0C, // a     **
        0x06, // b      **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x3d
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x7E, // 5  ******
        0x00, // 6
        0x00, // 7
        0x7E, // 8  ******
        0x00, // 9
        0x00, // a
        0x00, // b
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x3e
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x60, // 3  **
        0x30, // 4   **
        0x18, // 5    **
        0x0C, // 6     **
        0x06, // 7      **
        0x0C, // 8     **
        0x18, // 9    **
        0x30, // a   **
        0x60, // b  **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x3f
        0x00, // 0
        0x00, // 1
        0x7C, // 2  *****
        0xC6, // 3 **   **
        0xC6, // 4 **   **
        0x0C, // 5     **
        0x18, // 6    **
        0x18, // 7    **
        0x18, // 8    **
        0x00, // 9
        0x18, // a    **
        0x18, // b    **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x40
        0x00, // 0
        0x00, // 1
        0x7C, // 2  *****
        0xC6, // 3 **   **
        0xC6, // 4 **   **
        0xC6, // 5 **   **
        0xDE, // 6 ** ****
        0xDE, // 7 ** ****
        0xDE, // 8 ** ****
        0xDC, // 9 ** ***
        0xC0, // a **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x41
        0x00, // 0
        0x00, // 1
        0x10, // 2    *
        0x38, // 3   ***
        0x6C, // 4  ** **
        0xC6, // 5 **   **
        0xC6, // 6 **   **
        0xFE, // 7 *******
        0xC6, // 8 **   **
        0xC6, // 9 **   **
        0xC6, // a **   **
        0xC6, // b **   **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x42
        0x00, // 0
        0x00, // 1
        0xFC, // 2 ******
        0x66, // 3  **  **
        0x66, // 4  **  **
        0x66, // 5  **  **
        0x7C, // 6  *****
        0x66, // 7  **  **
        0x66, // 8  **  **
        0x66, // 9  **  **
        0x66, // a  **  **
        0xFC, // b ******
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x43
        0x00, // 0
        0x00, // 1
        0x3C, // 2   ****
        0x66, // 3  **  **
        0xC2, // 4 **    *
        0xC0, // 5 **
        0xC0, // 6 **
        0xC0, // 7 **
        0xC0, // 8 **
        0xC2, // 9 **    *
        0x66, // a  **  **
        0x3C, // b   ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x44
        0x00, // 0
        0x00, // 1
        0xF8, // 2 *****
        0x6C, // 3  ** **
        0x66, // 4  **  **
        0x66, // 5  **  **
        0x66, // 6  **  **
        0x66, // 7  **  **
        0x66, // 8  **  **
        0x66, // 9  **  **
        0x6C, // a  ** **
        0xF8, // b *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x45
        0x00, // 0
        0x00, // 1
        0xFE, // 2 *******
        0x66, // 3  **  **
        0x62, // 4  **   *
        0x68, // 5  ** *
        0x78, // 6  ****
        0x68, // 7  ** *
        0x60, // 8  **
        0x62, // 9  **   *
        0x66, // a  **  **
        0xFE, // b *******
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x46
        0x00, // 0
        0x00, // 1
        0xFE, // 2 *******
        0x66, // 3  **  **
        0x62, // 4  **   *
        0x68, // 5  ** *
        0x78, // 6  ****
        0x68, // 7  ** *
        0x60, // 8  **
        0x60, // 9  **
        0x60, // a  **
        0xF0, // b ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x47
        0x00, // 0
        0x00, // 1
        0x3C, // 2   ****
        0x66, // 3  **  **
        0xC2, // 4 **    *
        0xC0, // 5 **
        0xC0, // 6 **
        0xDE, // 7 ** ****
        0xC6, // 8 **   **
        0xC6, // 9 **   **
        0x66, // a  **  **
        0x3A, // b   *** *
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x48
        0x00, // 0
        0x00, // 1
        0xC6, // 2 **   **
        0xC6, // 3 **   **
        0xC6, // 4 **   **
        0xC6, // 5 **   **
        0xFE, // 6 *******
        0xC6, // 7 **   **
        0xC6, // 8 **   **
        0xC6, // 9 **   **
        0xC6, // a **   **
        0xC6, // b **   **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x49
        0x00, // 0
        0x00, // 1
        0x3C, // 2   ****
        0x18, // 3    **
        0x18, // 4    **
        0x18, // 5    **
        0x18, // 6    **
        0x18, // 7    **
        0x18, // 8    **
        0x18, // 9    **
        0x18, // a    **
        0x3C, // b   ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x4a
        0x00, // 0
        0x00, // 1
        0x1E, // 2    ****
        0x0C, // 3     **
        0x0C, // 4     **
        0x0C, // 5     **
        0x0C, // 6     **
        0x0C, // 7     **
        0xCC, // 8 **  **
        0xCC, // 9 **  **
        0xCC, // a **  **
        0x78, // b  ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x4b
        0x00, // 0
        0x00, // 1
        0xE6, // 2 ***  **
        0x66, // 3  **  **
        0x66, // 4  **  **
        0x6C, // 5  ** **
        0x78, // 6  ****
        0x78, // 7  ****
        0x6C, // 8  ** **
        0x66, // 9  **  **
        0x66, // a  **  **
        0xE6, // b ***  **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x4c
        0x00, // 0
        0x00, // 1
        0xF0, // 2 ****
        0x60, // 3  **
        0x60, // 4  **
        0x60, // 5  **
        0x60, // 6  **
        0x60, // 7  **
        0x60, // 8  **
        0x62, // 9  **   *
        0x66, // a  **  **
        0xFE, // b *******
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x4d
        0x00, // 0
        0x00, // 1
        0xC3, // 2 **    **
        0xE7, // 3 ***  ***
        0xFF, // 4 ********
        0xFF, // 5 ********
        0xDB, // 6 ** ** **
        0xC3, // 7 **    **
        0xC3, // 8 **    **
        0xC3, // 9 **    **
        0xC3, // a **    **
        0xC3, // b **    **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x4e
        0x00, // 0
        0x00, // 1
        0xC6, // 2 **   **
        0xE6, // 3 ***  **
        0xF6, // 4 **** **
        0xFE, // 5 *******
        0xDE, // 6 ** ****
        0xCE, // 7 **  ***
        0xC6, // 8 **   **
        0xC6, // 9 **   **
        0xC6, // a **   **
        0xC6, // b **   **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x4f
        0x00, // 0
        0x00, // 1
        0x7C, // 2  *****
        0xC6, // 3 **   **
        0xC6, // 4 **   **
        0xC6, // 5 **   **
        0xC6, // 6 **   **
        0xC6, // 7 **   **
        0xC6, // 8 **   **
        0xC6, // 9 **   **
        0xC6, // a **   **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x50
        0x00, // 0
        0x00, // 1
        0xFC, // 2 ******
        0x66, // 3  **  **
        0x66, // 4  **  **
        0x66, // 5  **  **
        0x7C, // 6  *****
        0x60, // 7  **
        0x60, // 8  **
        0x60, // 9  **
        0x60, // a  **
        0xF0, // b ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x510
        0x00, // 0
        0x00, // 1
        0x7C, // 2  *****
        0xC6, // 3 **   **
        0xC6, // 4 **   **
        0xC6, // 5 **   **
        0xC6, // 6 **   **
        0xC6, // 7 **   **
        0xC6, // 8 **   **
        0xD6, // 9 ** * **
        0xDE, // a ** ****
        0x7C, // b  *****
        0x0C, // c     **
        0x0E, // d     ***
        0x00, // e
        0x00, // f
         // code x52
        0x00, // 0
        0x00, // 1
        0xFC, // 2 ******
        0x66, // 3  **  **
        0x66, // 4  **  **
        0x66, // 5  **  **
        0x7C, // 6  *****
        0x6C, // 7  ** **
        0x66, // 8  **  **
        0x66, // 9  **  **
        0x66, // a  **  **
        0xE6, // b ***  **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x53
        0x00, // 0
        0x00, // 1
        0x7C, // 2  *****
        0xC6, // 3 **   **
        0xC6, // 4 **   **
        0x60, // 5  **
        0x38, // 6   ***
        0x0C, // 7     **
        0x06, // 8      **
        0xC6, // 9 **   **
        0xC6, // a **   **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x54
        0x00, // 0
        0x00, // 1
        0xFF, // 2 ********
        0xDB, // 3 ** ** **
        0x99, // 4 *  **  *
        0x18, // 5    **
        0x18, // 6    **
        0x18, // 7    **
        0x18, // 8    **
        0x18, // 9    **
        0x18, // a    **
        0x3C, // b   ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x55
        0x00, // 0
        0x00, // 1
        0xC6, // 2 **   **
        0xC6, // 3 **   **
        0xC6, // 4 **   **
        0xC6, // 5 **   **
        0xC6, // 6 **   **
        0xC6, // 7 **   **
        0xC6, // 8 **   **
        0xC6, // 9 **   **
        0xC6, // a **   **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x56
        0x00, // 0
        0x00, // 1
        0xC3, // 2 **    **
        0xC3, // 3 **    **
        0xC3, // 4 **    **
        0xC3, // 5 **    **
        0xC3, // 6 **    **
        0xC3, // 7 **    **
        0xC3, // 8 **    **
        0x66, // 9  **  **
        0x3C, // a   ****
        0x18, // b    **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x57
        0x00, // 0
        0x00, // 1
        0xC3, // 2 **    **
        0xC3, // 3 **    **
        0xC3, // 4 **    **
        0xC3, // 5 **    **
        0xC3, // 6 **    **
        0xDB, // 7 ** ** **
        0xDB, // 8 ** ** **
        0xFF, // 9 ********
        0x66, // a  **  **
        0x66, // b  **  **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
        
         // code x58
        0x00, // 0
        0x00, // 1
        0xC3, // 2 **    **
        0xC3, // 3 **    **
        0x66, // 4  **  **
        0x3C, // 5   ****
        0x18, // 6    **
        0x18, // 7    **
        0x3C, // 8   ****
        0x66, // 9  **  **
        0xC3, // a **    **
        0xC3, // b **    **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x59
        0x00, // 0
        0x00, // 1
        0xC3, // 2 **    **
        0xC3, // 3 **    **
        0xC3, // 4 **    **
        0x66, // 5  **  **
        0x3C, // 6   ****
        0x18, // 7    **
        0x18, // 8    **
        0x18, // 9    **
        0x18, // a    **
        0x3C, // b   ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x5a
        0x00, // 0
        0x00, // 1
        0xFF, // 2 ********
        0xC3, // 3 **    **
        0x86, // 4 *    **
        0x0C, // 5     **
        0x18, // 6    **
        0x30, // 7   **
        0x60, // 8  **
        0xC1, // 9 **     *
        0xC3, // a **    **
        0xFF, // b ********
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x5b
        0x00, // 0
        0x00, // 1
        0x3C, // 2   ****
        0x30, // 3   **
        0x30, // 4   **
        0x30, // 5   **
        0x30, // 6   **
        0x30, // 7   **
        0x30, // 8   **
        0x30, // 9   **
        0x30, // a   **
        0x3C, // b   ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x5c
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x80, // 3 *
        0xC0, // 4 **
        0xE0, // 5 ***
        0x70, // 6  ***
        0x38, // 7   ***
        0x1C, // 8    ***
        0x0E, // 9     ***
        0x06, // a      **
        0x02, // b       *
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x5d
        0x00, // 0
        0x00, // 1
        0x3C, // 2   ****
        0x0C, // 3     **
        0x0C, // 4     **
        0x0C, // 5     **
        0x0C, // 6     **
        0x0C, // 7     **
        0x0C, // 8     **
        0x0C, // 9     **
        0x0C, // a     **
        0x3C, // b   ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x5e
        0x10, // 0    *
        0x38, // 1   ***
        0x6C, // 2  ** **
        0xC6, // 3 **   **
        0x00, // 4
        0x00, // 5
        0x00, // 6
        0x00, // 7
        0x00, // 8
        0x00, // 9
        0x00, // a
        0x00, // b
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x5f
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x00, // 5
        0x00, // 6
        0x00, // 7
        0x00, // 8
        0x00, // 9
        0x00, // a
        0x00, // b
        0x00, // c
        0xFF, // d ********
        0x00, // e
        0x00, // f
         // code x60
        0x30, // 0   **
        0x30, // 1   **
        0x18, // 2    **
        0x00, // 3
        0x00, // 4
        0x00, // 5
        0x00, // 6
        0x00, // 7
        0x00, // 8
        0x00, // 9
        0x00, // a
        0x00, // b
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x61
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x78, // 5  ****
        0x0C, // 6     **
        0x7C, // 7  *****
        0xCC, // 8 **  **
        0xCC, // 9 **  **
        0xCC, // a **  **
        0x76, // b  *** **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x62
        0x00, // 0
        0x00, // 1
        0xE0, // 2  ***
        0x60, // 3   **
        0x60, // 4   **
        0x78, // 5   ****
        0x6C, // 6   ** **
        0x66, // 7   **  **
        0x66, // 8   **  **
        0x66, // 9   **  **
        0x66, // a   **  **
        0x7C, // b   *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x63
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x7C, // 5  *****
        0xC6, // 6 **   **
        0xC0, // 7 **
        0xC0, // 8 **
        0xC0, // 9 **
        0xC6, // a **   **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x64
        0x00, // 0
        0x00, // 1
        0x1C, // 2    ***
        0x0C, // 3     **
        0x0C, // 4     **
        0x3C, // 5   ****
        0x6C, // 6  ** **
        0xCC, // 7 **  **
        0xCC, // 8 **  **
        0xCC, // 9 **  **
        0xCC, // a **  **
        0x76, // b  *** **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x65
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x7C, // 5  *****
        0xC6, // 6 **   **
        0xFE, // 7 *******
        0xC0, // 8 **
        0xC0, // 9 **
        0xC6, // a **   **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x66
        0x00, // 0
        0x00, // 1
        0x38, // 2   ***
        0x6C, // 3  ** **
        0x64, // 4  **  *
        0x60, // 5  **
        0xF0, // 6 ****
        0x60, // 7  **
        0x60, // 8  **
        0x60, // 9  **
        0x60, // a  **
        0xF0, // b ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x67
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x76, // 5  *** **
        0xCC, // 6 **  **
        0xCC, // 7 **  **
        0xCC, // 8 **  **
        0xCC, // 9 **  **
        0xCC, // a **  **
        0x7C, // b  *****
        0x0C, // c     **
        0xCC, // d **  **
        0x78, // e  ****
        0x00, // f
         // code x68
        0x00, // 0
        0x00, // 1
        0xE0, // 2 ***
        0x60, // 3  **
        0x60, // 4  **
        0x6C, // 5  ** **
        0x76, // 6  *** **
        0x66, // 7  **  **
        0x66, // 8  **  **
        0x66, // 9  **  **
        0x66, // a  **  **
        0xE6, // b ***  **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x69
        0x00, // 0
        0x00, // 1
        0x18, // 2    **
        0x18, // 3    **
        0x00, // 4
        0x38, // 5   ***
        0x18, // 6    **
        0x18, // 7    **
        0x18, // 8    **
        0x18, // 9    **
        0x18, // a    **
        0x3C, // b   ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x6a
        0x00, // 0
        0x00, // 1
        0x06, // 2      **
        0x06, // 3      **
        0x00, // 4
        0x0E, // 5     ***
        0x06, // 6      **
        0x06, // 7      **
        0x06, // 8      **
        0x06, // 9      **
        0x06, // a      **
        0x06, // b      **
        0x66, // c  **  **
        0x66, // d  **  **
        0x3C, // e   ****
        0x00, // f
         // code x6b
        0x00, // 0
        0x00, // 1
        0xE0, // 2 ***
        0x60, // 3  **
        0x60, // 4  **
        0x66, // 5  **  **
        0x6C, // 6  ** **
        0x78, // 7  ****
        0x78, // 8  ****
        0x6C, // 9  ** **
        0x66, // a  **  **
        0xE6, // b ***  **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x6c
        0x00, // 0
        0x00, // 1
        0x38, // 2   ***
        0x18, // 3    **
        0x18, // 4    **
        0x18, // 5    **
        0x18, // 6    **
        0x18, // 7    **
        0x18, // 8    **
        0x18, // 9    **
        0x18, // a    **
        0x3C, // b   ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x6d
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0xE6, // 5 ***  **
        0xFF, // 6 ********
        0xDB, // 7 ** ** **
        0xDB, // 8 ** ** **
        0xDB, // 9 ** ** **
        0xDB, // a ** ** **
        0xDB, // b ** ** **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x6e
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0xDC, // 5 ** ***
        0x66, // 6  **  **
        0x66, // 7  **  **
        0x66, // 8  **  **
        0x66, // 9  **  **
        0x66, // a  **  **
        0x66, // b  **  **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x6f
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x7C, // 5  *****
        0xC6, // 6 **   **
        0xC6, // 7 **   **
        0xC6, // 8 **   **
        0xC6, // 9 **   **
        0xC6, // a **   **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x70
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0xDC, // 5 ** ***
        0x66, // 6  **  **
        0x66, // 7  **  **
        0x66, // 8  **  **
        0x66, // 9  **  **
        0x66, // a  **  **
        0x7C, // b  *****
        0x60, // c  **
        0x60, // d  **
        0xF0, // e ****
        0x00, // f
         // code x71
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x76, // 5  *** **
        0xCC, // 6 **  **
        0xCC, // 7 **  **
        0xCC, // 8 **  **
        0xCC, // 9 **  **
        0xCC, // a **  **
        0x7C, // b  *****
        0x0C, // c     **
        0x0C, // d     **
        0x1E, // e    ****
        0x00, // f
         // code x72
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0xDC, // 5 ** ***
        0x76, // 6  *** **
        0x66, // 7  **  **
        0x60, // 8  **
        0x60, // 9  **
        0x60, // a  **
        0xF0, // b ****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x73
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0x7C, // 5  *****
        0xC6, // 6 **   **
        0x60, // 7  **
        0x38, // 8   ***
        0x0C, // 9     **
        0xC6, // a **   **
        0x7C, // b  *****
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x74
        0x00, // 0
        0x00, // 1
        0x10, // 2    *
        0x30, // 3   **
        0x30, // 4   **
        0xFC, // 5 ******
        0x30, // 6   **
        0x30, // 7   **
        0x30, // 8   **
        0x30, // 9   **
        0x36, // a   ** **
        0x1C, // b    ***
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x75
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0xCC, // 5 **  **
        0xCC, // 6 **  **
        0xCC, // 7 **  **
        0xCC, // 8 **  **
        0xCC, // 9 **  **
        0xCC, // a **  **
        0x76, // b  *** **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x76
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0xC3, // 5 **    **
        0xC3, // 6 **    **
        0xC3, // 7 **    **
        0xC3, // 8 **    **
        0x66, // 9  **  **
        0x3C, // a   ****
        0x18, // b    **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x77
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0xC3, // 5 **    **
        0xC3, // 6 **    **
        0xC3, // 7 **    **
        0xDB, // 8 ** ** **
        0xDB, // 9 ** ** **
        0xFF, // a ********
        0x66, // b  **  **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x78
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0xC3, // 5 **    **
        0x66, // 6  **  **
        0x3C, // 7   ****
        0x18, // 8    **
        0x3C, // 9   ****
        0x66, // a  **  **
        0xC3, // b **    **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x79
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0xC6, // 5 **   **
        0xC6, // 6 **   **
        0xC6, // 7 **   **
        0xC6, // 8 **   **
        0xC6, // 9 **   **
        0xC6, // a **   **
        0x7E, // b  ******
        0x06, // c      **
        0x0C, // d     **
        0xF8, // e *****
        0x00, // f
         // code x7a
        0x00, // 0
        0x00, // 1
        0x00, // 2
        0x00, // 3
        0x00, // 4
        0xFE, // 5 *******
        0xCC, // 6 **  **
        0x18, // 7    **
        0x30, // 8   **
        0x60, // 9  **
        0xC6, // a **   **
        0xFE, // b *******
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x7b
        0x00, // 0
        0x00, // 1
        0x0E, // 2     ***
        0x18, // 3    **
        0x18, // 4    **
        0x18, // 5    **
        0x70, // 6  ***
        0x18, // 7    **
        0x18, // 8    **
        0x18, // 9    **
        0x18, // a    **
        0x0E, // b     ***
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x7c
        0x00, // 0
        0x00, // 1
        0x18, // 2    **
        0x18, // 3    **
        0x18, // 4    **
        0x18, // 5    **
        0x00, // 6
        0x18, // 7    **
        0x18, // 8    **
        0x18, // 9    **
        0x18, // a    **
        0x18, // b    **
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x7d
        0x00, // 0
        0x00, // 1
        0x70, // 2  ***
        0x18, // 3    **
        0x18, // 4    **
        0x18, // 5    **
        0x0E, // 6     ***
        0x18, // 7    **
        0x18, // 8    **
        0x18, // 9    **
        0x18, // a    **
        0x70, // b  ***
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
         // code x7e
        0x00, // 0
        0x00, // 1
        0x76, // 2  *** **
        0xDC, // 3 ** ***
        0x00, // 4
        0x00, // 5
        0x00, // 6
        0x00, // 7
        0x00, // 8
        0x00, // 9
        0x00, // a
        0x00, // b
        0x00, // c
        0x00, // d
        0x00, // e
        0x00, // f
        
		};
