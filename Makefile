CC = cc
CFlags = -Wall -Wextra -pedantic

run:
	$(CC) $(CFlags) -o main main.c && ./main

comp:
	$(CC) $(CFlags) -o main main.c 


clean:
	rm -rf ./main
