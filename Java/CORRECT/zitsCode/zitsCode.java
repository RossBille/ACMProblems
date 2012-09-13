import java.util.*;
import java.lang.*;
import java.io.*;
public class Main {
    static char[][] grid;
    static int maxSize = 0;
    public static void gridWrite(String message, int size) {
        int charCount = 0;
        int charNum = size*size;
        int count = 0;
        while (charCount < charNum) {
            int bounds = size-count;
            for (int i = 0 + count; i < bounds; i++) {
                if (charCount < message.length()){
                    grid[count][i] = message.charAt(charCount);
                } else {
                    grid[count][i] = '$';
                }
                charCount++;
            }
            for (int i = 1+count; i < bounds; i++) {
                if (charCount < message.length()){
                    grid[i][bounds-1] = message.charAt(charCount);
                } else {
                    grid[i][bounds-1] = '$';
                }
                charCount++;
            }
            for (int i = 1; i < bounds-count; i++) {
                if (charCount < message.length()){
                    grid[bounds-1][bounds-1-i] = message.charAt(charCount);
                } else {
                    grid[bounds-1][bounds-1-i] = '$';
                }
                charCount++;
            }
            for (int i = 1; i < bounds-count-1; i++) {
                if (charCount < message.length()) {
                    grid[bounds-i-1][count] = message.charAt(charCount);
                } else {
                    grid[bounds-i-1][count] = '$';
                }
                charCount++;
            }
            count++;
        }
    }
    public static void printGrid(int size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                System.out.print(grid[i][j]);
            }
        }
    }
    public static void main(String[] args) throws IOException {
        
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        
        int caseNum = Integer.parseInt(in.readLine());
        
        for (int i = 0; i < caseNum; i++) {
            
            String message = in.readLine();
            int size = (int)Math.ceil(Math.sqrt((double)message.length()));
            
            if (size > maxSize) {
                grid = new char[size][size];
                maxSize = size;
            }
            
            gridWrite(message, size);
            printGrid(size);
            //if (i != caseNum - 1) {
                System.out.println();
           // }
           
            
        }
    }
}
        