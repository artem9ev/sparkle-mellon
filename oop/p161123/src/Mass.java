import java.util.*;

public class Mass<T> {
    T[] a;
    Mass(T[] a){
        this.a = a.clone();
    }
    void print(){
        System.out.println("Массив: ");
        for (T elem : a){
            System.out.println(elem + " ");
        }
        System.out.println();
    }

    public T elemByInd(int id) throws ArrayIndexOutOfBoundsException {
        if (id < 0 || id >= a.length) throw new ArrayIndexOutOfBoundsException("Выход за границы массива");
        return a[id];
    }

    public void obrAr() {

    }

    void chast(int id) throws ArrayIndexOutOfBoundsException {
        if (id < 0 || id >= a.length) throw new ArrayIndexOutOfBoundsException("Выход за границы массива");
        for (int i = 0; i < id; i++){
            System.out.println(a[i] + " ");
        }
        System.out.println();
    }
}
