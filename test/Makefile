bins = dev0 dev1 dev2

all: $(bins)

dev0: dev0.o
	gcc dev0.o -o dev0
dev0.o: dev0.c
	gcc -c -I../include dev0.c

dev1: dev1.o
	gcc dev1.o -o dev1
dev1.o: dev1.c
	gcc -c -I../include dev1.c

dev2: dev2.o
	gcc dev2.o -o dev2
dev2.o: dev2.c
	gcc -c -I../include dev2.c

.PHONY: clean
clean:
	rm -rf $(bins) *.o
