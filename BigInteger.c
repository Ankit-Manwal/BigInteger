#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"


 int length(struct node* head)
{
    int count = 0;
    while (head) {
        head = head->next;
        count++;
    }
    return count;
}

struct node* insert(struct node* head, int val)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    
    temp->data = val;
    temp->next = head;
    return temp;
}

void insert_end(struct BigInteger* n, int val) 
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));

    temp->data = val;
    temp->next = NULL;
    n->length += 1;
    if (n->head == NULL) {
        n->head = temp;
        return;
    }
    struct node* itr = n->head;
    while (itr->next != NULL) {
        itr = itr->next;
    }
    itr->next = temp;
}
struct node* reverse(struct node* head)
 {
    struct node* prev = NULL, * front = NULL, * curr = head;
    while (curr) 
    {
        front = curr->next;
        curr->next = prev;
        prev = curr;
        curr = front;
    }
    return prev;
}


int compare(struct BigInteger n1, struct BigInteger n2) 
{
    if (n2.length > n1.length) {
        return 1;
    } 
    else if (n2.length == n1.length) {
        int tempR = 0;
        n1.head = reverse(n1.head);
        n2.head = reverse(n2.head);
        struct node* head1 = n1.head, * head2 = n2.head;
        while (head1 != NULL && head2 != NULL)
         {
            if (head2->data > head1->data)
             {
                tempR = 1;
                break;
            } 
            else if (head1->data < head2->data) 
            {
                tempR = 0;
                break;
            }
            head1 = head1->next;
            head2 = head2->next;
        }
        n1.head = reverse(n1.head);
        n2.head = reverse(n2.head);
        return tempR;
    }
    return 0;
}

//initialize
struct BigInteger initialize(char* s)
{
    struct BigInteger temp;
    int i;
    temp.head = NULL;
    if(s[0] == '-')  temp.sign = '-';  
    else   temp.sign = '+';
    if(temp.sign == '-')   i = 1;   
    else    i = 0;
    for(i; s[i] != '\0'; i++)
        temp.head = insert(temp.head, s[i] - '0'); 
    temp.length = length(temp.head);
    return temp;
}

void trailing(struct node ** head)
{  
    *head=reverse(*head);
    while (*head  && (*head)->data == 0)
    {
        struct node* tmp = head;
        *head = (*head)->next;
        free(tmp);
    }
    *head=reverse(*head);
}
//addition
struct BigInteger add(struct BigInteger n1, struct BigInteger n2)
{
    struct BigInteger n3;
    n3.head = NULL;
    n3.sign = '+';
    n3.length = 0;

    if (n1.sign == '-' && n2.sign == '-') 
        n3.sign = '-';
    else if (n1.sign == '-')
     {
        n1.sign = '+';
        n3 = sub(n2, n1);
        n1.sign = '-';
        return n3;
    } 
    else if (n2.sign == '-') 
    {
        n2.sign = '+';
        n3 = sub(n1, n2);
        n2.sign = '-';
        return n3;
    }

    struct node* l1 = n1.head, * l2 = n2.head;
    int sum, carry = 0;

    while (l1 != NULL || l2 != NULL || carry != 0) {
        int d1 = (l1 != NULL) ? l1->data : 0;
        int d2 = (l2 != NULL) ? l2->data : 0;

        sum = d1 + d2 + carry;
        carry = sum / 10;
        insert_end(&n3, sum % 10);

        if (l1 != NULL) l1 = l1->next;
        if (l2 != NULL) l2 = l2->next;
    }
    return n3;
}

//subtract
struct BigInteger sub(struct BigInteger n1, struct BigInteger n2)
{
    struct BigInteger n3;
    n3.head = NULL;
    n3.sign = '+';
    n3.length = 0;
    if (n1.sign == '-' && n2.sign == '+') 
    {
        n1.sign = '+';
        n3 = add(n1, n2);
        n1.sign = '-';
        n3.sign = '-';
        return n3;
    }
    else if (n1.sign == '-' && n2.sign == '-') 
    {
        n2.sign = '+';
        n1.sign = '+';
        n3 = sub(n2, n1);
        n2.sign = '-';
        n1.sign = '-';
        return n3;
    }
    else if (compare(n1, n2)) 
    {
        struct node* temp = n1.head;
        n1.head = n2.head;
        n2.head = temp;
        n3.sign = '-';
    } 
    else if (n1.sign == '+' && n2.sign == '-') 
    {
        n2.sign = '+';
        n3 = add(n1, n2);
        n2.sign = '-';
        return n3;
    } 
    struct node* len1 = n1.head, * len2 = n2.head;
    int difference, borrow = 0;

    while (len1 != NULL || len2 != NULL) 
    {
        int d1 = (len1 != NULL) ? len1->data : 0;
        int d2 = (len2 != NULL) ? len2->data : 0;

        difference = d1 - d2 - borrow;

        if (difference < 0)
        {
            difference += 10;
            borrow = 1;
        } 
        else 
            borrow = 0;
        insert_end(&n3, difference);
        if (len1 != NULL) len1 = len1->next;
        if (len2 != NULL) len2 = len2->next;
    }
    trailing(n3.head);
    return n3;
}

//multiply
struct BigInteger mul(struct BigInteger n1, struct BigInteger n2)
{
    struct node* num1 = n1.head, * num2 = n2.head;
    struct BigInteger num3 = initialize("");  
    num3.length = 0;
    if (!num1 || !num2 )    return num3; 
    struct BigInteger temp, ans = initialize(""); 
    int carry = 0, product = 0, i = 0;
    while (num2 )
     {
        num1 = n1.head;
        carry = 0;
        temp = initialize("");
        for (int j = 0; j < i; j++) 
            insert_end(&temp, 0);
        while (num1)
        {
            product = (num1->data) * (num2->data) + carry;
            insert_end(&temp, product % 10);
            carry = product / 10;
            num1 = num1->next;
        }
        if (carry > 0) 
            insert_end(&temp, carry);
        ans = add(temp, ans);
        struct node* current = temp.head;
        free_linked(&temp);
        num2 = num2->next;
        i++;
    }
    if (n1.sign != n2.sign) 
        ans.sign = '-';
    return ans;
}

void displaylinked(struct node* head)
{
    if(!head)  return;
    displaylinked(head->next);
    printf("%d", head->data);
}

void display(struct BigInteger n)
{
    if(!(n.head))
    {
        printf("0");
        return;
    }
    if(n.sign == '-')
        printf("-");
    displaylinked(n.head);
}

void free_linked(struct BigInteger* n) 
{
    struct node* itr = n->head;
    while (itr != NULL)
    {
        struct node* temp = itr;
        itr = itr->next;
        free(temp);
    } 
    n->length = 0;
    n->head = NULL;
}
