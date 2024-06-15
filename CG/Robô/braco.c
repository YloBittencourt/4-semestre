#include <GL/glut.h>
#include <stdlib.h>

static GLint ombro = 0, cotovelo = 0, mao = 0;

void Desenho(void);
void Redimensionamento(GLint largura, GLint altura);
void Teclado (unsigned char tecla, GLint x, GLint y);
void DesenhaQuadrado(void);

void DesenhaQuadrado(void) {
     glBegin(GL_LINE_LOOP);
          glVertex2f(-1,1);
          glVertex2f(-1,-1);
          glVertex2f(1,-1);
          glVertex2f(1,1);
     glEnd();
}

void Desenho(void) {
   glClear (GL_COLOR_BUFFER_BIT);
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glPushMatrix();
        glTranslatef (-1.0, 0.0, 0.0);
        glRotatef ((GLfloat) ombro, 0.0, 0.0, 1.0);
        glTranslatef (1.0, 0.0, 0.0);
        glPushMatrix();
            glScalef(1.0, 0.3, 1.0);
            DesenhaQuadrado();
        glPopMatrix();
        glPushMatrix();
            glTranslatef (1.0, 0.0, 0.0);
            glRotatef ((GLfloat) cotovelo, 0.0, 0.0, 1.0);
            glTranslatef (1.0, 0.0, 0.0);
            glPushMatrix();
                glScalef(1.0, 0.3, 1.0);
                DesenhaQuadrado();
            glPopMatrix();
            glPushMatrix();
                glTranslatef (1.0, 0.0, 0.0);
                glRotatef ((GLfloat) mao, 0.0, 0.0, 1.0);
                glTranslatef (1.0, 0.0, 0.0);
                glPushMatrix();
                    glScalef(1.0, 0.3, 1.0);
                    DesenhaQuadrado();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
   glPopMatrix();
   glutSwapBuffers();
}

void Redimensionamento(GLint largura, GLint altura) {
   glViewport (0, 0, (GLsizei) largura, (GLsizei) altura);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D(-5.0,5.0,-5.0,5.0);//Exibição Bidimensional
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void Teclado (unsigned char tecla, GLint x, GLint y) {
   switch (tecla) {
      case 'a':
         ombro = (ombro + 5);
         break;
      case 's':
         ombro = (ombro - 5);
         break;
      case 'n':
         cotovelo = (cotovelo + 5);
         break;
      case 'm':
         cotovelo = (cotovelo - 5);
         break;
      case 'z':
         mao = (mao + 5);
         break;
      case 'x':
         mao = (mao - 5);
         break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (800, 800);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   glutDisplayFunc(Desenho);
   glutReshapeFunc(Redimensionamento);
   glutKeyboardFunc(Teclado);
   glutMainLoop();
   return 0;
}

