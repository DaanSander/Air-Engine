#include "ElementBuffer.hpp"

namespace engine {
	namespace graphics {

		ElementBuffer::ElementBuffer(BufferUsage usage) {
			m_Usage = usage;
			glGenBuffers(1, &m_ID);
		}

		ElementBuffer::~ElementBuffer() {
			glDeleteBuffers(1, &m_ID);
		}

		void ElementBuffer::Bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		}

		void ElementBuffer::UnBind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void ElementBuffer::SetData(const void* data, uint32 size) {
			Bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, m_Usage);
		}
} }