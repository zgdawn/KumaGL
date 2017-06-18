// 简单的纹理应用示例


#include "pixel_magic_app.h"
#include "../klib/kgl_defines.h"

PixelMagicApp::PixelMagicApp():
colorful_ring_shader_(nullptr),
heart_beat_shader_(nullptr),
mobius_shader_(nullptr),
sun_shader_(nullptr),
simple_fractal_shader_(nullptr),
rectangle_primitive_(nullptr),
current_effect_index_(0),
effect_count_(5)
{
}

PixelMagicApp::~PixelMagicApp()
{
    KGL_SAFE_DELETE(colorful_ring_shader_);
    KGL_SAFE_DELETE(heart_beat_shader_);
    KGL_SAFE_DELETE(mobius_shader_);
    KGL_SAFE_DELETE(sun_shader_);
    KGL_SAFE_DELETE(simple_fractal_shader_);
    KGL_SAFE_DELETE(rectangle_primitive_);
    texture_1_.reset();
    texture_2_.reset();
}

void PixelMagicApp::InitScene()
{
    screen_resolution_ = glm::vec2(800.0f, 600.0f);
// ================================================================
    heart_beat_shader_ = new kgl::GPUProgram;
    heart_beat_shader_->CreateFromFile("resources/shader/pixel_magic_vs.glsl", "resources/shader/heart_beat_fs.glsl", nullptr);
// ================================================================
    colorful_ring_shader_ = new kgl::GPUProgram;
    colorful_ring_shader_->CreateFromFile("resources/shader/pixel_magic_vs.glsl", "resources/shader/colorful_ring_fs.glsl", nullptr);
// ================================================================
    mobius_shader_ = new kgl::GPUProgram;
    mobius_shader_->CreateFromFile("resources/shader/pixel_magic_vs.glsl", "resources/shader/mobius_fs.glsl", nullptr);
// ================================================================
    sun_shader_ = new kgl::GPUProgram;
    sun_shader_->CreateFromFile("resources/shader/pixel_magic_vs.glsl", "resources/shader/sun_fs.glsl", nullptr);
// ================================================================
    simple_fractal_shader_ = new kgl::GPUProgram;
    simple_fractal_shader_->CreateFromFile("resources/shader/pixel_magic_vs.glsl", "resources/shader/pm_japan_flag_fs.glsl", nullptr);
// ================================================================
    kgl::TextureParams texture_param;
    texture_param.WrapSMode = GL_REPEAT;
    texture_param.WrapTMode = GL_REPEAT;
    texture_param.MagFilterMode = GL_LINEAR;
    texture_param.MinFilterMode = GL_LINEAR;
    texture_param.InternalFormat = GL_RGB;
    texture_param.SrcImgPixelComponentType = GL_UNSIGNED_BYTE;
    texture_param.SrcImgFormat = GL_RGB;
    texture_param.LoadChannel = SOIL_LOAD_RGB;
    texture_param.UseMipmap = false;

    texture_rock_ = std::make_shared<kgl::SourceTexture>();
    texture_rock_->CreateFromFile("resources/image/stone_small.jpg", texture_param);

    GLfloat vertices[] =
    {
        // 位置          // 颜色            //纹理坐标1 //纹理坐标2 //纹理坐标3 //纹理坐标4
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,// 右上角
        1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下角
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,0.0f, 0.0f, // 左下角
        - 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f  //左上角
    };

    GLuint indices[] =
    {
        0, 1, 3,
        1, 2, 3
    };

    kgl::VertexAttribute va_position;
    va_position.Index = 0;
    va_position.Normalized = GL_FALSE;
    va_position.Type = GL_FLOAT;
    va_position.Size = 3; // 一个“顶点位置”的属性由3个分量组成
    va_position.Stride = 14 * sizeof(GLfloat); // 每个顶点的步长
    va_position.Pointer = nullptr;

    kgl::VertexAttribute va_color;
    va_color.Index = 1;
    va_color.Normalized = GL_FALSE;
    va_color.Type = GL_FLOAT;
    va_color.Size = 3; // 一个“顶点颜色”的属性由3个分量组成
    va_color.Stride = 14 * sizeof(GLfloat); //每个顶点的步长
    va_color.Pointer = reinterpret_cast<GLvoid*> (3 * sizeof(GLfloat));

    kgl::VertexAttribute va_texture_coord_1;
    va_texture_coord_1.Index = 2;
    va_texture_coord_1.Normalized = GL_FALSE;
    va_texture_coord_1.Type = GL_FLOAT;
    va_texture_coord_1.Size = 2; // 一个“顶点坐标”的属性由3个分量组成
    va_texture_coord_1.Stride = 14 * sizeof(GLfloat); // 每个顶点的步长
    va_texture_coord_1.Pointer = reinterpret_cast<GLvoid*> (6 * sizeof(GLfloat)); // 纹理坐标数据在字段中的起始指针处

    kgl::VertexAttribute va_texture_coord_2;
    va_texture_coord_2.Index = 3;
    va_texture_coord_2.Normalized = GL_FALSE;
    va_texture_coord_2.Type = GL_FLOAT;
    va_texture_coord_2.Size = 2; // 一个“顶点坐标”的属性由3个分量组成
    va_texture_coord_2.Stride = 14 * sizeof(GLfloat); // 每个顶点的步长
    va_texture_coord_2.Pointer = reinterpret_cast<GLvoid*> (8 * sizeof(GLfloat)); // 纹理坐标数据在字段中的起始指针处

    kgl::VertexAttribute va_texture_coord_3;
    va_texture_coord_3.Index = 4;
    va_texture_coord_3.Normalized = GL_FALSE;
    va_texture_coord_3.Type = GL_FLOAT;
    va_texture_coord_3.Size = 2; // 一个“顶点坐标”的属性由3个分量组成
    va_texture_coord_3.Stride = 14 * sizeof(GLfloat); // 每个顶点的步长
    va_texture_coord_3.Pointer = reinterpret_cast<GLvoid*> (10 * sizeof(GLfloat)); // 纹理坐标数据在字段中的起始指针处

    kgl::VertexAttribute va_texture_coord_4;
    va_texture_coord_4.Index = 5;
    va_texture_coord_4.Normalized = GL_FALSE;
    va_texture_coord_4.Type = GL_FLOAT;
    va_texture_coord_4.Size = 2; // 一个“顶点坐标”的属性由3个分量组成
    va_texture_coord_4.Stride = 14 * sizeof(GLfloat); // 每个顶点的步长
    va_texture_coord_4.Pointer = reinterpret_cast<GLvoid*> (12 * sizeof(GLfloat)); // 纹理坐标数据在字段中的起始指针处

    std::vector<kgl::VertexAttribute> vtx_attri_array;
    vtx_attri_array.push_back(va_position);
    vtx_attri_array.push_back(va_color);
    vtx_attri_array.push_back(va_texture_coord_1);
    vtx_attri_array.push_back(va_texture_coord_2);
    vtx_attri_array.push_back(va_texture_coord_3);
    vtx_attri_array.push_back(va_texture_coord_4);

    rectangle_primitive_ = new kgl::Primitive;
    rectangle_primitive_->Create(GL_TRIANGLES, vertices, sizeof(vertices), GL_STATIC_DRAW, kgl::Primitive::UINT32, indices, sizeof(indices), GL_STATIC_DRAW, vtx_attri_array);
}

