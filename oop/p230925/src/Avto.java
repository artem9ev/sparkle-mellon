public class Avto {
    String marka;
    String number;
    String vin;
    int year;
    double vol;
    int price;
    int km;

    Avto(String marka, String number, String vin, int year, double vol, int price, int km){
        this.marka = marka;
        this.number = number;
        this.vin = vin;
        this.year = year;
        this.vol = vol;
        this.price = price;
        this.km = km;
    }

    public String toString(){
        return "Марка: " + marka + "\nНомер: " + number + "\nВин: " + vin
                + "\nГод: " + year + "\nОбъем двигателя: " + vol
                + "\nЦена: " + price + "\nПробег: " + km;
    }
    String getMarka(){
        return marka;
    }
}
