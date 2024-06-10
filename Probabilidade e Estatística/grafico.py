import random
import matplotlib.pyplot as plt
import numpy as np

# Gerando os dados
random.seed(1)  # Fixa a semente para tornar os resultados reproduzíveis
dados = [random.normalvariate(2, 1) for _ in range(100)]  # Gera uma lista de 100 números aleatórios com distribuição normal (média=5, desvio padrão=1)

def grafico(data):
    # Dicionário para armazenar a contagem de ocorrências de cada classe
    freq = {}
    for d in data:  # Itera sobre os dados
        classe = int(d)  # Arredonda cada valor para a classe mais próxima
        freq[classe] = freq.get(classe, 0) + 1  # Incrementa a contagem para a classe correspondente

    # Configura o layout para ter quatro gráficos em uma matriz 2x2
    fig, axs = plt.subplots(2, 2, figsize=(15, 10))

    # Gráfico de Barras
    axs[0, 0].bar(freq.keys(), freq.values(), color='blue', edgecolor='black')
    axs[0, 0].set_xlabel('Classes')
    axs[0, 0].set_ylabel('Frequência')
    axs[0, 0].set_title('Gráfico de Barras')

    # Histograma
    axs[0, 1].hist(data, bins=20, color='green', edgecolor='black')
    axs[0, 1].set_xlabel('Valor')
    axs[0, 1].set_ylabel('Frequência')
    axs[0, 1].set_title('Histograma')

    # Gráfico de Curvas
    density, bins, _ = axs[1, 0].hist(data, bins=30, density=True, alpha=0)  # Obtém a densidade dos dados
    center = (bins[:-1] + bins[1:]) / 2
    axs[1, 0].plot(center, density, color='red')
    axs[1, 0].set_xlabel('Valor')
    axs[1, 0].set_ylabel('Densidade')
    axs[1, 0].set_title('Gráfico de Curvas')

    # Gráfico de Pizza
    labels = list(freq.keys())
    sizes = list(freq.values())
    colors_pie = ['lightcoral', 'gold', 'yellowgreen', 'lightskyblue', 'lightpink', 'lightgrey', 'lightgreen', 'lightblue', 'lightyellow']

    axs[1, 1].pie(sizes, labels=labels, colors=colors_pie, autopct='%1.1f%%', shadow=True, startangle=140)
    axs[1, 1].axis('equal')  # Assegura que o gráfico de pizza seja desenhado como um círculo
    axs[1, 1].set_title('Gráfico de Pizza')

    plt.tight_layout()  # Ajusta o layout para evitar sobreposição
    plt.show()  # Exibe os gráficos

grafico(dados)  # Chama a função para gerar os gráficos
