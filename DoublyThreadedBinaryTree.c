#include<stdio.h>
#include<stdlib.h>
#define MAX 50

struct node{
    int data;
    int lbit,rbit;
    struct node* left,*right;
};

struct node* createNode(int data){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->lbit = newNode->rbit = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct node* insertTBT(struct node* head,int data){
    struct node* temp, *curr;
    temp = createNode(data);
    if(head->left == head){
        temp->left = temp->right = head;
        head->left = temp;
        return head;
    }
    curr = head->left;
    while(1){
        if(data < curr->data && curr->lbit == 1){
            curr = curr->left;
        }
        if(data > curr->data && curr->rbit == 1){
            curr = curr->right;
        }
        else{
            break;
        }
    }
    if(data < curr->data){
        curr->lbit = 1;
        temp->left = curr->left;
        curr->left = temp;
        temp->right = curr;
    }
    else if(data > curr->data){
        curr->rbit = 1;
        temp->right = curr->right;
        curr->right = temp;
        temp->left = curr;
    }
    return head;
}

void inOrderTBT(struct node* head){
    struct node* temp = head->left;
    while(temp != head){
        while(temp->lbit == 1){
            temp = temp->left;
        }
        printf("%d\t",temp->data);
        while(temp->rbit == 0 && temp->right != head){
            temp = temp->right;
            printf("%d\t",temp->data);
        }
        temp = temp->right;
    }
    printf("\n");
}

// void inOrder(struct node* head){
//     struct node* temp = head->left;
//     while(temp->lbit != 0){
//         temp = temp->left;
//     }
//     while(temp != head){
//         printf("%d\t",temp->data);
//         temp = temp->right;
//     }
//     return;
// }

struct node* inorderPredecessor(struct node* root){
    root = root->left;
    while(root->rbit == 1){
        root = root->right;
    }
    return root;
}

struct node* deleteTBT(struct node* head, int data) {
    struct node *parent = NULL, *curr = head->left;

    while (curr != NULL && curr->data != data) {
        parent = curr;
        curr = (data < curr->data) ? curr->left : curr->right;
    }

    if (curr == NULL) {
        printf("Node not found!");
        return head;
    }

    if (curr->lbit == 0 && curr->rbit == 0) {
        if (parent != NULL) {
            if (curr == parent->left) {
                parent->lbit = 0;
                parent->left = curr->left;
            } else {
                parent->rbit = 0;
                parent->right = curr->right;
            }
        } else {
            head->left = head;
        }
        free(curr);
    } else if (curr->lbit == 0 || curr->rbit == 0) {
        struct node* child = (curr->lbit == 1) ? curr->left : curr->right;
        if (parent != NULL) {
            if (curr == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        } else {
            head->left = child;
        }
        free(curr);
    } else {
        struct node* pred = inorderPredecessor(curr);
        int tempData = pred->data;
        deleteTBT(head, pred->data);
        curr->data = tempData;
    }
    return head;
}

void preOrder(struct node* head){
    struct node* curr = head->left;
    while(curr != head){
        while(curr->lbit != 0){
            printf("%d\t",curr->data);
            curr = curr->left;
        }
        while(curr != head && curr->rbit == 0){
            if(curr->rbit == 0){
                printf("%d\t",curr->data);
            }
            curr = curr->right;
        }
        curr = curr->right;
    }
}

int main(){
    int data,choice;
    struct node* head = (struct node*)malloc(sizeof(struct node));
    head->lbit = head->rbit = 1;
    head->left = head->right = head;
    while(1){
        printf("Following operations can be Performed on a TBT:\n");
        printf("1. Insert\n2. Inorder\n3. Deletion\n4. Exit\n5.preOrder\n");
        printf("Enter you choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter data: ");
                scanf("%d",&data);
                head = insertTBT(head, data);
            break;
            case 2:
                printf("Inorder-->\n");
                inOrderTBT(head);
            break;
            case 3:
                printf("Enter the data to delete: ");
                scanf("%d",&data);
                head = deleteTBT(head, data);
            break;
            case 4:
                exit(0);
            break;
            case 5:
                printf("Preorder-->\n");
                preOrder(head);
            default: printf("Invalid choice!!\n");
        }
    }
}
