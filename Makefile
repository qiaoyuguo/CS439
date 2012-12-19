BUILD  := build
STATIC := static

SOBJS :=	$(STATIC)/part1_harness.o \
		$(STATIC)/part2_harness.o \
		$(STATIC)/part3_harness.o \
		$(STATIC)/part4_harness.o \
		$(STATIC)/part5_harness.o

CC     := gcc
CFLAGS := -m32

OBJS :=	$(BUILD)/part1 \
	$(BUILD)/part2 \
	$(BUILD)/part3 \
	$(BUILD)/part4 \
	$(BUILD)/part5


all: $(OBJS)
	@:

$(BUILD)/part%: part%.c $(SOBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -g -c part$*.c -o $(BUILD)/part$*.o
	$(CC) $(CFLAGS) $(STATIC)/part$*_harness.o $(BUILD)/part$*.o -lm -o $(BUILD)/part$*

clean-logs: always
	rm -f *.out

clean: always clean-logs
	rm -rf $(BUILD)

grade:
	@echo $(MAKE) clean
	@$(MAKE) -s --no-print-directory clean
	@./grade-lab1

TURNIN   := /lusr/bin/turnin
GRADER   := imr
LAB_NAME := cs439-lab1
TARBALL  := lab1-handin.tar.gz

# Most of the next two rules ripped from MIT JOS.
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

.PHONY: all always
