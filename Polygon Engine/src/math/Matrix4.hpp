#pragma once
#include <iostream>
#include "Vector4.hpp"
#include "Vector3.hpp"

//TODO Add transpose function
///Default OpenGL is column major
///[x, x, x, x]
///[y, y, y, y]
///[z, z, z, z]
///[w, w, w, w]
///Axis angle rotation: http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToMatrix/index.htm
///Define TRANSPOSED to change it to row major
///#define TRANSPOSED

namespace engine {
	namespace math {

		template<typename T>
		struct Matrix4 {

			union {

				struct {
					T m_Elements[4 * 4];
				};

				Vector4<T> m_Rows[4];
			};

			Matrix4() {
				memset(m_Elements, 0, sizeof(m_Elements));
			}

			Matrix4(const Matrix4<T>& matrix) {
				for (int i = 0; i < 4 * 4; i++)
					m_Elements[i] = matrix.m_Elements[i];
			}

			Matrix4(T diagonal) {
				memset(m_Elements, 0, sizeof(m_Elements));

				for (int i = 0; i < 4; i++)
					m_Elements[i + i * 4] = diagonal;
			}

			static constexpr Matrix4<T> Identity() {
				return Matrix4((T)1);
			}

#ifdef TRANSPOSED
			static Matrix4<T> translation(T x, T y, T z) {
				Matrix4<T> out = Matrix4<T>::identity();

				out.m_Elements[3 + 0 * 4] = x;
				out.m_Elements[3 + 1 * 4] = y;
				out.m_Elements[3 + 2 * 4] = z;
				return out;
			}
#else
			static Matrix4<T> Translation(const Vector3<T>& translation) {
				Matrix4<T> out = Matrix4<T>::Identity();

				out.m_Elements[0 + 3 * 4] = translation.m_X;
				out.m_Elements[1 + 3 * 4] = translation.m_Y;
				out.m_Elements[2 + 3 * 4] = translation.m_Z;

				return out;
			}
#endif

			static Matrix4<T> Scale(const Vector3<T>& scale) {
				Matrix4<T> out = Matrix4<T>::Identity();

				out.m_Elements[0 + 0 * 4] = scale.m_X;
				out.m_Elements[1 + 1 * 4] = scale.m_Y;
				out.m_Elements[2 + 2 * 4] = scale.m_Z;
				return out;
			}

			//ANGLE IN RADIANS
			static Matrix4<T> Rotation(const Vector3<T>& axis, T angle) {
				Matrix4<T> out;

				T c = cos(angle);
				T s = sin(angle);
				T omc = 1 - c;

				Vector3<T> norm = axis.Normalize();
				T x = norm.m_X;
				T y = norm.m_Y;
				T z = norm.m_Z;

				out.m_Elements[0 + 0 * 4] = omc * x * x + c;
				out.m_Elements[1 + 0 * 4] = omc * x * y - z * s;
				out.m_Elements[2 + 0 * 4] = omc * x * z + y * s;

				out.m_Elements[0 + 1 * 4] = omc * x * y + z * s;
				out.m_Elements[1 + 1 * 4] = omc * y * y + c;
				out.m_Elements[2 + 1 * 4] = omc * y * z - x * s;

				out.m_Elements[0 + 2 * 4] = omc * x * z - y * s;
				out.m_Elements[1 + 2 * 4] = omc * y * z + x * s;
				out.m_Elements[2 + 2 * 4] = omc * z * z + c;
				return out;
			}

			//RADIANS
			static Matrix4<T> Euler_Angles(const Vector3<T>& angles) {
				Vector3<T> x = Vector3<T>(1, 0, 0);
				Vector3<T> y = Vector3<T>(0, 1, 0);
				Vector3<T> z = Vector3<T>(0, 0, 1);

				return (rotation(x, angles.m_X).rotation(y, angles.m_Y)).multiply(rotation(z, angles.m_Z));
			}

