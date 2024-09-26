#ifndef ATAQUE_VERIFICADOR_HPP
#define ATAQUE_VERIFICADOR_HPP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include "Ataque.hpp"
#include "Hero.hpp"
#include <list>
#include <unistd.h>

class AtaqueVerificador : public ObjetoDeJogo
{
public:
    AtaqueVerificador(const ObjetoDeJogo &obj):ObjetoDeJogo(obj){}
    virtual ~AtaqueVerificador(){
        for(auto &a : ataques){
            delete a;
        }
    }

    void update(){
        for(auto ataque:ataques){
            int i = ataque->getDir();
            
            switch (i){
                case 1:
                    if (ataque->getPosL() > 9){
                        ataque->moveUp(ataque->getVelAtaque());
                    }
                break;
            
                default:
                    if (ataque->getPosL() < 46){
                        ataque->moveDown(ataque->getVelAtaque());
                    }
                break;
            }

            if(ataque->getPosL() < 10 || ataque->getPosL() > 45){
                ataque->desativarObj();
            }
        }
    }

    void criaAtaque(int posL, int posC, int dir, int velAtaque, int dano = 10){
        std::string sprite;
        if(dir == 1){
            sprite = "./rsc/heroBullet.txt";
        }else if(dir == 2){
            sprite = "./rsc/enemy2Bullet.txt";
        }else if(dir == 3){
            sprite = "./rsc/enemy3Bullet.txt";
        }

        novoAtaque = new Ataque(ObjetoDeJogo("Ataque", Sprite(sprite), posL, posC), velAtaque, dir, dano);
        novoAtaque->ativarObj();
        ataques.push_back(novoAtaque);
    }

    int verificaColisao(const std::list<ObjetoDeJogo*> &objs){
        for(auto obj:objs){
            for(auto ataque:ataques){
                if(ataque->getDir()!=1 && (ataque->colideCom(*obj) && obj->getName() == "Hero")){
                    ataque->desativarObj();
                    Hero *hero=dynamic_cast<Hero*>(obj);
                    hero->sofreDano(ataque->getDano());
                    return 0;
                }else if(ataque->getDir()==1 && (ataque->colideCom(*obj) && (obj->getName()=="Enemy" || obj->getName()=="Enemy2" || obj->getName()=="Enemy3"))){
                    ataque->desativarObj();
                    obj->desativarObj();
                    return 1;
                } else if (ataque->getDir() == 3 && (ataque->colideCom(*obj) && obj->getName() == "Obstáculo")) {
                    ataque->desativarObj();
                    obj->desativarObj();
                    return 2;
                }else if ((ataque->getDir() == 1 || ataque->getDir() == 2) && (ataque->colideComBordas(*obj) && obj->getName() == "Obstáculo")) {
                    ataque->desativarObj();
                    return 3;
                }
            }
        }
        return 2;
    }

    void draw(SpriteBase &screen, int x, int y){
        for(auto ataque:ataques){
            ataque->draw(screen, ataque->getPosL(), ataque->getPosC());
        }
    }

    bool ataquesExistentes(){
        bool existe = false;
        for (auto ataque:ataques){
            if(ataque->Existe()){
                existe = true;
                break;
            }
        }
        return existe;
    }

private:
    std::list<Ataque*> ataques;
    Ataque *novoAtaque;
};

#endif //ATAQUE_VERIFICADOR_HPP