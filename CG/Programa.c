#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Para a função abs()

#define MAX_PIXEL_DIFF 255 // Define o valor máximo de diferença entre pixels

// Declaração de variáveis
FILE *fpin1, *fpin2, *fpout_sub, *fpout_seg; // Primeira imagem, segunda imagem, imagem subtraida e imagem segmentada
int **imagem1R, **imagem1G, **imagem1B; // Matrizes R, G e B da primeira imagem
int **imagem2R, **imagem2G, **imagem2B; // Matrizes R, G e B da segunda imagem
int **imagemSubR, **imagemSubG, **imagemSubB; // Matrizes para a imagem da subtração
int **imagemSegR, **imagemSegG, **imagemSegB; // Matrizes para a imagem da segmentação
int ncol, nlin, quant_nivel_cinza;

// Protótipos de funções (tem no classroom)
void abrir_arquivos(int argc, char *argv[]);
void ler_cabecalho(FILE *fp);
void ler_imagem(FILE *fp, int ***imagemR, int ***imagemG, int ***imagemB);
void calcular_subtracao_segmentacao(int pixel_diff);
void gravar_imagem(void);
void gravar_segmentacao_imagem(void);
void fechar_arquivos(void);
void liberar_memoria(int ***imagemR, int ***imagemG, int ***imagemB);

void abrir_arquivos(int argc, char *argv[]) {
    if (argc < 6) {
        printf("Modo correto de uso: <prog> <imagem1> <imagem2> <imagemSub> <imagemSeg> <percentual_erro>\n");
        exit(0);
    }
    if ((fpin1 = fopen(argv[1], "r")) == NULL || (fpin2 = fopen(argv[2], "r")) == NULL) {
        printf("Nao foi possivel abrir algum dos arquivos de imagem\n");
        exit(1);
    }
    if ((fpout_sub = fopen(argv[3], "w")) == NULL || (fpout_seg = fopen(argv[4], "w")) == NULL) {
        printf("Nao foi possivel abrir arquivo de saida\n");
        exit(1);
    }
}

void ler_cabecalho(FILE *fp) {
    char controle[4];
    fscanf(fp, "%s\n", controle);
    fscanf(fp, "%d %d\n", &ncol, &nlin); 
    fscanf(fp, "%d\n", &quant_nivel_cinza); 
}

void ler_imagem(FILE *fp, int ***imagemR, int ***imagemG, int ***imagemB) {
    int cont, col, lin;
    *imagemR = (int **)malloc((nlin + 1) * sizeof(int *)); 
    *imagemG = (int **)malloc((nlin + 1) * sizeof(int *)); 
    *imagemB = (int **)malloc((nlin + 1) * sizeof(int *)); 
    for (cont = 0; cont < nlin; cont++) {
        (*imagemR)[cont] = (int *)malloc(ncol * sizeof(int)); 
        (*imagemG)[cont] = (int *)malloc(ncol * sizeof(int)); 
        (*imagemB)[cont] = (int *)malloc(ncol * sizeof(int)); 
        if ((*imagemR)[cont] == NULL || (*imagemG)[cont] == NULL || (*imagemB)[cont] == NULL) {
            printf("Falha na alocacao de memoria\n");
            exit(1);
        }
    }
    for (lin = 0; lin < nlin; lin++) {
        for (col = 0; col < ncol; col++) {
            fscanf(fp, "%d", &(*imagemR)[lin][col]);
            fscanf(fp, "%d", &(*imagemG)[lin][col]);
            fscanf(fp, "%d", &(*imagemB)[lin][col]);
        }
    }
}

