#include "ebo.hpp"

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	SetData(indices, size);
}

EBO::EBO(const GLuint* indices, GLsizeiptr size)
{
	SetData(indices, size);
}

EBO::~EBO()
{
	Delete();
}

EBO::EBO(EBO&& other) noexcept
	: ID{other.ID}
{
	other.ID = 0;
}

EBO& EBO::operator=(EBO&& other) noexcept
{
	if (this != &other)
	{
		Delete();

		ID = other.ID;
		other.ID = 0;
	}

	return *this;
}

void EBO::SetData(const GLuint* indices, GLsizeiptr size)
{
	if (ID == 0)
	{
		glCreateBuffers(1, &ID);
	}

	glNamedBufferData(ID, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() noexcept
{
	if (ID != 0)
	{
		glDeleteBuffers(1, &ID);
		ID = 0;
	}
}