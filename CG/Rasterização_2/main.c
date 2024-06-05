#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Protótipos de função
void exibirCirculo(int raio);
void iniciarJanelaCirculo(void);

// Função principal (main)
int main(int argc, char **argv)
{
    int raioCirculo = 0; // Declaração da variável que irá armazenar o raio do círculo

    // Verifica se o número de argumentos é correto (./main e valor do raio)
    if (argc != 2)
    {
        printf("Uso: %s <raio>\n", argv[0]); // Mensagem de uso correto do programa
        return 1; // Retorna erro
    }

    raioCirculo = atoi(argv[1]); // Converte o raio para um inteiro, já que inicialmente é uma string

    if (raioCirculo < 1 || raioCirculo > 10) // Verifica se o raio está dentro do intervalo de 1 a 10
    {
        printf("O raio deve estar entre 1 e 10.\n"); // Mensagem de raio inválido
        return 1; // Retorna erro
    }

    glutInit(&argc, argv); // Inicialização da GLUT
    iniciarJanelaCirculo(); // Chamada da função para configuração da janela
    exibirCirculo(raioCirculo); // Chamada da função para exibição do círculo com o raio fornecido
    glutMainLoop(); // Loop principal da GLUT
    return 0;
}

// Função para configurar a janela
void iniciarJanelaCirculo(void)
{
    glutInitWindowSize(640, 640); // Define o tamanho da janela
    glutInitWindowPosition(100, 100); // Define a posição da janela
    glutCreateWindow("Circulo"); // Cria a janela com o título "Circulo"
    glClearColor(1.0, 1.0, 1.1, 0.0); // Define a cor de fundo da janela
    glOrtho(-11, 11, -11, 11, -1, 1); // Define a projeção ortogonal
}

// Função para exibir o círculo
void exibirCirculo(int raio)
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cor
    glColor3f(0.0, 0.0, 0.0); // Define a cor do círculo como preto
    glLineWidth(2.0); // Define a largura da linha
    glBegin(GL_LINES); // Inicia a definição de linhas
    glVertex2i(0, -10); // Define os vértices da linha vertical
    glVertex2i(0, 10);
    glVertex2i(-10, 0); // Define os vértices da linha horizontal
    glVertex2i(10, 0);
    glEnd();

    // Algoritmo de rasterização do círculo utilizando o método do ponto médio (adaptado para criação de círculo)
    int x = 0;
    int y = raio;
    int d = 1 - raio;
    int deltaE = 3;
    int deltaSE = -2 * raio + 5;

    glColor3f(0.0, 0.0, 0.0); // Define a cor do círculo como preto
    glPointSize(4.0); // Define o tamanho do ponto

    glBegin(GL_POINTS); // Inicia a definição de pontos
    while (y >= x) // Loop para rasterizar o círculo
    {                     
        glVertex2i(x, y); // Plota os pontos do círculo em todas as oito octantes
        glVertex2i(y, x);
        glVertex2i(-x, y);
        glVertex2i(-y, x);
        glVertex2i(-x, -y);
        glVertex2i(-y, -x);
        glVertex2i(x, -y);
        glVertex2i(y, -x);

        if (d < 0) // Verifica a posição relativa do ponto em relação ao círculo
        { 
            d += deltaE;
            deltaE += 2;
            deltaSE += 2;
        }
        else
        {
            d += deltaSE;
            deltaE += 2;
            deltaSE += 4;
            y--; // Move para o próximo ponto
        }
        x++; // Move para o próximo ponto
    }
    glEnd(); // Finaliza a definição de pontos

    glFlush(); // Força a renderização
}
