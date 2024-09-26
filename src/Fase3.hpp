#ifndef FASE3_HPP
#define FASE3_HPP

#include "../ASCII_Engine/Fase.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"
#include "Ataque.hpp"
#include "AtaqueVerificador.hpp"

class Fase3 : public Fase
{
public:
    Fase3(std::string name, const Sprite &bkg):Fase(name,bkg){}
    virtual ~Fase3(){}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    int getCountEnemy()const{return countEnemy;}
    void setCountEnemy(int contEnemy){this->countEnemy = contEnemy;}
    virtual void draw(SpriteBase &screen, int x=0, int y=0) override;

private:
    Hero *hero;
    Enemy *enemy1[10];
    Enemy *enemy2[8]; 
    Enemy *enemy3[5];   
    AtaqueVerificador *ataqueVerificador;
    int countEnemy;
    TextSprite *vida, *ataques;
    AtaqueVerificador *controlador;
};

#endif //FASE3_HPP
