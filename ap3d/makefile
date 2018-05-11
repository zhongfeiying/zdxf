#BIN = /cygdrive/d/MinGWStudio/MinGw/bin/
#BIN = /cygdrive/c/mingw/bin/
CC = $(BIN)gcc 
PRJ = ap3d
#CFLAGS = -mno-cygwin

INCPATH = -I/usr/local/include
LIBPATH = -L/usr/local/lib
LIBS = -lcomctl32 -lole32 -lopengl32 -llua -liphlpapi -lgdi32

DEPS = $(PRJ).dep
SRCS :=$(wildcard *.c)
HPPS :=$(wildcard *.h)
OBJS :=$(patsubst %.c,%.o,$(SRCS))
RRCS :=$(wildcard *.rc)
RRCS_OBJS :=$(patsubst %.rc,%.res,$(RRCS))
WINDRES = $(BIN)windres
all:$(PRJ).exe $(DEPS) tags
tags:$(SRCS) $(HPPS)
	ctags -R .
$(PRJ).exe :$(OBJS) $(RRCS_OBJS)
	$(CC) -o $@ $(OBJS) $(RRCS_OBJS) $(LIBPATH) $(LIBS) 
%.o:%.c	
	$(CC) $(INCPATH) -c $< 
%.res:%.rc
	$(WINDRES) -O COFF -i "$<" -o "$@"
$(DEPS):$(SRCS) $(HPPS)
	$(CC) -MM $(INCPATH) *.c >$(DEPS)
-include $(DEPS)
install:
	cp $(PRJ).dll bin/
clean:
	-@rm *.o $(PRJ).dll *.dep 
