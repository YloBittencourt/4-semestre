#include <GL/glut.h>  // Biblioteca para a criação de aplicações OpenGL usando GLUT
#include <stdio.h>    // Biblioteca padrão de entrada e saída
#include <stdlib.h>   // Biblioteca padrão para funções utilitárias

// Definindo macros para obter o sinal, valor absoluto e o piso de um número
#define SIGN(x) ((x) < 0 ? (-1) : (1))
#define ABS(x) ((x) < 0 ? (-x) : (x))
#define FLOOR(x) ((int)(x))

// Declaração das funções que serão usadas no programa
void displayDDA(void);
void displayPM(void);
void iniciarDDA(void);
void iniciarPM(void);
void keyboard(unsigned char key, int x, int y);
void desenhar_poligono(int n, float vertices[][2]);
void DDA(int x1, int y1, int x2, int y2);
void PM(int x1, int y1, int x2, int y2);
void ler_poligono();
void limpar_tela();

// Variáveis globais para armazenar os IDs das janelas GLUT e os vértices do polígono
int DDA_funcao, PM_function;
float vertices[10][2];  // Array para armazenar até 10 vértices
int nVertices;          // Número de vértices do polígono

// Função principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);  // Inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Define o modo de display

    // Inicializa as janelas e define as funções de callback
    iniciarDDA();
    iniciarPM();
    glutKeyboardFunc(keyboard);  // Define a função de callback para o teclado
    ler_poligono();  // Chama a função para ler os vértices do polígono

    glutMainLoop();  // Inicia o loop principal do GLUT
    return 0;  // Retorna 0 ao sistema operacional
}

// Função para inicializar a janela DDA
void iniciarDDA(void)
{
    glutInitWindowSize(640, 640);  // Define o tamanho da janela
    glutInitWindowPosition(10, 10);  // Define a posição da janela
    DDA_funcao = glutCreateWindow("DDA");  // Cria a janela com o título "DDA"
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Define a cor de fundo da janela
    glOrtho(-2, 12, -2, 12, -1, 1);  // Define a projeção ortogonal
    glutDisplayFunc(displayDDA);  // Define a função de display para a janela
}

// Função para inicializar a janela PM
void iniciarPM(void)
{
    glutInitWindowSize(640, 640);  // Define o tamanho da janela
    glutInitWindowPosition(700, 10);  // Define a posição da janela
    PM_function = glutCreateWindow("Ponto Médio");  // Cria a janela com o título "Ponto Médio"
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Define a cor de fundo da janela
    glOrtho(-2, 12, -2, 12, -1, 1);  // Define a projeção ortogonal
    glutDisplayFunc(displayPM);  // Define a função de display para a janela
}

// Função de display para a janela DDA
void displayDDA(void)
{
    limpar_tela();  // Limpa a tela
    glColor3f(0.0, 0.0, 0.0);  // Define a cor para preto
    desenhar_poligono(nVertices, vertices);  // Desenha o polígono
    glFlush();  // Garante que todos os comandos foram executados
}

// Função de display para a janela PM
void displayPM(void)
{
    limpar_tela();  // Limpa a tela
    glColor3f(0.0, 0.0, 0.0);  // Define a cor para preto
    desenhar_poligono(nVertices, vertices);  // Desenha o polígono
    glFlush();  // Garante que todos os comandos foram executados
}

// Função para desenhar um polígono
void desenhar_poligono(int n, float vertices[][2])
{
    int i;
    for (i = 0; i < n; i++)  // Loop através de todos os vértices do polígono
    {
        int x1 = vertices[i][0];
        int y1 = vertices[i][1];
        int x2 = vertices[(i + 1) % n][0];
        int y2 = vertices[(i + 1) % n][1];
        DDA(x1, y1, x2, y2);  // Desenha a linha usando o algoritmo DDA
        PM(x1, y1, x2, y2);  // Desenha a linha usando o algoritmo Ponto Médio
    }
    glBegin(GL_LINE_LOOP);  // Inicia o desenho de um loop de linhas
    for (i = 0; i < n; i++)  // Loop através de todos os vértices do polígono
    {
        glVertex2f(vertices[i][0], vertices[i][1]);  // Define os vértices do polígono
    }
    glEnd();  // Termina o desenho do loop de linhas
}

