#include "Matrix.h"

class Singleton
{
public:
	static Singleton& getInstance()
	{
		static Singleton instance;

		return instance;

	}
	float fastSin(float angle);
	float fastCos(float angle);
	float fastSin(int angle);
	float fastCos(int angle);
	int index(int row, int col, int width);
	float *multiplyMatrices(float *mat1, float *mat2, int r1, int c1, int r2, int c2);
	

	Matrix rotateAboutAxis(Matrix *vector, int angle, char axis);

private:
	void loadMatrix(char axis, int angle);


	float cos_lut[360];
	float sin_lut[360];
	Matrix *rotationMatrix;
	Singleton();
};