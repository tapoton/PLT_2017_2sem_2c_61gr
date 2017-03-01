package Solution;

import java.io.*;
import java.util.*;

/**
 * Laba 2.Task 14. There are list of students : 
FIO, number of student card, list of backlogs. 
Find information about the student with entered number of student card.
 */
public class HashChainApp {

    public static void main(String[] args) throws IOException
    {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        int size,n,key,number,choice;
        ArrayList<String> list = new ArrayList<>();
        String name;
        Link item;

        System.out.println("Enter size of hash table: ");
        size = getInt();
        System.out.println("Enter amount of items: ");
        n = Integer.parseInt(reader.readLine());

        HashTable theTable = new HashTable(size);

        for (int i=0;i<n;i++) {
            System.out.println("Enter name of student: ");
            name = getString();
            System.out.println("Enter id of student: ");
            key = getInt();
            System.out.println("Enter number of backlogs: ");
            number = getInt();
            if (number != 0) {
                System.out.println("Enter each backlog in new line: ");
                for (int j=0;j<number;j++) {
                    list.add(getString());
                }
            }
            else
                list.add(name + " hasn`t backlogs");
            item = new Link(name,key,list);
            theTable.insert(item);
            list.clear();
        }

        while (true) {
            System.out.println("Enter 1 for exit, 2 for find the student, 3 for display all students: ");
            choice = getInt();

            switch (choice) {
                case 1: return;
                case 2:
                    System.out.println("Enter id for find: ");
                    key = getInt();
                    item = theTable.find(key);
                    if (item != null)
                    {
                        item.displayLink();
                    }
                    else
                        System.out.println("Couldn`t find student with id = " + key);
                    break;
                case 3:
                    theTable.displayHashTable();
            }
        }
    }

    public static String getString() throws IOException
    {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String s = reader.readLine();
        return s;
    }

    public static int getInt() throws IOException
    {
        String s = getString();
        return Integer.parseInt(s);
    }
}
