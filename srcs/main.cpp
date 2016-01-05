#include "Parser.hpp"
#include <iostream>
#include <exception>

int		main(int argc, char **argv)
{
	if (argc == 0) {

	}

	else if (argc == 2) {
		Parser		*p;
		try {

		p = new Parser(argv[1]);
		}
		catch (std::exception &e){
			std::cerr << "exception : " << e.what() << std::endl;
		}
	}

	else {
		std::cout << "Usage : ./npuzzle [file]" << std::endl;
	}
	return (0);
}