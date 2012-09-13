import java.util.*;
public class Main {
    
    static int[] monthArr;
    static int maxSize = 0;
    public static void main(String[] args) {
        
        Scanner in = new Scanner(System.in);
        
        int monthNum = in.nextInt();
        in.nextLine();
        
        while (monthNum != 0) {
            
            if (monthNum > maxSize) {
                monthArr = new int[monthNum];
                maxSize = monthNum;
            }
            int largestMonth = 0;
            for (int i = 0; i < monthNum; i++) {
                monthArr[i] = in.nextInt();
                if (monthArr[i] > largestMonth) {
                    largestMonth = monthArr[i];
                }
            }
            in.nextLine();
            
            int moonCycle = in.nextInt();
            
            in.nextLine();
            
            Scanner dateParse = new Scanner(in.nextLine()).useDelimiter("/");
            int initDay = dateParse.nextInt();
            int initMonth = dateParse.nextInt();
            int initYear = dateParse.nextInt();
            
            int day = initDay, month = initMonth-1, year = initYear;
            dateParse.close();
            boolean possible = true;
            
            if (moonCycle > largestMonth) {
                possible = false;
            }
            
            int nextCycle = moonCycle;
            Map<String, Boolean> visited = new HashMap<String,Boolean>();
            if (possible != false) {
                possible = false;
                do {
                    String currentDay = day + " " + month;
                    if (visited.containsKey(currentDay)) {
                        break;
                    } else {
                        visited.put(currentDay, true);
                    }
                    if (nextCycle < monthArr[month] && (monthArr[month]-nextCycle) > day) {
                        possible = true;
                        day += moonCycle;
                    } else {
                        day = day + nextCycle;
                        while (day > monthArr[month]) {
                            if (day > monthArr[month]) {
                                day -= monthArr[month];
                                month++;
                            }
                            if (month > monthNum-1) {
                                month = 0;
                                year++;
                            }
                        }
                    }                
                } while (!possible);
            }
            if (possible) {
                System.out.println("The next Blue Moon Festival will be held on " + day + "/" + (month+1) + "/" + year + ".");
            } else {
                System.out.println("There can never be a Blue Moon Festival");
            }
            monthNum = in.nextInt();
        }
    }
}
            
        