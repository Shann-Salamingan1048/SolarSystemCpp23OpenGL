#include "vbo.hpp"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	SetData(vertices, size);
}

VBO::VBO(const GLfloat* vertices, GLsizeiptr size)
{
	SetData(vertices, size);
}

VBO::~VBO()
{
	Delete();
}

VBO::VBO(VBO&& other) noexcept
	: ID{other.ID}
{
	other.ID = 0;
}

VBO& VBO::operator=(VBO&& other) noexcept
{
	if (this != &other)
	{
		Delete();

		ID = other.ID;
		other.ID = 0;
	}

	return *this;
}

void VBO::SetData(const GLfloat* vertices, GLsizeiptr size)
{
	if (ID == 0)
	{
		glCreateBuffers(1, &ID);
	}

	glNamedBufferData(ID, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() noexcept
{
	if (ID != 0)
	{
		glDeleteBuffers(1, &ID);
		ID = 0;
	}
}