import java.util.Comparator;

public class AdressPoshta {
    private String street;
    private String city;
    private String country;
    private String postalCode;

    public String toString() {
        return ("AdressPoshta = "+street+" "+city+" "+country+" "+postalCode+ "\n");
    }

    public AdressPoshta(String street, String city, String country, String postalCode) {
        this.street = street;
        this.city = city;
        this.country = country;
        this.postalCode = postalCode;
    }

    // Getters and setters for street, city, country, and postalCode

    public void setStreet(String street) {
        this.street = street;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public void setPostalCode(String postalCode) {
        this.postalCode = postalCode;
    }

    public String getStreet() {
        return street;
    }

    public String getCity() {
        return city;
    }

    public String getCountry() {
        return country;
    }

    public String getPostalCode() {
        return postalCode;
    }

    public static  Comparator<AdressPoshta> StreetComparator = new Comparator<AdressPoshta>() {
        @Override
        public int compare(AdressPoshta s1, AdressPoshta s2) {
            return s1.getStreet().compareTo(s2.getStreet());
        }
    };
    public static  Comparator<AdressPoshta> CountryComparator = new Comparator<AdressPoshta>() {
        @Override
        public int compare(AdressPoshta s1, AdressPoshta s2) {
            return s1.getCountry().compareTo(s2.getCountry());
        }
    };
    public static Comparator<AdressPoshta> CityComparator = new Comparator<AdressPoshta>() {
        @Override
        public int compare(AdressPoshta o1, AdressPoshta o2) {
            return new String(o1.getCity()).compareTo(new String(o2.getCity()));
        }
    };
    public static Comparator<AdressPoshta> PostalCodeComparator = new Comparator<AdressPoshta>() {
        @Override
        public int compare(AdressPoshta o1, AdressPoshta o2) {
            return new String(o1.getPostalCode()).compareTo(new String(o2.getPostalCode()));
        }
    };

}
