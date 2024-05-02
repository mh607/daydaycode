#include "Soldier.h"
#include <iostream>

using namespace std;

void Test()
{
    Soldier soldier("xusanduo", make_unique<Gun>("AK47", 0));
    soldier.AddBulletToGun(10);
    soldier.Fire();
}

int main(int argc, char** argv)
{
    cout << "Hello World!" << endl;
    Test();
    return 0;
}