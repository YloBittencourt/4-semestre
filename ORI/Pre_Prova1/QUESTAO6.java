
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class QUESTAO6 {
    private JFrame frame;
    private JTextField nomeArquivoField;
    private JTextArea resultadoArea;

    private final String DIRETORIO_DESTINO = "diretorio_destino";

    public QUESTAO6() {
        frame = new JFrame("Verificador de Arquivo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 200);
        frame.setLayout(new BorderLayout());

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(2, 1));

        JLabel label = new JLabel("Nome do Arquivo (.txt):");
        nomeArquivoField = new JTextField();
        panel.add(label);
        panel.add(nomeArquivoField);

        JButton verificarButton = new JButton("Verificar Arquivo");
        verificarButton.addActionListener(new VerificarListener());
        panel.add(verificarButton);

        frame.add(panel, BorderLayout.NORTH);

        resultadoArea = new JTextArea();
        resultadoArea.setEditable(false);
        frame.add(new JScrollPane(resultadoArea), BorderLayout.CENTER);

        frame.setVisible(true);
    }

    private class VerificarListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            String nomeArquivo = nomeArquivoField.getText();

            String caminhoArquivo = DIRETORIO_DESTINO + File.separator + nomeArquivo + ".txt";

            File arquivo = new File(caminhoArquivo);
            if (arquivo.exists()) {
                resultadoArea.setText("O arquivo " + nomeArquivo + ".txt existe no diretório.");
            } else {
                resultadoArea.setText("O arquivo " + nomeArquivo + ".txt não existe no diretório.");
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(QUESTAO6::new);
    }
}

