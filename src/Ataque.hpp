#ifndef ATAQUE_HPP
#define ATAQUE_HPP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Ataque : public ObjetoDeJogo
{
public:
    Ataque(const ObjetoDeJogo &obj, int velAtaque, int dir, int dano = 10):ObjetoDeJogo(obj), velAtaque(velAtaque), dir(dir), dano(dano){}
    virtual ~Ataque(){}

    void update(){
        if(dir==1){
            moveUp(velAtaque);
        }else{
            moveDown(velAtaque);
        }
    }

    int getVelAtaque() const {return velAtaque;}
    void setVelAtaque(int velAtaque) {this->velAtaque = velAtaque;}

    int getDir() const {return dir;}
    void setDir(int dir) {this->dir = dir;}

    int getDano() const {return dano;}

private:
    int velAtaque;
    int dir;
    int dano;
};

#endif //ATAQUE_HPP