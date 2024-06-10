#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// Variáveis globais para armazenar as imagens e dimensões
int **imagemR, **imagemG, **imagemB;
int **imagem1VizinhoR, **imagem1VizinhoG, **imagem1VizinhoB;
int **imagem4VizinhosR, **imagem4VizinhosG, **imagem4VizinhosB;
unsigned char *imagemDisplay;
int largura, altura, quant_nivel_cinza;
int m, n;

// Função para abrir a imagem PPM
void abrirImagem(const char *nomeArquivo)
{
    FILE *fp;
        if ((fp = fopen(nomeArquivo, "r")) == NULL)
    {
        printf("Não foi possível abrir o arquivo  %s\n", nomeArquivo);
        exit(1);
    }

    // Ler o cabeçalho
    char controle[4];
    fscanf(fp, "%s\n", controle);
    fscanf(fp, "%d %d\n", &largura, &altura);
    fscanf(fp, "%d\n", &quant_nivel_cinza);

    // Alocar memória para a imagem
    imagemR = (int **)malloc(altura * sizeof(int *));
    imagemG = (int **)malloc(altura * sizeof(int *));
    imagemB = (int **)malloc(altura * sizeof(int *));
    for (int i = 0; i < altura; ++i)
    {
        imagemR[i] = (int *)malloc(largura * sizeof(int));
        imagemG[i] = (int *)malloc(largura * sizeof(int));
        imagemB[i] = (int *)malloc(largura * sizeof(int));
    }

    // Ler a imagem
    for (int i = 0; i < altura; ++i)
    {
        for (int j = 0; j < largura; ++j)
        {
            fscanf(fp, "%d", &imagemR[i][j]);
            fscanf(fp, "%d", &imagemG[i][j]);
            fscanf(fp, "%d", &imagemB[i][j]);
        }
    }

    fclose(fp);
}

// Função para interpolação 1-vizinho
void interpolacao1Vizinho()
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int oldX = i * altura / m;
            int oldY = j * largura / n;
            imagem1VizinhoR[i][j] = imagemR[oldX][oldY];
            imagem1VizinhoG[i][j] = imagemG[oldX][oldY];
            imagem1VizinhoB[i][j] = imagemB[oldX][oldY];
        }
    }
}

// Função para interpolação 4-vizinhos (média aritmética)
void interpolacao4Vizinhos()
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int oldX = i * altura / m;
            int oldY = j * largura / n;
            int somaR = 0, somaG = 0, somaB = 0;
            int contagem = 0;
            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    int nx = oldX + dx;
                    int ny = oldY + dy;
                    if (nx >= 0 && nx < altura && ny >= 0 && ny < largura)
                    {
                        somaR += imagemR[nx][ny];
                        somaG += imagemG[nx][ny];
                        somaB += imagemB[nx][ny];
                        contagem++;
                    }
                }
            }
            imagem4VizinhosR[i][j] = somaR / contagem;
            imagem4VizinhosG[i][j] = somaG / contagem;
            imagem4VizinhosB[i][j] = somaB / contagem;
        }
    }
}

// Função para preparar a imagem a ser exibida com OpenGL
void Preparar_Imagem()
{
    int larguraTotal = n * 2;
    imagemDisplay = (unsigned char *)malloc(m * larguraTotal * 3 * sizeof(unsigned char));

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            // Ajuste da ordem dos pixels para corrigir a inversão
            imagemDisplay[((m - 1 - i) * larguraTotal + j) * 3] = (unsigned char)imagem1VizinhoR[i][j];
            imagemDisplay[((m - 1 - i) * larguraTotal + j) * 3 + 1] = (unsigned char)imagem1VizinhoG[i][j];
            imagemDisplay[((m - 1 - i) * larguraTotal + j) * 3 + 2] = (unsigned char)imagem1VizinhoB[i][j];

            imagemDisplay[((m - 1 - i) * larguraTotal + (j + n)) * 3] = (unsigned char)imagem4VizinhosR[i][j];
            imagemDisplay[((m - 1 - i) * larguraTotal + (j + n)) * 3 + 1] = (unsigned char)imagem4VizinhosG[i][j];
            imagemDisplay[((m - 1 - i) * larguraTotal + (j + n)) * 3 + 2] = (unsigned char)imagem4VizinhosB[i][j];
        }
    }
}

// Função para exibir as imagens utilizando OpenGL
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(n * 2, m, GL_RGB, GL_UNSIGNED_BYTE, imagemDisplay);
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Uso: %s <nome_do_arquivo.ppm> <m> <n>\n", argv[0]);
        return 1;
    }

    char *nomeArquivo = argv[1];
    m = atoi(argv[2]);
    n = atoi(argv[3]);

    abrirImagem(nomeArquivo);

    // Alocar memória para as novas imagens
    imagem1VizinhoR = (int **)malloc(m * sizeof(int *));
    imagem1VizinhoG = (int **)malloc(m * sizeof(int *));
    imagem1VizinhoB = (int **)malloc(m * sizeof(int *));
    imagem4VizinhosR = (int **)malloc(m * sizeof(int *));
    imagem4VizinhosG = (int **)malloc(m * sizeof(int *));
    imagem4VizinhosB = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i)
    {
        imagem1VizinhoR[i] = (int *)malloc(n * sizeof(int));
        imagem1VizinhoG[i] = (int *)malloc(n * sizeof(int));
        imagem1VizinhoB[i] = (int *)malloc(n * sizeof(int));
        imagem4VizinhosR[i] = (int *)malloc(n * sizeof(int));
        imagem4VizinhosG[i] = (int *)malloc(n * sizeof(int));
        imagem4VizinhosB[i] = (int *)malloc(n * sizeof(int));
    }

    interpolacao1Vizinho();
    interpolacao4Vizinhos();

    Preparar_Imagem();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(n * 2, m);
    glutCreateWindow("Interpolação de Imagens");
    glutDisplayFunc(display);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop();

    // Liberar memória alocada
    for (int i = 0; i < m; ++i)
    {
        free(imagem1VizinhoR[i]);
        free(imagem1VizinhoG[i]);
        free(imagem1VizinhoB[i]);
        free(imagem4VizinhosR[i]);
        free(imagem4VizinhosG[i]);
        free(imagem4VizinhosB[i]);
    }
    free(imagem1VizinhoR);
    free(imagem1VizinhoG);
    free(imagem1VizinhoB);
    free(imagem4VizinhosR);
    free(imagem4VizinhosG);
    free(imagem4VizinhosB);

    for (int i = 0; i < altura; ++i)
    {
        free(imagemR[i]);
        free(imagemG[i]);
        free(imagemB[i]);
    }
    free(imagemR);
    free(imagemG);
    free(imagemB);
    free(imagemDisplay);

    return 0;
}
