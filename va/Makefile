
CC	 := gcc
LD	 := ld
SRCS := printf.c		\
	   main.c
OBJS :=	printf.o	\
		main.o

all: $(OBJS)
	$(CC) -o main $(OBJS)

.c.o:
	$(CC) -g -o $@ $< -c
clean:
	rm $(OBJS) main
