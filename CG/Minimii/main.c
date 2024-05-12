#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int R = 0, G = 0, B = 0;                                                    // Cores padrão
int rosto = 0, cabelo = 0, olhos = 0, boca = 0, sobrancelha = 0, nariz = 0; // Variáveis para controle dos elementos do rosto

void display(void);
void keyboard(unsigned char key, int x, int y);
void Special_keyboard(GLint tecla, int x, int y);
void DesenhaTexto(char *string);
void DesenhaRosto();
void DesenhaCabelo();
void DesenhaOlhos();
void DesenhaBoca();
void DesenhaSobrancelha();
void DesenhaNariz();

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    glClearColor(1.0, 1.0, 1.0, 0.0); // Cor de fundo branca
    glOrtho(-1, 1, -1, 1, -1, 1);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(Special_keyboard);
    glutMainLoop();
    return 0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    DesenhaTexto("Contorno facial: F1...F6\nCabelos: F7...F12\nOlhos: 1...6\nBoca: q, w, e, r, t, y\nSobrancelha: a, s, d, f, g, h\nNariz: z, x, c, v, b, n");
    glColor3ub(R, G, B); // Define a cor atual
    // Desenhar os elementos do rosto
    DesenhaRosto();
    DesenhaCabelo();
    DesenhaOlhos();
    DesenhaBoca();
    DesenhaSobrancelha();
    DesenhaNariz();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // Tecla ESC para sair
        exit(0);
        break;
    case 'q':
    case 'w':
    case 'e':
    case 'r':
    case 't':
    case 'y': // Teclas para a boca
        switch (key)
        {
        case 'q':
            boca = 1;
            break;
        case 'w':
            boca = 2;
            break;
        case 'e':
            boca = 3;
            break;
        case 'r':
            boca = 4;
            break;
        case 't':
            boca = 5;
            break;
        case 'y':
            boca = 6;
            break;
        }
        glutPostRedisplay();
        break;
    case 'a':
    case 's':
    case 'd':
    case 'f':
    case 'g':
    case 'h':                        // Teclas para a sobrancelha
        sobrancelha = key - 'a' + 1; // Adicionando 1 para ajustar ao novo número de opções
        glutPostRedisplay();
        break;
    case 'z':
    case 'x':
    case 'c':
    case 'v':
    case 'b':
    case 'n':                  // Teclas para o nariz
        nariz = key - 'z' + 1; // Adicionando 1 para ajustar ao novo número de opções
        glutPostRedisplay();
        break;
    default:
        olhos = key - '1' + 1; // Adicionando 1 para ajustar ao novo número de opções
        glutPostRedisplay();
        break;
    }
}

void Special_keyboard(GLint tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_F1:
    case GLUT_KEY_F2:
    case GLUT_KEY_F3:
    case GLUT_KEY_F4:
    case GLUT_KEY_F5:
    case GLUT_KEY_F6:                    // Teclas para o contorno facial
        rosto = tecla - GLUT_KEY_F1 + 1; // Adicionando 1 para ajustar ao novo número de opções
        glutPostRedisplay();
        break;
    case GLUT_KEY_F7:
    case GLUT_KEY_F8:
    case GLUT_KEY_F9:
    case GLUT_KEY_F10:
    case GLUT_KEY_F11:
    case GLUT_KEY_F12:                    // Teclas para o cabelo
        cabelo = tecla - GLUT_KEY_F7 + 1; // Adicionando 1 para ajustar ao novo número de opções
        glutPostRedisplay();
        break;
    }
}

void DesenhaTexto(char *string)
{
    glColor3ub(0, 0, 0);      // Cor preta para o texto
    glRasterPos2f(-0.9, 0.9); // Posição do texto na janela
    // Exibição do texto caracter por caracter
    while (*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *string++);
}

