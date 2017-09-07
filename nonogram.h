#ifndef __NONOGRAM_H__
#define __NONOGRAM_H__
#define COL 1
#define ROW 2

#include <iostream>
#include <fstream>
#include <deque>
#include <map>

class Nonogram {

	protected:
		int rows;
		int columns;
		int tot_rows;
		int tot_cols;
		std::deque<std::deque<int>> rows_values;
		std::deque<std::deque<int>> cols_values;
		std::map<int, std::map<int, int>> matrix;

	public:
		Nonogram();
		Nonogram(const char* file_name);
		void setMap(const char* file_name);
		void print();
		void reset();
		const std::deque<int> get(const int& type, const int& n) const;
		void set(const int& i, const int& j, const bool& value);
		const int getRows() const;
		const int getTotalRows() const;
		const int getColumns() const;
		const int getTotalColumns() const;
		const bool isOn(const int& i, const int& j) const;
};

#endif
