#include "Parser.hpp"
#include "Solve.hpp"
#include "Gen.hpp"
#include "Options.hpp"
#include <iostream>
#include <exception>
#include <string.h>


int		main(int argc, char **argv) {
	Options o(argc, argv);
	heuristic	h = md;

	if (o.heuristic.find("-md")->second)
		h = md;
	else if (o.heuristic.find("-to")->second)
		h = to;
	else if (o.heuristic.find("-mt")->second)
		h = mt;

	if (o.options.find("-gen")->second) {
		Gen			*g;
		Solve		*s;

		g = new Gen(o.size, o.options.find("-uns")->second);
		s = new Solve(g->puzzle, o.size, h);
		delete g;
		delete s;
	}
	else {
		Parser		*p;
		Solve		*s;

		p = new Parser(o.filename);
		s = new Solve(p->puzzle, p->size, h);
		delete p;
		delete s;
	}
	return (0);
}

