#ifndef IO_HPP
#define IO_HPP

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class Io {
   private:
	string getFileName(const int& argc, char** argv, const string& flag);
	int getId(const int& argc, char** argv, const string& flag);

   public:
	string getInputFileName(const int& argc, char** argv);
	int getSolutionId(const int& argc, char** argv);
};

#endif
