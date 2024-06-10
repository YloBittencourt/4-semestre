# Tabela baseada no slide pag. 34
import pandas as pd
import tkinter as tk
from tkinter import ttk

# Dados originais (pag. 33 do slide)
dados = [10, 12, 9, 11, 10, 8, 9, 10, 7, 10, 8, 9, 9, 10, 10, 11, 9, 11, 10, 10]

# Criando uma série pandas com os dados
dados_serie = pd.Series(dados)

# Contando ocorrências de cada valor e ordenando em ordem crescente
contagem_valores = dados_serie.value_counts().sort_index()

# Calculando as diferentes medidas de frequência
frequencia_absoluta = contagem_valores
frequencia_relativa = contagem_valores / len(dados)
frequencia_percentual = frequencia_relativa * 100
frequencia_percentual_acumulada = frequencia_percentual.cumsum()

# Criando um DataFrame pandas para armazenar os resultados
tabela = pd.DataFrame({
    'Classe': contagem_valores.index,
    'Freq': frequencia_absoluta.values,
    'Freq_relativa': frequencia_relativa.values,
    'Freq_percentual': frequencia_percentual.values,
    'Freq_percentual_ac': frequencia_percentual_acumulada.values
})

# Função para exibir a tabela na interface gráfica
def exibir_tabela():
    # Criando uma nova janela
    root = tk.Tk()
    root.title('Tabela de Frequências')

    # Criando uma Treeview (tabela) na janela
    tree = ttk.Treeview(root)
    tree["columns"] = list(tabela.columns)
    tree["show"] = "headings"
    
    # Adicionando cabeçalhos à tabela
    for column in tree["columns"]:
        tree.heading(column, text=column)

    # Preenchendo a tabela com os dados do DataFrame
    for index, row in tabela.iterrows():
        tree.insert("", "end", values=list(row))

    # Exibindo a tabela na janela
    tree.pack()

    # Iniciando o loop principal da interface gráfica
    root.mainloop()

# Chamando a função para exibir a tabela na interface
exibir_tabela()
