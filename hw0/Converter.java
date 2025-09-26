/*
 * 
 * Nick Pinto
 * hw0
 * Ivalyo Illinkin
 * Due: 09/04/2025 11:59pm
 * 
* I affirm I have upheld the highest principles of honesty and integrity in my academic work and did not commit/see any violation
* of the Honor Code
 */

import java.util.Objects;
import java.util.HashMap;


public class Converter {

    /**
     * Testing helper (provided in the assignment).
     */
    public static <E1, E2> void assertEquals(E1 a, E2 b) {
        String strA = Objects.toString(a);
        String strB = Objects.toString(b);

        if (!strA.equals(strB)) {
            throw new RuntimeException();
        }
    }

    /**
     * Converts a Base10 number to the given base in [2..10].
     */
    public static long from10(long number, int base) {
        if (base < 2 || base > 10) {
            throw new IllegalArgumentException("Base must be in the range from 2 to 10, inclusive");
        }

        if (number == 0) {
            return 0;
        }

        long position = 1;
        long result = 0;
        long n = number;

        while (n > 0){
            long remainder = n % base; // remainder is long for consistency. int works too but must cast
            result = result + (remainder * position);
            position = position * 10;
            n = n / base;
        }
        return result; 
    }

    /**
     * Converts a Base10 number to base 16 and returns a String result.
     */
    public static String from10(long number) {
        if (number == 0) { return "0";}

        char[] remainders = new char[16]; // max 16 digits for long type
        int digitCount = 0; 

        while (number > 0) {
            long remainder = number % 16; // must be long type to use getSymbol
            remainders[digitCount] = getSymbol(remainder);
            digitCount++;
            number = number / 16;
        }

        // reverse order of hexDigit array filled with remainders (read right to left)
        char[] result = new char[digitCount];
        
        for (int i = 0; i < digitCount; i++){
            result[i] = remainders[digitCount - 1 - i];
        }

        return String.valueOf(result); // returns VALUE of the char[]; tried result.toString() but returns object id, not characters in array
        }

    /**
     * Returns the hexadecimal symbol for value 0..15 (provided in assignment).
     */
    public static char getSymbol(long digit) {
        if (digit >= 0 && digit <= 9) {
            return (char) ('0' + digit);
        } else {
            return (char) ('A' + (digit - 10));
        }
    }

    /**
     * Converts a number from the given base in [2..10] to Base10.
     */
    public static long to10(long number, int base) {
        if (base < 2 || base > 10){
            throw new IllegalArgumentException("Base parameter must be between [2, 10] inclusive.");
        }

        long result = 0;
        long power = 1; // the power in which each digit (from right to left) will get mulktipled by in the total sum

        while (number > 0){
            long digit = number % 10; // assigns LSD to digit var
            result = result + (digit * power);
            power = power * base; // set new power for next iteration
            number = number / 10; // calculates the next digit place (shift right by one decimal) for next iteration
        }
        return result;
    }

    /**
     * Converts a hexadecimal string to Base10.
     */
    public static long to10(String number) {
        if (number == null || number.length() == 0){
            throw new IllegalArgumentException("Please provide a valid hexadecimal string");
        }
        number = number.toUpperCase(); // avoids any input like 'f' or 'd', etc.
        long result = 0;
        long power = 1;

        for (int i = number.length() - 1; i >= 0; i--){
            char c = number.charAt(i); // get right-most (unvisited) character from hex-string
            long digit = getValue(c); // convert hex-digit to decimal value for computation in next line.

            result = result + (digit * power);
            power = power * 16;
        }
        return result;
    }

    /**
     * Returns the decimal value 0..15 for hexadecimal digit 0..F (provided).
     */
    public static long getValue(char symbol) {
        if (symbol >= '0' && symbol <= '9') {
            return symbol - '0';
        } else {
            return (symbol - 'A') + 10;
        }
    }

    /**
     * Builds and returns a HashMap with the single Roman "digits" and their
     * decimal equivalents (rows 1 and 5 in the standard table).
     */
    public static HashMap<Character, Integer> buildRomanMap() {
        HashMap<Character, Integer> map = new HashMap<>();

        map.put('I', 1);
        map.put('V', 5);
        map.put('X', 10);
        map.put('L', 50);
        map.put('C', 100);
        map.put('D', 500);
        map.put('M', 1000);

        return map;
    }

