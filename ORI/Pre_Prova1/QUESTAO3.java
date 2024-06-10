
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class QUESTAO3 {
    private JFrame frame;
    private JTextField[] nomeArquivoFields;
    private JTextArea displayArea;

    public QUESTAO3() {
        frame = new JFrame("Gravar Arquivos"); //Criar a janela
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300); //Ajustar o tamanho
        frame.setLayout(new BorderLayout()); //Ajustar o layout

        JPanel panel = new JPanel(); //Criar o painel
        panel.setLayout(new GridLayout(4, 1)); //Ajustar o layout do painel

        nomeArquivoFields = new JTextField[3]; //Espaço para o nome dos três arquivos
        for (int i = 0; i < 3; i++) {
            nomeArquivoFields[i] = new JTextField(); //Digitar o nome do arquivo
            JLabel label = new JLabel("Nome do Arquivo " + (i + 1) + " (.txt):");
            panel.add(label); //Adicionar o rotulo ao painel
            panel.add(nomeArquivoFields[i]); //Adicionar o nome dos arquivos no painel
        }

        JButton gravarButton = new JButton("Gravar Arquivos"); //Criação do botão
        gravarButton.addActionListener(new GravarListener());
        panel.add(gravarButton); //Adicionar ao painel

        frame.add(panel, BorderLayout.NORTH);

        displayArea = new JTextArea();
        displayArea.setEditable(false);
        frame.add(new JScrollPane(displayArea), BorderLayout.CENTER);

        frame.setVisible(true); //Tornar visível
    }

    private class GravarListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String[] nomesArquivos = new String[3]; //Como são 3 arquivos
            for (int i = 0; i < 3; i++) { //0,1,2
                nomesArquivos[i] = nomeArquivoFields[i].getText(); //Capturar o nome dos arquivos
            }
          
            String diretorio = "diretorio_destino";
           
            File diretorioDestino = new File(diretorio);
            if (!diretorioDestino.exists()) {
                diretorioDestino.mkdir(); //Criar um novo diretorio chamado de diretorio_destino
            }
          
            for (String nomeArquivo : nomesArquivos) {
                File arquivo = new File(diretorio, nomeArquivo + ".txt");
                try {
                    arquivo.createNewFile();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }

            displayArea.setText("Arquivos gravados com sucesso no diretório:\n" + diretorio + "\n\n");
            for (String nomeArquivo : nomesArquivos) {
                displayArea.append(nomeArquivo + ".txt\n");
            }
        }
    }
    public static void main(String[] args) {
        SwingUtilities.invokeLater(QUESTAO3::new);
    }
}