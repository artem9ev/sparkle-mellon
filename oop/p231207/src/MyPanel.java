import javax.swing.*;

public class MyPanel extends JPanel {
    JLabel l1, l2, l3;
    JTextField f1, f2, f3;
    JButton button;

    public MyPanel() {
        l1 = new JLabel("1-е слагаемое");
        add(l1);
        f1 = new JTextField();

    }
}
