#pragma once
#include <vector>

#define MAX_SHADERS 6

class ShaderFile;

class Shaderman // Shader manager
{
private:
	std::vector<ShaderFile *> shaders;
	GLuint program;

public:
	Shaderman();
	~Shaderman() {};

	bool initShaders();
	inline GLuint getProgram() { return program; }

	void setComputeShader(const char *com_shad);
	void setVertexShader(const char *vert_shad);
	void setTessControlShader(const char *tes_ctrl_shad);
	void setTessEvaluationShader(const char *tes_eval_shad);
	void setGeometryShader(const char *geom_shad);
	void setFragmentShader(const char *frag_shad);
};
