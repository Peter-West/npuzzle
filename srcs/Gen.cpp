#include "Gen.hpp"

Gen::Gen() {
	
}

Gen::Gen(Gen const & src) {
	*this = src;
}

Gen::~Gen() {
	
}

Gen &Gen::operator=(Gen const & rhs) {
	*this = rhs;
	return (*this);
}

Gen::Gen(int size) : _size(size) {
	this->generate();
	std::cout << "taille : " << this->_size << std::endl;
	this->pour_faire_plaisir_a_manu();
	while (!this->count_inversions()) {
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

bool				Gen::count_inversions() {
	int			count = 0;

	for (size_t i = 0 ; i < this->puzzle.size(); i++) {
		for (size_t j = i ; j < this->puzzle.size(); j++) {
			if (this->puzzle[i] != 0 && this->puzzle[j] != 0 && this->puzzle[i] > this->puzzle[j])
				count++;
		}
	}
	printf("count inv : %d\n", count);
	this->count_inv = count;
	if (this->_size % 2 == 0 && count % 2 == 0)
		return (true);
	if (this->_size % 2 != 0 && count % 2 != 0)
		return (true);
	else
		return (false);
}

std::string		Gen::manu_me_casse_les_couilles(int m) {
	std::string	 pfff;
	int		lmt = this->_size * this->_size;
	int		count_m = 0;

	// std::cout << "m : " << m;
	if (m == 0)
		m = 1;
	while (m < lmt) {
		if ((m = m * 10) < lmt)
			count_m++;
	}
	// std::cout << " count_m : " << count_m << std::endl;
	while (count_m > 0)
	{
		pfff += "0";
		count_m--;
	}
	// std::cout << std::endl;
	return pfff;
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