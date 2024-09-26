#ifndef FASE1_HPP
#define FASE1_HPP

#include "../ASCII_Engine/Fase.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"
#include "Ataque.hpp"
#include "AtaqueVerificador.hpp"

class Fase1 : public Fase
{
public:
    Fase1(std::string name, const Sprite &bkg):Fase(name,bkg){}
    virtual ~Fase1(){}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    int getCountEnemy()const{return countEnemy;}
    void setCountEnemy(int contEnemy){this->countEnemy = contEnemy;}
    virtual void draw(SpriteBase &screen, int x=0, int y=0) override;

private:
    Hero *hero;
    Enemy *enemy1[10];
    AtaqueVerificador *ataqueVerificador;
    int countEnemy;
    TextSprite *vida, *ataques;
    AtaqueVerificador *controlador;
};

#endif //FASE1_HPP