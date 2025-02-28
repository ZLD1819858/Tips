# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -Iinclude

# 目标可执行文件
TARGET = pmsav7

# 源文件
SRC = pmsav7.c

# 头文件路径
# INCLUDE = include/pmsav7.h

# 目标文件
OBJ = $(SRC:.c=.o)

# 默认目标：编译生成可执行文件
all: $(TARGET)

# 生成可执行文件
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# 编译每个源文件为目标文件
%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJ) $(TARGET)

# 重新编译
rebuild: clean all

# 伪目标
.PHONY: all clean rebuild
