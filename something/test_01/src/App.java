
public class App {
    public static void main(String[] args) throws Exception {
        Car ferari = new Car();
        Car lambotrgini = new Car();

        ferari.Go();
        lambotrgini.Go();

        lambotrgini = null;
    }
}
