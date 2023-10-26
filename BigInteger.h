#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node* next;
};
struct BigInteger
{
    struct node* head;
    int length;
    char sign;
};

struct node* insert(struct node* head, int val);
void insert_end(struct BigInteger* n, int element);
int length(struct node* head);
struct node* reverse(struct node* head);
int compare(struct BigInteger n1, struct BigInteger n2);
struct BigInteger initialize(char* s);
void trailing(struct node ** head);
struct BigInteger add(struct BigInteger n1, struct BigInteger n2);
struct BigInteger sub(struct BigInteger n1, struct BigInteger n2);
struct BigInteger mul(struct BigInteger n1, struct BigInteger n2);
void displaylinked(struct node* head);
void display(struct BigInteger n);
void display(struct BigInteger n);
void free_linked(struct BigInteger* n);