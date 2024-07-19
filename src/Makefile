.PHONY: all clean tests install uninstall dvi dist gcov_report

CFLAGS = -Wall -Wextra -Werror -std=c++17 
GCOVFLAGS = -fprofile-arcs -ftest-coverage
QMAKE = qmake6  
OS = $(shell uname)

INST_DIR = build
EXE_DIR = View
TEST_DIR = Tests
CLANG = clang-format --verbose -style=Google

ifeq ($(OS), Darwin)
	TEST_LIBS=-lgtest -lgtest_main
	EXE_FILE=3D_Viewer_2_0.app
else
	TEST_LIBS=-lgtest -lgtest_main -DQT_TESTLIB_LIB
	EXE_FILE=3D_Viewer_2_0
endif

all: style install tests gcov_report dvi dist

install: uninstall clean
	mkdir -p $(INST_DIR)
	cd $(EXE_DIR) && \
	$(QMAKE) && \
	make && \
	mv $(EXE_FILE) ../$(INST_DIR)
	$(MAKE) clean

uninstall: 
	rm -rf $(INST_DIR)

clean:
	rm -rf $(TEST_DIR)/coverage*
	rm -rf $(TEST_DIR)/test
	rm -rf $(TEST_DIR)/*gcov
	rm -rf $(TEST_DIR)/*gcno
	rm -rf $(TEST_DIR)/*gcda
	rm -rf 3D_Viewer_2_0.tar.gz
	rm -rf $(EXE_DIR)/$(EXE_FILE) $(EXE_DIR)/.qmake.stash
	rm -rf $(EXE_DIR)/*.o
	rm -rf $(EXE_DIR)/moc*
	rm -rf $(EXE_DIR)/ui*
	rm -rf $(EXE_DIR)/Makefile

dvi:
	open ./dvi/index.html

dist: install
	tar -cf 3D_Viewer_2_0.tar.gz build/

tests:
	cd $(TEST_DIR) && \
	g++ $(CFLAGS) tests.cc ../Model/*.cc ../Model/Parser/*cc -o test $(TEST_LIBS) && \
	./test
	
gcov_report: 
	cd $(TEST_DIR) && \
	g++ $(GCOVFLAGS) *.cc ../Model/*.cc ../Model/Parser/*.cc -o report.out $(TEST_LIBS) && \
	./report.out && \
	gcov ./*gcda ./*gcno && \
	lcov --ignore-errors inconsistent --capture --directory . --output-file coverage.info --exclude '/usr/local/*'  && \
	genhtml coverage.info --output-directory coverage_report && \
	rm -f *.gcno *.gcda *.info report.out *.gcov && \
	open coverage_report/index.html
	
style:
	$(CLANG) -n Controller/*.cc
	$(CLANG) -n Controller/*.h
	$(CLANG) -n Model/*.h
	$(CLANG) -n Model/*.cc
	$(CLANG) -n Model/Parser/*.h
	$(CLANG) -n Model/Parser/*.cc
	$(CLANG) -n View/*.cc
	$(CLANG) -n View/*.h

lint:
	$(CLANG) -i Controller/*.cc
	$(CLANG) -i Controller/*.h
	$(CLANG) -i Model/*.h
	$(CLANG) -i Model/*.cc
	$(CLANG) -i Model/Parser/*.h
	$(CLANG) -i Model/Parser/*.cc
	$(CLANG) -i View/*.cc
	$(CLANG) -i View/*.h