void DesenhaRosto()
{
    glColor3ub(255, 200, 150); // Cor da pele
    switch (rosto)
    {
    case 1: // Rosto quadrado
        glBegin(GL_POLYGON);
        // Modificando os vértices para formar um contorno facial
        glVertex2f(-0.6, -0.3); // Queixo esquerdo
        glVertex2f(-0.3, -0.5); // Queixo central
        glVertex2f(0.3, -0.5);  // Queixo direito
        glVertex2f(0.6, -0.3);  // Bochecha direita
        glVertex2f(0.6, 0.3);   // Bochecha direita
        glVertex2f(0.3, 0.6);   // Testa direita
        glVertex2f(-0.3, 0.6);  // Testa central
        glVertex2f(-0.6, 0.3);  // Bochecha esquerda
        glEnd();
        break;
    case 2: // Rosto circular
        glBegin(GL_POLYGON);
        // Modificando os vértices para formar um contorno facial mais redondo
        for (int i = 0; i <= 360; i += 10)
        {
            float angle = i * 3.14159 / 180;
            float x = 0.6 * cos(angle); // Ajuste do raio para a largura desejada
            float y = 0.6 * sin(angle); // Ajuste do raio para a altura desejada
            glVertex2f(x, y);
        }
        glEnd();
        break;
    case 3:
        glBegin(GL_POLYGON);
        // Modificando os vértices para formar um contorno facial losangular
        glVertex2f(-0.6, -0.3); // Queixo esquerdo
        glVertex2f(-0.3, -0.5); // Queixo central
        glVertex2f(0.3, -0.5);  // Queixo direito
        glVertex2f(0.6, -0.3);  // Bochecha direita
        glVertex2f(0.5, 0.4);   // Testa direita
        glVertex2f(0.0, 0.6);   // Testa central
        glVertex2f(-0.5, 0.4);  // Testa esquerda
        glEnd();
        break;
    case 4:
        glBegin(GL_POLYGON);
        // Metade superior redonda
        for (int i = 0; i <= 180; i += 10)
        {
            float angle = i * 3.14159 / 180;
            float x = 0.6 * cos(angle); // Ajuste do raio para a largura desejada
            float y = 0.6 * sin(angle); // Ajuste do raio para a altura desejada
            glVertex2f(x, y);
        }
        // Metade inferior losangular (triângulo invertido)
        glVertex2f(-0.5, -0.5); // Canto inferior esquerdo
        glVertex2f(0.5, -0.5);  // Canto inferior direito
        glVertex2f(0.0, -1.0);  // Canto superior
        glVertex2f(-0.5, -0.5); // Parte esquerda do losango inferior
        glEnd();
        break;
    case 5: // Rosto losangular
    glBegin(GL_POLYGON);
    // Modificando os vértices para formar um contorno facial hexagonal
    glVertex2f(-0.6, -0.3); // Queixo esquerdo
    glVertex2f(-0.4, -0.6); // Queixo central esquerdo
    glVertex2f(0.4, -0.6);  // Queixo central direito
    glVertex2f(0.6, -0.3);  // Queixo direito
    glVertex2f(0.4, 0.3);   // Testa direita
    glVertex2f(-0.4, 0.3);  // Testa esquerda
    glEnd();
        break;
    case 6:
        glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.4);
        glVertex2f(-0.3, -0.3);
        glVertex2f(-0.1, -0.2);
        glVertex2f(0.1, -0.2);
        glVertex2f(0.3, -0.3);
        glVertex2f(0.5, -0.4);
        glVertex2f(0.5, 0.3);
        glVertex2f(-0.5, 0.3);
        glEnd();
        break;
    }
}

