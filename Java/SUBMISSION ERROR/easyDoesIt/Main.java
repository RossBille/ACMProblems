import java.util.*;
import java.lang.*;
public class Main {
    /* constant declarations */
    
    /* Inner class declaration */
    private static class Name {
        
        /* Member declarations */
        
        /* Methods */
        
    }
    
    /* global declarations (arrays, array sizes etc) */
    static Vector< List<Integer> > adjList;
    public static void main(String args[]) {
        
        Scanner in = new Scanner(System.in);
        
        //get start case input
        int cityNum = in.nextInt();
        in.nextLine();
        while (cityNum != 0) {
            Map<String, Integer> nameMap = new HashMap<String, Integer>();
            adjList = new Vector< List<Integer> >();
            for (int i = 0; i < cityNum; i++) {
                adjList.addElement(new LinkedList<Integer>());
                String city = in.next();
                nameMap.put(city, i);
                in.nextLine();
            }
            int roadNum = in.nextInt();
            in.nextLine();
            
            for(int i = 0; i < roadNum; i++) {
                LinkedList<Integer> roadCities = new LinkedList<Integer>();
                String line = in.nextLine();
                line = line.trim();
                int count = 0;
                Scanner lineScan = new Scanner(line);
                while (lineScan.hasNext()) {
                    lineScan.next();
                    roadCities.add(nameMap.get(lineScan.next()));
                    count++;
                }
                Integer[] cityArray = new Integer[count]; 
                roadCities.toArray(cityArray);
                
                for (int k = 0; k < cityArray.length; k++) {
                    for (int j = 0; j < cityArray.length; j++) {
                        if (j != k) {
                            adjList.elementAt(cityArray[k]).add(cityArray[j]);
                        }
                    }
                }
            }
            int queryNum = in.nextInt();
            
            for (int i = 0; i < queryNum; i++) {
                String s = in.next();
                String t = in.next();
                int start = nameMap.get(s);
                int target = nameMap.get(t);
                
                in.nextLine();
                
                int[] dist = new int[cityNum];
                for (int c = 0; c < cityNum; c++) {
                    dist[c] = 101;
                }
                boolean[] visited = new boolean[cityNum];
                for(boolean b : visited) b = false;
                
                LinkedList<Integer> queue = new LinkedList<Integer>();
                queue.addLast(start);
                visited[start] = true;
                dist[start] = 0;
                int smallDist = 0;
                boolean found = false;
                while(!queue.isEmpty() && found == false) {
                    int cur = queue.getFirst();
                    queue.removeFirst();
                    for (int b = 0; b < adjList.elementAt(cur).size(); b++) {
                        Integer a = adjList.elementAt(cur).get(b);
                        if (a == target) {
                            smallDist = dist[cur]+1;
                            found = true;
                            break;
                        }
                        if (visited[a] == false) {
                            queue.addLast(a);
                            visited[a] = true;
                            if (dist[a] > dist[cur] + 1) dist[a] = dist[cur]+1;
                        }
                    }
                }
                System.out.println("Number of roads needed from " + s + " to " + t + " is " + smallDist);
                cityNum = in.nextInt();
            }
        }
    }
}