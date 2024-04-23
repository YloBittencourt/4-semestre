package EXTRA;

import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.nio.file.Files;

public class ORI extends JFrame {
    
    //Criação dos botões
    private JButton criar_diretorio;
    private JButton criar_arquivos;
    private JButton renomear_arquivos;
    private JButton copiar_arquivos;
    private JButton verificar_arquivos;

    //Criação dos arquivos
    private File diretorio1;
    private File diretorio2;
    private File arquivo1;
    private File arquivo2;
    private File arquivoRenomeado1;
    private File arquivoRenomeado2;
    private File arquivoCopiado1;
    private File arquivoCopiado2;

    public ORI() {
        setTitle("Operações de Arquivo"); //Título da janela
        setSize(400, 200); //Tamanho
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        //Adicionando os botões para quando clicado acionar a função especificada
        criar_diretorio = new JButton("Criar Diretórios");
        criar_diretorio.addActionListener(e->criarDiretorios());

        criar_arquivos = new JButton("Criar Arquivos");
        criar_arquivos.addActionListener(e->criarArquivos());

        renomear_arquivos = new JButton("Renomear Arquivos");
        renomear_arquivos.addActionListener(e->renomearArquivos());

        copiar_arquivos = new JButton("Copiar Arquivos");
        copiar_arquivos.addActionListener(e->copiarArquivos());

        verificar_arquivos = new JButton("Verificar Arquivos");
        verificar_arquivos.addActionListener(e->verificarArquivos());

        //Criação do painel, configurando o layout(5 linhas e 1 coluna) e adicionando os botoes no painel
        JPanel painel = new JPanel();
        painel.setLayout(new GridLayout(5, 1));
        painel.add(criar_diretorio);
        painel.add(criar_arquivos);
        painel.add(renomear_arquivos);
        painel.add(copiar_arquivos);
        painel.add(verificar_arquivos);

        //Adicionar o painel ao frame(janela)
        add(painel);
    }

    private void criarDiretorios() {
        
        //Criação dos dois diretórios
        diretorio1 = new File("diretorio 1");
        diretorio2 = new File("diretorio 2");

        //Se não existir, vai criar e mostrar a mensagem, se não, vai dizer que já existem
        if(!diretorio1.exists() && !diretorio2.exists()){
            diretorio1.mkdir();
            diretorio2.mkdir();

            JOptionPane.showMessageDialog(this, "Diretório 1 e Diretório 2 criados.");
        }else{
            JOptionPane.showMessageDialog(this, "Diretórios já existem");
        }
    }

    private void criarArquivos() {

        //Criar os arquivos no caminho do diretorio1
        arquivo1 = new File(diretorio1, "arquivo1.txt");
        arquivo2 = new File(diretorio1, "arquivo2.txt");

        try {
            arquivo1.createNewFile();
            arquivo2.createNewFile();

            JOptionPane.showMessageDialog(this, "Arquivos criados no 'diretorio 1'.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void renomearArquivos() {

        //Crir o arquivo renomeado no caminho do diretorio1
        arquivoRenomeado1 = new File(diretorio1, "arquivoRenomeado1.txt");
        arquivoRenomeado2 = new File(diretorio1, "arquivoRenomeado2.txt");

        //Renomar o arquivo para arquivoRenomeado
        arquivo1.renameTo(arquivoRenomeado1);
        arquivo2.renameTo(arquivoRenomeado2);

        JOptionPane.showMessageDialog(this, "Arquivos renomeados no 'diretorio 1'.");
    }

    private void copiarArquivos() {

        arquivoCopiado1 = new File(diretorio2, arquivoRenomeado1.getName());
        arquivoCopiado2 = new File(diretorio2, arquivoRenomeado2.getName());

        try {
            Files.copy(arquivoRenomeado1.toPath(), arquivoCopiado1.toPath());
            Files.copy(arquivoRenomeado2.toPath(), arquivoCopiado2.toPath());

            JOptionPane.showMessageDialog(this, "Arquivos copiados para 'diretorio 2'.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void verificarArquivos() {
        File[] arquivosCopiados = diretorio2.listFiles();
        if (arquivosCopiados != null && arquivosCopiados.length > 0) {
            JOptionPane.showMessageDialog(this, "Arquivos existem em 'diretorio 2'.");
        } else {
            JOptionPane.showMessageDialog(this, "Arquivos não existem em 'diretorio 2'.");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new ORI().setVisible(true);
            }
        });
    }
}