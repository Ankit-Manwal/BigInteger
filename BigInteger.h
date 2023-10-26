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

struct node* insert_node(struct node* head, int val);
struct BigInteger initialize(char* s);
void insert_big_end(struct BigInteger* n, int val) ;
int length(struct node* head);
struct node* reverse(struct node* head);
int compare(struct BigInteger n1, struct BigInteger n2);
void trailing(struct node ** head);
struct BigInteger add(struct BigInteger n1, struct BigInteger n2);
struct BigInteger sub(struct BigInteger n1, struct BigInteger n2);
struct BigInteger mul(struct BigInteger n1, struct BigInteger n2);
struct BigInteger div1(struct BigInteger n1, struct BigInteger n2);
void displaylinked(struct node* head);
void display(struct BigInteger n);
void free_linked(struct BigInteger* n);
