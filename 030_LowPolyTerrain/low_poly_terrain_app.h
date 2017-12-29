﻿/*!
 * \file low_poly_terrain_app.h
 * \date 2017/11/25 0:32
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 展示几何着色器的一些相关操作
 *
 * \note
*/
#ifndef low_poly_terrain_app_h__
#define low_poly_terrain_app_h__

#include "../klib/kgl_lib_pch.h"
#include "../klib/kgl_light.h"
#include "../klib/kgl_app.h"
#include "../klib/kgl_render_state_cull_mode.h"
#include "../klib/kgl_render_state_depth.h"
#include "../klib/kgl_terrain.h"
#include "../klib/kgl_flat_terrain_generator.h"
#include "../klib/kgl_perlin_noise.h"
#include "../klib/kgl_color_generator.h"
#include "../klib/kgl_indices_generator.h"
#include "../klib/kgl_render_state_draw_mode.h"

class LowPolyTerrainApp: public kgl::App
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="GeometryShaderApp"/> class.
	/// </summary>
	LowPolyTerrainApp();

	/// <summary>
	/// Finalizes an instance of the <see cref="GeometryShaderApp"/> class.
	/// </summary>
	virtual ~LowPolyTerrainApp();

protected:
	/// <summary>
	/// Pres the render frame.
	/// </summary>
	virtual void PreRenderFrame() override;

	/// <summary>
	/// Initializes the model.
	/// </summary>
	virtual void InitModel() override;

	/// <summary>
	/// Initializes the shader.
	/// </summary>
	virtual void InitShaders() override;

	virtual void InitLights() override;

	/// <summary>
	/// Initializes the main camera.
	/// </summary>
	virtual void InitMainCamera() override;

	/// <summary>
	/// Initializes the font.
	/// </summary>
	virtual void InitFont() override;

	/// <summary>
	/// Renders the frame.
	/// </summary>
	virtual void RenderFrame() override;

	/// <summary>
	/// Called when [key action].
	/// </summary>
	/// <param name="window">The window.</param>
	/// <param name="key">The key.</param>
	/// <param name="scancode">The scancode.</param>
	/// <param name="action">The action.</param>
	/// <param name="mode">The mode.</param>
	virtual void OnKeyAction(GLFWwindow* window, int key, int scancode, int action, int mode) override;

	/// <summary>
	/// Called when [mouse action].
	/// </summary>
	/// <param name="window">The window.</param>
	/// <param name="xpos">The xpos.</param>
	/// <param name="ypos">The ypos.</param>
	virtual void OnMouseAction(GLFWwindow* window, double xpos, double ypos) override;

	/// <summary>
	/// Called when [scroll action].
	/// </summary>
	/// <param name="window">The window.</param>
	/// <param name="xoffset">The xoffset.</param>
	/// <param name="yoffset">The yoffset.</param>
	virtual void OnScrollAction(GLFWwindow* window, double xoffset, double yoffset) override;

	/// <summary>
	/// 处理外设输入的方法
	/// </summary>
	virtual void ProcessInput() override;
private:
	/// <summary>
	/// 绘制彩色多边形
	/// </summary>
	void RenderColoredPolygon();

	/// <summary>
	/// 绘制爆炸的模型
	/// </summary>
	void RenderExplodeModel();

	/// <summary>
	/// 绘制帮助文本
	/// </summary>
	/// <param name="view_pos">摄像机的位置</param>
	void DrawHelpText(const glm::vec3& view_pos);
private:
	kgl::low_poly_terrain::TerrainSPtr terrain_;
	kgl::low_poly_terrain::FlatTerrainGenerator* flat_terrain_generator_ = nullptr;
	kgl::low_poly_terrain::PerlinNoiseSPtr perlin_noise_;
	kgl::low_poly_terrain::ColorGeneratorSPtr color_generator_;
	kgl::low_poly_terrain::IndicesGeneratorSPtr indices_generator_;

	kgl::LowPolyTerrainLight light_;

	/// <summary>
	/// 启用深度buffer的render state
	/// </summary>
	kgl::RenderStateDepth	rs_depth_;
	
	/// <summary>
	/// The toggle_help_on_text_
	/// </summary>
	std::wstring            toggle_help_on_text_;

	/// <summary>
	/// The toggle_help_off_text_
	/// </summary>
	std::wstring            toggle_help_off_text_;

	std::wstring			camera_ctrl_text_;

	/// <summary>
	/// 是否显示帮助文档
	/// </summary>
	bool is_help_on_ = true;
	
	/// <summary>
	///
	/// </summary>
	kgl::RenderStateDrawMode	draw_mode_;
	
	/// <summary>
	///
	/// </summary>
	bool draw_mode_line_ = false;

	
};


#endif // low_poly_terrain_app_h__