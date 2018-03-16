#include "VertexArray.hpp"

namespace engine {
	namespace graphics {

		VertexArray::VertexArray() {
			glGenVertexArrays(1, &m_ID);
		}

		VertexArray::~VertexArray() {
			glDeleteVertexArrays(1, &m_ID);
		}

		void VertexArray::Bind() const {
			glBindVertexArray(m_ID);
		}

		void VertexArray::UnBind() const {
			glBindVertexArray(0);
		}
	}
}