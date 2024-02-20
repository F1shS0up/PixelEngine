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

//void pixel_simulation::Update(registry* reg, entity_manager* eManager, input_manager* inputManager, double* deltaTime)
//{
//	if (inputManager->MouseButtonDown(input_manager::left))
//	{
//		spawnDelay += *deltaTime;
//		if (spawnDelay >= SPAWN_DELAY)
//		{
//			for (int y = -BRUSH_CIRCLE_RADIUS; y <= BRUSH_CIRCLE_RADIUS; y++)
//			{
//				for (int x = -BRUSH_CIRCLE_RADIUS; x <= BRUSH_CIRCLE_RADIUS; x++)
//				{
//					if (x * x + y * y <= BRUSH_CIRCLE_RADIUS * BRUSH_CIRCLE_RADIUS)
//					{
//						CreatePixel(inputManager->MousePos().x - BOUNDS.x + x, inputManager->MousePos().y - BOUNDS.y + y, glm::vec2(0, 0), current);
//					}
//				}
//			}
//			spawnDelay = 0;
//		}
//	}
//	else if (inputManager->MouseButtonDown(input_manager::right))
//	{
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x, inputManager->MousePos().y - BOUNDS.y);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x, inputManager->MousePos().y - BOUNDS.y + 1);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x, inputManager->MousePos().y - BOUNDS.y - 1);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x + 1, inputManager->MousePos().y - BOUNDS.y);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x - 1, inputManager->MousePos().y - BOUNDS.y);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x + 1, inputManager->MousePos().y - BOUNDS.y + 1);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x + 1, inputManager->MousePos().y - BOUNDS.y - 1);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x - 1, inputManager->MousePos().y - BOUNDS.y + 1);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x - 1, inputManager->MousePos().y - BOUNDS.y - 1);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x + 2, inputManager->MousePos().y - BOUNDS.y);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x - 2, inputManager->MousePos().y - BOUNDS.y);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x, inputManager->MousePos().y - BOUNDS.y + 2);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x, inputManager->MousePos().y - BOUNDS.y - 2);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x + 2, inputManager->MousePos().y - BOUNDS.y + 1);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x + 2, inputManager->MousePos().y - BOUNDS.y - 1);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x - 2, inputManager->MousePos().y - BOUNDS.y + 1);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x - 2, inputManager->MousePos().y - BOUNDS.y - 1);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x + 1, inputManager->MousePos().y - BOUNDS.y + 2);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x + 1, inputManager->MousePos().y - BOUNDS.y - 2);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x - 1, inputManager->MousePos().y - BOUNDS.y + 2);
//		DeletePixel(inputManager->MousePos().x - BOUNDS.x - 1, inputManager->MousePos().y - BOUNDS.y - 2);
//		
//	}
//	else if (inputManager->MouseButtonDown(input_manager::middle))
//	{
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x, inputManager->MousePos().y - BOUNDS.y, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x, inputManager->MousePos().y - BOUNDS.y + 1, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x, inputManager->MousePos().y - BOUNDS.y - 1, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x + 1, inputManager->MousePos().y - BOUNDS.y, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x - 1, inputManager->MousePos().y - BOUNDS.y, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x + 1, inputManager->MousePos().y - BOUNDS.y + 1, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x + 1, inputManager->MousePos().y - BOUNDS.y - 1, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x - 1, inputManager->MousePos().y - BOUNDS.y + 1, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x - 1, inputManager->MousePos().y - BOUNDS.y - 1, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x + 2, inputManager->MousePos().y - BOUNDS.y, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x - 2, inputManager->MousePos().y - BOUNDS.y, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x, inputManager->MousePos().y - BOUNDS.y + 2, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x, inputManager->MousePos().y - BOUNDS.y - 2, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x + 2, inputManager->MousePos().y - BOUNDS.y + 1, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x + 2, inputManager->MousePos().y - BOUNDS.y - 1, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x - 2, inputManager->MousePos().y - BOUNDS.y + 1, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x - 2, inputManager->MousePos().y - BOUNDS.y - 1, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x + 1, inputManager->MousePos().y - BOUNDS.y + 2, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x + 1, inputManager->MousePos().y - BOUNDS.y - 2, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x - 1, inputManager->MousePos().y - BOUNDS.y + 2, current);
//		DeletePixelOnlyOfType(inputManager->MousePos().x - BOUNDS.x - 1, inputManager->MousePos().y - BOUNDS.y - 2, current);
//	}
//	else
//	{
//		spawnDelay = 0;
//	}
//
//	if (inputManager->KeyPressed(SDL_SCANCODE_TAB))
//	{
//		current = (physicalpixel_type)((current + 1) % 11);
//	}
//	
//	
//	for (int y = BOUNDS.h - 1; y > -1; y--)
//	{
//		for (int x = 0; x < BOUNDS.w; x++)
//		{
//			if (grid[y][x] == nullptr || grid[y][x]->updated == true)
//			{
//				continue;
//			}
//			else if (grid[y][x]->type == rock)
//			{
//				grid[y][x]->updated = true;
//				continue;
//			}
//			physicalpixel_component* c = grid[y][x];
//			c->updated = true;
//
//
//			if (c->type == sand)
//			{
//				UpdateSand(x, y, c, deltaTime);
//			}
//			else if (c->type == water)
//			{
//				UpdateWater(x, y, c, deltaTime);
//			}
//			else if (c->type == smoke)
//			{
//				UpdateSmoke(x, y, c, deltaTime);
//			}
//			else if (c->type == fire)
//			{
//				UpdateFire(x, y, (fire_s*)c, deltaTime);
//			}
//			else if (c->type == wood)
//			{
//				UpdateWood(x, y, (flamable_s*)c, deltaTime);
//			}
//			else if (c->type == gun_powder)
//			{
//				UpdateGunPowder(x, y, (flamable_s*)c, deltaTime);
//			}
//			else if (c->type == steam)
//			{
//				UpdateSteam(x, y, c, deltaTime);
//			}
//			else if (c->type == magma)
//			{
//				UpdateMagma(x, y, c, deltaTime);
//			}
//			else if (c->type == string)
//			{
//				UpdateString(x, y, (flamable_s*)c, deltaTime);
//			}
//		}
//	}
//	for (int y = BOUNDS.h - 1; y > -1; y--)
//	{
//		for (int x = 0; x < BOUNDS.w; x++)
//		{
//			if(grid[y][x])grid[y][x]->updated = false;
//		}
//	}
//
//}
//
//void pixel_simulation::Render(registry* reg, entity_manager* eManager, SDL_Renderer* renderer, input_manager* inputManager)
//{
//	for (int y = 0; y < BOUNDS.h; y++)
//	{
//		for (int x = 0; x < BOUNDS.w; x++)
//		{
//			if (grid[y][x] == nullptr) continue;
//			physicalpixel_component* c = grid[y][x];
//
//			SDL_SetRenderDrawColor(renderer, c->color.r, c->color.g, c->color.b, c->color.a);
//			SDL_RenderDrawPoint(renderer, x, y);
//		}
//	}
//	SDL_SetRenderDrawColor(renderer, 60, 141, 240, 255);
//	SDL_RenderDrawRect(renderer, new SDL_Rect{ BOUNDS.x - 1, BOUNDS.y - 1, BOUNDS.w + 2, BOUNDS.h + 2 });
//	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
//
//	//DEBUG
//	{
//		if (current == sand)
//		{
//			SDL_SetRenderDrawColor(renderer, SAND_COLOR.r, SAND_COLOR.g, SAND_COLOR.b, 255);
//		}
//		else if (current == smoke)
//		{
//			SDL_SetRenderDrawColor(renderer, SMOKE_COLOR.r, SMOKE_COLOR.g, SMOKE_COLOR.b, 255);
//		}
//		else if (current == water)
//		{
//			SDL_SetRenderDrawColor(renderer, WATER_COLOR.r, WATER_COLOR.g, WATER_COLOR.b, 255);
//		}
//		else if (current == rock)
//		{
//			SDL_SetRenderDrawColor(renderer, ROCK_COLOR.r, ROCK_COLOR.g, ROCK_COLOR.b, 255);
//		}
//		else if (current == wood)
//		{
//			SDL_SetRenderDrawColor(renderer, WOOD_COLOR.r, WOOD_COLOR.g, WOOD_COLOR.b, 255);
//		}
//		else if (current == fire)
//		{
//			SDL_SetRenderDrawColor(renderer, (FIRE_COLOR_MAX.r + FIRE_COLOR_MIN.r) / 2, (FIRE_COLOR_MAX.g + FIRE_COLOR_MIN.g) / 2, (FIRE_COLOR_MAX.b + FIRE_COLOR_MIN.b) / 2, 255);
//		}
//		else if (current == gun_powder)
//		{
//			SDL_SetRenderDrawColor(renderer, GUN_POWDER_COLOR.r, GUN_POWDER_COLOR.g, GUN_POWDER_COLOR.b, 255);
//		}
//		else if (current == steam)
//		{
//			SDL_SetRenderDrawColor(renderer, STEAM_COLOR.r, STEAM_COLOR.g, STEAM_COLOR.b, 255);
//		}
//		else if (current == magma)
//		{
//			SDL_SetRenderDrawColor(renderer, MAGMA_COLOR.r, MAGMA_COLOR.g, MAGMA_COLOR.b, 255);
//		}
//		else if (current == obsidian)
//		{
//			SDL_SetRenderDrawColor(renderer, 
//				(OBSIDIAN_COLOR_MAX.r + OBSIDIAN_COLOR_MIN.r) / 2, 
//				(OBSIDIAN_COLOR_MAX.g + OBSIDIAN_COLOR_MIN.g) / 2,
//				(OBSIDIAN_COLOR_MAX.b + OBSIDIAN_COLOR_MIN.b) / 2, 255);
//		}
//		else if (current == string)
//		{
//			SDL_SetRenderDrawColor(renderer, STRING_COLOR.r, STRING_COLOR.g, STRING_COLOR.b, 255);
//		}
//		for (int y = -BRUSH_CIRCLE_RADIUS; y <= BRUSH_CIRCLE_RADIUS; y++)
//		{
//			for (int x = -BRUSH_CIRCLE_RADIUS; x <= BRUSH_CIRCLE_RADIUS; x++)
//			{
//				if (x * x + y * y <= BRUSH_CIRCLE_RADIUS * BRUSH_CIRCLE_RADIUS)
//				{
//					SDL_RenderDrawPoint(renderer, inputManager->MousePos().x - BOUNDS.x + x, inputManager->MousePos().y - BOUNDS.y + y);
//				}
//			}
//		}
//	}
//}
//
//void pixel_simulation::UpdateFlamable(flamable_s* c, double* deltaTime, int x, int y, bool& retFlag)
//{
//	retFlag = true;
//	if (c->onFire)
//	{
//		c->timeFromLastSpreading += *deltaTime;
//		bool spread = false;
//		if (y + 1 <= BOUNDS.h - 1 && grid[y + 1][x] != nullptr)
//		{
//			if (grid[y + 1][x]->type == water)
//			{
//				c->onFire = false;
//				c->timeOnFire = 0;
//				c->timeFromLastSpreading = 0;
//				if (c->type == wood)
//				{
//					c->color = WOOD_COLOR;
//				}
//				else if (c->type == gun_powder)
//				{
//					c->color = GUN_POWDER_COLOR;
//				}
//				else if (c->type == string)
//				{
//					c->color = STRING_COLOR;
//				}
//				return;
//			}
//			else if (c->timeFromLastSpreading >= c->fireSpreadDelay && IsFlamable(x, y + 1) && !((flamable_s*)grid[y + 1][x])->onFire)
//			{
//				((flamable_s*)grid[y + 1][x])->onFire = true;
//				spread = true;
//			}
//		}
//		if (y - 1 >= 0 && grid[y - 1][x] != nullptr)
//		{
//			if (grid[y - 1][x]->type == water)
//			{
//				c->onFire = false;
//				c->timeOnFire = 0;
//				c->timeFromLastSpreading = 0;
//				if (c->type == wood)
//				{
//					c->color = WOOD_COLOR;
//				}
//				else if (c->type == gun_powder)
//				{
//					c->color = GUN_POWDER_COLOR;
//				}
//				else if (c->type == string)
//				{
//					c->color = STRING_COLOR;
//				}
//				return;
//			}
//			else if (c->timeFromLastSpreading >= c->fireSpreadDelay && IsFlamable(x, y - 1) && !((flamable_s*)grid[y - 1][x])->onFire)
//			{
//				((flamable_s*)grid[y - 1][x])->onFire = true;
//				spread = true;
//			}
//		}
//		if (x + 1 <= BOUNDS.w - 1 && grid[y][x + 1] != nullptr)
//		{
//			if (grid[y][x + 1]->type == water)
//			{
//				c->onFire = false;
//				c->timeOnFire = 0;
//				c->timeFromLastSpreading = 0;
//				if (c->type == wood)
//				{
//					c->color = WOOD_COLOR;
//				}
//				else if (c->type == gun_powder)
//				{
//					c->color = GUN_POWDER_COLOR;
//				}
//				else if (c->type == string)
//				{
//					c->color = STRING_COLOR;
//				}
//				return;
//			}
//			else if (c->timeFromLastSpreading >= c->fireSpreadDelay && IsFlamable(x + 1, y) && !((flamable_s*)grid[y][x + 1])->onFire)
//			{
//				((flamable_s*)grid[y][x + 1])->onFire = true;
//				spread = true;
//			}
//		}
//		if (x - 1 >= 0 && grid[y][x - 1] != nullptr)
//		{
//			if (grid[y][x - 1]->type == water)
//			{
//				c->onFire = false;
//				c->timeOnFire = 0;
//				c->timeFromLastSpreading = 0;
//				if (c->type == wood)
//				{
//					c->color = WOOD_COLOR;
//				}
//				else if (c->type == gun_powder)
//				{
//					c->color = GUN_POWDER_COLOR;
//				}
//				else if (c->type == string)
//				{
//					c->color = STRING_COLOR;
//				}
//				return;
//			}
//			else if (c->timeFromLastSpreading >= c->fireSpreadDelay && IsFlamable(x - 1, y) && !((flamable_s*)grid[y][x - 1])->onFire)
//			{
//				((flamable_s*)grid[y][x - 1])->onFire = true;
//				spread = true;
//			}
//		}
//
//		if (spread)
//		{
//			c->timeFromLastSpreading = 0;
//		}
//
//
//		c->color = SDL_Color{
//			(Uint8)(std::rand() % (FIRE_COLOR_MAX.r - FIRE_COLOR_MIN.r) + FIRE_COLOR_MIN.r),
//			(Uint8)(std::rand() % (FIRE_COLOR_MAX.g - FIRE_COLOR_MIN.g) + FIRE_COLOR_MIN.g),
//			(Uint8)(std::rand() % (FIRE_COLOR_MAX.b - FIRE_COLOR_MIN.b) + FIRE_COLOR_MIN.b), 255 };
//		c->timeOnFire += *deltaTime;
//		if (c->timeOnFire >= c->vaporizationTime)
//		{
//			DeletePixel(x, y);
//			CreatePixel(x, y, glm::vec2(0, 0), smoke);
//		}
//	}
//	retFlag = false;
//}
//
//void pixel_simulation::SetAroundOnFire(int x, int y)
//{
//	if (y + 1 <= BOUNDS.h - 1 && grid[y + 1][x] != nullptr)
//	{
//		if (grid[y + 1][x]->type == wood || grid[y + 1][x]->type == gun_powder || grid[y + 1][x]->type == string)
//		{
//			((flamable_s*)grid[y + 1][x])->onFire = true;
//		}
//		else if (grid[y + 1][x]->type == water)
//		{
//			DeletePixel(x, y + 1);
//			CreatePixel(x, y + 1, glm::vec2(0, 0), steam);
//		}
//	}
//	if (y - 1 >= 0 && grid[y - 1][x] != nullptr)
//	{
//		if (grid[y - 1][x]->type == wood || grid[y - 1][x]->type == gun_powder || grid[y - 1][x]->type == string)
//		{
//			((flamable_s*)grid[y - 1][x])->onFire = true;
//		}
//		else if (grid[y - 1][x]->type == water)
//		{
//			DeletePixel(x, y - 1);
//			CreatePixel(x, y - 1, glm::vec2(0, 0), steam);
//		}
//	}
//	if (x + 1 <= BOUNDS.w - 1 && grid[y][x + 1] != nullptr)
//	{
//		if (grid[y][x + 1]->type == wood || grid[y][x + 1]->type == gun_powder || grid[y][x + 1]->type == string)
//		{
//			((flamable_s*)grid[y][x + 1])->onFire = true;
//		}
//		else if (grid[y][x + 1]->type == water)
//		{
//			DeletePixel(x + 1, y);
//			CreatePixel(x + 1, y, glm::vec2(0, 0), steam);
//		}
//	}
//	if (x - 1 >= 0 && grid[y][x - 1] != nullptr)
//	{
//		if (grid[y][x - 1]->type == wood || grid[y][x - 1]->type == gun_powder || grid[y][x - 1]->type == string)
//		{
//			((flamable_s*)grid[y][x - 1])->onFire = true;
//		}
//		else if (grid[y][x - 1]->type == water)
//		{
//			DeletePixel(x - 1, y);
//			CreatePixel(x - 1, y, glm::vec2(0, 0), steam);
//		}
//	}
//}
//
//void pixel_simulation::UpdateSand(int x, int y, physicalpixel_component* c, double* deltaTime)
//{
//	c->velocity += glm::vec2(0, GRAVITY * 1.6 * *deltaTime);
//	c->holdY += c->velocity.y * *deltaTime;
//	int upcomingY = y + std::floor(c->holdY);
//	c->holdY = c->holdY - std::floor(c->holdY);
//	int yDir = upcomingY - y;
//	int yStep = c->velocity.y > 0 ? 1 : -1;
//
//	for (int step = 1; step <= std::abs(yDir); step++)
//	{
//		int newY = yStep + y;
//		if (!InBounds(x, newY))
//		{
//			c->velocity.y = 0;
//			break;
//		}
//
//		if (grid[newY][x] != nullptr)
//		{
//			if (grid[newY][x]->type == water)
//			{
//				c->velocity.y *= 0.5;
//				FlipPixels_Update(&x, &y, x, newY);
//			}
//			else if (grid[newY][x]->type == smoke)
//			{
//				c->velocity.y *= 0.5; // slow a bit when smoke is there
//				grid[newY][x]->velocity.y = c->velocity.y;
//				FlipPixels_Update(&x, &y, x, newY);
//			}
//			else
//			{
//				int incrementX = rand() % 3 - 1;
//				if (InBounds(x - incrementX, newY))
//				{
//					if (InBounds(x + incrementX, newY) && grid[newY][x + incrementX] == nullptr)
//					{
//						MovePixel_Update(&x, &y, x + incrementX, newY);
//					}
//					else if (InBounds(x - incrementX, newY) && grid[newY][x - incrementX] == nullptr)
//					{
//						MovePixel_Update(&x, &y, x - incrementX, newY);
//					}
//					else
//					{
//						c->velocity.y = 0;
//						break;
//					}
//				}
//				else
//				{
//					c->velocity.y = 0;
//					break;
//				}
//			}
//		}
//		else
//		{
//			MovePixel_Update(&x, &y, x, newY);
//		}
//	}
//}
//
//void pixel_simulation::UpdateWater(int x, int y, physicalpixel_component* c, double* deltaTime)
//{
//	c->velocity += glm::vec2(0, GRAVITY * *deltaTime);
//	c->holdY += c->velocity.y * *deltaTime;
//	int upcomingY = y + std::floor(c->holdY);
//	c->holdY = c->holdY - std::floor(c->holdY);
//	int yStepCount = std::abs(upcomingY - y);
//	int yStep = c->velocity.y > 0 ? 1 : -1;
//	
//	for (int step = 1; step <= yStepCount; step++)
//	{
//		int newY = yStep + y;
//
//		if (!InBounds(x, newY))
//		{
//			c->velocity.y = 0;
//			break;
//		}
//
//		if (grid[newY][x] != nullptr)
//		{
//			if (grid[newY][x]->type == smoke)
//			{
//				c->velocity.y *= 0.5; // slow a bit when smoke is there
//				grid[newY][x]->velocity.y = c->velocity.y;
//				FlipPixels_Update(&x, &y, x, newY);
//			}
//			else
//			{
//				int incrementX = rand() % 3 - 1;
//				if (InBounds(x - incrementX, newY))
//				{
//					if (grid[newY][x + incrementX] == nullptr)
//					{
//						MovePixel_Update(&x, &y, x + incrementX, newY);
//					}
//					else if (grid[newY][x - incrementX] == nullptr)
//					{
//						MovePixel_Update(&x, &y, x - incrementX, newY);
//					}
//					else if (grid[y][x + incrementX] == nullptr)
//					{
//						for (int waterStep = 1; waterStep <= WATER_DISPERTION_RATE; waterStep++)
//						{
//							int newX = x + incrementX;
//							if (!InBounds(x + incrementX, y))
//							{
//								break;
//							}
//
//							if (grid[y][newX] != nullptr && grid[y][newX]->type == water)
//							{
//								continue;
//							}
//							else if (grid[y][newX] == nullptr)
//							{
//								MovePixel_Update(&x, &y, newX, y);
//							}
//							else
//							{
//								break;
//							}
//						}
//					}
//					else if (grid[y][x - incrementX] == nullptr)
//					{
//						for (int waterStep = 1; waterStep <= WATER_DISPERTION_RATE; waterStep++)
//						{
//							int newX = x - incrementX;
//							if (!InBounds(x - incrementX, y))
//							{
//								break;
//							}
//
//							if (grid[y][newX] != nullptr && grid[y][newX]->type == water)
//							{
//								continue;
//							}
//							else if (grid[y][newX] == nullptr)
//							{
//								MovePixel_Update(&x, &y, newX, y);
//							}
//							else
//							{
//								break;
//							}
//						}
//					}
//					else
//					{
//						c->velocity.y = 0;
//						c->falling = false;
//						break;
//					}
//				}
//				else
//				{
//					c->velocity.y = 0;
//					c->falling = false;
//					break;
//				}
//			}
//		}
//		else
//		{
//			MovePixel_Update(&x, &y, x, newY);
//		}
//	}
//}
//
//void pixel_simulation::UpdateSmoke(int x, int y, physicalpixel_component* c, double* deltaTime)
//{
//	c->velocity = glm::vec2(std::clamp<float>(c->velocity.x, -10, 10), std::clamp<float>(c->velocity.y - GRAVITY / 4 * *deltaTime, -150, 150));
//	c->holdY += c->velocity.y * *deltaTime;
//	int upcomingY = y + std::floor(c->holdY);
//	c->holdY = c->holdY - std::floor(c->holdY);
//	int yStepCount = std::abs(upcomingY - y);
//	int yStep = c->velocity.y > 0 ? 1 : -1;
//
//	for (int step = 1; step <= yStepCount; step++)
//	{
//		int newY = yStep + y;
//
//		if (!InBounds(x, newY))
//		{
//			c->velocity.y = 0;
//			c->falling = false;
//			break;
//		}
//
//		if (grid[newY][x] != nullptr)
//		{
//			if (grid[newY][x]->type == smoke)
//			{
//				c->velocity.y *= 0.5; // slow a bit when smoke is there
//				grid[newY][x]->velocity.y = c->velocity.y;
//				FlipPixels_Update(&x, &y, x, newY);
//			}
//			else
//			{
//				int incrementX = rand() % 3 - 1;
//				if (InBounds(x - incrementX, newY))
//				{
//					if (grid[newY][x + incrementX] == nullptr)
//					{
//						MovePixel_Update(&x, &y, x + incrementX, newY);
//					}
//					else if (grid[newY][x - incrementX] == nullptr)
//					{
//						MovePixel_Update(&x, &y, x - incrementX, newY);
//					}
//					else if (grid[y][x + incrementX] == nullptr)
//					{
//						c->falling = false;
//						for (int waterStep = 1; waterStep <= WATER_DISPERTION_RATE; waterStep++)
//						{
//							int newX = x + incrementX;
//							if (!InBounds(x + incrementX, y))
//							{
//								break;
//							}
//
//							if (grid[y][newX] != nullptr && grid[y][newX]->type == water)
//							{
//								continue;
//							}
//							else if (grid[y][newX] == nullptr)
//							{
//								MovePixel_Update(&x, &y, newX, y);
//							}
//							else
//							{
//								break;
//							}
//						}
//					}
//					else if (grid[y][x - incrementX] == nullptr)
//					{
//						c->falling = false;
//						for (int waterStep = 1; waterStep <= WATER_DISPERTION_RATE; waterStep++)
//						{
//							int newX = x - incrementX;
//							if (!InBounds(x - incrementX, y))
//							{
//								break;
//							}
//
//							if (grid[y][newX] != nullptr && grid[y][newX]->type == water)
//							{
//								continue;
//							}
//							else if (grid[y][newX] == nullptr)
//							{
//								MovePixel_Update(&x, &y, newX, y);
//							}
//							else
//							{
//								break;
//							}
//						}
//					}
//					else
//					{
//						c->velocity.y = 0;
//						c->falling = false;
//						break;
//					}
//				}
//				else
//				{
//					c->velocity.y = 0;
//					c->falling = false;
//					break;
//				}
//			}
//		}
//		else
//		{
//			MovePixel_Update(&x, &y, x, newY);
//		}
//	}
//}
//
//void pixel_simulation::UpdateFire(int x, int y, fire_s* c, double* deltaTime)
//{
//	c->lifeTime += *deltaTime;
//	srand(c->lifeTime * 1000 + *deltaTime * 10000 + c->id * 10);
//
//	c->color = SDL_Color{ 
//		(Uint8)((std::rand() % (FIRE_COLOR_MAX.r - FIRE_COLOR_MIN.r) + FIRE_COLOR_MIN.r) * std::clamp<float>((-(c->lifeTime / c->fireLifeTime) + 1) / POINT_OF_FIRE_DISAPEARING, 0, 1)), 
//		(Uint8)((std::rand() % (FIRE_COLOR_MAX.g - FIRE_COLOR_MIN.g) + FIRE_COLOR_MIN.g) * std::clamp<float>((-(c->lifeTime / c->fireLifeTime) + 1) / POINT_OF_FIRE_DISAPEARING, 0, 1)),
//		(Uint8)((std::rand() % (FIRE_COLOR_MAX.b - FIRE_COLOR_MIN.b) + FIRE_COLOR_MIN.b) * std::clamp<float>((-(c->lifeTime / c->fireLifeTime) + 1) / POINT_OF_FIRE_DISAPEARING, 0, 1)), (Uint8)(255 * std::clamp<float>((-(c->lifeTime / c->fireLifeTime) + 1) / POINT_OF_FIRE_DISAPEARING, 0, 1)) };
//
//	if (c->lifeTime >= c->fireLifeTime)
//	{
//		DeletePixel(x, y);
//	}
//
//	c->velocity = glm::vec2(rand() % 25 - 12, std::clamp<float>(c->velocity.y - GRAVITY / 10 * *deltaTime, -20, 20));
//
//	c->xVelHolder += c->velocity.x * *deltaTime;
//	c->holdY += c->velocity.y * *deltaTime;
//
//	int upcomingX = x + std::floor(c->xVelHolder);
//	int upcomingY = y + std::floor(c->holdY);
//
//	c->xVelHolder = c->xVelHolder - std::floor(c->xVelHolder);
//	c->holdY = c->holdY - std::floor(c->holdY);
//
//	int xStepCount = std::abs(upcomingX - x);
//	int yStepCount = std::abs(upcomingY - y);
//
//	int xStep = c->velocity.x > 0 ? 1 : -1;
//
//	if (xStep != 0 && upcomingX - x != 0)
//	{
//		int newX = x + xStep;
//		if (newX <= BOUNDS.w - 1 && newX >= 0 && grid[y][newX] == nullptr)
//		{
//			MovePixel_Update(&x, &y, newX, y);
//		}
//	}
//
//	int yStep = c->velocity.y > 0 ? 1 : -1;
// 
//	for (int step = 1; step <= yStepCount; step++)
//	{
//		int newY = yStep + y;
//		if (newY > BOUNDS.h - 1)
//		{
//			c->velocity.y = 0;
//			break;
//		}
//		else if (newY < 0)
//		{
//			c->velocity.y = 0;
//			break;
//		}
//
//		if (grid[newY][x] != nullptr)
//		{
//			if (x + 1 <= BOUNDS.w - 1 && grid[newY][x + 1] == nullptr)
//			{
//				MovePixel_Update(&x, &y, x + 1, newY);
//				SetAroundOnFire(x, y);
//			}
//			else if (x - 1 >= 0 && grid[newY][x - 1] == nullptr)
//			{
//				MovePixel_Update(&x, &y, x - 1, newY);
//				SetAroundOnFire(x, y);
//			}
//			else
//			{
//				c->velocity.y = 0;
//				break;
//			}
//
//		}
//		else
//		{
//			MovePixel_Update(&x, &y, x, newY);
//			SetAroundOnFire(x, y);
//		}
//	}
//
//}
//
//void pixel_simulation::UpdateWood(int x, int y, flamable_s* c, double* deltaTime)
//{
//	bool retFlag;
//	UpdateFlamable(c, deltaTime, x, y, retFlag);
//	if (retFlag) return;
//}
//
//void pixel_simulation::UpdateGunPowder(int x, int y, flamable_s* c, double* deltaTime)
//{
//	bool retFlag;
//	UpdateFlamable(c, deltaTime, x, y, retFlag);
//	if (retFlag) return;
//
//	c->velocity += glm::vec2(0, GRAVITY * 1.6 * *deltaTime);
//	c->holdY += c->velocity.y * *deltaTime;
//	int upcomingY = y + std::floor(c->holdY);
//	c->holdY = c->holdY - std::floor(c->holdY);
//	int yDir = upcomingY - y;
//
//	int xStep = c->velocity.x > 0 ? 1 : -1;
//	int yStep = c->velocity.y > 0 ? 1 : -1;
//
//	for (int step = 1; step <= std::abs(yDir); step++)
//	{
//		int newY = yStep + y;
//		if (newY > BOUNDS.h - 1)
//		{
//			c->velocity.y = 0;
//			break;
//		}
//		else if (newY < 0)
//		{
//			c->velocity.y = 0;
//			break;
//		}
//
//		if (grid[newY][x] != nullptr)
//		{
//			if (grid[newY][x]->type == water)
//			{
//				c->velocity.y *= 0.5;
//				FlipPixels_Update(&x, &y, x, newY);
//			}
//			else if (grid[newY][x]->type == smoke)
//			{
//				c->velocity.y *= 0.5; // slow a bit when smoke is there
//				grid[newY][x]->velocity.y = c->velocity.y;
//				FlipPixels_Update(&x, &y, x, newY);
//			}
//			else
//			{
//				if (x + 1 <= BOUNDS.w - 1 && grid[newY][x + 1] == nullptr)
//				{
//					MovePixel_Update(&x, &y, x + 1, newY);
//				}
//				else if (x - 1 >= 0 && grid[newY][x - 1] == nullptr)
//				{
//					MovePixel_Update(&x, &y, x - 1, newY);
//				}
//				else
//				{
//					c->velocity.y = 0;
//					break;
//				}
//			}
//		}
//		else
//		{
//			MovePixel_Update(&x, &y, x, newY);
//		}
//	}
//}
//
//void pixel_simulation::UpdateSteam(int x, int y, physicalpixel_component* c, double* deltaTime)
//{
//	c->velocity = glm::vec2(std::clamp<float>(c->velocity.x, -10, 10), std::clamp<float>(c->velocity.y - GRAVITY / 4 * *deltaTime, -150, 150));
//	c->holdY += c->velocity.y * *deltaTime;
//	int upcomingY = y + std::floor(c->holdY);
//	c->holdY = c->holdY - std::floor(c->holdY);
//	int yStepCount = std::abs(upcomingY - y);
//	int yStep = c->velocity.y > 0 ? 1 : -1;
//
//	if (!c->falling)
//	{
//		if (!InBounds(x, y + 1) || grid[y + 1][x] != nullptr)
//		{
//			int incrementX = rand() % 3 - 1;
//			if (grid[y][x + incrementX] == nullptr)
//			{
//				for (int steamStep = 1; steamStep <= STEAM_DISPERTION_RATE; steamStep++)
//				{
//					int newX = x + incrementX;
//					if (!InBounds(x + incrementX, y))
//					{
//						break;
//					}
//
//					if (grid[y][newX] != nullptr && grid[y][newX]->type == steam)
//					{
//						continue;
//					}
//					else if (grid[y][newX] == nullptr)
//					{
//						MovePixel_Update(&x, &y, newX, y);
//					}
//					else
//					{
//						break;
//					}
//				}
//			}
//			else if (grid[y][x - incrementX] == nullptr)
//			{
//				for (int steamStep = 1; steamStep <= STEAM_DISPERTION_RATE; steamStep++)
//				{
//					int newX = x - incrementX;
//					if (!InBounds(x - incrementX, y))
//					{
//						break;
//					}
//
//					if (grid[y][newX] != nullptr && grid[y][newX]->type == steam)
//					{
//						continue;
//					}
//					else if (grid[y][newX] == nullptr)
//					{
//						MovePixel_Update(&x, &y, newX, y);
//					}
//					else
//					{
//						break;
//					}
//				}
//			}
//		}
//		else if (grid[y + 1][x] == nullptr && InBounds(x, y + 1))
//		{
//			c->falling = true;
//		}
//	}
//	else
//	{
//		for (int step = 1; step <= yStepCount; step++)
//		{
//			int newY = yStep + y;
//
//			if (!InBounds(x, newY))
//			{
//				c->velocity.y = 0;
//				c->falling = false;
//				break;
//			}
//
//			if (grid[newY][x] != nullptr)
//			{
//				if (grid[newY][x]->type == smoke)
//				{
//					c->velocity.y *= 0.5; // slow a bit when smoke is there
//					grid[newY][x]->velocity.y = c->velocity.y;
//					FlipPixels_Update(&x, &y, x, newY);
//				}
//				else
//				{
//					int incrementX = rand() % 3 - 1;
//					if (InBounds(x - incrementX, newY))
//					{
//						if (grid[newY][x + incrementX] == nullptr)
//						{
//							MovePixel_Update(&x, &y, x + incrementX, newY);
//						}
//						else if (grid[newY][x - incrementX] == nullptr)
//						{
//							MovePixel_Update(&x, &y, x - incrementX, newY);
//						}
//						else if (grid[y][x + incrementX] == nullptr)
//						{
//							for (int steamStep = 1; steamStep <= STEAM_DISPERTION_RATE; steamStep++)
//							{
//								int newX = x + incrementX;
//								if (!InBounds(x + incrementX, y))
//								{
//									break;
//								}
//
//								if (grid[y][newX] != nullptr && grid[y][newX]->type == steam)
//								{
//									continue;
//								}
//								else if (grid[y][newX] == nullptr)
//								{
//									MovePixel_Update(&x, &y, newX, y);
//								}
//								else
//								{
//									break;
//								}
//							}
//						}
//						else if (grid[y][x - incrementX] == nullptr)
//						{
//							for (int steamStep = 1; steamStep <= STEAM_DISPERTION_RATE; steamStep++)
//							{
//								int newX = x - incrementX;
//								if (!InBounds(x - incrementX, y))
//								{
//									break;
//								}
//
//								if (grid[y][newX] != nullptr && grid[y][newX]->type == steam)
//								{
//									continue;
//								}
//								else if (grid[y][newX] == nullptr)
//								{
//									MovePixel_Update(&x, &y, newX, y);
//								}
//								else
//								{
//									break;
//								}
//							}
//						}
//						else
//						{
//							c->velocity.y = 0;
//							c->falling = false;
//							break;
//						}
//					}
//					else
//					{
//						c->velocity.y = 0;
//						c->falling = false;
//						break;
//					}
//				}
//			}
//			else
//			{
//				MovePixel_Update(&x, &y, x, newY);
//			}
//		}
//	}
//}
//
//void pixel_simulation::UpdateMagma(int x, int y, physicalpixel_component* c, double* deltaTime)
//{
//	c->velocity += glm::vec2(0, GRAVITY * *deltaTime);
//	c->holdY += c->velocity.y * *deltaTime;
//	int upcomingY = y + std::floor(c->holdY);
//	c->holdY = c->holdY - std::floor(c->holdY);
//	int yStepCount = std::abs(upcomingY - y);
//	int yStep = c->velocity.y > 0 ? 1 : -1;
//
//	if (yStepCount > 0)
//	{
//		SetAroundOnFire(x, y);
//	}
//
//	if (!c->falling)
//	{
//		if (!InBounds(x, y + 1) || grid[y + 1][x] != nullptr)
//		{
//			int incrementX = rand() % 3 - 1;
//			if (grid[y][x + incrementX] == nullptr)
//			{
//				for (int waterStep = 1; waterStep <= WATER_DISPERTION_RATE; waterStep++)
//				{
//					int newX = x + incrementX;
//					if (!InBounds(x + incrementX, y))
//					{
//						break;
//					}
//
//					if (grid[y][newX] != nullptr && grid[y][newX]->type == water)
//					{
//						continue;
//					}
//					else if (grid[y][newX] == nullptr)
//					{
//						MovePixel_Update(&x, &y, newX, y);
//					}
//					else
//					{
//						break;
//					}
//				}
//			}
//			else if (grid[y][x - incrementX] == nullptr)
//			{
//				for (int waterStep = 1; waterStep <= WATER_DISPERTION_RATE; waterStep++)
//				{
//					int newX = x - incrementX;
//					if (!InBounds(x - incrementX, y))
//					{
//						break;
//					}
//
//					if (grid[y][newX] != nullptr && grid[y][newX]->type == water)
//					{
//						continue;
//					}
//					else if (grid[y][newX] == nullptr)
//					{
//						MovePixel_Update(&x, &y, newX, y);
//					}
//					else
//					{
//						break;
//					}
//				}
//			}
//		}
//		else if (grid[y + 1][x] == nullptr && InBounds(x, y + 1))
//		{
//			c->falling = true;
//		}
//	}
//	else
//	{
//		for (int step = 1; step <= yStepCount; step++)
//		{
//			int newY = yStep + y;
//
//			if (!InBounds(x, newY))
//			{
//				c->velocity.y = 0;
//				c->falling = false;
//				break;
//			}
//
//			if (grid[newY][x] != nullptr)
//			{
//				if (grid[newY][x]->type == smoke)
//				{
//					c->velocity.y *= 0.5; // slow a bit when smoke is there
//					grid[newY][x]->velocity.y = c->velocity.y;
//					FlipPixels_Update(&x, &y, x, newY);
//				}
//				else
//				{
//					int incrementX = rand() % 3 - 1;
//					if (InBounds(x - incrementX, newY))
//					{
//						if (grid[newY][x + incrementX] == nullptr)
//						{
//							MovePixel_Update(&x, &y, x + incrementX, newY);
//						}
//						else if (grid[newY][x - incrementX] == nullptr)
//						{
//							MovePixel_Update(&x, &y, x - incrementX, newY);
//						}
//						else if (grid[y][x + incrementX] == nullptr)
//						{
//							c->velocity.y = 0;
//							c->falling = false;
//							for (int magmaStep = 1; magmaStep <= MAGMA_DISPERTION_RATE; magmaStep++)
//							{
//								int newX = x + incrementX;
//								if (!InBounds(x + incrementX, y))
//								{
//									break;
//								}
//
//								if (grid[y][newX] != nullptr && grid[y][newX]->type == water)
//								{
//									continue;
//								}
//								else if (grid[y][newX] == nullptr)
//								{
//									MovePixel_Update(&x, &y, newX, y);
//								}
//								else
//								{
//									break;
//								}
//							}
//							break;
//						}
//						else if (grid[y][x - incrementX] == nullptr)
//						{
//							c->velocity.y = 0;
//							c->falling = false;
//							for (int magmaStep = 1; magmaStep <= MAGMA_DISPERTION_RATE; magmaStep++)
//							{
//								int newX = x - incrementX;
//								if (!InBounds(x - incrementX, y))
//								{
//									break;
//								}
//
//								if (grid[y][newX] != nullptr && grid[y][newX]->type == water)
//								{
//									continue;
//								}
//								else if (grid[y][newX] == nullptr)
//								{
//									MovePixel_Update(&x, &y, newX, y);
//								}
//								else
//								{
//									break;
//								}
//							}
//							break;
//						}
//						else
//						{
//							c->velocity.y = 0;
//							c->falling = false;
//							break;
//						}
//					}
//					else
//					{
//						c->velocity.y = 0;
//						c->falling = false;
//						break;
//					}
//				}
//			}
//			else
//			{
//				MovePixel_Update(&x, &y, x, newY);
//			}
//		}
//	}
//}
//
//void pixel_simulation::UpdateString(int x, int y, flamable_s* c, double* deltaTime)
//{
//	bool retFlag;
//	UpdateFlamable(c, deltaTime, x, y, retFlag);
//	if (retFlag) return;
//}

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

			grid[y][x]->updated = true;

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

