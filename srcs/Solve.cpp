#include "Solve.hpp"

Solve::Solve() {

}

Solve::Solve(std::vector<int> puzzle, int size) : _puzzle(puzzle), _size(size) {
	this->_size = 4;
	this->test();
	this->to_match();
}

Solve::Solve(Solve const & src) {
	*this = src;
}

Solve::~Solve() {

}

Solve &Solve::operator=(Solve const & rhs) {
	*this = rhs;
	return (*this);
}

int		Solve::get_position(int x, int y) {
	int	pos = (x + (y * this->_size));

	// if (pos < static_cast<int>(_puzzle.size()))
	if (pos < static_cast<int>(this->_size * this->_size))
		return (pos);
	else 
		return (-1);
}

void	Solve::test(void) {
	int		D = get_position(1, 2);
	
	std::cout << "nb : " << _puzzle[D] << std::endl;
	std::cout << "size : " << _puzzle.size() << std::endl;
}

void	Solve::to_match(void) {
	std::vector<int>	solution(this->_size * this->_size, -1);
	int					i = 1;
	int					x_max = this->_size - 1;
	int					x_min = 0;
	int					y_max = this->_size - 1;
	int					y_min = 0;
	int					x = 0;
	int					y = 0;

	while (i < (this->_size * this->_size) + 1) {
		while (x <= x_max && x >= x_min) {
			std::cout << "Dans X => i : " << i << "; x : " << x << "; y : " << y << std::endl;	
			
			solution[get_position(x, y)] = i;
			if (y == y_max && x >= x_min) {
				// std::cout << "ICI !! x : " << x << std::endl;
				x--;
			}
			else if (x <= x_max) {
				// x_max--;
				x++;
				std::cout << "ICI !! x : " << x << std::endl;
			}
			i++;
			if (x == x_max && y == y_min) {
				y_min++;
			}
			if (x == x_min && y == y_max) {
				y_max--;
			}
			/*if (x == x_max || x == x_min) {
				// x_max--;
				// static int i = 0;
				// if (i > 1)
				// 	y_min--;
				break ;
			}*/
			/*if (x == y) {
				std::cout << "LA !!!!!!!!" <<std::endl;
				// y_min++;
				x_max--;
			}*/
		}

		if (x > x_max)
			x = x_max;
		if (x < x_min)
			x = x_min;

		while (y <= y_max && y >= y_min) {
			std::cout << "Dans Y => i : " << i << "; x : " << x << "; y : " << y << std::endl;	
			
			solution[get_position(x, y)] = i;
			if (x == x_min && y >= y_min) {
				// y_min++;
				// x_max--;
				y--;
				std::cout << "ICI !! y : " << y << std::endl;
			}
			else if (y <= y_max)
				y++;
			i++;
			if (y == y_min && x == x_min) {
				x_min++;
			}
			if (y == y_max && x == x_max) {
				x_max--;
			}
			/*if (y == y_max || y == y_min) {
				// std::cout<< "changement de limite" << std::endl;
				// x_max--;
				break ;
			}*/
			/*if (x == y) {
				std::cout << "LA !!!!!!!!" <<std::endl;
				x_max--;
			}*/
		}
		if (y > y_max)
			y = y_max;
		if (y < y_min)
			y = y_min;

				// y_min++;
		
		std::cout << "x_max : " << x_max <<std::endl;
		std::cout << "x_min : " << x_min <<std::endl;
		std::cout << "y_max : " << y_max <<std::endl;
		std::cout << "y_min : " << y_min <<std::endl;
		
		// x_max--;
	}

	i = 0;
	for (std::vector<int>::iterator it=solution.begin() ; it != solution.end() ; it++) {
		if (i != 0 && (i % this->_size) == 0)
			std::cout << std::endl;
		i++;
		std::cout << *it << " ";
	}

}