class Intervalo:
    def __init__(self, inicio, fim, indice):
        self.inicio = inicio  # Tempo de início do intervalo
        self.fim = fim  # Tempo de fim do intervalo
        self.indice = indice  # Identificador do intervalo
        self.cor = None  # Cor atribuída ao intervalo

def colorir_intervalos(intervalos):
    cores_disponiveis = ["vermelho", "amarelo", "azul", "verde"]
    
    # Ordena(função sort) os intervalos em ordem não-decrescente de tempo de início
    # lambda = cada elemento x na lista será avaliado em relação ao seu atributo inicio
    # x.inicio acessa o atributo inicio do objeto x, que é um objeto da classe Intervalo.
    intervalos.sort(key=lambda x: x.inicio)

    # Verifica se há interseção entre os dois intervalos, ou seja, se um intervalo começa antes do fim do outro e vice-versa. Se essa condição for verdadeira, os intervalos se interceptam.
    def se_intercepta(intervalo1, intervalo2):
        return intervalo1.inicio < intervalo2.fim and intervalo2.inicio < intervalo1.fim

    # Cria um dicionário onde cada chave é um objeto Intervalo da lista intervalos, e cada valor é um conjunto vazio.
    # Após a execução, contém todos os intervalos como chaves, e cada intervalo tem um conjunto vazio associado a ele.
    vizinhos = {intervalo: set() for intervalo in intervalos}

    # Constrói o grafo de intervalos
    for i in range(len(intervalos)): # Itera sobre todos os índices dos intervalos na lista intervalos.
        for j in range(i + 1, len(intervalos)): # Itera sobre todos os índices subsequentes aos de i. Isso garante que cada par de intervalos seja verificado apenas uma vez, evitando repetições.
            if se_intercepta(intervalos[i], intervalos[j]): # Verifica se o intervalo intervalos[i] se intercepta com o intervalo intervalos[j].
                vizinhos[intervalos[i]].add(intervalos[j]) # Adiciona o intervalo intervalos[j] como vizinho do intervalo intervalos[i].
                vizinhos[intervalos[j]].add(intervalos[i]) # Adiciona o intervalo intervalos[i] como vizinho do intervalo intervalos[j].

    # Função para atribuir cores aos intervalos
    def atribuir_cor(intervalo):
        # Cores já atribuídas aos intervalos vizinhos
        cores_vizinhas = {vizinho.cor for vizinho in vizinhos[intervalo] if vizinho.cor is not None}
        # Procura por uma cor disponível
        for cor in cores_disponiveis:
            if cor not in cores_vizinhas:
                return cor

    # Percorre todos os intervalos na lista intervalos e atribui uma cor a cada um deles utilizando a função atribuir_cor(intervalo)
    for intervalo in intervalos:
        intervalo.cor = atribuir_cor(intervalo)

    # Criar um conjunto (set) contendo todas as cores atribuídas aos intervalos e retornar esse conjunto juntamente com a lista de intervalos coloridos.
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

# Chamar a função colorir_intervalos(intervalos) para colorir os intervalos fornecidos e atribuir cores a eles.
cores, intervalos_coloridos = colorir_intervalos(intervalos)

print("Intervalos coloridos:")
for intervalo in intervalos_coloridos:
    print(f"Intervalo {intervalo.indice}: Cor {intervalo.cor}")
