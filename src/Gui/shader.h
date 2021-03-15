#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <fstream>
#include <sstream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar* geometryPath = nullptr);
    // activate the shader
    // ------------------------------------------------------------------------
    void use();
    // utility uniform functions
    // ------------------------------------------------------------------------
    GLuint getID();

    void setBool(const GLchar* name, bool value);
    // ------------------------------------------------------------------------
    void setInt(const GLchar* name, int value);
    // ------------------------------------------------------------------------
    void setFloat(const GLchar* name, float value);
    // ------------------------------------------------------------------------
    void setVec2(const GLchar* name, const glm::vec2 &value);
    void setVec2(const GLchar* name, float x, float y);
    // ------------------------------------------------------------------------
    void setVec3(const GLchar* name, const glm::vec3 &value);
    void setVec3(const GLchar* name, float x, float y, float z);
    // ------------------------------------------------------------------------
    void setVec4(const GLchar* name, const glm::vec4 &value);
    void setVec4(const GLchar* name, float x, float y, float z, float w);
    // ------------------------------------------------------------------------
    void setMat2(const GLchar* name, const glm::mat2 &mat);
    // ------------------------------------------------------------------------
    void setMat3(const GLchar* name, const glm::mat3 &mat);
    // ------------------------------------------------------------------------
    void setMat4(const GLchar* name, const glm::mat4 &mat);
    void setTexture(GLuint mode, const GLchar* name, GLuint texture);

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, GLchar* type, const GLchar *vertexPath);
    const std::string readFile(const GLchar* path);

    GLuint n_texture;
};

#endif // SHADER_H
