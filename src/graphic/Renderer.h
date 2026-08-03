#pragma once

struct GLFWwindow;
class Shader;
class Mesh;
class Transform;
class Camera;

class Renderer {
public:
	Renderer();
	void Init(GLFWwindow* window);
	void draw(Shader& shader, const Mesh& mesh, const Transform& transform, const Camera& camera);
	void cleanup();
private:
	float sunAngle;
	int viewSamples;
	int lightSamples;
};