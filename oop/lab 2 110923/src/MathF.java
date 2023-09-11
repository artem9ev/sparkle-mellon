public class MathF {
    boolean isProstoe(int x){
        int s = 0;
        for (int i = 1; i < x; i++)
        {
            if (x % i == 0){
                s += i;
            }
        }
        return x == s;
    }
}
