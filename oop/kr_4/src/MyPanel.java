import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import static java.lang.Math.sqrt;

//Сделать окно, где можно вычислить корни квадратного уравнения по их индексам
public class MyPanel extends JPanel {
    JLabel l1, l2, l3, l4, l5;
    JTextField f1, f2, f3, f4, f5;
    JButton button;

    MyPanel() {
        l1 = new JLabel("введите a");
        add(l1);
        f1 = new JTextField();
        f1.setColumns(10);
        add(f1);


        l2 = new JLabel("введите b");
        add(l2);
        f2 = new JTextField();
        f2.setColumns(10);
        add(f2);

        l3 = new JLabel("введите c");
        add(l3);
        f3 = new JTextField();
        f3.setColumns(10);
        add(f3);

        l5 = new JLabel("х1");
        add(l5);
        f5 = new JTextField();
        f5.setColumns(10);
        add(f5);
        l4 = new JLabel("х2");
        add(l4);
        f4 = new JTextField();
        f4.setColumns(10);
        add(f4);


        button = new JButton("результат");
        MyListener m = new MyListener();
        button.addActionListener(m);
        add(button);


    }

    public class MyListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            int a = Integer.parseInt(f1.getText());
            int b = Integer.parseInt(f2.getText());
            int c = Integer.parseInt(f3.getText());
            double d = b * b - 4 * a * c;
            if (d < 0) {
                f4.setText("The equation has no real roots");
                f5.setText("The equation has no real roots");
            } else {
                double root;
                if (d == 0) {
                    int s4 = (int) ((-b + sqrt(d)) / (2 * a));
                    f4.setText(String.valueOf(s4));
                } else {
                    int s4 = (int) ((-b + sqrt(d)) / (2 * a));
                    int s5 = (int) ((-b - sqrt(d)) / (2 * a));

                    if (s4 < 0 && s5 < 0 || s4 < 0 || s5 < 0) {
                        f4.setText(String.valueOf((s4)));
                        f5.setText(String.valueOf((s5)));
                    } else {
                        f4.setText(String.valueOf(s4));
                        f5.setText(String.valueOf(s5));
                    }
                }
            }
        }
    }
}

