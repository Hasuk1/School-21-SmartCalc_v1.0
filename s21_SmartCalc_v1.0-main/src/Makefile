TARGET = SmartCalc

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OS = $(shell uname)
CONTROLLER = smart_calc_controller
MODULES = $(wildcard modules/*.c)
OBJECTS = $(patsubst %.c, %.o, $(MODULES))
TEST_CONTROLLER = test_controller
TEST_MODUlES = test_modules

ifeq ($(OS), Linux)
	LDLIBS = -lcheck_pic -pthread -lrt -lm -lsubunit
else
	LDLIBS = -lcheck -lm
endif

all: clean install

%.o: %.c
	mkdir -p obj
	$(CC) -c $(CFLAGS) $< $(LDLIBS) -o $(patsubst modules%, obj%, $@)

$(CONTROLLER).o: $(CONTROLLER).c
	mkdir -p obj
	$(CC) -c $(CFLAGS) $(CONTROLLER).c $(LDLIBS) -o obj/$(CONTROLLER).o

install:
	@echo "Start installation"
	@mkdir -p ../build
	@cd view && qmake && make && make clean && rm -rf Makefile && mv S21_SmartCalc_GUI.app ../../build/$(TARGET).app
	@cp -R ../build/$(TARGET).app ~/Desktop/$(TARGET).app
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃     The project is located in the       ┃"
	@echo "┃    build folder and on the desktop.     ┃"
	@echo "┗=========================================┛"

uninstall:
	@rm -rf ~/Desktop/SmartCalc.app ../build
	@echo "Uninstall completed successfully"

dvi:
	@open ../README_RUS.md

dist:
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET)_v1.0.tgz *
	@cd ../dist && rm -rf $(TARGET).app README.md README_RUS.md
	@echo "The build was successfully archived"

test: $(CONTROLLER).o $(OBJECTS)
	@$(CC) $(CFLAGS) ./tests/controller_tests.c $(LDLIBS) obj/*.o -o tests/$(TEST_CONTROLLER)
	@$(CC) $(CFLAGS) ./tests/module_tests.c $(LDLIBS) obj/*.o -o tests/$(TEST_MODUlES)
	@echo "Testing modules:"
	@./tests/$(TEST_MODUlES)
	@echo "Testing controller:"
	@./tests/$(TEST_CONTROLLER)

gcov_report: $(CONTROLLER).o $(OBJECTS)
	@echo "┏=========================================┓"
	@echo "┃     Generating your html report ...     ┃"
	@echo "┗=========================================┛"
	@$(CC) --coverage $(CFLAGS) ./tests/module_tests.c $(LDLIBS) ./modules/*.c -o ./tests/$(TEST_MODUlES)
	@./tests/$(TEST_MODUlES)
	@mkdir -p tests/modules_gcov
	@mv *.gcno ./tests/modules_gcov/ && mv *.gcda ./tests/modules_gcov/
	@lcov -t "test_coverage" -o test_coverage.info -c -d .
	@$(CC) --coverage $(CFLAGS) ./tests/controller_tests.c $(LDLIBS) ./modules/*.c smart_calc_controller.c -o ./tests/$(TEST_CONTROLLER)
	@./tests/$(TEST_CONTROLLER)
	@mkdir -p tests/controller_gcov
	@mv *.gcno ./tests/controller_gcov/ && mv *.gcda ./tests/controller_gcov/
	@lcov -t "test_coverage" -o test_coverage.info -c -d .
	@genhtml -o report test_coverage.info
	@open report/index.html
	@rm -rf *.gcda *.gcno report/test_coverage.info tests/modules_gcov tests/controller_gcov

style_check:
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -n *.c *.h **/*.c **/*.h **/*.cpp
	@rm ./.clang-format

format_style:
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@cp ../materials/linters/.clang-format .
	@clang-format -i *.c *.h **/*.c **/*.h **/*.cpp
	@rm ./.clang-format

valgrind_check: test
	@CK_FORK=no valgrind --vgdb=no --leak-check=full \
	--show-leak-kinds=all --track-origins=yes --log-file="controller_tests_vg.log" -v --verbose -q --quiet -s tests/$(TEST_CONTROLLER)
	@CK_FORK=no valgrind --vgdb=no --leak-check=full \
	--show-leak-kinds=all --track-origins=yes --log-file="module_tests_tests_vg.log" -v --verbose -q --quiet -s tests/$(TEST_MODUlES)
	@echo "┏=========================================┓"
	@echo "┃        Valgrind check is over           ┃"
	@echo "┃       logs have been generated          ┃"
	@echo "┗=========================================┛"

fonts:
	open view/fonts/.

clean:
	@rm -rf tests/logs/*.log tests/$(TEST_CONTROLLER) tests/$(TEST_MODUlES) obj *.dSYM **/*.dSYM report test_coverage.info

fclean: clean
	@rm -rf ../build ../dist ~/Desktop/$(TARGET).app controller_tests_vg.log module_tests_tests_vg.log

.PHONY: all install uninstall dvi dist test gcov_report valgrind_check style_check format_style fonts clean fclean
