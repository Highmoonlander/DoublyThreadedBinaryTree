
public class DoublyThreadedInOrderTree {
    static class Node{
        int data;
        int lbit, rbit;
        Node left, right;
        Node(int data){
            this.data = data;
            this.lbit = this.rbit = 0;
            this.left = this.right = null;
        }
    }

    public static Node insert(Node head, int data) {
        Node newNode = new Node(data);
        if (head.left == head) {
            head.left = newNode;
            newNode.left = head;
            newNode.right = head;
            head.lbit = 1;
            return head;
        }
        Node curr = head.left;
        Node prev = null;
        do{
            prev = curr;
            if (data < curr.data) {
                if (curr.lbit == 0) {
                    break;
                }
                curr = curr.left;
            } else if (data > curr.data) {
                if (curr.rbit == 0) {
                    break;
                }
                curr = curr.right;
            } else {
                // Handle duplicate values (if needed)
                return head;
            }
        }while (curr != head);

        if (data < prev.data) {
            newNode.left = prev.left;
            prev.left = newNode;
            newNode.right = prev;
            prev.lbit = 1;
        } else if (data > prev.data) {
            newNode.right = prev.right;
            prev.right = newNode;
            newNode.left = prev;
            prev.rbit = 1;
        }
        return head;
    }

    public static void inOrder(Node head){
        Node curr = head.left;
        do{
            while (curr.lbit == 1) {
                curr = curr.left;
            }
            System.out.printf("%d\t",curr.data);
            while (curr.rbit == 0) {
                curr = curr.right;
                if(curr == head){
                    break;
                }
                System.out.printf("%d\t",curr.data);
            }
            curr = curr.right;
        }while(curr != head);
    }

    public static void preOrder(Node head){
        Node curr = head.left;
        do{
            System.out.printf("%d\t",curr.data);
            if(curr.lbit == 1){
                curr = curr.left;
            }
            else if(curr.rbit == 0){
                while (curr.rbit == 0) {
                    curr = curr.right;
                    curr = curr.right;
                }
            }
            else if(curr.rbit == 1){
                curr = curr.right;
            }
        }while(curr != head);
    }

    public static void main(String[] args) {
        Node head = new Node(-1);
        head.rbit = head.lbit = 1;
        head.left = head.right = head;
/*
                8
              /   \
            3       9
           / \       \
          2   5       10
               \
                7     
 */
        int[] arr = {8,3,2,5,9,7,10};
        for(int i : arr){
            head = insert(head, i);
        }
        inOrder(head);
        System.out.println();
        preOrder(head);
    }
}

