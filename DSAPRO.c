#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
    char foodName[50];
    int qty;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};

struct node *head_c = NULL,*newnode,*tail_c = NULL;
struct node *head_a = NULL, *tail_a = NULL;
struct node *head_s;

void customermenu() {
    printf("\n\t1. Place your order\n");
    printf("\t2. View your ordered items\n");
    printf("\t3. Delete an item from the order\n");
    printf("\t4. Display final bill amount\n");
    printf("\t5. Back To Main Menu \n\n");
    printf("\tEnter Your Choice : ");
}

void adminmenu() {
    printf("\n\t1. Display total items to delivered\n");
    printf("\t2. Add new item in the order sequence\n");
    printf("\t3. Delete items from the order sequence\n");
    printf("\t4. Display Food Menu\n");
    printf("\t5. Back To Main Menu \n\n");
    printf("\tEnter Your Choice : ");
}

struct node* createAd(struct node *head,int data, char foodName[50], float price)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->price = price;
    newnode-> qty = 0;
    strcpy(newnode->foodName,foodName);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;

    if(temp==NULL)
        head_a = tail_a = newnode;
    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newnode;
        newnode->prev =tail_a;
        tail_a = newnode;
    }

    return head_a;
}

struct node* createCustomer(struct node *head,int data,int qty)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    struct node *temp1 = head_a;
    int flag = 0;
    while(temp1!=NULL) {
        if(temp1->data==data) {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if(flag==1) {
        newnode->data = data;
        newnode->price = qty*(temp1->price);
        newnode-> qty = qty;
        strcpy(newnode->foodName,temp1->foodName);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if(temp==NULL)
            head_c = tail_c = newnode;
        else {
            while(temp->next!=NULL)
                temp=temp->next;

            temp->next=newnode;
            newnode->prev = tail_c;
            tail_c = newnode;
        }
    }
    else {
        printf("\tThis item is not present in the menu!\n");
    }
    return head_c;
}

void displayList(struct node *head) {
    struct node *temp1 = head;
    if(temp1==NULL) printf("\n\tList is empty!!\n\n");
    else {
        printf("\n");
        while(temp1!=NULL) {
            if(temp1->qty==0)
                printf("\t%d\t%s\t%0.2f\n",temp1->data,temp1->foodName,temp1->price);
            else {
                printf("\t%d\t%s\t%d\t%0.2f\n",temp1->data,temp1->foodName,temp1->qty,temp1->price);
            }

            temp1 = temp1->next;
        }
        printf("\n");
    }

}

struct node* totalsale(int data,int qty)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = head_a;
    while(temp1->data!=data) {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = qty*(temp1->price);
    newnode-> qty = qty;
    strcpy(newnode->foodName,temp1->foodName);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if(temp==NULL)
        head_s = newnode;
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                flag = 1;
                break;
            }
            temp=temp->next;
        }

        if(flag==1)
        {
            temp->qty += newnode-> qty;
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
        }
    }

    return head_s;
}

void calculatetotsales()
{
    struct node *temp = head_c;
    while(temp!=NULL)
    {
        head_s = totalsale(temp->data, temp->qty);
        temp=temp->next;
    }
}

