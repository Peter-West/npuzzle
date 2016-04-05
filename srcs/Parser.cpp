#include "Parser.hpp"

Parser::Parser() {
	std::cout << "Parser Created" << std::endl;
}

Parser::Parser(Parser const &src) {
	*this = src;
}

Parser::~Parser() {
	std::cout << "Parser Destroyed" << std::endl;
}

Parser &Parser::operator=(Parser const & rhs) {
	if (this != &rhs)
		*this = rhs;
	return (*this);
}


Parser::Parser(std::string name) : size(0) {
	std::ifstream	ifs;
	std::string		line;
	std::string		tmp;

	ifs.open(name, std::ifstream::in);
	if (!ifs.good()) {
		std::cout << "Can't read file !" << std::endl;
		exit(EXIT_FAILURE);
	}

	while (ifs.good()) {
		std::getline(ifs, line);
		split(line, ' ');
	}
	for (std::vector<int>::iterator it = puzzle.begin(); it != puzzle.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	this->to_match();
	if (!this->isSolvable()) {
		std::cout << "This is unsolvable" << std::endl;
		exit(EXIT_FAILURE);
	}
}

std::vector<int>			&Parser::split(const std::string &s, char delim, std::vector<int> &puzzle) {
	std::stringstream	ss(s);
	std::string 		item;

	while (std::getline(ss, item, delim)) {
		if (!item.empty()) {
			int tmp = 0;
			if (this->is_digits(item)) {
				if (size == 0)
					size = std::stoi(item);
				else {
					tmp = std::stoi(item);
					puzzle.push_back(tmp);
				}
			}
		}
	}
	return puzzle;
}

void						Parser::split(const std::string &s, char delim) {
	split(s, delim, puzzle);
}

bool						Parser::isSolvable() {
    int startInversions = count_inversions(this->puzzle);
    int goalInversions = count_inversions(this->_goal);

    if (this->size % 2 == 0) { // In this case, the row of the '0' tile matters

	    startInversions += this->pos_zero(this->puzzle) / this->size;
        goalInversions += this->pos_zero(this->_goal) / this->size;
    }

    return (startInversions % 2 == goalInversions % 2);
}

int							Parser::count_inversions(std::vector<int> puzz) {
	int			count = 0;

	for (size_t i = 0 ; i < puzz.size(); i++) {
		for (size_t j = i ; j < puzz.size(); j++) {
			if (puzz[i] != 0 && puzz[j] != 0 && puzz[i] > puzz[j])
				count++;
		}
	}
	return (count);
}

void						Parser::to_match(void) {
	int					total_size = this->size * this->size;
	std::vector<int>	puzzle(total_size, -1);
	int					current = 1;
	int					x = 0;
	int					ix = 1;
	int					y = 0;
	int					iy = 0;

	
	while (1) {
		puzzle[x + y * this->size] = current;
		if (current == 0)
			break ;
		current++;
		if (x + ix == this->size || x + ix < 0 || (ix != 0 && puzzle[x + ix + y * this->size] != -1)) {
			iy = ix;
			ix = 0;
		}
		else if (y + iy == this->size || y + iy < 0 || (iy != 0 && puzzle[x + (y + iy) * this->size] != -1)) {
			ix = -iy;
			iy = 0;
		}
		x += ix;
		y += iy;
		if (current == total_size) {
			current = 0;
		}
	}
	this->_goal = puzzle;
}

int							Parser::pos_zero(std::vector<int> v) {
	size_t		i; 

	for (i = 0; i < v.size() ; i++) {
		if (v[i] == 0)
			break;
	}
	return (i);
}

bool						Parser::is_digits(const std::string &str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}