#include "Solve.hpp"
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>

Solve::Solve(std::vector<int> puzzle, int size, heuristic h) : _puzzle(puzzle), _size(size), _h(h) {
	// bool(Solve::*fn_ptr)(node, node);
	// fn_ptr = &Solve::fncomp;
	// this->_open_set(fn_ptr);
	

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

int		Solve::get_position(int x, int y) {
	int	pos = (x + (y * this->_size));

	if (pos < static_cast<int>(this->_size * this->_size))
		return (pos);
	else 
		return (-1);
}



bool	Solve::match_closed_nodes(std::vector<point> m) {
	size_t		count_node = 0;
	size_t		count_point;

	// printf("SIZE CLOSED SET : %zu\n", this->_closed_set.size());
	if (!this->_closed_set.empty()) {
		for (std::vector<node>::iterator it = this->_closed_set.begin() ; it != this->_closed_set.end() ; it++) {
			count_point = 0;
			std::vector<point>::iterator iit = m.begin();
			for (std::vector<point>::iterator p = it->map.begin(); p != it->map.end() ; p++) {
				// std::cout << "ICIIII : " << p->value << std::endl;
				if (p->value == iit->value && p->x == iit->x && p->y == iit->y) {
					iit++;
				}
				else {
					break ;
				}
				if (count_point == m.size() - 1) {
					// printf("TRUE at : %zu\n", count_node);
					node tmp_node;
					tmp_node.map = m;
					if (this->_h == md) {
						if (this->heuristic_manhattan_distance(*it) > this->heuristic_manhattan_distance(tmp_node))
							return (false);
						else
							return (true);
					}
					else if (this->_h == mt) {
						if (this->misplaced_tiles(*it) > this->misplaced_tiles(tmp_node))
							return (false);
						else
							return (true);
					}
				}
				count_point++;

			}
			count_node++;
		}
	}
	return (false);
}

bool	Solve::match_open_nodes(std::vector<point> m) {
	size_t		count_node = 0;
	size_t		count_point;

	// printf("SIZE CLOSED SET : %zu\n", this->_closed_set.size());
	if (!this->_open_set.empty()) {
		for (std::set<node, ptr_cmp>::iterator it = this->_open_set.begin() ; it != this->_open_set.end() ; it++) {
			count_point = 0;
			std::vector<point>::iterator iit = m.begin();
			for (size_t i = 0; i < it->map.size() ; i++) {
				// std::cout << "ICIIII : " << p->value << std::endl;
				if (it->map[i].value == iit->value && it->map[i].x == iit->x && it->map[i].y == iit->y) {
					iit++;
				}
				else {
					break ;
				}
				if (count_point == m.size() - 1) {
					// printf("TRUE at : %zu\n", count_node);
					node tmp_node;
					tmp_node.map = m;
					if (this->_h == md) {
						if (this->heuristic_manhattan_distance(*it) > this->heuristic_manhattan_distance(tmp_node))
							return (false);
						else
							return (true);
					}
					else if (this->_h == mt) {
						if (this->misplaced_tiles(*it) > this->misplaced_tiles(tmp_node))
							return (false);
						else
							return (true);
					}
				}
				count_point++;

			}
			count_node++;
		}
	}
	return (false);
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
}

bool	Solve::goal_reached(std::vector<point> m) {
	for (size_t i = 0; i < m.size() ; i++) {
		for (size_t j = 0; j < this->_solution.size() ; j++) {
			if (m[i].value == this->_solution[j].value && (m[i].x != this->_solution[j].x || m[i].y != this->_solution[j].y))
				return (false);
		}
	}
	return (true);
}

int		Solve::misplaced_tiles(node n) {
	int res = 0;

	for (size_t i = 0; i < n.map.size() ; i++) {
		for (size_t j = 0; j < this->_solution.size() ; j++) {
			if (n.map[i].value == this->_solution[j].value) {
				if (n.map[i].x != this->_solution[j].x || n.map[i].y != this->_solution[j].y) {
					res++;
				}
			}
		}
	}
	return (res);
}

int		Solve::heuristic_manhattan_distance(node n) {
	int	res = 0;

	for (size_t i = 0; i < n.map.size() ; i++) {
		for (size_t j = 0; j < this->_solution.size() ; j++) {
			if (n.map[i].value == this->_solution[j].value) {
				res += res + (abs(n.map[i].x - this->_solution[j].x) + abs(n.map[i].y - this->_solution[j].y));
			}
		}
	}
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

void	Solve::add_map_and_swap(int xm, int ym, int i0, int g_count) {
	int					current_point = 0;
	std::vector<point>	tmp_map;

	node best = *this->_open_set.begin();
	std::vector<point>::iterator it;
	for (it = best.map.begin() ; it != best.map.end() ; it++) {
		
		if (it->x == xm && it->y == ym) {
			tmp_map.resize(this->_size*this->_size);
			
			std::copy(best.map.begin(), best.map.end(), tmp_map.begin());
			std::swap(tmp_map[i0].x, tmp_map[current_point].x);
			std::swap(tmp_map[i0].y, tmp_map[current_point].y);
			
			if (!this->match_closed_nodes(tmp_map) && !this->match_open_nodes(tmp_map)) {
				/** SET MODE **/
				node node_tmp;
				node_tmp.map = tmp_map;
				node_tmp.parent = &best;
				node_tmp.g_score = g_count;
				if (this->_h == md)
					node_tmp.h_cost = this->heuristic_manhattan_distance(node_tmp);
				else if (this->_h == mt)
					node_tmp.h_cost = this->misplaced_tiles(node_tmp);
				
				node_tmp.f_score = g_count + node_tmp.h_cost;
				// printf("node ptr : %p\n", &node_tmp);
				// printf("open_set ptr : %p\n", &this->_open_set);
				// printf("open set 0 size : %zu\n", _open_set.size());
				this->_open_set.insert(node_tmp);
				// printf("open set 1 size : %zu\n", _open_set.size());
			}
		}
		current_point++;
	}
}

void	Solve::count_poss(point zero, int point_zero) {
	static int				g_count = 0;
	std::vector<point>		tmp;

	if ((zero.x - 1) > -1) {
		add_map_and_swap(zero.x - 1, zero.y, point_zero, g_count);
	}

	if ((zero.x + 1) < this->_size){
		add_map_and_swap(zero.x + 1, zero.y, point_zero, g_count);
	}
	
	if ((zero.y - 1) > -1) {
		add_map_and_swap(zero.x, zero.y - 1, point_zero, g_count);
	}
	
	if ((zero.y + 1) < this->_size) {
		add_map_and_swap(zero.x, zero.y + 1, point_zero, g_count);
	}
	g_count++;
}

void	Solve::used_node(std::set<node, ptr_cmp>::iterator it) {
	node			tmp_node;

	tmp_node.map = it->map;
	tmp_node.parent = it->parent;
	tmp_node.h_cost = it->h_cost;
	tmp_node.g_score = it->g_score;
	tmp_node.f_score = it->f_score;
	this->_closed_set.push_back(tmp_node);
	
	// char	Array[this->_size][this->_size];

	// printf("USED open set 0 size : %zu\n", _open_set.size());
/*	for(size_t i = 0; i < it->map.size(); i++) {
			Array[it->map[i].y][it->map[i].x] = it->map[i].value;
		}
	std::cout << "**************" << std::endl;
	std::cout << "F score : " << it->f_score << std::endl;
	std::cout << "G score : " << it->g_score << std::endl;
	std::cout << "H cost : " << it->h_cost << std::endl;
	for (int i = 0 ; i < this->_size ; i++) {
		for (int j = 0 ; j < this->_size ; j++) {
			printf("%d ", Array[i][j]);
		}
		std::cout << std::endl;
	}
	std::cout << "**************" << std::endl;*/

	this->_open_set.erase(it);
	// printf("USED open set 1 size : %zu\n", _open_set.size());
	// printf("Closed Set size : %zu\n", this->_closed_set.size());
}


void	Solve::move_empty_point() {
	size_t	point_zero = -1;
	size_t	current_node = 0;
	node	n_start;

	n_start.map.resize(this->_size*this->_size);
	std::copy(this->_points.begin(), this->_points.end(), n_start.map.begin());

	this->_open_set.insert(n_start);

	for (point_zero = 0 ; point_zero < this->_points.size() ; point_zero++) {
		if (this->_points[point_zero].zero == true) {
			break ;
		}
	}

	while (!this->_open_set.empty()) {
		if (this->goal_reached(this->_open_set.begin()->map)) {
			std::cout << "current_node : " << current_node << std::endl;
			std::cout << "VICTORY !!" << std::endl;
			break ;
		}
		if (current_node > 0) {
			if (current_node % 1000 == 0)
				std::cout << "current_node : " << current_node << std::endl;
			std::set<node, ptr_cmp>::iterator it = this->_open_set.begin();
			// printf("ptr begin avant : %p\n", &it);
			this->count_poss(this->_open_set.begin()->map[point_zero], point_zero);
			// std::set<node, ptr_cmp>::iterator it0 = this->_open_set.begin();
			// printf("ptr begin apres : %p\n", &it0);
			
			this->used_node(it);
			// sleep(1);
		}
		else {
			
			this->count_poss(this->_open_set.begin()->map[point_zero], point_zero);
			// this->_closed_set.push_back(n_start);
			// this->_open_set.erase(std::prev(this->_open_set.end()));
		}
		// this->print();
		current_node++;
	}
	printf("WAOH !!!!!\n");
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
	char	Array[this->_size][this->_size];
	int		count = 0;

	// std::cout << std::endl << std::endl << "**** START ****" << std::endl;
	// std::cout << "_open_set.size : " << this->_open_set.size() << std::endl;

	for (std::set<node, ptr_cmp>::iterator it = _open_set.begin(); it != _open_set.end() ; it++) {
		// std::cout << "Parent F score : " << it->parent->f_score << std::endl;
		
		if (it->h_cost < 101) {
			std::cout << std::endl << std::endl << "**** START ****" << std::endl;
			std::cout << "Position in set : " << count << std::endl;
			std::cout << "F score : " << it->f_score << std::endl;
			std::cout << "G score : " << it->g_score << std::endl;
			std::cout << "H cost : " << it->h_cost << std::endl;
			for (size_t i = 0; i < it->map.size() ; i++) {
				Array[it->map[i].y][it->map[i].x] = it->map[i].value;
			}

			std::cout << "**************" << std::endl;
			for (int i = 0 ; i < this->_size ; i++) {
				for (int j = 0 ; j < this->_size ; j++) {
					printf("%d ", Array[i][j]);
				}
				std::cout << std::endl;
			}
			std::cout << "**************" << std::endl;
		}
		count++;
	}
	// std::cout << std::endl << "**** END ****" << std::endl;
	// std::cout << std::endl;
}