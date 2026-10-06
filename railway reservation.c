#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINS 10

struct Train {
    int trainNo;
    char trainName[50];
    char source[30];
    char destination[30];
    int totalSeats;
    int availableSeats;
};

struct Passenger {
    int pnr;
    char name[50];
    int age;
    char gender;
    int trainNo;
    int seatNo;
    char status[20];

    struct Passenger *next;
};

// WAITING QUEUE NODE

struct QueueNode {
    struct Passenger passenger;
    struct QueueNode *next;
};

//GLOBAL VARIABLES

struct Train trains[MAX_TRAINS];
int trainCount = 0;

struct Passenger *confirmedHead = NULL;

struct QueueNode *front = NULL;
struct QueueNode *rear = NULL;

int nextPNR = 1001;

//FIND TRAIN
int findTrain(int trainNo)
{
    int i;

    for (i = 0; i < trainCount; i++)
    {
        if (trains[i].trainNo == trainNo)
        {
            return i;
        }
    }

    return -1;
}

//ADD TRAIN

void addTrain()
{
    if (trainCount >= MAX_TRAINS)
    {
        printf("\nMaximum train limit reached.\n");
        return;
    }

    printf("\nEnter Train Number: ");
    scanf("%d", &trains[trainCount].trainNo);

    printf("Enter Train Name: ");
    scanf(" %[^\n]", trains[trainCount].trainName);

    printf("Enter Source: ");
    scanf(" %[^\n]", trains[trainCount].source);

    printf("Enter Destination: ");
    scanf(" %[^\n]", trains[trainCount].destination);

    printf("Enter Total Seats: ");
    scanf("%d", &trains[trainCount].totalSeats);

    trains[trainCount].availableSeats =trains[trainCount].totalSeats;

    trainCount++;

    printf("\nTrain added successfully.\n");
}

//DISPLAY TRAINS

void displayTrains()
{
    int i;

    if (trainCount == 0)
    {
        printf("\nNo trains available.\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-15s %-12s %-15s\n","Train No", "Train Name", "Source","Destination", "Total Seats", "Available");

    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < trainCount; i++)
    {
        printf("%-10d %-20s %-15s %-15s %-12d %-15d\n",trains[i].trainNo,trains[i].trainName,trains[i].source,trains[i].destination,trains[i].totalSeats,trains[i].availableSeats);
    }
}

//SEARCH TRAIN
void searchTrain()
{
    int trainNo;
    int index;

    printf("\nEnter Train Number to search: ");
    scanf("%d", &trainNo);

    index = findTrain(trainNo);

    if (index == -1)
    {
        printf("\nTrain not found.\n");
        return;
    }

    printf("\nTrain Found\n");
    printf("Train Number : %d\n", trains[index].trainNo);
    printf("Train Name   : %s\n", trains[index].trainName);
    printf("Source       : %s\n", trains[index].source);
    printf("Destination  : %s\n", trains[index].destination);
    printf("Total Seats  : %d\n", trains[index].totalSeats);
    printf("Available    : %d\n", trains[index].availableSeats);
}

