package Solution;

import java.util.ArrayList;

/**
 * Created by Алена on 01.03.2017.
 */
public class Link {
    private String name;
    private int id;
    private ArrayList<String> exam = new ArrayList<>();
    public Link next;

    public Link(String name,int id,ArrayList<String> list) {
        this.name = name;
        this.id = id;
        for (String element : list) {
            exam.add(element);
        }
    }

    public int getId() {
        return id;
    }

    public void displayLink() {
        System.out.print(name + ", id =  " + id + ", list of backlogs: ");
        for (String element : exam) {
            System.out.print(element+" ");
        }
        System.out.println("");
    }
}
