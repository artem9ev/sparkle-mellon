import java.util.ArrayList;

public class Spisok {
    private ArrayList<AdressPoshta> records;

    public Spisok() {
        records = new ArrayList<>();
    }

    public void addAdressP(AdressPoshta record) {
        records.add(record);
    }

    public void removeAdressPoshta(AdressPoshta record) {
        records.remove(record);
    }

    public AdressPoshta searchCountryObject(String attribute) {
        for (AdressPoshta record : records) {
            if (record.getCountry().equals(attribute)) {
                return record;
            }
        }
        return null;
    }

    public void sortByCity()
    {
        records.sort(AdressPoshta.CityComparator);
    }
    public void sortByCountry()
    {
        records.sort(AdressPoshta.CountryComparator);
    }

    public void sortByStreet()
    {
        records.sort(AdressPoshta.StreetComparator);
    }
    public void sortByPostaCode()
    {
        records.sort(AdressPoshta.PostalCodeComparator);
    }

    public void print(){
        for (int i = 0; i <records.size(); i++)
        {
            System.out.println(records.get(i).toString());
        }
        System.out.println();
    }

}
