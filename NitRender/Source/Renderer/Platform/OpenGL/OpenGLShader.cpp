#include "OpenGLShader.h"
#include <glad/glad.h>

namespace Nit
{
    OpenGLShader::OpenGLShader() = default;

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_ShaderId);
    }

    void OpenGLShader::Compile(const char* vertexSource, const char* fragmentSource)
    {
        if (m_Compiled)
        {
            glDeleteProgram(m_ShaderId);
            m_Compiled = false;
        }

        // Create an empty vertex shader handle
        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that String's .c_str is NULL character terminated.
        const GLchar* source = vertexSource;
        glShaderSource(vertexShader, 1, &source, nullptr);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog.data());
            std::cout << "Error compiling the vertex shader: " << infoLog.data() << "\n";

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            assert(false && "Vertex shader compilation failed!");
        }

        // Create an empty fragment shader handle
        const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that String's .c_str is NULL character terminated.
        source = fragmentSource;
        glShaderSource(fragmentShader, 1, &source, nullptr);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog.data());
            std::cout << "Error compiling the fragment shader: '%s'" << infoLog.data() << "\n";

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            assert(false && "Fragment shader compilation failed!");
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_ShaderId = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(m_ShaderId, vertexShader);
        glAttachShader(m_ShaderId, fragmentShader);

        // Link our program
        glLinkProgram(m_ShaderId);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(m_ShaderId, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_ShaderId, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_ShaderId, maxLength, &maxLength, infoLog.data());
            std::cout << "Error linking the shaders: " << infoLog.data() << "\n";

            // We don't need the program anymore.
            glDeleteProgram(m_ShaderId);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            assert(false && "Shader linkage failed!");
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_ShaderId, vertexShader);
        glDetachShader(m_ShaderId, fragmentShader);

        m_Compiled = true;
    }

    static ShaderDataType ShaderDataTypeFromOpenGL(int32_t type)
    {
        switch (type)
        {
        case GL_FLOAT:      return ShaderDataType::Float;
        case GL_FLOAT_VEC2: return ShaderDataType::Float2;
        case GL_FLOAT_VEC3: return ShaderDataType::Float3;
        case GL_FLOAT_VEC4: return ShaderDataType::Float4;
        case GL_FLOAT_MAT3: return ShaderDataType::Mat3;
        case GL_FLOAT_MAT4: return ShaderDataType::Mat4;
        case GL_INT:        return ShaderDataType::Int;
        case GL_INT_VEC2:   return ShaderDataType::Int2;
        case GL_INT_VEC3:   return ShaderDataType::Int3;
        case GL_INT_VEC4:   return ShaderDataType::Int4;
        case GL_BOOL:       return ShaderDataType::Bool;
        default:            return ShaderDataType::None;
        }
    }

    void OpenGLShader::GetConstantCollection(std::vector<ConstantUniquePtr>& constants) const
    {
        int32_t uniformCount;
        glGetProgramiv(m_ShaderId, GL_ACTIVE_UNIFORMS, &uniformCount);

        for (int32_t i = 0; i < uniformCount; ++i)
        {
            constexpr int32_t bufSize = 16;
            char name[bufSize];
            uint32_t type;
            int32_t lenght;
            int32_t size;
            glGetActiveUniform(m_ShaderId, i, bufSize, &lenght, &size, &type, name);
            auto constant = Constant::CreateUnique(std::string(name), ShaderDataTypeFromOpenGL(type), size);
            if (!constant) { continue; }
            constants.push_back(std::move(constant));
        }
    }

    void OpenGLShader::SetConstantMat4(const char* constantName, const glm::mat4& mat) const
    {
        const uint32_t id = glGetUniformLocation(m_ShaderId, constantName);
        glUniformMatrix4fv(id, 1, false, glm::value_ptr(mat));
    }

    void OpenGLShader::SetConstantVec4(const char* constantName, const glm::vec4& vec) const
    {
        const uint32_t id = glGetUniformLocation(m_ShaderId, constantName);
        glUniform4fv(id, 1, glm::value_ptr(vec));
    }

    void OpenGLShader::SetConstantInt(const char* constantName, const int num)
    {
        const uint32_t id = glGetUniformLocation(m_ShaderId, constantName);
        glUniform1i(id, num);
    }

    void OpenGLShader::SetConstantIntArray(const char* constantName, const int32_t* array, const int32_t size)
    {
        const uint32_t id = glGetUniformLocation(m_ShaderId, constantName);
        glUniform1iv(id, size, array);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_ShaderId);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }
}