#pragma once

namespace Nit
{
    class Shader;
    using ShaderPtr     = std::shared_ptr<Shader>;
    using ShaderWeakPtr = std::weak_ptr<Shader>;

    class Constant;
    using ConstantUniquePtr = std::unique_ptr<Constant>;

    //#TODO_asuarez Ser�a mejor pre-reservar memoria para todos los uniforms al principio para que est� m�s alineada y facilitar el acceso.
    // que el uniform se cree a s� mismo
    // hacer un getter de la data, o hacerla directamente p�blica
    // quitar el in�til weak ptr del shader
    // quiz�s habr�a que hacer que el material creara los uniforms al crearse, no el shader. Esto implicar�a hacer una abstracci�n de Material por plataforma.
    // en ese caso mover todo esto al fichero Material.cpp
    // Al final Uniform va a ser un struct muy data oriented quiz�s...
    
    class Constant
    {
    public:
        static ConstantUniquePtr CreateUnique(const std::string& name, ShaderDataType type, int32_t size);

        Constant(const std::string& name, ShaderDataType type, int32_t size);
        Constant(Constant&& other) noexcept;
        Constant& operator=(Constant&& other) noexcept;

        int32_t*             GetIntData()   const { return m_IntData;   }
        float*               GetFloatData() const { return m_FloatData; }
        const std::string&   GetName()      const { return m_Name;      }
        ShaderDataType       GetType()      const { return m_Type;      }
        int32_t              GetSize()      const { return m_Size;      }

        ~Constant();

    private:
        union
        {
            void* m_Data = nullptr;
            int32_t* m_IntData;
            float* m_FloatData;
        };

        std::string    m_Name;
        ShaderDataType m_Type;
        int32_t        m_Size;
    };


    class Shader
    {
    public:
        static ShaderPtr Create();

        virtual void Compile(const char* vertexSource, const char* fragmentSource) = 0;
        
        virtual void GetConstantCollection(std::vector<ConstantUniquePtr>& constants) const = 0;
        
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