#include "io.hpp"

string Io::getFileName(const int& argc, char** argv, const string& flag) {
	string file_name;
	for (int i = 1; i < argc; i += 2) {
		string argument = argv[i];
		if (argument == flag) {
			file_name = argv[i + 1];
			return file_name;
		}
	}
	return "";
}

string Io::getInputFileName(const int& argc, char** argv) {
	string flag = "-i";
	string input_file_name = getFileName(argc, argv, flag);
	return input_file_name;
}

int Io::getId(const int& argc, char** argv, const string& flag) {
	for (int i = 1; i < argc; i += 2) {
		if (not strcmp(argv[i], flag.c_str())) {
			return atoi(argv[i + 1]);
		}
	}
	return 1;
}

int Io::getSolutionId(const int& argc, char** argv) { return getId(argc, argv, "-s"); }
