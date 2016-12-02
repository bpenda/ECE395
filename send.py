import sys
import struct
def pallet_256bmp(filename):
	f = open(filename, 'r')
	f.read(54)
	pal_arr = f.read(1024);
	f.close()
	i = len(pal_arr)-1
	while i >= 0:
		#sys.stdout.write(str(ord(pal_arr[i])) + ' ')
		if i%4 == 3:
			#print ""
			pal_arr = pal_arr[:i] + pal_arr[i+1:]
		i -=1
	return pal_arr


def data_256bmp(filename):
	f = open(filename, 'r')
	info = f.read(54)
	width = ord(info[18]) + (ord(info[19]) << 8) + (ord(info[20]) << 16) + (ord(info[21]) << 24)
	height = ord(info[22]) + (ord(info[23]) << 8) + (ord(info[24]) << 16) + (ord(info[25]) << 24)
	#print width 
	#print height
	f.read(1024);
	pix_data = f.read(width*height)
	f.close()
	return (width, height, pix_data)

def rlencode(data):
	a = ['0']*len(data)*2
	j = 0
	dlen = 1
	a[0] = data[0]
	for i in range(1,len(data)):
		if a[j] == data[i] and dlen < 0xCF :
			dlen +=1
		else:
			#print str(dlen) + ' - '+ str(ord(a[j]))
			a[j+1] = chr(dlen)
			dlen = 1
			j +=2
			a[j] = data[i] 
	print "final len" + str(j)
	return a


def main():
	if len(sys.argv) != 2:
		print "send.py filename_to_send"
		exit(1)
	pal = pallet_256bmp(sys.argv[1])
	(width,height,data) = data_256bmp(sys.argv[1])
	print len(data)
	encode = rlencode(data)
	print "Picture sent"

main()
'''
print "\n----------------------"
for i in range(0, len(a)):#
	if (i % 100) == 0:
		print ""
	sys.stdout.write(str(ord(a[i]))+ " ")
'''