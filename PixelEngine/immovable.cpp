#include "immovable.h"

void immovable::Update(double* deltaTime, pixel_simulation* pxSim, int x, int y)
{
	element::Update(deltaTime, pxSim, x, y);
	if (onFire)CoolDownCheck(pxSim, x, y);
}
void immovable::Reset()
{

}
