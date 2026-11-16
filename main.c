#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do
{
    printf("\nAddress Book Menu:\n");
    printf("1. Create contact\n");
    printf("2. Search contact\n");
    printf("3. Edit contact\n");
    printf("4. Delete contact\n");
    printf("5. List all contacts\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("Input error. Exiting.\n");
        break;
    }

    switch (choice)
    {
       case 1:
    createContact(&addressBook);
    saveContactsToFile(&addressBook);
    break;

case 2:
    searchContact(&addressBook);
    break;

case 3:
    editContact(&addressBook);
    saveContactsToFile(&addressBook);
    break;

case 4:
    deleteContact(&addressBook);
    saveContactsToFile(&addressBook);
    break;

        case 5:
        {
            int sortChoice;

            printf("\nSelect sort criteria:\n");
            printf("1. Sort by name\n");
            printf("2. Sort by phone\n");
            printf("3. Sort by email\n");
            printf("Enter your choice: ");

            if (scanf("%d", &sortChoice) != 1)
            {
                printf("Input error. Exiting.\n");
                return 1;
            }

            if (sortChoice >= 1 && sortChoice <= 3)
                listContacts(&addressBook, sortChoice);
            else
                printf("Invalid sorting choice.\n");

            break;
        }

        case 6:
              printf("Saving and exiting...\n");
              saveAndExit(&addressBook);
              break;

        default:
            printf("Invalid choice.\n");
    }

} while (choice != 6);
    
       return 0;
}