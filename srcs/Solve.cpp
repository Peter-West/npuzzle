#include "Solve.hpp"
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>

Solve::Solve() {

}

Solve::Solve(std::vector<int> puzzle, int size) : _puzzle(puzzle), _size(size) {
	// this->test();
	this->to_match();
	this->fill_vec_points();
	this->move_empty_point();
	// this->tesssst();
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

void	Solve::tesssst() {
	node	n1;
	node	n2;

	n1.map = _points;
	n2.map = _solution;

	
	printf (">>>>>>%d\n", this->Compare2nodes(n1, n2));
}

int		Solve::get_position(int x, int y) {
	int	pos = (x + (y * this->_size));

	if (pos < static_cast<int>(this->_size * this->_size))
		return (pos);
	else 
		return (-1);
}

bool	Solve::match_nodes(node n) {
	size_t		count_node = 0;
	// int		count_point = 0;

	std::vector<point>::iterator iit = n.map.begin();
	if (!this->_closed_set.empty()) {
		for (std::vector<node>::iterator it = this->_closed_set.begin() ; it != this->_closed_set.end() ; it++) {
			printf("BLABLA\n");
			for (std::vector<point>::iterator p = it->map.begin(); p != it->map.end() ; p++) {
				std::cout << "ICIIII : " << p->value << std::endl;
				if (p->value == iit->value && p->x == iit->x && p->y == iit->y) {
					iit++;
				}
				else {
					break ;
				}
			}
		}
	}
	count_node++;
	if (count_node == this->_closed_set.size())
		return (false);
	else
		return (true);
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

/*	for (std::vector<point>::iterator it=this->_points.begin() ; it != this->_points.end() ; it++) {
		// std::cout << "value : " << it->value << ", x : " << it->x << ", y : " << it->y << ". Zero ? : " << it->zero << std::endl;
	}*/
}
/*
void	Solve::shortest_way() {

}*/

int		Solve::heuristic_manhattan_distance(node n) {
	int	res = 0;

	for (size_t i = 0; i < n.map.size() ; i++) {
		for (size_t j = 0; j < this->_solution.size() ; j++) {
			if (n.map[i].value == this->_solution[j].value) {
				res += res + (abs(n.map[i].x - this->_solution[j].x) + abs(n.map[i].y - this->_solution[j].y));
				printf("resultat %zu : value : %d tmp : %d\n", j, n.map[i].value,res);
			}
		}
	}
	printf("resultat heuristic_manhattan_distance : %d\n", res);
	return (res);
}

int		Solve::Compare2nodes(node n1, node n2) {
	if (this->heuristic_manhattan_distance(n1) < this->heuristic_manhattan_distance(n2))
		return (1);
	if (this->heuristic_manhattan_distance(n1) == this->heuristic_manhattan_distance(n2))
		return (0);
	else
		return (-1);
}

void	Solve::add_map_and_swap(int xm, int ym, int i0, int current_node, int g_count) {
	int					current_point = 0;
	std::vector<point>	tmp_map;

	std::cout << "xm : " << xm << ", ym : " << ym << std::endl;

	for (std::vector<point>::iterator it=this->_open_set[current_node].map.begin() ; it !=this->_open_set[current_node].map.end() ; it++) {
		if (it->x == xm && it->y == ym) {
			tmp_map.resize(this->_size*this->_size);
			
			std::copy(this->_open_set[current_node].map.begin(), this->_open_set[current_node].map.end(), tmp_map.begin());
			
			std::cout << "i0 : " << i0 << ", current_point : " << current_point << std::endl;
			std::cout << "tmp_map[i0].x : " << tmp_map[i0].x << ", tmp_map[current_point].x : " << tmp_map[current_point].x << std::endl;
			std::cout << "tmp_map[i0].y : " << tmp_map[i0].y << ", tmp_map[current_point].y : " << tmp_map[current_point].y << std::endl;

			std::swap(tmp_map[i0].x, tmp_map[current_point].x);
			std::swap(tmp_map[i0].y, tmp_map[current_point].y);
			this->_open_set.push_back(node());
			this->_open_set.back().map = tmp_map;
			printf("adresse enfant : %p\n", &this->_open_set[current_node]);
			if (this->_open_set[current_node].parent) {
				printf("adresse parent %p\n", this->_open_set[current_node].parent);
			}
			this->_open_set.back().g_score = g_count;
			this->_open_set.back().parent = &this->_open_set[current_node];
			
			std::cout << "_open_set map size : " << this->_open_set[current_node].map.size() << ", i0 : " << i0 << std::endl;
		}
		current_point++;
	} 
}

void	Solve::count_poss(point zero, int point_zero, int current_node) {
	static int				g_count = 0;
	std::vector<point>		tmp;

	std::cout << "x : " << zero.x << ", y : " << zero.y << std::endl;
	if ((zero.x - 1) > -1) {
		add_map_and_swap(zero.x - 1, zero.y, point_zero, current_node, g_count);
	}

	if ((zero.x + 1) < this->_size){
		add_map_and_swap(zero.x + 1, zero.y, point_zero, current_node, g_count);
	}
	
	if ((zero.y - 1) > -1) {
		add_map_and_swap(zero.x, zero.y - 1, point_zero, current_node, g_count);
	}
	
	if ((zero.y + 1) < this->_size) {
		add_map_and_swap(zero.x, zero.y + 1, point_zero, current_node, g_count);
	}
	this->print();
}

void	Solve::used_node(size_t current_node) {
	size_t			count = 0;
	
	this->_closed_set.push_back(node());
	this->_closed_set.back() = this->_open_set[current_node];
	
	for (std::vector<node>::iterator it = this->_open_set.begin() ; it != this->_open_set.end() ; it++) {
		if (count == current_node)
			this->_open_set.erase(it);
		count++;
	}
}


void	Solve::move_empty_point() {
	size_t point_zero = -1;

	this->_open_set.push_back(node());
	this->_open_set[0].map.resize(this->_size*this->_size);
	std::copy(this->_points.begin(), this->_points.end(), this->_open_set[0].map.begin());
/*	for (size_t current_node = 0 ; current_node < this->_open_set.size() ; current_node++) {
		if (current_node > 0) {
			std::cout << "current_node : " << current_node << std::endl;
			sleep(1);
		}
		printf("current_node : %zu\n", current_node);
		for (size_t point_zero = 0 ; point_zero < this->_open_set[current_node].map.size() ; point_zero++) {
			if (this->_open_set[current_node].map[point_zero].zero == true){
				printf("point_zero found at : %zu\n", point_zero);
				this->count_poss(this->_open_set[current_node].map[point_zero], point_zero, current_node);
				this->used_node(current_node);
			}
			if (point_zero > 24) {
				std::cout << "current_node : " << current_node << std::endl;
				sleep(1);
			}
		}
	}*/
	for (point_zero = 0 ; point_zero < this->_points.size() ; point_zero++) {
		if (this->_points[point_zero].zero == true) {
			printf("point_zero found at : %zu\n", point_zero);
			break ;
		}
	}

	while (!this->_open_set.empty()) {
		for (size_t current_node = 0 ; current_node < this->_open_set.size() ; current_node++) {
			if (current_node > 0) {
				std::cout << "current_node : " << current_node << std::endl;
				sleep(1);
			}
			if (!match_nodes(this->_open_set[current_node])) {
				printf("YOYOYO\n");
				this->count_poss(this->_open_set[current_node].map[point_zero], point_zero, current_node);
				this->used_node(current_node);
			}
		}
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

	int					i = 0;

	for (std::vector<int>::iterator it=puzzle.begin() ; it != puzzle.end() ; it++) {
		_solution.push_back(point());
		_solution[i].x = i % this->_size;
		_solution[i].y = i / this->_size;
		_solution[i].value = *it;
		_solution[i].right_place = false;
		if (*it == 0)
			_solution[i].zero = true;
		else
			_solution[i].zero = false;
		i++;
	}
}

void	Solve::print() {
	int		i;
	int		j;
	char	Array[this->_size][this->_size];

	std::cout << std::endl << "**** START ****" << std::endl;
	std::cout << "_open_set.size : " << this->_open_set.size() << std::endl;

	for (std::vector<node>::iterator it = this->_open_set.begin(); it != this->_open_set.end() ; it++) {
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
	std::cout << std::endl << "**** END ****" << std::endl;
}