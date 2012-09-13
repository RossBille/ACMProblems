import java.util.*;

public class tripVerification {
    static Vector< List<Integer> > adjList;
    private static boolean search(int searchTo, int nodeNumber) {
        boolean possible = true;
        /* basically, for each city in the initial list, find a path between
         * n and n+1 by doing a BFS to find a path between them */
        for (int i = 0; i+1 <= searchTo-1; i++) {
            possible = possible && BFS(i, i+1, nodeNumber);
            if (!possible) {
                break;
            }
        }
        return possible;
    }
    private static boolean BFS(int start, int target, int nodeNumber) {
        /* standard BFS stuff, not much to say. Stops the BFS adding nodes
           before the current city in the initial path list*/
        LinkedList<Integer> queue = new LinkedList<Integer>();
        boolean[] visited = new boolean[nodeNumber];
        for (boolean i : visited) i = false;
        for (int i = 0; i < start; i++) visited[i] = true;
        visited[start] = true;
        queue.addLast(start);
        while (!queue.isEmpty()) {
            Integer cur = queue.getFirst();
            queue.removeFirst();
            for(int i = 0; i < adjList.elementAt(cur).size(); i++) {
                int node = adjList.elementAt(cur).get(i);
                if (node == target) return true;
                if (!visited[node]) {
                    visited[node] = true;
                    queue.addLast(node);
                }
            }
        }
        return false;
    }
    public static void main(String args[]) {
        /* the 'random' in.nextLine()'s you'll see are to remove the linebreak from the
         * end of lines so the Scanner methods don't get mucked up */
         
        Scanner in = new Scanner(System.in);
        while (in.hasNext()) {
            Map<String, Integer> nameMap = new HashMap<String, Integer>();
            adjList = new Vector< List<Integer> >();
            int cityNum = in.nextInt();
            int initialNum = cityNum;
            if (cityNum != 0) {
                in.nextLine();
                /* initial city input loop*/
                for (int i = 0; i < cityNum; i++) {
                    nameMap.put(in.next(), new Integer(i));
                    adjList.addElement(new ArrayList<Integer>());
                }
                in.nextLine();
                
                int tripNum = in.nextInt();
                in.nextLine();
                /* Graph building and city list adding
                 * if a city hasn't been seen before, it's added to the nameMap
                 * before being added to the adjList vector. I used ArrayList over LinkedList
                 * because I'll be accessing those elements directly. I suppose I could have
                 * used LinkedList and then toArray().
                 */
                for (int i = 0; i < tripNum; i++) {
                    String firstCity = in.next();
                    String secondCity = in.next();
                    in.nextLine();
                    //First city in the pairing
                    if (!nameMap.containsKey(firstCity)) {
                        nameMap.put(firstCity,new Integer(cityNum++));
                        adjList.addElement(new ArrayList<Integer>(cityNum));
                    }
                    //Second city in the pairing
                    if(!nameMap.containsKey(secondCity)) {
                        nameMap.put(secondCity,new Integer(cityNum++));
                        adjList.addElement(new ArrayList<Integer>(cityNum));
                    }
                    
                    int firstIndex = nameMap.get(firstCity), secondIndex = nameMap.get(secondCity);
                    adjList.elementAt(firstIndex).add(secondIndex);
                }
                if(search(initialNum, cityNum)) {
                    System.out.println("The tour can be planned.");
                } else {
                    System.out.println("The tour cannot be planned with the given flight segments.");
                }
            } else {
                break;
            }
        }
    }
}