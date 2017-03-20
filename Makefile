#
# 'make'        build executable file $(TARGET)
# 'make clean'  removes all .o and executable files
# 'make run'	build executalbe file $(TARGET) and run it ./$(TARGET)
#

# define the C/C++ compiler to use
CC = g++

# define the remove command
RM = rm

# define object files directory
OBJS_DIR = obj

# define any compile-time flags
CFLAGS = -Wall

# define the C source files
SRCS = main.cpp \
	   dfa.cpp

OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

# define the executable file 
TARGET = launch

.PHONY: depend clean run

all: $(TARGET)
	@echo launch has been succesfully compiled

# generate target file
$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile Object files
$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) -f $(OBJS_DIR)/*.o $(TARGET)
	$(RM) -r $(OBJS_DIR)