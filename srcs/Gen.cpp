#include "Gen.hpp"

Gen::Gen() {
	
}

Gen::Gen(Gen const & src) {
	*this = src;
}

Gen::~Gen() {
	
}

Gen &Gen::operator=(Gen const & rhs) {
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

Gen::Gen(int size, bool unsolv) : _size(size), _unsolv(unsolv) {
	this->generate();
	std::cout << "taille : " << this->_size << std::endl;
	this->pour_faire_plaisir_a_manu();
	this->to_match();
	
	if (this->_unsolv) {
		std::cout << "Puzzle is Unsolvable" <<std::endl;
		while (this->isSolvable())
			this->generate();
	}
	else {
		std::cout << "Puzzle is Solvable" <<std::endl;
		while (!this->isSolvable())
			this->generate();
	}
}

void	Gen::generate() {
	int		limit = this->_size * this->_size;
	int		tmp;
	bool	available;

	this->puzzle.clear();
	srand (time(NULL));
	while (static_cast<int>(puzzle.size()) != limit) {
		available = true;
		tmp = rand() % limit;
		for(std::vector<int>::iterator it = puzzle.begin(); it != puzzle.end(); it++) {
			if (tmp == *it)	{
				available = false;
				break ;
			}
		}
		if (available == true) {
			puzzle.push_back(tmp);
		}
	}
}

int				Gen::pos_zero(std::vector<int> v) {
	size_t		i; 

	for (i = 0; i < v.size() ; i++) {
		if (v[i] == 0)
			break;
	}
	return (i);
}

// Returns true if `start` belongs to the same permutation group as `goal`
// template <uint size>
bool			Gen::isSolvable() {
    int startInversions = count_inversions(this->puzzle);
    int goalInversions = count_inversions(this->_goal);

    printf("startInversions : %d\n", startInversions);
    printf("goalInversions : %d\n", goalInversions);

    if (this->_size % 2 == 0) { // In this case, the row of the '0' tile matters

	    startInversions += this->pos_zero(this->puzzle) / this->_size;
        goalInversions += this->pos_zero(this->_goal) / this->_size;
    }

    return (startInversions % 2 == goalInversions % 2);
}

int				Gen::count_inversions(std::vector<int> puzz) {
	int			count = 0;

	for (size_t i = 0 ; i < puzz.size(); i++) {
		for (size_t j = i ; j < puzz.size(); j++) {
			if (puzz[i] != 0 && puzz[j] != 0 && puzz[i] > puzz[j])
				count++;
		}
	}
	return (count);
}

void			Gen::to_match(void) {
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
	this->_goal = puzzle;
}

void			Gen::pour_faire_plaisir_a_manu() {
	int	i = 0;

	for(std::vector<int>::iterator it = puzzle.begin(); it != puzzle.end(); it++) {
		// std::cout << this->manu_me_casse_les_couilles(*it) << *it;
		std::cout << *it;
		i++;
		if ((i % (this->_size) == 0))
			std::cout << std::endl;
		else
			std::cout << " ";
	}
	std::cout << std::endl;
}