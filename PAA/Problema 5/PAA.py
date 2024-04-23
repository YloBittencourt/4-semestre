def mesclar(esq, dir):
    # Função para mesclar duas listas ordenadas juntamente com suas frequências
    resultado = []  # Lista para armazenar o resultado da mesclagem, iniciando como vazia
    i = 0  # Índice para percorrer a lista esquerda
    j = 0  # Índice para percorrer a lista direita
    tam_esq = len(esq)  # Tamanho da lista esquerda
    tam_dir = len(dir) # Tamanho da lista direita

    # Enquanto houver elementos em ambas as listas
    while i < tam_esq and j < tam_dir:
        # Se o elemento da lista esquerda é menor que o elemento da lista direita
        if esq[i][0] < dir[j][0]:
            # Adiciona o elemento da lista esquerda ao resultado
            resultado.append(esq[i])
            i += 1  # Move para o próximo elemento da lista esquerda
        # Se o elemento da lista esquerda é maior que o elemento da lista direita
        elif esq[i][0] > dir[j][0]:
            # Adiciona o elemento da lista direita ao resultado
            resultado.append(dir[j])
            j += 1  # Move para o próximo elemento da lista direita
        # Se os elementos são iguais
        else:
            # Combina os elementos e acumula suas frequências
            resultado.append((esq[i][0], esq[i][1] + dir[j][1]))
            i += 1  # Move para o próximo elemento da lista esquerda
            j += 1  # Move para o próximo elemento da lista direita
    
    # Adiciona os elementos restantes da lista esquerda ao resultado
    while i < tam_esq:
        resultado.append(esq[i])
        i += 1
    
    # Adiciona os elementos restantes da lista direita ao resultado
    while j < tam_dir:
        resultado.append(dir[j])
        j += 1

    return resultado  

def dividir_e_conquistar(vet):
    # Função para ordenar uma lista de elementos juntamente com suas frequências
    if len(vet) <= 1:  # Caso base: se a lista tem um elemento ou está vazia, retorna a lista
        return vet

    meio = len(vet) // 2  # Calcula o ponto médio da lista
    # Divide a lista em duas metades e chama recursivamente a função para cada metade
    esq = dividir_e_conquistar(vet[:meio])
    dir = dividir_e_conquistar(vet[meio:])

    # Chama a função mesclar para mesclar as duas metades ordenadas
    return mesclar(esq, dir)

def imprimir(vet):
    # Função para imprimir os elementos ordenados juntamente com suas frequências
    # Ordena os elementos chamando a função dividir_e_conquistar e imprime
    vet_ordenado = dividir_e_conquistar([(x, 1) for x in vet])
    for elem, freq in vet_ordenado:
        print("({}, {})".format(elem, freq), end=" ") 

# Solicita ao usuário os elementos do vetor
vetor = input("Digite os elementos do vetor separados por espaços: ")
vet = vetor.split()  # Divide a entrada em uma lista de elementos

print("Vetor ordenado juntamente com a frequência dos elementos:")
imprimir(vet)  # Imprime os elementos do vetor com suas frequências
