EXEC = test
# CFLAGS = -ansi -pedantic -Wall
SRCS = add.c mul.c life.c cmp.c test.c
OBJS = $(SRCS:.c=.o)
.PHONY: clean

$(EXEC) : $(OBJS)
	gcc -o $@ $^

%.o : %.c
	gcc -c $(CFLAGS) $<

clean :
	rm $(OBJS) $(EXEC)
