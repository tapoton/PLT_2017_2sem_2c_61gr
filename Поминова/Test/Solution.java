package test;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

/**
 * Laba 3. Task 15. Find min set of lines on which you can place all points of given set
 *
 */
public class Solution {

    static Boolean[] used;
    static Boolean[] usedP;
    static ArrayList<String> listOfLines = new ArrayList<>(); //list of all lines
    static int bestChoiceN;
    static int count = 0; //amount of lines
    static ArrayList<String> curChoice = new ArrayList<>();
    static ArrayList<String> bestChoice = new ArrayList<>();
    static ArrayList<Point> listOfPoints = new ArrayList<>(); //list of all points
    static int amountOfPoints;

    public static void main(String[] args) throws IOException {

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        int x,y;
        System.out.println("Enter amount of points more than 1: ");
        amountOfPoints = Integer.parseInt(reader.readLine());

        usedP = new Boolean[amountOfPoints];
        for (int i=0;i<amountOfPoints;i++)  //create list of points
        {
            System.out.println("Enter coordinates if point x and y by new line: ");
            x = Integer.parseInt(reader.readLine());
            y = Integer.parseInt(reader.readLine());
            Point p = new Point(x,y);
            usedP[i] = false;
            listOfPoints.add(p);
        }

        for (int i=0;i<amountOfPoints;i++) {   //for each point found line which connects it with each of other points
            Point p = listOfPoints.get(i);
            for (int j=0;j<amountOfPoints;j++) {
                if (i == j)
                    p.setLine("null");
                else
                {
                    Point q = listOfPoints.get(j);
                    String l = BuildLine(p.getX(),p.getY(),q.getX(),q.getY());
                    p.setLine(l);
                    if (!Find(l))   //add new line to list of lines
                    {
                        listOfLines.add(l);
                        count++;
                    }
                }
            }
        }

        used = new Boolean[count];
        for (int i=0;i<count;i++)
            used[i] = false;

        bestChoiceN = count;
        for (int i=0;i<count;i++) {
            int j=0;
            used[i] = true;
            String line = listOfLines.get(i);
            curChoice.add(line);

            for (Point elem: listOfPoints) {
                if (!usedP[j]) {
                    if (elem.FindLine(line))
                    usedP[j] = true;
                }
                j++;
            }
            j--;

            Recurs(i); //call recurs and before remember current line in CurChoice array

            curChoice.clear();
            for (int k=0;k<j;k++) {
                usedP[k] = false;
            }

            used[i] = false;
        }

        for (Point elem : listOfPoints) {
            elem.PrintPoint();
            System.out.println();
        }

       /* for (String elem : listOfLines) {
            System.out.println(elem);
        }*/
        System.out.println("");
        for (String elem : bestChoice) {
            System.out.print(elem + "   ");
        }
    }

    public static Boolean Find(String line) {
        for (String elem : listOfLines)
            if (elem.equals(line))
                return true;
        return false;
    }

    public static String BuildLine (int x1, int y1, int x2, int y2) {
        double k,b;
        String line = "y = ";

        if (x1 == x2)
        {
            return ("x = " + x1);
        }

        k = (double)(y2 - y1)/(x2 - x1);
        b = y1 - k * x1;

        if (Math.abs(k) == 1.0){
            if (k<0)
                line += "-x ";
            else
                line += "x ";
        }
        else
            if (k != 0.0)
                line += k + "x ";

        if (b != 0.0) {
            if (b > 0)
                line += "+ " + b;
            else
                line += b;
        }

        return line;
    }

    public static void Recurs(int curn) {   //Recurs function

        if (curn < bestChoiceN) {   //if current amount of lines less then bestChoiceN then continue
            //remember current choice
            Boolean fl = true;
            for (int i=0;i<amountOfPoints;i++) {
               // System.out.println(curn +" "+ used[i] + " ");
                if (!usedP[i])
                    fl = false;
            }

            if (fl) {              //if there isn`t points then remember current choice as best choice
            //    System.out.println("YES " + curn);
                bestChoice.clear();                    //clear previous choice
                for (String elem: curChoice)
                    bestChoice.add(elem);
                bestChoiceN = curn;
            }

            for (int i=0;i<count;i++) {
                if (!used[i] && !listOfPoints.isEmpty()) {
                    used[i] = true;
                    String line = listOfLines.get(i);
                    curChoice.add(line);   //choose current line

                    ArrayList<Integer> deletingPoint = new ArrayList<>();

                    int j=0;
                    for (Point elem: listOfPoints) {
                        if (!usedP[j] && elem.FindLine(line)) {
                            usedP[j] = true;
                            deletingPoint.add(j);
                        }
                        j++;
                    }
                    j--;

                    Recurs(curn+1); //recurs call

                    used[i] = false;
                    for (Integer index: deletingPoint) {
                        usedP[index] = false;
                    }
                    deletingPoint.clear();
                    curChoice.remove(listOfLines.get(i));
                }
            }
        }
    }
}

