#ifndef ARGS_HPP
# define ARGS_HPP
# include <iostream>
# include <map>

class Options
{
public:
	Options();
	Options(int argc, char **argv);
	Options(Options const &src);
	Options &operator=(Options const & rhs);
	~Options();

	std::map<std::string, bool>	options;
	std::map<std::string, bool>	heuristic;
	std::string					filename;
	int							size;
	bool						manhattan_distance;
	bool						tiles_out_of_place;
	bool						misplaced_tiles;
	bool						generate_random_start;
	bool						unsolvable;

private:
	void						start();
	void						usage();
	bool						is_digits(const std::string &str);
	void						check_errors(int argc, char **argv);
	void						check_options_errors();
	void						get_args(int argc, char **argv);
	void						get_size(char *size);
};

#endif