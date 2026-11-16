#include <stdio.h>
#include "file.h"
#include<string.h>
#include<ctype.h>

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "w");

    if (fp == NULL)
    {
        printf("Unable to open file!\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);
    printf("Contacts saved successfully!\n");
}

void loadContactsFromFile(AddressBook *addressBook) {
        FILE *fp = fopen("contacts.csv", "r");

    if (fp == NULL)
    {
        printf("No saved contacts found!\n");
        return;
    }

    char line[512];

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (addressBook->contactCount >=
            sizeof(addressBook->contacts) / sizeof(addressBook->contacts[0]))
        {
            break;
        }

        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, "\n");

        if (name == NULL || phone == NULL || email == NULL)
        {
            continue;
        }

        int i = addressBook->contactCount;

        strcpy(addressBook->contacts[i].name, name);
        strcpy(addressBook->contacts[i].phone, phone);
        strcpy(addressBook->contacts[i].email, email);

        addressBook->contactCount++;
    }

    fclose(fp);

    printf("Contacts loaded successfully!\n");
    
}
