#ifndef SOLVE_HPP
# define SOLVE_HPP

# include <iostream>
# include <vector>

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
	int					_size;

	int					get_position(int x, int y);
	void				test();
	void				to_match();

};

#endif