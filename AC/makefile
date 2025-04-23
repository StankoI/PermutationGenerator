TARGET = perm_test

SRCS = main.c PermutationGenerator.c PermutationByRank.c RankOfPermutation.c TestRandPerm.c

HEADERS = PermutationGenerator.h PermutationByRank.h RankOfPermutation.h TestRandPerm.h PermutationInfo.h

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


clean:
	rm -f $(OBJS) $(TARGET)

$(OBJS): $(HEADERS)

.PHONY: all clean
