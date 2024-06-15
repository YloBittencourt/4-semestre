#include <GL/glut.h>
#include <stdlib.h>

// Definindo os ângulos para as diversas partes do robô
static GLint ombroEsq = 0, cotoveloEsq = 0, maoEsq = 0;
static GLint ombroDir = 0, cotoveloDir = 0, maoDir = 0;
static GLint dedo1Esq = 0, dedo2Esq = 0, dedo1Dir = 0, dedo2Dir = 0;
static GLint pernaEsq = 0, joelhoEsq = 0, pernaDir = 0, joelhoDir = 0, peEsq = 0, peDir = 0;
static GLint cabeca = 0, pescoco = 0, tronco = 0;

// Função DesenhaQuadrado conforme pedido na questão
void DesenhaQuadrado(void) {
    glBegin(GL_LINE_LOOP);
        glVertex2f(-1, 1);
        glVertex2f(-1, -1);
        glVertex2f(1, -1);
        glVertex2f(1, 1);
    glEnd();
}

// Início da função para realizar os desenhos
void Desenho(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

        /*
        Hierarquia:
        Mexeu o pescoço -> Mexer a cabeça OK
        Mexeu o ombro -> Mexer o cotovelo -> Mexer a mão OK
        Mexeu o cotovelo -> Mexer a mão OK
        Mexeu o perna -> Mexer o joelho -> Mexer o pé OK
        Mexeu o joelho -> Mexer o pé OK
        */

    glPushMatrix();
        // Tronco
        glTranslatef(0.0, 1.0, 0.0);
        glRotatef((GLfloat) tronco, 0.0, 0.0, 1.0);
        glScalef(1.0, 2.0, 0.5);
        DesenhaQuadrado();
    glPopMatrix();

// Pescoço
glPushMatrix();
    glTranslatef(0.0, 3.0, 0.0); 
    glRotatef((GLfloat) pescoco, 0.0, 0.0, 1.0); 
    glTranslatef(0.0, 0.25, 0.0); 
    glScalef(0.3, 0.25, 1.0); 
    DesenhaQuadrado();

    // Cabeça
    glPushMatrix();
        glTranslatef(0.0, 0.5, 0.0); 
        glRotatef((GLfloat) cabeca, 0.0, 0.0, 1.0); 
        glTranslatef(0.0, 2.5, 0.0);
        glScalef(2.2, 2.0, 0.5); 
        DesenhaQuadrado();
    glPopMatrix();
glPopMatrix(); 

    // Braço Esquerdo 
    //Ombro
    glPushMatrix();
        glTranslatef(-1.5, 2.0, 0.0);
        glRotatef((GLfloat) ombroEsq, 0.0, 0.0, 1.0);
        glTranslatef(-0.3, 0.0, 0.0);
        glScalef(0.8, 0.3, 1.0);
        DesenhaQuadrado();
        
        // Cotovelo Esquerdo
        glPushMatrix();
            glTranslatef(-1.0, 0.0, 0.0);
            glRotatef((GLfloat) cotoveloEsq, 0.0, 0.0, 1.0);
            glTranslatef(-0.5, 0.0, 0.0);
            glScalef(0.5, 0.7, 1.0);
            DesenhaQuadrado();

            // Mão esquerda
            glPushMatrix();
                glTranslatef(-1.0, 0.0, 0.0);
                glRotatef((GLfloat) maoEsq, 0.0, 0.0, 1.0);
                glTranslatef(-0.5, 0.0, 0.0);
                glScalef(0.5, 0.3, 1.0);
                DesenhaQuadrado();
                
                // Dedos Esquerdo
                glPushMatrix();
                    glTranslatef(-0.5, 0.1, 0.0);
                    glRotatef((GLfloat) dedo1Esq, 0.0, 0.0, 1.0);
                    glTranslatef(-0.25, 0.0, 0.0);
                    glScalef(0.5, 0.1, 1.0);
                    DesenhaQuadrado();
                glPopMatrix();
                
                glPushMatrix();
                    glTranslatef(-0.5, -0.1, 0.0);
                    glRotatef((GLfloat) dedo2Esq, 0.0, 0.0, 1.0);
                    glTranslatef(-0.25, 0.0, 0.0);
                    glScalef(0.5, 0.1, 1.0);
                    DesenhaQuadrado();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    // Braço Direito
    glPushMatrix();
        glTranslatef(1.5, 2.0, 0.0);
        glRotatef((GLfloat) ombroDir, 0.0, 0.0, 1.0);
        glTranslatef(0.3, 0.0, 0.0);
        glScalef(0.8, 0.3, 1.0);
        DesenhaQuadrado();
        
        // Cotovelo direito
        glPushMatrix();
            glTranslatef(1.0, 0.0, 0.0);
            glRotatef((GLfloat) cotoveloDir, 0.0, 0.0, 1.0);
            glTranslatef(0.5, 0.0, 0.0);
            glScalef(0.5, 0.7, 1.0);
            DesenhaQuadrado();
            
            // Mão direita
            glPushMatrix();
                glTranslatef(1.0, 0.0, 0.0);
                glRotatef((GLfloat) maoDir, 0.0, 0.0, 1.0);
                glTranslatef(0.5, 0.0, 0.0);
                glScalef(0.5, 0.3, 1.0);
                DesenhaQuadrado();
                
                // Dedos Direito
                glPushMatrix();
                    glTranslatef(0.5, 0.1, 0.0);
                    glRotatef((GLfloat) dedo1Dir, 0.0, 0.0, 1.0);
                    glTranslatef(0.25, 0.0, 0.0);
                    glScalef(0.5, 0.1, 1.0);
                    DesenhaQuadrado();
                glPopMatrix();
                
                glPushMatrix();
                    glTranslatef(0.5, -0.1, 0.0);
                    glRotatef((GLfloat) dedo2Dir, 0.0, 0.0, 1.0);
                    glTranslatef(0.25, 0.0, 0.0);
                    glScalef(0.5, 0.1, 1.0);
                    DesenhaQuadrado();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    // Perna Esquerda
glPushMatrix();
    glTranslatef(-0.75, -1.5, 0.0);
    glRotatef((GLfloat) pernaEsq, 0.0, 0.0, 1.0);
    glTranslatef(0.2, -0.5, 0.0);
    glScalef(0.3, 1.0, 1.0);
    DesenhaQuadrado();
    
    // Joelho esquerdo
    glPushMatrix();
        glTranslatef(0.0, -1.0, 0.0);
        glRotatef((GLfloat) joelhoEsq, 0.0, 0.0, 1.0);
        glTranslatef(0.0, -0.5, 0.0);
        glScalef(0.5, 0.5, 1.0);
        DesenhaQuadrado();
        
        // Pé esquerdo
        glPushMatrix();
            glTranslatef(0.0, -1.5, 0.0); 
            glRotatef((GLfloat) peEsq, 0.0, 0.0, 1.0); 
            glTranslatef(0.0, 0.0, 0.0);
            glScalef(1.5, 0.5, 1.0); 
            DesenhaQuadrado();
        glPopMatrix();
    glPopMatrix();
glPopMatrix();

// Perna Direita (estrutura similar, ajuste as transformações conforme necessário)
glPushMatrix();
    glTranslatef(0.75, -1.5, 0.0);
    glRotatef((GLfloat) pernaDir, 0.0, 0.0, 1.0);
    glTranslatef(-0.2, -0.5, 0.0);
    glScalef(0.3, 1.0, 1.0);
    DesenhaQuadrado();

    glPushMatrix();
        glTranslatef(0.0, -1.0, 0.0);
        glRotatef((GLfloat) joelhoDir, 0.0, 0.0, 1.0);
        glTranslatef(0.0, -0.5, 0.0);
        glScalef(0.5, 0.5, 1.0);
        DesenhaQuadrado();

        glPushMatrix();
            glTranslatef(0.0, -1.5, 0.0);
            glRotatef((GLfloat) peDir, 0.0, 0.0, 1.0);
            glTranslatef(0.0, 0.0, 0.0);
            glScalef(1.5, 0.5, 1.0);
            DesenhaQuadrado();
        glPopMatrix();
    glPopMatrix();
glPopMatrix();

    glutSwapBuffers();
}

