#ifndef CONTACT_H
#define CONTACT_H

typedef struct {
    char name[50];
    char phone[15];
    char email[50];

    int is_favourite;
    char fav_type[20];
} Contact;
typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;
// ================= MAIN FUNCTIONS =================
void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void favoritecontacts(AddressBook *addressBook);

// ================= VALIDATION =================
int my_alpha(char *s);
int valid_phone(char *phone);
int validate_email(char *str);

// ================= DUPLICATES =================
int is_duplicate_phone(AddressBook *addressBook, char *phone, int index);
int is_duplicate_email(AddressBook *addressBook, char *email, int index);

// ================= SEARCH =================
void search_contact(char *key, AddressBook *addressBook, int type);
int search_and_select(AddressBook *addressBook);

// ================= CHECKING =================
void sort_structure(AddressBook *addressBook);
int is_empty(AddressBook *addressBook);

// ================= WELCOME =================
void welcome_and_loading();

#endif