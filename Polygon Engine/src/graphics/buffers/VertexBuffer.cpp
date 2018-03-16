#include "VertexBuffer.hpp"

namespace engine {
	namespace graphics {

		VertexBuffer::VertexBuffer(BufferUsage usage) {
			m_Usage = usage;
			glGenBuffers(1, &m_ID);
		}

		VertexBuffer::VertexBuffer(BufferUsage usage, const void* data, uint32 size) {
			m_Usage = usage;

			glGenBuffers(1, &m_ID);
			SetData(data, size);
		}

		VertexBuffer::~VertexBuffer() {
			glDeleteBuffers(1, &m_ID);
		}

		void VertexBuffer::Bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		}

		void VertexBuffer::UnBind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void VertexBuffer::SetData(const void* data, uint32 size) {
			Bind();
			glBufferData(GL_ARRAY_BUFFER, size, data, m_Usage);
		}
} }