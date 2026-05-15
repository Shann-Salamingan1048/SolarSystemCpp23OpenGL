#pragma once

#include <glad/glad.h>

class EBO
{
public:
	GLuint ID{0};

public:
	EBO() = default;

	EBO(GLuint* indices, GLsizeiptr size);
	EBO(const GLuint* indices, GLsizeiptr size);

	~EBO();

	EBO(const EBO&) = delete;
	EBO& operator=(const EBO&) = delete;

	EBO(EBO&& other) noexcept;
	EBO& operator=(EBO&& other) noexcept;

	void SetData(const GLuint* indices, GLsizeiptr size);

	void Bind() const;
	static void Unbind();

	void Delete() noexcept;
};