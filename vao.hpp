#pragma once

#include <glad/glad.h>

class VBO;
class EBO;

class VAO
{
public:
	GLuint ID{0};

public:
	VAO();
	~VAO();

	VAO(const VAO&) = delete;
	VAO& operator=(const VAO&) = delete;

	VAO(VAO&& other) noexcept;
	VAO& operator=(VAO&& other) noexcept;

	void LinkAttrib(
		VBO& vbo,
		GLuint layout
	);

	void LinkAttrib(
		VBO& vbo,
		GLuint layout,
		GLuint numComponents,
		GLenum type,
		GLsizeiptr stride,
		void* offset
	);

	void LinkEBO(EBO& ebo);

	void Bind() const;
	static void Unbind();

	void Delete() noexcept;
};