#ifndef __IMGUI_INCLUDE_H__
#define __IMGUI_INCLUDE_H__

#define RGFWDEF
#include <RGFW.h>
#include <imgui_impl_rgfw.h>
#include <imgui_impl_opengl2.h>

extern RGFW_window* win;
extern ImGuiIO*	    io;
extern bool	    opengl;
extern int	    open_about;
extern int	    open_file;

extern ImVec2 menu;

void toolbox(void);
void nav(void);
void stuff(void);

#endif
