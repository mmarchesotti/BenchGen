TARGET = single_loop
SRC_DIR = src

all: $(TARGET)

# Tell the V compiler to compile the entire source directory.
$(TARGET):
	v $(SRC_DIR) -o $(TARGET)

run:
	v run $(SRC_DIR)

clean:
	rm -f $(TARGET)
