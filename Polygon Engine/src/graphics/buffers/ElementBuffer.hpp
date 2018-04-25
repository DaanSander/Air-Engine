#pragma once
#include <glad\glad.h>
#include "../../DataTypes.h"
#include "VertexBuffer.hpp"

namespace engine {
	namespace graphics {

		class ElementBuffer {

			uint32 m_ID;
			BufferUsage m_Usage;

			ElementBuffer(BufferUsage usage);

			~ElementBuffer();

			void Bind() const;

			void UnBind() const;

			void SetData(const void* data, uint32 size);

			inline BufferUsage GetBufferUsage() const { m_Usage; }

			inline uint32 GetID() const { return m_ID; }
		};	

} }