import java.math.BigDecimal;
import java.math.RoundingMode;

public class Test {
    public static void main(String[] args) {
        double a = 0.1;
        double b = 0.2;
        double c = a + b;
        System.out.println(c);

        System.out.println("-----------------------");

        BigDecimal a1 = BigDecimal.valueOf(a);
        BigDecimal b1 = BigDecimal.valueOf(b);

        BigDecimal c1 = a1.add(b1);
        System.out.println(c1);

        BigDecimal c2 = a1.subtract(b1); // 减法
        BigDecimal c3 = a1.multiply(b1); // 乘法
        BigDecimal c4 = a1.divide(b1); // 除法

        System.out.println("减法：" + c2 + " 乘法：" + c3 + " 除法：" + c4);
        System.out.println("--------------------------");

        BigDecimal x = BigDecimal.valueOf(0.1);
        BigDecimal y = BigDecimal.valueOf(0.3);
        BigDecimal k = x.divide(y, 2, RoundingMode.HALF_UP); // 除法
        Double db = k.doubleValue();
        System.out.println(db);

    }
}