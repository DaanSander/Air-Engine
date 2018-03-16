#pragma once
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Matrix4.hpp"
#include <memory.h>
//TODO Rotation matrix
namespace engine {
	namespace math {

		template<typename T>
		struct Matrix3 {
			union {
				T m_Elements[3 * 3];

				Vector3<T> m_Rows[3];
			};

			Matrix3() {
				memset(m_Elements, (T)0, sizeof(m_Elements));
			}

			Matrix3(const Matrix3<T>& matrix) {
				for (unsigned int i = 0; i < 3 * 3; i++)
					m_Elements[i] = matrix.m_Elements[i];
			}

			Matrix3(T diagonal) {
				memset(m_Elements, (T)0, sizeof(m_Elements));

				for (unsigned int i = 0; i < 3; i++)
					m_Elements(i + i * 3) = diagonal;
			}

			Matrix3(const Matrix4<T>& mat4) {
				for (unsigned int y = 0; y < 3; y++) {
					for (unsigned int x = 0; x < 3; x++) {
						m_Elements[x + y * 3] = mat4.m_Elements[x + y * 4];
					}
				}
			}

			static constexpr Matrix3<T> Identity() {
				return Matrix3<T>((T)1);
			}

			static Matrix3<T> Translation(const Vector2<T>& translation) {
				Matrix3<T> ou = Identity();

				out.m_Elements[0 + 2 * 3] = translation.m_X;
				out.m_Elements[1 + 2 * 3] = translation.m_Y;

				return out;
			}

			static Matrix3<T> Scale(const Vector2<T> scale) {
				Matrix3<T> out = Identity();

				out.m_Elements[0 + 0 * 3] = scale.m_X;
				out.m_Elements[1 + 1 * 3] = scale.m_Y;

				return out;
			}

			Matrix3<T> Transpose() const {
				Matrix3<T> out;

				for (unsigned int y = 0; y < 3; y++) {
					for (unsigned int x = 0; x < 3; x++) {
						out.m_Elements[x + y * 3] = m_Elements[y + x * 3];
					}
				}

				return out;
			}

			Matrix3<T> Negative() const {
				Matrix3<T> out;

				for (unsigned int i = 0; i < 3 * 3; i++)
					out.m_Elements[i] = -m_Elements[i];

				return out;
			}

			T Determinant() const {
				return m_Elements[0 + 0 * 3] * m_Elements[1 + 1 * 3] * m_Elements[2 + 2 * 3] + 
					   m_Elements[0 + 1 * 3] * m_Elements[1 + 2 * 3] * m_Elements[2 + 0 * 3] +

					   m_Elements[0 + 2 * 3] * m_Elements[1 + 0 * 3] * m_Elements[2 + 1 * 3] -
					   m_Elements[0 + 0 * 3] * m_Elements[1 + 2 * 3] * m_Elements[2 + 1 * 3] -
					   m_Elements[0 + 1 * 3] * m_Elements[1 + 0 * 3] * m_Elements[2 + 2 * 3] -
					   m_Elements[0 + 2 * 3] * m_Elements[1 + 1 * 3] * m_Elements[2 + 0 * 3];
			}

