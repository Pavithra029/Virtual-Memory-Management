CC=gcc
CFLAGS= -Wall -Wextra
SRCS= main.c buddy.c tlb.c mm.c pagere.c firstfit.c bestfit.c worstfit.c DemandPaging.c
OBJS=$(SRCS:.c=.o)
TARGET=vmm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)

