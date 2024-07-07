import PyPDF2

def extrair_pagina_pdf(arquivo_pdf_entrada, numero_pagina, arquivo_pdf_saida):
    # Abrir o arquivo PDF de entrada
    with open(arquivo_pdf_entrada, 'rb') as arquivo_pdf:
        leitor_pdf = PyPDF2.PdfReader(arquivo_pdf)
        escritor_pdf = PyPDF2.PdfWriter()
        
        # Adicionar a página especificada ao novo PDF
        escritor_pdf.add_page(leitor_pdf.pages[numero_pagina - 1])
        
        # Salvar o novo PDF com a página extraída
        with open(arquivo_pdf_saida, 'wb') as arquivo_saida:
            escritor_pdf.write(arquivo_saida)

# Substitua os caminhos e o número da página pelos valores desejados
arquivo_pdf_entrada = '/home/ylo/Documentos/Covalidação/ementa unopar.pdf'
numero_pagina = 48  # número da página a ser extraída
arquivo_pdf_saida = 'pagina_extraida.pdf'

extrair_pagina_pdf(arquivo_pdf_entrada, numero_pagina, arquivo_pdf_saida)
