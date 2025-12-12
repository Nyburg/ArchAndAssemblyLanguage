CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.
LDFLAGS =
OBJFILES = main.o parser.o symtable.o error.o
TARGET = assembler

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJFILES) $(TARGET) *~