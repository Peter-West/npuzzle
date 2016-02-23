#ifndef SOLVE_HPP
# define SOLVE_HPP

# include <iostream>
# include <vector>
# include <map>
# include <algorithm>
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
	int					cost;
	int					heuristic;
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
	std::vector<node>				_list;
	int								_size;
	// int						g_score;
	// int						f_score;

	int						get_position(int x, int y);
	void					test();
	void					to_match();
	void					fill_vec_points();
	void					count_poss(point zero, int point_zero, int current_node);
	void					move_empty_point();
	int						heuristic_manhattan_distance();
	void					add_map_and_swap(int xm, int ym, int i0, int current_node);
	void					print();
};

#endif