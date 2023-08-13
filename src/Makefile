CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11
GCOVFLAGS := -fprofile-arcs -ftest-coverage
LDFLAGS := -lcheck -lgcov -fprofile-arcs --coverage
ifeq ($(shell uname), Linux)
    LDFLAGS += -lpthread -lrt -lm -lsubunit
    OPEN_CMD := xdg-open
else ifeq ($(shell uname), Darwin)
    OPEN_CMD := open
endif

SRC := $(wildcard modules/*.c)
OBJ = $(patsubst modules/%.c, obj/%.o, $(SRC))
OBJ_GCOV = $(patsubst modules/%.c, gcov_obj/%.o, $(SRC))
TEST_SRC := $(wildcard tests/test_*.c)
TEST_OBJ = $(patsubst tests/%.c, tests/%.o, $(TEST_SRC))

TARGET := SmartCalc

all: clean install

obj/%.o: modules/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

gcov_obj/%.o: modules/%.c
	@$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

smart_calc.a: $(OBJ)
	@ar -src $@ $(OBJ)

smart_calc_gcov.a: $(OBJ_GCOV)
	@ar -src $@ $(OBJ_GCOV)

test: tests/tests.o smart_calc_gcov.a
	@$(CC) -g $< smart_calc_gcov.a -o $@ $(LDFLAGS) $(GCOVFLAGS)
	@clear
	@./$@

install: uninstall
	@clear
	@echo "===>    Installation has started     <==="
	@mkdir -p ../build
	@cd ui/SmartCalc1/ && qmake && make && make clean && rm -rf Makefile && mv $(TARGET).app ../../../build
	@cp -R ../build/$(TARGET).app ~/Desktop/$(TARGET).app
	@echo "===> SmartCalc application installed <==="

uninstall:
	@rm -rf ../build/$(TARGET).app
	@rm -rf ~/Desktop/$(TARGET).app
	@echo "===>  SmartCalc application removed  <==="

dvi:
	@open ../README_RUS.md

dist:
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET).app README.md README_RUS.md

gcov_report: test
	lcov -c -d gcov_obj/. -o gcov_obj/coverage.info
	genhtml gcov_obj/coverage.info --output-directory out
	$(OPEN_CMD) out/index.html

clean:
	@rm -rf ../build ../dist gcov_obj/*.o test
	@rm -rf gcov_obj/*.gcda gcov_obj/*.gcno 
	@rm -rf gcov_obj/*.info out *.a *.gcno tests/tests.o qt/*
	@rm -rf ../.DS_Store .DS_Store ../.vscode ui/.DS_Store

ultra_test: clean test gcov_report

clang:
	@clang-format -i modules/*.c modules/*.h tests/*.c ui/SmartCalc1/*.cpp ui/SmartCalc1/*.h ui/SmartCalc1/*.ui

style:
	@clang-format -n modules/*.c modules/*.h tests/*.c ui/SmartCalc1/*.cpp ui/SmartCalc1/*.h ui/SmartCalc1/*.ui

cppcheck: clean test
	@cppcheck --enable=all --suppress=missingIncludeSystem modules/ ui/SmartCalc1/

valgrind: clean test
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

leaks: clean test
	@leaks -atExit -- ./test