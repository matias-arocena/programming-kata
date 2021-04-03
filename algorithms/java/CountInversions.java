package algorithms.java;

import java.io.*;

public class CountInversions {
    public static void main(String[] args) {
        try {
            BufferedReader bReader = new BufferedReader(new InputStreamReader(System.in));
            int testCases = Integer.parseInt(bReader.readLine().trim());
            for (int i = 0; i < testCases; i++) {
                int dim = Integer.parseInt(bReader.readLine().trim());
                int matrix[][] = new int[dim][dim];
                for (int j = 0; j < dim; j++) {
                    String[] line = bReader.readLine().trim().split(" ");
                    for (int k = 0; k < dim; k++) {
                        matrix[j][k] = Integer.parseInt(line[k]);
                    }
                }
                System.out.println(countInversions(matrix, dim));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static int countInversions(int[][] matrix, int dim) {
        int count = 0;
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                for (int p = i; p < dim; p++) {
                    for (int q = j; q < dim; q++) {
                        if (matrix[i][j] > matrix[p][q]) count++;
                    }
                }
            }
        }
        return count;
    }
}
