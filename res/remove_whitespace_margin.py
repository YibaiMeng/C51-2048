from PIL import Image


def remove_white_edge(filename):
    im = Image.open(filename)
    im = im.convert("RGB")
    bbox = im.getbbox()
    assert(bbox[3] - bbox[1] == bbox[2] - bbox[0] == 71) # should be
    im = im.crop(bbox)
    return im
    
def cvt_to_bw(im, filename):
    a= im.getcolors()
    a.sort(key=lambda x: x[0])  # TODO: A palette based compression?
    clr = a[-1][1]
    w, h = im.size
    cnt = 0
    for px in im.getdata():
        if px == clr:
            im.putpixel((int(cnt % w), int(cnt / w)), (0, 0, 0))
        else:
            im.putpixel((int(cnt % w), int(cnt / w)), (0xff, 0xff, 0xff))
        cnt += 1  
    im = im.convert("1")
    im.save("cvt/"+filename.split("/")[1].split(".")[0] + ".pbm")
    
import sys
for i in range(1, 11 + 1, 1): # 2 to 2048
    filename = "screenshots/"+str(int(2 ** i)) + ".png"
    cvt_to_bw(remove_white_edge(filename), filename)


