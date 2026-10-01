#ifndef BUILD_CSV_HPP
#define BUILD_CSV_HPP

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CsvBuilder {
   public:
	ofstream csv_file;

	void addLine(const vector<double>& values);

	CsvBuilder(const string& _csv_file, const vector<string>& labels);
	~CsvBuilder();

   private:
	void addLabels(const vector<string>& labels);
};

#endif
