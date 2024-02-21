#include "entity.h"
#include "registry.h"
#include "input_manager.h"
#include <algorithm>
#include <numeric>
#include "pixel_simulation.h"
#include "sand.h"
#include "water.h"
#include "acid.h"
#include "smoke.h"
#include "steam.h"
#include "rubber.h"
#include "rock.h"
#include "dirt.h"
#include "particle.h"
#include "explosion.h"
#include "wood.h"
#include "oil.h"


inline int ReverseNumber(int num, int min, int max)
{
	return (max + min) - num;
}

bool pixel_simulation::InBounds(int x, int y)
{
	return x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT;
}

void pixel_simulation::DeleteElement(int x, int y)
{
	if (grid[y][x] == nullptr) return;

	delete grid[y][x];
	grid[y][x] = nullptr;
}

void pixel_simulation::MoveElement(int x, int y, int newX, int newY)
{
	if (!InBounds(newX, newY)) return;

	grid[newY][newX] = grid[y][x];
	grid[y][x] = nullptr;
	
}

void pixel_simulation::MoveElement(int* x, int* y, int newX, int newY)
{
	if (!InBounds(newX, newY)) return;

	grid[newY][newX] = grid[*y][*x];
	grid[*y][*x] = nullptr;
	*x = newX;
	*y = newY;
}

void pixel_simulation::FlipElement(int* ax, int* ay, int bx, int by)
{
	element* holder = grid[*ay][*ax];
	grid[*ay][*ax] = grid[by][bx];
	grid[by][bx] = holder;

	*ay = by;
	*ax = bx;
}

void pixel_simulation::ReplaceElement(int x, int y, element* newElement)
{
	grid[y][x] = newElement;
}

void pixel_simulation::ReplaceElementAndDeleteLast(int x, int y, element* newElement)
{
	delete grid[y][x];
	grid[y][x] = newElement;
}

void pixel_simulation::Init()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			grid[y][x] == nullptr;
		}
	}
}

