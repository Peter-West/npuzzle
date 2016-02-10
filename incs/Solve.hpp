#ifndef SOLVE_HPP
# define SOLVE_HPP

# include <iostream>
# include <vector>
# include <map>
# include "Astar.hpp"


struct point {
	int		value;
	int		x;
	int		y;
	int		cost;
	int		heuristic;
	bool	zero;
	bool	right_place;
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
	std::vector<int>				_solution;
	// std::vector<t_points>		_points;
	std::vector<point>				_points;
	std::vector<std::vector<point>>	_list;
	int								_size;
	// int						g_score;
	// int						f_score;

	int						get_position(int x, int y);
	void					test();
	void					to_match();
	void					fill_vec_points();
	void					count_poss(point zero, int i);
	void					move_empty_point();
	int						heuristic_manhattan_distance();
	void					add_map_and_swap(int xm, int ym, int i0);
	void					print();
};

#endif