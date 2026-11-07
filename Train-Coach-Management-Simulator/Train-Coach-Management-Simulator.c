
/*
    ==========================================================
              TRAIN COACH MANAGEMENT SIMULATOR
    ==========================================================

    Language       : C
    Data Structure : Doubly Linked List

    PROJECT DESCRIPTION:
    This project manages train coaches using a Doubly Linked
    List. Each coach stores its coach number, coach type,
    and passenger capacity.

    FEATURES:
    1. Add a coach at the end.
    2. Insert a coach at a specific position.
    3. Delete a coach using its number.
    4. Search for a coach.
    5. Display coaches in forward direction.
    6. Display coaches in backward direction.
    7. Calculate total passenger capacity.
    8. Count total coaches.
    9. Exit the program.

    ==========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>


// ==========================================================
// STEP 1: DEFINE THE COACH NODE
// ==========================================================

struct Coach
{
    int coachNo;
    char type[30];
    int capacity;

    // Pointers connecting previous and next coaches.
    struct Coach *prev;
    struct Coach *next;
};


// ==========================================================
// STEP 2: DECLARE HEAD AND TAIL POINTERS
// ==========================================================

// head points to the first coach.
// tail points to the last coach.

struct Coach *head = NULL;
struct Coach *tail = NULL;


// ==========================================================
// STEP 3: SAFE INTEGER INPUT FUNCTION
// ==========================================================

/*
    Reads an integer safely.

    Returns:
    1 = Valid integer received.
    0 = End of input reached.
*/

int readInteger(const char *message, int *value)
{
    char input[100];
    char *endPointer;
    long number;

    while (1)
    {
        printf("%s", message);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            return 0;
        }

        errno = 0;
        number = strtol(input, &endPointer, 10);

        // Skip spaces after the entered number.
        while (isspace((unsigned char)*endPointer))
        {
            endPointer++;
        }

        // Check whether the input is a valid integer.
        if (endPointer == input ||
            *endPointer != '\0' ||
            errno == ERANGE ||
            number < INT_MIN ||
            number > INT_MAX)
        {
            printf("Invalid input! Please enter a valid integer.\n");
            continue;
        }

        *value = (int)number;
        return 1;
    }
}


// ==========================================================
// STEP 4: SAFE TEXT INPUT FUNCTION
// ==========================================================

/*
    Reads text safely and prevents buffer overflow.
*/

int readText(const char *message, char text[], int size)
{
    while (1)
    {
        printf("%s", message);

        if (fgets(text, size, stdin) == NULL)
        {
            return 0;
        }

        // Check whether the complete input was read.
        if (strchr(text, '\n') == NULL)
        {
            int ch;

            // Clear remaining characters from the input line.
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            printf("Input is too long! Please try again.\n");
            continue;
        }

        // Remove the newline character.
        text[strcspn(text, "\n")] = '\0';

        if (strlen(text) == 0)
        {
            printf("Input cannot be empty!\n");
            continue;
        }

        return 1;
    }
}


// ==========================================================
// STEP 5: VALIDATE COACH TYPE
// ==========================================================

/*
    Only three coach types are accepted:

    AC
    Sleeper
    General
*/

int isValidCoachType(char type[])
{
    if (strcmp(type, "AC") == 0 ||
        strcmp(type, "Sleeper") == 0 ||
        strcmp(type, "General") == 0)
    {
        return 1;
    }

    return 0;
}


// ==========================================================
// STEP 6: CREATE A NEW COACH
// ==========================================================

/*
    malloc() dynamically allocates memory for a new coach.

    Initially, both prev and next pointers are NULL.
*/

struct Coach* createCoach(int no, char type[], int capacity)
{
    struct Coach *newCoach;

    newCoach = (struct Coach*)malloc(sizeof(struct Coach));

