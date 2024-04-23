package QUESTAO7;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class QUESTAO7 {
    private JFrame frame;
    private JLabel labelDiretorioAntes;
    private JLabel labelArquivoAntes;
    private JLabel labelDiretorioDepois;
    private JLabel labelArquivoDepois;

    public QUESTAO7() {
        frame = new JFrame("Renomeador de Diretório e Arquivo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 200);
        frame.setLayout(new GridLayout(5, 2));

        JLabel labelTitulo = new JLabel("Objetos criados antes do renome:");
        frame.add(labelTitulo);
        frame.add(new JLabel());

        labelDiretorioAntes = new JLabel();
        frame.add(new JLabel("Diretório:"));
        frame.add(labelDiretorioAntes);

        labelArquivoAntes = new JLabel();
        frame.add(new JLabel("Arquivo:"));
        frame.add(labelArquivoAntes);

        JButton renomearButton = new JButton("Renomear");
        renomearButton.addActionListener(new RenomearListener());
        frame.add(renomearButton);
        frame.add(new JLabel());

        JLabel labelTituloDepois = new JLabel("Objetos criados após o renome:");
        frame.add(labelTituloDepois);
        frame.add(new JLabel());

        labelDiretorioDepois = new JLabel();
        frame.add(new JLabel("Novo Diretório:"));
        frame.add(labelDiretorioDepois);

        labelArquivoDepois = new JLabel();
        frame.add(new JLabel("Novo Arquivo:"));
        frame.add(labelArquivoDepois);

        frame.setVisible(true);
    }

    private class RenomearListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String nomeDiretorio = "diretorio";
            String nomeArquivo = "arquivo";
            File diretorioAntes = new File(nomeDiretorio);
            diretorioAntes.mkdir();
            File arquivoAntes = new File(diretorioAntes, nomeArquivo + ".dat");
            try {
                arquivoAntes.createNewFile();
            } catch (IOException ex) {
                ex.printStackTrace();
            }

            labelDiretorioAntes.setText(nomeDiretorio);
            labelArquivoAntes.setText(nomeArquivo + ".dat");

            String novoNomeDiretorio = "novo_diretorio";
            String novoNomeArquivo = "novo_arquivo";
            File diretorioDepois = new File(novoNomeDiretorio);
            diretorioAntes.renameTo(diretorioDepois);
            File arquivoDepois = new File(diretorioDepois, novoNomeArquivo + ".txt");
            arquivoAntes.renameTo(arquivoDepois);

            labelDiretorioDepois.setText(novoNomeDiretorio);
            labelArquivoDepois.setText(novoNomeArquivo + ".txt");

            JOptionPane.showMessageDialog(frame, "Diretório e arquivo renomeados com sucesso!");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(QUESTAO7::new);
    }
}
