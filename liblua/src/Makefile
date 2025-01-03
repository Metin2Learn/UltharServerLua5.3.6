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

# 默认目标，创建静态库
all:	$(T)

# 构建静态库
$(T):	$(OBJS)
	@if [ ! -d $(LIB) ]; then mkdir -p $(LIB); fi
	$(AR) rcu $@ $(OBJS)
	$(RANLIB) $@

# 清理编译生成的文件
clean:
	rm -f $(OBJS) $(T)

# 检出源代码（CVS）
co:
	co -q -f -M $(SRCS)

# 清理并删除源文件
klean:	clean
	rm -f $(SRCS)

# 添加复制文件的目标
copy_files:
	@echo "Copying .c and .o files to lib directory..."
	# 将 .c 和 .o 文件复制到 lib 目录
	cp $(SRCS) $(LIB)/
	cp $(OBJS) $(LIB)/