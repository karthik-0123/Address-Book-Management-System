#include <stdio.h>
#include <unistd.h>
#include "contact.h"
#include "colors.h"
#include "file.h"

int main()
{
    welcome_and_loading();
    AddressBook addressBook;
    initialize(&addressBook);
    loadContactsFromFile(&addressBook);
    int password;
    int choice;
    int attempts = 5;   //FIXED (added)

start:
    printf(BOLD_MAGENTA "\n🔐 ENTER PASSWORD TO OPEN ADDRESS BOOK 🔐\n" RESET);
    printf(CYAN "-----------------------------------------\n" RESET);
    printf("Enter password: ");
    scanf("%d", &password);

    if(password == 258456)
    {
        printf(GREEN "\n✅ Access Granted!\n" RESET);

        do 
        {
            printf(BOLD_MAGENTA "\n📒 ADDRESS BOOK MENU 📒\n" RESET);
            printf(CYAN "-----------------------------------------\n" RESET);
            printf(YELLOW "1. Create contact\n" );
            printf("2. Search contact\n");
            printf("3. Edit contact\n");
            printf("4. Delete contact\n");
            printf("5. List all contacts\n");
            printf("6. Favorite contacts\n");
            printf("7. Save and Exit\n" RESET);
            printf(CYAN "-----------------------------------------\n" RESET);

            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) 
            {
                case 1:
                    createContact(&addressBook);
                    break;

                case 2:
                    searchContact(&addressBook);
                    break;

                case 3:
                    editContact(&addressBook);
                    break;

                case 4:
                    deleteContact(&addressBook);
                    break;

                case 5:
                    listContacts(&addressBook);
                    break;

                case 6:
                    favoritecontacts(&addressBook);
                    break;

                case 7:
                    printf(GREEN "\n💾 Saving and Exiting...\n" RESET);
                    saveContactsToFile(&addressBook);
                    break;

                default:
                    printf(RED "❌ Invalid choice. Try again.\n" RESET);
            }

        } while (choice != 7);
    }
    else
    {
        attempts--;
        printf(RED "❌ Wrong Password!\n" RESET);
        printf(YELLOW "You have only %d attempts left.\n" RESET, attempts);
        if(attempts == 0){
            printf(RED "\n🚫 Access Denied. Exiting...\n" RESET);
            return 1;
        }
        goto start;
    }

    return 0;
}