#include "Options.hpp"

Options::Options() {

}

Options::Options(int argc, char **argv) {
	this->start();
	this->get_args(argc, argv);
	this->check_errors();
	this->get_size(argv[argc - 1]);
}

Options::Options(Options const &src) {
	*this = src;
}

Options & Options::operator=(Options const & rhs) {
	*this = rhs;
	return (*this);
}
Options::~Options() {

}

void	Options::usage() {
		std::cout << "Usage : ./npuzzle [options] [heuristic] [size]" << std::endl;
		std::cout << "Usage : ./npuzzle [heuristic] [file]" << std::endl << std::endl;
		std::cout << "options : \n\t-gen = generate de random puzzle(default is solvable)\n\t-uns = unsolvable random puzzle" << std::endl;
		std::cout << "heuristic(only one) : \n\t-md = manhattan distance \n\t-mt = misplaced tiles\n\t-to = tiles out of place" << std::endl;
		exit(EXIT_FAILURE);
}

bool	Options::is_digits(const std::string &str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}

void	Options::check_errors() {
	for (auto & ent : this->options) {
		if (ent.first == "-uns" && ent.second == true) {
			for (auto & ent : this->options) {
				if (ent.first == "-gen" && ent.second == false) {
					this->usage();
				}
			}
		}
	}

	int	count = 0;
	for (auto & ent : this->heuristic) {
		if (ent.second == true)
			count++;
	}
	if (count > 1) {
		this->usage();
		
	}
}

void	Options::get_size(char *size) {
	if (this->options.find("-gen")->second == true) {
		if (this->is_digits(size))
			this->size = std::stoi(size);
		else
			usage();
	}
}

void	Options::get_args(int argc, char **argv) {
	for (int i = 1; i < argc ; i++) {
		for (auto & ent : this->options) {
			if (argv[i] == ent.first)
				ent.second = true;				
		}
	}

	for (int i = 1; i < argc ; i++) {
		for (auto & ent : this->heuristic) {
			if (argv[i] == ent.first)
				ent.second = true;				
		}
	}
}

void	Options::start() {
	this->options = {	{"-gen", this->generate_random_start = false},
				{"-uns", this->unsolvable = false} };
										
	this->heuristic = { {"-md", this->manhattan_distance = false},
				{"-mt", this->misplaced_tiles = false},
				{"-to", this->tiles_out_of_place = false} };
}