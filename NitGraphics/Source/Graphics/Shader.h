#pragma once

namespace Graphics
{
    class Constant
    {
    public:
        static std::unique_ptr<Constant> CreateUnique(const std::string& name, ShaderDataType type, int32_t size);

        Constant(const std::string& name, ShaderDataType type, int32_t size);
        Constant(Constant&& other) noexcept;
        Constant& operator=(Constant&& other) noexcept;

        int32_t*             GetIntData()   const { return m_intData;   }
        float*               GetFloatData() const { return m_floatData; }
        const std::string&   GetName()      const { return m_name;      }
        ShaderDataType       GetType()      const { return m_type;      }
        int32_t              GetSize()      const { return m_size;      }

        ~Constant();

    private:
        union
        {
            void*    m_data = nullptr;
            int32_t* m_intData;
            float*   m_floatData;
        };

        std::string    m_name;
        ShaderDataType m_type;
        int32_t        m_size;
    };


    class Shader
    {
    public:
        static std::shared_ptr<Shader> Create();

        virtual void Compile(const char* vertexSource, const char* fragmentSource) = 0;
        
        virtual void GetConstantCollection(std::vector<std::unique_ptr<Constant>>& constants) const = 0;
        
        virtual void SetConstantFloat     (const char* name, float value)                        const = 0;
        virtual void SetConstantVec2      (const char* name, const float* value)                 const = 0;
        virtual void SetConstantVec3      (const char* name, const float* value)                 const = 0;
        virtual void SetConstantVec4      (const char* name, const float* value)                 const = 0;
        virtual void SetConstantMat4      (const char* name, const float* value)                 const = 0;
        virtual void SetConstantInt       (const char* name, int value)                          const = 0;
        virtual void SetConstantSampler2D (const char* name, const int32_t* value, int32_t size) const = 0;
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };
}