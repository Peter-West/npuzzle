#ifndef SOLVE_HPP
# define SOLVE_HPP

# include <iostream>
# include <vector>
# include <map>
# include <algorithm>
# include <set>
# include <unordered_set>
# include <iterator>
# include <exception>
# include "Astar.hpp"

enum heuristic { md, mt, to };

struct point {
	int		value;
	int		x;
	int		y;
	bool	zero;
	bool	right_place;
};

struct node {
	std::vector<point>	map;
	size_t				hash;
	struct node			*parent;
	int					h_cost;
	int					g_score;
	int					f_score;
};

struct ptr_cmp {
	bool	operator()(node *n1, node *n2) {
		return n1->h_cost <= n2->h_cost;
	}
};

struct hash_vec {
	unsigned int hash_uint(unsigned int x) const {
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x);
		return x;
	}

	std::size_t operator()(node const *n1) const {
		std::size_t seed = n1->map.size();
		for(auto i : n1->map) {
			seed ^= hash_uint(i.value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= hash_uint(i.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= hash_uint(i.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return (seed);
	}
};

class Solve
{
public:
	Solve(std::vector<int> puzzle, int size, heuristic h);
	Solve() = delete;
	Solve(Solve const & src);
	~Solve();
	Solve &operator=(Solve const & rhs);

private:
	std::vector<int>					_puzzle;
	std::vector<point>					_solution;
	std::vector<point>					_points;
	std::set<node*, ptr_cmp>			_open_set;
	// std::vector<node*>					_closed_set;
	std::unordered_set<node*, hash_vec>	_closed_set;
	std::vector<node*>					_final_path;
	int									_size;
	heuristic							_h;

	int						get_position(int x, int y);
	void					to_match();
	void					fill_vec_points();
	void					count_poss(point zero, int point_zero);
	void					move_empty_point();
	void					add_map_and_swap(int xm, int ym, int i0, int g_count);
	void					print();
	void					print_final_path();
	void					reverse_path(std::set<node*, ptr_cmp>::iterator it);
	void					tesssst();
	void					used_node(std::set<node*, ptr_cmp>::iterator it);
	bool					match_closed_nodes(std::vector<point> m);
	bool					match_open_nodes(std::vector<point> m);
	bool					goal_reached(std::vector<point> m);
	int						heuristic_manhattan_distance(node *n);
	int						misplaced_tiles(node *n);
	int						tiles_out_of_place(node *n);
	void					clean();
};

#endif