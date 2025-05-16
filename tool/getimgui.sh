#!/bin/sh
get () {
	curl -L https://github.com/ocornut/imgui/raw/refs/heads/master/$2/$1 > $1
}

cd external/imgui
get imgui_impl_opengl2.cpp backends
get imgui_impl_opengl2.h backends
get imgui.h
get imgui.cpp
get imconfig.h
get imgui_internal.h
get imgui_draw.cpp
get imgui_tables.cpp
get imgui_widgets.cpp
get imstb_rectpack.h
get imstb_textedit.h
get imstb_truetype.h
curl -L https://github.com/ColleagueRiley/imgui_imp_rgfw.h/raw/refs/heads/main/imgui_impl_rgfw.h > imgui_impl_rgfw.h
curl -L https://github.com/ColleagueRiley/RGFW/raw/refs/heads/main/RGFW.h > RGFW.h
