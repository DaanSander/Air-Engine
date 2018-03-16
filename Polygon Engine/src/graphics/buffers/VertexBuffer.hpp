#pragma once
#include <glad\glad.h>
#include "../../DataTypes.h"

namespace engine {
	namespace graphics {

		enum BufferUsage {
			STATIC = GL_STATIC_DRAW,
			DYNAMIC = GL_DYNAMIC_DRAW
		};

		class VertexBuffer {
			uint32 m_ID;
			BufferUsage m_Usage;
			uint32 m_Size;

		public:
			VertexBuffer(BufferUsage usage);
			
			VertexBuffer(BufferUsage usage, const void* data, uint32 size);

			~VertexBuffer();
			
			void Bind() const;

			void UnBind() const;

			void SetData(const void* data, uint32 size);

			inline uint32 GetID() const { return m_ID; }

			inline BufferUsage GetBufferUsage() const { return m_Usage; }

			inline uint32 GetSize() const { return m_Size; }
		};
} }