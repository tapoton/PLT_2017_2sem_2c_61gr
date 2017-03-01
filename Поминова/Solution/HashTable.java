package Solution;

/**
 * Created by Алена on 01.03.2017.
 */
public class HashTable {
    private SortedList[] hashArray;
    private int size;

    public HashTable(int size) {
        this.size = size;
        hashArray = new SortedList[this.size];
        for (int i=0;i<this.size;i++)
            hashArray[i] = new SortedList();
    }

    public void displayHashTable() {
        for (int i=0;i<size;i++)
        {
            System.out.print((i+1) + ": ");
            hashArray[i].displayList();
        }
    }

    public int hashFunc (int key) {
        return key % size;
    }

    public void insert(Link theLink) {
        int key = theLink.getId();
        int hashValue = hashFunc(key);
        hashArray[hashValue].insert(theLink);
    }

    public Link find(int key) {
        int hashValue = hashFunc(key);
        Link theLink = hashArray[hashValue].find(key);
        return theLink;
    }
}
