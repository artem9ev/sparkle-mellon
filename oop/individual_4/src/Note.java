import java.util.Comparator;
public class Note {
    private String name; // название
    private String date; // страна
    private String info; // страна
    public Note(String name, String date, String info) {
        this.name = name;
        this.date = date;
        this.info = info;
    }
    public String toShortString() {
        StringBuilder str = new StringBuilder();
        str.append(name+" | "+date);
        return str.toString();
    }
    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append(name+" | "+date+"\n"+info);
        return str.toString();
    }
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public String getDate() {
        return date;
    }
    public void setDate(String date) {
        this.date = date;
    }
    public void setInfo(String info) {
        this.info = info;
    }
    public String getInfo() {
        return info;
    }

    public static  Comparator<Note> NameComparator = new Comparator<Note>() {
        @Override
        public int compare(Note s1, Note s2) {
            return s1.getName().compareTo(s2.getName());
        }
    };
    public static  Comparator<Note> DateComparator = new Comparator<Note>() {
        @Override
        public int compare(Note s1, Note s2) {
            return s1.getDate().compareTo(s2.getDate());
        }
    };
}