    if (newCoach == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newCoach->coachNo = no;
    strcpy(newCoach->type, type);
    newCoach->capacity = capacity;

    newCoach->prev = NULL;
    newCoach->next = NULL;

    return newCoach;
}


// ==========================================================
// STEP 7: CHECK WHETHER COACH NUMBER ALREADY EXISTS
// ==========================================================

/*
    Coach numbers must be unique.

    Returns:
    1 = Coach exists.
    0 = Coach does not exist.
*/

int coachExists(int no)
{
    struct Coach *temp = head;

    while (temp != NULL)
    {
        if (temp->coachNo == no)
        {
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}


// ==========================================================
// STEP 8: COUNT TOTAL COACH NODES
// ==========================================================

int countCoachNodes()
{
    int count = 0;
    struct Coach *temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}


// ==========================================================
// STEP 9: ADD COACH AT THE END
// ==========================================================

/*
    If the train is empty:
        head and tail point to the new coach.

    Otherwise:
        Connect the new coach after tail.
        Update the tail pointer.
*/

void addCoach()
{
    int no, capacity;
    char type[30];

    printf("\n========== ADD NEW COACH ==========\n");

    if (!readInteger("Enter Coach Number: ", &no))
        return;

    if (no <= 0)
    {
        printf("Coach number must be positive!\n");
        return;
    }

    if (coachExists(no))
    {
        printf("Coach number already exists!\n");
        return;
    }

    if (!readText("Enter Coach Type (AC/Sleeper/General): ",
                  type, sizeof(type)))
        return;

    if (!isValidCoachType(type))
    {
        printf("Invalid coach type!\n");
        return;
    }

    if (!readInteger("Enter Passenger Capacity: ", &capacity))
        return;

    if (capacity <= 0)
    {
        printf("Capacity must be greater than zero!\n");
        return;
    }

    struct Coach *newCoach = createCoach(no, type, capacity);

    if (newCoach == NULL)
        return;

    // Case 1: Train is empty.
    if (head == NULL)
    {
        head = newCoach;
        tail = newCoach;
    }
    else
    {
        // Connect new coach after the last coach.
        tail->next = newCoach;
        newCoach->prev = tail;

        // Update tail to the new last coach.
        tail = newCoach;
    }

    printf("\nCoach added successfully!\n");
}


// ==========================================================
// STEP 10: INSERT COACH AT A SPECIFIC POSITION
// ==========================================================

/*
    Position starts from 1.

    Example:

    Before:
    101 <-> 103

    Insert 102 at position 2.

    After:
    101 <-> 102 <-> 103
*/

void insertCoach()
{
    int no, capacity, position;
    char type[30];

    printf("\n========== INSERT COACH ==========\n");

    if (!readInteger("Enter Coach Number: ", &no))
        return;

    if (no <= 0)
    {
        printf("Coach number must be positive!\n");
        return;
    }

    if (coachExists(no))
    {
        printf("Coach number already exists!\n");
        return;
    }

    if (!readText("Enter Coach Type (AC/Sleeper/General): ",
                  type, sizeof(type)))
        return;

    if (!isValidCoachType(type))
    {
        printf("Invalid coach type!\n");
        return;
    }

    if (!readInteger("Enter Passenger Capacity: ", &capacity))
        return;

    if (capacity <= 0)
    {
        printf("Invalid capacity!\n");
        return;
    }

    if (!readInteger("Enter Position: ", &position))
        return;

    // Valid positions are from 1 to total coaches + 1.
    if (position < 1 || position > countCoachNodes() + 1)
    {
        printf("Invalid position!\n");
        return;
    }

    struct Coach *newCoach = createCoach(no, type, capacity);

    if (newCoach == NULL)
        return;

    // Case 1: Insert at the beginning.
    if (position == 1)
    {
        newCoach->next = head;

        if (head != NULL)
        {
            head->prev = newCoach;
        }
        else
        {
            // Train was empty.
            tail = newCoach;
        }

        head = newCoach;
    }
    else
    {
        struct Coach *temp = head;
        int currentPosition = 1;

        // Move to the coach just before the required position.
        while (currentPosition < position - 1)
        {
            temp = temp->next;
            currentPosition++;
        }

        // Connect new coach with its neighbours.
        newCoach->next = temp->next;
        newCoach->prev = temp;

        if (temp->next != NULL)
        {
            temp->next->prev = newCoach;
        }
        else
        {
            // New coach becomes the last coach.
            tail = newCoach;
        }

        temp->next = newCoach;
    }

    printf("\nCoach inserted successfully!\n");
}


// ==========================================================
// STEP 11: DELETE COACH BY COACH NUMBER
// ==========================================================

/*
    First search for the required coach.

    Then connect its previous and next coaches.

    Finally, free() releases its memory.
*/

void deleteCoach()
{
    int no;

    printf("\n========== DELETE COACH ==========\n");

    if (!readInteger("Enter Coach Number to Delete: ", &no))
        return;

    if (no <= 0)
    {
        printf("Coach number must be positive!\n");
        return;
    }

    struct Coach *temp = head;

    // Search for the coach.
    while (temp != NULL && temp->coachNo != no)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Coach not found!\n");
        return;
    }

    // Update the previous coach's next pointer.
    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    else
    {
        // Deleted coach was the first coach.
        head = temp->next;
    }

    // Update the next coach's previous pointer.
    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }
    else
    {
        // Deleted coach was the last coach.
        tail = temp->prev;
    }

    free(temp);

    printf("Coach deleted successfully!\n");
}


// ==========================================================
// STEP 12: SEARCH FOR A COACH
// ==========================================================

void searchCoach()
{
    int no;

    printf("\n========== SEARCH COACH ==========\n");

    if (!readInteger("Enter Coach Number to Search: ", &no))
        return;

    if (no <= 0)
    {
        printf("Coach number must be positive!\n");
        return;
    }

    struct Coach *temp = head;

    while (temp != NULL)
    {
        if (temp->coachNo == no)
        {
            printf("\nCoach Found!\n");

            printf("Coach Number : %d\n", temp->coachNo);
            printf("Coach Type   : %s\n", temp->type);
            printf("Capacity     : %d\n", temp->capacity);

            return;
        }

        temp = temp->next;
    }

    printf("Coach not found!\n");
}


// ==========================================================
// STEP 13: DISPLAY TRAIN IN FORWARD DIRECTION
// ==========================================================

/*
    Start from head and move using next pointer.

    This displays coaches from first to last.
*/

void displayForward()
{
    struct Coach *temp = head;

    if (head == NULL)
    {
        printf("\nTrain is empty!\n");
        return;
    }

    printf("\n========== TRAIN COACHES ==========\n");

    printf("%-15s %-15s %-15s\n",
           "Coach Number", "Type", "Capacity");

    printf("---------------------------------------------\n");

    while (temp != NULL)
    {
        printf("%-15d %-15s %-15d\n",
               temp->coachNo,
               temp->type,
               temp->capacity);

        temp = temp->next;
    }

    printf("---------------------------------------------\n");
}


// ==========================================================
// STEP 14: DISPLAY TRAIN IN BACKWARD DIRECTION
// ==========================================================

/*
    Start from tail and move using prev pointer.

    This displays coaches from last to first.
*/

void displayBackward()
{
    struct Coach *temp = tail;

    if (tail == NULL)
    {
        printf("\nTrain is empty!\n");
        return;
    }

    printf("\n========== REVERSE TRAIN ORDER ==========\n");

    while (temp != NULL)
    {
        printf("Coach Number: %d | Type: %s | Capacity: %d\n",
               temp->coachNo,
               temp->type,
               temp->capacity);

        temp = temp->prev;
    }
}


// ==========================================================
// STEP 15: CALCULATE TOTAL PASSENGER CAPACITY
// ==========================================================

void totalCapacity()
{
    int total = 0;

    struct Coach *temp = head;

    while (temp != NULL)
    {
        total += temp->capacity;
        temp = temp->next;
    }

    printf("\nTotal Passenger Capacity: %d\n", total);
}


// ==========================================================
// STEP 16: DISPLAY TOTAL NUMBER OF COACHES
// ==========================================================

/*
    Reuse countCoachNodes() instead of repeating
    the linked-list traversal.
*/

void countCoaches()
{
    printf("\nTotal Number of Coaches: %d\n",
           countCoachNodes());
}


// ==========================================================
// STEP 17: FREE ALL ALLOCATED MEMORY
// ==========================================================

/*
    Release memory occupied by every coach.

    Save the next coach's address before freeing
    the current coach.
*/

void freeTrain()
{
    struct Coach *temp = head;

    while (temp != NULL)
    {
        struct Coach *nextCoach = temp->next;

        free(temp);

        temp = nextCoach;
    }

    // Reset both pointers.
    head = NULL;
    tail = NULL;
}


// ==========================================================
// STEP 18: MAIN FUNCTION
// ==========================================================

int main()
{
    int choice;

    do
    {
        printf("\n\n");
        printf("============================================\n");
        printf("       TRAIN COACH MANAGEMENT SYSTEM        \n");
        printf("============================================\n");

        printf("1. Add Coach\n");
        printf("2. Insert Coach at Position\n");
        printf("3. Delete Coach\n");
        printf("4. Search Coach\n");
        printf("5. Display Train (Forward)\n");
        printf("6. Display Train (Backward)\n");
        printf("7. Total Passenger Capacity\n");
        printf("8. Count Total Coaches\n");
        printf("9. Exit\n");

        printf("============================================\n");

        if (!readInteger("Enter Your Choice: ", &choice))
        {
            printf("\nInput ended. Closing the program...\n");
            break;
        }

        switch (choice)
        {
            case 1:
                addCoach();
                break;

            case 2:
                insertCoach();
                break;

            case 3:
                deleteCoach();
                break;

            case 4:
                searchCoach();
                break;

            case 5:
                displayForward();
                break;

            case 6:
                displayBackward();
                break;

            case 7:
                totalCapacity();
                break;

            case 8:
                countCoaches();
                break;

            case 9:
                printf("\nThank you for using Train Coach Management System!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 9);

    // Release all dynamically allocated memory.
    freeTrain();

    return 0;
}
