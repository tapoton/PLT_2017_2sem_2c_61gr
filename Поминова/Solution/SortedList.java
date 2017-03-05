package Solution;

/**
 * Created by Алена on 01.03.2017.
 */
public class SortedList {
    private Link first;

    public SortedList() {
        first = null;
    }

    public void insert(Link theLink) {
        int key = theLink.getId();
        Link previous = null;
        Link current = first;

        while (current != null && key > current.getId()) {
            previous = current;
            current = current.next;
        }

        if (previous == null)
            first = theLink;
        else
            previous.next = theLink;
        theLink.next = current;
    }

    public Link find(int key) {
        Link current = first;

        while (current != null && current.getId() <= key) {
            if (current.getId() == key)
                return current;
            current = current.next;
        }

        return null;
    }

    public void displayList() {
        Link current = first;

        while (current != null) {
            current.displayLink();
            current = current.next;
        }
        System.out.println("");
    }
}
