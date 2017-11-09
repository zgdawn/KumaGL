﻿// 静态的Mesh类
#ifndef kgl_static_mesh_h__
#define kgl_static_mesh_h__

#include "kgl_texture.h"
#include "kgl_vertex_type.h"
#include "kgl_gpu_program.h"

namespace kgl
{
    class StaticMesh : public boost::noncopyable
    {
    public:
        StaticMesh();
        virtual ~StaticMesh();

        /// <summary>
        /// Setups the specified vertex_type.
        /// </summary>
        /// <param name="vertex_type">The vertex_type.</param>
        /// <param name="vertex_data">The vertex_data.</param>
        /// <param name="vertex_byte_count">The vertex_byte_count.</param>
        /// <param name="index_data">The index_data.</param>
        /// <param name="index_byte_count">The index_byte_count.</param>
        /// <param name="texture_array">The texture_array.</param>
        /// <param name="local_transform_matrix">本mesh的模型变换矩阵</param>
        void Setup(VertexType vertex_type, const unsigned char* vertex_data, uint32_t vertex_byte_count, const uint32_t* index_data, uint32_t index_byte_count, const std::vector<TextureSPtr>& texture_array, const glm::mat4& local_transform_matrix);
        
        /// <summary>
        /// Draws this instance.
        /// </summary>
        void Draw();

        /// <summary>
        /// Sets the shader.
        /// </summary>
        /// <param name="shader">The shader.</param>
        inline void SetShader(GPUProgramSPtr shader)
        {
            shader_ = shader;
        }

        /// <summary>
        /// Gets the shader.
        /// </summary>
        /// <returns>GPUProgramSPtr.</returns>
        inline GPUProgramSPtr GetShader()
        {
            return shader_;
        }

        inline const glm::mat4& GetLocalTransformMatrix() const
        {
            return local_transform_matrix_;
        }

    protected:
        /// <summary>
        /// Clears this instance.
        /// </summary>
        void Clear();

        /// <summary>
        /// Setups the vertex attribute buffer.
        /// </summary>
        /// <param name="vertex_type">The vertex_type.</param>
        void SetupVertexAttributeBuffer(VertexType vertex_type);

        /// <summary>
        /// Setups the vertex attribute buffer p.
        /// </summary>
        void SetupVertexAttributeBufferP();

        /// <summary>
        /// Setups the vertex attribute buffer PNTB t1.
        /// </summary>
        void SetupVertexAttributeBufferPNTBT1();

        /// <summary>
        /// Setups the vertex attribute buffer PNTB t2.
        /// </summary>
        void SetupVertexAttributeBufferPNTBT2();

        /// <summary>
        /// Setups the vertex attribute buffer PNTB t3.
        /// </summary>
        void SetupVertexAttributeBufferPNTBT3();

        /// <summary>
        /// Setups the vertex attribute buffer PNTB t4.
        /// </summary>
        void SetupVertexAttributeBufferPNTBT4();

        /// <summary>
        /// Setups the vertex attribute buffer pc.
        /// </summary>
        void SetupVertexAttributeBufferPC();

        /// <summary>
        /// Setups the vertex attribute buffer pn.
        /// </summary>
        void SetupVertexAttributeBufferPN();

        /// <summary>
        /// Setups the vertex attribute buffer PNTB.
        /// </summary>
        void SetupVertexAttributeBufferPNTB();

        /// <summary>
        /// Setups the vertex attribute buffer pn t1.
        /// </summary>
        void SetupVertexAttributeBufferPNT1();

        /// <summary>
        /// Setups the vertex attribute buffer pn t2.
        /// </summary>
        void SetupVertexAttributeBufferPNT2();

        /// <summary>
        /// Setups the vertex attribute buffer pn t3.
        /// </summary>
        void SetupVertexAttributeBufferPNT3();

        /// <summary>
        /// Setups the vertex attribute buffer pn t4.
        /// </summary>
        void SetupVertexAttributeBufferPNT4();


    protected:
        /// <summary>
        ///  顶点缓冲区首指针
        /// </summary>
        uint8_t*                    vertex_data_;

        /// <summary>
        /// 顶点数据的字节数
        /// </summary>
        uint32_t                    vertex_byte_count_;

        /// <summary>
        /// The index_data_
        /// </summary>
        uint32_t*                   index_data_;

        /// <summary>
        /// The index_byte_count_
        /// </summary>
        uint32_t                    index_byte_count_;

        /// <summary>
        /// The texture_array_
        /// </summary>
        std::vector<TextureSPtr>    texture_array_;

        /// <summary>
        /// The vao_
        /// </summary>
        GLuint                      vao_;

        /// <summary>
        /// The vbo_
        /// </summary>
        GLuint                      vbo_;

        /// <summary>
        /// The ebo_
        /// </summary>
        GLuint                      ebo_;

        /// <summary>
        /// The vertex_type_
        /// </summary>
        VertexType                  vertex_type_;

        /// <summary>
        /// The shader_
        /// </summary>
        GPUProgramSPtr              shader_;

        /// <summary>
        /// 模型自身的局部坐标
        /// </summary>
        glm::mat4                   local_transform_matrix_;
    };
}
#endif // kgl_static_mesh_h__