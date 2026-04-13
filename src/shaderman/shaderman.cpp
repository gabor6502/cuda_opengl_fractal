#include <glad.h>
#include "shaderfile.h"
#include "shaderman.h"

Shaderman::Shaderman(): program(BAD_SHADER)
{
	/* do nothing */
}

bool Shaderman::initShaders()
{
	std::vector<ShaderFile*>::iterator current;
	ShaderFile* shad_file;
	
	GLint linked;
	char link_error_log[MAX_SHAD_ERROR_LOG];

	program = glCreateProgram();

	// init all
	for (current = shaders.begin(); current != shaders.end(); ++current)
	{
		shad_file = (*current);

		shad_file->init();
		if (shad_file->hasErrors())
		{
			shad_file->printErrorLog(); // print errors and get out of here
			return false;
		}
		
		glAttachShader(program, shad_file->getShaderProgram()); // add the individual shaders to the whole program
	}

	// link whole program together and check
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		glGetProgramInfoLog(program, MAX_SHAD_ERROR_LOG, NULL, link_error_log);
		return false;
	}

	// clear list of shaders and delete them, they're all in the program now
	while (!shaders.empty())
	{
		shad_file = shaders.back();

		glDeleteShader(shad_file->getShaderProgram());
		delete shad_file;

		shaders.pop_back();
	}

	return true;
}

void Shaderman::setComputeShader(const char * com_shad)
{
	shaders.push_back(ComputeShader::create(com_shad));
}
void Shaderman::setVertexShader(const char * vert_shad)
{
	shaders.push_back(VertexShader::create(vert_shad));
}
void Shaderman::setTessControlShader(const char * tes_ctrl_shad)
{
	shaders.push_back(TessControlShader::create(tes_ctrl_shad));
}
void Shaderman::setTessEvaluationShader(const char * tes_eval_shad)
{
	shaders.push_back(TessEvaluationShader::create(tes_eval_shad));
}
void Shaderman::setGeometryShader(const char * geom_shad)
{
	shaders.push_back(GeometryShader::create(geom_shad));
}
void Shaderman::setFragmentShader(const char * frag_shad)
{
	shaders.push_back(FragmentShader::create(frag_shad));
}
