#pragma once

namespace engine {
	namespace math {

		template<typename T>
		struct Vector4 {

			union {

				struct {
					T m_X, m_Y, m_Z, m_W;
				};

				T m_Elements[4];
			};

			Vector4(T x = 0.0f, T y = 0.0f, T z = 0.0f, T w = 0.0f) {
				m_X = x;
				m_Y = y;
				m_Z = z;
				m_W = w;
			}

			Vector4(const Vector4& vector) {
				m_X = vector.m_X;
				m_Y = vector.m_Y;
				m_Z = vector.m_Z;
				m_W = vector.m_W;
			}

			Vector4<T> Reverse() const {
				Vector4<T> out;

				out.m_X = -m_X;
				out.m_Y = -m_Y;
				out.m_Z = -m_Z;
				out.m_W = -m_W;
				return out;
			}

			Vector4<T> Clamp(T min, T max) const {
				Vector4<T> out;

				out.m_X = m_X < min ? min : (m_X > max ? max : m_X);
				out.m_Y = m_Y < min ? min : (m_Y > max ? max : m_Y);
				out.m_Z = m_Z < min ? min : (m_Z > max ? max : m_Z);
				out.m_W = m_W < min ? min : (m_W > max ? max : m_W);
				return out;
			}

			Vector4<T> Add(const Vector4<T>& other) const {
				Vector4<T> out;

				out.m_X = m_X = other.m_X;
				out.m_Y = m_Y = other.m_Y;
				out.m_Z = m_Z = other.m_Z;
				out.m_W = m_W = other.m_W;
				return out;
			}

			Vector4<T> Subtract(const Vector4<T>& other) const {
				return Add(other.Reverse());
			}

			Vector4<T> Multiply(T scalar) const {
				Vector4<T> out;

				out.m_X = m_X * scalar;
				out.m_Y = m_Y * scalar;
				out.m_Z = m_Z * scalar;
				out.m_W = m_W * scalar;
				return out;
			}

			T Dotp(const Vector4<T>& other) const {
				return (m_X * other.m_X) + (m_Y * other.m_Y) + (m_Z * other.m_Z) + (m_W * other.m_W);
			}

			Vector4<T> operator-() const {
				return Reverse();
			}

			friend Vector4<T> operator+(const Vector4<T>& a, const Vector4<T>& b) {
				return a.Add(b);
			}

			friend Vector4<T> operator-(const Vector4<T>& a, const Vector4<T>& b) {
				return a.Subtract(b);
			}

			friend Vector4<T> operator*(const Vector4<T>& vector, T scalar) {
				return vector.Multiply(scalar);
			}
		};
} }