void PixelMagicApp::RenderFrame()
{
    switch (current_effect_index_)
    {
    case 0:this->RenderBeatHeart(); break;
    case 1:this->RenderColorfulRing(); break;
    case 2:this->RenderMobius(); break;
    case 3:this->RenderSun(); break;
    case 4:this->RenderSimpleFractal(); break;
    }

    rectangle_primitive_->DrawIndexed();
}

void PixelMagicApp::RenderBeatHeart()
{
    heart_beat_shader_->Use();
    heart_beat_shader_->ApplyFloat(glfwGetTime(), "global_time");
    heart_beat_shader_->ApplyVector2(glm::value_ptr(screen_resolution_), "screen_resolution");
}

void PixelMagicApp::RenderColorfulRing()
{
    colorful_ring_shader_->Use();
    colorful_ring_shader_->ApplyFloat(glfwGetTime(), "global_time");
    colorful_ring_shader_->ApplyVector2(glm::value_ptr(screen_resolution_), "screen_resolution");
}

void PixelMagicApp::RenderMobius()
{
    mobius_shader_->Use();
    mobius_shader_->ApplyFloat(glfwGetTime(), "global_time");
    mobius_shader_->ApplyVector2(glm::value_ptr(screen_resolution_), "screen_resolution");
    mobius_shader_->ApplyVector2(glm::value_ptr(mouse_input_pos_), "mouse_input_pos");
}

void PixelMagicApp::RenderSun()
{
    sun_shader_->Use();
    sun_shader_->ApplyFloat(glfwGetTime(), "global_time");
    sun_shader_->ApplyVector2(glm::value_ptr(screen_resolution_), "screen_resolution");
    sun_shader_->ApplyVector2(glm::value_ptr(mouse_input_pos_), "mouse_input_pos");
    sun_shader_->ApplyTexture(texture_rock_, "texture_channel_1", 0);
}

void PixelMagicApp::RenderSimpleFractal()
{
    simple_fractal_shader_->Use();
    simple_fractal_shader_->ApplyVector2(glm::value_ptr(screen_resolution_), "screen_resolution");
}

void PixelMagicApp::OnKeyAction(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_RIGHT  && action == GLFW_RELEASE)
    {
        current_effect_index_++;

        if (current_effect_index_  >= effect_count_)
            current_effect_index_ = 0;
    }

    if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
    {
        current_effect_index_--;

        if (current_effect_index_ < 0)
            current_effect_index_ = effect_count_ -  1;
    }

    App::OnKeyAction(window, key, scancode, action, mode);
}

void PixelMagicApp::OnMouseAction(GLFWwindow* window, double xpos, double ypos)
{
    mouse_input_pos_.x = static_cast<float>(xpos);
    mouse_input_pos_.y = static_cast<float>(ypos);
}