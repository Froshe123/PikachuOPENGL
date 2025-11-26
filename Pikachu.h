#ifndef PROJETGL_PIKACHU_H
#define PROJETGL_PIKACHU_H


#include "Cylindre.h"

class Pikachu {

public:
    double posX, posY, posZ; //position du Pikachu
    double frameAnim,is_started,espanim,phase,poke ; //variables pour l'animation

    Pikachu(double posX, double posY, double posZ); //constructeur
    void draw();
    void IdleAnimation();
};


#endif //PROJETGL_PIKACHU_H