			T Determinant() const {
				return
					m_Elements[0 + 3 * 4] * m_Elements[1 + 2 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 2 * 4] * m_Elements[1 + 3 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 3 * 4] * m_Elements[1 + 1 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 0 * 4] +
					m_Elements[0 + 1 * 4] * m_Elements[1 + 3 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 0 * 4] +
					m_Elements[0 + 2 * 4] * m_Elements[1 + 1 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 1 * 4] * m_Elements[1 + 2 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 3 * 4] * m_Elements[1 + 2 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 1 * 4] +
					m_Elements[0 + 2 * 4] * m_Elements[1 + 3 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 1 * 4] +
					m_Elements[0 + 3 * 4] * m_Elements[1 + 0 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 1 * 4] -
					m_Elements[0 + 0 * 4] * m_Elements[1 + 3 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 1 * 4] - 
					m_Elements[0 + 2 * 4] * m_Elements[1 + 0 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 1 * 4] + 
					m_Elements[0 + 0 * 4] * m_Elements[1 + 2 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 1 * 4] +					
					m_Elements[0 + 3 * 4] * m_Elements[1 + 1 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 2 * 4] -
					m_Elements[0 + 1 * 4] * m_Elements[1 + 3 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 2 * 4] -
					m_Elements[0 + 3 * 4] * m_Elements[1 + 0 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 2 * 4] +
					m_Elements[0 + 0 * 4] * m_Elements[1 + 3 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 2 * 4] +					
					m_Elements[0 + 1 * 4] * m_Elements[1 + 0 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 2 * 4] -
					m_Elements[0 + 0 * 4] * m_Elements[1 + 1 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 2 * 4] -
					m_Elements[0 + 2 * 4] * m_Elements[1 + 1 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 3 * 4] +
					m_Elements[0 + 1 * 4] * m_Elements[1 + 2 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 3 * 4] +					
					m_Elements[0 + 2 * 4] * m_Elements[1 + 0 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 3 * 4] -
					m_Elements[0 + 0 * 4] * m_Elements[1 + 2 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 3 * 4] -
					m_Elements[0 + 1 * 4] * m_Elements[1 + 0 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 3 * 4] +
					m_Elements[0 + 0 * 4] * m_Elements[1 + 1 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 3 * 4];
			}

