CFLAG=-lsodium
all: enc	dec

enc:	enc.c print.c	
	gcc $(CFLAG) enc.c print.c -o enc 

dec: 	dec.c
	gcc $(CFLAG) dec.c -o dec

sig:	sig.c
	gcc $(CFLAG) sig.c -o sig
clean:
	rm enc dec sig

