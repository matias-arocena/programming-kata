package algorithms.java;

import java.io.InputStreamReader;
import java.io.BufferedReader;

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail

class ReverseString {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int totalLines = Integer.parseInt(br.readLine());
        String input;
        for(int i = 0; i < totalLines; i++) {
            input = br.readLine();
            System.out.println(reverse(input));
        }
    }

    private static String reverse(String str) {
        if(str.length() <= 1) {
            return str;
        } else {
            return str.charAt(str.length() - 1) + reverse(str.substring(0, str.length() - 1));
        }    
    }
}