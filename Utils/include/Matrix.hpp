#pragma once 

#include <iostream>
#include <cmath>
#include <array>
#include <string>

#define vector_function template <typename test = std::enable_if<nRows == 1 || nCols == 1>::type>
#define vector3_function template <typename test = std::enable_if<(nRows == 1 && nCols == 3) || (nRows == 3 && nCols == 1)>::type>

#define matrix_function template <typename test = std::enable_if<nRows == nCols && (nRows > 1)>::type>

template <typename ValueType, size_t nRows, size_t nCols>
class Matrix : public std::array<ValueType, nRows * nCols> {
public:
	matrix_function static void identity(Matrix<ValueType, nRows, nCols> &matrix) {
		for (size_t i = 0; i < matrix.size(); i++)
			matrix[i] = 0;

		for (size_t i = 0; i < matrix.size(); i += nCols + 1)
			matrix[i] = 1;
	}

	static void add(const Matrix<ValueType, nRows, nCols>& matrix1, const Matrix<ValueType, nRows, nCols>& matrix2, Matrix<ValueType, nRows, nCols>& result) {
		for (size_t i = 0; i < matrix1.size(); i++)
			result._Elems[i] = matrix1._Elems[i] + matrix2._Elems[i];
	}

	static void subtract(const Matrix<ValueType, nRows, nCols>& matrix1, const Matrix<ValueType, nRows, nCols>& matrix2, Matrix<ValueType, nRows, nCols>& result) {
		for (size_t i = 0; i < matrix1.size(); i++)
			result._Elems[i] = matrix1._Elems[i] - matrix2._Elems[i];
	}

	static void scale(const Matrix<ValueType, nRows, nCols>& matrix, const ValueType& scalar, Matrix<ValueType, nRows, nCols>& result) {
		for (size_t i = 0; i < matrix.size(); i++)
			result._Elems[i] = matrix._Elems[i] * scalar;
	}

	template <size_t otherCols>
	static void multiply(const Matrix<ValueType, nRows, nCols>& leftMatrix, const Matrix<ValueType, nCols, otherCols>& rightMatrix, Matrix<ValueType, nRows, otherCols>& result) {
		size_t resultIndex = 0;
		for (size_t rowStartIndex = 0; rowStartIndex < leftMatrix.size(); rowStartIndex+=nCols) {
			for (size_t colStartIndex = 0; colStartIndex < otherCols; colStartIndex++) {
				ValueType sum = 0;
				size_t rightIndex = colStartIndex;
				for (size_t leftIndex = 0; leftIndex < nCols; leftIndex++) {
					sum += leftMatrix[leftIndex + rowStartIndex] * rightMatrix[rightIndex];
					rightIndex += otherCols;
				}
				result[resultIndex] = sum;
				resultIndex++;
			}
		}
	}

	static void transpose(const Matrix<ValueType, nRows, nCols>& matrix, Matrix<ValueType, nCols, nRows>& result) {
		size_t resultIndex = 0;
		for (size_t colStartIndex = 0; colStartIndex < nCols; colStartIndex++) {
			for (size_t index = colStartIndex; index < matrix.size(); index += nCols) {
				result[resultIndex] = matrix[index];
				resultIndex++;
			}
		}
	}

	vector_function static ValueType magnitude(const Matrix<ValueType, nRows, nCols>& vector) {
		ValueType sum = 0;

		for (auto& v : vector)
			sum += v * v;

		return sqrt(sum);
	}

	vector_function static void normalize(const Matrix<ValueType, nRows, nCols>& vector, Matrix<ValueType, nRows, nCols>& output) {
		ValueType length = magnitude(vector);

		for (size_t i = 0; i < vector.size(); i++)
			output[i] = vector[i] / length;
	}

