#include "nonogram.h"

Nonogram::Nonogram() {
	reset();
}

Nonogram::Nonogram(const char* file_name) {
	setMap(file_name);
}

void Nonogram::setMap(const char* file_name) {
	reset();
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
	for(int i = 0; i < rows; i++) {
		std::vector<int> row(columns, 0);
		matrix.push_back(row);
	}
	input.close();
}

void Nonogram::reset() {
	this->rows = 0;
	this->columns = 0;
	this->rows_values.clear();
	this->cols_values.clear();
	matrix.clear();
}

const int Nonogram::get(const int& type, const int& n) const {
	if(type == ROW) {
		return rows_values[n];
	} else if(type == COL) {
		return cols_values[n];
	}
}

void Nonogram::set(const int& i, const int& j, const bool& value) {
	if(i < rows && j < columns) {
		this->matrix[i][j] = value;
	}
}

const int Nonogram::getRows() const {
	return this->rows;
}

const int Nonogram::getColumns() const {
	return this->columns;
}

const bool Nonogram::isOn(const int& i, const int& j) const {
	if(i < rows && j < columns) {
		return matrix[i][j] == 1;
	}
	throw std::logic_error("Access error: The position doesn't exist");
}

const bool Nonogram::isCorrect() const {
	bool correct = true;
	for(int i = 0; i < rows; i++) {
		int sum = 0;
		for(int j = 0; j < columns; j++) {
			sum += matrix[i][j];
		}
		correct &= sum == rows_values[i];
	}
	for(int j = 0; j < columns; j++) {
		int sum = 0;
		for(int i = 0; i < rows; i++) {
			sum += matrix[i][j];
		}
		correct &= sum == cols_values[j];
	}
	return correct;
}

const bool Nonogram::isCorrect(const int& type, const int& n) const {
	int sum = 0;
	if(type == COL && n < columns) {
		for(int i = 0; i < rows; i++) {
			sum += matrix[i][n];
		}
		return sum == cols_values[n];
	} else if(type == ROW && n < rows) {
		for(int j = 0; j < columns; j++) {
			sum += matrix[n][j];
		}
		return sum == rows_values[n];
	}
	throw std::logic_error("The value of type or n is invalid");
}

std::vector<int>& Nonogram::operator[] (const int& i) {
	return matrix[i];
}
