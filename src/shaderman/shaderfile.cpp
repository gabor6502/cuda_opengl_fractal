#include <glad.h>
#include "shaderfile.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

ShaderFile::ShaderFile(const char* fname)
	: shader(BAD_SHADER)
{
	shader_source_code = readSourceCode(fname);
}

void ShaderFile::logErrorToConsole(const GLchar* message) const
{
	if (message != nullptr && shader == BAD_SHADER)
	{
		printf("%s\n", message);
	}
}

GLchar* ShaderFile::readSourceCode(const char * fname)
{
	GLchar* buffered_read;
	long content_size;

	assert(fname != nullptr);
	if (fname == nullptr)
	{
		error_log = "No shader source code file name provided";
		return nullptr;
	}

	FILE* file_in = fopen(fname, "rb"); // open as readable binary file
	
    assert(file_in != NULL);
	if (file_in == NULL)
	{
		error_log = "File could not be opened or was not found";
		return nullptr;
	}

	// size
	fseek(file_in, 0L, SEEK_END); // go all the way to the end
	content_size = ftell(file_in); // current position of file pointer within the stream, at the END of the file, is the size
	buffered_read = new GLchar[content_size + 1]; // +1 for adding null termination

	// content
	fseek(file_in, 0L, SEEK_SET); // rewind

	fread(buffered_read, 1, content_size, file_in); // read all bytes in
	buffered_read[content_size] = '\0';

	// release and return
	error_log = nullptr;
	fclose(file_in);
	return buffered_read;
}

void ShaderFile::init()
{
	assert(shader_source_code != nullptr);
	if (shader_source_code == nullptr)
	{
		return;
	}

	GLint compiled;

	int error_log_index;
	
	// create reference to a shader object, set source code, and compile
	shader = glCreateShader(getShaderType());
	glShaderSource(shader, 1, &shader_source_code, NULL);
	glCompileShader(shader);

	// check status of compilation
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		glGetShaderInfoLog(shader, MAX_SHAD_ERROR_LOG, NULL, &shader_error_log);
		
		// just print it while we're here (avoid variable stack corruption issue)

		error_log_index = 0;
		printf("\n");
		while ((& shader_error_log)[error_log_index] != '\0')
		{
			printf("%c", (&shader_error_log)[++error_log_index]);
		}

		shader = BAD_SHADER;
	}

	delete[] shader_source_code; // we don't need it anymore
}

ShaderFile::~ShaderFile()
{
	if (error_log != nullptr && shader == BAD_SHADER)
	{
		delete[] error_log;
	}
}


// ** subclass methods **

ComputeShader* ComputeShader::create(const char* fname)
{
	if (fname == nullptr)
	{
		return nullptr;
	}
	else
	{
		return new ComputeShader(fname);
	}
}

inline
void ComputeShader::printErrorLog() const
{
	printf("COMPUTE SHADER\n");
	logErrorToConsole(error_log);
}

VertexShader* VertexShader::create(const char* fname)
{
	if (fname == nullptr)
	{
		return nullptr;
	}
	else
	{
		return new VertexShader(fname);
	}
}

inline
void VertexShader::printErrorLog() const
{
	printf("VERTEX SHADER\n");
	logErrorToConsole(error_log);
}

TessControlShader* TessControlShader::create(const char* fname)
{
	if (fname == nullptr)
	{
		return nullptr;
	}
	else
	{
		return new TessControlShader(fname);
	}
}

inline
void TessControlShader::printErrorLog() const
{
	printf("TESS CONTROL SHADER\n");
	logErrorToConsole(error_log);
}

TessEvaluationShader* TessEvaluationShader::create(const char* fname)
{
	if (fname == nullptr)
	{
		return nullptr;
	}
	else
	{
		return new TessEvaluationShader(fname);
	}
}

inline
void TessEvaluationShader::printErrorLog() const
{
	printf("TESS EVALUATION SHADER\n");
	logErrorToConsole(error_log);
}

GeometryShader* GeometryShader::create(const char* fname)
{
	if (fname == nullptr)
	{
		return nullptr;
	}
	else
	{
		return new GeometryShader(fname);
	}
}

inline
void GeometryShader::printErrorLog() const
{
	printf("GEOMETRY SHADER\n");
	logErrorToConsole(error_log);
}

FragmentShader* FragmentShader::create(const char* fname)
{
	if (fname == nullptr)
	{
		return nullptr;
	}
	else
	{
		return new FragmentShader(fname);
	}
}

inline
void FragmentShader::printErrorLog() const
{
	printf("FRAGMENT SHADER\n");
	logErrorToConsole(error_log);
}
