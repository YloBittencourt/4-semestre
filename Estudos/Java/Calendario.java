import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.time.LocalDate;
import java.time.YearMonth;
import java.util.*;
import java.util.List;

public class Calendario extends JFrame {
    private JComboBox<Integer> anoComboBox; // ComboBox para selecionar o ano
    private JComboBox<String> mesComboBox; // ComboBox para selecionar o mês
    private JPanel calendarioPanel; // Painel do calendário
    private JPanel tarefasPanel; // Painel das tarefas
    private Map<LocalDate, List<String>> tarefasMap = new HashMap<>(); // Mapa para armazenar as tarefas

    public Calendario() {
        /*
        Configurações do JFrame
        1. Definir o título do JFrame
        2. Definir o tamanho do JFrame 
        3. Definir a operação padrão ao fechar o JFrame como EXIT_ON_CLOSE
        4. Centralizar o JFrame na tela
        */
        setTitle("Calendário Acadêmico");
        setSize(1000, 600); 
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null); 

        // ComboBox para selecionar o ano
        anoComboBox = new JComboBox<>();

        /*
        LocalDate.now().getYear() --> 
        utiliza a classe LocalDate do pacote java.time para obter a data atual(LocalDate.now())
        em seguida extrai o ano da data atual (getYear()) e armazena na variável currentYear
        */
        int currentYear = LocalDate.now().getYear(); // Obtém o ano atual

        // Adiciona os anos de 5 anos antes até 5 anos depois do ano atual
        for (int i = currentYear - 5; i <= currentYear + 5; i++) {
            anoComboBox.addItem(i); // Adiciona o ano ao ComboBox
        }

