#ifndef HERO_HPP
#define HERO_HPP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Hero : public ObjetoDeJogo
{
public:
    Hero(const ObjetoDeJogo &obj,int totalAtaques, int velAtaque, int vida = 100): ataques(0), totalAtaques(totalAtaques), velAtaque(velAtaque), vida(vida), ObjetoDeJogo(obj){}

    virtual ~Hero(){}

    bool isAlive() const{return vida != 0;}
    void sofreDano(int dano){vida = (vida - dano >= 0)?(vida - dano):0;}
    int atirar() const{return 10;}
    int getAtaques() const{return ataques;}
    int getVelAtaque() const{return velAtaque;}
    void setVelAtaque(int velAtaque){this->velAtaque = velAtaque;}
    int getVida() const{return vida;}
    int getTotalAtaques() const{return totalAtaques;}
    void incrementaAtaque(){ataques++;}

private:
    int ataques;
    int totalAtaques;
    int velAtaque;
    int vida;
};
#endif //HERO_HPP