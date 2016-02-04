#include "Parser.hpp"
#include "Solve.hpp"
#include "Gen.hpp"
#include <iostream>
#include <exception>
#include <string.h>

bool	is_digits(const std::string &str);

int		main(int argc, char **argv) {
	if (argc == 3) {
		Gen			*g;
		if (strcmp(argv[1],"-gen") == 0) {
			/*int		i = 0;
			while (argv[2][i] != '\0') {
				if (is_digits(!argv[2][i])) {
					std::cout << "T'as rien compris !" << std::endl;
					exit(EXIT_FAILURE);
				}
				i++;
			}*/
			g = new Gen(std::stoi(argv[2]));
		}
	}

	else if (argc == 2) {
		Parser		*p;
		Solve		*s;
		try {
			p = new Parser(argv[1]);
			s = new Solve(p->puzzle, p->size);
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
/*
bool	is_digits(const std::string &str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}*/