			Matrix3<T> Inverse() const {
				Matrix3<T> out;

				T det = Determinant();
				if (det == 0) return nullptr;
				T invDet = (T)1 / det;

				out.m_Elements[0 + 0 * 3] =
					m_Elements[1 + 1 * 3] * m_Elements[2 + 2 * 3] -
					m_Elements[1 + 2 * 3] * m_Elements[2 + 1 * 3];

				out.m_Elements[0 + 1 * 3] =
					m_Elements[0 + 2 * 3] * m_Elements[2 + 1 * 3] -
					m_Elements[0 + 1 * 3] * m_Elements[2 + 2 * 3];

				out.m_Elements[0 + 2 * 3] =
					m_Elements[0 + 1 * 3] * m_Elements[1 + 2 * 3] -
					m_Elements[0 + 2 * 3] * m_Elements[1 + 1 * 3];

				out.m_Elements[1 + 0 * 3] =
					m_Elements[1 + 2 * 3] * m_Elements[2 + 0 * 3] -
					m_Elements[1 + 0 * 3] * m_Elements[2 + 2 * 3];

				out.m_Elements[1 + 1 * 3] =
					m_Elements[0 + 0 * 3] * m_Elements[2 + 2 * 3] -
					m_Elements[0 + 2 * 3] * m_Elements[2 + 0 * 3];

				out.m_Elements[1 + 2 * 3] =
					m_Elements[0 + 2 * 3] * m_Elements[1 + 0 * 3] -
					m_Elements[0 + 0 * 3] * m_Elements[1 + 2 * 3];

				out.m_Elements[2 + 0 * 3] =
					m_Elements[1 + 0 * 3] * m_Elements[2 + 1 * 3] -
					m_Elements[1 + 1 * 3] * m_Elements[2 + 0 * 3];

				out.m_Elements[2 + 1 * 3] =
					m_Elements[0 + 1 * 3] * m_Elements[2 + 0 * 3] -
					m_Elements[0 + 0 * 3] * m_Elements[2 + 1 * 3];

				out.m_Elements[0 + 0 * 3] =
					m_Elements[0 + 0 * 3] * m_Elements[1 + 1 * 3] -
					m_Elements[0 + 1 * 3] * m_Elements[1 + 0 * 3];

				out = out.multiply(invDet);

				return out;
			}

			Matrix3<T> Add(const Matrix3<T>& other) const {
				Matrix3<T> out;

				for (unsigned int i = 0; i < 3 * 3; i++)
					out.m_Elements[i] = m_Elements[i] + other.m_Elements[i];

				return out;
			}

			Matrix3<T> Subtract(const Matrix3<T>& other) const {
				Matrix3<T> out;

				for (unsigned int i = 0; i < 3 * 3; i++)
					out.m_Elements[i] = m_Elements[i] - other.m_Elements[i];

				return out;
			}

			Matrix3<T> Multiply(T scalar) const {
				Matrix3<T> out;

				for (int i = 0; i < (3 * 3); i++)
					out.m_Elements[i] = m_Elements[i] * scalar;

				return out;
			}

			Matrix3<T> Multiply(const Matrix3<T>& other) const {
				Matrix3<T> out;

				for (unsigned int y = 0; y < 3; y++) {
					for (unsigned int x = 0; x < 3; x++) {
						for (unsigned int c = 0; c < 3; c++) {
							out.m_Elements[x + y * 3] += m_Elements[c + y * 4] * other.m_Elements[x + c * 4];
						}
					}
				}

				return out;
			}

			Vector3<T> Multiply(const Vector3<T>& vector) const {
				Vector3<T> out;

				for (unsigned int y = 0; y < 3; y++) {
					for (unsigned int x = 0; x < 3; x++) {
						out.m_Elements[y] = m_Elements[x + y * 3] * vector.m_Elements[x];
					}
				}

				return out;
			}

			Matrix3<T> operator-() const {
				return Negative();
			}

			friend Matrix3<T> operator+(const Matrix3<T>& a, const Matrix3<T>& b) {
				return a.Add(b);
			}

			friend Matrix3<T> operator-(const Matrix3<T>& a, const Matrix3<T>& b) {
				return a.Subtract(b);
			}

			friend Matrix3<T> operator*(const Matrix3<T>& matrix, T scalar) {
				return matrix.Multiply(scalar);
			}

			friend Matrix3<T> operator*(const Matrix3<T>& a, const Matrix3<T>& b) {
				return a.Multiply(b);
			}

			friend Vector4<T> operator*(const Matrix4<T>& matrix, const Vector4<T>& vector) {
				return matrix.Multiply(vector);
			}
		};
} }