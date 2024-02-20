#pragma once
#include "glm/glm.hpp"
#include "SDL.h"
#include <vector>
#include "element.h"

class pixel_simulation
{
public:
	bool InBounds(int x, int y);

	void DeleteElement(int x, int y);

	template <typename T>
	element* CreateElement(int x, int y)
	{
		if (!InBounds(x, y) || grid[y][x] != nullptr)
		{ 
			return nullptr; 
		}

		T* t = new T();
		t->id = particleCount++;
		grid[y][x] = t;
		return t;
	}

	void MoveElement(int x, int y, int newX, int newY);
	void MoveElement(int* x, int* y, int newX, int newY);

	void FlipElement(int* ax, int* ay, int bx, int by);

	void ReplaceElement(int x, int y, element* newElement);
	void ReplaceElementAndDeleteLast(int x, int y, element* newElement);

	template <typename T>
	void ReplaceElementAndDeleteLast(int x, int y)
	{
		delete grid[y][x];
		grid[y][x] = CreateElement<T>(x, y);
	}

	void Init();
	void Update(class registry* reg ,class entity_manager* eManager, class input_manager* inputManager, double* deltaTime);
	void Render(class registry* reg, class entity_manager* eManager, SDL_Renderer* renderer, class input_manager* inputManager);

	static const int WIDTH = 384, HEIGHT = 216;

	element* grid[HEIGHT][WIDTH];
	const int PAINT_BRUSH_CIRCLE_RADIUS = 6;
	const int ERASE_BRUSH_CIRCLE_RADIUS = 1;
	const int PARTICLE_BRUSH_CIRCLE_RADIUS = 50;
	const int EXPLOSION_BRUSH_CIRCLE_RADIUS = 50;

	int particleCount = 0;

	//DEBUG
	SDL_Color currentElementColor = { 230, 187, 108, 255 };
	int currentElementIndex = 0;

};