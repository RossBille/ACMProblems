import java.util.*;
import java.io.*;

public class Main {
    static int charCount = 0;
    static boolean firstLine = true;
    static boolean firstPageNum = true;
    public static void main(String args[]) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        Scanner s = new Scanner(in.readLine());
        int maxLines = s.nextInt();
        int outWidth = s.nextInt();
        s.close();
        
        String pageLine = " ";
        int pageCount = 1;
        while(!pageLine.equals("##")) {
            charCount = 0;
            firstLine = true;
            String tempParse = in.readLine().trim();
            if (tempParse.equals("##")) break;
            if (firstPageNum) {
                System.out.println("Page number " + pageCount++);
                firstPageNum = false;
            } else {
                System.out.println("\nPage number " + pageCount++);
            }
            int pageWidth = Integer.parseInt(tempParse);
            LinkedList<String> page = new LinkedList<String>();
            pageLine = in.readLine();
            int lineCount = 1;
            while (!pageLine.equals("#")) {
                page.add(pageLine);
                lineCount++;
                pageLine = in.readLine();
            }
            if (lineCount != 1) {
                String[] vertPage = new String[pageWidth];
                for (int i = 0; i < pageWidth; i++) vertPage[i] = "";
                
                for(int i = 0; i < pageWidth; i++) {
                    ListIterator list = page.listIterator(0);
                    while(list.hasNext()) {
                        String temp = (String)list.next();
                        vertPage[i] += temp.charAt(i);
                    }
                }
                Scanner[] scanArr = new Scanner[pageWidth];
                for (int i = 0; i < pageWidth; i++) scanArr[i] = new Scanner(vertPage[i]);
                boolean pageFinished = false;
                while(!pageFinished) {
                    for (int i = 0; i < pageWidth; i++) {
                        if(scanArr[i].hasNext()) {
                            printPage(scanArr[i].next(), outWidth);
                        }
                    }
                    for (int i = 0; i < pageWidth; i++) {
                        if (scanArr[i].hasNext()) {
                            pageFinished = pageFinished || true;
                        }
                    }
                    pageFinished = !pageFinished;
                }
                for (int i = 0; i < pageWidth; i++) scanArr[i].close();
            } else {
                System.out.print("This page is empty.");
            }
        }
        System.out.print("");
    }
    private static void printPage(String word, int limit) {
        if ((word.length() + charCount) > limit) {
            if (!firstLine) {
                System.out.println();
            } else {
                firstLine = false;
            }
            System.out.print(word+" ");
            charCount = word.length() + 1;
        } else {
            firstLine = false;
            System.out.print(word+" ");
            charCount += word.length() + 1;
        }
    }     
}