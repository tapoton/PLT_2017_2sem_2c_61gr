package test;

import java.util.ArrayList;


public class Point {
    private int x,y;
   // private ArrayList<Integer> listOfOtherPointX = new ArrayList<>();
   // private ArrayList<Integer> listOfOtherPointY = new ArrayList<>();
    private ArrayList<String> listOfLine = new ArrayList<>();

    public Point(int x,int y) {
        this.x = x;
        this.y = y;
    }

    public Integer getX() {
        return x;
    }

    public Integer getY() {
        return y;
    }

    public String getLine(int i) {
        return listOfLine.get(i);
    }

    public Boolean FindLine(String line) {

            for (String element : listOfLine) {
                    if (element.equals(line))
                        return true;
            }

            return false;
    }

    public void setLine(String line) {
        listOfLine.add(line);
    }

    public void PrintPoint() {
        System.out.print("( " + x + ";" + y + " ) : ");
        for (String elem : listOfLine)
            System.out.print(elem + "; ");
    }
}
