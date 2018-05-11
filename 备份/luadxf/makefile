#BIN = /cygdrive/d/MinGWStudio/MinGw/bin/
#BIN = /cygdrive/c/mingw/bin/
CC = $(BIN)gcc 
PRJ = luadxf
#CFLAGS = -mno-cygwin
CFLAGS = 
ifeq ($(notrace),1)
C_PROC= 
else
C_PROC = -DENABLE_TRACE
endif
ifeq ($(test),1)
C_PROC += -DENABLE_TEST
endif
INCPATH = -I/usr/local/include
LIBPATH = -L/usr/local/lib
LIBS = -ltrace -lstdc++ -lcomctl32 -lole32 -lopengl32 -llua -liphlpapi -lgdi32
#LDFLAGS = -mwindows -mno-cygwin
LDFLAGS = -pipe -shared 
DEPS = $(PRJ).dep
EXP = $(PRJ).exp
SRCS :=$(wildcard *.cpp)
HPPS :=$(wildcard *.h)
OBJS :=$(patsubst %.cpp,%.o,$(SRCS))
RRCS :=$(wildcard *.rc)
RRCS_OBJS :=$(patsubst %.rc,%.res,$(RRCS))
WINDRES = $(BIN)windres
all:$(PRJ).dll $(DEPS) tags
tags:$(SRCS) $(HPPS)
	ctags -R .
$(PRJ).dll :$(OBJS) $(RRCS_OBJS) $(EXP)
	$(CC) -o $@ $(EXP) $(OBJS) $(RRCS_OBJS) $(LIBPATH) $(LIBS) $(LDFLAGS)
$(EXP):$(PRJ).def
	dlltool -e $@ -d $< --no-export-all-symbols
%.o:%.cpp	
	$(CC) $(CFLAGS) $(C_PROC) $(INCPATH) -c $< 
%.res:%.rc
	$(WINDRES) -O COFF -i "$<" -o "$@"
$(DEPS):$(SRCS) $(HPPS)
	$(CC) -MM $(INCPATH) *.cpp >$(DEPS)
#-@if test ! -r "$(DEPS)";then echo>$(DEPS);fi
#	makedepend  -f$(DEPS)>&/dev/null *.c
-include $(DEPS)
install:
	cp $(PRJ).dll ../ap3d/
clean:
	-@rm *.o $(PRJ).dll *.dep *.exp
