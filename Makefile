#PROJECT := $(dirname $(abspath $(lastword $(MAKEFILE_LIST))))
PROJECT := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))


clear:
	rm -rf _build


lib: clear
	mkdir _build
	g++ -std=c++17 -c $(PROJECT)/src/string_parser.cpp      -I$(PROJECT)/include -fPIC -Wall -o $(PROJECT)/_build/string_parser.o
	g++ -std=c++17 -c $(PROJECT)/src/tree_serialization.cpp -I$(PROJECT)/include -fPIC -Wall -o $(PROJECT)/_build/tree_serialization.o

	g++ -shared $(PROJECT)/_build/string_parser.o $(PROJECT)/_build/tree_serialization.o -o $(PROJECT)/_build/libtree.a


example: lib
	g++ -std=c++17 $(PROJECT)/example/example.cpp -I$(PROJECT)/include -L$(PROJECT)/_build -Wall -o $(PROJECT)/example.exe -ltree


test: lib
	g++ -Wall -g -pthread $(PROJECT)/test/string_parser.cpp $(PROJECT)/test/tree_node.cpp $(PROJECT)/test/tree_serialization.cpp -lgtest_main  -lgtest -lpthread -I$(PROJECT)/include -std=c++17 -ltree -L$(PROJECT)/_build -o $(PROJECT)/test.exe


# TODO: Code coverage in test
# coverage: clear
#	mkdir _build
#
#	g++ -std=c++17 -c src/string_parser.cpp      -I"./include" -fPIC -Wall -o _build/string_parser.o -fprofile-arcs -ftest-coverage
#	g++ -std=c++17 -c src/tree_serialization.cpp -I"./include" -fPIC -Wall -o _build/tree_serialization.o -fprofile-arcs -ftest-coverage
#
#	g++ -shared _build/string_parser.o _build/tree_serialization.o -o _build/libtree.a -fprofile-arcs -ftest-coverage
#
#	g++ -Wall -g -pthread -L"./_build" test/string_parser.cpp test/tree_node.cpp test/tree_serialization.cpp -lgtest_main  -lgtest -lpthread -I"./include" -std=c++17 -ltree -fprofile-arcs -ftest-coverage
