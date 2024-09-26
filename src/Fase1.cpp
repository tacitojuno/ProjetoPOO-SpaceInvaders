#include "Fase1.hpp"
#include <ctime>
#include <cstdlib>
#include <string>
#include "CaptureKey.hpp"
#include <iostream>

using namespace std;

void Fase1::init(){

    hero = new Hero(ObjetoDeJogo("Hero", Sprite("rsc/hero.txt"), 42, 80), 10, 2);
    objs.push_back(hero);

    countEnemy = 0;
    int pos = 0;
    for(int i=0; i < 10; i++){
        countEnemy += 1;
        enemy1[pos] = new Enemy(ObjetoDeJogo("Enemy", Sprite("rsc/enemy1.txt"),25,15 + (i*15)),1);
        objs.push_back(enemy1[pos++]);
    }

    objs.push_back(new ObjetoDeJogo("Vida", TextSprite("##########"),4,133 ));
    SpriteBase *tmp=const_cast<SpriteBase*>(objs.back()->getSprite());
    vida = dynamic_cast<TextSprite*>(tmp);

    objs.push_back(new ObjetoDeJogo("Ataques", TextSprite("0/10"),4,30 ));
    SpriteBase *tmp2=const_cast<SpriteBase*>(objs.back()->getSprite());
    ataques = dynamic_cast<TextSprite*>(tmp2);

    objs.push_back(new ObjetoDeJogo("Fase", TextSprite("1"), 4, 84));

    controlador = new AtaqueVerificador(ObjetoDeJogo("AtaqueVerificador", Sprite("rsc/enemy2Bullet.txt"),0,0));
    objs.push_back(controlador);

    srand(time(NULL));

    objs.push_back(new ObjetoDeJogo("Obstáculo", TextSprite("############"), 37, 16));
    objs.push_back(new ObjetoDeJogo("Obstáculo", TextSprite("############"), 37, 80));
    objs.push_back(new ObjetoDeJogo("Obstáculo", TextSprite("############"), 37, 135));
    
}

unsigned Fase1::run(SpriteBuffer &screen){
    std::string ent;

    draw(screen);
    system("clear");
    show(screen);

    int cont = 0;
    int colisao;
    while(true){
        char ch = captureKey();
        if(ch == 'q'){
            return Fase::END_GAME;
        }else if (ch =='a' && hero->getPosC() > 3){
            hero->moveLeft(1);
        }else if (ch =='d' && hero->getPosC() < 159){
            hero->moveRight(1);
        }else if (ch =='w' && hero->getAtaques() < hero->getTotalAtaques()){
            controlador->criaAtaque(hero->getPosL() -2, hero->getPosC() +5, 1, hero->getVelAtaque());
            hero->incrementaAtaque();
            ataques->setText(std::to_string(hero->getAtaques()) + "/" + std::to_string(hero->getTotalAtaques()));
        }else if (ch == 'o') return Fase::LEVEL_COMPLETE;

        colisao = controlador->verificaColisao(objs);
        if(colisao==1){
            countEnemy--;
        }else if(colisao==0){
            vida->setText(string(hero->getVida()/10,'#'));
        }

        update();
        draw(screen);
        system("clear");

        if(countEnemy==0){
            return Fase::LEVEL_COMPLETE;
        }else if((hero->getAtaques()==hero->getTotalAtaques()&&countEnemy>0)||(!hero->isAlive())){
            return Fase::GAME_OVER;
        }

        show(screen);
    }
}

void Fase1::draw(SpriteBase &screen, int x, int y){
    background->draw(screen, 0, 0);
    for(auto obj : objs){
        obj->draw(screen, obj->getPosL(), obj->getPosC());
    }
}