struct node* delete(int data,struct node* head, struct node* tail)
{
    if(head==NULL)
    {
        printf("\tList is empty\n");
    }
    else
    {
        struct node* temp;
        if(data==head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if(data==tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while(data!=temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}

int deleteAdmin()
{
    printf("\n\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=head_a;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            head_a = delete(num, head_a, tail_a);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

int deleteCustomer()
{
    printf("\n\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=head_c;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            head_c = delete(num, head_c, tail_c);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

void displayBill()
{
    displayList(head_c);
    struct node *temp = head_c;
    float total_price = 0;
    while (temp!=NULL)
    {
        total_price +=temp->price;
        temp = temp->next;
    }

    printf("\tTotal amount : %0.02f\n",total_price);
}

struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void admin()
{
    printf("----------------------------------------------   \n");
    printf("\t\t\tADMIN SECTION\n");
    printf("----------------------------------------------\n");
    while(1)
    {
        adminmenu();

        int opt; scanf("%d",&opt);

        if(opt==5) break;
        switch (opt)
        {
            case 1:
                displayList(head_s);
                break;
            case 2:
            
                printf("\n\tEnter serial no. of the food item: ");
                int num,flag = 0;
                char name[50];
                float price;
                scanf("%d",&num);
                struct node *temp = head_a;

                while(temp!=NULL) {
                    if(temp->data==num) {
                        printf("\n\tFood item with given sr. number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(flag==1) break;
                printf("\n\tEnter food item Name: ");
                scanf("%s",name);
                printf("\n\tEnter Price: ");
                scanf("%f",&price);
                head_a = createAd(head_a, num, name, price);
                printf("\n\tNew food item is added to the list!\n\n");
                break;
            
            case 3:
                if(deleteAdmin()) {
                    printf("\n\t<== Updated list of food items menu ==>\n");
                    displayList(head_a);
                }
                else
                    printf("\n\tFood item with given serial number doesn't exist!\n\n");

                break;
            case 4:
                printf("\n\t :: MENU :: \n");
                displayList(head_a);
                break;

            default:
                printf("\n\tPLease choose valid option!\n");
                break;
        }
    }
}

void customer() {
    int flag=0,j=1;
    char ch;
    printf("----------------------------------------------\n");
    printf("\t\t    < CUSTOMER SECTION >\n");
    printf("----------------------------------------------\n");
    
    while(1) {
        customermenu();

        int opt;
        scanf("%d",&opt);

        if(opt==5) break;

        switch (opt) {
            case 1:
                displayList(head_a);
                printf("\n\tEnter number corresponding to the item you want to order: ");
                int n;
                scanf("%d",&n);
                printf("\n\tEnter quantity: ");
                int quantity;
                scanf("%d",&quantity);
                head_c = createCustomer(head_c, n, quantity);
                break;
            
            case 2:
                printf("\n\t --> List of ordered items <-- \n");
                displayList(head_c);
                break;
                
            case 3:
                if(deleteCustomer()) {
                    printf("\n\t || Updated list of your ordered food items || \n");
                    displayList(head_c);
                }
                else
                    printf("\n\tFood item with given sr. number doesn't exist!!\n");
                break;
                
            case 4:
                calculatetotsales();
                printf("\n\tFINAL PAYMENT\n");
                displayBill();
                head_c = deleteList(head_c);
                printf("\n\tPress any key to return : \n");
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;

            default:
                printf("\n\tPlease choose valid option\n");
                break;
        }
        if(flag==1)
            break;
    }
}

void mainnenu()
{
    printf("1.CUSTOMER SECTION \n");
    printf("2.ADMIN SECTION \n");
    printf("3.Exit \n\n");
    printf("Enter Your Choice : ");
}

int main()
{
    printf("\n**************************************************************************\n");
    printf("                  RESTAURANT MANAGEMENT SYSTEM\n");
    printf("****************************************************************************\n\n\n");
    
    head_a = createAd(head_a,1,"Hot and Sour Soup",119);
    head_a = createAd(head_a,2,"Manchow Soup",110);
    head_a = createAd(head_a,3,"Manchurian Noodles",80);
    head_a = createAd(head_a,4,"Fried Rice",100);
    head_a = createAd(head_a,5,"Hakka Noodles",120);

    while(1)
    {
        mainnenu();
        int choice;
        scanf("%d",&choice);

        if(choice==3)
        {
            printf("\n\n\t\t\t\t\t\t\t*******   Thank you!!   *******\n");
            break;
        }

        switch (choice)
        {
            case 1:
                customer();
                break;
            case 2:
                admin();
                break;
            case 3:
                break;

            default:
                printf("\n\tPLease choose valid option\n");
                break;
        }
    }
}