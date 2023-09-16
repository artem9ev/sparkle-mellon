public class Mathf {
    public static boolean isProstoe(int x){
        if (x < 2){
            return false;
        }
        for (int i = 2; i < x; i++){
            if (x % i == 0){
                return false;
            }
        }
        return true;
    }
    public static boolean isSoversh(int x){
        int s = 0;
        for (int i = 1; i < x; i++){
            if (x % i == 0){
                s += i;
            }
        }
        return s == x;
    }
}
