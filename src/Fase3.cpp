#include "Fase3.hpp"
#include <ctime>
#include <cstdlib>
#include <string>
#include "CaptureKey.hpp"
#include <iostream>
using namespace std;

void Fase3::init(){

    hero = new Hero(ObjetoDeJogo("Hero", Sprite("rsc/hero.txt"), 42, 80), 50, 2);
    objs.push_back(hero);

    countEnemy = 0;
    int pos = 0;
    for(int i=0; i < 10; i++){
        countEnemy += 1;
        enemy1[pos] = new Enemy(ObjetoDeJogo("Enemy", Sprite("rsc/enemy1.txt"),30,15 + (i*15)),1);
        objs.push_back(enemy1[pos++]);
    }
    pos = 0; 
    for(int i=0; i < 8; i++){ 
        countEnemy += 1;
        enemy2[pos] = new Enemy(ObjetoDeJogo("Enemy2", Sprite("rsc/enemy2.txt"),20, 12 + (i*20)),1);
        objs.push_back(enemy2[pos++]);
    }
    pos = 0; 
    for(int i=0; i < 5; i++){ 
        countEnemy += 1;
        enemy3[pos] = new Enemy(ObjetoDeJogo("Enemy3", Sprite("rsc/enemy3.txt"),10, 22 + (i*30)),1);
        objs.push_back(enemy3[pos++]);
    }

    objs.push_back(new ObjetoDeJogo("Vida", TextSprite("##########"),4,133 ));
    SpriteBase *tmp=const_cast<SpriteBase*>(objs.back()->getSprite());
    vida = dynamic_cast<TextSprite*>(tmp);

    objs.push_back(new ObjetoDeJogo("Ataques", TextSprite("0/50"),4,30 ));
    SpriteBase *tmp2=const_cast<SpriteBase*>(objs.back()->getSprite());
    ataques = dynamic_cast<TextSprite*>(tmp2);

    objs.push_back(new ObjetoDeJogo("Fase", TextSprite("3"), 4, 84));

    controlador = new AtaqueVerificador(ObjetoDeJogo("AtaqueVerificador", Sprite("rsc/enemy2Bullet.txt"),0,0));
    objs.push_back(controlador);

    srand(time(NULL));

    objs.push_back(new ObjetoDeJogo("Obstáculo", TextSprite("############"), 37, 16));
    objs.push_back(new ObjetoDeJogo("Obstáculo", TextSprite("############"), 37, 80));
    objs.push_back(new ObjetoDeJogo("Obstáculo", TextSprite("############"), 37, 135));
    
}

unsigned Fase3::run(SpriteBuffer &screen){
    std::string ent;

    draw(screen);
    system("clear");
    show(screen);

    int cont = 0;
    int cont1 = 0;

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
        }

        cont++; 
        if(cont==20){
            int i = rand()%8;
            if(enemy2[i]->Existe()){
                controlador->criaAtaque(enemy2[i]->getPosL() + 5, enemy2[i]->getPosC() + 2, 2, 1);
            }
            cont=0;
        } 
        
        cont1++; 
        if(cont1==30){
            int i = rand()%5;
            if(enemy3[i]->Existe()){
                controlador->criaAtaque(enemy3[i]->getPosL() + 5, enemy3[i]->getPosC() + 2, 3, 1, 50);
            }
            cont1=0;
        } 

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

void Fase3::draw(SpriteBase &screen, int x, int y){
    background->draw(screen, 0, 0);
    for(auto obj : objs){
        obj->draw(screen, obj->getPosL(), obj->getPosC());
    }
}