// Função para calcular a subtração e segmentação das imagens
void calcular_subtracao_segmentacao(int pixel_diff) {
    // Aloca memória para as matrizes resultantes da subtração e segmentação
    imagemSubR = (int **)malloc(nlin * sizeof(int *));
    imagemSubG = (int **)malloc(nlin * sizeof(int *));
    imagemSubB = (int **)malloc(nlin * sizeof(int *));
    imagemSegR = (int **)malloc(nlin * sizeof(int *));
    imagemSegG = (int **)malloc(nlin * sizeof(int *));
    imagemSegB = (int **)malloc(nlin * sizeof(int *));
    for (int i = 0; i < nlin; i++) {
        imagemSubR[i] = (int *)malloc(ncol * sizeof(int));
        imagemSubG[i] = (int *)malloc(ncol * sizeof(int));
        imagemSubB[i] = (int *)malloc(ncol * sizeof(int));
        imagemSegR[i] = (int *)malloc(ncol * sizeof(int));
        imagemSegG[i] = (int *)malloc(ncol * sizeof(int));
        imagemSegB[i] = (int *)malloc(ncol * sizeof(int));
    }

    // Percorre os pixels das imagens e realiza a subtração e segmentação
    for (int i = 0; i < nlin; i++) {
        for (int j = 0; j < ncol; j++) {
            int diffR = abs(imagem1R[i][j] - imagem2R[i][j]);
            int diffG = abs(imagem1G[i][j] - imagem2G[i][j]);
            int diffB = abs(imagem1B[i][j] - imagem2B[i][j]);
            // Verifica se a diferença entre os pixels é maior que o limite definido
            if (diffR > pixel_diff || diffG > pixel_diff || diffB > pixel_diff) {
                // Se sim, copia o pixel da primeira imagem para a imagem de subtração
                // e atribui o valor máximo de intensidade (255) para a imagem de segmentação
                imagemSubR[i][j] = imagem1R[i][j];
                imagemSubG[i][j] = imagem1G[i][j];
                imagemSubB[i][j] = imagem1B[i][j];
                imagemSegR[i][j] = 255;
                imagemSegG[i][j] = 255;
                imagemSegB[i][j] = 255;
            } else {
                // Se não, atribui valor zero para os pixels das imagens de subtração e segmentação
                imagemSubR[i][j] = 0;
                imagemSubG[i][j] = 0;
                imagemSubB[i][j] = 0;
                imagemSegR[i][j] = 0;
                imagemSegG[i][j] = 0;
                imagemSegB[i][j] = 0;
            }
        }
    }
}

// Função para gravar a imagem de subtração em arquivo
void gravar_imagem(void) {
    int lin, col;
    fprintf(fpout_sub, "P3\n"); // Escreve o tipo de arquivo P3
    fprintf(fpout_sub, "%d %d\n", ncol, nlin); // Escreve as dimensões da imagem
    fprintf(fpout_sub, "%d\n", quant_nivel_cinza); // Escreve o número de níveis de cinza

    // Escreve os valores RGB de cada pixel da imagem de subtração
    for (lin = 0; lin < nlin; lin++) {
        for (col = 0; col < ncol; col++) {
            fprintf(fpout_sub, "%d ", imagemSubR[lin][col]);
            fprintf(fpout_sub, "%d ", imagemSubG[lin][col]);
            fprintf(fpout_sub, "%d ", imagemSubB[lin][col]);
        }
        fprintf(fpout_sub, "\n");
    }
}

// Função para gravar a imagem de segmentação em arquivo
void gravar_segmentacao_imagem(void) {
    int lin, col;
    fprintf(fpout_seg, "P3\n"); // Escreve o tipo de arquivo P3
    fprintf(fpout_seg, "%d %d\n", ncol, nlin); // Escreve as dimensões da imagem
    fprintf(fpout_seg, "%d\n", quant_nivel_cinza); // Escreve o número de níveis de cinza

    // Escreve os valores RGB de cada pixel da imagem de segmentação
    for (lin = 0; lin < nlin; lin++) {
        for (col = 0; col < ncol; col++) {
            fprintf(fpout_seg, "%d ", imagemSegR[lin][col]);
            fprintf(fpout_seg, "%d ", imagemSegG[lin][col]);
            fprintf(fpout_seg, "%d ", imagemSegB[lin][col]);
        }
        fprintf(fpout_seg, "\n");
    }
}

// Função para fechar os arquivos abertos
void fechar_arquivos(void) {
    fclose(fpin1);
    fclose(fpin2);
    fclose(fpout_sub);
    fclose(fpout_seg);
}

// Função para liberar a memória alocada para as imagens
void liberar_memoria(int ***imagemR, int ***imagemG, int ***imagemB) {
    int i;
    for (i = 0; i < nlin; i++) {
        free((*imagemR)[i]);
        free((*imagemG)[i]);
        free((*imagemB)[i]);
    }
    free(*imagemR);
    free(*imagemG);
    free(*imagemB);
}

// Função principal
int main(int argc, char *argv[]) {
    abrir_arquivos(argc, argv); // Abre os arquivos de entrada e saída
    // Ler cabeçalhos e imagens das duas entradas
    ler_cabecalho(fpin1);
    ler_cabecalho(fpin2);
    ler_imagem(fpin1, &imagem1R, &imagem1G, &imagem1B);
    ler_imagem(fpin2, &imagem2R, &imagem2G, &imagem2B);

    // Calcular subtração e segmentação com base no percentual de erro
    int percentual_erro = atoi(argv[5]);
    int pixel_diff = MAX_PIXEL_DIFF * percentual_erro / 100;
    calcular_subtracao_segmentacao(pixel_diff);
    gravar_imagem();
    gravar_segmentacao_imagem();

    // Liberar memória alocada e fechar arquivos
    liberar_memoria(&imagem1R, &imagem1G, &imagem1B);
    liberar_memoria(&imagem2R, &imagem2G, &imagem2B);
    fechar_arquivos();

    return 0;
}
