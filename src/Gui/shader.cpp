#include "shader.h"
#include <iostream>

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar* geometryPath):n_texture(0)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    vertexCode = readFile(vertexPath);
    fragmentCode = readFile(fragmentPath);
    if(geometryPath != nullptr){
        geometryCode = readFile(geometryPath);
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX", vertexPath);

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT", fragmentPath);

    // if geometry shader is given, compile geometry shader
    unsigned int geometry;
    if(geometryPath != nullptr)
    {
        const char * gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY", geometryPath);
    }

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if(geometryPath != nullptr)
        glAttachShader(ID, geometry);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM", nullptr);

    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(geometryPath != nullptr)
        glDeleteShader(geometry);

}

void Shader::use()
{
    glUseProgram(ID);
}

GLuint Shader::getID()
{
    return ID;
}

void Shader::setBool(const GLchar* name, bool value)
{
    glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void Shader::setInt(const GLchar* name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::setFloat(const GLchar* name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::setVec2(const GLchar* name, const glm::vec2 &value)
{
    glUniform2fv(glGetUniformLocation(ID, name), 1, &value[0]);
}

void Shader::setVec2(const GLchar* name, float x, float y)
{
    glUniform2f(glGetUniformLocation(ID, name), x, y);
}

void Shader::setVec3(const GLchar* name, const glm::vec3 &value)
{
    glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]);
}

void Shader::setVec3(const GLchar* name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}

void Shader::setVec4(const GLchar* name, const glm::vec4 &value)
{
    glUniform4fv(glGetUniformLocation(ID, name), 1, &value[0]);
}

void Shader::setVec4(const GLchar* name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}

void Shader::setMat2(const GLchar* name, const glm::mat2 &mat)
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const GLchar* name, const glm::mat3 &mat)
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const GLchar* name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setTexture(GLuint mode, const GLchar* name, GLuint texture)
{
    setInt(name, n_texture);
    glActiveTexture(GL_TEXTURE0 + n_texture);
    glBindTexture(mode, texture);
    glUniform1i(glGetUniformLocation(ID, name), n_texture++);
}

const std::string Shader::readFile(const GLchar *path)
{
    std::string code;
    std::ifstream file;

    file.exceptions(std::ifstream::badbit);
    try {
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        code = stream.str();

    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_WAS_NOT_SUCCESFULLY_READ";
    }{}

    return code;
}

void Shader::checkCompileErrors(GLuint shader, GLchar* type, const GLchar *path)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << " " << path << "\n" << infoLog << "\n -- --------------------------------------------------- -- ";
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << " " << path << "\n" << infoLog << "\n -- --------------------------------------------------- -- ";
        }
    }
}
