# # Sets default compiler
CC = gcc
# # Sets flags
CFLAGS = -Wall -Wextra -pedantic 
hello:playlist.c max_tester_for_all.c
	$(CC) $(CFLAGS) -o hello playlist.c max_tester_for_all.c
all: hello