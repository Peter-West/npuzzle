#ifndef ASTAR_HPP
# define ASTAR_HPP

#include <iostream>
#include <vector>
/*
struct node
{
	int	value;
	int	x;
	int	y;
	int	cost;
	int heuristic;
};*/

class Astar {
public:
	Astar();
	Astar(Astar const & src);
	~Astar();
	Astar &operator=(Astar const & rhs);

private:
	int	heuristic_manhattan_distance();
	// std::vector<node>	_openlist;
	// std::vector<node>	_closedlist;

};

#endif