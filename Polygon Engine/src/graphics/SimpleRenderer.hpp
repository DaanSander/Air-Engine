#pragma once

#include "buffers\VertexArray.hpp"

namespace engine {
	namespace graphics {

		class SimpleRenderer {

			SimpleRenderer();

			void Prepare() const;

			void Render(const VertexArray& vertexArray) const;
		};
} }