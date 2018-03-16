#pragma once
#include <string>
#include <glad\glad.h>
#include <vector>
#include <unordered_map>
#include "../DataTypes.h"

namespace engine {
	namespace graphics {

		class Shader {

			uint32 m_ProgramID, m_VertexID, m_FragmentID;
			std::unordered_map<std::string, uint32> m_UniformLocations;

		public:
			Shader(const std::string& vertexSource, const std::string& fragmentSource);

			~Shader();

		private:
			void InitProgram();

		public:
			void Bind() const;

			void UnBind() const;

			inline int32 GetProgramID() const { return m_ProgramID; }

			inline int32 GetVertexID() const { return m_VertexID; }

			inline int32 GetFragmentID() const { return m_FragmentID; }

			inline uint32 GetUniformLocation(const std::string& name) { 
				return m_UniformLocations[name]; 
			}

		private:
			int32 CompileShader(const char* source, int32 shaderType) const;
		};
} }