﻿// 简单的纹理应用示例
#ifndef assimp_app_h__
#define assimp_app_h__

#include "../klib/kgl_lib_pch.h"
#include "../klib/kgl_app.h"
#include "../klib/kgl_gpu_program.h"
#include "../klib/kgl_primitive.h"
#include "../klib/kgl_source_texture.h"
#include "../klib/kgl_basic_static_mesh.h"
#include "../klib/kgl_font_renderer.h"
#include "../klib/kgl_render_state_blend.h"
#include "../klib/kgl_render_state_depth.h"

class AssimpApp : public kgl::App
{
public:
	AssimpApp();
	virtual ~AssimpApp();
	virtual void InitScene()  override;
protected:
	virtual void RenderFrame() override;
	virtual void ProcessInput() override;
	virtual void InitModel() override;
	virtual void InitShaders() override;
	virtual void InitFont() override;
	virtual void InitMainCamera() override;
	void RenderText();
private:
	kgl::GPUProgramSPtr			model_shader_;
	kgl::BasicStaticMesh*		model_;
	kgl::RenderStateDepth		rs_depth_;
	kgl::RenderStateBlend		rs_blend_;
};

#endif // assimp_app_h__