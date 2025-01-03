# makefile for Lua standard library

LUA= ../..

include $(LUA)/config

EXTRA_DEFS= $(POPEN) $(TMPNAM) $(DEGREES) $(LOADLIB)

# 自动查找所有 .c 文件
SRCS=$(wildcard *.c)

# 自动生成对应的 .o 文件
OBJS=$(SRCS:.c=.o)

# 生成的静态库
T= $(LIB)/liblualib.a

# 默认目标
all:	$(T)

# 生成静态库
$(T):	$(OBJS)
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

# 清理目标
clean:
	rm -f $(OBJS) $(T)

# 使用 `co` 版本控制工具
co:
	co -q -f -M $(SRCS)

# 删除源文件
klean:	clean
	rm -f $(SRCS)
