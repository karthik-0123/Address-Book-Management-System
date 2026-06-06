# Address-Book-Management-System

A simple C-based address book application for managing contacts. The program supports creating, searching, editing, deleting, listing, and marking favorite contacts. Contact data is persisted in `contacts.txt`, so information is preserved between program runs.

## Features

- Add new contacts with name, phone number, email, and favorite status
- Search contacts by name, phone number, or email
- Edit existing contact details
- Delete contacts
- List all saved contacts in a formatted table
- View favorite contacts and categorize them as Friend, Family, or Others
- Automatic data persistence in `contacts.txt`
- Input validation for names, phone numbers, and emails

## Project Structure

- `main.c` - main application loop and menu handler
- `contact.c` - contact management functions (create, edit, list, search, delete)
- `functions.c` - input validation, search utilities, and helper functions
- `file.c` - file save/load implementation
- `contact.h` - address book and contact structure definitions
- `file.h` - file operation declarations
- `functions.h` - helper function declarations
- `colors.h` - terminal color macros for styled output
- `contacts.txt` - saved contact data file

## Build Instructions

Compile the project using a C compiler such as `gcc`.

```bash
gcc main.c contact.c functions.c file.c -o addressbook
```

## Run Instructions

Execute the compiled program from the command line:

```bash
./addressbook
```

On Windows with MinGW or a similar toolchain, use:

```bash
addressbook.exe
```

## Usage

The program displays a menu with options to:

1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Favorite contacts
7. Save and Exit

Choose the desired option by entering its number and follow the prompts.

## Notes

- The address book supports up to 100 contacts.
- Phone numbers must be 10 digits and start with a digit between 6 and 9.
- Emails must be lowercase and end with `.com`.
- The project is designed for console usage with text-based interaction.
