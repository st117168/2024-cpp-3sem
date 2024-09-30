TARGET = program
RM = rm
CC = g++

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.c, %.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	$(RM) $(TARGET) *.o