inline void drawCircle(int xc, int yc, int x, int y, SDL_Renderer* rend)
{
	SDL_RenderDrawPoint(rend, xc + x, yc + y);
	SDL_RenderDrawPoint(rend, xc - x, yc + y);
	SDL_RenderDrawPoint(rend, xc + x, yc - y);
	SDL_RenderDrawPoint(rend, xc - x, yc - y);
	SDL_RenderDrawPoint(rend, xc + y, yc + x);
	SDL_RenderDrawPoint(rend, xc - y, yc + x);
	SDL_RenderDrawPoint(rend, xc + y, yc - x);
	SDL_RenderDrawPoint(rend, xc - y, yc - x);
}

// Function for circle-generation 
// using Bresenham's algorithm 
inline void circleBres(int xc, int yc, int r, SDL_Renderer* rend)
{
	int x = 0, y = r;
	int d = 3 - 2 * r;
	drawCircle(xc, yc, x, y, rend);
	while (y >= x)
	{
		// for each pixel we will 
		// draw all eight pixels 

		x++;

		// check for decision parameter 
		// and correspondingly  
		// update d, x, y 
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		drawCircle(xc, yc, x, y, rend);
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
	circleBres(inputManager->MousePos().x, inputManager->MousePos().y, PAINT_BRUSH_CIRCLE_RADIUS, renderer);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}
