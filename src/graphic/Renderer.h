#pragma once

class Shader;
class Mesh;
class Transform;
class Camera;

class Renderer {
public:
	void draw(Shader& shader, const Mesh& mesh, const Transform& transform, const Camera& camera) const;
};