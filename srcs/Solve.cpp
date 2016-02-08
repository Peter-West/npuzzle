#include "Solve.hpp"
#include <unistd.h>

Solve::Solve() {

}

Solve::Solve(std::vector<int> puzzle, int size) : _puzzle(puzzle), _size(size) {
	// this->test();
	// this->to_match();
	this->find_0();
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

std::map<int,int>	Solve::find_0() {
	int					i = 0;
	int					x = 0;
	int					y = 0;
	std::map<int,int>	res;

	for(std::vector<int>::iterator it=this->_puzzle.begin() ; it != this->_puzzle.end() ; it++) {
		if (*it == 0) {
			x = i % this->_size;
			y = i / this->_size;
			std::cout << "zero => X : " << x << ", Y: " << y << std::endl;
			res[x] = y;
			return (res);
		}
		i++;
	}
	return (res);
}

void	Solve::test(void) {
	int		D = get_position(1, 2);
	
	std::cout << "nb : " << _puzzle[D] << std::endl;
	std::cout << "size : " << _puzzle.size() << std::endl;
}

void	Solve::to_match(void) {
	int					total_size = this->_size * this->_size;
	std::vector<int>	puzzle(total_size, -1);
	int					current = 1;
	int					x = 0;
	int					ix = 1;
	int					y = 0;
	int					iy = 0;

	while (1) {
		puzzle[x + y * this->_size] = current;
		if (current == 0)
			break ;
		current++;
		if (x + ix == this->_size || x + ix < 0 || (ix != 0 && puzzle[x + ix + y * this->_size] != -1)) {
			iy = ix;
			ix = 0;
		}
		else if (y + iy == this->_size || y + iy < 0 || (iy != 0 && puzzle[x + (y + iy) * this->_size] != -1)) {
			ix = -iy;
			iy = 0;
		}
		x += ix;
		y += iy;
		if (current == total_size) {
			current = 0;
		}
	}

	this->_solution = puzzle;

	int					i = 0;

	for (std::vector<int>::iterator it=this->_solution.begin() ; it != this->_solution.end() ; it++) {
		if (i != 0 && (i % this->_size) == 0)
			std::cout << std::endl;
		i++;
		std::cout << *it << " ";
	}
}