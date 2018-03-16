#pragma once
#include <string>
#include <glad\glad.h>
#include <vector>
#include <unordered_map>

namespace engine {
	namespace graphics {

		class Shader {

			unsigned int m_ProgramID, m_VertexID, m_FragmentID;
			std::unordered_map<std::string, unsigned int> m_UniformLocations;

		public:
			Shader(const std::string& vertexSource, const std::string& fragmentSource);

			~Shader();

		private:
			void InitProgram();

		public:
			void Bind() const;

			void UnBind() const;

			inline int GetProgramID() const { return m_ProgramID; }

			inline int GetVertexID() const { return m_VertexID; }

			inline int GetFragmentID() const { return m_FragmentID; }

			inline unsigned int GetUniformLocation(const std::string& name) { 
				return m_UniformLocations[name]; 
			}

		private:
			int CompileShader(const char* source, int shaderType) const;
		};
} }