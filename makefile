SRC_FILES := checkint.c count.c path.c peek.c proclore.c warp.c seekfile.c seek.c past.c activities.c man.c neonate.c signal.c main.c
OBJ_FILES := $(SRC_FILES:.c=.o)
TARGET := myprogram
CC := gcc
CFLAGS := -g -Wall
LDFLAGS := -lcurl  # Add the -lcurl flag here

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LDFLAGS)  # Move $(LDFLAGS) to the end of the linker command

clean:
	rm -f $(OBJ_FILES) $(TARGET)
