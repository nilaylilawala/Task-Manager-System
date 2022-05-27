//Task Manager Program using Doubly Circular Linked List

#include <stdio.h>
#include <string.h>

//Initializing Circular Doubly Linked List
struct node
{
    struct node *prev;
    char data[20];
    struct node *next;
};

struct node *start = NULL, *ptr = NULL, *now = NULL, *now2 = NULL, *ptr2 = NULL;

//Function Declarations
void add(void);
struct node *close(struct node *);
void display(void);
void next(void);
void prev(void);
void first(void);
void last(void);
void specific(void);
void split(void);
void end_split(void);
void empty(void);

//Main Function
int main()
{
    int c;
    printf("\t\t\t------TASK MANAGER------\n\n");

    //do-while
    do
    {
        printf("1. Add New Program\n2. Close Program\n3. View Running Programs\n4. Switch to Next Program\n5. Switch to Previous Program\n");
        printf("6. Switch to First Program\n7. Switch to Last Program\n8. Switch to Specific Program\n9. Split Screen\n10. End Split Screen\n11. Exit\n\n");
        printf("-->Enter your choice: ");
        scanf("%d", &c);

        switch(c)
        {
        case 1:
            add();   //Adding program
            break;
        case 2:
            start = close(start);     //Closing program
            if(start == NULL && now != NULL)
                printf("\n\t\t---!All Programs are Closed!---\n");
            break;
        case 3:
            display();  //Traversing Programs
            break;
        case 4:
            next();    //Next Program
            break;
        case 5:
            prev();    //Previous Program
            break;
        case 6:
            first();   //First Program
            break;
        case 7:
            last();    //Last Program
            break;
        case 8:
            specific();   //Specific Program
            break;
        case 9:
            split();
            break;        //Split Screen
        case 10:
            end_split();    //End Split Screen
            break;
        case 11:
            exit(0);      //Exit
            break;
        default:
            printf("\n\t\t---!Please Choose Correct Option!---\n");
            break;
        }
        if(start != NULL)
        {
            if(now2 != NULL)
            {
                printf("\n\t-------------------------------------------------");
                printf("\n\t-->>Running... \n\t\tScreen 1 : \"%s\"\n\t\tScreen 2 : \"%s\"\n", now->data, now2->data);
                printf("\t-------------------------------------------------\n\n");
            }
            else
            {
                printf("\n\t---------------------");
                printf("\n\t-->>Running \"%s\"...\n", now->data);
                printf("\t---------------------\n\n");
            }

        }

    } while(c != 11);
    return 0;
}

void add()
{
    struct node *new_node;
    new_node = (struct node *)malloc(sizeof(struct node));  //dynamic memory allocation
    printf("\n->Enter Program Name: ");
    fflush(stdin);
    gets(new_node->data);
    if(start == NULL)   //For the first time entry
    {
        start = new_node;
        new_node->next = start;
        new_node->prev = NULL;
        now = start;
    }
    else
    {
        ptr = start;
        while(ptr->next != start)
            ptr = ptr->next;
        ptr->next = new_node;
        new_node->prev = ptr;
        new_node->next = start;
        start->prev = new_node;
        printf("\n\t\t->\"%s\" added Successfully!---\n\n", new_node->data);
    }
}

struct node *close(struct node *start)
{
    if(start == NULL)
    {
        empty();
        return NULL;
    }
    else
    {
        char name[20];
        printf("Enter the Program Name to be Deleted: ");
        fflush(stdin);
        gets(name);
        ptr = start;

        do
        {
            if(strcmpi(name, ptr->data) == 0)
                break;
            else if(ptr->next == start)
            {
                printf("\n\t\t---!No Result Found!---\n");
                return start;
            }
            else
                ptr = ptr->next;
            } while(ptr != start);

        if(start->prev == NULL || start->prev == start)
        {
            start = NULL;
            now = NULL;
            printf("\n\t\t->\"%s\" is deleted!\n", ptr->data);
            printf("\n\t\t--!All Programs are Closed!--\n\n");
            return start;
        }
        else
        {
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
            printf("\n\t\t->\"%s\" is deleted!\n", ptr->data);
            if(ptr == start)
                start = ptr->next;
        }
        if(now == ptr)
            now = now->next;
        if(now2 == ptr)
            now2 = now2->next;
        return start;
    }
}

void display()
{
    if(start == NULL)
        empty();
    else
    {
        int i = 1;
        ptr = start;
        printf("\n\t\t\t----Task List----\n");
        for(ptr = start; ptr->next != start; ptr = ptr->next)   //traversing with for loop
            printf("%d. %s\n", i++, ptr->data);
        printf("%d. %s\n\n", i, ptr->data);

    }
}

void next()
{
    if(start == NULL)
        empty();
    else
        now = now->next;
}

void prev()
{
    if(start == NULL)
        empty();
    else
        now = now->prev;
}

void first()
{
    if(start == NULL)
        empty();
    else
        now = start;
}

void last()
{
    if(start == NULL)
        empty();
    else
        now = start->prev;
}

void specific()
{
    if(start == NULL)
        empty();
    else
    {
        int c;
        char name[20];
        here:
        printf("\n->Select Program by \n1. Name\n2. Number\n");    //2 options for selection
        printf("->Choose Option: ");
        scanf("%d", &c);

        switch(c)
        {
        case 1:    //Search by name
            printf("->Enter the Program Name: ");
            fflush(stdin);
            gets(name);
            ptr = start;
            do
            {
                if(strcmpi(name, ptr->data) == 0)
                {
                    printf("\n\t\t->\"%s\" found!\n", name);
                    now = ptr;
                    break;
                }
                else if(ptr->next == start)
                {
                    printf("\n\t\t---!No Result Found!---\n");
                    break;
                }

                else
                    ptr = ptr->next;
            }while(ptr != start);
            break;
        case 2:    //Search by number
            here2:
            printf("->Enter the Program number: ");
            scanf("%d", &c);
            ptr = start;
            for(int i=1; i<c; i++)
            {
                ptr = ptr->next;
                if(ptr == start)
                {
                    printf("\n\t\t---!Invalid Program Number!---\n\n");
                    goto here2;
                }
            }
            now = ptr;
            break;
        default:
            printf("\n!\t---!Please Choose Correct Option!--\n");
            goto here;
        }
    }
}

void split()
{
    if(start == NULL)
        empty();
    else
    {
        int c;
        here3:
        display();
        printf("Enter the program number for Screen 2: ");
        scanf("%d", &c);
        ptr2 = start;
        for(int i=1; i<c; i++)
        {
            ptr2 = ptr2->next;
            if(ptr2 == start)
            {
                printf("\n\t\t---!Invalid Program Number!---\n\n");
                goto here3;
            }
        }
        now2 = ptr2;
    }
}

void end_split()
{
    if(start == NULL)
        empty();
    else
        now2 = NULL;
}

void empty()
{
    printf("\n\t\t---!No Program is Running in Background!---\n\n");
}
