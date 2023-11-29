#include "Matrix.h"

Matrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
Matrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}

Matrix::IntMatrix(const Matrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns), rows(new IntArray *[rhs.numRows]) {
  for (int m = 0; m < rhs.numRows; m++) {
    rows[m] = new IntArray(rhs.numColumns);
  }
  for (int i = 0; i < rhs.getRows(); i++) {
    for (int j = 0; j < rhs.getColumns(); j++) {
      (*this)[i][j] = rhs[i][j];
    }
  }
}

Matrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

Matrix & Matrix::operator=(const Matrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray(rhs[i]);
    }
    for (int j = 0; j < numRows; j++) {
      delete rows[j];
    }
    delete[] rows;
    numColumns = rhs.numColumns;
    numRows = rhs.numRows;
    rows = temp;
  }
  return *this;
}

int Matrix::getRows() const {
  return numRows;
}

int Matrix::getColumns() const {
  return numColumns;
}

const T & Matrix::operator[](int index) const {
  assert(index >= 0 && index <= numRows - 1);
  return *rows[index];
}

T & IntMatrix::operator[](int index) {
  assert(index < numRows && index >= 0);
  return *rows[index];
}

bool Matrix::operator==(const Matrix & rhs) const {
  if (numColumns != rhs.numColumns) {
    return false;
  }
  if (numRows != rhs.numRows) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    if ((*this)[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numColumns == rhs.numColumns);
  assert(numRows == rhs.numRows);
  IntMatrix ans(numRows, numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      ans[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }
  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i < rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