void DesenhaCabelo()
{
    switch (cabelo)
    {
    case 1:                      // Moicano marrom
        glColor3ub(139, 69, 19); // Marrom
        glBegin(GL_POLYGON);
        glVertex2f(-0.3, 0.5);
        glVertex2f(0.3, 0.5);
        glVertex2f(0.1, 0.8);
        glVertex2f(-0.1, 0.8);
        glEnd();
        break;
    case 2:                  // Cabelo liso preto
        glColor3ub(0, 0, 0); // Preto
        glBegin(GL_POLYGON);
        glVertex2f(-0.3, 0.5);
        glVertex2f(0.3, 0.5);
        glVertex2f(0.5, 0.9);
        glVertex2f(-0.5, 0.9);
        glEnd();
        break;
    case 3:                      // Cabelo cacheado marrom
        glColor3ub(139, 69, 19); // Marrom
        glBegin(GL_POLYGON);
        glVertex2f(-0.3, 0.5);
        glVertex2f(0.3, 0.5);
        glVertex2f(0.5, 0.9);
        glVertex2f(-0.5, 0.9);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(-0.5, 0.9);
        glVertex2f(0.5, 0.9);
        glVertex2f(0.3, 1.0);
        glVertex2f(-0.3, 1.0);
        glEnd();
        break;
    case 4:                  // Cabelo calvo preto
        glColor3ub(0, 0, 0); // Preto
        glBegin(GL_POLYGON);
        glVertex2f(-0.3, 0.5);
        glVertex2f(0.3, 0.5);
        glVertex2f(0.5, 0.8);
        glVertex2f(-0.5, 0.8);
        glEnd();
        break;
    case 5:                      // Cabelo espetado loiro
        glColor3ub(255, 215, 0); // Loiro
        glBegin(GL_POLYGON);
        glVertex2f(-0.3, 0.5);
        glVertex2f(0.3, 0.5);
        glVertex2f(0.2, 0.8);
        glVertex2f(-0.2, 0.8);
        glEnd();
        break;
    case 6:                  // Cabelo longo preto
        glColor3ub(0, 0, 0); // Preto
        glBegin(GL_POLYGON);
        glVertex2f(-0.3, 0.5);
        glVertex2f(0.3, 0.5);
        glVertex2f(0.6, 1.0);
        glVertex2f(-0.6, 1.0);
        glEnd();
        break;
    }
}

void DesenhaOlhos()
{
    switch (olhos)
    {
    case 1:                    // Olhos redondos verdes
        glColor3ub(0, 128, 0); // Verde
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 5)
        {
            float angle = i * 3.14159 / 180;
            glVertex2f(-0.25 + 0.1 * cos(angle), 0.1 + 0.1 * sin(angle));
        }
        glEnd();
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 5)
        {
            float angle = i * 3.14159 / 180;
            glVertex2f(0.25 + 0.1 * cos(angle), 0.1 + 0.1 * sin(angle));
        }
        glEnd();
        break;
    case 2:                    // Olhos voltados para cima azuis
        glColor3ub(0, 0, 255); // Azul
        glBegin(GL_POLYGON);
        for (int i = 180; i < 360; i += 5)
        {
            float angle = i * 3.14159 / 180;
            glVertex2f(-0.25 + 0.1 * cos(angle), 0.1 + 0.1 * sin(angle));
        }
        glVertex2f(-0.35, 0.2);
        glEnd();
        glBegin(GL_POLYGON);
        for (int i = 180; i < 360; i += 5)
        {
            float angle = i * 3.14159 / 180;
            glVertex2f(0.25 + 0.1 * cos(angle), 0.1 + 0.1 * sin(angle));
        }
        glVertex2f(0.35, 0.2);
        glEnd();
        break;
    case 3:                      // Olhos tipo coreano castanhos
        glColor3ub(139, 69, 19); // Marrom
        glBegin(GL_POLYGON);
        glVertex2f(-0.25, 0.2);
        glVertex2f(-0.15, 0.2);
        glVertex2f(-0.2, 0.3);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0.25, 0.2);
        glVertex2f(0.15, 0.2);
        glVertex2f(0.2, 0.3);
        glEnd();
        break;
    case 4:
        glColor3ub(139, 69, 19); // Marrom
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 5)
        {
            float angle = i * 3.14159 / 180;
            glVertex2f(-0.25 + 0.1 * cos(angle), 0.1 + 0.1 * sin(angle));
        }
        glEnd();
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 5)
        {
            float angle = i * 3.14159 / 180;
            glVertex2f(0.25 + 0.1 * cos(angle), 0.1 + 0.1 * sin(angle));
        }
        glEnd();
        break;
    case 5:
        glColor3ub(0, 128, 0);
        glBegin(GL_POLYGON);
        for (int i = 180; i < 360; i += 5)
        {
            float angle = i * 3.14159 / 180;
            glVertex2f(-0.25 + 0.1 * cos(angle), 0.1 + 0.1 * sin(angle));
        }
        glVertex2f(-0.35, 0.2);
        glEnd();
        glBegin(GL_POLYGON);
        for (int i = 180; i < 360; i += 5)
        {
            float angle = i * 3.14159 / 180;
            glVertex2f(0.25 + 0.1 * cos(angle), 0.1 + 0.1 * sin(angle));
        }
        glVertex2f(0.35, 0.2);
        glEnd();
        break;
    case 6:
        glColor3ub(0, 0, 0); // Azul
        glBegin(GL_POLYGON);
        for (int i = 180; i < 360; i += 5)
        {
            float angle = i * 3.14159 / 180;
            glVertex2f(-0.25 + 0.1 * cos(angle), 0.1 + 0.1 * sin(angle));
        }
        glVertex2f(-0.35, 0.2);
        glEnd();
        glBegin(GL_POLYGON);
        for (int i = 180; i < 360; i += 5)
        {
            float angle = i * 3.14159 / 180;
            glVertex2f(0.25 + 0.1 * cos(angle), 0.1 + 0.1 * sin(angle));
        }
        glVertex2f(0.35, 0.2);
        glEnd();
        break;
    }
}

