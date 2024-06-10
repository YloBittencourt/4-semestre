import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class QUESTAO2 {
    private JFrame frame;
    private JTextField caminhoField; //Espaço para digitar o nome do caminho
    private JTextField diretorioField; //Espaço para digitar o nome do diretorio
    private JTextField subdiretorioField; //Espaço para digitar o nome do subdiretorio
    private JLabel resultadoLabel;

    public QUESTAO2() {
        //Titulo da janela, juntamente com seu tamanho e layout
        frame = new JFrame("Verificar Diretório");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 200);
        frame.setLayout(new BorderLayout());

        //Adicionar um painel à janela
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(4, 2));

        //Adicionar um rótulo para o caminho, nome do diretorio e nome do subdiretorio
        JLabel caminhoLabel = new JLabel("Caminho:");
        caminhoField = new JTextField();
        panel.add(caminhoLabel);
        panel.add(caminhoField);

        JLabel diretorioLabel = new JLabel("Nome do Diretório:");
        diretorioField = new JTextField();
        panel.add(diretorioLabel);
        panel.add(diretorioField);

        JLabel subdiretorioLabel = new JLabel("Nome do Subdiretório:");
        subdiretorioField = new JTextField();
        panel.add(subdiretorioLabel);
        panel.add(subdiretorioField);

        //Criar o botão para verificar
        JButton verificarButton = new JButton("Verificar");
        verificarButton.addActionListener(new VerificarListener());
        panel.add(verificarButton);

        resultadoLabel = new JLabel();
        panel.add(resultadoLabel);

        //Tornar a interface visível
        frame.add(panel, BorderLayout.CENTER);
        frame.setVisible(true);
    }

    private class VerificarListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String caminho = caminhoField.getText(); //Capturar a entrada no espaço caminho
            String nomeDiretorio = diretorioField.getText(); //Capturar a entrada no espaço diretorio
            String nomeSubdiretorio = subdiretorioField.getText(); //Capturar a entrada no espaço subdiretorio

            //Fazer a verificação de existência (boolean retorna true or false)
            boolean caminhoExiste = new File(caminho).exists();
            boolean diretorioExiste = new File(caminho, nomeDiretorio).exists();
            boolean subdiretorioExiste = new File(caminho + "/" + nomeDiretorio, nomeSubdiretorio).exists();

            if (caminhoExiste && diretorioExiste && subdiretorioExiste) {
                resultadoLabel.setText("Verdadeiro");
            } else {
                resultadoLabel.setText("Falso");
            }
        }
    }
    public static void main(String[] args) {
        SwingUtilities.invokeLater(QUESTAO2::new);
    }
}