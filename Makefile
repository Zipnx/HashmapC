
CC := /usr/bin/gcc
CFLAGS := -Wall -Wextra -ggdb

BUILDDIR := ./build/
SRCDIR   := ./src/
BINDIR   := ./
BINNAME  := map

SRCFILES := $(wildcard $(SRCDIR)*.c)
OBJFILES := $(patsubst $(SRCDIR)%.c, $(BUILDDIR)%.o, $(SRCFILES))

all:
	$(MAKE) $(BINDIR)$(BINNAME)

bnr:
	@echo ==== BUILDING ====
	$(MAKE) $(BINDIR)$(BINNAME)
	@echo ==== BUILD COMPLETE ====
	$(BINDIR)$(BINNAME)

build:
	$(MAKE) $(BINDIR)$(BINNAME)	

$(BINDIR)$(BINNAME) : $(OBJFILES)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(BUILDDIR)*.o $(BUILDDIR)*.o $(BINDIR)$(BINNAME)
