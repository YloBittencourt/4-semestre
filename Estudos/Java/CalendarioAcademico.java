import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.time.LocalDate;
import java.time.YearMonth;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class CalendarioAcademico extends JFrame {
    private JComboBox<Integer> anoComboBox;
    private JComboBox<String> mesComboBox;
    private JPanel calendarioPanel;
    private JPanel tarefasPanel;
    private Map<LocalDate, List<String>> tarefasMap = new HashMap<>();

    public CalendarioAcademico() {
        setTitle("Calendário Acadêmico");
        setSize(1000, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // ComboBox para selecionar o ano
        anoComboBox = new JComboBox<>();
        int currentYear = LocalDate.now().getYear();
        for (int i = currentYear - 5; i <= currentYear + 5; i++) {
            anoComboBox.addItem(i);
        }
        anoComboBox.setSelectedItem(currentYear);
        anoComboBox.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                atualizarCalendario();
            }
        });

        // ComboBox para selecionar o mês
        mesComboBox = new JComboBox<>(new String[]{"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"});
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

        add(mainPanel);
        atualizarCalendario();
    }

    private void atualizarCalendario() {
        calendarioPanel.removeAll();
        tarefasPanel.removeAll();

        String[] diasDaSemana = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sáb"};
        for (String dia : diasDaSemana) {
            calendarioPanel.add(new JLabel(dia, SwingConstants.CENTER));
        }

        int ano = (int) anoComboBox.getSelectedItem();
        int mes = mesComboBox.getSelectedIndex() + 1;
        YearMonth yearMonth = YearMonth.of(ano, mes);
        LocalDate primeiroDiaDoMes = yearMonth.atDay(1);
        int diaDaSemana = primeiroDiaDoMes.getDayOfWeek().getValue() % 7;

        for (int i = 0; i < diaDaSemana; i++) {
            calendarioPanel.add(new JLabel(""));
        }

        int diasNoMes = yearMonth.lengthOfMonth();
        for (int dia = 1; dia <= diasNoMes; dia++) {
            LocalDate data = LocalDate.of(ano, mes, dia);
            JButton diaButton = new JButton(String.valueOf(dia));
            if (tarefasMap.containsKey(data)) {
                diaButton.setBackground(Color.YELLOW);
            }
            diaButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    if (tarefasMap.containsKey(data)) {
                        int result = JOptionPane.showConfirmDialog(CalendarioAcademico.this, "Já existe tarefa(s) para esta data. Deseja adicionar uma nova tarefa?");
                        if (result == JOptionPane.YES_OPTION) {
                            String tarefa = JOptionPane.showInputDialog(CalendarioAcademico.this, "Adicionar tarefa para " + data);
                            if (tarefa != null && !tarefa.isEmpty()) {
                                tarefasMap.get(data).add(tarefa);
                                atualizarTarefasPanel();
                            }
                        }
                    } else {
                        String tarefa = JOptionPane.showInputDialog(CalendarioAcademico.this, "Adicionar tarefa para " + data);
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
            calendarioPanel.add(diaButton);
        }

        calendarioPanel.revalidate();
        calendarioPanel.repaint();
        atualizarTarefasPanel();
    }

    private void atualizarTarefasPanel() {
        tarefasPanel.removeAll();
        int ano = (int) anoComboBox.getSelectedItem();
        int mes = mesComboBox.getSelectedIndex() + 1;

        Map<LocalDate, List<String>> tarefasFiltradas = new TreeMap<>();
        for (Map.Entry<LocalDate, List<String>> entry : tarefasMap.entrySet()) {
            LocalDate data = entry.getKey();
            if (data.getYear() == ano && data.getMonthValue() == mes) {
                tarefasFiltradas.put(data, entry.getValue());
            }
        }

        for (Map.Entry<LocalDate, List<String>> entry : tarefasFiltradas.entrySet()) {
            LocalDate data = entry.getKey();
            for (String tarefa : entry.getValue()) {
                JLabel tarefaLabel = new JLabel(data + ": " + tarefa);
                tarefasPanel.add(tarefaLabel);
            }
        }

        tarefasPanel.revalidate();
        tarefasPanel.repaint();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new CalendarioAcademico().setVisible(true);
            }
        });
    }
}
