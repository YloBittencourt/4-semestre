import java.io.File; //Usado para manipulação de arquivos e diretórios
import java.io.IOException; //Para excessões (try/catch)
import javax.swing.*; //Contém classes para criação de interfaces
import java.awt.*; //Fornece classes para criação de elementos gráficos

public class QUESTAO1 {
    private JFrame frame; //private: a variavel frame só pode ser acessada dentro da classe QUESTAO1

    public QUESTAO1() {
        //Configurar o titulo da janela, seu tamanho e o layout
        frame = new JFrame("Gravar Diretório");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 200); //Size(tamanho)
        frame.setLayout(new BorderLayout()); //Layout

        //Adicionar um painel à janela
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(3, 1));

        //Adicionar um rótulo
        JLabel label = new JLabel("Criar diretório, subdiretórios e arquivos.");
        panel.add(label); //Adicionar no painel

        //Criar um botão
        JButton button = new JButton("Criar");
        button.addActionListener(e -> criarDiretorio());
        panel.add(button); //Adicionar o botão no painel

        frame.add(panel, BorderLayout.CENTER); //Adiciona o painel(panel) à janela (frame) e posiciona (center) na janela, para desse jeito formar a interface
        frame.setVisible(true); //Torna a janela vísivel na tela (true)
    }

    private void criarDiretorio() {
        
        File diretorioPrincipal = new File("diretorio_principal"); //Criar um novo diretorio
        
        //Verificar se o diretorio existe, se não, ele vai criar(mkdir())
        if (!diretorioPrincipal.exists()) {
           
            diretorioPrincipal.mkdir();

           //Criação dos dois subdiretorios dentro do diretorioPrincipal
            File subdiretorio1 = new File(diretorioPrincipal, "subdiretorio1");
            File subdiretorio2 = new File(diretorioPrincipal, "subdiretorio2");

           //Função mkdir() para criar
            subdiretorio1.mkdir();
            subdiretorio2.mkdir();

           //Criação de dois arquivos txt e csv dentro de cada subdiretorio
            File arquivoTxt1 = new File(subdiretorio1, "arquivo1.txt");
            File arquivoTxt2 = new File(subdiretorio2, "arquivo2.txt");
            File arquivoCsvFile1 = new File(subdiretorio1, "arquivo1.csv");
            File arquivoCsvFile2 = new File(subdiretorio2, "arquivo1.csv");
    
            try {
                //Criar os dois arquivos de cada
                arquivoTxt1.createNewFile();
                arquivoTxt2.createNewFile();
                arquivoCsvFile1.createNewFile();
                arquivoCsvFile2.createNewFile();

                //Exibir a mensagem de sucesso
                JOptionPane.showMessageDialog(frame, "Criados com sucesso!\nVerifique na sua pasta.");
            } catch (IOException e) {
                //Exibir a mensagem de erro
                JOptionPane.showMessageDialog(frame, "Erro ao criar os arquivos: " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
            }
        } else {
            //Exibir a mensagem de alerta
            JOptionPane.showMessageDialog(frame, "O diretório principal já existe.", "Aviso", JOptionPane.WARNING_MESSAGE);
        }
    }

    public static void main(String[] args) {
        //Invocar as importações utilizadas
        SwingUtilities.invokeLater(QUESTAO1::new);
    }
}