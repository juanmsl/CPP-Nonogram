#include "nonogram.h"

Nonogram::Nonogram() {
	this->rows = 0;
	this->columns = 0;
	this->tot_rows = 0;
	this->tot_cols = 0;
	this->rows_values.clear();
	this->cols_values.clear();
	matrix.clear();
}

void Nonogram::setMap(const char* file_name) {
	std::ifstream input(file_name);
	int rc, cc, value;
	input >> rows >> columns;
	for(int i = 0; i < rows; i++) {
		input >> rc;
		std::deque<int> aux;
		for(int j = 0; j < rc; j++) {
			input >> value;
			aux.push_front(value);
		}
		if(aux.size() > tot_cols) {
			tot_cols = aux.size();
		}
		rows_values.push_back(aux);
	}

	for(int j = 0; j < columns; j++) {
		input >> cc;
		std::deque<int> aux;
		for(int i = 0; i < cc; i++) {
			input >> value;
			aux.push_front(value);
		}
		if(aux.size() > tot_rows) {
			tot_rows = aux.size();
		}
		cols_values.push_back(aux);
	}
	tot_cols += columns;
	tot_rows += rows;
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

const std::deque<int> Nonogram::get(const int& type, const int& n) const {
	if(type == ROW) {
		return rows_values[n];
	} else if(type == COL) {
		return cols_values[n];
	}
}

const int Nonogram::getRows() const {
	return this->rows;
}

const int Nonogram::getTotalRows() const {
	return this->tot_rows;
}

const int Nonogram::getColumns() const {
	return this->columns;
}

const int Nonogram::getTotalColumns() const {
	return this->tot_cols;
}

const bool Nonogram::isOn(const int& i, const int& j) const {
	std::map<int, int> column = matrix.find(i)->second;
	return (column.find(j)->second == 1);
}
