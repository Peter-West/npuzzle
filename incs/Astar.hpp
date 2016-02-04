#ifndef ASTAR_HPP
# define ASTAR_HPP

#include <iostream>

class Astar {
public:
	Astar();
	Astar(Astar const & src);
	~Astar();
	Astar &operator=(Astar const & rhs);
};

#endif