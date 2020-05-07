#include <iostream>

#include "StarWars.h"

using namespace std;



int main(int argc, char **argv) {
	try {
		StarWars g;
		g.start();
	} catch (std::string &e) { // catch errors thrown as strings
		cerr << e << endl;
	} catch (const std::exception &e) { // catch other exceptions
		cerr << e.what();
	} catch (...) {
		cerr << "Caught and exception of unknown type ..";
	}

	return 0;
}
