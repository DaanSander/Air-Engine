#pragma once
#include <glad\glad.h>
#include "../../DataTypes.h"

namespace engine {
	namespace graphics {

		class VertexArray {

		private:
			uint32 m_ID;

		public:
			VertexArray();

			~VertexArray();

			void Bind() const;

			void UnBind() const;

			inline uint32 GetID() const { return m_ID; }
		};
} }