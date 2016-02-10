#include "Solve.hpp"
#include <unistd.h>

Solve::Solve() {

}

Solve::Solve(std::vector<int> puzzle, int size) : _puzzle(puzzle), _size(size) {
	// this->test();
	// this->to_match();
	this->fill_vec_points();
	this->move_empty_point();
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

void	Solve::fill_vec_points() {
	int						i = 0;

	for (std::vector<int>::iterator it=this->_puzzle.begin() ; it != this->_puzzle.end() ; it++) {
		_points.push_back(point());
		_points[i].x = i % this->_size;
		_points[i].y = i / this->_size;
		_points[i].value = *it;
		_points[i].right_place = false;
		if (*it == 0)
			_points[i].zero = true;
		else
			_points[i].zero = false;
		i++;
	}

	for (std::vector<point>::iterator it=this->_points.begin() ; it != this->_points.end() ; it++) {
		std::cout << "value : " << it->value << ", x : " << it->x << ", y : " << it->y << ". Zero ? : " << it->zero << std::endl;
	}
}

int		Solve::heuristic_manhattan_distance() {
	int	res = 0;

	// res = abs(xb - xa) + abs(yb - ya);
	return (res);
}

void	Solve::add_map_and_swap(int xm, int ym, int i0) {
	// int					tmp_x0 = 0;
	// int					tmp_y0 = 0;
	std::vector<point>	tmp_map;
	int					i = 0;

// PB0 : Recherche dans le vecteur de vecteur plutot que dans la carte de base
// => pas les meme args entre les points et les maps
	std::cout << "i0 : " << i0 << std::endl;
	for (std::vector<point>::iterator it=this->_points.begin() ; it != this->_points.end() ; it++) {
		if (it->x == xm && it->y == ym) {
			for (size_t	 j = 0 ; j != this->_points.size() ; j++) {
				if (this->_points[j].zero == true) {
					std::vector<point> tmp_map = this->_points;
					this->_list.push_back(std::vector<point>());
					/*tmp_x0 = this->_points[j].x;
					tmp_y0 = this->_points[j].y;
					tmp_map[j].x = this->_points[j].x;
					tmp_map[j].y = this->_points[j].y;
					tmp_map[i].x = tmp_x0;
					tmp_map[i].y = tmp_y0;*/
					std::swap(tmp_map[j].x , tmp_map[i].x);
					std::swap(tmp_map[j].y , tmp_map[i].y);
					this->_list.back() = tmp_map;
					std::cout << "j : " << j << std::endl;
				}
			}
		}
		i++;
	}
	this->print();
}

void	Solve::print() {
	int	i = 0;

	for (std::vector<std::vector<point>>::iterator it = this->_list.begin(); it != this->_list.end() ; it++) {
		for (std::vector<point>::iterator iit = it->begin(); iit != it->end() ; iit++ ) {
			std::cout << iit->value;
			if (i != 0 && (i % this->_size) == 0)
				std::cout << std::endl;
			else
				std::cout << " ";
			i++;
		}
	}
}

void	Solve::count_poss(point zero, int i) {
	int						count = 0;
	std::vector<point>		tmp;

	if ((zero.x - 1) > -1) {
		add_map_and_swap(zero.x--, zero.y, i);
		count++;
	}

	if ((zero.x + 1) < this->_size)
		count++;
	
	if ((zero.y - 1) > -1)
		count++;
	
	if ((zero.y + 1) < this->_size)
		count++;

	std::cout << "count possibility : " << count << std::endl;
}

void	Solve::move_empty_point() {
	int	i = 0;
	for (std::vector<point>::iterator it=this->_points.begin() ; it != this->_points.end() ; it++) {
		if (it->zero == true)
			this->count_poss(*it, i);
		i++;
	}
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
/*
	int					i = 0;

	for (std::vector<int>::iterator it=this->_solution.begin() ; it != this->_solution.end() ; it++) {
		if (i != 0 && (i % this->_size) == 0)
			std::cout << std::endl;
		i++;
		std::cout << *it << " ";
	}*/
}