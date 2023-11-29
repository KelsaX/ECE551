#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows() {}

  Matrix(int r, int c) : numRows(r), numColumns(c), rows(r, std::vector<T>(c)) {
    // for (int i = 0; i < numRows; i++) {
    //  rows[i] = new std::vector<T>(numColumns);
    //}
  }

  Matrix(const Matrix<T> & rhs) :
      numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {
    //  for (int m = 0; m < rhs.numRows; m++) {
    // rows[m] = new IntArray(rhs.numColumns);
    //}
    //  for (int i = 0; i < rhs.getRows(); i++) {
    // for (int j = 0; j < rhs.getColumns(); j++) {
    //  (*this)[i][j] = rhs[i][j];
    // }
    // }
  }
  ~Matrix() {
    // for (int i = 0; i < numRows; i++) {
    //  delete rows[i];
    // }
    //  delete[] rows;
  }

  Matrix<T> & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      //  std::vector<std::vector<T> > temp;
      //      for (int i = 0; i < rhs.numRows; i++) {
      // temp[i] = new IntArray(rhs[i]);
      // }
      // for
      //  for (int j = 0; j < numRows; j++) {
      // delete rows[j];
      //  }
      // delete[] rows;
      // numColumns = rhs.numColumns;
      //  numRows = rhs.numRows;
      // rows = temp;
      // }
      rows = rhs.rows;
    }
    return *this;
  }

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index <= numRows - 1);
    return rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert(index < numRows && index >= 0);
    return rows[index];
  }

  bool operator==(const Matrix<T> & rhs) const {
    //  if (numColumns != rhs.numColumns) {
    //  return false;
    // }
    // if (numRows != rhs.numRows) {
    //  return false;
    // }
    // for (int i = 0; i < numRows; i++) {
    //  if ((*this)[i] != rhs[i]) {
    // return false;
    // }
    //}
    if (rows == rhs.rows) {
      return true;
    }
    return false;
  }

  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(numColumns == rhs.numColumns);
    assert(numRows == rhs.numRows);
    Matrix ans(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ans[i][j] = (*this)[i][j] + rhs[i][j];
      }
    }
    return ans;
  }
};
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << "{";
    for (int j = 0; j < rhs.getColumns(); j++) {
      s << rhs[i][j];
      if (j < rhs.getColumns() - 1) {
        s << ", ";
      }
    }
    // s << rhs[i];
    s << "}";
    if (i < rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}

#endif