void DesenhaBoca()
{
    switch (boca)
    {
    case 1:                    // Boca sorrindo
        glColor3ub(255, 0, 0); // Vermelho
        glBegin(GL_POLYGON);
        for (int i = 180; i < 360; i += 5)
        {
            float angle = i * 3.14159 / 180;
            glVertex2f(0.2 * cos(angle), -0.2 + 0.1 * sin(angle));
        }
        glEnd();
        break;
    case 2:                    // Boca triste
        glColor3ub(255, 0, 0); // Vermelho
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 5)
        {
            float angle = i * 3.14159 / 180;
            glVertex2f(0.15 * cos(angle), -0.25 + 0.1 * sin(angle));
        }
        glEnd();
        break;
    case 3:                    // Boca séria
        glColor3ub(255, 0, 0); // Vermelho
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.1, -0.3);
        glVertex2f(0.1, -0.3);
        glVertex2f(0.0, -0.4);
        glEnd();
        break;
    case 4:                    // Boca larga
        glColor3ub(255, 0, 0); // Vermelho
        glBegin(GL_POLYGON);
        glVertex2f(-0.2, -0.3);
        glVertex2f(0.2, -0.3);
        glVertex2f(0.2, -0.4);
        glVertex2f(-0.2, -0.4);
        glEnd();
        break;
    case 5:                    // Boca fina
        glColor3ub(255, 0, 0); // Vermelho
        glBegin(GL_POLYGON);
        glVertex2f(-0.15, -0.3);
        glVertex2f(0.15, -0.3);
        glVertex2f(0.15, -0.35);
        glVertex2f(-0.15, -0.35);
        glEnd();
        break;
    case 6:                    // Boca pequena
        glColor3ub(255, 0, 0); // Vermelho
        glBegin(GL_POLYGON);
        glVertex2f(-0.15, -0.3);
        glVertex2f(0.15, -0.3);
        glVertex2f(0.15, -0.4);
        glVertex2f(-0.15, -0.4);
        glEnd();
        break;
    }
}

