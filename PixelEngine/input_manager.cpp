#include "input_manager.h"

bool input_manager::KeyDown(SDL_Scancode scanCode)
{
	return keyboardState[scanCode];
}
bool input_manager::KeyPressed(SDL_Scancode scanCode)
{
	return !previousKeyState[scanCode] && keyboardState[scanCode];
}
bool input_manager::KeyReleased(SDL_Scancode scanCode)
{
	return previousKeyState[scanCode] && !keyboardState[scanCode];
}

glm::ivec2 input_manager::MousePos()
{
	return glm::ivec2(mousePos.x / dividerX, mousePos.y / dividerY);
}
glm::ivec2 input_manager::PrevMousePos()
{
	return glm::ivec2(prevMousePos.x / dividerX, prevMousePos.y / dividerY);
}

bool input_manager::MouseButtonDown(MOUSE_BUTTONS button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	case middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (mouseState & mask);
}
bool input_manager::MouseButtonPressed(MOUSE_BUTTONS button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	case middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return !(prevMouseState & mask) && (mouseState & mask);
}
bool input_manager::MouseButtonReleased(MOUSE_BUTTONS button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	case middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (prevMouseState & mask) && !(mouseState & mask);
}

void input_manager::Update()
{
	mouseState = SDL_GetMouseState((int*)&mousePos.x, (int*)&mousePos.y);
}
void input_manager::UpdatePrevInput()
{
	SDL_memcpy(previousKeyState, keyboardState, keyLength);
	prevMousePos = mousePos;
	prevMouseState = mouseState;
}

input_manager::input_manager(float dividerX, float dividerY)
{
	keyboardState = SDL_GetKeyboardState(&keyLength);
	previousKeyState = new Uint8[keyLength];
	SDL_memcpy(previousKeyState, keyboardState, keyLength);
	this->dividerX = dividerX;
	this->dividerY = dividerY;
}

input_manager::~input_manager()
{
	delete[] previousKeyState;
	previousKeyState = NULL;
}