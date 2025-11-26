#include <cmath>
#include <GL/glut.h>
#include "Cylindre.h"

// creation d'une structure pour stocker les coordonnées des points
struct Point {
    double x;
    double y;
    double z;
};

Cylindre::Cylindre(int nbFaces, double hauteur, double rayon) {
    this->nbFaces = nbFaces;
    this->hauteur = hauteur;
    this->rayon = rayon;
    this->posY = 0;
    this->posX = 0;
    this->posZ = 0;
}

void Cylindre::draw() {
    disque(nbFaces, hauteur / 2, rayon);
    disque(nbFaces, -hauteur / 2, rayon);
    cotes(nbFaces, hauteur, rayon);
}

void Cylindre::cotes(int nbFaces, double hauteur, double rayon) {
    double yBas  = posY - hauteur *0.5;
    double yHaut = posY + hauteur * 0.5;

    glBegin(GL_QUADS);
    for (int i = 0; i < nbFaces; ++i) {
        // Angles pour les segments
        double theta0 = 2.0 * M_PI *  i      / nbFaces;
        double theta1 = 2.0 * M_PI * (i + 1) / nbFaces;

        // Calcul des coordonnées des points
        double x0 = posX + rayon * cos(theta0);
        double z0 = posZ + rayon * sin(theta0);
        double x1 = posX + rayon * cos(theta1);
        double z1 = posZ + rayon * sin(theta1);

        float u0 = (float) i      / nbFaces;
        float u1 = (float)(i + 1) / nbFaces;

        /* ====== NORMALES POUR LES CÔTÉS ====== */
        glNormal3f(cos(theta0), 0, sin(theta0));
        glTexCoord2f(u0, 1.0f); glVertex3f(x0, yBas,  z0);

        glNormal3f(cos(theta1), 0, sin(theta1));
        glTexCoord2f(u1, 1.0f); glVertex3f(x1, yBas,  z1);

        glNormal3f(cos(theta1), 0, sin(theta1));
        glTexCoord2f(u1, 0.0f); glVertex3f(x1, yHaut, z1);

        glNormal3f(cos(theta0), 0, sin(theta0));
        glTexCoord2f(u0, 0.0f); glVertex3f(x0, yHaut, z0);
    }
    glEnd();
}


void Cylindre::disque(int nbFaces, double hauteur, double rayon) {
    Point tabPointDisque[nbFaces + 1];
    int tabFacesDisque[nbFaces][3];

    for (int i = 0; i < nbFaces; i++) {
        tabPointDisque[i].x = this->posX + rayon * cos((2 * i * M_PI) / nbFaces);
        tabPointDisque[i].z = this->posZ + rayon * sin((2 * i * M_PI) / nbFaces);
        tabPointDisque[i].y = this->posY + hauteur;
    }
    tabPointDisque[nbFaces].x = this->posX;
    tabPointDisque[nbFaces].z = this->posZ;
    tabPointDisque[nbFaces].y = this->posY + hauteur;

    for (int i = 0; i < nbFaces; i++) {
        tabFacesDisque[i][0] = i;
        tabFacesDisque[i][1] = (i + 1) % nbFaces;
        tabFacesDisque[i][2] = nbFaces;
    }
    float normalY = (hauteur > 0) ? 1.0f : -1.0f;

    for (int i = 0; i < nbFaces; i++) {
        glBegin(GL_POLYGON);

        glNormal3f(0, normalY, 0);  // normale du disque

        for (int j = 0; j < 3; j++) {
            glVertex3f(tabPointDisque[tabFacesDisque[i][j]].x,
                       tabPointDisque[tabFacesDisque[i][j]].y,
                       tabPointDisque[tabFacesDisque[i][j]].z);
        }
        glEnd();
    }
}