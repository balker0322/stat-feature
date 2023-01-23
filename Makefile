#make file - this is a comment section

CC=gcc  #compiler
TARGET=main #target file name
SRC=main.c\

all:
	$(CC) $(SRC) -o $(TARGET)

clean:
	rm $(TARGET)


