#pragma once
#include <glad\glad.h>

namespace engine {
	namespace graphics {

		enum class BufferUsage {
			STATIC = GL_STATIC_DRAW,
			DYNAMIC = GL_DYNAMIC_DRAW
		};

		class VertexBuffer {
			unsigned int m_ID;
			BufferUsage m_BufferUsage;
			unsigned int m_Size;

		public:
			~VertexBuffer();
			
			void SetData(const void* data, unsigned int size);

			void Bind() const;

			void UnBind() const;

			inline unsigned int GetID() const { return m_ID; }

			inline BufferUsage GetBufferUsage() const { return m_BufferUsage; }

			inline unsigned int GetSize() const { return m_Size; }
		};
} }