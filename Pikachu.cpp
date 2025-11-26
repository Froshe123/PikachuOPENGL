#include "Pikachu.h"
#include <GL/glut.h>
#include <cmath>
#include "Cylindre.h"

Pikachu::Pikachu(double posX, double posY, double posZ) {
    this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;

    this->frameAnim = 0;
    this->is_started = 0;
    this->espanim = 0;
    this->phase = 0;
    this->poke = 0;
}

void Pikachu::draw() {

    /* ===== PIED DROIT ===== */
    glPushMatrix();
        glTranslatef(posX + 0.5, posY, posZ);
        glScalef(0.5, 0.25, 0.6);
        glutSolidSphere(0.5, 18, 18);
    glPopMatrix();

    /* ===== PIED GAUCHE ===== */
    glPushMatrix();
        glTranslatef(posX - 0.5, posY, posZ);
        glScalef(0.5, 0.25, 0.6);
        glutSolidSphere(0.5, 18, 18);
    glPopMatrix();

    /* ===== CORPS ===== */
    glPushMatrix();
        glTranslatef(posX, posY + 0.75, posZ);
        glutSolidSphere(0.8, 40, 40);
    glPopMatrix();

    /* ===== TETE ===== */
    glPushMatrix();

        /* --- boule tête --- */
        glPushMatrix();
            glTranslatef(posX, posY + 1.8, posZ);
            glutSolidSphere(0.65, 40, 40);
        glPopMatrix();

        /* --- oeil droit --- */
        glPushMatrix();
            glColor3f(0, 0, 0);
            glTranslatef(posX + 0.23, posY + 1.85, posZ + 0.55);
            glScalef(0.20, 0.20, 0.20);
            glutSolidSphere(0.5, 20, 20);
        glPopMatrix();

        /* --- oeil gauche --- */
        glPushMatrix();
            glColor3f(0, 0, 0);
            glTranslatef(posX - 0.23, posY + 1.85, posZ + 0.55);
            glScalef(0.20, 0.20, 0.20);
            glutSolidSphere(0.5, 20, 20);
        glPopMatrix();

        /* --- étincelle oeil droit --- */
        glPushMatrix();
            glColor3f(1, 1, 1);
            glTranslatef(posX + 0.245, posY + 1.88, posZ + 0.61);
            glScalef(0.1, 0.1, 0.1);
            glutSolidSphere(0.5, 20, 20);
        glPopMatrix();

        /* --- étincelle oeil gauche --- */
        glPushMatrix();
            glColor3f(1, 1, 1);
            glTranslatef(posX - 0.245, posY + 1.88, posZ + 0.61);
            glScalef(0.1, 0.1, 0.1);
            glutSolidSphere(0.5, 20, 20);
        glPopMatrix();

        /* --- sourire --- */
        glPushMatrix();
            glColor3f(0, 0, 0);
            glTranslatef(posX, posY + 1.60, posZ + 0.56);
            glScalef(0.25f, 0.07f, 0.20f);
            glutSolidSphere(0.5, 30, 30);
        glPopMatrix();

        /* --- joue gauche --- */
        glPushMatrix();
            glColor3f(1, 0, 0);
            glTranslatef(posX - 0.39, posY + 1.60, posZ + 0.30);
            glScalef(0.3, 0.25, 0.28);
            glutSolidSphere(0.5, 20, 20);
        glPopMatrix();

        /* --- joue droite --- */
        glPushMatrix();
            glColor3f(1, 0, 0);
            glTranslatef(posX + 0.39, posY + 1.60, posZ + 0.30);
            glScalef(0.3, 0.25, 0.28);
            glutSolidSphere(0.5, 20, 20);
        glPopMatrix();

    glPopMatrix(); // fin TETE

    /* ===== BRAS DROIT ===== */
    glPushMatrix();
        glColor3f(1, 1, 0);
        glTranslatef(posX + 1, posY + 1.0, posZ);
        glRotatef(-45, 0, 0, 1);
        glScalef(0.3, 0.7, 0.3);
        glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    /* ===== BRAS GAUCHE ===== */
    glPushMatrix();
        glColor3f(1, 1, 0);
        glTranslatef(posX - 1, posY + 1.0, posZ);
        glRotatef(45, 0, 0, 1);
        glScalef(0.3, 0.7, 0.3);
        glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    /* ===== OREILLE DROITE ===== */
    glPushMatrix();
        glTranslatef(posX + 0.4f, posY + 2.0f, posZ);
        glRotatef(-20 + sin(frameAnim) * 6.0f, 0, 0, 1);
        glRotatef(-90, 1, 0, 0);

        glColor3f(1, 1, 0);
        glutSolidCone(0.15, 0.9, 20, 20);
         /*====partie noire droite====*/
        glPushMatrix();
            glTranslatef(0, 0, 0.647f);
            glColor3f(0, 0, 0);
            glutSolidCone(0.050, 0.25, 20, 20);
        glPopMatrix();
    glPopMatrix();

    /* ===== OREILLE GAUCHE ===== */
    glPushMatrix();
        glTranslatef(posX - 0.4f, posY + 2.0f, posZ);
        glRotatef(20 - sin(frameAnim) * 6.0f, 0, 0, 1);
        glRotatef(-90, 1, 0, 0);

        glColor3f(1, 1, 0);
        glutSolidCone(0.15, 0.9, 20, 20);
        /*====partie noire gauche====*/
        glPushMatrix();
            glTranslatef(0, 0, 0.647f);
            glColor3f(0, 0, 0);
            glutSolidCone(0.050, 0.25, 20, 20);
        glPopMatrix();
    glPopMatrix();

    /* ===== CHAPEAU ===== */
    {
        Cylindre base(30, 0.05, 0.40);
        Cylindre corp(30, 0.45, 0.22);

        glPushMatrix();
            glTranslatef(posX, posY + 2.4, posZ);

            glPushMatrix();
                glColor3f(0.05f, 0.05f, 0.05f);
                base.draw();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, 0.25, 0);
                glRotatef(90, 0, 1, 0);

                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 2);
                glColor3f(1, 1, 1);
                corp.draw();
                glDisable(GL_TEXTURE_2D);
            glPopMatrix();

        glPopMatrix();
    }

    /* ===== QUEUE ===== */
    float baseZ = posZ - 0.75f;
    float offsetZ = -0.05f;

    glPushMatrix();
        glTranslatef(posX, posY + 0.8f, baseZ);
        glRotatef(sin(frameAnim) * 20.0f, 0, 1, 0);

        glPushMatrix();
            glColor3f(0.45f, 0.30f, 0.10f);
            glTranslatef(0, 0.25f, offsetZ * 1);
            glScalef(0.15f, 0.45f, 0.20f);
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glColor3f(1, 1, 0);
            glTranslatef(0.15f, 0.55f, offsetZ * 2);
            glRotatef(20, 0, 0, 1);
            glScalef(0.35f, 0.15f, 0.20f);
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glColor3f(1, 1, 0);
            glTranslatef(0.25f, 0.80f, offsetZ * 3);
            glScalef(0.15f, 0.45f, 0.20f);
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glColor3f(1, 1, 0);
            glTranslatef(0.45f, 1.10f, offsetZ * 4);
            glRotatef(-15, 0, 0, 1);
            glScalef(0.45f, 0.25f, 0.20f);
            glutSolidCube(1.0);
        glPopMatrix();

    glPopMatrix();

    /* ===== HAUT DU CHAPEAU ANIMÉ ===== */
    float pivot = -0.22f;

    glPushMatrix();
        glColor3f(1.0f, 0.3f, 0.3f);
        glTranslatef(posX + pivot, posY + 2.87f, posZ);
        glRotatef(espanim, 0, 0, 1);
        glTranslatef(-pivot, 0, 0);
        
        glScalef(1, 0.1, 1);
        glutSolidSphere(0.22, 20, 20);
    glPopMatrix();

    /* ===== BOULE ===== */

    glEnable(GL_LIGHT1);// activation lumière ponctuelle bleue sur la boule 

    GLfloat pos1[] = {
        (float)posX,
        (float)(posY + 2.4 + (poke * 0.015)),
        (float)posZ,
        1.0f
    };

    GLfloat amb1[]  = {0, 0, 1, 1};
    GLfloat diff1[] = {0, 0, 1, 1};
    GLfloat spec1[] = {0, 0, 1, 1};

    glLightfv(GL_LIGHT1, GL_POSITION, pos1);
    glLightfv(GL_LIGHT1, GL_AMBIENT,  amb1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  diff1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);

    glPushMatrix();
        glColor3f(0, 0, 1);
        glTranslatef(posX, posY + 2.4 + (poke * 0.015), posZ);
        glRotatef(frameAnim, 1, 0, 0);
        glutSolidSphere(0.115, 20, 20);
    glPopMatrix();
}

void Pikachu::IdleAnimation() {

    frameAnim += 0.1;

    if (!is_started) return;

    if (phase == 0) {
        espanim += 2;
        poke = espanim;

        if (espanim >= 90) {
            espanim = 90;
            phase = 1;
        }
    }
    else if (phase == 1) {
        espanim -= 2;

        if (espanim > 39)
            poke = espanim;

        if (espanim <= 0) {
            espanim = 0;
            phase = 0;
            is_started = 0;
        }
    }
}