			Matrix4<T> Inverse() const {
				Matrix4<T> out;

				T det = Determinant();
				if (det == 0) return Identity();
				T invDet = (T)1 / det;

				out.m_Elements[0 + 0 * 4] =
					m_Elements[1 + 2 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 1 * 4] -
					m_Elements[1 + 3 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 1 * 4] +
					m_Elements[1 + 3 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 2 * 4] -
					m_Elements[1 + 1 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 2 * 4] -
					m_Elements[1 + 2 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 3 * 4] +
					m_Elements[1 + 1 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 3 * 4];

				out.m_Elements[0 + 1 * 4] =
					m_Elements[0 + 3 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 1 * 4] -
					m_Elements[0 + 2 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 1 * 4] -
					m_Elements[0 + 3 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 2 * 4] +
					m_Elements[0 + 1 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 2 * 4] +
					m_Elements[0 + 2 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 3 * 4] -
					m_Elements[0 + 1 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 3 * 4];

				out.m_Elements[0 + 2 * 4] =
					m_Elements[0 + 2 * 4] * m_Elements[1 + 3 * 4] * m_Elements[3 + 1 * 4] -
					m_Elements[0 + 3 * 4] * m_Elements[1 + 2 * 4] * m_Elements[3 + 1 * 4] +
					m_Elements[0 + 3 * 4] * m_Elements[1 + 1 * 4] * m_Elements[3 + 2 * 4] -
					m_Elements[0 + 1 * 4] * m_Elements[1 + 3 * 4] * m_Elements[3 + 2 * 4] -
					m_Elements[0 + 2 * 4] * m_Elements[1 + 1 * 4] * m_Elements[3 + 3 * 4] +
					m_Elements[0 + 1 * 4] * m_Elements[1 + 2 * 4] * m_Elements[3 + 3 * 4];

				out.m_Elements[0 + 3 * 4] =
					m_Elements[0 + 3 * 4] * m_Elements[1 + 2 * 4] * m_Elements[2 + 1 * 4] -
					m_Elements[0 + 2 * 4] * m_Elements[1 + 3 * 4] * m_Elements[2 + 1 * 4] -
					m_Elements[0 + 3 * 4] * m_Elements[1 + 1 * 4] * m_Elements[2 + 2 * 4] +
					m_Elements[0 + 1 * 4] * m_Elements[1 + 3 * 4] * m_Elements[2 + 2 * 4] +
					m_Elements[0 + 2 * 4] * m_Elements[1 + 1 * 4] * m_Elements[2 + 3 * 4] -
					m_Elements[0 + 1 * 4] * m_Elements[1 + 2 * 4] * m_Elements[2 + 3 * 4];

				out.m_Elements[1 + 0 * 4] =
					m_Elements[1 + 3 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[1 + 2 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[1 + 3 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 2 * 4] +
					m_Elements[1 + 0 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 2 * 4] +
					m_Elements[1 + 2 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 3 * 4] -
					m_Elements[1 + 0 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 3 * 4];

				out.m_Elements[1 + 1 * 4] =
					m_Elements[0 + 2 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 3 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 0 * 4] +
					m_Elements[0 + 3 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 2 * 4] -
					m_Elements[0 + 0 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 2 * 4] -
					m_Elements[0 + 2 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 3 * 4] +
					m_Elements[0 + 0 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 3 * 4];

				out.m_Elements[1 + 2 * 4] =
					m_Elements[0 + 3 * 4] * m_Elements[1 + 2 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 2 * 4] * m_Elements[1 + 3 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 3 * 4] * m_Elements[1 + 0 * 4] * m_Elements[3 + 2 * 4] +
					m_Elements[0 + 0 * 4] * m_Elements[1 + 3 * 4] * m_Elements[3 + 2 * 4] +
					m_Elements[0 + 2 * 4] * m_Elements[1 + 0 * 4] * m_Elements[3 + 3 * 4] -
					m_Elements[0 + 0 * 4] * m_Elements[1 + 2 * 4] * m_Elements[3 + 3 * 4];

				out.m_Elements[1 + 3 * 4] =
					m_Elements[0 + 2 * 4] * m_Elements[1 + 3 * 4] * m_Elements[2 + 0 * 4] -
					m_Elements[0 + 3 * 4] * m_Elements[1 + 2 * 4] * m_Elements[2 + 0 * 4] +
					m_Elements[0 + 3 * 4] * m_Elements[1 + 0 * 4] * m_Elements[2 + 2 * 4] -
					m_Elements[0 + 0 * 4] * m_Elements[1 + 3 * 4] * m_Elements[2 + 2 * 4] -
					m_Elements[0 + 2 * 4] * m_Elements[1 + 0 * 4] * m_Elements[2 + 3 * 4] +
					m_Elements[0 + 0 * 4] * m_Elements[1 + 2 * 4] * m_Elements[2 + 3 * 4];

				out.m_Elements[2 + 0 * 4] =
					m_Elements[1 + 1 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[1 + 3 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 0 * 4] +
					m_Elements[1 + 3 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 1 * 4] -
					m_Elements[1 + 0 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 1 * 4] -
					m_Elements[1 + 1 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 3 * 4] +
					m_Elements[1 + 0 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 3 * 4];

				out.m_Elements[2 + 1 * 4] =
					m_Elements[0 + 3 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 1 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 3 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 1 * 4] +
					m_Elements[0 + 0 * 4] * m_Elements[2 + 3 * 4] * m_Elements[3 + 1 * 4] +
					m_Elements[0 + 1 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 3 * 4] -
					m_Elements[0 + 0 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 3 * 4];

				out.m_Elements[2 + 2 * 4] =
					m_Elements[0 + 1 * 4] * m_Elements[1 + 3 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 3 * 4] * m_Elements[1 + 1 * 4] * m_Elements[3 + 0 * 4] +
					m_Elements[0 + 3 * 4] * m_Elements[1 + 0 * 4] * m_Elements[3 + 1 * 4] -
					m_Elements[0 + 0 * 4] * m_Elements[1 + 3 * 4] * m_Elements[3 + 1 * 4] -
					m_Elements[0 + 1 * 4] * m_Elements[1 + 0 * 4] * m_Elements[3 + 3 * 4] +
					m_Elements[0 + 0 * 4] * m_Elements[1 + 1 * 4] * m_Elements[3 + 3 * 4];

				out.m_Elements[2 + 3 * 4] =
					m_Elements[0 + 3 * 4] * m_Elements[1 + 1 * 4] * m_Elements[2 + 0 * 4] -
					m_Elements[0 + 1 * 4] * m_Elements[1 + 3 * 4] * m_Elements[2 + 0 * 4] -
					m_Elements[0 + 3 * 4] * m_Elements[1 + 0 * 4] * m_Elements[2 + 1 * 4] +
					m_Elements[0 + 0 * 4] * m_Elements[1 + 3 * 4] * m_Elements[2 + 1 * 4] +
					m_Elements[0 + 1 * 4] * m_Elements[1 + 0 * 4] * m_Elements[2 + 3 * 4] -
					m_Elements[0 + 0 * 4] * m_Elements[1 + 1 * 4] * m_Elements[2 + 3 * 4];

				out.m_Elements[3 + 0 * 4] =
					m_Elements[1 + 2 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[1 + 1 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[1 + 2 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 1 * 4] +
					m_Elements[1 + 0 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 1 * 4] +
					m_Elements[1 + 1 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 2 * 4] -
					m_Elements[1 + 0 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 2 * 4];

				out.m_Elements[3 + 1 * 4] =
					m_Elements[0 + 1 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 2 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 0 * 4] +
					m_Elements[0 + 2 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 1 * 4] -
					m_Elements[0 + 0 * 4] * m_Elements[2 + 2 * 4] * m_Elements[3 + 1 * 4] -
					m_Elements[0 + 1 * 4] * m_Elements[2 + 0 * 4] * m_Elements[3 + 2 * 4] +
					m_Elements[0 + 0 * 4] * m_Elements[2 + 1 * 4] * m_Elements[3 + 2 * 4];

				out.m_Elements[3 + 2 * 4] =
					m_Elements[0 + 2 * 4] * m_Elements[1 + 1 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 1 * 4] * m_Elements[1 + 2 * 4] * m_Elements[3 + 0 * 4] -
					m_Elements[0 + 2 * 4] * m_Elements[1 + 0 * 4] * m_Elements[3 + 1 * 4] +
					m_Elements[0 + 0 * 4] * m_Elements[1 + 2 * 4] * m_Elements[3 + 1 * 4] +
					m_Elements[0 + 1 * 4] * m_Elements[1 + 0 * 4] * m_Elements[3 + 2 * 4] -
					m_Elements[0 + 0 * 4] * m_Elements[1 + 1 * 4] * m_Elements[3 + 2 * 4];

				out.m_Elements[3 + 3 * 4] =
					m_Elements[0 + 1 * 4] * m_Elements[1 + 2 * 4] * m_Elements[2 + 0 * 4] -
					m_Elements[0 + 2 * 4] * m_Elements[1 + 1 * 4] * m_Elements[2 + 0 * 4] +
					m_Elements[0 + 2 * 4] * m_Elements[1 + 0 * 4] * m_Elements[2 + 1 * 4] -
					m_Elements[0 + 0 * 4] * m_Elements[1 + 2 * 4] * m_Elements[2 + 1 * 4] -
					m_Elements[0 + 1 * 4] * m_Elements[1 + 0 * 4] * m_Elements[2 + 2 * 4] +
					m_Elements[0 + 0 * 4] * m_Elements[1 + 1 * 4] * m_Elements[2 + 2 * 4];

				out = out.Multiply(invDet);
				return out;
			}

			Matrix4<T> Transpose() const {
				Matrix4<T> out;

				for (unsigned int y = 0; y < 4; y++) {
					for (unsigned int x = 0; x < 4; x++) {
						out.m_Elements[y + x * 4] = out.m_Elements[x + y * 4];
					}
				}

				return out;
			}

			Matrix4<T> Negative() const {
				Matrix4<T> out;

				for (unsigned int i = 0; i < 4 * 4; i++)
					out.m_Elements[i] = -m_Elements[i];

				return out;
			}

			Matrix4<T> Add(const Matrix4<T>& other) const {
				Matrix4<T> out;

				for (unsigned int i = 0; i < 4 * 4; i++)
					out.m_Elements[i] = m_Elements[i] + other.m_Elements[i];

				return out;
			}

			Matrix4<T> Subtract(const Matrix4<T>& other) const {
				Matrix4<T> out;

				for (unsigned int i = 0; i < 4 * 4; i++)
					out.m_Elements[i] = m_Elements[i] - other.m_Elements[i];

				return out;
			}

			Matrix4<T> Multiply(T scalar) const {
				Matrix4<T> out;

				for (unsigned int i = 0; i < (4 * 4); i++)
					out.m_Elements[i] = m_Elements[i] * scalar;

				return out;
			}

			Matrix4<T> Multiply(const Matrix4<T>& other) const {
				Matrix4<T> out;

				for (unsigned int y = 0; y < 4; y++) {
					for (unsigned int x = 0; x < 4; x++) {
						for (unsigned int c = 0; c < 4; c++) {
							out.m_Elements[x + y * 4] += m_Elements[c + y * 4] * other.m_Elements[x + c * 4];
						}
					}
				}
				return out;
			}

			Vector4<T> Multiply(const Vector4<T>& vector) const {
				Vector4<T> out;

				for (unsigned int y = 0; y < 4; y++) {
					for (unsigned int x = 0; x < 4; x++) {
						out.m_Elements[y] += m_Elements[x + y * 4] * vector.m_Elements[x];
					}
				}

				return out;
			}

			Matrix4<T> operator-() const {
				return Negative();
			}

			friend Matrix4<T> operator+(const Matrix4<T>& a, const Matrix4<T>& b) {
				return a.Add(b);
			}

			friend Matrix4<T> operator-(const Matrix4<T>& a, const Matrix4<T>& b) {
				return a.Subtract(b);
			}

			friend Matrix4<T> operator*(const Matrix4<T>& matrix, T scalar) {
				return matrix.Multiply(scalar);
			}

			friend Matrix4<T> operator*(const Matrix4<T>& a, const Matrix4<T>& b) {
				return a.Multiply(b);
			}

			friend Vector4<T> operator*(const Matrix4<T>& matrix, const Vector4<T>& vector) {
				return matrix.Multiply(vector);
			}
		};
	}
}