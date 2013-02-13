#include "Matrix.h"
#include <iostream>
using std::cout;


Matrix::Matrix(int rows, int cols) 
{
	if(rows == 0 && cols == 0)
	{
		//error
	}

	if(rows < 0 || cols < 0)
	{
		//error
	}
		
	allocate(rows, cols);
}

void Matrix::allocate(int rows, int cols)
{
	m_rows = rows;
	m_cols = cols;

	
	
	m_pElementen = new double*[rows];
	
	for(int i=0; i<rows; i++)
	{
		m_pElementen[i] = new double[cols];
	}
}

void Matrix::toon() const
{
	for(int i=0; i<m_rows; i++)
	{
		//cout<<"[";
		for(int j=0; j<m_cols; j++)
		{
			//cout<<m_pElementen[i][j]<< " ";
		}
		//cout<<"]\n";
	}
}

double Matrix::getElement(int row, int col) const 
{
	if(row >= m_rows || col >= m_cols)
	{
		//error
	}
	return m_pElementen[row][col];
}

Matrix::Matrix(const Matrix & m)
{
	//cout<<"\ncopy constructor\n";
	
	allocate(m.getRows(), m.getCols());
	for(int i=0; i<m_rows; i++)
	{
		for(int j=0; j<m_cols; j++)
		{
			m_pElementen[i][j] = m.getElement(i, j);
		}
	}
}

void Matrix::setElement(int row, int col, double value)
{
	if(row >= m_rows || col >= m_cols)
	{
		//error
	}
	m_pElementen[row][col] = value;
}

Matrix & Matrix::operator +=(const Matrix &m)
{
	if(this->getRows() != m.getRows() || this->getCols() != m.getCols())
	{
		//error
	}
	for(int i=0; i<m_rows; i++)
	{
		for(int j=0; j<m_cols; j++)
		{
			m_pElementen[i][j] += m.getElement(i, j);
		}
	}
	return *this;
}

Matrix & Matrix::operator -=(const Matrix &m)
{
	if(this->getRows() != m.getRows() || this->getCols() != m.getCols())
	{
		//error
	}
	for(int i=0; i<m_rows; i++)
	{
		for(int j=0; j<m_cols; j++)
		{
			m_pElementen[i][j] -= m.getElement(i, j);
		}
	}
	return *this;
}

Matrix & Matrix::operator =(const Matrix &m)
{
	return Matrix(m);
}

Matrix Matrix::operator +(const Matrix & m)
{
	if(this->getRows() != m.getRows() || this->getCols() != m.getCols())
	{
		//error
	}
	Matrix hulp = m;
	hulp += *this;
	return hulp;
}

Matrix Matrix::operator -(const Matrix & m)
{
	if(this->getRows() != m.getRows() || this->getCols() != m.getCols())
	{
		//error
	}
	Matrix hulp = m;
	hulp -= *this;
	return hulp;
}

bool Matrix::operator ==(const Matrix &m)
{
	bool isEqual = true;
	for(int i=0; i<m_rows && isEqual; i++)
	{
		for(int j=0; j<m_cols && isEqual; j++)
		{
			isEqual = m_pElementen[i][j] == m.getElement(i, j);
		}
	}
	return isEqual;
}

bool Matrix::operator != (const Matrix &m)
{
	return !(*this == m);
}

Matrix Matrix::operator- (void)
{
	for(int i=0; i<m_rows; i++)
	{
		for(int j=0; j<m_cols; j++)
		{
			m_pElementen[i][j] = 0 - m_pElementen[i][j];
		}
	}
	return *this;
}



double Matrix::kruisproduct(int i, int j, Matrix m1, const Matrix & m2)
{
	double result = 0.0;
	for(int t=0; t<m1.getRows(); t++)
	{
		double elem1 = m1.m_pElementen[i][t];
		double elem2 = m2.getElement(t, j);
		result += elem1 * elem2;
	}
	
	return result;
}


Matrix & Matrix::operator*= (const Matrix & m)
{
	if(this->getCols() != m.getRows() || this->getRows() != m.getCols())
	{
		//error
	}
	Matrix product(m_rows, m.getCols());
	Matrix hulp(*this);
	//cout<<"hulp:\n";
	hulp.toon();
	//cout<<"m param:\n";
	m.toon();

	this->allocate(m_rows, m.getCols());
	
	for(int i=0; i<product.getRows(); i++)
	{
		for(int j=0; j<product.getCols(); j++)
		{
			this->setElement(i, j, kruisproduct(i, j, hulp, m));
		}
	}
	
	return *this;
}

Matrix Matrix::operator* (const Matrix & m)
{
	if(this->getCols() != m.getRows() || this->getRows() != m.getCols())
	{
		//error
	}
	Matrix hulp(*this);
	hulp *= m;
	return hulp;
}

Matrix Matrix::operator [] (int index)
{
	Matrix m(1, this->getCols());
	for(int i=0; i<m_cols; i++)
		m.setElement(0, i, getElement(index, i));
	return m;
}
