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
	generate();
	std::cout << "taille : " << this->_size << std::endl;
	pour_faire_plaisir_a_manu();
}

void	Gen::generate() {
	int		limit = this->_size * this->_size;
	int		tmp;
	bool	available;

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

std::string		Gen::manu_me_casse_les_couilles(int m) {
	std::string	 pfff;
	int		lmt = this->_size * this->_size;
	int		count_m = 0;

	std::cout << "m : " << m;
	if (m == 0)
		m = 1;
	while (m < lmt) {
		if ((m = m * 10) < lmt)
			count_m++;
	}
	std::cout << " count_m : " << count_m << std::endl;
	while (count_m > 0)
	{
		pfff += "0";
		count_m--;
	}
	std::cout << std::endl;
	return pfff;
}

void			Gen::pour_faire_plaisir_a_manu() {
	int	i = 0;

	for(std::vector<int>::iterator it = puzzle.begin(); it != puzzle.end(); it++) {
		std::cout << this->manu_me_casse_les_couilles(*it) << *it;
		i++;
		if ((i % (this->_size) == 0))
			std::cout << std::endl;
		else
			std::cout << " ";
	}
	std::cout << std::endl;
}