
#pragma once
#include <math.h>

namespace engine {
	namespace math {

		template<typename T>
		struct Vector2 {
			union {

				struct {
					T m_X, m_Y;
				};

				T m_Elements[2];
			};

			Vector2(T x = 0, T y = 0) {
				m_X = x;
				m_Y = y;
			}

			Vector2(const Vector2& vector) {
				m_X = vector.m_X;
				m_Y = vector.m_Y;
			}

			T Magnitude() const {
				return sqrt((m_X * m_X) + (m_Y * m_Y));
			}

			Vector2<T> Normalize() const {
				Vector2<T> out;
				T length = Magnitude();
				out.m_X = m_X / length;
				out.m_Y = m_Y / length;

				return out;
			}

			Vector2<T> Clamp(T min, T max) const {
				Vector2<T> out;
				out.m_X = m_X < min ? min : (m_X > max ? max : m_X);
				out.m_Y = m_Y < min ? min : (m_Y > max ? max : m_Y);

				return out;
			}

			Vector2<T> Reverse() const {
				Vector2<T> out;
				out.m_X = -m_X;
				out.m_Y = -m_Y;

				return out;
			}

			Vector2<T> Add(const Vector2<T>& other) const {
				Vector2<T> out;
				out.m_X = m_X + other.m_X;
				out.m_Y = m_Y + other.m_Y;

				return out;
			}

			inline Vector2<T> Subtract(const Vector2<T>& other) const {
				return Add(other.Reverse());
			}

			Vector2<T> Multiply(T scalar) const {
				Vector2<T> out;
				out.m_X = m_X * scalar;
				out.m_Y = m_Y * scalar;

				return out;
			}

			T Dotp(const Vector2<T> other) const {
				return (m_X * other.m_X) + (m_Y * other.m_Y);
			}

			Vector2<T> operator-() const {
				return Reverse();
			}

			friend Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b) {
				return a.Add(b);
			}

			friend Vector2<T> operator*(const Vector2<T>& a, T scalar) {
				return a.Multiply(scalar);
			}

			friend Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b) {
				return a.Subtract(b);
			}

			friend bool operator<(const Vector2<T>& a, const Vector2<T>& b) {
				return a.Magnitude() < b.Magnitude();
			}

			friend bool operator<=(const Vector2<T>& a, const Vector2<T>& b) {
				return a.Magnitude() > b.Magnitude();
			}

			friend bool operator>(const Vector2<T>& a, const Vector2<T>& b) {
				return a.Magnitude() <= b.Magnitude();
			}

			friend bool operator>=(const Vector2<T>& a, const Vector2<T>& b) {
				return a.Magnitude() >= b.Magnitude();
			}
		};
	}
}