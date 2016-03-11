#ifndef SOLVE_HPP
# define SOLVE_HPP

# include <iostream>
# include <vector>
# include <map>
# include <algorithm>
# include <set>
# include <iterator>
# include "Astar.hpp"


struct point {
	int		value;
	int		x;
	int		y;
	bool	zero;
	bool	right_place;
};

struct node {
	std::vector<point>	map;
	struct node			*parent;
	int					h_cost;
	int					g_score;
	int					f_score;
};

struct ptr_cmp {
	bool	operator()(node n1, node n2) {
		// printf("n1.f_score : %d, n2.f_score : %d\n", n1.f_score, n2.f_score);
		return n1.h_cost <= n2.h_cost;
	}
};


class Solve
{
public:
	Solve(std::vector<int> puzzle, int size);
	Solve() = delete;
	Solve(Solve const & src);
	~Solve();
	Solve &operator=(Solve const & rhs);

private:
	std::vector<int>					_puzzle;
	std::vector<point>					_solution;
	std::vector<point>					_points;
	std::set<node, ptr_cmp>				_open_set;
	std::vector<node>					_closed_set;
	std::vector<node>					_total_path;
	int									_size;

	int						get_position(int x, int y);
	void					to_match();
	void					fill_vec_points();
	void					count_poss(point zero, int point_zero);
	void					move_empty_point();
	int						heuristic_manhattan_distance(node n);
	void					add_map_and_swap(int xm, int ym, int i0, int g_count);
	void					print();
	int						Compare2nodes(node n1, node n2);
	void					tesssst();
	void					used_node(std::set<node, ptr_cmp>::iterator it);
	bool					match_closed_nodes(std::vector<point> m);
	bool					match_open_nodes(std::vector<point> m);
	bool					goal_reached(std::vector<point> m);
};

#endif