.PHONY = all clean

CC = gcc
CFLAGS = -W -Wall -Werror -Wextra 
TARGET = test 
OBJECTS = yp_file.o yp_pid.o yp_main.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o $(TARGET)
