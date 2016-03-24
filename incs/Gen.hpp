#ifndef GEN_HPP
# define GEN_HPP

# include <iostream>
# include <stdlib.h>
# include <time.h>
# include <vector>

class Gen
{
public:
	Gen();
	Gen(Gen const & src);
	~Gen();
	Gen &operator=(Gen const & rhs);
	Gen(int size, bool unsolv);
	
	std::vector<int>	puzzle;
	int					count_inv;

private:
	std::vector<int>	_goal;
	int					_size;
	bool				_unsolv;

	bool				isSolvable();
	void				to_match(void);
	int					count_inversions(std::vector<int> puzz);
	void				generate();
	void				pour_faire_plaisir_a_manu();
	int					pos_zero(std::vector<int> v);
};

#endif