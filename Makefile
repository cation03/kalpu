all: kalpesh.o
	gcc -o kalpesh kalpesh.c -w
kalpesh.o: cat.c rm.c ls.c mkdir.c date.c
	gcc -o cat cat.c
	gcc -o rm rm.c
	gcc -o ls ls.c
	gcc -o mkdir mkdir.c
	gcc -o date date.c
