
all: lib tictactoe

clean:
	rm -f *.o

lib:
	gcc -c includes/*.c

tictactoe:
	gcc -o main main.c *.o