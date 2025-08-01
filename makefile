
all: lib tictactoe clean

clean:
	rm -f *.o

lib:
	gcc -c include/*.c

tictactoe:
	gcc -o main main.c *.o