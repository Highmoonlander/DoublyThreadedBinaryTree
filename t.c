#include <stdio.h>
#include <stdlib.h>
#define MAX 10

struct node{
    int data;
    struct node* left,*right;
    int lbit,rbit;
};

struct node* createNode(int data){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->lbit = newNode->rbit = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct node* insert(struct node* head,int data){
    struct node* prev,*curr,*newNode = createNode(data);
    if(head->left == head){
        head->lbit = 1;
        newNode->left = head->left;
        newNode->right = head;
        head->left = newNode;
        return head;
    }
    curr = head->left;
    while(1){
        prev = curr;
        if(data < curr->data && curr->lbit == 1){
            curr = curr->left;
        }
        else if(data > curr->data && curr->rbit == 1){
            curr = curr->right;
        }
        else{
            break;
        }
    }
    if(data < prev->data){
        newNode->left = prev->left;
        newNode->right = prev;
        prev->lbit = 1;
        prev->left = newNode;
    }
    else if(data > prev->data){
        newNode->right = prev->right;
        newNode->left = prev;
        prev->right = newNode;
        prev->rbit = 1;
    }
    return head;
}

void inOrder(struct node* head){
    struct node* curr = head->left;
    if(curr == head){
        return;
    }
    while(curr != head){
        while(curr->lbit == 1){
            curr = curr->left;
        }
        printf("%d\t",curr->data);
        while(curr->rbit == 0 && curr->right != head){
            curr = curr->right;
            printf("%d\t",curr->data);
        }
        curr = curr->right;
    }
    printf("\n");
}

struct node* inOrderPredesessor(struct node* root){
    root = root->left;
    while(root->rbit == 1){
        root = root->right;
    }
    return root;
}

struct node* delete(struct node* head,int data){
    struct node* curr = head->left,*prev = NULL;
    while(curr != NULL && curr->data != data){
        prev = curr;
        curr = (data < curr->data) ? curr->left : curr->right;
    }
    if(curr == NULL){
        printf("error 404!");
        return head;
    }
    if(curr->rbit == 0 && curr->lbit == 0){
        if(prev != NULL){
            if(curr == prev->left){
                prev->left = curr->left;
                prev->lbit = 0;
            }
            else{
                prev->right = curr->right;
                prev->rbit = 0;
            }
        }else{
            head->left = head;
        }
        free(curr);
    }
    else if(curr->rbit == 0 || curr->lbit == 0){
        struct node *child = (curr->lbit == 1) ? curr->left : curr->right;
        if(prev != NULL){
            if(curr == prev->left){
                prev->left = child;
            }
            else{
                prev->right = child;
            }
        }else{
            head->left = child;
        }
        free(curr);
    }
    else{
        struct node* iPre = inOrderPredesessor(curr);
        int temp = iPre->data;
        delete(head,iPre->data);
        curr->data = temp;
    }
    return head;
}

int main() {
    struct node* head = createNode(0);
    head->lbit = head->rbit = 0;
    head->left = head->right = head;
    head = insert(head ,10);
    head = insert(head, 8);
    head = insert(head, 15);
    head = insert(head, 5);
    head = insert(head, 9);
    head = insert(head, 13);
    head = insert(head, 17);
    printf("Inorder-->");
    inOrder(head);
    head = delete(head,8);
    printf("inorder-->");
    inOrder(head);
    return 0;
}