#pragma once

#include <iostream>
#include <vector>

#include <sparkygl.h>

#include "../../maths/maths.h"
#include "../../utils/fileutils.h"

namespace sparky { namespace graphics {

#define SHADER_VERTEX_INDEX		0
#define SHADER_UV_INDEX			1
#define SHADER_MASK_UV_INDEX	2
#define SHADER_TID_INDEX		3
#define SHADER_MID_INDEX		4
#define SHADER_COLOR_INDEX		5

	class Shader
	{
	private:
		const char* m_Name;
		const char* m_VertPath;
		const char* m_FragPath;
		const char* m_VertSrc;
		const char* m_FragSrc;
	public:
		GLuint m_ShaderID;
		Shader(const char* name, const char* vertSrc, const char* fragSrc);
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void setUniform1f(const GLchar* name, float value);
		void setUniform1fv(const GLchar* name, float* value, int count);
		void setUniform1i(const GLchar* name, int value);
		void setUniform1iv(const GLchar* name, int* value, int count);
		void setUniform2f(const GLchar* name, const maths::vec2& vector);
		void setUniform3f(const GLchar* name, const maths::vec3& vector);
		void setUniform4f(const GLchar* name, const maths::vec4& vector);
		void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

		void enable() const;
		void disable() const;
	private:
		GLuint load(const char* vertSrc, const char* fragSrc);
		GLint getUniformLocation(const GLchar* name);
	public:
		static Shader* FromFile(const char* vertPath, const char* fragPath);
		static Shader* FromSource(const char* vertSrc, const char* fragSrc);
		static Shader* FromSource(const char* name, const char* vertSrc, const char* fragSrc);
	};

} }