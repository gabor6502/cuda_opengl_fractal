#pragma once

// maximum log size in bytes
#define MAX_SHAD_ERROR_LOG 1024
#define BAD_SHADER -1

// holds data needed on a shader file, reads code, compiles and links
class ShaderFile 
{
private:
	GLchar* shader_source_code;
	GLuint shader; // reference to the created shader

	GLchar* readSourceCode(const char * fname);
	
protected:
	const GLchar* error_log;
	GLchar shader_error_log;

	ShaderFile(const char* fname); // I want control over what is returned depending on file name

	void logErrorToConsole(const GLchar * message) const;

public:
	virtual ~ShaderFile();
	
	void init();
	inline GLuint getShaderProgram() const { return shader; };
	inline bool hasErrors() const { return shader == BAD_SHADER; };

	virtual void printErrorLog() const = 0;
	virtual GLenum getShaderType() const = 0;
};

// implementations

class ComputeShader : public ShaderFile
{
private:
	ComputeShader(const char* fname) : ShaderFile(fname) {};

public:
	static ComputeShader* create(const char* fname);
	~ComputeShader() {};

	virtual void printErrorLog() const;
	inline virtual GLenum getShaderType() const { return GL_COMPUTE_SHADER; }
};

class VertexShader : public ShaderFile
{
private:
	VertexShader(const char* fname) : ShaderFile(fname) {};

public:
	static VertexShader* create(const char* fname);
	~VertexShader() {};

	virtual void printErrorLog() const;
	inline virtual GLenum getShaderType() const { return GL_VERTEX_SHADER; }
};

class TessControlShader : public ShaderFile
{
private:
	TessControlShader(const char* fname) : ShaderFile(fname) {};

public:
	static TessControlShader* create(const char* fname);
	~TessControlShader() {};

	virtual void printErrorLog() const;
	inline virtual GLenum getShaderType() const { return GL_TESS_CONTROL_SHADER; }
};

class TessEvaluationShader : public ShaderFile
{
private:
	TessEvaluationShader(const char* fname) : ShaderFile(fname) {};

public:
	static TessEvaluationShader* create(const char* fname);
	~TessEvaluationShader() {};

	virtual void printErrorLog() const;
	inline virtual GLenum getShaderType() const { return GL_TESS_EVALUATION_SHADER; }
};

class GeometryShader : public ShaderFile
{
private:
	GeometryShader(const char* fname) : ShaderFile(fname) {};

public:
	static GeometryShader* create(const char* fname);
	~GeometryShader() {};

	virtual void printErrorLog() const;
	inline virtual GLenum getShaderType() const { return GL_GEOMETRY_SHADER; }
};

class FragmentShader : public ShaderFile
{
private:
	FragmentShader(const char* fname) : ShaderFile(fname) {};

public:
	static FragmentShader* create(const char* fname);
	~FragmentShader() {};

	virtual void printErrorLog() const;
	inline virtual GLenum getShaderType() const { return GL_FRAGMENT_SHADER; }
};

