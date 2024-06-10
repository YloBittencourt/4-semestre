
import java.io.File;

public class QUESTAO4 {
    public static void main(String[] args) {
        String diretorio = "diretorio_destino";

        File diretorioDestino = new File(diretorio);
        
        //Se o diretorio existe e de fato é um diretório
        if (diretorioDestino.exists() && diretorioDestino.isDirectory()) {

            File[] arquivos = diretorioDestino.listFiles();

            if (arquivos != null && arquivos.length > 0) {
                System.out.println("Arquivos encontrados no diretório " + diretorio + ":");
                for (File arquivo : arquivos) {
                    if (arquivo.isFile() && arquivo.getName().endsWith(".txt")) {
                        System.out.println(arquivo.getName());
                    }
                }
            } else {
                System.out.println("Nenhum arquivo encontrado no diretório " + diretorio);
            }
        } else {
            System.out.println("O diretório " + diretorio + " não existe ou não é um diretório válido.");
        }
    }
}