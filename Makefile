all: donut.c
	gcc ./donut.c -o donut -lm
clean:
	rm -f ./donut
