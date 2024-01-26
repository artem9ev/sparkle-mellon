import java.util.*;
public class Notebook {
    private ArrayList<Note> notes;

    public Notebook() {
        notes = new ArrayList<>();
    }
    public void addNote(Note record) {
        notes.add(record);
    }
    public void removeNote(String name) {
        for (Note note : notes){
            if (note.getName().equals(name)) {
                notes.remove(note);
            }
        }
    }
    public Note searchNote(String attribute) {
        for (Note record : notes) {
            if (record.getName().equals(attribute)) {
                return record;
            }
        }
        return null;
    }
    public void sortByName()
    {
        notes.sort(Note.NameComparator);
    }
    public void sortByDate()
    {
        notes.sort(Note.DateComparator);
    }
    public void print(){
        for (int i = 0; i < notes.size(); i++)
        {
            System.out.println(notes.get(i).toString());
        }
        System.out.println();
    }
    public void addFirstObject(){
        notes.add(new Note("Купить продукты", "25.12.23", "Молоко, яйца, перец, шпинат"));
        notes.add(new Note("Сдать индивидуалки", "17.12.23", "ооп 3 и 4 индивидуалки"));
        notes.add(new Note("Купить подарки", "27.12.23", "Купить куклы для сестры"));
    }

    public String toString() {
        String str = "Записи\n";
        for (Note note : notes) {
            str += (note.getName() + " | " + note.getDate() + "\n");
        }
        return str.toString();
    }

}
