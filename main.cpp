/****************************************************************************************/
/*                                main.cpp — Projet Tortue                              */
/****************************************************************************************/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "Pikachu.h"

#include <jpeglib.h>
#include <jerror.h>

using namespace std;

/* === CAMERA === */
char presse;
int anglex = 0, angley = 0;
int x, y, xold, yold;
double zoom = 9;

/* === DIMENSIONS IMAGE === */
const unsigned int largimg = 600;
const unsigned int hautimg = 835;
const unsigned int largimg2 = 512;
const unsigned int hautimg2 = 512;
unsigned char image[largimg * hautimg * 3];
unsigned char image2[largimg2 * hautimg2 * 3];

/* === UN SEUL PIKACHU === */
Pikachu* pikachu = new Pikachu(0, 0, 0);

/* === PROTOTYPES === */
void affichage();
void clavier(unsigned char touche, int x, int y);
void clavierTouchesSpeciales(int touche, int x, int y);
void reshape(int w, int h);
void idle();
void mouse(int bouton, int etat, int x, int y);
void mousemotion(int x, int y);
void gestionLumiere();
void loadJpegImage(const char* fichier,
                   unsigned char* buffer,
                   unsigned long larg,
                   unsigned long haut);



/****************************************************************************************/
/*                                       MAIN                                            */
/****************************************************************************************/

int main(int argc, char **argv)
{
    /* Chargement de l'image */
    loadJpegImage("carte.jpg", image, largimg , hautimg);
    loadJpegImage("pokeball.jpg", image2, largimg2 , hautimg2);
    /* GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Pikachu");

    /* Projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 0.5, 100);
    glMatrixMode(GL_MODELVIEW);

    /* === CRÉATION DE LA TEXTURE OPENGL === */
    glBindTexture(GL_TEXTURE_2D, 1);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largimg, hautimg, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image);

    glBindTexture(GL_TEXTURE_2D, 2);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largimg2, hautimg2, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image2);

    /* OpenGL */
    glClearColor(0.0, 0.0 , 0.0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);               // normales corrigées après glScalef
    glEnable(GL_COLOR_MATERIAL);          // permet à glColor3f de fonctionner sous lumière
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    GLfloat matSpec[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 64.0f);


    /* Callbacks */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutSpecialFunc(clavierTouchesSpeciales);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}


/****************************************************************************************/
/*                                   AFFICHAGE                                           */
/****************************************************************************************/

void affichage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glLoadIdentity();
    gluLookAt(0, 0, zoom,
              0, 0, 0,
              0, 1, 0);

    glRotatef(angley, 1, 0, 0);
    glRotatef(anglex, 0, 1, 0);
    
    /* === SUPPORT TEXTURÉ SOUS PIKACHU === */
    glPushMatrix();
           

        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, -0.10f, 0.0f); 
        glScalef(2.0f, 1.0f, 2.8f);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 1);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex3f(-1, 0, 1);
            glTexCoord2f(0, 0); glVertex3f(-1, 0,  -1);
            glTexCoord2f(1, 0); glVertex3f( 1, 0,  -1);
            glTexCoord2f(1, 1); glVertex3f( 1, 0, 1);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glColor3f(1.0f, 1.0f, 0.0f); 


    glPopMatrix();

    /* === PIKACHU === */
    pikachu->draw();

    gestionLumiere();

    glutSwapBuffers();
}


/****************************************************************************************/
/*                                 TOUCHES CLAVIER                                       */
/****************************************************************************************/

void clavier(unsigned char touche, int x, int y)
{
    switch(touche)
    {
        case 'q': exit(0); break;
        case 'z': zoom -= 0.3; break;
        case 'Z': zoom += 0.3; break;
        case ' ':{pikachu->is_started=1;
        printf("salut");}
    }
    glutPostRedisplay();
}


void clavierTouchesSpeciales(int touche, int x, int y)
{
    if (touche == GLUT_KEY_LEFT) anglex -= 2;
    if (touche == GLUT_KEY_RIGHT) anglex += 2;
    if (touche == GLUT_KEY_UP) angley -= 2;
    if (touche == GLUT_KEY_DOWN) angley += 2;

    glutPostRedisplay();
}


/****************************************************************************************/
/*                                 RESHAPE                                               */
/****************************************************************************************/

void reshape(int w, int h)
{
    if (w < h)
        glViewport(0, (h - w) / 2, w, w);
    else
        glViewport((w - h) / 2, 0, h, h);
}


/****************************************************************************************/
/*                                     SOURIS                                            */
/****************************************************************************************/

void mouse(int bouton, int etat, int X, int Y)
{
    if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
        presse = 1;
        xold = X;
        yold = Y;
    }
    if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP)
        presse = 0;

    if (bouton == 3) zoom -= 0.1;
    if (bouton == 4) zoom += 0.1;

    glutPostRedisplay();
}

void mousemotion(int X, int Y)
{
    if (presse) {
        anglex += (X - xold);
        angley += (Y - yold);
    }

    xold = X;
    yold = Y;
    glutPostRedisplay();
}


/****************************************************************************************/
/*                                  ANIMATION IDLE                                       */
/****************************************************************************************/

void idle()
{
    pikachu->IdleAnimation();
    glutPostRedisplay();
}


/****************************************************************************************/
/*                                  LUMIÈRES                                             */
/****************************************************************************************/

void gestionLumiere()
{
    glEnable(GL_LIGHTING);

    /* === LUMIÈRE 0 : Soleil (directionnelle) === */
    glEnable(GL_LIGHT0);

    GLfloat pos0[] = {1.0f, 1.0f, 0.5f, 0.0f}; // lumière directionnelle

    // composantes ambiantes, diffuses et spéculaires
    GLfloat amb0[]  = {0.15f, 0.15f, 0.15f, 1.0f};
    GLfloat diff0[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat spec0[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, pos0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  amb0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diff0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

   
}



/****************************************************************************************/
/*                              CHARGEMENT JPEG                                          */
/****************************************************************************************/

void loadJpegImage(const char* fichier,
                   unsigned char* buffer,
                   unsigned long larg,
                   unsigned long haut)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE* file;
    unsigned char* ligne;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    file = fopen(fichier, "rb");
    if (!file) {
        cerr << "ERREUR : impossible d'ouvrir " << fichier << endl;
        exit(1);
    }

    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    if (cinfo.image_width != larg || cinfo.image_height != haut) {
        cerr << "ERREUR : image doit être "
             << larg << " × " << haut << endl;
        exit(1);
    }

    jpeg_start_decompress(&cinfo);

    while (cinfo.output_scanline < cinfo.output_height)
    {
        ligne = buffer + 3 * larg * cinfo.output_scanline;
        jpeg_read_scanlines(&cinfo, &ligne, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);
}


