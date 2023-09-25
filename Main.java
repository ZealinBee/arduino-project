import java.util.ArrayList;

class Main {
    public int romanToInt(String s) {
        char nextCh;
        int indexCh1;
        int sum = 0;
        ArrayList<Character> roman = new ArrayList<>();
        ArrayList<Integer> ints = new ArrayList<>();
        roman.add('I');
        roman.add('V');
        roman.add('X');
        roman.add('L');
        roman.add('C');
        roman.add('D');
        roman.add('M');
        ints.add(1);
        ints.add(5);
        ints.add(10);
        ints.add(50);
        ints.add(100);
        ints.add(500);
        ints.add(1000);
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            if (i != s.length() - 1) {
                nextCh = s.charAt(i + 1);
                indexCh1 = roman.indexOf(nextCh);
            } else {
                nextCh = 'H';
                indexCh1 = 1000;
            }
            int indexCh = roman.indexOf(ch);
            if (nextCh != 'H') {
                if (indexCh1 <= indexCh) {
                    sum += ints.get(indexCh);
                }

                else {
                    sum -= ints.get(indexCh);
                }
            } else {
                sum += ints.get(indexCh);
            }
        }
        return sum;
    }

    public static void main(String[] args) {
        Main m = new Main();
        System.out.println(m.romanToInt("III"));
    }
}
