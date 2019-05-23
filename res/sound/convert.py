with open("sound_data.raw", "rb") as fp:
    dat = fp.read()
print("This is what to write for SOUND_POSITION_END", len(dat) // 2)

with open("sound_data.inc","w") as fp:
    fp.write("__code const uint16_t sound_data[] = {")
    i = 0
    while i< len(dat):
        data = abs(dat[i] * 0x100 + dat[i+1] - 0x8000)
        fp.write(hex(data)+ ",")
        i+=2
    fp.write("0x0000};")

