CFLAG=-lsodium
all: enc	dec

enc:	enc.c
	gcc $(CFLAG) enc.c -o enc

dec: 	dec.c
	gcc $(CFLAG) dec.c -o dec

clean:
	rm *.o
	rm enc dec 

