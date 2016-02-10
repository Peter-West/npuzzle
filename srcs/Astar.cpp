#include "Astar.hpp"

Astar::Astar() {
	std::cout << "Astar created" << std::endl;
}

Astar::Astar(Astar const & src) {
	*this = src;
}

Astar::~Astar() {
	std::cout << "Astar destroyed" << std::endl;
}

Astar &Astar::operator=(Astar const & rhs) {
	*this = rhs;
	return (*this);
}
/*
int		Astar::cmp_nodes(node1, node2) {
	if (node1 < node2)
		return (1);
	else if
		return (0);
	else
		return (-1);
}

Astar::Astar(start, goal) {

}
*/
/*
int		Astar::heuristic_manhattan_distance() {
	int	res = 0;

	res = abs(xb - xa) + abs(yb - ya);
	return (res);
}
*/
