###
### Makefile for Gerp Project
###
### Author:  Jerry Qiao (jqiao04)
## 


##
## Here is a special rule that removes all .o files besides the provided ones 
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -O3
LDFLAGS  = -g3 -lncurses


gerp: main.o Gerp.o FSTree.o DirNode.o processing.o
	$(CXX) $(LDFLAGS) $^ -o gerp

main.o: main.cpp Gerp.h 

Gerp.o: Gerp.cpp Gerp.h FSTree.h processing.h


unit_test: unit_test_driver.o \
processing.o FSTree.o DirNode.o Table.h Gerp.o
	$(CXX) $(LDFLAGS) $^

processing.o: processing.h processing.cpp FSTree.h DirNode.h

try: try.o processing.o FSTree.o DirNode.o
	$(CXX) $(LDFLAGS) -o try $^

try.o: try.cpp processing.h


clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ try gerp