	vector3_function static void cross(const Matrix<ValueType, nRows, nCols>& vector1, const Matrix<ValueType, nRows, nCols>& vector2, const Matrix<ValueType, nRows, nCols>& output) {
		output[0] = (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
		output[1] = (vector1[2] * vector2[0]) - (vector1[0] * vector2[2]);
		output[2] = (vector1[0] * vector2[1]) - (vector1[1] * vector2[0]);
	}

	void add(const Matrix<ValueType, nRows, nCols>& toAdd) { add(*this, toAdd, *this); }
	void subtract(const Matrix<ValueType, nRows, nCols>& toSubtract) { subtract(*this, toSubtract, *this); }
	void scale(const ValueType& scalar) { scale(*this, scalar, *this); }

	template <size_t otherCols>
	Matrix<ValueType, nRows, otherCols> multiply(const Matrix <ValueType, nCols, otherCols>& rightMatrix) { 
		Matrix<ValueType, nRows, otherCols> toRet;
		multiply(*this, rightMatrix, toRet);
		return toRet;
	}

	matrix_function void identity() {
		identity(*this);
	}

	vector_function ValueType magnitude() const {
		return magitude(*this);
	}

	vector_function void normalize() {
		normalize(*this, *this);
	}

	vector_function void normalize(Matrix<ValueType, nRows, nCols>& output) const {
		normalize(*this, output);
	}

	vector3_function Matrix<ValueType, nRows, nCols> cross(const Matrix<ValueType, nRows, nCols> &vector2) const {
		Matrix<ValueType, nRows, nCols> output;
		cross(*this, vector2, output);

		return output;
	}

	Matrix<ValueType, nRows, nCols> operator+(const Matrix<ValueType, nRows, nCols>& toAdd) const {
		Matrix<ValueType, nRows, nCols> toRet;
		add(*this, toAdd, toRet);
		return toRet;
	}

	Matrix<ValueType, nRows, nCols> operator-(const Matrix<ValueType, nRows, nCols>& toSubtract) const {
		Matrix<ValueType, nRows, nCols> toRet;
		subtract(*this, toSubtract, toRet);
		return toRet;
	}

	Matrix<ValueType, nRows, nCols> operator*(const ValueType& scalar) const {
		Matrix<ValueType, nRows, nCols> toRet;
		scale(*this, scalar, toRet);
		return toRet;
	}

	template <size_t otherCols>
	Matrix<ValueType, nRows, otherCols> operator*(const Matrix<ValueType, nCols, otherCols>& rightMatrix) const {
		Matrix<ValueType, nRows, otherCols> toRet;
		multiply(*this, rightMatrix, toRet);
		return toRet;
	}

	void operator+=(const Matrix<ValueType, nRows, nCols>& toAdd) { add(*this, toAdd, *this); }
	void operator-=(const Matrix<ValueType, nRows, nCols>& toAdd) { subtract(*this, toAdd, *this); }
	void operator*=(const ValueType& scalar) { scale(*this, scalar, *this); }

	void print(const std::string &name) {
		if (nRows > 1) {
			if (name != "")
				std::cout << name << " : {" << std::endl;
			else
				std::cout << "{" << std::endl;
		}

		size_t index = 0;
		std::string indentString = nRows > 1 ? "   " : (name == "" ? "" : name + " : ");
		for (size_t row = 0; row < nRows; row++) {
			std::cout << indentString << "{ ";
			for (size_t col = 0; col < nCols; col++) {
				if (col == nCols - 1)
					std::cout << at(index) << " ";
				else
					std::cout << at(index) << ", ";
				index++;
			}
			std::cout << "}" << std::endl;
		}

		if (nRows > 1)
			std::cout << "}" << std::endl;
	}

	void print() { print(""); }
};

typedef Matrix<float, 4, 4> Mat4f;
typedef Matrix<float, 3, 3> Mat3f;

typedef Matrix<float, 1, 4> VecRow4f;
typedef Matrix<float, 1, 3> VecRow3f;
typedef Matrix<float, 1, 2> VecRow2f;

typedef Matrix<float, 4, 1> VecCol4f;
typedef Matrix<float, 3, 1> VecCol3f;
typedef Matrix<float, 2, 1> VecCol2f;

typedef VecCol3f Vec3f;