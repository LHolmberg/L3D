game:
	g++ engine/Source.cpp engine/rendering.cpp engine/Ai.cpp engine/math.cpp engine/console.cpp engine/physics.cpp engine/gui.cpp engine/external/imgui/imgui_impl_glfw_gl3.cpp engine/external/imgui/imgui.cpp engine/external/imgui/imgui_draw.cpp engine/external/imgui/imgui_demo.cpp -w -lglfw -lglew -lSOIL -lassimp -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon

gamelin:
	g++ engine/Source.cpp engine/rendering.cpp engine/Ai.cpp engine/math.cpp engine/console.cpp engine/physics.cpp engine/gui.cpp engine/external/imgui/imgui_impl_glfw_gl3.cpp engine/external/imgui/imgui.cpp engine/external/imgui/imgui_draw.cpp engine/external/imgui/imgui_demo.cpp -w -lX11 -lassimp -lGL -g -Wall -lglfw -lGLEW -lSOIL
