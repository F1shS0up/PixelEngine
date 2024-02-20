#pragma once
#include "SDL.h"
#include "glm/glm.hpp"

struct element
{
	unsigned int id;
	SDL_Color color;
	SDL_Color initialColor;
	bool updated;
	bool falling = true;
	float density;
	int explosionResistance;
	int fireResistance;
	float health = 1.f;
	bool onFire = false;
	float fireSpreadDelay;
	float fireDamagePerSecond;
	int sparkSpawnChance;

	float fireSpreadCountdown;
	float instantiateSmokeCountdown;

	element();
	~element();

	virtual void Update(double* deltaTime, class pixel_simulation* pxSim, int x, int y);
	virtual void Reset();
	virtual void TransferVelocity(glm::vec2 velocity);
	virtual void Darken();
	void ReplaceAsParticle(glm::vec2 velocity, class pixel_simulation* pxSim, int x, int y);
	void AddHealth(float amount, class pixel_simulation* pxSim, int x, int y);
	void ReceiveFire();
	void CreateSmokeAround(int x, int y, class pixel_simulation* pxSim);
	void SpreadFire(class pixel_simulation* pxSim, int x, int y);
	void CoolDownCheck(class pixel_simulation* pxSim, int x, int y);
};