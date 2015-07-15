#pragma once

#include <sparky_types.h>

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"

#include "renderer2d.h"
#include "texture.h"

#include "../maths/maths.h"
#include "shaders/shader.h"

namespace sparky { namespace graphics {

	struct VertexData
	{
		maths::vec3 vertex;
		maths::vec2 uv;
		maths::vec2 mask_uv;
		float tid;
		float mid;
		unsigned int color;
	};

#define RENDERER_VERTEX_SIZE	sizeof(VertexData)

	class Renderable2D
	{
	protected:
		maths::vec3 m_Position;
		maths::vec2 m_Size;
		unsigned int m_Color;
		std::vector<maths::vec2> m_UV;
		Texture* m_Texture;
	protected:
		Renderable2D() : m_Texture(nullptr) { setUVDefaults(); }
	public:
		Renderable2D(maths::vec3 position, maths::vec2 size, unsigned int color)
			: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr)
		{ setUVDefaults(); }

		virtual ~Renderable2D() { }

		virtual void submit(Renderer2D* renderer) const
		{
			renderer->submit(this);
		}

		void setColor(unsigned int color) { m_Color = color; }
		void setColor(const maths::vec4& color)
		{ 
			uint r = (uint)(color.x * 255.0f);
			uint g = (uint)(color.y * 255.0f);
			uint b = (uint)(color.z * 255.0f);
			uint a = (uint)(color.w * 255.0f);

			m_Color = a << 24 | b << 16 | g << 8 | r;
		}

		inline const maths::vec3& getPosition() const { return m_Position; }
		inline const maths::vec2& getSize() const { return m_Size; }
		inline const unsigned int getColor() const { return m_Color; }
		inline const std::vector<maths::vec2>& getUV() const { return m_UV; }

		inline const GLuint getTID() const { return m_Texture ? m_Texture->getID() : 0; }
		inline const Texture* getTexture() const { return m_Texture; }
	private:
		void setUVDefaults()
		{
			m_UV.push_back(maths::vec2(0, 0));
			m_UV.push_back(maths::vec2(0, 1));
			m_UV.push_back(maths::vec2(1, 1));
			m_UV.push_back(maths::vec2(1, 0));
		}
	};

} }