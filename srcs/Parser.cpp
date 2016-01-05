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

Parser &Parser::operator=(Parser const &rhs) {
	*this = rhs;
	return (*this);
}

Parser::Parser(std::string name) : size(0) {
	std::ifstream	ifs;
	std::string		line;
	std::string		tmp;

	ifs.open(name, std::ifstream::in);
	while (ifs.good()) {
		std::getline(ifs, line);
		split(line, ' ');
	}
	for (std::vector<int>::iterator it = puzzle.begin(); it != puzzle.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
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

bool						Parser::is_digits(const std::string &str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}