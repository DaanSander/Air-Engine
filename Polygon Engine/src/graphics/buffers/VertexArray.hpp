#pragma once
#include <glad\glad.h>

namespace engine {
	namespace graphics {

		class VertexArray {

		private:
			unsigned int m_ID;

		public:
			VertexArray();

			~VertexArray();

			void Bind() const;

			void UnBind() const;

			inline unsigned int GetID() const { return m_ID; }
		};
} }