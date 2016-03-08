#include "Solve.hpp"
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>

Solve::Solve(std::vector<int> puzzle, int size) : _puzzle(puzzle), _size(size) {
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



bool	Solve::match_nodes(std::vector<point> m) {
	size_t		count_node = 0;
	size_t		count_point;

	// printf("SIZE CLOSED SET : %zu\n", this->_closed_set.size());
	if (!this->_closed_set.empty()) {
		for (std::vector<node>::iterator it = this->_closed_set.begin() ; it != this->_closed_set.end() ; it++) {
			// printf("BLABLA\n");
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
					return (true);
				}
				count_point++;

			}
			count_node++;
		}
	}
	// printf("false\n");
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
				// printf("resultat %zu : value : %d tmp : %d\n", j, n.map[i].value,res);
			}
		}
	}
	// printf("resultat heuristic_manhattan_distance : %d\n", res);
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

	// std::cout << "xm : " << xm << ", ym : " << ym << std::endl;

	// this->_open_set.find()

	// printf("X : %d\n", this->_open_set.begin()->map[8].x);
	// std::set<node, bool(*)(node,node)>::iterator ptr_begin = this->_open_set.begin();
	// for (std::vector<point>::iterator it = ptr_begin->map.begin() ; it != ptr_begin->map.end() ; it++) {
	node best = *this->_open_set.begin();
	std::vector<point>::iterator it;
	for (it = best.map.begin() ; it != best.map.end() ; it++) {
		
		if (it->x == xm && it->y == ym) {
			tmp_map.resize(this->_size*this->_size);
			
			std::copy(best.map.begin(), best.map.end(), tmp_map.begin());
			
			// std::cout << "p[0].map.size : " << p[0].map.size() << "\n";
			// std::cout << "i0 : " << i0 << ", current_point : " << current_point << std::endl;
			// std::cout << "tmp_map[i0].x : " << tmp_map[i0].x << ", tmp_map[current_point].x : " << tmp_map[current_point].x << std::endl;
			// std::cout << "tmp_map[i0].y : " << tmp_map[i0].y << ", tmp_map[current_point].y : " << tmp_map[current_point].y << std::endl;

			std::swap(tmp_map[i0].x, tmp_map[current_point].x);
			std::swap(tmp_map[i0].y, tmp_map[current_point].y);
			

			if (!this->match_nodes(tmp_map)) {


				// this->_open_set.push_back(node());
				// this->_open_set.back().map = tmp_map;
				// printf("adresse enfant : %p\n", &this->_open_set[current_node]);
				// if (this->_open_set[current_node].parent) {
				// 	printf("adresse parent %p\n", this->_open_set[current_node].parent);
				// }
				// this->_open_set.back().g_score = g_count;
				// this->_open_set.back().parent = &this->_open_set[current_node];

		/*		node node_tmp;
				node_tmp.map = tmp_map;
				this->_open_set.back().h_cost = this->heuristic_manhattan_distance(node_tmp);
				this->_open_set.back().f_score = g_count + this->_open_set.back().h_cost; */

				/** SET MODE **/
				node node_tmp;
				node_tmp.map = tmp_map;
				node_tmp.parent = &best;
				node_tmp.g_score = g_count;
				node_tmp.h_cost = this->heuristic_manhattan_distance(node_tmp);
				node_tmp.f_score = g_count + node_tmp.h_cost;
				printf("node ptr : %p\n", &node_tmp);
				printf("node ptr : %d\n", node_tmp.map[8].x);
				printf("open_set ptr : %p\n", &this->_open_set);
				this->_open_set.insert(node_tmp); //Seg fault : pb de pointeur sur fction (bool...)??
				// if (!this->_open_set.insert(node_tmp).first)
				// 	printf("insert failed \n");
				// std::cout << "_open_set map size : " << this->_open_set[current_node].map.size() << ", i0 : " << i0 << std::endl;
			}
		}
		current_point++;
	}
}

void	Solve::count_poss(point zero, int point_zero) {
	static int				g_count = 0;
	std::vector<point>		tmp;
	printf("X : %d\n", this->_open_set.begin()->map[8].x);

	// std::cout << "x : " << zero.x << ", y : " << zero.y << std::endl;
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
	this->print();
}

void	Solve::used_node() {
	// size_t			count = 0;
	node			tmp_node;

	tmp_node.map = this->_open_set.begin()->map;
	tmp_node.parent = this->_open_set.begin()->parent;
	tmp_node.h_cost = this->_open_set.begin()->h_cost;
	tmp_node.g_score = this->_open_set.begin()->g_score;
	tmp_node.f_score = this->_open_set.begin()->f_score;

	// this->_closed_set.push_back(node());
	this->_closed_set.push_back(tmp_node);
	// std::back_inserter(this->_open_set.end());


// std::copy(input.begin(), input.end(), std::back_inserter(output));
	// std::copy(this->_open_set.begin(), this->_open_set.end(), std::back_inserter(this->_closed_set));
	// this->_closed_set.back() = this->_open_set.begin();


	this->_open_set.erase(this->_open_set.begin());


/*	for (std::vector<node>::iterator it = this->_open_set.begin() ; it != this->_open_set.end() ; it++) {
		if (count == current_node)
			this->_open_set.erase(it);
		count++;
	}*/
	// printf("used node -> current_node : %zu\n", current_node);
}


void	Solve::move_empty_point() {
	size_t	point_zero = -1;
	size_t	current_node = 0;
	node	n_start;

	// this->_open_set.push_back(node());


	

	n_start.map.resize(this->_size*this->_size);
	std::copy(this->_points.begin(), this->_points.end(), n_start.map.begin());

	this->_open_set.insert(n_start);


	// this->_open_set.

	for (point_zero = 0 ; point_zero < this->_points.size() ; point_zero++) {
		if (this->_points[point_zero].zero == true) {
			break ;
		}
	}

	while (!this->_open_set.empty()) {
		// if ((current_node % 10000) == 0) {
		if (current_node > 0) {
			std::cout << "current_node : " << current_node << std::endl;
			sleep(1);
		}
		// this->count_poss(this->_open_set[0].map[point_zero], point_zero, 0);
		this->count_poss(this->_open_set.begin()->map[point_zero], point_zero);
		this->used_node();
		current_node++;
	}
	printf("WAOH !!!!!\n");
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
	// int		i;
	// int		j;
	// node	*p;
	char	Array[this->_size][this->_size];


	std::cout << std::endl << "**** START ****" << std::endl;
	std::cout << "_open_set.size : " << this->_open_set.size() << std::endl;


	// p=this->_open_set.get_allocator().allocate(this->_size * this->_size);


	// for (int k = 0; k < this->_size * this->_size; k++) {
	for (std::set<node, ptr_cmp>::iterator it = _open_set.begin(); it != _open_set.end() ; it++) {
		/*for ( std::vector<point>::iterator iit = it->map.begin(); iit != it->map.end() ; iit++) {
			Array[iit->y][iit->x] = iit->value;
		}*/

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
		std::cout << std::endl;
	}
	std::cout << std::endl << "**** END ****" << std::endl;
/*
	for (std::set<node, bool(*)(node,node)>::iterator it = this->_open_set.begin(); it != this->_open_set.end() ; it++) {
		// if (it->map)
		// std::cout << "map size : " << it->map.size() << std::endl;
		std::cout << "f score : " << it->f_score << std::endl;
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
	std::cout << std::endl << "**** END ****" << std::endl;*/
}