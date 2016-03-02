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


class Solve
{
public:
	Solve(std::vector<int> puzzle, int size);
	Solve();
	Solve(Solve const & src);
	~Solve();
	Solve &operator=(Solve const & rhs);

private:
	std::vector<int>				_puzzle;
	std::vector<point>				_solution;
	std::vector<point>				_points;
	// bool(*fn_ptr)(node, node) = fncomp;
	
	std::set<node, bool(*)(node,node)>	_open_set;
	// std::vector<node>				_open_set;
	std::vector<node>				_closed_set;
	std::vector<node>				_total_path;
	int								_size;

	int						get_position(int x, int y);
	void					test();
	void					to_match();
	void					fill_vec_points();
	void					count_poss(point zero, int point_zero);
	void					move_empty_point();
	int						heuristic_manhattan_distance(node n);
	void					add_map_and_swap(int xm, int ym, int i0, int g_count);
	void					print();
	int						Compare2nodes(node n1, node n2);
	void					tesssst();
	void					used_node();
	bool					match_nodes(std::vector<point> m);
	bool					fncomp(node n1, node n2);
};

#endif