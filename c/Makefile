.PHONY: help all test debug clean distclean

# test
CC=cc

CFLAGS:=-std=c99 $(CFLAGS)

RUN      := run

TEST_DIR := test
TEST_SRC := $(wildcard $(addsuffix /*.c,$(TEST_DIR)))
TEST_RUN := $(addprefix $(RUN)/,$(TEST_DIR))
TEST     := $(addprefix $(RUN)/,$(patsubst %.c,%,$(TEST_SRC)))

all: test

test: $(TEST_RUN)/stamp $(TEST)

$(TEST_RUN)/stamp:
	@mkdir -p $(TEST_RUN)
	@touch $@

$(TEST_RUN)/address-of-operator: $(TEST_DIR)/address-of-operator.c
	$(CC) $(CFLAGS) -o $@ $<

$(TEST_RUN)/progress_bar: $(TEST_DIR)/progress_bar.c
	$(CC) $(CFLAGS) -o $@ $<

debug:
	@echo "TEST_DIR = $(TEST_DIR)"
	@echo "TEST_SRC = $(TEST_SRC)"
	@echo "TEST_RUN = $(TEST_RUN)"
	@echo "TEST     = $(TEST)"

help:
	@echo "make help        print this help"
	@echo "make all         build all stuff"
	@echo "make test        build all tests"
	@echo "make debug       print builtin variables"
	@echo "make clean       clean all stuff"

distclean clean:
	rm -rf run
