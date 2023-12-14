import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;

public class MyList {
    private LinkedList<Integer> list;

    public MyList() {
        list = new LinkedList<Integer>();
    }
    private boolean isSoversh(Integer a){
        int s = 0;
        for (int i = 1; i < a; i++){
            if (a % i == 0){
                s += i;
            }
        }
        return s == a;
    }
    void deleteSoversh(){
        ListIterator<Integer> it = list.listIterator();
        while(it.hasNext()){
            if (isSoversh(it.next())){
                it.remove();
            }
        }
    }
    boolean isSymmetric(){
        ListIterator<Integer> it1 = list.listIterator(); // итератор в начале
        ListIterator<Integer> it2 = list.listIterator(list.size()); // итератор в конце
        while(it1.nextIndex() < it2.previousIndex()){
            if (it1.next() != it2.previous() && it1.hasNext() && it2.hasPrevious()){
                return false;
            }
        }
        return true;
    }
    void input(){
        Integer x;
        Scanner sc = new Scanner(System.in);

        System.out.println("input list: ");
        x = sc.nextInt();
        while(x != 0){
            list.addLast(x);
            x = sc.nextInt();
        }
    }
    void print() {
        ListIterator<Integer> it = list.listIterator();
        System.out.print("print list:");
        while (it.hasNext()) {
            System.out.print(" " + it.next());
        }
        System.out.println();
    }
}
