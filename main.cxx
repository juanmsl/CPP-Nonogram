#include <iostream>
#include "nonogram.h"
#include "controller.h"
#include "drawer.h"

int main(int argc, char* argv[]) {

	if(argc != 2) {
		std::cerr << ANSI_COLOR_RED << "Error: " << ANSI_COLOR_RESET << "Missing arguments\n";
    std::cerr << "Usage: " << argv[0]  << ANSI_COLOR_BLUE << " file\n"  << ANSI_COLOR_RESET;
		return -1;
	}

	dr::BOXSIZE = 50;
  Nonogram nonogram(argv[1]);
	dr::Drawer drawer(nonogram);
	cr::Controller controller(argc, argv, nonogram, drawer);

	return 0;
}
