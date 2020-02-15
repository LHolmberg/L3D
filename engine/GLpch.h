#pragma once

#define EXIT glfwSetWindowShouldClose(glfwGetCurrentContext(), 1)
template<typename T>
constexpr auto GETKEY(T x) { return glfwGetKey(glfwGetCurrentContext(), x); }
#define running !glfwWindowShouldClose(core::win.window)
