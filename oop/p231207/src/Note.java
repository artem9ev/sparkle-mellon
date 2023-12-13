import java.util.Date;

public class Note implements Comparable<Note> {
    private String header;
    private String text;

    @Override
    public int compareTo(Note o) {
        return 0;
    }

    public void setHeader(String header) {
        this.header = header;
    }

    public void setText(String text) {
        this.text = text;
    }

    public String getHeader() {
        return header;
    }

    public String getText() {
        return text;
    }
}
