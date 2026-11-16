#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include<ctype.h>

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    int i, j;
    Contact temp;

    for (i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            int result = 0;

            if (sortCriteria == 1)
            {
                result = strcmp(addressBook->contacts[j].name,
                                addressBook->contacts[j + 1].name);
            }
            else if (sortCriteria == 2)
            {
                result = strcmp(addressBook->contacts[j].phone,
                                addressBook->contacts[j + 1].phone);
            }
            else if (sortCriteria == 3)
            {
                result = strcmp(addressBook->contacts[j].email,
                                addressBook->contacts[j + 1].email);
            }

            if (result > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    printf("\nName\t\tPhone\t\tEmail\n");
for (i = 0; i < addressBook->contactCount; i++)
{
    printf("\nContact %d\n", i + 1);
    printf("Name  : %s\n", addressBook->contacts[i].name);
    printf("Phone : %s\n", addressBook->contacts[i].phone);
    printf("Email : %s\n", addressBook->contacts[i].email);
    printf("--------------------------------\n");
}
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    printf("contacts saved succesfully!\n");
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
   
    if(addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("The limit is over to save contacts\n");
        return;
    }

    Contact s1;
    int attempt = 0;
    int flag, length, i;

    while(attempt < 3)
    {
        flag = 1;
        printf("Enter the name: ");
        scanf(" %99[^\n]", s1.name);
        length = strlen(s1.name);
        //char length should be 4 or more
        if(length < 4)
        {
            flag = 0;
        }
        else
        {
            //the name should contain only digits
            for(i = 0; i < length; i++)
            {
                if(!isalpha((unsigned char)s1.name[i]) && s1.name[i] != ' ')
                {
                    flag = 0;
                    break;
                }

                if(s1.name[i] == ' ' && (i == 0 || i == length-1|| s1.name[i - 1] == ' '))
                {
                    flag = 0;
                    break;
                }
            }
        }

        if(flag == 0)
        {
            attempt++;
            printf("Invalid name. Attempts remaining: %d\n", 3 - attempt);
        }
        else
        break;
        
    }
    if(attempt==3)
    {
    printf("Maximum attempts reached.\n");  //if attempts reaches max then go to menu
    printf("------------------------------------------------------------\n");
    return;
    }
    //mobile number validation
      attempt=0;
    do {
    flag = 1; // Reset flag at the start of each attempt
    printf("enter the ph no: ");
    scanf(" %19[^\n]", s1.phone); 
    int len = strlen(s1.phone);
    //  Length validation
    if (len != 10) {
        flag = 0;
        printf("The phone number must be exactly 10 digits long.\n");
    } else {
        // First digit validation (between '6' and '9')
        if (s1.phone[0] < '6' || s1.phone[0] > '9') {
            flag = 0;
            printf("Enter the first digit between 6 and 9.\n");
        }
        
        else {
            //  checking all characters are digits
            for (i = 0; i < len; i++) {
                if (!isdigit((unsigned char)s1.phone[i])) {
                    printf("The number must contain only digits (no spaces or letters).\n");
                    flag = 0;
                    break;
                }
            }
        }
    }
    if(flag==1)
    {
    for(i=0;i<addressBook->contactCount;i++)
    {
        int res = strcmp(s1.phone,addressBook->contacts[i].phone);
        if(res==0)
        {
            printf("the enterd number is already matched with previous data\n");
            flag=0;
            break;
        }
    }
}
    if (flag == 0) {
        attempt++;
        printf("Invalid phone no. Attempts remaining: %d\n", 3 - attempt);
        
        if (attempt == 3) {
            printf("Maximum attempts reached.\n");
           printf("------------------------------------------------------------\n");
            return; 
        }
    } 

} while (flag == 0 && attempt < 3);
// Email Writting and Validating
    // Email validation
    attempt = 0;
    do
    {
        flag = 1;
        int at = 0, pos = -1, dot = 0;

        printf("Enter the Email: ");
        scanf("%s", s1.email);

        length = strlen(s1.email);

        for (i = 0; i < length; i++)
        {
            if (s1.email[i] == '@')    //here checking @ how many times repeated
            {
                at++;
                pos = i;
            }
     // here checking  any uppercase found or all digits 
            if (!(islower((unsigned char)s1.email[i]) ||  isdigit((unsigned char)s1.email[i]) ||
                  s1.email[i] == '@' || s1.email[i] == '.'))
                flag = 0;
        }

        if (at != 1 || pos == 0)
            flag = 0;

        if (at == 1)
        {
            for (i = pos + 2; i < length; i++)
                if (s1.email[i] == '.')
                    dot = 1;
        }

        if (!dot || length < 5 ||
            strcmp(s1.email + length - 4, ".com") != 0)
            flag = 0;
      // here we checking unique email
        for (i = 0; flag && i < addressBook->contactCount; i++)
            if (strcmp(s1.email, addressBook->contacts[i].email) == 0)
                flag = 0;

        if (!flag)
        {
            attempt++;
            printf("Invalid email. Attempts remaining: %d\n", 3 - attempt);
        }

        if (attempt == 3)
        {
            printf("Maximum attempts reached.\n");
            return;
        }

    } while (flag== 0);

   addressBook->contacts[addressBook->contactCount++] = s1;
}
void searchContact(AddressBook *addressBook) 
{
   /* Define the logic for search */
    int choice;
    do
    {
        printf("\nSearch Menu:\n");
        printf("1.Search Name\n");
        printf("2.Search Phone\n");
        printf("3.Search Email\n");
        printf("4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            char name[50];
            printf("Enter name to search: ");
            scanf(" %[^\n]", name);
            int i = 0,flag=0;
            while (name[i] != '\0')
            {
                name[i] = ((unsigned char)name[i]);
                i++;
            }
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].name, name) == 0)
                {
                    printf("\nContact found: %s, %s, %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag=1;
                }
            }

            
            if(flag==0)printf("Inavalid:Contact Name doesn't exists.\n");
            
            
        }
        else if(choice==2)
        {  char phone[11];
            int flag=0;
            printf("Enter Number to Search:");
            scanf("%s",phone);
             for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    printf("Contact found: %s, %s, %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag=1;
                }
            }

            if(flag==0)printf("Inavalid: Contact Number doesn't exists.\n");
          

        }
        else if(choice==3)
        {
            char email[30];
            int flag=0;
            printf("Enter the Seach Email:");
            scanf("%s",email);
             for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, email) == 0)
                {
                    printf("Contact found: %s, %s, %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    flag=1;
                }
            }

           if(flag==0) printf("Inavalid: Contact Email doesn't exists.\n");
            
           
        }
        else if(choice==4)
        {
            printf(" Exiting from the Seach Menu.\n");
            return;
        }
        else
        {
            printf("Invalid Menu Choice please Enter the correct choice.\n");
            
        
        }

    } while (choice != 4);

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice, i, j, count, index;
    int flag, attempt, length, at, pos, dot;
    int matches[MAX_CONTACTS];

    do
    {
        printf("\n========== EDIT CONTACT MENU ==========\n");
        printf("1. Edit by Name\n");
        printf("2. Edit by Phone Number\n");
        printf("3. Edit by Email ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4)
        {
            printf("Exiting Edit Menu.\n");
            return;
        }

        if (choice < 1 || choice > 4)
        {
            printf("Invalid menu choice.\n");
            continue;
        }

        char search[100];

        if (choice == 1)
        {
            printf("Enter name to search: ");
            scanf(" %99[^\n]", search);
        }
        else if (choice == 2)
        {
            printf("Enter phone number to search: ");
            scanf(" %99s", search);
        }
        else
        {
            printf("Enter email ID to search: ");
            scanf(" %99s", search);
        }

        count = 0;

        /* Find all matching contacts */
        for (i = 0; i < addressBook->contactCount; i++)
        {
            flag = 0;

            if (choice == 1 &&
                strcmp(addressBook->contacts[i].name, search) == 0)
            {
                flag = 1;
            }
            else if (choice == 2 &&
                     strcmp(addressBook->contacts[i].phone, search) == 0)
            {
                flag = 1;
            }
            else if (choice == 3 &&
                     strcmp(addressBook->contacts[i].email, search) == 0)
            {
                flag = 1;
            }

            if (flag)
            {
                matches[count] = i;
                count++;
            }
        }

        if (count == 0)
        {
            printf("No matching contact found.\n");
            continue;
        }

        /* If duplicate records exist, ask the user to select one */
        if (count > 1)
        {
            printf("\nMultiple contacts found:\n");

            for (i = 0; i < count; i++)
            {
                index = matches[i];

                printf("%d. Name: %s | Phone: %s | Email: %s\n",
                       i + 1,
                       addressBook->contacts[index].name,
                       addressBook->contacts[index].phone,
                       addressBook->contacts[index].email);
            }

            int selected;

            printf("Select the contact number to edit (0 to cancel): ");
            scanf("%d", &selected);

            if (selected == 0)
            {
                printf("Edit cancelled.\n");
                continue;
            }

            if (selected < 1 || selected > count)
            {
                printf("Invalid contact selection.\n");
                continue;
            }

            index = matches[selected - 1];
        }
        else
        {
            index = matches[0];
        }

        /* Select which field to edit */
        int field;

        printf("\nContact selected:\n");
        printf("Name  : %s\n", addressBook->contacts[index].name);
        printf("Phone : %s\n", addressBook->contacts[index].phone);
        printf("Email : %s\n", addressBook->contacts[index].email);

        printf("\nWhat do you want to edit?\n");
        printf("1. Name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");
        printf("4. Cancel\n");
        printf("Enter your choice: ");
        scanf("%d", &field);

        if (field == 4)
        {
            printf("Edit cancelled.\n");
            continue;
        }

        if (field < 1 || field > 4)
        {
            printf("Invalid field choice.\n");
            continue;
        }

        /* EDIT NAME */
        if (field == 1)
        {
            attempt = 0;

            while (attempt < 3)
            {
                flag = 1;

                printf("Enter new name: ");
                scanf(" %99[^\n]", search);

                length = strlen(search);

                if (length < 4)
                {
                    flag = 0;
                    printf("Invalid name: Name must contain at least 4 characters.\n");
                }
                else
                {
                    for (i = 0; i < length; i++)
                    {
                        if (!isalpha((unsigned char)search[i]) &&
                            search[i] != ' ')
                        {
                            flag = 0;
                            printf("Invalid name: Only alphabets and spaces are allowed.\n");
                            break;
                        }

                        if (search[i] == ' ' &&
                            (i == 0 || i == length - 1 ||
                             search[i - 1] == ' '))
                        {
                            flag = 0;
                            printf("Invalid name: Leading, trailing, or consecutive spaces are not allowed.\n");
                            break;
                        }
                    }
                }

                if (flag)
                {
                    strcpy(addressBook->contacts[index].name, search);
                    printf("Name updated successfully.\n");
                    break;
                }

                attempt++;
                printf("Attempts remaining: %d\n", 3 - attempt);
            }

            if (attempt == 3)
            {
                printf("Maximum attempts reached. Name was not updated.\n");
            }
        }

        /* EDIT PHONE NUMBER */
        else if (field == 2)
        {
            attempt = 0;

            while (attempt < 3)
            {
                flag = 1;

                printf("Enter new phone number: ");
                scanf(" %99s", search);

                length = strlen(search);

                if (length != 10)
                {
                    flag = 0;
                    printf("Invalid phone number: Must contain exactly 10 digits.\n");
                }
                else if (search[0] < '6' || search[0] > '9')
                {
                    flag = 0;
                    printf("Invalid phone number: First digit must be between 6 and 9.\n");
                }
                else
                {
                    for (i = 0; i < length; i++)
                    {
                        if (!isdigit((unsigned char)search[i]))
                        {
                            flag = 0;
                            printf("Invalid phone number: Only digits are allowed.\n");
                            break;
                        }
                    }
                }

                /* Check duplicate phone numbers, excluding current contact */
                if (flag)
                {
                    for (i = 0; i < addressBook->contactCount; i++)
                    {
                        if (i != index &&
                            strcmp(search, addressBook->contacts[i].phone) == 0)
                        {
                            flag = 0;
                            printf("Invalid phone number: This number already belongs to another contact.\n");
                            break;
                        }
                    }
                }

                if (flag)
                {
                    strcpy(addressBook->contacts[index].phone, search);
                    printf("Phone number updated successfully.\n");
                    break;
                }

                attempt++;
                printf("Attempts remaining: %d\n", 3 - attempt);
            }

            if (attempt == 3)
            {
                printf("Maximum attempts reached. Phone number was not updated.\n");
            }
        }

        /* EDIT EMAIL ID */
        else if (field == 3)
        {
            attempt = 0;

            while (attempt < 3)
            {
                flag = 1;
                at = 0;
                pos = -1;
                dot = 0;

                printf("Enter new email ID: ");
                scanf(" %99s", search);

                length = strlen(search);

                for (i = 0; i < length; i++)
                {
                    if (search[i] == '@')
                    {
                        at++;
                        pos = i;
                    }

                    if (!(islower((unsigned char)search[i]) ||
                          isdigit((unsigned char)search[i]) ||
                          search[i] == '@' || search[i] == '.'))
                    {
                        flag = 0;
                    }
                }

                if (at != 1 || pos == 0)
                {
                    flag = 0;
                    printf("Invalid email: Must contain exactly one @ symbol, not at the beginning.\n");
                }

                if (at == 1)
                {
                    for (i = pos + 2; i < length; i++)
                    {
                        if (search[i] == '.')
                        {
                            dot = 1;
                        }
                    }
                }

                if (!dot || length < 5 ||
                    strcmp(search + length - 4, ".com") != 0)
                {
                    flag = 0;
                    printf("Invalid email: Must contain a valid domain and end with .com.\n");
                }

                /* Check duplicate emails, excluding current contact */
                if (flag)
                {
                    for (i = 0; i < addressBook->contactCount; i++)
                    {
                        if (i != index &&
                            strcmp(search, addressBook->contacts[i].email) == 0)
                        {
                            flag = 0;
                            printf("Invalid email: This email already belongs to another contact.\n");
                            break;
                        }
                    }
                }

                if (flag)
                {
                    strcpy(addressBook->contacts[index].email, search);
                    printf("Email updated successfully.\n");
                    break;
                }

                attempt++;
                printf("Attempts remaining: %d\n", 3 - attempt);
            }

            if (attempt == 3)
            {
                printf("Maximum attempts reached. Email was not updated.\n");
            }
        }

    } while (choice != 4);
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    void deleteContact(AddressBook *addressBook)
{
    int choice, i, count, index;
    int matches[MAX_CONTACTS];
    char search[100];
    char confirm;

    do
    {
        printf("\n========== DELETE CONTACT MENU ==========\n");
        printf("1. Delete by Name\n");
        printf("2. Delete by Phone Number\n");
        printf("3. Delete by Email ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4)
        {
            printf("Exiting Delete Menu.\n");
            return;
        }

        if (choice < 1 || choice > 4)
        {
            printf("Invalid menu choice.\n");
            continue;
        }

        /* Read search value */
        if (choice == 1)
        {
            printf("Enter name to search: ");
            scanf(" %99[^\n]", search);
        }
        else if (choice == 2)
        {
            printf("Enter phone number to search: ");
            scanf(" %99s", search);
        }
        else
        {
            printf("Enter email ID to search: ");
            scanf(" %99s", search);
        }

        /* Find matching contacts */
        count = 0;

        for (i = 0; i < addressBook->contactCount; i++)
        {
            int flag = 0;

            if (choice == 1 &&
                strcmp(addressBook->contacts[i].name, search) == 0)
            {
                flag = 1;
            }
            else if (choice == 2 &&
                     strcmp(addressBook->contacts[i].phone, search) == 0)
            {
                flag = 1;
            }
            else if (choice == 3 &&
                     strcmp(addressBook->contacts[i].email, search) == 0)
            {
                flag = 1;
            }

            if (flag)
            {
                matches[count] = i;
                count++;
            }
        }

        /* No matching contact */
        if (count == 0)
        {
            printf("No matching contact found.\n");
            continue;
        }

        /* Handle duplicate records */
        if (count > 1)
        {
            printf("\nMultiple contacts found:\n");

            for (i = 0; i < count; i++)
            {
                index = matches[i];

                printf("%d. Name: %s | Phone: %s | Email: %s\n",
                       i + 1,
                       addressBook->contacts[index].name,
                       addressBook->contacts[index].phone,
                       addressBook->contacts[index].email);
            }

            int selected;

            printf("Select the contact to delete (0 to cancel): ");
            scanf("%d", &selected);

            if (selected == 0)
            {
                printf("Deletion cancelled.\n");
                continue;
            }

            if (selected < 1 || selected > count)
            {
                printf("Invalid contact selection.\n");
                continue;
            }

            index = matches[selected - 1];
        }
        else
        {
            index = matches[0];
        }

        /* Display selected contact */
        printf("\nContact selected for deletion:\n");
        printf("Name  : %s\n", addressBook->contacts[index].name);
        printf("Phone : %s\n", addressBook->contacts[index].phone);
        printf("Email : %s\n", addressBook->contacts[index].email);

        /* Ask for confirmation */
        printf("\nAre you sure you want to delete this contact? (y/n): ");
        scanf(" %c", &confirm);

        if (confirm == 'y' || confirm == 'Y')
        {
            /* Shift remaining contacts one position left */
            for (i = index; i < addressBook->contactCount - 1; i++)
            {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }

            addressBook->contactCount--;

            printf("Contact deleted successfully.\n");
        }
        else if (confirm == 'n' || confirm == 'N')
        {
            printf("Deletion cancelled. Contact was not deleted.\n");
        }
        else
        {
            printf("Invalid confirmation. Contact was not deleted.\n");
        }

    } while (choice != 4);
}
   
}
