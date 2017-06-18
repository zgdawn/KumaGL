﻿// 简单的纹理应用示例
#include "transform_app.h"
#include "../klib/kgl_defines.h"
#include "../klib/kgl_debug_tool.h"

TransformApp::TransformApp() :gpu_program_(nullptr), rectangle_primitive_(nullptr)
{
}

TransformApp::~TransformApp()
{
	KGL_SAFE_DELETE(gpu_program_);
	KGL_SAFE_DELETE(rectangle_primitive_);
	texture_1_.reset();
	texture_2_.reset();
}

void TransformApp::InitScene()
{
	gpu_program_ = new kgl::GPUProgram;
	gpu_program_->CreateFromFile("resources/shader/004_transform_vs.glsl", "resources/shader/004_transform_fs.glsl", nullptr);

	kgl::TextureParams texture_param;
	texture_param.wrap_s_mode = GL_REPEAT;
	texture_param.wrap_t_mode = GL_REPEAT;
	texture_param.mag_filter_mode = GL_LINEAR;
	texture_param.min_filter_mode = GL_LINEAR;
	texture_param.internal_format = GL_RGB;
	texture_param.src_img_px_component_type = GL_UNSIGNED_BYTE;
	texture_param.src_img_format = GL_RGB;
	texture_param.load_channel = SOIL_LOAD_RGB;
	texture_param.used_mipmap = false;

	texture_1_ = std::make_shared<kgl::SourceTexture>();
	texture_1_->CreateFromFile("resources/image/coordinate.bmp", texture_param);

	texture_2_ = std::make_shared<kgl::SourceTexture>();
	texture_2_->CreateFromFile("resources/image/braynzar.jpg", texture_param);

	GLfloat vertices[] =
	{
		// 位置          // 颜色           // 纹理映射坐标
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右上角
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下角
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  //左上角
	};

	GLuint indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	kgl::VertexAttribute va_position;
	va_position.index = 0;
	va_position.normalized = GL_FALSE;
	va_position.type = GL_FLOAT;
	va_position.size = 3; // 一个“顶点位置”的属性由3个分量组成
	va_position.stride = 8 * sizeof(GLfloat); // 每个顶点的步长
	va_position.pointer = nullptr;

	kgl::VertexAttribute va_color;
	va_color.index = 1;
	va_color.normalized = GL_FALSE;
	va_color.type = GL_FLOAT;
	va_color.size = 3; // 一个“顶点颜色”的属性由3个分量组成
	va_color.stride = 8 * sizeof(GLfloat); //每个顶点的步长
	va_color.pointer = reinterpret_cast<GLvoid*> (3 * sizeof(GLfloat));

	kgl::VertexAttribute va_texture_coord;
	va_texture_coord.index = 2;
	va_texture_coord.normalized = GL_FALSE;
	va_texture_coord.type = GL_FLOAT;
	va_texture_coord.size = 2; // 一个“顶点坐标”的属性由3个分量组成
	va_texture_coord.stride = 8 * sizeof(GLfloat); // 每个顶点的步长
	va_texture_coord.pointer = reinterpret_cast<GLvoid*> (6 * sizeof(GLfloat)); // 纹理坐标数据在字段中的起始指针处

	std::vector<kgl::VertexAttribute> vtx_attri_array;
	vtx_attri_array.push_back(va_position);
	vtx_attri_array.push_back(va_color);
	vtx_attri_array.push_back(va_texture_coord);

	rectangle_primitive_ = new kgl::Primitive;
	rectangle_primitive_->Create(GL_TRIANGLES, vertices, sizeof(vertices), GL_STATIC_DRAW, kgl::Primitive::UINT32, indices, sizeof(indices), GL_STATIC_DRAW, vtx_attri_array);
}

void TransformApp::RenderFrame()
{
	gpu_program_->Use();
	gpu_program_->ApplyTexture(texture_1_, "ourTexture1", 0);
	gpu_program_->ApplyTexture(texture_2_, "ourTexture2", 1);

	// 计算变换
	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
	transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 0.5f, glm::vec3(0.0f, 0.0f, 1.0f));
	gpu_program_->ApplyMatrix(glm::value_ptr(transform), "transform");

	rectangle_primitive_->DrawIndexed();
}