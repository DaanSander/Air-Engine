#pragma once
#include "Vector2.hpp"
#include "Matrix3.hpp"

namespace engine {
	namespace math {

		template<typename T>
		struct Matrix2 {
			union {
				T m_Elements[2 * 2];

				Vector2<T> m_Rows[2];
			};

			Matrix2() {
				memset(m_Elements, (T)0, sizeof(m_Elements));
			}

			Matrix2(const Matrix2<T>& matrix) {
				for (unsigned int i = 0; i < 4 * 4; i++)
					m_Elements[i] = matrix.m_Elements[i];
			}

			Matrix2(T diagonal) {
				memset(m_Elements, (T)0, sizeof(m_Elements));

				for (int i = 0; i < 2; i++)
					m_Elements[i + i * 2] = diagonal;
			}

			Matrix2(const Matrix3<T>& mat3) {
				m_Elements[0 + 0 * 2] = mat3.m_Elements[0 + 0 * 3];
				m_Elements[0 + 1 * 2] = mat3.m_Elements[0 + 1 * 3];

				m_Elements[1 + 0 * 2] = mat3.m_Elements[1 + 0 * 3];
				m_Elements[1 + 1 * 2] = mat3.m_Elements[1 + 1 * 3];
			}

			//Matrix2(T elements[2 * 2]) {
			//	m_Elements = elements;
			//}

			static constexpr Matrix2<T> Identity() {
				return Matrix2<T>((T)1);
			}

			Matrix2<T> Transpose() const {
				Matrix2<T> out;

				for (unsigned int y = 0; y < 2; y++) {
					for (unsigned int x = 0; x < 2; x++) {
						out.m_Elements[x + y * 2] = m_Elements[y + x * 2];
					}
				}

				return out;
			}

			Matrix2<T> Negative() const {
				Matrix2<T> out;

				for (unsigned int i = 0; i < 2 * 2; i++)
					out.m_Elements[i] = -m_Elements[i];

				return out;
			}

			T Determinant() const {
				return (m_Elements[0 + 0 * 2] * m_Elements[1 + 1 * 2]) - (m_Elements[1 + 0 * 2] * m_Elements[0 + 1 * 2]);
			}

			Matrix2<T> Inverse() const {
				Matrix2<T> out;

				T det = Determinant();
				if (det == 0) return Identity();

				out.m_Elements[0 + 0 * 2] =  m_Elements[1 + 1 * 2] / det;
				out.m_Elements[0 + 1 * 2] = -m_Elements[1 + 0 * 2] / det;
				out.m_Elements[1 + 0 * 2] = -m_Elements[0 + 1 * 2] / det;
				out.m_Elements[1 + 1 * 2] =  m_Elements[0 + 0 * 2] / det;
				//TODO test this
				return out;
			}

			Matrix2<T> Add(const Matrix2<T>& other) const {
				Matrix2<T> out;

				for (unsigned int i = 0; i < 2 * 2; i++)
					out.m_Elements[i] = m_Elements[i] + other.m_Elements[i];

				return out;
			}

			Matrix2<T> Subtract(const Matrix2<T>& other) const {
				Matrix2<T> out;

				for (unsigned int i = 0; i < 2 * 2; i++)
					out.m_Elements[i] = m_Elements[i] - other.m_Elements[i];

				return out;
			}

			Matrix2<T> Multiply(T scalar) const {
				Matrix2<T> out;

				for (int i = 0; i < (3 * 3); i++)
					out.m_Elements[i] = m_Elements[i] * scalar;

				return out;
			}

			Matrix2<T> Multiply(const Matrix2<T>& other) const {
				Matrix2<T> out;

				for (unsigned int y = 0; y < 2; y++) {
					for (unsigned int x = 0; x < 2; x++) {
						for (unsigned int c = 0; c < 2; c++) {
							out.m_Elements[x + y * 2] += m_Elements[c + y * 2] * other.m_Elements[x + c * 2];
						}
					}
				}

				return out;
			}

			Vector3<T> Multiply(const Vector2<T>& vector) const {
				Vector3<T> out;

				for (unsigned int y = 0; y < 2; y++) {
					for (unsigned int x = 0; x < 2; x++) {
						out.m_Elements[y] = m_Elements[x + y * 2] * vector.m_Elements[x];
					}
				}

				return out;
			}

			Matrix2<T> operator-() const {
				return Negative();
			}

			friend Matrix2<T> operator+(const Matrix2<T>& a, const Matrix2<T>& b) {
				return a.Add(b);
			}

			friend Matrix2<T> operator-(const Matrix2<T>& a, const Matrix2<T>& b) {
				return a.Subtract(b);
			}

			friend Matrix2<T> operator*(const Matrix2<T>& matrix, T scalar) {
				return matrix.Multiply(scalar);
			}

			friend Matrix2<T> operator*(const Matrix2<T>& a, const Matrix2<T>& b) {
				return a.Multiply(b);
			}

			friend Vector2<T> operator*(const Matrix2<T>& matrix, const Vector2<T>& vector) {
				return matrix.Multiply(vector);
			}
		};
} }