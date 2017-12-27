﻿// 一些工具宏的定义
#ifndef kgl_defines_h__
#define kgl_defines_h__

#include "kgl_error.h"

#define THROW_GL_EXCEPTION(error_desc_array,error_code_array,file_name,code_line) if (kgl::Error::GetGLErrorDesc(error_desc_array, error_code_array)){\
    throw kgl::Error(error_code_array, error_desc_array, file_name, code_line);}

#define KGL_SAFE_DELETE(obj) do{if(nullptr != obj){delete obj;obj = nullptr;}}while(0)

#define KGL_SAFE_DELETE_ARRAY(obj) do{if(nullptr != obj){delete [] obj;obj = nullptr;}}while(0)

typedef boost::multi_array<float, 2> Float2DArray;
typedef boost::multi_array<glm::vec4, 2> Color2DArray;
typedef boost::multi_array<glm::vec4, 2> Vec4Array2D;
typedef boost::multi_array<glm::vec3, 2> Vec3Array2D;

#define COLOR_TEXTURE_UNIT					GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX			0
#define SHADOW_TEXTURE_UNIT					GL_TEXTURE1
#define SHADOW_TEXTURE_UNIT_INDEX			1
#define NORMAL_TEXTURE_UNIT					GL_TEXTURE2
#define NORMAL_TEXTURE_UNIT_INDEX			2
#define RANDOM_TEXTURE_UNIT					GL_TEXTURE3
#define RANDOM_TEXTURE_UNIT_INDEX			3
#define DISPLACEMENT_TEXTURE_UNIT			GL_TEXTURE4
#define DISPLACEMENT_TEXTURE_UNIT_INDEX		4
#define MOTION_TEXTURE_UNIT					GL_TEXTURE5
#define MOTION_TEXTURE_UNIT_INDEX			5
#define CASCACDE_SHADOW_TEXTURE_UNIT0       SHADOW_TEXTURE_UNIT
#define CASCACDE_SHADOW_TEXTURE_UNIT0_INDEX SHADOW_TEXTURE_UNIT_INDEX
#define CASCACDE_SHADOW_TEXTURE_UNIT1       GL_TEXTURE6
#define CASCACDE_SHADOW_TEXTURE_UNIT1_INDEX 6
#define CASCACDE_SHADOW_TEXTURE_UNIT2       GL_TEXTURE7
#define CASCACDE_SHADOW_TEXTURE_UNIT2_INDEX 7

#endif // kgl_defines_h__