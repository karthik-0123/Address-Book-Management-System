#include <stdio.h>
#include "contact.h"
#include "file.h"
//To save the contacts in a file
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp,"#%d\n",addressBook->contactCount);
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s,%d,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email,
            addressBook->contacts[i].is_favourite,addressBook->contacts[i].fav_type);
    }

    fclose(fp);
}
//To load contacts from file
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "r");
    if (fp == NULL) {
        printf("No file found. Starting fresh.\n");
        return;
    }
    fscanf(fp,"#%d\n",&addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++){
        fscanf(fp,"%[^,],%[^,],%[^,],%d,%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,
            addressBook->contacts[i].email,&addressBook->contacts[i].is_favourite,addressBook->contacts[i].fav_type);
    }
    fclose(fp);
}