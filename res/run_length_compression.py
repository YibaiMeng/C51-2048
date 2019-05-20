from PIL import Image


def run_length_compression(im):
    '''This assumes a image of mode '1'.
    
    The format is as follow: for each line, x continuous white pixels are represented as x, x continuous black pixels are represented as -x, 0 represents the end of each line.
    
    The coordinate system is with 0,0 at topleft, and WIDTH, HEIGHT at bottom right
    
    For example:
    {-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-31,9,-31,0,-29,13,-29,0,-28,15,-28,0,-27,16,-28,0,-27,17,-27,0,-27,7,-3,7,-27,0,-26,7,-5,6,-27,0,-26,7,-5,6,-27,0,-30,3,-5,6,-27,0,-37,7,-27,0,-37,7,-27,0,-36,7,-28,0,-35,8,-28,0,-34,8,-29,0,-33,8,-30,0,-32,9,-30,0,-31,9,-31,0,-30,9,-32,0,-29,9,-33,0,-28,9,-34,0,-28,8,-35,0,-27,17,-27,0,-27,17,-27,0,-26,18,-27,0,-26,18,-27,0,-26,18,-27,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71,0,-71}
    
    '''
    w, h = im.size
    cnt = 0
    black_count = 0
    white_count = 0
    mode = None
    print("{", end="")
    for px in im.getdata():
        if px == 255:
            if mode == "black":
                print(-1 * black_count, end=",")
                black_count = 0      
            mode = "white"
            white_count+=1
        else:
            if mode == "white":
                print(white_count, end=",")
                white_count = 0
            mode = "black"
            black_count += 1
        
        cnt += 1
        if cnt % w == 0:
            if mode == "black":
                print(-1 * black_count, end=",")
                black_count = 0
                mode = None
            else:
                print(white_count, end=",")
                white_count = 0
                mode = None
            print("0", end="")
            if cnt != w * h:
                print(",", end="")
            else:
                print("};")
for i in range(1, 11 + 1, 1):
    im = Image.open("cvt/"+str(int(2 ** i)) + ".pbm")
    print("const __code uint8_t img_"+str(int(2 ** i))+" = ", end="")
    run_length_compression(im)
 

