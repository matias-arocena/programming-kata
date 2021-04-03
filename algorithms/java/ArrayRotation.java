package algorithms.java;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ArrayRotation {
    public static void main(String[] args) {
        BufferedReader bReader = new BufferedReader(new InputStreamReader(System.in));
        try {
            int testCases = Integer.parseInt(bReader.readLine());
            for (int i = 0; i < testCases; i++) {
                String[] config = bReader.readLine().split(" ");
                int arraySize = Integer.parseInt(config[0]);
                int rotation = Integer.parseInt(config[1]);
                String[] inputArray = bReader.readLine().split(" ");
                String[] rotated = rotate(inputArray, arraySize, rotation);
                StringBuilder result = new StringBuilder();
                for(int j = 0; j < arraySize - 1; j++) {
                   result.append(rotated[j] + " ");
                }
                result.append(rotated[arraySize - 1]);
                System.out.println(result);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    private static String[] rotate(String[] arr, int size, int rotation) {
        String[] rotated = new String[size];
        for(int i = 0; i < size; i++) {
            rotated[(i + rotation) % size] = arr[i];
        }
        return rotated;
    }
}
