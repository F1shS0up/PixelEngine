#pragma once

#include <SDL.h>
#include "glm/glm.hpp"

class input_manager
{
public:

	enum MOUSE_BUTTONS { left = 0, right, middle, back, forward };

private:

	Uint8* previousKeyState;
	const Uint8* keyboardState;
	int keyLength;

	Uint32 prevMouseState;
	Uint32 mouseState;

	glm::ivec2 mousePos = glm::ivec2(0, 0);
	glm::ivec2 prevMousePos;

public:

	input_manager(float dividerX, float dividerY);
	~input_manager();

	bool KeyDown(SDL_Scancode scanCode);
	bool KeyPressed(SDL_Scancode scanCode);
	bool KeyReleased(SDL_Scancode scanCode);

	bool MouseButtonDown(MOUSE_BUTTONS button);
	bool MouseButtonPressed(MOUSE_BUTTONS button);
	bool MouseButtonReleased(MOUSE_BUTTONS button);

	float dividerX, dividerY;

	glm::ivec2 MousePos();
	glm::ivec2 PrevMousePos();

	void Update();
	void UpdatePrevInput();

};