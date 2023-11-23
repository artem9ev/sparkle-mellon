import java.util.Arrays;

public class Student {
    private String fio, adress, fakulty;
    private int kurs;
    private int[] marks;

    public Student(String fio, String adress, String fakulty, int kurs, int[] marks) {
        this.fio = fio;
        this.adress = adress;
        this.fakulty = fakulty;
        this.kurs = kurs;
        this.marks = marks;
    }

    public String getFio() {
        return fio;
    }

    public void setFio(String fio) {
        this.fio = fio;
    }

    double sr() {
        double s = 0;
        for (int i = 0; i < marks.length; i++) {
            s += marks[i];
        }
        return s / marks.length;
    }

    @Override
    public String toString() {
        return "Student" +
                "\nfio='" + fio + '\'' +
                "\nadress='" + adress + '\'' +
                "\nfakulty='" + fakulty + '\'' +
                "\nkurs=" + kurs +
                "\nmarks=" + Arrays.toString(marks);
    }
}
