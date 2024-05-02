#pragma once
#include <string>

class Gun
{
private:
    /* data */
    std::string m_typeName;
    uint32_t m_bulletCount;

public:
    Gun(std::string typeName, uint32_t bulletCount) :
        m_typeName(typeName), m_bulletCount(bulletCount) {}
    void AddBullet(uint32_t bulletNum);
    void Shoot();
};
