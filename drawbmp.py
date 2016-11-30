import PIL
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

import server as serv

#CONSTS
SCREEN = (480, 800)

#COLOR PALETTE
BACKGROUND_COLOR    = (0,0,0)  
PRIMARY_TEXT        = (255,255,255)  
SECONDARY_TEXT      = (0,0,0)  
TERTIARY_TEXT       = (0,0,0)  

#Fonts
font1 = ImageFont.truetype("fonts/1.ttf",80)
font2 = ImageFont.truetype("fonts/1.ttf",30)
font3 = ImageFont.truetype("fonts/1.ttf",15)

#DATA
data = serv.getInfo()
TIME = data["DateTime"].split()[1]
DATE = data["DateTime"].split()[0]
TEMP = str(data["Weather"][1]['temp'])
WEAT = str(data["Weather"][0])
NEWS = "Headlines"
NEWS0 = "-- " + str(data["Headlines"][0])
NEWS1 = "-- " + str(data["Headlines"][1])
NEWS2 = "-- " + str(data["Headlines"][2])
NEWS3 = "-- " + str(data["Headlines"][3])

#TEMP Fix for double line news stories
if len(NEWS0) > 50:
    NEWS0 = NEWS0[:50] + "\n   " + NEWS0[50:]
if len(NEWS1) > 50:
    NEWS1 = NEWS1[:50] + "\n   " + NEWS1[50:]
if len(NEWS2) > 50:
    NEWS2 = NEWS2[:50] + "\n   " + NEWS2[50:]

def drawScreen():
    img = Image.new("RGBA", SCREEN, BACKGROUND_COLOR)
    draw = ImageDraw.Draw(img)
    im = Image.open("weather/" + WEAT + ".png").convert('RGBA')

    #DRAWING
    draw.text((20, 20),     TIME,   PRIMARY_TEXT,   font=font1)
    draw.text((20, 120),    DATE,   PRIMARY_TEXT,   font=font2)
    img.paste(im, (20,200), im)
    draw.text((30, 350),    TEMP,   PRIMARY_TEXT,   font=font2)
    draw.text((20, 420),    NEWS,   PRIMARY_TEXT,   font=font2)
    draw.text((20, 460),    NEWS0,   PRIMARY_TEXT,   font=font3)
    draw.text((20, 500),    NEWS1,   PRIMARY_TEXT,   font=font3)
    draw.text((20, 540),    NEWS2,   PRIMARY_TEXT,   font=font3)

    draw = ImageDraw.Draw(img)
    img = img.convert(mode="P", colors=255)
    img.save("a_test.bmp")
    img.show()

drawScreen()
