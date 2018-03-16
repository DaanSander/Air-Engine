#pragma once
#include <glad\glad.h>

namespace engine {
	namespace graphics {

		enum BufferUsage {
			STATIC = GL_STATIC_DRAW,
			DYNAMIC = GL_DYNAMIC_DRAW
		};

		class VertexBuffer {
			unsigned int m_ID;
			BufferUsage m_Usage;
			unsigned int m_Size;

		public:
			VertexBuffer(BufferUsage usage);
			
			VertexBuffer(BufferUsage usage, const void* data, unsigned int size);

			~VertexBuffer();
			
			void Bind() const;

			void UnBind() const;

			void SetData(const void* data, unsigned int size);

			inline unsigned int GetID() const { return m_ID; }

			inline BufferUsage GetBufferUsage() const { return m_Usage; }

			inline unsigned int GetSize() const { return m_Size; }
		};
} }