# Makefile for the CS:APP Shell Lab, with modifications for CS439.

CC = gcc
CFLAGS = -Wall -O2 -g
FILES = ./psh ./fib ./ascii

all: $(FILES)

psh: psh.o util.o 
	$(CC) $(CFLAGS) psh.o util.o -o psh

.PHONY: clean always

clean:
	rm -f $(FILES) *.o *~ *.bak *.BAK


TURNIN   := /lusr/bin/turnin
GRADER   := imr
LAB      ?= labsh
LAB_NAME := cs439w-$(LAB)
TARBALL  := $(LAB)-handin.tar.gz

tarball:
	@if ! git diff-files --quiet || ! git diff-index --quiet --cached HEAD; then \
		git status; \
		echo; \
		echo "You have uncomitted changes.  Please commit or stash them."; \
		false; \
	fi
	@if test -n "`git ls-files -o --exclude-standard`"; then \
		git status; \
		read -p "Untracked files will not be handed in.  Continue? [y/N] " r; \
		test "$$r" = y; \
	fi
	tar -cf - `git ls-files` './.git' | gzip > $(TARBALL)

turnin: tarball
	@echo
	@echo "Are you sure you want to turn in this lab to \"$(LAB_NAME)$*\"? If Yes, press any key (and Enter) to continue. Else, press Ctrl-C to abort"
	@read p
	$(TURNIN) --submit $(GRADER) $(LAB_NAME)$* $(TARBALL)

tidy: always
	git clean -dff
