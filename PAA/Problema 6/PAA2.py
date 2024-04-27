class Intervalo:
    def __init__(self, inicio, fim, indice):
        self.inicio = inicio 
        self.fim = fim 
        self.indice = indice  
        self.cor = None  

def colorir_intervalos(intervalos):
    cores_disponiveis = ["vermelho", "amarelo", "azul", "verde"]
    
    intervalos.sort(key=lambda x: x.inicio)

    def se_intercepta(intervalo1, intervalo2):
        return intervalo1.inicio < intervalo2.fim and intervalo2.inicio < intervalo1.fim

    vizinhos = {intervalo: set() for intervalo in intervalos}

    for i in range(len(intervalos)): 
        for j in range(i + 1, len(intervalos)): 
            if se_intercepta(intervalos[i], intervalos[j]):
                vizinhos[intervalos[i]].add(intervalos[j]) 
                vizinhos[intervalos[j]].add(intervalos[i])

    def atribuir_cor(intervalo):
        cores_vizinhas = {vizinho.cor for vizinho in vizinhos[intervalo] if vizinho.cor is not None}

        for cor in cores_disponiveis:
            if cor not in cores_vizinhas:
                return cor

    for intervalo in intervalos:
        intervalo.cor = atribuir_cor(intervalo)

    cores = set(intervalo.cor for intervalo in intervalos)
    return cores, intervalos

# Exemplo de utilização (igual o slide)
intervalos = [
    Intervalo(0, 6, 'A'),
    Intervalo(1, 4, 'B'),
    Intervalo(3, 5, 'C'),
    Intervalo(3, 8, 'D'),
    Intervalo(4, 7, 'E'),
    Intervalo(5, 9, 'F'),
    Intervalo(6, 10, 'G'),
    Intervalo(7, 11, 'H')
]

cores, intervalos_coloridos = colorir_intervalos(intervalos)

print("Intervalos coloridos:")
for intervalo in intervalos_coloridos:
    print(f"Intervalo {intervalo.indice}: Cor {intervalo.cor}")
