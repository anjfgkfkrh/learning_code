#include <string.h>
#include <iostream>

class Photon_Cannon
{
   int hp, shield;
   int coord_x, coord_y;
   int damage;

   char *name;

public:
   Photon_Cannon(int x, int y);
   Photon_Cannon(int x, int y, char *_name);
   Photon_Cannon(const Photon_Cannon &pc);

   void show_status();

   ~Photon_Cannon();
};

Photon_Cannon::Photon_Cannon(const Photon_Cannon &pc)
{
   std::cout << "복사 생성자 호출 !" << std::endl;
   hp = pc.hp;
   shield = pc.shield;
   coord_x = pc.coord_x;
   coord_y = pc.coord_y;
   damage = pc.damage;

   if (pc.name != NULL)
   {
      name = new char[strlen(pc.name) + 1];
      strcpy(name, pc.name);
   }
   else
      name = NULL;
}
Photon_Cannon::Photon_Cannon(int x, int y) : hp(100), shield(100), damage(20), name(NULL)
{
   std::cout << "생성자 호출 !" << std::endl;
   coord_x = x;
   coord_y = y;
}
Photon_Cannon::Photon_Cannon(int x, int y, char *_name) : hp(100), shield(100), damage(20)
{
   std::cout << "생성자 호출 !" << std::endl;
   coord_x = x;
   coord_y = y;

   name = new char[strlen(_name) + 1];
   strcpy(name, _name);
}
void Photon_Cannon::show_status()
{
   std::cout << "Photon Cannon " << std::endl;
   std::cout << " Location : (" << coord_x << " , " << coord_y << " ) " << std::endl;
   std::cout << " HP : " << hp << std::endl;
   if (name != NULL)
      std::cout << " Name: " << name << std::endl;
}
Photon_Cannon::~Photon_Cannon()
{
   if (name != NULL)
      delete[] name;
}
int main()
{
   Photon_Cannon pc1(3, 3);
   Photon_Cannon pc2(pc1);
   Photon_Cannon pc3 = pc2;

   pc1.show_status();
   pc2.show_status();
}