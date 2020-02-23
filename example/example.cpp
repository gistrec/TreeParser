#include <iostream>

#include "tree/tree_serialization.hpp"


int main(int argc, char* argv[]) {
    std::string input;
    std::string output;

    if (argc != 5) {
        std::cout << "Usage: " << argv[0] << " -i/--input <input> -o/--output <output>" << std::endl;
        std::cout << "<input>  - input file name"  << std::endl;
        std::cout << "<output> - output file name" << std::endl;

        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-i" || arg == "--input") {
            if (i + 1 < argc) {
                input = argv[++i];
            } else {
                std::cerr << "Invalid argument: input file name" << std::endl;
                return 1;
            }
        }
        if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                output = argv[++i];
            } else {
                std::cerr << "Invalid argument: output file name" << std::endl;
                return 1;
            }
        }
    }

    try {
        std::shared_ptr<tree::Node> tree;

        tree::read(input, tree);
        tree::print(tree);
        tree::write(output, tree);

    } catch (const std::runtime_error &error) {
        std::cerr << error.what() << std::endl;
        return 2;
    }

	return 0;
}
