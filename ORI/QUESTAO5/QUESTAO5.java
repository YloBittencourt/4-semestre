package QUESTAO5;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class QUESTAO5 {
    private JFrame frame;
    private JTextField arquivo1Field;
    private JTextField arquivo2Field;
    private JTextArea displayArea;
    private File diretorioDestino;

    public QUESTAO5() {
        frame = new JFrame("Deletador de Arquivos"); //Criação da janela
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300); //Ajuste do tamanho
        frame.setLayout(new BorderLayout()); //Ajuste do layout

        JPanel panel = new JPanel(); //Adicionar um painel à janela
        panel.setLayout(new GridLayout(3, 2)); //Ajuste do layout do painel

        arquivo1Field = new JTextField(); //Criar o espaço  para digitar
        JLabel label1 = new JLabel("Arquivo 1 (.txt):"); //Adicionar o rótulo ao painel
        panel.add(label1);
        panel.add(arquivo1Field);

        arquivo2Field = new JTextField();
        JLabel label2 = new JLabel("Arquivo 2 (.txt):");
        panel.add(label2);
        panel.add(arquivo2Field);

        JButton deletarButton = new JButton("Deletar Arquivos"); //Criação do botão
        deletarButton.addActionListener(new DeletarListener());
        panel.add(deletarButton);

        frame.add(panel, BorderLayout.NORTH);

        displayArea = new JTextArea();
        displayArea.setEditable(false);
        frame.add(new JScrollPane(displayArea), BorderLayout.CENTER);

        frame.setVisible(true); //Tornar visível
    }

    private class DeletarListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String arquivo1 = arquivo1Field.getText(); //Capturar o texto
            String arquivo2 = arquivo2Field.getText(); //Capturar o texto

            if (diretorioDestino == null) { //Se o diretorio for vazio
                JOptionPane.showMessageDialog(frame, "Diretório não especificado.");
                return;
            }

            File arquivo1ParaDeletar = new File(diretorioDestino, arquivo1 + ".txt"); //Procurar o arquivo no diretoriodestino
            File arquivo2ParaDeletar = new File(diretorioDestino, arquivo2 + ".txt"); //Procurar o arquivo no diretoriodestino

            //boolean retorna verdadeiro ou falso
            boolean arquivo1Deletado = arquivo1ParaDeletar.delete(); //Deletar o arquivo1
            boolean arquivo2Deletado = arquivo2ParaDeletar.delete(); //Deletar o arquivo2

            if (arquivo1Deletado && arquivo2Deletado) {
                JOptionPane.showMessageDialog(frame, "Arquivos deletados com sucesso.");
            } else {
                JOptionPane.showMessageDialog(frame, "Falha ao deletar arquivos.");
            }

            // Atualiza a lista de arquivos no diretório
            atualizarListaArquivos();
        }
    }

    private void atualizarListaArquivos() {
        if (diretorioDestino != null && diretorioDestino.exists()) { //Se o diretorio não for nulo e existir
            File[] arquivos = diretorioDestino.listFiles();
            displayArea.setText("Arquivos restantes no diretório:\n\n");
            if (arquivos != null) {
                for (File arquivo : arquivos) {
                    if (arquivo.isFile()) {
                        displayArea.append(arquivo.getName() + "\n");
                    }
                }
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            QUESTAO5 questao = new QUESTAO5();
            questao.diretorioDestino = new File("diretorio_destino");
            questao.atualizarListaArquivos();
        });
    }
}
