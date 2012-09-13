import java.util.*;
public class Main {
    static final int MAX_VAL = 30000;
    static final int MIN_VAL = -30000;
    static final int BORDER = -30001;
    
    static Cell[][] grid = new Cell[101][101];
    static int rows, cols;
    
    private static class Cell {
        public int row, col, val;
        public boolean visited;
        Cell(int r, int c, int v) {
            row = r;
            col = c;
            val = v;
            visited = false;
        }
    }
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        rows = in.nextInt()+1;
        cols = in.nextInt()+1;
        in.nextLine();
        
        for (int i = 0; i < 101; i++) {
            for (int j = 0; j < 101; j++) {
                grid[i][j] = new Cell(i,j,BORDER);
            }
        }
        
        while (rows != 0 && cols != 0) {
            for (int i = 0; i < rows; i++) {
                 grid[i][cols] = new Cell(i,0,BORDER);
                 grid[rows][i] = new Cell(0,i,BORDER);
            }
                
            int target = MIN_VAL, minVal = MAX_VAL;
            for (int i = 1; i < rows; i++) {
                for (int j = 1; j < cols; j++) {
                    grid[i][j] = new Cell(i,j,in.nextInt());
                    if (grid[i][j].val < minVal) {
                        minVal = grid[i][j].val;
                    }
                    if (grid[i][j].val > target) {
                        target = grid[i][j].val;
                    }
                }
                in.nextLine();
            }
            
            LinkedList<Cell> startPoints = new LinkedList<Cell>();
            for (int i = 1; i < rows; i++) {
                for (int j = 1; j < cols; j++) {
                    if (grid[i][j].val == minVal) {
                        startPoints.add(grid[i][j]);
                    }
                }
            }
            
            boolean found = false;
            while (!startPoints.isEmpty() && !found) {
                Cell cur = startPoints.getFirst();
                startPoints.removeFirst();
                Integer[] gaps = getGaps(cur);
                if (gaps.length > 0) {
                    for (int i = 0; i < gaps.length && !found; i++) {
                        found = search(cur, gaps[i], target);
                        for (int a = 1; a < rows; a++) for (int b = 0; b < cols; b++) grid[a][b].visited = false;
                    }
                }
            }
            
            if (found) {
                System.out.println("At least one pattern exists.");
            } else {
                System.out.println("No pattern can be found.");
            }
            rows = in.nextInt()+1;
            cols = in.nextInt()+1;
            in.nextLine();
        }
    }
    private static Integer[] getGaps(Cell c) {
        int x = c.row, y = c.col;
        int north = grid[x][y-1].val, south = grid[x][y+1].val;
        int east = grid[x-1][y].val, west = grid[x+1][y].val;
        
        ArrayList<Integer> list = new ArrayList<Integer>();
        if (north != BORDER) list.add(north-c.val);
        if (south != BORDER) list.add(south-c.val);
        if (east != BORDER) list.add(east-c.val);
        if (west != BORDER) list.add(west-c.val);
        list.trimToSize();
        
        return list.toArray(new Integer[list.size()]);
    }
    private static boolean search(Cell cur, int gap, int target) {
        if (cur.val == target) return true;
        cur.visited = true;
        
        int x = cur.row, y = cur.col;
        boolean found = false;
        Cell north = grid[x][y-1], south = grid[x][y+1];
        Cell east = grid[x-1][y], west = grid[x+1][y];
        
        if (north.val != BORDER && !north.visited && north.val-cur.val == gap) found = found || search(north, gap, target);
        if (south.val != BORDER && !south.visited && south.val-cur.val == gap) found = found || search(south, gap, target);
        if (east.val != BORDER && !east.visited && east.val-cur.val == gap) found = found || search(east, gap, target);
        if (west.val != BORDER && !west.visited && west.val-cur.val == gap) found = found || search(west, gap, target);
        
        return found;
    }
}
                        