// Função para desenhar uma linha usando o algoritmo DDA
void DDA(int x1, int y1, int x2, int y2)
{
    int length;
    float deltax, deltay, x, y;
    int i;

    if (ABS(x2 - x1) >= ABS(y2 - y1))
        length = ABS(x2 - x1);
    else
        length = ABS(y2 - y1);

    deltax = (float)(x2 - x1) / (float)length;
    deltay = (float)(y2 - y1) / (float)length;

    x = x1 + 0.5 * SIGN(deltax);
    y = y1 + 0.5 * SIGN(deltay);

    // Loop para desenhar os pontos ao longo da linha
    for (i = 0; i < length; i++)
    {
        glBegin(GL_POINTS);  // Inicia o desenho de pontos
        glVertex2i(FLOOR(x), FLOOR(y));  // Define a posição do ponto
        glEnd();  // Termina o desenho de pontos
        x += deltax;  // Incrementa x
        y += deltay;  // Incrementa y
    }
}

// Função para desenhar uma linha usando o algoritmo do Ponto Médio
void PM(int x1, int y1, int x2, int y2)
{
    int deltax, deltay, signalx, signaly, interchange, tmp;
    int x, y, erro, i;

    deltax = ABS(x2 - x1);
    deltay = ABS(y2 - y1);
    signalx = SIGN(x2 - x1);
    signaly = SIGN(y2 - y1);
    x = x1;
    y = y1;

    if (signalx < 0)
        x -= 1;
    if (signaly < 0)
        y -= 1;
    interchange = 0;

    if (deltay > deltax)
    {
        tmp = deltax;
        deltax = deltay;
        deltay = tmp;
        interchange = 1;
    }

    erro = 2 * deltay - deltax;

    // Loop para desenhar os pontos ao longo da linha
    for (i = 0; i < deltax; i++)
    {
        glBegin(GL_POINTS);  // Inicia o desenho de pontos
        glVertex2i(x, y);  // Define a posição do ponto
        glEnd();  // Termina o desenho de pontos

        while (erro >= 0)
        {
            if (interchange)
                x = x + signalx;
            else
                y = y + signaly;
            erro = erro - 2 * deltax;
        }

        if (interchange)
            y = y + signaly;
        else
            x = x + signalx;
        erro = erro + 2 * deltay;
    }
}

// Função de callback para o teclado
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:  // Se a tecla 'Esc' for pressionada
        exit(0);  // Sai do programa
    case 'r':  // Se a tecla 'r' for pressionada
        ler_poligono();  // Lê novamente os vértices do polígono
        glutPostRedisplay();  // Solicita o redesenho da janela
        break;
    }
}

// Função para ler os vértices do polígono do usuário
void ler_poligono()
{
    printf("Digite o número de vértices do polígono (máximo 10): ");
    scanf("%d", &nVertices);

    if (nVertices < 3 || nVertices > 10)
    {
        printf("Número de vértices inválido!\n");
        return;
    }

    printf("Digite as coordenadas dos vértices:\n");
    int i;
    for (i = 0; i < nVertices; i++)
    {
        printf("Vértice %d (x y): ", i + 1);
        scanf("%f %f", &vertices[i][0], &vertices[i][1]);
    }
}

// Função para limpar a tela
void limpar_tela()
{
    glClear(GL_COLOR_BUFFER_BIT);  // Limpa o buffer de cor
    glLineWidth(2.0);  // Define a largura da linha
    glBegin(GL_LINES);  // Inicia o desenho de linhas
    glVertex3i(0, 0, 0.0);  // Define os vértices das linhas
    glVertex3i(0.0, 10, 0.0);
    glVertex3i(0.0, 0, 0.0);
    glVertex3i(10, 0, 0.0);
    glEnd();  // Termina o desenho de linhas
}
