.PHONY: clean

all:
	$(MAKE) -C emulator
	$(MAKE) -C assembler

clean:
	rm -f $(wildcard *.o)
	rm -f $(wildcard extension/*.o)
	$(MAKE) clean -C emulator
	$(MAKE) clean -C assembler
