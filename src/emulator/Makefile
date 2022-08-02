CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic -fcommon
OBJS 		= emulator.o io.o fetch.o decode.o execute/execute.o execute/barrel_shifter.o execute/branch.o execute/data_processing.o execute/multiply.o execute/single_data_transfer.o cpsr.o ../utils.o decompiler.o gpio.o utils.o ../extension/emulator/decode.o ../extension/emulator/stack.o ../extension/emulator/execute/block_data_transfer.o ../extension/emulator/execute/single_data_swap.o
OUT			= ../emulate

.SUFFIXES: .c .o

.PHONY: clean

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

emulate.o: io.h fetch.h decode.h execute/execute.h ../definitions.h decompiler.h ../utils.h definitions.h
io.o: io.h
fetch.o: fetch.h
decode.o: decode.h
execute.o: execute/execute.c execute/execute.h
barrel_shifter.o: execute/barrel_shifter.c execute/barrel_shifter.h
branch.o: execute/branch.c execute/branch.h
data_processing.o: execute/data_processing.c execute/data_processing.h
multiply.o: execute/multiply.c execute/multiply.h
single_data_transfer.o: execute/single_data_transfer.c execute/single_data_transfer.h
cpsr.o: cpsr.h
../utils.o: ../utils.c ../utils.h
utils.o: utils.h
decompiler.o: decompiler.h
gpio.o: gpio.h
../extension/emulator/decode.o: ../extension/emulator/decode.c ../extension/emulator/decode.h
../extension/emulator/stack.o: ../extension/emulator/stack.c ../extension/emulator/stack.h
../extension/emulator/execute/block_data_transfer.o: ../extension/emulator/execute/block_data_transfer.c ../extension/emulator/execute/block_data_transfer.h
../extension/emulator/execute/single_data_swap.o: ../extension/emulator/execute/single_data_swap.c ../extension/emulator/execute/single_data_swap.h

clean:
	rm -f $(wildcard *.o)
	rm -f $(OUT)
	rm -f $(wildcard execute/*.o)