void pixel_simulation::Update(registry* reg, entity_manager* eManager, input_manager* inputManager, double* deltaTime)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (grid[y][x] == nullptr || grid[y][x]->updated) continue;

			grid[y][x]->Update(deltaTime, this, x, y);
		}
	}
	if (inputManager->MouseButtonDown(input_manager::left))
	{
		for (int y = -PAINT_BRUSH_CIRCLE_RADIUS; y <= PAINT_BRUSH_CIRCLE_RADIUS; y++)
		{
			for (int x = -PAINT_BRUSH_CIRCLE_RADIUS; x <= PAINT_BRUSH_CIRCLE_RADIUS; x++)
			{
				if (x * x + y * y <= PAINT_BRUSH_CIRCLE_RADIUS * PAINT_BRUSH_CIRCLE_RADIUS)
				{
					if (currentElementIndex == 0)
					{
						CreateElement<sand>(inputManager->MousePos().x + x, inputManager->MousePos().y + y);
					}
					else if (currentElementIndex == 1)
					{
						CreateElement<water>(inputManager->MousePos().x + x, inputManager->MousePos().y + y);
					}
					else if (currentElementIndex == 2)
					{
						CreateElement<acid>(inputManager->MousePos().x + x, inputManager->MousePos().y + y);
					}
					else if (currentElementIndex == 3)
					{
						CreateElement<smoke>(inputManager->MousePos().x + x, inputManager->MousePos().y + y);
					}
					else if (currentElementIndex == 4)
					{
						CreateElement<steam>(inputManager->MousePos().x + x, inputManager->MousePos().y + y);
					}
					else if (currentElementIndex == 5)
					{
						CreateElement<rubber>(inputManager->MousePos().x + x, inputManager->MousePos().y + y);
					}
					else if (currentElementIndex == 6)
					{
						CreateElement<rock>(inputManager->MousePos().x + x, inputManager->MousePos().y + y);
					}
					else if (currentElementIndex == 7)
					{
						CreateElement<dirt>(inputManager->MousePos().x + x, inputManager->MousePos().y + y);
					}
					else if (currentElementIndex == 8)
					{
						CreateElement<wood>(inputManager->MousePos().x + x, inputManager->MousePos().y + y);
					}
					else if (currentElementIndex == 9)
					{
						CreateElement<oil>(inputManager->MousePos().x + x, inputManager->MousePos().y + y);
					}
				}
			}
		}
	}
	else if (inputManager->MouseButtonDown(input_manager::right))
	{
		for (int y = -ERASE_BRUSH_CIRCLE_RADIUS; y <= ERASE_BRUSH_CIRCLE_RADIUS; y++)
		{
			for (int x = -ERASE_BRUSH_CIRCLE_RADIUS; x <= ERASE_BRUSH_CIRCLE_RADIUS; x++)
			{
				if (InBounds(x + inputManager->MousePos().x, y + inputManager->MousePos().y) && x * x + y * y <= ERASE_BRUSH_CIRCLE_RADIUS * ERASE_BRUSH_CIRCLE_RADIUS)
				{
					DeleteElement(inputManager->MousePos().x + x, inputManager->MousePos().y + y);
				}
			}
		}

	}
	//else if (inputManager->MouseButtonPressed(input_manager::forward))
	//{
	//	for (int y = -PARTICLE_BRUSH_CIRCLE_RADIUS; y <= PARTICLE_BRUSH_CIRCLE_RADIUS; y++)
	//	{
	//		for (int x = -PARTICLE_BRUSH_CIRCLE_RADIUS; x <= PARTICLE_BRUSH_CIRCLE_RADIUS; x++)
	//		{
	//			if (x * x + y * y <= PARTICLE_BRUSH_CIRCLE_RADIUS * PARTICLE_BRUSH_CIRCLE_RADIUS)
	//			{
	//				if (InBounds(x + inputManager->MousePos().x, y + inputManager->MousePos().y) && grid[y + inputManager->MousePos().y][x + inputManager->MousePos().x] != nullptr && !dynamic_cast<particle*>(grid[y + inputManager->MousePos().y][x + inputManager->MousePos().x]))
	//				{
	//					glm::vec2 velDif = glm::vec2(0, 0);
	//					float distSqr = x * x + y * y;
	//					float realStrength = (ReverseNumber(distSqr, 0, (float)PARTICLE_BRUSH_CIRCLE_RADIUS * (float)PARTICLE_BRUSH_CIRCLE_RADIUS) / ((float)PARTICLE_BRUSH_CIRCLE_RADIUS * (float)PARTICLE_BRUSH_CIRCLE_RADIUS)) * 150.f;
	//
	//					if (x != 0)velDif.x = x > 0 ? (float)ReverseNumber(std::abs(x), 1, (float)PARTICLE_BRUSH_CIRCLE_RADIUS) / (float)PARTICLE_BRUSH_CIRCLE_RADIUS + ((float)(rand() % 101 - 50) / 100.f)
	//						: -(float)ReverseNumber(std::abs(x), 1, (float)PARTICLE_BRUSH_CIRCLE_RADIUS) / (float)PARTICLE_BRUSH_CIRCLE_RADIUS + ((float)(rand() % 101 - 50) / 100.f);
	//					if (y != 0)velDif.y = y > 0 ? (float)ReverseNumber(std::abs(y), 1, (float)PARTICLE_BRUSH_CIRCLE_RADIUS) / (float)PARTICLE_BRUSH_CIRCLE_RADIUS + ((float)(rand() % 101 - 50) / 100.f)
	//						: -(float)ReverseNumber(std::abs(y), 1, (float)PARTICLE_BRUSH_CIRCLE_RADIUS) / (float)PARTICLE_BRUSH_CIRCLE_RADIUS + ((float)(rand() % 101 - 50) / 100.f);
	//
	//					velDif *= realStrength;
	//
	//					grid[y + inputManager->MousePos().y][x + inputManager->MousePos().x]->ReplaceAsParticle(velDif, this, x + inputManager->MousePos().x, y + inputManager->MousePos().y);
	//				}
	//			}
	//		}
	//	}
	//}
	else if (inputManager->MouseButtonPressed(input_manager::forward))
	{
		if (grid[inputManager->MousePos().y][inputManager->MousePos().x] != nullptr)
		{
			grid[inputManager->MousePos().y][inputManager->MousePos().x]->onFire = true;
		}
	}
	else if (inputManager->MouseButtonPressed(input_manager::back))
	{
		explosion* e = new explosion{ EXPLOSION_BRUSH_CIRCLE_RADIUS, 10, 80.f, 0.9f, 200.f, inputManager->MousePos().x , inputManager->MousePos().y, 16, 60, 25.f, 10, 80, 150.f };
		e->ApplyExplosion(this);
	}

	if (inputManager->KeyPressed(SDL_SCANCODE_TAB))
	{
		currentElementIndex = (currentElementIndex + 1) % 10;
		if (currentElementIndex == 0)
		{
			currentElementColor = SDL_Color{ 230, 187, 108 , 255 };
		}
		else if (currentElementIndex == 1)
		{
			currentElementColor = SDL_Color{ 18, 40, 204, 155 };
		}
		else if (currentElementIndex == 2)
		{
			currentElementColor = SDL_Color{ 177, 237, 116, 155 };
		}
		else if (currentElementIndex == 3)
		{
			currentElementColor = SDL_Color{ 132, 136, 132, 170 };
		}
		else if (currentElementIndex == 4)
		{
			currentElementColor = SDL_Color{ 255, 255, 255, 50 };
		}
		else if (currentElementIndex == 5)
		{
			currentElementColor = SDL_Color{ 255, 56, 245, 255 };
		}
		else if (currentElementIndex == 6)
		{
			currentElementColor = SDL_Color{ 69, 69, 69, 255 };
		}
		else if (currentElementIndex == 7)
		{
			currentElementColor = SDL_Color{ 135, 54, 20, 255 };
		}
		else if (currentElementIndex == 8)
		{
			currentElementColor = SDL_Color{ 138, 92, 52, 255 };
		}
		else if (currentElementIndex == 9)
		{
			currentElementColor = SDL_Color{ 51, 33, 19, 255 };
		}
	}


	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (grid[y][x] == nullptr) continue;

			grid[y][x]->updated = false;
		}
	}
}

void pixel_simulation::Render(registry* reg, entity_manager* eManager, SDL_Renderer* renderer, input_manager* inputManager)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (grid[y][x] == nullptr) continue;

			SDL_SetRenderDrawColor(renderer, grid[y][x]->color.r, grid[y][x]->color.g, grid[y][x]->color.b, grid[y][x]->color.a);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	SDL_SetRenderDrawColor(renderer, currentElementColor.r, currentElementColor.g, currentElementColor.b, currentElementColor.a);
	for (int y = -PAINT_BRUSH_CIRCLE_RADIUS; y <= PAINT_BRUSH_CIRCLE_RADIUS; y++)
	{
		for (int x = -PAINT_BRUSH_CIRCLE_RADIUS; x <= PAINT_BRUSH_CIRCLE_RADIUS; x++)
		{
			if (x * x + y * y <= PAINT_BRUSH_CIRCLE_RADIUS * PAINT_BRUSH_CIRCLE_RADIUS)
			{
				SDL_RenderDrawPoint(renderer, x + inputManager->MousePos().x, y + inputManager->MousePos().y);
			}
		}
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}
