#pragma once
#include "global.hpp"
#include <dwmapi.h>
#include "imgui/imgui_internal.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"


auto setup_window() -> void;
auto begindraw() -> void;
auto cleandraw() -> void;
auto cleanup_d3d() -> void;
void DefaultTheme();
void DrawFilledRect2(int x, int y, int w, int h, ImColor color);
void DrawNormalBox(int x, int y, int w, int h, int borderPx, int type);
void DrawScope(int x, int y, int w, int h, int borderPx);
auto enddraw() -> void;
auto init_wndparams()->HRESULT;
