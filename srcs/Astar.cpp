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
