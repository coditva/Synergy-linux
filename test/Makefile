bins = dev0

all: $(bins)

dev0: dev0.o payload.o
	gcc -g dev0.o payload.o -o dev0
dev0.o: dev0.c
	gcc -g -c -I../include dev0.c

payload.o: ../src/payload.c
	gcc -g -c -I../include ../src/payload.c

.PHONY: clean
clean:
	rm -rf $(bins) *.o
