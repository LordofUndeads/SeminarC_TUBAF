CC = gcc
CFLAGS = -c -Wextra -g -O3 -lm
LD = $(CC)


TARGET = hash.out
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
