.PHONY : all, install, uninstall, clean, dvi, dist, test, gcov_report

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
LIBRARIES =
GCOV_FLAGS := -fprofile-arcs -ftest-coverage
LCOV_FLAGS := --ignore-errors inconsistent,empty --no-external -t -s
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log

TARGET :=Maze
DIST_DIR :=archive

SOURCES := model/*.cc

ifeq ($(shell uname), Linux)
	TEST_FLAGS := -lcheck -lgtest -lm -lpthread -lrt -lsubunit
else
	TEST_FLAGS := -lcheck -lgtest -lm -lpthread
endif

OPEN_COMMAND =open
ifeq ($(OS), Linux)
	OPEN_COMMAND=xdg-open
else
	OPEN_COMMAND=open
endif


all: clean install run

install:
	cd view && cmake -B build . && cmake --build build
	cp view/build/${TARGET} .

run:
	./${TARGET}

cli:
	$(CC) -g ${SOURCES} ${CFLAGS} ${LIBRARIES} -o ${TARGET}_exe
	./${TARGET}_exe

gcov_report_snake: clean
	@mkdir -p report
	${CC} $(BACKEND_SOURCES) $(TEST_FLAGS) $(GCOV_FLAGS) -o ./gcov_report.out
	./gcov_report.out
	lcov ${LCOV_FLAGS} "test" -o test.info -c -d .
	genhtml -o report/ test.info
	${OPEN_COMMAND} ./report/index.html
	make clean_gcov

clang_check:
	@find .. -type f -name "*.c" -exec clang-format -n  -style=Google {} \;
	@find .. -type f -name "*.cc" -exec clang-format -n  -style=Google {} \;
	@find .. -type f -name "*.cpp" -exec clang-format -n  -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -n -style=Google {} \;
	@echo "Clang format style check is finished"

clang_format:
	@find .. -type f -name "*.c" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.cc" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.cpp" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -i -style=Google {} \;
	@echo "Clang format style apply is finished"

clean: clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report clean_dist clean_build
	@echo "Clean finished"

clean_dist:
	@rm -rf ${DIST_DIR}
	@rm -rf ${DIST_DIR}.tar.gz
clean_after_building:
	@rm -rf ${OBJ_DIR}
clean_static_lib:
	@find .. -type f -name "*.a" -exec rm {} \;
clean_log:
	@find .. -type f -name "*.log" -exec rm {} \;
clean_exec:
	@find .. -type f -name "*.out" -exec rm {} \;
	@find .. -type f -name "test" -exec rm {} \;

clean_build:
	@rm -rf view/build
	@find ./view -type f -name "Makefile" -exec rm -f {} \;
	@find .. -type f -name "cmake_install.cmake" -exec rm {} \;
	@find .. -type f -name "CMakeCache.txt" -exec rm {} \;
clean_obj:
	@find .. -type f -name "*.o" -exec rm {} \;
clean_gcov:
	@if [ -d "../src/gcov_report.out.dSYM" ]; then rm -rf ../src/gcov_report.out.dSYM; fi
	@find .. -type f -name "*.gcda" -exec rm {} \;
	@find .. -type f -name "*.gcno" -exec rm {} \;
clean_lcov:
	@find .. -type f -name "*.info" -exec rm {} \;
clean_lcov_report:
	@rm -rf report