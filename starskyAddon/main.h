#pragma once

#include "dx8/d3d8.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx8.h"

#pragma comment(lib,"d3d8.lib")

static LPDIRECT3DDEVICE8 d3d8Device = NULL;
static HWND gameWindowHwnd = 0;
