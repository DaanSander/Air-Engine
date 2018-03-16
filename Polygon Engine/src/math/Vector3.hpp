#pragma once

namespace engine {
	namespace math {

		template<typename T>
		struct Vector3 {

			union {
				struct {
					T m_X, m_Y, m_Z;
				};

				T m_Elements[3];
			};

			Vector3(T x = 0, T y = 0, T z = 0) {
				m_X = x;
				m_Y = y;
				m_Z = z;
			}

			Vector3(const Vector3<T>& vector) {
				m_X = vector.m_X;
				m_Y = vector.m_Y;
				m_Z = vector.m_Z;
			}

			T Magnitude() const {
				return sqrt((m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z));
			}

			Vector3<T> Normalize() const {
				Vector3<T> out;

				T length = Magnitude();

				out.m_X = m_X / length;
				out.m_Y = m_Y / length;
				out.m_Z = m_Z / length;

				return out;
			}

			Vector3<T> Clamp(T min, T max) const {
				Vector3<T> out;

				out.m_X = m_X < min ? min : (m_X > max ? max : m_X);
				out.m_Y = m_Y < min ? min : (m_Y > max ? max : m_Y);
				out.m_Z = m_Z < min ? min : (m_Z > max ? max : m_Z);

				return out;
			}

			Vector3<T> Reverse() const {
				Vector3<T> out;

				out.m_X = -m_X;
				out.m_Y = -m_Y;
				out.m_Z = -m_Z;

				return out;
			}

			Vector3<T> Add(const Vector3<T>& other) const {
				Vector3<T> out;

				out.m_X = m_X + other.m_X;
				out.m_Y = m_Y + other.m_Y;
				out.m_Z = m_Z + other.m_Z;
				return out;
			}

			Vector3<T> Subtract(const Vector3<T>& other) const {
				return Add(other.Reverse());
			}

			Vector3<T> Multiply(T scalar) const {
				Vector3<T> out;

				out.m_X = m_X * scalar;
				out.m_Y = m_Y * scalar;
				out.m_Z = m_Z * scalar;
				return out;
			}

			T Dotp(const Vector3<T>& other) const {
				return (m_X * other.m_X) + (m_Y * other.m_Y) + (m_Z * other.m_Z);
			}

			Vector3<T> Crossp(const Vector3<T>& other) const {
				Vector3<T> out;

				out.m_X = (m_Y * other.m_Z) - (m_Z * other.m_Y);
				out.m_X = (m_Z * other.m_X) - (m_X * other.m_Z);
				out.m_X = (m_X * other.m_Y) - (m_Y * other.m_X);
				return out;
			}


			Vector3<T> operator-() const {
				return Reverse();
			}

			friend Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b) {
				return a.Add(b);
			}

			friend Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b) {
				return a.Subtract(b);
			}

			friend Vector3<T> operator*(const Vector3<T>& vector, T scalar) {
				return vector.Multiply(scalar);
			}

			friend bool operator<(const Vector3<T>& a, const Vector3<T>& b) {
				return a.Magnitude() < b;
			}

			friend bool operator<=(const Vector3<T>& a, const Vector3<T>& b) {
				return a.magnitude <= b;
			}

			friend bool operator>(const Vector3<T>& a, const Vector3<T>& b) {
				return a.Magnitude() > b;
			}

			friend bool operator>=(const Vector3<T>& a, const Vector3<T>& b) {
				return a.Magnitude() >= b;
			}
		};
	}
}