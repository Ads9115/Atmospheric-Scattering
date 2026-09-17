#pragma once


#include<glad/gl.h>
#include<cstddef>


class Mesh {
public:
	Mesh(const float* vertices, size_t vertexSize, const unsigned int* indices, size_t indexSize);
	~Mesh();

	void draw() const;

private:
	GLuint VAO, VBO, EBO;
	GLsizei indexCount;


};
