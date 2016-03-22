#include "Parser.hpp"
#include "Solve.hpp"
#include "Gen.hpp"
#include <iostream>
#include <exception>
#include <string.h>

bool	is_digits(const std::string &str);

void	ft_usage() {
		std::cout << "Usage : ./npuzzle [-gen] [heuristic] [file]" << std::endl;
		std::cout << "Usage : ./npuzzle [heuristic] [file]" << std::endl;
		std::cout << "heuristic : \n\t-md = manhattan distance \n\t-mt = misplaced tiles\n\t-to = tiles out of place" << std::endl;
}

int		main(int argc, char **argv) {
	/*if (argc == 3) {
		Gen			*g;
		if (strcmp(argv[1],"-gen") == 0) {*/
			/*int		i = 0;
			while (argv[2][i] != '\0') {
				if (is_digits(!argv[2][i])) {
					std::cout << "T'as rien compris !" << std::endl;
					exit(EXIT_FAILURE);
				}
				i++;
			}*/
/*			g = new Gen(std::stoi(argv[2]));
			delete g;
		}
	} */

	if (argc == 4) {
		Gen			*g;
		Solve		*s;
		heuristic	h = md;

		if (strcmp(argv[1],"-gen") == 0) {
			if (strcmp(argv[2], "-md") == 0)
				h = md;
			else if (strcmp(argv[2], "-mt") == 0)
				h = mt;
			else if (strcmp(argv[2], "-to") == 0)
				h = to;
			else {
				ft_usage();
				exit(0);
			}
		}
		if (is_digits(argv[3])) {
			g = new Gen (std::stoi(argv[3]));
			s = new Solve(g->puzzle, std::stoi(argv[3]), h);
			printf("count_inv : %d\n", g->count_inv);
			delete g;
			delete s;
		}
	}
	else if (argc == 3) {
		Parser		*p;
		Solve		*s;
		heuristic	h = md;

		if (strcmp(argv[1], "-md") == 0)
			h = md;
		else if (strcmp(argv[1], "-mt") == 0)
			h = mt;
		else if (strcmp(argv[1], "-to") == 0)
			h = to;
		else {
			ft_usage();
			exit(0);
		}
		printf("heuristic choisi : %d\n", h);
		try {
			p = new Parser(argv[2]);
			s = new Solve(p->puzzle, p->size, h);
			delete p;
			delete s;
		}
		catch (std::exception &e){
			
			std::cerr << "exception : " << e.what() << std::endl;
		}
	}
	else {
		ft_usage();
	}
	return (0);
}

bool	is_digits(const std::string &str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}