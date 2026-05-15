#include "vao.hpp"

#include <cstdint>

#include "vbo.hpp"
#include "ebo.hpp"

VAO::VAO()
{
	glCreateVertexArrays(1, &ID);
}

VAO::~VAO()
{
	Delete();
}

VAO::VAO(VAO&& other) noexcept
	: ID{other.ID}
{
	other.ID = 0;
}

VAO& VAO::operator=(VAO&& other) noexcept
{
	if (this != &other)
	{
		Delete();

		ID = other.ID;
		other.ID = 0;
	}

	return *this;
}

void VAO::LinkAttrib(VBO& vbo, GLuint layout)
{
	constexpr GLsizei stride = 3 * sizeof(GLfloat);

	glEnableVertexArrayAttrib(ID, layout);
	glVertexArrayAttribFormat(ID, layout, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(ID, layout, layout);
	glVertexArrayVertexBuffer(ID, layout, vbo.ID, 0, stride);
}

void VAO::LinkAttrib(
	VBO& vbo,
	GLuint layout,
	GLuint numComponents,
	GLenum type,
	GLsizeiptr stride,
	void* offset
)
{
	const auto relativeOffset =
		static_cast<GLuint>(reinterpret_cast<uintptr_t>(offset));

	glEnableVertexArrayAttrib(ID, layout);
	glVertexArrayAttribFormat(ID, layout, numComponents, type, GL_FALSE, relativeOffset);
	glVertexArrayAttribBinding(ID, layout, layout);

	glVertexArrayVertexBuffer(
		ID,
		layout,
		vbo.ID,
		0,
		static_cast<GLsizei>(stride)
	);
}

void VAO::LinkEBO(EBO& ebo)
{
	glVertexArrayElementBuffer(ID, ebo.ID);
}

void VAO::Bind() const
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete() noexcept
{
	if (ID != 0)
	{
		glDeleteVertexArrays(1, &ID);
		ID = 0;
	}
}