// Função para redimensionar
void Redimensionamento(GLint largura, GLint altura) {
    glViewport(0, 0, (GLsizei) largura, (GLsizei) altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Função para ler as teclas e realizar os comandos
void Teclado(unsigned char tecla, GLint x, GLint y) {
    //OBS: Fizemos cada case em uma linha para o código não ficar muito extenso
    switch (tecla) {
        case '1': cabeca = (cabeca + 5) % 360; break;
        case '2': cabeca = (cabeca - 5) % 360; break;
        case '3': pescoco = (pescoco + 5) % 360; break;
        case '4': pescoco = (pescoco - 5) % 360; break;
        case '5': tronco = (tronco + 5) % 360; break;
        case '6': tronco = (tronco - 5) % 360; break;
        case '7': ombroEsq = (ombroEsq + 5) % 360; break;
        case '8': ombroEsq = (ombroEsq - 5) % 360; break;
        case '9': ombroDir = (ombroDir + 5) % 360; break;
        case '0': ombroDir = (ombroDir - 5) % 360; break;
        case 'q': pernaEsq = (pernaEsq + 5) % 360; break;
        case 'w': pernaEsq = (pernaEsq - 5) % 360; break;
        case 'e': joelhoEsq = (joelhoEsq + 5) % 360; break;
        case 'r': joelhoEsq = (joelhoEsq - 5) % 360; break;
        case 't': peEsq = (peEsq + 5) % 360; break;
        case 'y': peEsq = (peEsq - 5) % 360; break;
        case 'u': peDir = (peDir + 5) % 360; break;
        case 'i': peDir = (peDir - 5) % 360; break;
        case 'o': pernaDir = (pernaDir + 5) % 360; break;
        case 'p': pernaDir = (pernaDir - 5) % 360; break;
        case 'a': cotoveloEsq = (cotoveloEsq + 5) % 360; break;
        case 's': cotoveloEsq = (cotoveloEsq - 5) % 360; break;
        case 'd': maoEsq = (maoEsq + 5) % 360; break;
        case 'f': maoEsq = (maoEsq - 5) % 360; break;
        case 'g': dedo1Esq = (dedo1Esq + 5) % 360; break;
        case 'h': dedo1Esq = (dedo1Esq - 5) % 360; break;
        case 'j': dedo2Esq = (dedo2Esq + 5) % 360; break;
        case 'k': dedo2Esq = (dedo2Esq - 5) % 360; break;
        case 'z': cotoveloDir = (cotoveloDir + 5) % 360; break;
        case 'x': cotoveloDir = (cotoveloDir - 5) % 360; break;
        case 'c': maoDir = (maoDir + 5) % 360; break;
        case 'v': maoDir = (maoDir - 5) % 360; break;
        case 'b': dedo1Dir = (dedo1Dir + 5) % 360; break;
        case 'n': dedo1Dir = (dedo1Dir - 5) % 360; break;
        case 'm': dedo2Dir = (dedo2Dir + 5) % 360; break;
        case ',': dedo2Dir = (dedo2Dir - 5) % 360; break;
        case '-': joelhoDir = (joelhoDir + 5) % 360; break;
        case '=': joelhoDir = (joelhoDir - 5) % 360; break;
        case 27: exit(0); break;
        default: break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(Desenho);
    glutReshapeFunc(Redimensionamento);
    glutKeyboardFunc(Teclado);
    glutMainLoop();
    return 0;
}

/*
'1' '2': Cabeça
'3' '4': Pescoço
'5' '6': Tronco
'7' '8': Ombro Esquerdo
'9' '0': Ombro Direito
'Q' 'W': Perna Esquerda
'E' 'R': Joelho Esquerdo
'T' 'Y': Pé Esquerdo
'U' 'I': Pé Direito
'O' 'P': Perna Direita
'A' 'S': Cotovelo Esquerdo
'D' 'F': Mão Esquerda
'G' 'H': Dedo1 Esquerdo
'J' 'K': Dedo2 Esquerdo
'Z' 'X': Cotovelo Direito
'C' 'V': Mão Direita
'B' 'N': Dedo1 Direito
'M' ',': Dedo2 Direito
'-' '=': Joelho Direito
ESC: Fechar
*/