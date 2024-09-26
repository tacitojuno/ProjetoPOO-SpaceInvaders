#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"

enum class EstadoEnemy{Idle, MovingRight, MovingLeft};

class Enemy : public ObjetoDeJogo
{
public:
    Enemy(const ObjetoDeJogo &obj, int velocidade =1):ObjetoDeJogo(obj), velocidade(velocidade), state(EstadoEnemy::Idle){}
    virtual ~Enemy();

    virtual void update(){
        switch(state){
            case EstadoEnemy::Idle:
                moveTo(getPosL(), getPosC());
                state = EstadoEnemy::MovingRight;
                break;
            case EstadoEnemy::MovingRight:
                moveRight(getVelocidade());
                if(getPosC() == 176 - this->getSprite()->getLarguraMax() - 3){
                    state = EstadoEnemy::MovingLeft;
                }
                break;
            case EstadoEnemy::MovingLeft:
                moveLeft(getVelocidade());
                if(getPosC() == 2){
                    state = EstadoEnemy::MovingRight;
                }
                break;
        }
    }

    EstadoEnemy getState() const{return state;}
    void setState(EstadoEnemy state){this->state = state;}

    int getVelocidade() const {return velocidade;}

private:
    int velocidade;
    EstadoEnemy state;
};

#endif //ENEMY_HPP