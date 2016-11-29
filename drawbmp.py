import PIL
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
font = ImageFont.truetype("../Downloads/TNR.ttf",25)
img = Image.new("RGBA", (480,800),(255,255,2))
draw = ImageDraw.Draw(img)
draw.text((0, 0),"This is a test",(255,255,0),font=font)
draw = ImageDraw.Draw(img)
draw = ImageDraw.Draw(img)
img = img.convert(mode="P", colors=255)
img.save("a_test.png")
