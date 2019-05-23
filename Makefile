
SOURCES = $(wildcard src/*.c src/drivers/*.c)
HEADERS = $(wildcard include/*.h)
CC = sdcc
FLASHER = ec2writeflash
OUT_NAME = main
CC_FLAGS =  -mmcs51 -L/usr/local/share/sdcc/lib/large --model-large -I./include/
#-L/usr/local/share/sdcc/lib/small --model-small -I./include/

build/${OUT_NAME}.ihx : ${SOURCES} ${HEADERS}
	mkdir -p build/
	for file in ${SOURCES}; do \
		${CC} ${CC_FLAGS} -c $${file} -o build/; \
	done
	${CC} ${CC_FLAGS} build/*.rel -o build/${OUT_NAME}.ihx

# LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
.PHONY: flash
flash: build/${OUT_NAME}.ihx
	${FLASHER} --port USB --mode JTAG --hex build/${OUT_NAME}.ihx --run # --eraseall

.PHONY: clean
clean:
	rm -rf build/
