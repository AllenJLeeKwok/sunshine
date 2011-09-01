# @author guojiang2006@hotmal.com
#----------------------------------------------------
# python inputFile outputFile 9

import sys
import zlib

try:
    file = open(sys.argv[1], "rb")  #io.BufferedReader
    swf = open(sys.argv[2], "wb")
    level = sys.argv[3]
    b = file.read() #string
    print(len(b))
    listInt = range(len(b))
    for i in range(len(b)):
        listInt[i] = ord(b[i])
	
    print(listInt[0])
    print(listInt[1])
    print(listInt[2])	

    out = range(len(b))
    s = ''
    for i in range(len(listInt)):
        listInt[i] = (listInt[i] ^ i) & 255
        out[i] = chr(listInt[i])
        s += out[i]
    ret = zlib.compress(s, int(level))
    swf.write(ret)
except IOError:
    print(sys.stderr)
    print("File could not be opened")
    sys.exit(1)
