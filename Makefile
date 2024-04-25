CC = cc
CFlags = -Wall -Wextra -pedantic

run:
	$(CC) $(CFlags) -o main main.c && ./main

comp:
	$(CC) $(CFlags) -o main main.c 

test:
	$(CC) -o test test.c && ./test && rm -rf ./test

clean:
	rm -rf ./main
