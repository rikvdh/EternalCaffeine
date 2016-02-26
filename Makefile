COMPILE=gcc --std=c99 -Wall
LINK=-lm

all: halflife.o drinks.o text_interface.o
	$(COMPILE) main.c halflife.o drinks.o text_interface.o -o ec $(LINK)
	
halflife.o:
	$(COMPILE) -c halflife.c -o halflife.o

drinks.o:
	$(COMPILE) -c drinks.c -o drinks.o

text_interface.o:
	$(COMPILE) -c text_interface.c -o text_interface.o

clean:
	rm halflife.o drinks.o text_interface.o

install:
	cp ./ec /usr/sbin/
	cp ./drinks.txt /usr/sbin/drinks.txt
	
uninstall:
	rm /usr/sbin/ec /usr/sbin/drinks.txt
