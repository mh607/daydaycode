#include "Gun.h"
#include <iostream>

using namespace std;

void Gun::AddBullet(uint32_t bulletNum)
{
    m_bulletCount += bulletNum;
}

void Gun::Shoot()
{
    if (m_bulletCount == 0) {
        cout << "bulletCount == 0" << endl;
        return;
    } else {
        m_bulletCount--;
        cout << "bulletCount = " << m_bulletCount << endl;
    }
}