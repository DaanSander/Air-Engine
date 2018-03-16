#include "Shader.hpp"

namespace engine {
	namespace graphics {

		Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) {
			m_ProgramID = glCreateProgram();

			m_VertexID = CompileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
			m_FragmentID = CompileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

			glAttachShader(m_ProgramID, m_VertexID);
			glAttachShader(m_ProgramID, m_FragmentID);
			
			glLinkProgram(m_ProgramID);
			glValidateProgram(m_ProgramID);

			glDeleteShader(m_VertexID);
			glDeleteShader(m_FragmentID);
		}

		Shader::~Shader() {
			glDeleteProgram(m_ProgramID);
		}


		void Shader::Bind() const {
			glUseProgram(m_ProgramID);
		}

		void Shader::UnBind() const {
			glUseProgram(0);
		}

		int Shader::CompileShader(const char* source, int shaderType) const {
			int shaderID = glCreateShader(shaderType);

			glShaderSource(shaderID, 1, &source, NULL);
			glCompileShader(shaderID);

			int status;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
			if(status == GL_FALSE) {
				int length;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
				
				char* info_log = new char[length + 1];
				
				glGetShaderInfoLog(shaderID, length, &length, info_log);

				printf("An error ocurred whilst compiling a shader error: \n %s", info_log);
				delete[] info_log;
				return 0;
			}

			return shaderID;
		}
} }