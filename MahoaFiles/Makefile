CFLAG=-lsodium
all: enc	dec

enc:	enc.c
	gcc $(CFLAG) enc.c -o enc

dec: 	dec.c
	gcc $(CFLAG) dec.c -o dec

sig:	sig.c
	gcc $(CFLAG) sig.c -o test
run:	test
	./test
clean:
	rm enc dec
	rm test

