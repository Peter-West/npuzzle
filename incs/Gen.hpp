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
	Gen(int size);
	
	std::vector<int>	puzzle;
	int					count_inv;
	bool				solvable;

private:
	int					_size;
	bool				count_inversions();
	void				generate();
	void				pour_faire_plaisir_a_manu();
	std::string			manu_me_casse_les_couilles(int m);
};

#endif