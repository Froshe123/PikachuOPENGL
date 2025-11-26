

#ifndef PROJETGL_CYLINDRE_H
#define PROJETGL_CYLINDRE_H



class Cylindre {
private:
    int nbFaces;
    double hauteur;
    double rayon;
    double posX, posY, posZ;

    void cotes(int nbFaces, double hauteur, double rayon);

    void disque(int nbFaces, double hauteur, double rayon);

public:
    Cylindre(int nbFaces, double hauteur, double rayon);

    void draw();




};


#endif //PROJETGL_CYLINDRE_H