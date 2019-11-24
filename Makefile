CXX=g++
CXXFLAGS= -std=c++0x -g -fprofile-arcs -ftest-coverage
GXXFLAGS= -Wall -g -std=c++11

LINKFLAGS= -lgtest

SRC_DIR = src

DOCS_DIR = docs

TEST_DIR = test

SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

STATIC_ANALYSIS = cppcheck

STYLE_CHECK = cpplint.py

PROGRAM_TEST = testGame

GAME_PROGRAM = runningGame

.PHONY: all
all: $(PROGRAM_TEST) $(GAME_PROGRAM) memcheck coverage docs static style

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(GXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o *.txt $(TEST_SRC)/*.o *.gcov *.gcda *.gcno \
	$(COVERAGE_RESULTS) \
	$(PROGRAM_TEST) $(GAME_PROGRAM) $(MEMCHECK_RESULTS) \
	$(COVERAGE_DIR) \
	$(DOCS_DIR)/src/html \
	obj/ bin
	$(TEST_FILE_WIDGETS_WINDOW) \
	$(TEST_FILE_EMPTY_WINDOW) \


$(GAME_PROGRAM): $(SRC_DIR)
	$(CXX) $(GXXFLAGS) -o $(GAME_PROGRAM) $(INCLUDE) \
	$(SRC_DIR)/*.cpp $(SRC_DIR)/game/*.cpp

game: $(GAME_PROGRAM)
	$(GAME_PROGRAM)

$(PROGRAM_TEST): $(TEST_DIR)/main.cpp $(SRC_DIR)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST) $(INCLUDE) \
	$(TEST_DIR)/*.cpp $(SRC_DIR)/*.cpp  $(LINKFLAGS)

tests: $(PROGRAM_TEST)
	$(PROGRAM_TEST)

memcheck: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=yes $(PROGRAM_TEST)

coverage: $(PROGRAM_TEST)
	$(PROGRAM_TEST)
	#Determine code coverage
	$(LCOV) --capture --gcov-tool $(GCOV) --directory . --output-file $(COVERAGE_RESULTS)
	#Only show code coverage for the source code files (not library files)
	$(LCOV) --extract $(COVERAGE_RESULTS) "*/Elrond/src/*" -o $(COVERAGE_RESULTS)
	#Generate the HTML reports
	genhtml $(COVERAGE_RESULTS) --output-directory $(COVERAGE_DIR)
	#Remove all of the generated files from gcov
	rm -f *.gc*

static: ${SRC_DIR} ${TEST_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR} ${TEST_DIR} ${SRC_INCLUDE} --suppress=missingInclude

style: ${SRC_DIR} ${TEST_DIR} ${SRC_INCLUDE}
	${STYLE_CHECK} $(SRC_INCLUDE)/* ${SRC_DIR}/* ${TEST_DIR}/*

docs: ${SRC_INCLUDE} $(DOCS_DIR)/src
	doxygen doxyfile

