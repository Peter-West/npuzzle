#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class Parser
{
public:
	Parser();
	Parser(Parser const & src);
	~Parser();
	Parser &operator=(Parser const & rhs);
	Parser(std::string name);

	std::vector<int>	puzzle;
	int					size;

private:
	std::vector<int>	&split(const std::string &s, char delim, std::vector<int> &puzzle);
	void				split(const std::string &s, char delim);
	bool				is_digits(const std::string &str);

};

#endif