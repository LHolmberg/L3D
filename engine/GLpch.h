#pragma once

#define EXIT glfwSetWindowShouldClose(glfwGetCurrentContext(), 1)
#define running !glfwWindowShouldClose(win.window)
#define SWAP_BUFFERS glfwSwapBuffers(win.window)

constexpr auto K_W = 87;
constexpr auto K_A = 65;
constexpr auto K_S = 83;
constexpr auto K_D = 68;
constexpr auto K_ESC = 256;
constexpr auto K_SPACE = 32;

template<typename T>
constexpr auto GETKEY(T x) { return glfwGetKey(glfwGetCurrentContext(), x); }