void DesenhaSobrancelha()
{
    switch (sobrancelha)
    {
    case 1:                  // Sobrancelha levantada
        glColor3ub(0, 0, 0); // Preto
        glBegin(GL_POLYGON);
        glVertex2f(-0.2, 0.35);
        glVertex2f(-0.1, 0.4);
        glVertex2f(-0.15, 0.4);
        glVertex2f(-0.25, 0.35);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0.1, 0.4);
        glVertex2f(0.2, 0.35);
        glVertex2f(0.25, 0.35);
        glVertex2f(0.15, 0.4);
        glEnd();
        break;
    case 2:                  // Sobrancelha arqueada
        glColor3ub(0, 0, 0); // Preto
        glBegin(GL_POLYGON);
        glVertex2f(-0.2, 0.37);
        glVertex2f(-0.15, 0.42);
        glVertex2f(-0.1, 0.37);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0.1, 0.37);
        glVertex2f(0.15, 0.42);
        glVertex2f(0.2, 0.37);
        glEnd();
        break;
    case 3:                  // Sobrancelha reta
        glColor3ub(0, 0, 0); // Preto
        glBegin(GL_POLYGON);
        glVertex2f(-0.2, 0.37);
        glVertex2f(-0.1, 0.42);
        glVertex2f(-0.1, 0.37);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0.1, 0.37);
        glVertex2f(0.1, 0.42);
        glVertex2f(0.2, 0.37);
        glEnd();
        break;
    case 4: // Sem sobrancelha
        break;
    case 5:                  // Sobrancelha caída
        glColor3ub(0, 0, 0); // Preto
        glBegin(GL_POLYGON);
        glVertex2f(-0.2, 0.42);
        glVertex2f(-0.1, 0.37);
        glVertex2f(-0.15, 0.37);
        glVertex2f(-0.25, 0.42);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0.1, 0.37);
        glVertex2f(0.2, 0.42);
        glVertex2f(0.25, 0.42);
        glVertex2f(0.15, 0.37);
        glEnd();
        break;
    case 6:                  // Sobrancelha grossa
        glColor3ub(0, 0, 0); // Preto
        glBegin(GL_POLYGON);
        glVertex2f(-0.2, 0.37);
        glVertex2f(-0.1, 0.47);
        glVertex2f(-0.1, 0.37);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0.1, 0.37);
        glVertex2f(0.1, 0.47);
        glVertex2f(0.2, 0.37);
        glEnd();
        break;
    }
}

void DesenhaNariz()
{
    switch (nariz)
    {
    case 1:                      // Nariz pequeno
        glColor3ub(255, 128, 0); // Laranja
        glBegin(GL_POLYGON);
        glVertex2f(-0.05, 0.01); 
        glVertex2f(0.05, 0.01);  
        glVertex2f(0.0, -0.05);  
        glEnd();
        break;
    case 2:                      // Nariz grande
        glColor3ub(255, 128, 0); // Laranja
        glBegin(GL_POLYGON);
        glVertex2f(-0.05, 0.01); 
        glVertex2f(0.05, 0.01);  
        glVertex2f(0.0, -0.05);  
        glEnd();
        break;
    case 3:                      // Nariz fino
        glColor3ub(255, 128, 0); // Laranja
        glBegin(GL_POLYGON);
        glVertex2f(-0.05, 0.075);
        glVertex2f(0.05, 0.075);
        glVertex2f(0.0, 0.0);
        glEnd();
        break;
    case 4:                      // Nariz largo
        glColor3ub(255, 128, 0); // Laranja
        glBegin(GL_POLYGON);
        glVertex2f(-0.075, 0.05);
        glVertex2f(0.075, 0.05);
        glVertex2f(0.0, 0.0);
        glEnd();
        break;
    case 5:                      // Nariz fino e largo
        glColor3ub(255, 128, 0); // Laranja
        glBegin(GL_POLYGON);
        glVertex2f(-0.075, 0.075);
        glVertex2f(0.075, 0.075);
        glVertex2f(0.0, 0.0);
        glEnd();
        break;
    case 6:                      // Nariz arrebitado
        glColor3ub(255, 128, 0); // Laranja
        glBegin(GL_POLYGON);
        glVertex2f(-0.05, 0.1);
        glVertex2f(0.05, 0.1);
        glVertex2f(0.0, 0.0);
        glEnd();
        break;
    }
}