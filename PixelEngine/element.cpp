#include "element.h"
#include "particle.h"
#include "pixel_simulation.h"
#include "movable.h"
#include "liquid.h"
#include "gas.h"
#include "smoke.h"
#include <iostream>
#include "spark.h"
#include "water.h"
element::element()
{
}

element::~element()
{
}

void element::Update(double* deltaTime, pixel_simulation* pxSim, int x, int y)
{
	updated = true;
	if (onFire)
	{
		instantiateSmokeCountdown -= *deltaTime;
		if (instantiateSmokeCountdown <= 0)
		{
			CreateSmokeAround(x, y, pxSim);
			instantiateSmokeCountdown = (float)(rand() % 100) / 400.f + 0.75f;
		}

		AddHealth(-fireDamagePerSecond * *deltaTime, pxSim, x, y);
		if (health <= 0) return;

		if (health < 0.2f && health > 0 && !dynamic_cast<spark*>(this))
		{
			if (rand() % 101 < sparkSpawnChance)
			{
				spark* s = new spark();
				s->velocity = glm::vec2((float)(rand() % 201 - 100) / 4.f, 0);
				pxSim->ReplaceElementAndDeleteLast(x, y, s);
				return;
			}
		}

		color = SDL_Color{ 255, (Uint8)(rand() % 90 + 80), 3 , 255 };
		fireSpreadCountdown -= *deltaTime;
		if (fireSpreadCountdown <= 0.f)
		{
			SpreadFire(pxSim, x, y);
			fireSpreadCountdown = fireSpreadDelay;
		}
	}
}

void element::Reset()
{
}

void element::TransferVelocity(glm::vec2 velocity)
{
}

void element::Darken()
{

}

void element::ReplaceAsParticle(glm::vec2 velocity, pixel_simulation* pxSim, int x, int y)
{
	particle* p = nullptr;
	if (dynamic_cast<liquid*>(this))
	{
		p = new particle(((liquid*)pxSim->grid[y][x])->gravity, this, color, velocity, health, explosionResistance);
	}
	else if (dynamic_cast<movable*>(this))
	{
		p = new particle(((movable*)pxSim->grid[y][x])->gravity, this, color, velocity, health, explosionResistance);
	}
	else if (dynamic_cast<gas*>(this))
	{
		p = new particle(((gas*)pxSim->grid[y][x])->gravity, this, color, velocity, health, explosionResistance);
	}
	if(p != nullptr)pxSim->ReplaceElement(x, y, p);
}

void element::AddHealth(float amount, pixel_simulation* pxSim, int x, int y)
{
	health += amount;
	if (health <= 0)
	{
		pxSim->DeleteElement(x, y);
	}
}

void element::ReceiveFire()
{
	int rng = rand() % 101; // 0 - 100
	if (rng > fireResistance)
	{
		fireSpreadCountdown = fireSpreadDelay;
		instantiateSmokeCountdown = (float)(rand() % 100) / 400.f + 0.75f;
		onFire = true;
	}
}

void element::CreateSmokeAround(int x, int y, pixel_simulation* pxSim)
{
	if (pxSim->InBounds(x, y - 1))
	{
		if (pxSim->grid[y - 1][x] == nullptr)
		{
			pxSim->CreateElement<smoke>(x, y - 1);
			return;
		}
	}
}

void element::SpreadFire(pixel_simulation* pxSim, int x, int y)
{
	if (pxSim->InBounds(x + 1, y))
	{
		if (pxSim->grid[y][x + 1] != nullptr)
		{
			if (!pxSim->grid[y][x + 1]->onFire)pxSim->grid[y][x + 1]->ReceiveFire();
		}
	}
	if (pxSim->InBounds(x - 1, y))
	{
		if (pxSim->grid[y][x - 1] != nullptr)
		{
			if (!pxSim->grid[y][x - 1]->onFire)pxSim->grid[y][x - 1]->ReceiveFire();
		}
	}
	if (pxSim->InBounds(x, y + 1))
	{
		if (pxSim->grid[y + 1][x] != nullptr)
		{
			if (!pxSim->grid[y + 1][x]->onFire)pxSim->grid[y + 1][x]->ReceiveFire();
		}
	}
	if (pxSim->InBounds(x, y - 1))
	{
		if (pxSim->grid[y - 1][x] != nullptr)
		{
			if (!pxSim->grid[y - 1][x]->onFire)pxSim->grid[y - 1][x]->ReceiveFire();
		}
	}
}

void element::CoolDownCheck(pixel_simulation* pxSim, int x, int y)
{
	if (pxSim->InBounds(x + 1, y))
	{
		if (pxSim->grid[y][x + 1] != nullptr && dynamic_cast<water*>(pxSim->grid[y][x + 1]) && rand() % 101 > fireResistance)
		{
			if (dynamic_cast<spark*>(this))
			{
				AddHealth(-health, pxSim, x, y);
			}
			else
			{
				pxSim->grid[y][x + 1]->onFire = false;
				color = initialColor;
			}
		}
	}
	if (pxSim->InBounds(x - 1, y))
	{
		if (pxSim->grid[y][x - 1] != nullptr && dynamic_cast<water*>(pxSim->grid[y][x - 1]) && rand() % 101 > fireResistance)
		{
			if (dynamic_cast<spark*>(this))
			{
				AddHealth(-health, pxSim, x, y);
			}
			else
			{
				pxSim->grid[y][x - 1]->onFire = false;
				color = initialColor;
			}
		}
	}
	if (pxSim->InBounds(x, y + 1))
	{
		if (pxSim->grid[y + 1][x] != nullptr && dynamic_cast<water*>(pxSim->grid[y + 1][x]) && rand() % 101 > fireResistance)
		{
			if (dynamic_cast<spark*>(this))
			{
				AddHealth(-health, pxSim, x, y);
			}
			else
			{
				pxSim->grid[y + 1][x]->onFire = false;
				color = initialColor;
			}
		}
	}
	if (pxSim->InBounds(x, y - 1))
	{
		if (pxSim->grid[y - 1][x] != nullptr && dynamic_cast<water*>(pxSim->grid[y - 1][x]) && rand() % 101 > fireResistance)
		{
			if (dynamic_cast<spark*>(this))
			{
				AddHealth(-health, pxSim, x, y);
			}
			else
			{
				onFire = false;
				color = initialColor;
			}
		}
	}
}
