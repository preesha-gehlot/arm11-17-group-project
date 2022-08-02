CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic -fcommon
OBJS 		= assembler.o arrays.o branch.o data_processing.o multiply.o single_data_transfer.o io.o symbol_table.o tokenizer.o ../utils.o utils.o ../extension/assembler/block_data_transfer.o ../extension/assembler/single_data_swap.o
OUT			= ../assemble

.SUFFIXES: .c .o

.PHONY: clean

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

assembler.o: assembler.c io.h ../utils.h definitions.h single_data_transfer.h multiply.h branch.h data_processing.h
arrays.o: definitions.h
branch.o: branch.h
data_processing.o: data_processing.h
multiply.o: multiply.h
single_data_transfer.o: single_data_transfer.h
io.o: io.h
symbol_table.o: symbol_table.h
tokenizer.o: tokenizer.h
../utils.o: ../utils.c ../utils.h
utils.o: utils.h
../extension/assembler/block_data_transfer.o: ../extension/assembler/block_data_transfer.c ../extension/assembler/block_data_transfer.h
../extension/assembler/single_data_swap.o: ../extension/assembler/single_data_swap.c ../extension/assembler/single_data_swap.h

clean:
	rm -f $(wildcard *.o)
	rm -f $(OUT)
