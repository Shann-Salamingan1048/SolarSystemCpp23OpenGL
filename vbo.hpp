#pragma once

#include <glad/glad.h>

class VBO
{
public:
	GLuint ID{0};

public:
	VBO() = default;

	VBO(GLfloat* vertices, GLsizeiptr size);
	VBO(const GLfloat* vertices, GLsizeiptr size);

	~VBO();

	VBO(const VBO&) = delete;
	VBO& operator=(const VBO&) = delete;

	VBO(VBO&& other) noexcept;
	VBO& operator=(VBO&& other) noexcept;

	void SetData(const GLfloat* vertices, GLsizeiptr size);

	void Bind() const;
	static void Unbind();

	void Delete() noexcept;
};