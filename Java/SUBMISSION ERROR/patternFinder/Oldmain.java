import java.util.*;

public class Oldmain {
    static int[][] grid;
    static boolean[][] visited;
    static int rows, cols;
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        rows = in.nextInt();
        cols = in.nextInt();
        while (rows != -1 && cols != -1) {
            int minVal = 30000, minRow = 0, minCol = 0;
            int target = -30000;
            in.nextLine(); //flush newline
            grid = new int[rows][cols];
            visited = new boolean[rows][cols];
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    grid[i][j] = in.nextInt();
                    visited[i][j] = false;
                    if (grid[i][j] < minVal) {
                        minVal = grid[i][j];
                        minRow = i;
                        minCol = j;
                    }
                    if (grid[i][j] > target) {
                        target = grid[i][j];
                    }
                }
                in.nextLine(); //flush newline
            }
            //Map frontier = new Map<Integer, Boolean>();          
            boolean found = false;
            if (minRow > 0 && !found) {
                int gap = grid[minRow-1][minCol] - minVal;
                found = found || search(minRow, minCol, target,gap);
                for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) visited[i][j] = false;
            } else if(minRow+1 < rows && !found) {
                int gap = grid[minRow+1][minCol] - minVal;
                found = found || search(minRow, minCol, target,gap);
                for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) visited[i][j] = false;
            } else if(minCol > 0 && !found) {
                int gap = grid[minRow][minCol-1] - minVal;
                found = found || search(minRow, minCol, target,gap);
                for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) visited[i][j] = false;
            } else if(minCol+1 < cols && !found) {
                int gap = grid[minRow][minCol+1] - minVal;
                found = found || search(minRow, minCol, target,gap);
            }
            
            if (found) {
                System.out.println("At least one pattern exists.");
            } else {
                System.out.println("No pattern can be found.");
            }
            rows = in.nextInt();
            cols = in.nextInt();
        }
    }
    private static boolean search(int row, int col, int target, int gap) { 
        visited[row][col] = true;
        if (grid[row][col] == target) return true;
        if (row > 0 && !visited[row-1][col] && (grid[row-1][col] - grid[row][col] == gap)) {
            if(search(row-1, col, target, gap)) return true;
        } else if(row+1 < rows && !visited[row+1][col]&& (grid[row+1][col] - grid[row][col] == gap)) {
            if(search(row+1, col, target, gap)) return true;
        } else if(col > 0 && !visited[row][col-1]&& (grid[row][col-1] - grid[row][col] == gap)) {
            if(search(row, col-1, target, gap)) return true;
        } else if(col+1 < cols && !visited[row][col+1]&& (grid[row][col+1] - grid[row][col] == gap)) {
            if(search(row, col+1, target, gap)) return true;
        }
        return false;
    }
}