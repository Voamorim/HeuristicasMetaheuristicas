#include "build_csv.hpp"

CsvBuilder::CsvBuilder(const string& _csv_file, const vector<string>& labels)
	: csv_file(_csv_file) {
	addLabels(labels);
}

CsvBuilder::~CsvBuilder() {}

void CsvBuilder::addLabels(const vector<string>& labels) {
	for (int i = 0; i < labels.size(); ++i) {
		csv_file << labels[i];

		// Separador
		if (i < labels.size() - 1) {
			csv_file << ',';
		}
	}
	csv_file << endl;
}

void CsvBuilder::addLine(const vector<double>& values) {
	for (int i = 0; i < values.size(); ++i) {
		const double value = values[i];

		long long int_part = value;
		double frac_part = value - int_part;

		if (frac_part >= 0.001) {
			csv_file << fixed << setprecision(3) << value;
		} else {
			csv_file << int_part;
		}

		// Separador
		if (i < values.size() - 1) {
			csv_file << ',';
		}
	}
	csv_file << endl;
}
