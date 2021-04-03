package algorithms.java;

import java.io.*;


public class IterateOverMatrixDiagonals {
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
                System.out.println(transverseDiagonals(matrix, dim));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static int transverseDiagonals(int[][] matrix, int dim) {
        int count = 0;
        int diagonalsNumber = (dim - 1) * 2;
        for (int base_diagonal = 0; base_diagonal <= diagonalsNumber; base_diagonal++) {
            int i0 = (base_diagonal > dim - 1) ? base_diagonal - (dim - 1): 0;
            int iN = (base_diagonal > dim - 1) ? dim - 1: base_diagonal; 

            for (int i = i0; i <= iN; i++) {
                int j = base_diagonal - i;

                for (int compared_diagonal = base_diagonal + 1; compared_diagonal <= diagonalsNumber; compared_diagonal++) {
                    int p0 = (compared_diagonal > dim - 1) ? compared_diagonal - (dim - 1) : 0;
                    int pN = (compared_diagonal > dim - 1) ? dim - 1 : compared_diagonal;
                    for(int p = p0; p <= pN; p++) {
                        int q = compared_diagonal - p;
                        if(matrix[i][j] > matrix[p][q]) count++;

                    }
                }
            }
        }

        return count;
    }
}
