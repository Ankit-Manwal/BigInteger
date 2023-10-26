#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"


int length(struct node* head) {
   int count = 0;
    while (head) {
        head = head->next;
        count++;
    }
    return count;
}

struct node* insert_node(struct node* head, int val)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = head;
    return temp;
}

void insert_big_end(struct BigInteger* n, int val) 
{
    struct node* tmp = (struct node*)malloc(sizeof(struct node));

    tmp->data = val;
    tmp->next = NULL;
    n->length = (n->length) + 1;
    if (!(n->head))
    {
        n->head = tmp;
        return;
    }
    struct node* itr = n->head;
    while (itr->next != NULL) 
        itr = itr->next;
    itr->next = tmp;
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
    if (n2.length > n1.length) 
        return 1;
    else if (n2.length != n1.length)
        return 0;

    int tempR = 0;
    n1.head = reverse(n1.head);
    n2.head = reverse(n2.head);
    struct node* head1 = n1.head, * head2 = n2.head;
    for( head1, head2  ;head1 && head2;  head1 = head1->next,  head2 = head2->next )
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
    }
    n1.head = reverse(n1.head);
    n2.head = reverse(n2.head);
    return tempR;   
}

//initialize
struct BigInteger initialize(char* s)
{
    int index;
    struct BigInteger temp;
    temp.head = NULL;
    if(s[0] == '-') 
         temp.sign = '-';  
    else   
        temp.sign = '+';

    if(temp.sign == '-')   
       index = 1;   
    else    
       index = 0;
       
    while(s[index] != '\0')
    {    
        temp.head = insert_node(temp.head, s[index] - '0'); 
        index++;
    }
    temp.length = length(temp.head);
    return temp;
}

void trailing(struct node ** head)
{  
    *head=reverse(*head);
    while (*head  && (*head)->data == 0)
    {
        struct node* tmp = *head;
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

    struct node* temp1 = n1.head, * temp2 = n2.head;
    int sum, carry = 0;

    while (temp1 != NULL || temp2 != NULL || carry != 0) 
    {
        int x = (temp1 != NULL) ? temp1->data : 0;
        int y = (temp2 != NULL) ? temp2->data : 0;

        sum = x + y + carry;
        carry = sum / 10;
        insert_big_end(&n3, sum % 10);

        if (temp1 != NULL) 
              temp1 = temp1->next;
        if (temp2 != NULL)
              temp2 = temp2->next;
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
    else if (n1.sign == '+' && n2.sign == '-') 
    {
        n2.sign = '+';
        n3 = add(n1, n2);
        n2.sign = '-';
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
    struct node* temp1 = n1.head, * temp2 = n2.head;
    int difference, borrow = 0;

    while (temp1  || temp2 ) 
    {
        int x = (temp1 != NULL) ? temp1->data : 0;
        int y = (temp2 != NULL) ? temp2->data : 0;

        difference = x - y - borrow;

        if (difference < 0)
        {
            difference += 10;
            borrow = 1;
        } 
        else 
            borrow = 0;

        insert_big_end(&n3, difference);
        if (temp1 != NULL) 
              temp1 = temp1->next;
        if (temp2 != NULL) 
              temp2 = temp2->next;
    }
    trailing(&n3.head);
    return n3;
}

//multiply
struct BigInteger mul(struct BigInteger n1, struct BigInteger n2)
{
    struct node* num1 = n1.head, * num2 = n2.head;
    struct BigInteger n3 = initialize("");  
    n3.length = 0;
    if (!num1 || !num2 )   
          return n3; 
    struct BigInteger temp, ans = initialize(""); 
    int carry = 0, prod = 0, i = 0;
    while (num2 )
     {
        num1 = n1.head;
        carry = 0;
        temp = initialize("");
        for (int j = 0; j < i; j++) 
            insert_big_end(&temp, 0);
        while (num1)
        {
            prod = (num1->data) * (num2->data) + carry;
            insert_big_end(&temp, prod % 10);
            carry = prod / 10;
            num1 = num1->next;
        }
        if (carry > 0) 
            insert_big_end(&temp, carry);
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

//division
struct BigInteger div1(struct BigInteger n1, struct BigInteger n2)
{
  struct BigInteger n3 = initialize("0");
  int flag = 0;
  n3.length = 0;
  n3.sign = '+';
  char sign = '+';
  if (n2.length == 1 && n2.head->data == 0)
  {
    printf("Error\n");
    return n3;
  }
  if (n1.sign != n2.sign)
       sign = '-';
  char s1 = n1.sign;
  char s2 = n2.sign;
  n1.sign = '+';
  n2.sign = '+';
  struct BigInteger temp = add(n2, initialize("0"));
  while (compare(n1, temp) >= 0) 
  {
    temp = add(temp, n2);
    n3 = add(n3, initialize("1"));
    flag = 1;
  }
  if (flag!=0)
     n3.sign = sign;
  n1.sign = s1;
  n2.sign = s2;
  return n3;
}

void displaylinked(struct node* head)
{
    if(!head)  
        return;
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
