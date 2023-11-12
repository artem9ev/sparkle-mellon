public class Data {
    int d, m, y;
    Data(int d, int m, int y) throws MyException {
        if (d > 31 || m > 12 || y < 0 || d < 1 || m < 1)
        {
            throw new MyException("Некорректная дата", d, m, y);
        }
        this.d = d;
        this.m = m;
        this.y = y;
    }
    // метод вывода данных
    // метод - прибавить к дате заданное кол-во дней с получением даты
    // метод - вычислить номер дня от начала года
}
