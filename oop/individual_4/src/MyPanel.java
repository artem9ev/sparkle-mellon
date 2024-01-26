import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MyPanel extends JPanel {
    JLabel lAddNote, lName, lDate, lInfo, lFindByName, lSortings, lOutputWindow, lRemoveByName;
    JTextField fName, fDate, fInfo, fFindByName, fRemoveByName;
    JTextArea aOutputWindow;
    JButton button1, button2, button3, button4, button5;
    Notebook notebook;

    MyPanel() {
        notebook = new Notebook();
        notebook.addFirstObject();

        setLayout(new GridLayout(1, 1));

        JPanel leftPanel = new JPanel(new GridLayout(0, 1));
        JPanel midPanel = new JPanel(new GridLayout(0, 1));
        JPanel rightPanel = new JPanel(new GridLayout(0, 1));

        lAddNote = new JLabel("ДОБАВЛЕНИЕ ОБЪЕКТА");
        leftPanel.add(lAddNote);

        lName = new JLabel("Назание:");
        leftPanel.add(lName);
        fName = new JTextField();
        fName.setColumns(10);
        leftPanel.add(fName);

        lDate = new JLabel("Дата");
        leftPanel.add(lDate);
        fDate = new JTextField();
        fDate.setColumns(10);
        leftPanel.add(fDate);

        lInfo = new JLabel("Текст");
        leftPanel.add(lInfo);
        fInfo = new JTextField();
        fInfo.setColumns(10);
        leftPanel.add(fInfo);

        button1 = new JButton("ДОБАВИТЬ");
        AddListener m1 = new AddListener(notebook);
        button1.addActionListener(m1);
        leftPanel.add(button1);

        lSortings = new JLabel("СОРТИРОВКИ");
        midPanel.add(lSortings);

        button3 = new JButton("ПО НАЗВАНИЮ");
        SortByNameListener m3 = new SortByNameListener(notebook);
        button3.addActionListener(m3);
        midPanel.add(button3);

        button4 = new JButton("ПО ДАТЕ");
        SortByDateListener m4 = new SortByDateListener(notebook);
        button4.addActionListener(m4);
        midPanel.add(button4);

        lFindByName = new JLabel("ПОИСК ОБЪЕКТА ПО НАЗВАНИЮ");
        rightPanel.add(lFindByName);

        fFindByName = new JTextField();
        fFindByName.setColumns(10);
        rightPanel.add(fFindByName);

        button2 = new JButton("ПОИСК");
        FindListener m2 = new FindListener(notebook);
        button2.addActionListener(m2);
        rightPanel.add(button2);

        lOutputWindow = new JLabel("ОКНО ВЫВОДА");
        rightPanel.add(lOutputWindow);

        aOutputWindow = new JTextArea();
        aOutputWindow.setColumns(10);
        aOutputWindow.setRows(15);
        JScrollPane scrollPane = new JScrollPane(aOutputWindow);
        rightPanel.add(scrollPane);

        Dimension dim = new Dimension(200, 300);
        scrollPane.setPreferredSize(dim);

        add(leftPanel);
        add(midPanel);
        add(rightPanel);

        aOutputWindow.setText(notebook.toString());
    }

    class AddListener implements ActionListener {
        Notebook notebook;
        AddListener(Notebook notebook) {
            this.notebook = notebook;
        }
        public void actionPerformed(ActionEvent e) {

            String name = fName.getText();
            String date = fDate.getText();
            String info = fInfo.getText();

            Note newObject = new Note(name, date, info);
            notebook.addNote(newObject);

            aOutputWindow.setText(notebook.toString());
        }
    }

    class FindListener implements ActionListener {
        Notebook notebook;
        FindListener(Notebook notebook) {
            this.notebook = notebook;
        }
        public void actionPerformed(ActionEvent e) {
            String name = fFindByName.getText();
            String str = notebook.searchNote(name).toString();
            aOutputWindow.setText(str);
        }
    }

    class SortByNameListener implements ActionListener {
        Notebook notebook;
        SortByNameListener(Notebook notebook) {
            this.notebook = notebook;
        }
        public void actionPerformed(ActionEvent e) {
            notebook.sortByName();
            aOutputWindow.setText(notebook.toString());
        }
    }

    class SortByDateListener implements ActionListener {
        Notebook notebook;
        SortByDateListener(Notebook notebook) {
            this.notebook = notebook;
        }
        public void actionPerformed(ActionEvent e) {
            notebook.sortByDate();
            aOutputWindow.setText(notebook.toString());
        }
    }
}

