#include "nonogram.h"

Nonogram::Nonogram() {
	this->rows = 0;
	this->columns = 0;
	this->rows_values.clear();
	this->cols_values.clear();
	matrix.clear();
}

void Nonogram::setMap(const char* file_name) {
	std::ifstream input(file_name);
	int value;
	input >> rows >> columns;
	for(int i = 0; i < rows; i++) {
		input >> value;
		rows_values.push_back(value);
	}
	for(int j = 0; j < columns; j++) {
		input >> value;
		cols_values.push_back(value);
	}
	input.close();
}

void Nonogram::print() {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < columns; j++) {
			if(matrix[i][j] == 0) {
				std::cout << "  ";
			} else {
				std::cout << matrix[i][j] << " ";
			}
		}
		std::cout << "\n";
	}
}

const int Nonogram::get(const int& type, const int& n) const {
	if(type == ROW) {
		return rows_values[n];
	} else if(type == COL) {
		return cols_values[n];
	}
}

const int Nonogram::getRows() const {
	return this->rows;
}

const int Nonogram::getColumns() const {
	return this->columns;
}

const bool Nonogram::isOn(const int& i, const int& j) const {
	std::map<int, std::map<int, int>>::const_iterator column_map = matrix.find(i);
	if(column_map != matrix.end()) {
		std::map<int, int> column = column_map->second;
		std::map<int, int>::const_iterator row_map = column.find(j);
		if(row_map != column.end()) {
			return row_map->second == 1;
		}
	}
	return 0;
}
