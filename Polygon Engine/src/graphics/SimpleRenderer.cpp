#include "SimpleRenderer.hpp"

namespace engine {
	namespace graphics {

		SimpleRenderer::SimpleRenderer() {
			glClearColor(1.0f, 0.4f, 0.6f, 1.0f);
		}

		void SimpleRenderer::Prepare() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void SimpleRenderer::Render(const VertexArray& vertexArray) const {
			vertexArray.Bind();

			

			vertexArray.UnBind();
		}
} }