    /**
     * Converts a Roman numeral string to its Base10 equivalent.
     */
    public static int fromRoman(String number) {
        if (number == null || number.length() == 0){
            throw new IllegalArgumentException("Must enter valid Roman Numeral ");
        }
        number = number.toUpperCase(); // accounts for inputs like 'i', 'v', 'x', etc.

        HashMap<Character, Integer> map = new HashMap<>();
        map = buildRomanMap();

        int result = 0;

        // loop through all but last character in input
        for (int i = 0; i <= number.length() - 2; i++){
            char currChar = number.charAt(i); // gets curr character (key) at each index (line below too)
            char nextChar = number.charAt(i + 1);

            Integer currNum = map.get(currChar); // gets current numerical value at each index (line below too)
            Integer nextNum = map.get(nextChar);
            
            if (currNum == null || nextNum == null){
                throw new IllegalArgumentException("Argument(s) provided does not correspond to a valid Roman Numeral ");
            }

            if (currNum < nextNum){
                result = result - currNum; // subtractive case 
            }
            else {
                result = result + currNum; // additive case (every case where a smaller digit is in front of the larger one in the array)
            }

        }

        // handle last character
        char last = number.charAt(number.length() - 1); // obtain last char in string
        Integer lastInt = map.get(last); // obtain numerical value of last char in string

        result = result + lastInt;
        return result;

    }

    // test cases
    public static void main(String[] args) {
        // from 10 to base b cases

        // 120 in different  bases
        assertEquals(from10(120, 2), 1111000);           
        assertEquals(from10(120, 3), 11110);             
        assertEquals(from10(120, 7), 231);              
        assertEquals(from10(120, 8), 170);             
        assertEquals(from10(120, 10), 120);             

        // 12345 in different bases
        assertEquals(from10(12345, 2), 11000000111001L); 
        assertEquals(from10(12345, 3), 121221020);      
        assertEquals(from10(12345, 7), 50664);           
        assertEquals(from10(12345, 8), 30071);          
        assertEquals(from10(12345, 10), 12345);          

        // to10 to base b cases
        // convert numbers aforementioned to different bases 
        assertEquals(to10(1111000, 2), 120);
        assertEquals(to10(11000000111001L, 2), 12345L);

        assertEquals(to10(11110, 3), 120);
        assertEquals(to10(121221020, 3), 12345L);

        assertEquals(to10(231, 7), 120);
        assertEquals(to10(50664, 7), 12345L);

        assertEquals(to10(170, 8), 120);
        assertEquals(to10(30071, 8), 12345L);

        assertEquals(to10(120, 10), 120);
        assertEquals(to10(12345, 10), 12345L);

        // from 10 to hex cases

        assertEquals(from10(120), "78");
        assertEquals(from10(12345), "3039");


        // from hex to 10 cases

        assertEquals(to10("78"), 120L);
        assertEquals(to10("3039"), 12345L);

    // roman cases

    // 13 example numbers 
    assertEquals(fromRoman("XXXIX"), 39);
    assertEquals(fromRoman("CCXLVI"), 246);
    assertEquals(fromRoman("DCCLXXXIX"), 789);
    assertEquals(fromRoman("MMCDXXI"), 2421);
    assertEquals(fromRoman("CLX"), 160);
    assertEquals(fromRoman("CCVII"), 207);
    assertEquals(fromRoman("MIX"), 1009);
    assertEquals(fromRoman("MLXVI"), 1066);
    assertEquals(fromRoman("MMMCMXCIX"), 3999);
    assertEquals(fromRoman("MDCCLXXVI"), 1776);
    assertEquals(fromRoman("MCMXVIII"), 1918);
    assertEquals(fromRoman("MCMXLIV"), 1944);
    assertEquals(fromRoman("MMXXV"), 2025);

    // rows 4 and 6 from the table
    assertEquals(fromRoman("CD"), 400);
    assertEquals(fromRoman("XL"), 40);
    assertEquals(fromRoman("IV"), 4);

    assertEquals(fromRoman("DC"), 600);
    assertEquals(fromRoman("LX"), 60);
    assertEquals(fromRoman("VI"), 6);
    }
}
