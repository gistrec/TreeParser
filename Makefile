PROJECT := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

clear:
	rm -rf _build

lib:
	mkdir -p _build
	g++ -std=c++17 -c $(PROJECT)/src/string_parser.cpp      -I$(PROJECT)/include -fPIC -Wall -o $(PROJECT)/_build/string_parser.o
	g++ -std=c++17 -c $(PROJECT)/src/tree_serialization.cpp -I$(PROJECT)/include -fPIC -Wall -o $(PROJECT)/_build/tree_serialization.o

	g++ -shared $(PROJECT)/_build/string_parser.o $(PROJECT)/_build/tree_serialization.o -o $(PROJECT)/_build/libtree.a

example: lib
	g++ -std=c++17 -Wall -I$(PROJECT)/include   \
		-L$(PROJECT)/_build                     \
		$(PROJECT)/example/example.cpp -ltree   \
		-o $(PROJECT)/example.exe

test: lib
	g++ -std=c++17 -Wall -pthread                   \
		-lgtest_main  -lgtest -lpthread -ltree      \
		-I$(PROJECT)/include  -L$(PROJECT)/_build   \
		$(PROJECT)/test/string_parser.cpp           \
		$(PROJECT)/test/tree_node.cpp               \
		$(PROJECT)/test/tree_serialization.cpp      \
		-o $(PROJECT)/test.exe

# TODO: Code coverage in test
# coverage:
#	mkdir -p _build
#
#	g++ -std=c++17 -c src/string_parser.cpp      -I"./include" -fPIC -Wall -o _build/string_parser.o -fprofile-arcs -ftest-coverage
#	g++ -std=c++17 -c src/tree_serialization.cpp -I"./include" -fPIC -Wall -o _build/tree_serialization.o -fprofile-arcs -ftest-coverage
#
#	g++ -shared _build/string_parser.o _build/tree_serialization.o -o _build/libtree.a -fprofile-arcs -ftest-coverage
#
#	g++ -Wall -g -pthread -L"./_build" test/string_parser.cpp test/tree_node.cpp test/tree_serialization.cpp -lgtest_main  -lgtest -lpthread -I"./include" -std=c++17 -ltree -fprofile-arcs -ftest-coverage
