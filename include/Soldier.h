#pragma once
#include <string>
#include <memory>
#include "Gun.h"

class Soldier
{
private:
    std::string m_soldierName;
    std::unique_ptr<Gun> m_gun;
public:
    Soldier(std::string soldierName, std::unique_ptr<Gun> gun);
    void AddBulletToGun(uint32_t bulletNum);
    void Fire();
};
