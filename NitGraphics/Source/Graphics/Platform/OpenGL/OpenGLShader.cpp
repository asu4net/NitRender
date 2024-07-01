#include "OpenGLShader.h"
#include <glad/glad.h>

namespace Graphics
{
    OpenGLShader::OpenGLShader() = default;

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_shaderId);
    }

    void OpenGLShader::Compile(const char* vertexSource, const char* fragmentSource)
    {
        if (m_bCompiled)
        {
            glDeleteProgram(m_shaderId);
            m_bCompiled = false;
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
        m_shaderId = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(m_shaderId, vertexShader);
        glAttachShader(m_shaderId, fragmentShader);

        // Link our program
        glLinkProgram(m_shaderId);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(m_shaderId, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_shaderId, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_shaderId, maxLength, &maxLength, infoLog.data());
            std::cout << "Error linking the shaders: " << infoLog.data() << "\n";

            // We don't need the program anymore.
            glDeleteProgram(m_shaderId);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            assert(false && "Shader linkage failed!");
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_shaderId, vertexShader);
        glDetachShader(m_shaderId, fragmentShader);

        m_bCompiled = true;
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
        case GL_SAMPLER_2D: return ShaderDataType::Sampler2D;
        case GL_INT_VEC2:   return ShaderDataType::Int2;
        case GL_INT_VEC3:   return ShaderDataType::Int3;
        case GL_INT_VEC4:   return ShaderDataType::Int4;
        case GL_BOOL:       return ShaderDataType::Bool;
        default:            return ShaderDataType::None;
        }
    }

    void OpenGLShader::GetConstantCollection(std::vector<std::unique_ptr<Constant>>& constants) const
    {
        int32_t uniformCount;
        glGetProgramiv(m_shaderId, GL_ACTIVE_UNIFORMS, &uniformCount);

        for (int32_t i = 0; i < uniformCount; ++i)
        {
            constexpr int32_t bufSize = 32;
            char name[bufSize];
            uint32_t type;
            int32_t lenght;
            int32_t size;
            glGetActiveUniform(m_shaderId, i, bufSize, &lenght, &size, &type, name);
            auto constant = Constant::CreateUnique(name, ShaderDataTypeFromOpenGL(type), size);
            if (!constant) { continue; }
            constants.push_back(std::move(constant));
        }
    }

    void OpenGLShader::SetConstantFloat(const char* name, float value) const
    {
        const uint32_t location = glGetUniformLocation(m_shaderId, name);
        glUniform1f(location, value);
    }

    void OpenGLShader::SetConstantVec2(const char* name, const float* value) const
    {
        const uint32_t location = glGetUniformLocation(m_shaderId, name);
        glUniform2fv(location, 1, value);
    }

    void OpenGLShader::SetConstantVec3(const char* name, const float* value) const
    {
        const uint32_t location = glGetUniformLocation(m_shaderId, name);
        glUniform3fv(location, 1, value);
    }

    void OpenGLShader::SetConstantMat4(const char* name, const float* value) const
    {
        const uint32_t location = glGetUniformLocation(m_shaderId, name);
        glUniformMatrix4fv(location, 1, false, value);
    }

    void OpenGLShader::SetConstantVec4(const char* name, const float* value) const
    {
        const uint32_t location = glGetUniformLocation(m_shaderId, name);
        glUniform4fv(location, 1, value);
    }

    void OpenGLShader::SetConstantInt(const char* name, int value) const
    {
        const uint32_t location = glGetUniformLocation(m_shaderId, name);
        glUniform1i(location, value);
    }

    void OpenGLShader::SetConstantSampler2D(const char* name, const int32_t* value, int32_t size) const
    {
        const int location = glGetUniformLocation(m_shaderId, name);
        glUniform1iv(location, size, value);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_shaderId);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }
}