//ADD CONFIRMED PASSENGER BY LINKED LIST
void addConfirmedPassenger(struct Passenger p)
{
    struct Passenger *newNode;
    struct Passenger *temp;

    newNode = (struct Passenger *)malloc(sizeof(struct Passenger));

    *newNode = p;
    newNode->next = NULL;

    if (confirmedHead == NULL)
    {
        confirmedHead = newNode;
    }
    else
    {
        temp = confirmedHead;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

// ADD TO WAITING QUEUE

void enqueue(struct Passenger p)
{
    struct QueueNode *newNode;

    newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));

    newNode->passenger = p;
    newNode->next = NULL;

    if (rear == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

// REMOVE FROM WAITING QUEUE

struct Passenger dequeue()
{
    struct Passenger p;
    struct QueueNode *temp;

    p.pnr = -1;

    if (front == NULL)
    {
        return p;
    }

    temp = front;
    p = temp->passenger;

    front = front->next;

    if (front == NULL)
    {
        rear = NULL;
    }

    free(temp);

    return p;
}

// BOOK TICKET

void bookTicket()
{
    struct Passenger p;
    int trainNo;
    int index;

    printf("\nEnter Train Number: ");
    scanf("%d", &trainNo);

    index = findTrain(trainNo);

    if (index == -1)
    {
        printf("\nTrain not found.\n");
        return;
    }

    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Gender (M/F/O): ");
    scanf(" %c", &p.gender);

    p.pnr = nextPNR++;
    p.trainNo = trainNo;

    if (trains[index].availableSeats > 0)
    {
        p.seatNo =trains[index].totalSeats -trains[index].availableSeats + 1;

        strcpy(p.status, "CONFIRMED");

        trains[index].availableSeats--;

        addConfirmedPassenger(p);

        printf("\nTicket booked successfully!\n");
        printf("PNR        : %d\n", p.pnr);
        printf("Passenger  : %s\n", p.name);
        printf("Train No   : %d\n", p.trainNo);
        printf("Seat No    : %d\n", p.seatNo);
        printf("Status     : CONFIRMED\n");
    }
    else
    {
        p.seatNo = -1;
        strcpy(p.status, "WAITING");

        enqueue(p);

        printf("\nNo confirmed seats available.\n");
        printf("Passenger added to waiting list.\n");
        printf("PNR        : %d\n", p.pnr);
        printf("Passenger  : %s\n", p.name);
        printf("Status     : WAITING\n");
    }
}

// FIND PASSENGER BY PNR

struct Passenger *findPassenger(int pnr)
{
    struct Passenger *temp;

    temp = confirmedHead;

    while (temp != NULL)
    {
        if (temp->pnr == pnr)
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}

// CANCEL TICKET

void cancelTicket()
{
    int pnr;
    struct Passenger *temp;
    struct Passenger *prev;
    int index;

    printf("\nEnter PNR to cancel: ");
    scanf("%d", &pnr);

    temp = confirmedHead;
    prev = NULL;

    while (temp != NULL && temp->pnr != pnr)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("\nConfirmed ticket not found.\n");
        return;
    }

    index = findTrain(temp->trainNo);

    printf("\nTicket cancelled successfully.\n");
    printf("PNR       : %d\n", temp->pnr);
    printf("Passenger : %s\n", temp->name);

    // Remove passenger from linked list

    if (prev == NULL)
    {
        confirmedHead = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }

    free(temp);

    // Check waiting queue

    if (front != NULL)
    {
        struct Passenger waitingPassenger;

        waitingPassenger = dequeue();

        waitingPassenger.seatNo =
            trains[index].totalSeats -
            trains[index].availableSeats + 1;

        strcpy(waitingPassenger.status, "CONFIRMED");

        addConfirmedPassenger(waitingPassenger);

        printf("\nWaiting passenger promoted!\n");
        printf("PNR       : %d\n",waitingPassenger.pnr);
        printf("Passenger : %s\n",waitingPassenger.name);
        printf("Seat No   : %d\n",waitingPassenger.seatNo);
        printf("Status    : CONFIRMED\n");
    }
    else
    {
        trains[index].availableSeats++;
    }
}

// SEARCH PNR

void searchPNR()
{
    int pnr;
    struct Passenger *temp;

    printf("\nEnter PNR: ");
    scanf("%d", &pnr);

    temp = findPassenger(pnr);

    if (temp != NULL)
    {
        printf("\nPNR STATUS\n");
        printf("-------------------------\n");
        printf("PNR        : %d\n", temp->pnr);
        printf("Name       : %s\n", temp->name);
        printf("Age        : %d\n", temp->age);
        printf("Gender     : %c\n", temp->gender);
        printf("Train No   : %d\n", temp->trainNo);
        printf("Seat No    : %d\n", temp->seatNo);
        printf("Status     : %s\n", temp->status);

        return;
    }

    //Search waiting queue

    {
        struct QueueNode *q;

        q = front;

        while (q != NULL)
        {
            if (q->passenger.pnr == pnr)
            {
                printf("\nPNR STATUS\n");
                printf("-------------------------\n");
                printf("PNR        : %d\n", q->passenger.pnr);
                printf("Name       : %s\n",q->passenger.name);
                printf("Age        : %d\n",q->passenger.age);
                printf("Gender     : %c\n",q->passenger.gender);
                printf("Train No   : %d\n",q->passenger.trainNo);
                printf("Seat No    : Not Assigned\n");
                printf("Status     : WAITING\n");

                return;
            }

            q = q->next;
        }
    }

    printf("\nPNR not found.\n");
}

// DISPLAY CONFIRMED

void displayConfirmed()
{
    struct Passenger *temp;

    if (confirmedHead == NULL)
    {
        printf("\nNo confirmed reservations.\n");
        return;
    }

    printf("\nCONFIRMED RESERVATIONS\n");

    printf("\n%-8s %-20s %-8s %-8s %-10s %-10s\n","PNR", "Name", "Age", "Train", "Seat", "Status");

    printf("----------------------------------------------------------------\n");

    temp = confirmedHead;

    while (temp != NULL)
    {
        printf("%-8d %-20s %-8d %-8d %-10d %-10s\n",temp->pnr,temp->name,temp->age,temp->trainNo,temp->seatNo,temp->status);

        temp = temp->next;
    }
}

// DISPLAY WAITING LIST

void displayWaitingList()
{
    struct QueueNode *temp;

    if (front == NULL)
    {
        printf("\nWaiting list is empty.\n");
        return;
    }

    printf("\nWAITING LIST\n");

    printf("\n%-8s %-20s %-8s %-10s %-10s\n","PNR", "Name", "Age", "Train", "Status");

    printf("---------------------------------------------------------\n");

    temp = front;

    while (temp != NULL)
    {
        printf("%-8d %-20s %-8d %-10d %-10s\n",temp->passenger.pnr,temp->passenger.name,temp->passenger.age,temp->passenger.trainNo,temp->passenger.status);

        temp = temp->next;
    }
}

// SORT TRAINS BY BUBBLE SORT

void sortTrains()
{
    int i, j;
    struct Train temp;

    for (i = 0; i < trainCount - 1; i++)
    {
        for (j = 0; j < trainCount - i - 1; j++)
        {
            if (trains[j].trainNo >
                trains[j + 1].trainNo)
            {
                temp = trains[j];
                trains[j] = trains[j + 1];
                trains[j + 1] = temp;
            }
        }
    }

    printf("\nTrains sorted by train number.\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n");
        printf(" RAILWAY RESERVATION SYSTEM\n");
        printf("\n");

        printf("1. Add Train\n");
        printf("2. Display All Trains\n");
        printf("3. Search Train\n");
        printf("4. Book Ticket\n");
        printf("5. Cancel Ticket\n");
        printf("6. Check PNR Status\n");
        printf("7. Display Confirmed Reservations\n");
        printf("8. Display Waiting List\n");
        printf("9. Sort Trains\n");
        printf("10. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addTrain();
                break;

            case 2:
                displayTrains();
                break;

            case 3:
                searchTrain();
                break;

            case 4:
                bookTicket();
                break;

            case 5:
                cancelTicket();
                break;

            case 6:
                searchPNR();
                break;

            case 7:
                displayConfirmed();
                break;

            case 8:
                displayWaitingList();
                break;

            case 9:
                sortTrains();
                break;

            case 10:
                printf("\nThank you for using Railway Reservation System.\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 10);

    return 0;
}
