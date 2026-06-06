#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "colors.h"
void initialize(AddressBook *addressBook) {
    addressBook->contactCount=0;
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
//==========================CREATE CONTACT===========================
void createContact(AddressBook *addressBook)
{
    if(addressBook->contactCount >= 100){
        printf(RED "🚫 Address Book is Full! Cannot add more contacts.\n" RESET);
        printf(YELLOW "📌 Please delete an existing contact to add a new one.\n" RESET);
        return;
    }
    int index = addressBook->contactCount;

    //================== NAME ==================
    int count = 0;
    do{
        printf("Enter name: ");
        scanf(" %[^\n]", addressBook->contacts[index].name);
        if(my_alpha(addressBook->contacts[index].name) == 0)
        {
            printf(RED "The entered name is invalid. Try again\n" RESET);
            count++;
            if(count < 3)
                printf(YELLOW "You have only %d chances left.\n" RESET, 3 - count);
            if(count == 3){ return; }
        }
        else{
            break;
        }
    }while(count < 3);

    //================== PHONE ==================
    int c1 = 0;
    do{
        printf("Enter phone Number: ");
        scanf("%s", addressBook->contacts[index].phone);

        char *phone = addressBook->contacts[index].phone;

        if(!valid_phone(phone) || is_duplicate_phone(addressBook, phone, index))
        {
            printf(RED "Invalid or duplicate phone number. Try again.\n" RESET);
            c1++;
            if(c1 < 3)
                printf(YELLOW "You have only %d chances left.\n" RESET, 3 - c1);
            if(c1 == 3){ return; }
        }
        else{
            break;
        }
    }while(c1 < 3);

    //================== EMAIL ==================
    int c2 = 0;
    do{
        printf("Enter E-mail Id: ");
        scanf(" %[^\n]", addressBook->contacts[index].email);

        char *mail = addressBook->contacts[index].email;

        if(validate_email(mail) == 0 ||
           is_duplicate_email(addressBook, mail, index))
        {
            printf(RED "Invalid or duplicate email. Try again.\n" RESET);
            c2++;
            if(c2 < 3)
                printf(YELLOW "You have only %d chances left.\n" RESET, 3 - c2);
            if(c2 == 3){ return; }
        }
        else{
            break;
        }
    }while(c2 < 3);

    //================== FAVOURITE ==================
    char choice;
    printf("Mark as favorite? (y/n): ");
    scanf(" %c", &choice);
    if(choice == 'y' || choice == 'Y') {
        addressBook->contacts[index].is_favourite = 1;
        int type;
        printf("Select Favourite Type:\n");
        printf("1. Friend\n2. Family\n3. Others\n");
        printf("Enter choice: ");
        scanf("%d", &type);
        switch(type){
            case 1:
                strcpy(addressBook->contacts[index].fav_type, "Friend");
                break;
            case 2:
                strcpy(addressBook->contacts[index].fav_type, "Family");
                break;
            case 3:
                strcpy(addressBook->contacts[index].fav_type, "Others");
                break;
            default:
                strcpy(addressBook->contacts[index].fav_type, "Others");
        }
    }
    else{
        addressBook->contacts[index].is_favourite = 0;
        strcpy(addressBook->contacts[index].fav_type, "-");
    }
    printf(GREEN "Contact Saved Successfully.\n" RESET);
    addressBook->contactCount++;
    sort_structure(addressBook);
}


//==============================LIST ALL CONTACTS==================================
void listContacts(AddressBook *addressBook) 
{
    if(is_empty(addressBook)) return;
    printf(BOLD_MAGENTA "\n📒 CONTACT LIST 📒\n\n" RESET);
    printf(CYAN "-----------------------------------------------------------------------------\n" RESET);
    printf(YELLOW "| %-4s | %-20s | %-15s | %-25s |\n" RESET,
           "ID","Name","Phone","Email");
    printf(CYAN "-----------------------------------------------------------------------------\n" RESET);
    for(int i=0;i<addressBook->contactCount;i++){
        printf(GREEN "| %-4d | %-20s | %-15s | %-25s |\n" RESET,
               i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    printf(CYAN "-------------------------------------------------------------------------- --\n" RESET);
    }
}


//==============================SEARCH CONTACT==================================
void searchContact(AddressBook *addressBook) 
{
    //checking addressbook is empty are not
    if(is_empty(addressBook)) return;
    char ch[50];
    int choice;
    do{
        printf(YELLOW"Select option :\n1.Search by name\n2.Search by phone no\n3.Search by Email-Id\n4.Exit\n"RESET);
        printf("Enter your choice : ");
        scanf("%d",&choice);
        getchar();
        switch(choice){
        case 1:printf("Enter name : ");
               scanf(" %[^\n]",ch);
               search_contact(ch,addressBook,1);
               break;
        case 2:printf("Enter number : ");
               scanf(" %[^\n]",ch);
               search_contact(ch,addressBook,2);
               break;
        case 3:printf("Enter Email-Id : ");
               scanf(" %[^\n]",ch);
               search_contact(ch,addressBook,3);
               break;
        case 4:printf("Exiting.....\n");
               break;
        default:
               printf("Enter valid number.\n");
               break;
        }
    }
    while(choice!=4);
}


//=================================EDIT CONTACT ======================================
extern int index_list[100];

void editContact(AddressBook *addressBook)
{
    if(is_empty(addressBook)) return;

    int valid = search_and_select(addressBook);
    if(valid == 0){
        printf(RED "Contact Not found!!!\n" RESET);
        return;
    }

    int n;
    printf("Enter ID to Edit : ");
    scanf("%d", &n);
    if(n < 1 || n > valid){
        printf(RED "Invalid choice\n" RESET);
        return;
    }
    int m = index_list[n - 1];
    int choice;
    do{
        printf(CYAN "\n=========== EDIT MENU ===========\n" RESET);
        printf(YELLOW "1. Edit Name\n" RESET);
        printf(YELLOW "2. Edit Phone No\n" RESET);
        printf(YELLOW "3. Edit E-mail Id\n" RESET);
        printf(YELLOW "4. Edit Favourite\n" RESET);
        printf(YELLOW "5. Exit\n" RESET);
        printf(CYAN   "=================================\n" RESET);
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            {
                int attempts = 3;
                while(attempts > 0){
                    printf("Enter new name: ");
                    scanf(" %[^\n]", addressBook->contacts[m].name);
                    if(my_alpha(addressBook->contacts[m].name)){
                        printf(GREEN "✔ Name updated successfully!\n" RESET);
                        break;
                    }
                    attempts--;
                    printf(RED "Invalid name! Attempts left: %d\n" RESET, attempts);
                }
                if(attempts == 0) return;
                break;
            }
            case 2:
            {
                int attempts = 3;
                while(attempts > 0){
                    printf("Enter new phone: ");
                    scanf("%s", addressBook->contacts[m].phone);
                    if(valid_phone(addressBook->contacts[m].phone) &&
                       !is_duplicate_phone(addressBook, addressBook->contacts[m].phone, m)){
                        printf(GREEN "✔ Phone updated successfully!\n" RESET);
                        break;
                    }

                    attempts--;
                    printf(RED "Invalid or duplicate phone! Attempts left: %d\n" RESET, attempts);
                }
                if(attempts == 0) return;
                break;
            }

            case 3:
            {
                int attempts = 3;
                while(attempts > 0){
                    printf("Enter new email: ");
                    scanf(" %[^\n]", addressBook->contacts[m].email);
                    if(validate_email(addressBook->contacts[m].email) &&
                       !is_duplicate_email(addressBook, addressBook->contacts[m].email, m)){
                        printf(GREEN "✔ Email updated successfully!\n" RESET);
                        break;
                    }
                    attempts--;
                    printf(RED "Invalid or duplicate email! Attempts left: %d\n" RESET, attempts);
                }
                if(attempts == 0) return;
                break;
            }

            case 4:
            {
                char ch;
                while(1){
                    printf(CYAN "\n⭐ Favourite Option ⭐\n" RESET);
                    printf(YELLOW "Mark as favourite? (y/n): " RESET);
                    scanf(" %c", &ch);
                    if(ch == 'y' || ch == 'Y'){
                        addressBook->contacts[m].is_favourite = 1;
                        int type;
                        printf("1. Friend\n2. Family\n3. Others\n");
                        printf("Enter type: ");
                        scanf("%d", &type);
                        if(type == 1)
                            strcpy(addressBook->contacts[m].fav_type, "Friend");
                        else if(type == 2)
                            strcpy(addressBook->contacts[m].fav_type, "Family");
                        else
                            strcpy(addressBook->contacts[m].fav_type, "Others");
                        printf(GREEN "✔ Contact marked as favourite.\n" RESET);
                        break;
                    }
                    else if(ch == 'n' || ch == 'N'){
                        addressBook->contacts[m].is_favourite = 0;
                        strcpy(addressBook->contacts[m].fav_type, "-");
                        printf(GREEN "✔ Contact removed from favourites.\n" RESET);
                        break;
                    }
                    else{
                        printf(RED "✖ Invalid input! Enter y/n only.\n" RESET);
                    }
                }
                break;
            }

            case 5:
                printf(CYAN "Exiting edit menu...\n" RESET);
                break;

            default:
                printf(RED "Enter a valid option.\n" RESET);
        }

    } while(choice != 5);

    sort_structure(addressBook);
    printf(GREEN "\n✔ Contact updated successfully!\n" RESET);
}
//================================DELETE CONTACT======================================
void deleteContact(AddressBook *addressBook)
{
    if(is_empty(addressBook)) return;
    int choice;
    printf(BOLD_MAGENTA "\n 🗑️  DELETE MENU\n" RESET);
    printf(CYAN   "----------------------------------\n" RESET);
    printf(YELLOW "1. Delete a single contact\n" RESET);
    printf(YELLOW "2. Delete ALL contacts\n" RESET);
    printf(CYAN   "----------------------------------\n" RESET);
    printf("Enter your choice: ");
    scanf("%d", &choice);
    //This one is used to delete all the contacts
    if(choice == 2){
        char ch;
        while(1){
            printf(RED "\n ⚠ WARNING: This will delete ALL contacts permanently!\n" RESET);
            printf(YELLOW "Are you sure you want to continue? (y/n): " RESET);
            scanf(" %c", &ch);
            if(ch=='y'||ch=='Y'){
                addressBook->contactCount = 0;
                printf(GREEN "✔ All contacts deleted successfully.\n" RESET);
                return;
            }
            else if(ch=='n'||ch=='N'){
                printf(CYAN "Operation cancelled.\n" RESET);
                return;
            }
            else{
                printf(RED "✖ Invalid input! Please enter 'y' or 'n'.\n" RESET);
            }
        }
    }
    //calling a search and select function to delete the fields at that index
    int valid = search_and_select(addressBook);
    if(valid == 0){
        printf(RED "Contact Not found!!!\n" RESET);
        return;
    }
    int n;
    printf("Enter ID to delete : ");
    scanf("%d", &n);
    if(n < 1 || n > valid){
        printf(RED "Invalid choice\n" RESET);
        return;
    }
    //to delete all fields at the index
    int m = index_list[n - 1];
    char ch;
    start :
    printf("If you want to delete contact press 'y'/'n' \n");
    scanf(" %c",&ch);
    if(ch=='y'||ch=='Y'){
        for(int i=m;i<addressBook->contactCount-1;i++){
            addressBook->contacts[i]=addressBook->contacts[i+1];
        }
        addressBook->contactCount--;
        printf(GREEN"The contact is successfully deleted.\n"RESET);
    }
    else if(ch=='n'||ch=='N'){
        printf("Not deleting the contact.\n");
        return;
    }
    else{
        printf(YELLOW"Enter a valid character.\n"RESET);
        goto start;
    }
}


//=====================================FAVORITE CONTACTS===========================================
void favoritecontacts(AddressBook *addressBook)
{
    int flag = 0;
    if(is_empty(addressBook)) return;

    printf(BOLD MAGENTA "\n\t\t\t ❤️  FAVOURITE CONTACTS ❤️\n" RESET);
    printf(CYAN "=========================================================================================\n" RESET);
    printf(YELLOW "| %-4s | %-20s | %-15s | %-25s | %-10s |\n" RESET,
           "ID", "Name", "Phone No", "Email ID", "Type");
    printf(CYAN "=========================================================================================\n" RESET);

    for(int i = 0; i < addressBook->contactCount; i++){
        if(addressBook->contacts[i].is_favourite == 1){
            printf(GREEN "| %-4d | %-20s | %-15s | %-25s | %-10s |\n" RESET,
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email,
                   addressBook->contacts[i].fav_type);
            printf(CYAN "-----------------------------------------------------------------------------------------\n" RESET);
            flag = 1;
        }
    }

    if(flag == 0){
        printf(RED "\n ❤️ No favourite contacts found!\n\n" RESET);
    }
}