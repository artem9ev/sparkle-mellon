public class Money {
    private int rubles;
    private int kopeiki;
    Money(int rubles, int kopeiki){
        rubles += kopeiki / 100;
        kopeiki %= 100;
        this.rubles = rubles;
        this.kopeiki = kopeiki;
    }
    public int getRubles(){
        return rubles;
    }
    public int getKopeiki(){
        return kopeiki;
    }
    public void print(){
        System.out.print("На счету ");
        if (rubles < 20 && rubles > 10 || rubles % 10 == 0 || rubles % 10 > 4)
            System.out.print(rubles + " рублей ");
        else if (rubles % 10 == 1) System.out.print(rubles + " рубль ");
        else System.out.print(rubles + " рубля ");
    }
}
