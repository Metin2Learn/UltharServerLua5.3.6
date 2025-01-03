# Makefile for Lua core library

# Lua根目录，假设config文件位于这个目录
LUA= ..

# 引入配置文件
include $(LUA)/config

# 获取所有的源文件 (.c)
SRCS = $(wildcard $(LUA)/src/*.c)

# 根据源文件生成目标文件 (.o)
OBJS = $(SRCS:.c=.o)

# 静态库目标
T= $(LIB)/liblua.a

# 默认目标，创建静态库并执行后续操作
all:	$(T) copy_files post_build

# 构建静态库
$(T):	$(OBJS)
	@if [ ! -d $(LIB) ]; then mkdir -p $(LIB); fi
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

# 复制 .c 和 .o 文件到当前目录下的 lib 目录
copy_files:
	@echo "Copying .c and .o files to current lib directory..."
	# 将 .c 和 .o 文件复制到当前目录下的 lib 目录
	@if [ ! -d lib ]; then mkdir lib; fi
	cp $(SRCS) lib/
	cp $(OBJS) lib/
	@echo "Files copied to $(PWD)/lib"

# 执行 lib 目录下的 Makefile
post_build:
	@echo "Running make in $(LIB) directory..."
	$(MAKE) -C lib

# 清理编译生成的文件
clean:
	rm -f $(OBJS) $(T)

# 检出源代码（CVS）
co:
	co -q -f -M $(SRCS)

# 清理并删除源文件
klean:	clean
	rm -f $(SRCS)
