#ifndef SOLVE_HPP
# define SOLVE_HPP

# include <iostream>
# include <vector>
# include <map>

class Solve
{
public:
	Solve(std::vector<int> puzzle, int size);
	Solve();
	Solve(Solve const & src);
	~Solve();
	Solve &operator=(Solve const & rhs);

private:
	std::vector<int>	_puzzle;
	std::vector<int>	_solution;
	int					_size;


	int					get_position(int x, int y);
	void				test();
	void				to_match();
	std::map<int,int>	find_0();

};

#endif