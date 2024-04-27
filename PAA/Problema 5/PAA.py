def mesclar(esq, dir):
    resultado = []
    i = j = 0
    tam_esq = len(esq)
    tam_dir = len(dir)

    while i < tam_esq and j < tam_dir:
        if esq[i][0] < dir[j][0]:
            resultado.append(esq[i])
            i += 1
        elif esq[i][0] > dir[j][0]:
            resultado.append(dir[j])
            j += 1
        else:
            resultado.append((esq[i][0], esq[i][1] + dir[j][1]))
            i += 1
            j += 1

    while i < tam_esq:
        resultado.append(esq[i])
        i += 1

    while j < tam_dir:
        resultado.append(dir[j])
        j += 1

    return resultado

def dividir_e_conquistar(arr):
    if len(arr) <= 1:
        return arr

    meio = len(arr) // 2
    esq = dividir_e_conquistar(arr[:meio])
    dir = dividir_e_conquistar(arr[meio:])

    return mesclar(esq, dir)

def encontrar_elemento_mais_frequente(arr):
    arr_ordenado = dividir_e_conquistar([(x, 1) for x in arr])
    max_freq = 0
    elem_freq = None

    freq_atual = 0
    elem_atual = None
    for elem, freq in arr_ordenado:
        if elem != elem_atual:
            freq_atual = 0
            elem_atual = elem
        freq_atual += freq
        if freq_atual > max_freq:
            max_freq = freq_atual
            elem_freq = elem

    return elem_freq, max_freq

def imprimir_frequencia(arr):
    arr_ordenado = dividir_e_conquistar([(x, 1) for x in arr])
    for elem, freq in arr_ordenado:
        print("({}, {})".format(elem, freq), end=" ")

entrada_usuario = input("Digite os elementos do vetor separados por espaços: ")
arr = entrada_usuario.split()

print("Vetor ordenado juntamente com a frequência dos elementos:")
imprimir_frequencia(arr)