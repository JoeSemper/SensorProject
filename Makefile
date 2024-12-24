all: sensor

sensor: main.o temp_api.o util.o
	gcc -o sensor main.o temp_api.o util.o

main.o: main.c temp_api.h util.h
	gcc -c -o main.o main.c

temp_api.o: temp_api.c
	gcc -c -o temp_api.o temp_api.c

util.o: util.c
	gcc -c -o util.o util.c

clean:
	del -rf *.o *.exe