        anoComboBox.setSelectedItem(currentYear);  // Define o ano atual como selecionado
        anoComboBox.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                atualizarCalendario();
            }
        });

        // ComboBox para selecionar o mês
        mesComboBox = new JComboBox<>(new String[] { "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho","Agosto", "Setembro", "Outubro", "Novembro", "Dezembro" });

        /*
         Subtraindo 1, já que getMonthValue() retorna um valor de 1 a 12 (janeiro a dezembro) e o índice do ComboBox começa em 0
        */
        mesComboBox.setSelectedIndex(LocalDate.now().getMonthValue() - 1);
        mesComboBox.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                atualizarCalendario();
            }
        });

        // Painel principal
        JPanel mainPanel = new JPanel(new BorderLayout());
        JPanel topPanel = new JPanel(new FlowLayout());
        topPanel.add(new JLabel("Ano:"));
        topPanel.add(anoComboBox);
        topPanel.add(new JLabel("Mês:"));
        topPanel.add(mesComboBox);
        mainPanel.add(topPanel, BorderLayout.NORTH);

        // Painel do calendário
        calendarioPanel = new JPanel();
        calendarioPanel.setLayout(new GridLayout(0, 7));
        mainPanel.add(calendarioPanel, BorderLayout.CENTER);

        // Painel das tarefas
        tarefasPanel = new JPanel();
        tarefasPanel.setLayout(new BoxLayout(tarefasPanel, BoxLayout.Y_AXIS));
        JScrollPane tarefasScrollPane = new JScrollPane(tarefasPanel);
        tarefasScrollPane.setPreferredSize(new Dimension(250, 0));
        mainPanel.add(tarefasScrollPane, BorderLayout.EAST);

        add(mainPanel); // Adiciona o painel principal ao JFrame
        atualizarCalendario();
    }

    private void atualizarCalendario() {
        calendarioPanel.removeAll(); 
        tarefasPanel.removeAll(); 

        String[] diasDaSemana = { "Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sáb" };
        for (String dia : diasDaSemana) {
            calendarioPanel.add(new JLabel(dia, SwingConstants.CENTER)); // Adiciona os dias da semana ao calendário
        }

        /*
        1. Obter o ano selecionado
        2. Obter o mês selecionado
        3. Criar um objeto YearMonth com o ano e mês selecionados
        4. Obter o primeiro dia do mês
        5. Obter o dia da semana do primeiro dia do mês
        */
        int ano = (int) anoComboBox.getSelectedItem();
        int mes = mesComboBox.getSelectedIndex() + 1;
        YearMonth yearMonth = YearMonth.of(ano, mes);
        LocalDate primeiroDiaDoMes = yearMonth.atDay(1);
        int diaDaSemana = primeiroDiaDoMes.getDayOfWeek().getValue() % 7; 

        for (int i = 0; i < diaDaSemana; i++) {
            calendarioPanel.add(new JLabel("")); // Adiciona um espaço em branco para os dias antes do primeiro dia do mês
        }

        int diasNoMes = yearMonth.lengthOfMonth(); // Obtém o número de dias no mês

        /*
        1. Cria um botão para cada dia do mês
        2. Verifica se existem tarefas para a data
        3. Se existirem tarefas, define a cor de fundo do botão como amarelo
        4. Adiciona um ActionListener para o botão
        */
        for (int dia = 1; dia <= diasNoMes; dia++) { 
            LocalDate data = LocalDate.of(ano, mes, dia); 
            JButton diaButton = new JButton(String.valueOf(dia));
            if (tarefasMap.containsKey(data)) {
                diaButton.setBackground(Color.YELLOW);
            }
            diaButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {

                    /*
                    1. Verificar se existem tarefas para data 
                    2. Se o usuário clicar em "Sim" --> solicita a tarefa --> se o usuário informar uma tarefa --> adiciona à lista de tarefas da data
                    3. Atualiza o painel de tarefas 
                    */
                    if (tarefasMap.containsKey(data)) { 
                        int result = JOptionPane.showConfirmDialog(Calendario.this, "Já existe tarefa(s) para esta data. Deseja adicionar uma nova tarefa?"); // Exibe uma caixa de diálogo de confirmação
                        if (result == JOptionPane.YES_OPTION) { 
                            String tarefa = JOptionPane.showInputDialog(Calendario.this,"Adicionar tarefa para " + data); 
                            if (tarefa != null && !tarefa.isEmpty()) { 
                                tarefasMap.get(data).add(tarefa); 
                                atualizarTarefasPanel(); 
                            }
                        }
                    } else {
                        /*
                         Se não houver tarefas para a data, solicita a tarefa ao usuário e a adiciona à lista de tarefas da data
                        */
                        String tarefa = JOptionPane.showInputDialog(Calendario.this, "Adicionar tarefa para " + data);
                        if (tarefa != null && !tarefa.isEmpty()) { 
                            List<String> tarefas = new ArrayList<>(); 
                            tarefas.add(tarefa);
                            tarefasMap.put(data, tarefas); 
                            diaButton.setBackground(Color.YELLOW); 
                            atualizarTarefasPanel(); 
                        }
                    }
                }
            });
            calendarioPanel.add(diaButton); // Adiciona o botão ao calendário
        }
        
        calendarioPanel.revalidate();
        calendarioPanel.repaint(); 
        atualizarTarefasPanel(); 
    }

    private void atualizarTarefasPanel() {
        tarefasPanel.removeAll();
        int ano = (int) anoComboBox.getSelectedItem(); // Obtém o ano selecionado
        int mes = mesComboBox.getSelectedIndex() + 1; // Obtém o mês selecionado

        Map<LocalDate, List<String>> tarefasFiltradas = new TreeMap<>(); // Cria um TreeMap para armazenar as tarefas filtradas
        for (Map.Entry<LocalDate, List<String>> entry : tarefasMap.entrySet()) { // Itera sobre o mapa de tarefas
            LocalDate data = entry.getKey(); // Obtém a data da tarefa
            if (data.getYear() == ano && data.getMonthValue() == mes) { // Verifica se a tarefa é do ano e mês selecionados
                tarefasFiltradas.put(data, entry.getValue()); // Adiciona a tarefa ao mapa de tarefas filtradas
            }
        }

        JLabel mesLabel = new JLabel(mesComboBox.getSelectedItem().toString() + " " + ano, SwingConstants.CENTER); // Cria um rótulo com o mês e ano selecionados
        mesLabel.setFont(new Font("Serif", Font.BOLD, 18)); // Define a fonte do rótulo
        tarefasPanel.add(mesLabel); // Adiciona o rótulo ao painel de tarefas

        for (Map.Entry<LocalDate, List<String>> entry : tarefasFiltradas.entrySet()) { // Itera sobre o mapa de tarefas filtradas
            LocalDate data = entry.getKey(); // Obtém a data da tarefa
            JLabel dataLabel = new JLabel("Dia " + data.getDayOfMonth() + ":"); // Cria um rótulo com o dia da tarefa
            dataLabel.setFont(new Font("Serif", Font.BOLD, 14)); // Define a fonte do rótulo
            tarefasPanel.add(dataLabel); // Adiciona o rótulo ao painel de tarefas

            for (String tarefa : entry.getValue()) { // Itera sobre as tarefas da data
                JLabel tarefaLabel = new JLabel("- " + tarefa); // Cria um rótulo com a tarefa
                tarefaLabel.setBorder(BorderFactory.createEmptyBorder(0, 10, 0, 0)); // Define a margem do rótulo
                tarefasPanel.add(tarefaLabel); // Adiciona o rótulo ao painel de tarefas
            }
        }

        tarefasPanel.revalidate();
        tarefasPanel.repaint();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new Calendario().setVisible(true);
            }
        });
    }
}
