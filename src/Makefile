CC=g++
CFLAGS= -std=c++17
OS := $(shell uname -s)
ifeq ($(OS), Darwin)
  LDFLAGS= -lgtest -lstdc++
else
  LDFLAGS=-lgtest -lsubunit -lrt -lpthread -lm
endif
LIBSRC=$(filter-out test.c, $(wildcard *.c))
LIBOBJ=$(LIBSRC:.c=.o)
EXECUTABLE=result_file
LCOVEXEC=$(EXECUTABLE).info
REPORTDIR=report
STATICLIB=s21_calc_v2.a
APP = Calc_v2.app
TEXI2DVI=texi2dvi
GCOV=-coverage

all:  install tests dvi

build: test.o $(STATICLIB)
	$(CC) test.o $(STATICLIB) -o $(EXECUTABLE) $(LDFLAGS)

install:
	qmake View/Calc_v2.pro -o Makefile_qt
	make -f Makefile_qt
	@mkdir $(HOME)/Desktop/CPP3_SmartCalc_v2/
	@cp -rf $(APP) $(HOME)/Desktop/CPP3_SmartCalc_v2/
	
uninstall:
	@rm -rf $(HOME)/Desktop/CPP3_SmartCalc_v2/

tests: clean
	g++ -std=c++17 -coverage -c Sources/model.cc
	g++ -std=c++17 -c test.cc
	g++ -std=c++17 -coverage test.cc -o test model.o -lgtest -lstdc++
	./test

dist:
	@mkdir ../CPP3_SmartCalc_v2
	@mkdir ../CPP3_SmartCalc_v2/src
	@cp -rf Sources/*.cc Makefile View/*.ui Headers/*.h *.h *.cpp View/*.user ../CPP3_SmartCalc_v2/src
	@cd ..; tar czvf CPP3_SmartCalc_v2.tgz CPP3_SmartCalc_v2/*
	@mv ../CPP3_SmartCalc_v2.tgz $(HOME)/Desktop/
	@rm -rf ../CPP3_SmartCalc_v2

gcov_report: CFLAGS+=--coverage
gcov_report: LDFLAGS+=--coverage
gcov_report: test
	lcov -t $(EXECUTABLE) -o $(LCOVEXEC) -c -d .
	genhtml -o $(REPORTDIR) $(LCOVEXEC)
	open ./report/index.html


check:
	cp -f ../materials/linters/.clang-format clang-format
	clang-format -n Headers/*.h Sources/*.cc 
	rm -rf clang-format
	CK_FORK=no leaks --atExit -- ./test

clean:
	rm -rf Calc_v2.app .qmake.stash Makefile_qt moc_credit.cpp moc_mainwindow.cpp moc_predefs.h
	rm -rf a.out *.o *.a *.gcda *.gcno *.gcov *.info test gcov_report 1test report man.pdf man.dvi man.log man result_file
	rm -rf ../CPP3_SmartCalc_v2.tgz
	rm -rf moc_qcustomplot.cpp ui_credit.h ui_mainwindow.h

dvi:
	$(TEXI2DVI) ./man.texi
	texi2pdf ./man.texi
	makeinfo --html man.texi
	open ./man/index.html

rebuild: clean all

$(STATICLIB): $(LIBOBJ)
	ar rcs $@ $^
	ranlib $@

