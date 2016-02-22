#include "Solve.hpp"
#include <unistd.h>
#include <stdio.h>
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
		// std::cout << "value : " << it->value << ", x : " << it->x << ", y : " << it->y << ". Zero ? : " << it->zero << std::endl;
	}
}

int		Solve::heuristic_manhattan_distance() {
	int	res = 0;

	// res = abs(xb - xa) + abs(yb - ya);
	return (res);
}

void	Solve::add_map_and_swap(int xm, int ym, int i0, int current_node) {
	int					current_point = 0;
	std::vector<point>	tmp_map;

	std::cout << "xm : " << xm << ", ym : " << ym << std::endl;

	// current map non conservé **********


	for (std::vector<point>::iterator it=this->_list[current_node].map.begin() ; it !=this->_list[current_node].map.end() ; it++) {
		if (it->x == xm && it->y == ym) {
		
			tmp_map.resize(this->_size*this->_size);
			
			// std::cout << "**test size : " << this->_list[current_node].map.size() << std::endl;

			std::copy(this->_list[current_node].map.begin(), this->_list[current_node].map.end(), tmp_map.begin());
			
			// nod.map.push_back(std::vector<point>())
			// this->_list[current_point].map.push_back(point());

			// std::cout << "size : " << this->_list[current_node].map.size() << std::endl;
			// std::copy(tmp_map.begin(), tmp_map.end(), _list[current_node].map.begin());
			
			// verifie coord des deux points ***********

			std::swap(tmp_map[i0].x, tmp_map[current_point].x);
			std::swap(tmp_map[i0].y, tmp_map[current_point].y);
			this->_list.push_back(node());
			this->_list.back().map = tmp_map;
			
			// std::cout<< "add map and swap, current_point : " << current_point << std::endl;
			std::cout << "_list map size : " << this->_list[current_node].map.size() << ", i0 : " << i0 << std::endl;
			
			/*for (int j = 0 ; j < (int)_list[current_point].map.size() ; j++) {
				std::cout << _list[current_point].map[j].value << " ";
			}*/
			// std::cout << std::endl;

			current_point++;
		}
	}
}


/*
	for (std::vector<point>::iterator it=this->_points.begin() ; it != this->_points.end() ; it++) {
		if (it->x == xm && it->y == ym) {
			tmp_map.resize(this->_size*this->_size);
			// tmp_map = this->_list[i0].map;

			std::cout << "**test size : " << this->_list[i0].map.size() << std::endl;

			std::copy(this->_list[i0].map.begin(), this->_list[i0].map.end(), tmp_map.begin());
			
			// nod.map.push_back(std::vector<point>())
			this->_list.push_back(node());
			// this->_list[i].map.push_back(point());

			_list[i].map = tmp_map;
			std::cout << "size : " << _list[i].map.size() << std::endl;
			std::swap(tmp_map[i0].x, tmp_map[i].x);
			std::swap(tmp_map[i0].y, tmp_map[i].y);
			std::copy(tmp_map.begin(), tmp_map.end(), _list[i].map.begin());
			// printf("_list[i].map ptr : %p \n", _list[i].map);
			
			std::cout<< "add map and swap, i : " << i << std::endl;
			
			for (int j = 0 ; j < (int)_list[i].map.size() ; j++) {
				std::cout << _list[i].map[j].value << " ";
			}

			std::cout << std::endl;
			i++;
		}
	}
*/


void	Solve::count_poss(point zero, int point_zero, int current_node) {
	int						count = 0;
	std::vector<point>		tmp;

	std::cout << "x : " << zero.x << ", y : " << zero.y << std::endl;
	if ((zero.x - 1) > -1) {
		add_map_and_swap(zero.x - 1, zero.y, point_zero, current_node);
		count++;
	}

	if ((zero.x + 1) < this->_size){
		add_map_and_swap(zero.x + 1, zero.y, point_zero, current_node);
		count++;
	}
	
	if ((zero.y - 1) > -1) {
		add_map_and_swap(zero.x, zero.y - 1, point_zero, current_node);
		count++;
	}
	
	if ((zero.y + 1) < this->_size) {
		add_map_and_swap(zero.x, zero.y + 1, point_zero, current_node);
		count++;
	}

	this->print();
	std::cout << "count possibility : " << count << std::endl;

}

void	Solve::move_empty_point() {
	int		point_zero = 0;
	int		current_node = 0;

	this->_list.push_back(node());
	std::cout << "test taille: " << this->_list.size() << std::endl;
	this->_list[0].map.resize(this->_size*this->_size);
	std::copy(this->_points.begin(), this->_points.end(), this->_list[0].map.begin());
	std::cout << "test taille map : " << this->_list[0].map.size() << std::endl;
	for (std::vector<node>::iterator it=this->_list.begin() ; it != this->_list.end() ; it++) {
		if (current_node > 0)
			break ;
		printf("current_node : %d\n", current_node);
		for (std::vector<point>::iterator iit=it->map.begin() ; iit !=it->map.end() ; iit++) {
			if (iit->zero == true){
				printf("point_zero found at : %d\n", point_zero);
				this->count_poss(*iit, point_zero, current_node);
			}
			if (point_zero > 24) {
				printf("it->map.size() : %lu, point_zero : %d\n", it->map.size(), point_zero);
				sleep(1);
			}
			point_zero++;
		}
		current_node++;
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

void	Solve::print() {
	int		i;
	int		j;
	char	Array[this->_size][this->_size];

	std::cout << "_list.size : " << this->_list.size() << std::endl;

	for (std::vector<node>::iterator it = this->_list.begin(); it != this->_list.end() ; it++) {
		// if (it->map)
		std::cout << "map size : " << it->map.size() << std::endl;
		// else
			// std::cout << "no map" << std::endl;
		for (std::vector<point>::iterator iit = it->map.begin(); iit != it->map.end() ; iit++) {
			
			// std::cout << iit->value << " ";
			Array[iit->y][iit->x] = iit->value;
		}
		std::cout << "**************" << std::endl;
		for (i = 0 ; i < this->_size ; i++) {
			for (j = 0 ; j < this->_size ; j++) {
				printf("%d ", Array[i][j]);
			}
			std::cout << std::endl;
		}
		std::cout << "**************" << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl << "END" << std::endl;
}