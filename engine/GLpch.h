#pragma once

#define EXIT glfwSetWindowShouldClose(glfwGetCurrentContext(), 1)
#define GETKEY(x) glfwGetKey(glfwGetCurrentContext(), x)
#define running !glfwWindowShouldClose(core::win.window)
