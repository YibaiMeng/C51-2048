#!/usr/bin/python3
import sys


def cvt(r,g,b):
    #print(r,g,b)
    rgb = r * 0x10000 + g * 0x100 + b
    #print(hex(rgb))
    #rgb = int(sys.argv[1], 16)
    assert(rgb >= 0 and rgb <= 0xFFFFFF)
    r = rgb & 0xFF0000
    g = rgb & 0x00FF00
    b = rgb & 0x0000FF
    #print(r,g,b)
    b = b >> 3 
    g = (g >> 5) & 0x7E0  
    r = (r >> 8) & 0xF800
    print(hex(r + g + b),end=",")
    
a = [0xfa, 0xf8, 0xef]
i = 0
while True:
    cvt(a[i],a[i+1],a[i+2])
    i += 3
    if i == len(a):
        break
    
