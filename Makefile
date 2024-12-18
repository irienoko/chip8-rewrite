BINARY=pain
SOURCEDIR=source
INCDIRS=include

CC=gcc
OPT=-O0

DEPFLAGS=-MP -MD

CFLAGS=-Wall -Wextra -g $(foreach D, $(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)

CFILES=$(foreach D, $(SOURCEDIR), $(wildcard $(D)/*.c))
LDLIBS = -lm -lSDL2main -lSDL2

OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))



all: $(BINARY)

$(BINARY): $(OBJECTS)
		$(CC) -o $@ $^ $(LDLIBS)

%.o:%.c
		$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

-include $(DEPFILES)



