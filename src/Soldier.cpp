#include <iostream>
#include "Soldier.h"

using namespace std;

Soldier::Soldier(const string soldierName, unique_ptr<Gun> gun) :
   m_soldierName(soldierName), m_gun(move(gun))
{
}

void Soldier::AddBulletToGun(uint32_t bulletNum)
{
    this->m_gun->AddBullet(bulletNum);
}

void Soldier::Fire()
{
    this->m_gun->Shoot();
}