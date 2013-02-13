#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
	int m_rows, m_cols;
	double **m_pElementen;
public:
Matrix(int rows, int cols);
Matrix::Matrix(const Matrix & m);
int getRows() const {return m_rows;}
int getCols() const {return m_cols;}
void allocate(int rows, int cols);
void toon() const;
double getElement(int row, int col) const;
void setElement(int row, int col, double value);
Matrix &operator+=(const Matrix &m);
Matrix &operator-=(const Matrix &m);
Matrix &operator =(const Matrix &m);
Matrix operator +(const Matrix &m);
Matrix operator -(const Matrix &m);
bool operator==(const Matrix &m);
bool operator!=(const Matrix &m);
Matrix &operator*=(const Matrix &m);
Matrix operator*(const Matrix &m);
Matrix operator- (void);
Matrix operator [] (int index);
double kruisproduct(int i, int j, Matrix m1, const Matrix & m2);
};

#endif