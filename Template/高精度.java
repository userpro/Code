import java.util.*;
import java.io.*;
import java.math.*;

public class 高精度 { // 提交时类名改为 Main
    public static void main(String []args) {
        Scanner sc = new Scanner(System.in);
        BigInteger a = sc.nextBigInteger();
        BigInteger b = sc.nextBigInteger();
        int n = sc.nextInt();
        BigInteger c = BigInteger.ONE;
        BigDecimal d = sc.nextBigDecimal(); // 高精度定点数
        BigInteger e = sc.nextBigInteger();
        String str = sc.nextLine();
         
        /*
        //d为int型，a,b,c都为大数 
        c=a.add(b);         // 相加 
        c=a.subtract(b);    // 相减 
        c=a.multiply(b);    // 相乘 
        c=a.divide(b);      // 相除取整 
        c=a.gcd(b);         // 最大公约数 
        c=a.remainder(b);   // 取余 
        c=a.mod(b);         // a % b 
        c=a.abs();          // a的绝对值 
        c=a.negate();       // a的相反数 
        c=a.pow(d);         // a的b次幂 d为int型     
        c=a.max(b);         // 取a,b中较大的 
        c=a.min(b);         // 取a,b中较小的 
        d=a.compareTo(b);   // 比较a与b的大小 d=-1小于 d=0等于 d=1大于  d为int型
        a.equals(b);        //  判断a与b是否相等 相等返回true 不相等返回false
        */
         
        // 加减乘除add,subtract,multiply,divide
        System.out.println(a.add(b));
        System.out.println(a.subtract(b));
        System.out.println(a.multiply(b));
        System.out.println(a.divide(b));
         
        // 阶乘
        // 注意BigInteger.valueOf()的使用
        for(int i=1;i<=n;i++) {
            c=c.multiply(BigInteger.valueOf(i));
        }
        System.out.println(c);
        //比较大小
        int flag=a.compareTo(b);
        if(flag==-1) {
            System.out.println("a<b");
        } else if(flag==0) {
            System.out.println("a=b");
        } else {
            System.out.println("a>b");
        }
        // 高精度幂
        // stripTrailingZeros():返回数值上等于此小数，但从该表示形式移除所有尾部0的BigDecimal
        // toPlainString():将BigDecimal转换为字符串
        // stratswith("c"):判断该字符串是不是以字符c开头的
        // substring(st,en):返回该字符串减去下标在[st,en)的字符串
        String res=d.pow(n).stripTrailingZeros().toPlainString();
        if(res.startsWith("0")) {
            res=res.substring(0,1);
        }
        System.out.println(res);
        // 大数的进制转换
        // 先将字符串转化为10进制大数，然后将大数转化为2进制字符串
        e=new BigInteger(str,10);
        String tmp=e.toString(2);
        /*
         d=a.intValue();      // 将大数a转换为 int 类型赋值给 d 
         e=a.longValue();     // 将大数a转换为 long 类型赋值给 e 
         f=a.floatValue();    // 将大数a转换为 float 类型赋值给 f 
         g=a.doubleValue();   // 将大数a转换为 double 类型赋值给 g 
         s=a.toString();      // 将大数a转换为 String 类型赋值给 s
         a=BigInteger.valueOf(e);  // 将 e 以大数形式赋值给大数 a   e只能为long或int 
         */
        sc.close();
    }
}