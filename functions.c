#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "colors.h"
#include <unistd.h>
// Validate name (only letters + max one space, no leading/trailing space)
int my_alpha(char *s)
{
    if (s == NULL || s[0] == ' ' || s[0] == '\0')
        return 0;

    int spacect = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == ' ')
        {
            spacect++;
            if (spacect > 1 || s[i + 1] == '\0') // trailing space check
                return 0;
        }
        else if (!isalpha((unsigned char)s[i]))
        {
            return 0;
        }
    }
    return 1;
}


// Check all digits
int my_dig( char *s)
{
    if (s == NULL || *s == '\0')
        return 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isdigit(s[i]))
            return 0;
    }
    return 1;
}


// Validate phone
int valid_phone( char *phone)
{
    if (!phone) return 0;
    if (strlen(phone) != 10)
        return 0;

    if (phone[0] < '6' || phone[0] > '9')
        return 0;

    if (!my_dig(phone))
        return 0;

    return 1;
}


// Check duplicate phone
int is_duplicate_phone(AddressBook *addressBook,  char *phone, int index)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i == index) continue;
        if (addressBook->contacts[i].phone &&strcmp(addressBook->contacts[i].phone, phone) == 0)
            return 1;
    }
    return 0;
}

//  Email validation
int validate_email(char *str)
{
    int pos = 0;
    int atCount = 0;
    int dotCount = 0;
    if(str[0] == '\0' || str[0] == '@' || str[0] == '.')
        return 0;
    while(str[pos] != '\0')
    {
        if(str[pos] == ' ')
            return 0;

        if(str[pos] == '@')
        {
            atCount++;
            if(pos == 0 || str[pos + 1] == '\0')
                return 0;
        }

        if(str[pos] == '.')
        {
            dotCount++;
            if(pos == 0 || str[pos + 1] == '\0')
                return 0;

            if(str[pos + 1] == '.')
                return 0;
        }

        if(!(islower(str[pos]) || isdigit(str[pos]) ||
             str[pos] == '@' || str[pos] == '.' ||
             str[pos] == '_' || str[pos] == '-'))
        {
            return 0;
        }

        pos++;
    }

    if(atCount != 1 || dotCount < 1)
        return 0;

    char *atPosition = strchr(str, '@');
    char *lastDot = strrchr(str, '.');
    //if lastdot is before @
    if(lastDot < atPosition)
        return 0;
    //if . is immediately after @
    if(*(atPosition + 1) == '.')
        return 0;
    //to find length between @ and last dot if it is <5
    int length_between = lastDot - atPosition - 1;
    if(length_between < 5)
        return 0;
    //.com should be mandatory
    if(strcmp(lastDot, ".com") != 0)
        return 0;

    return 1;
}

//  Check duplicate email
int is_duplicate_email(AddressBook *addressBook, char *email, int skipIndex)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i == skipIndex) continue;
        if (addressBook->contacts[i].email &&strcmp(addressBook->contacts[i].email, email) == 0)
            return 1;
    }
    return 0;
}


//  Sort contacts by name
void sort_structure(AddressBook *addressBook)
{
    if (!addressBook) return;
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if (strcmp(addressBook->contacts[j].name,addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped==0) break;
    }
}

//  Search contact
void search_contact(char *key, AddressBook *addressBook, int type)
{
    int flag = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        char *check = NULL;
        if (type == 1)
            check = addressBook->contacts[i].name;
        else if (type == 2)
            check = addressBook->contacts[i].phone;
        else
            check = addressBook->contacts[i].email;
        if (strcasestr(check, key))
        {
            if (flag==0)
            {
                printf(CYAN "-------------------------------------------------------------------------------------------------\n" RESET);
                printf(YELLOW "| %-4s | %-25s | %-15s | %-40s |\n" RESET,"ID", "Name", "Phone No", "Email ID");
                printf(CYAN "-------------------------------------------------------------------------------------------------\n" RESET);
                flag = 1;
            }
            printf(GREEN "| %-4d | %-25s | %-15s | %-40s |\n" RESET,i + 1,addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,addressBook->contacts[i].email);
            printf(CYAN "-------------------------------------------------------------------------------------------------\n" RESET);
        }
    }
    if (flag==0)
        printf(RED "Contact Not Found.\n" RESET);
}
//  Safer input search
int index_list[100];
int search_and_select(AddressBook *addressBook)
{
    char ch[50];
    int count = 0;
    printf("Enter name/phone/email to search: ");
    scanf(" %s",ch);
    getchar();
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((addressBook->contacts[i].name &&
             strcasestr(addressBook->contacts[i].name, ch)) ||
            (addressBook->contacts[i].phone &&
             strcasestr(addressBook->contacts[i].phone, ch)) ||
            (addressBook->contacts[i].email &&
             strcasestr(addressBook->contacts[i].email, ch)))
        {
            if(count==0){
                printf(CYAN "\n-------------------------------------------------------------------------------------------------\n" RESET);
                printf(YELLOW "| %-4s | %-25s | %-15s | %-40s |\n" RESET,"ID", "Name", "Phone No", "Email ID");
                printf(CYAN "-------------------------------------------------------------------------------------------------\n" RESET);

            }
            printf(GREEN "| %-4d | %-25s | %-15s | %-40s |\n" RESET,count + 1,addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,addressBook->contacts[i].email);
            printf(CYAN "-------------------------------------------------------------------------------------------------\n" RESET);
            if (count < 100)
                index_list[count++] = i;
        }
    }

    if (count == 0)
        printf(RED "No matching contacts found!\n" RESET);

    return count;
}

// Check empty
int is_empty(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf(RED "\n📂 Address Book is Empty!\n" RESET);
        printf(YELLOW "👉 Please add contacts first.\n" RESET);
        return 1;
    }
    return 0;
}

// Loading animation
void welcome_and_loading()
{
    printf(CYAN BOLD "\n");
    printf("============================================================\n");
    printf("            CONTACT MANAGEMENT SYSTEM\n");
    printf("============================================================\n");
    printf(RESET);

    printf(YELLOW "Starting Application...\n\n" RESET);

    printf(BOLD GREEN "[Loading");
    fflush(stdout);

    for (int i = 0; i <= 100; i++)
    {
        printf("\r" BOLD GREEN "[Loading....... %-3d%%]" RESET, i);
        fflush(stdout);
        usleep(30000); // faster
    }

    printf(GREEN " ✔\n" RESET);
}
