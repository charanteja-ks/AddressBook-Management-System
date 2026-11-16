ADDRESS BOOK MANAGEMENT SYSTEM (C)

Name: KS Charan Teja
Batch ID: 26022_172

Description:
A menu-driven C application to create, search, edit, delete, and list contacts.
Contact information is stored in contacts.csv so it can be loaded the next time
that the program runs.

Files:
- main.c       Main menu and program flow; includes project documentation.
- contact.c    Contact creation, search, edit, delete, sorting, initialization.
- contact.h    Contact structures and function declarations.
- file.c       Loading and saving contacts.csv.
- file.h       File-handling function declarations.
- contacts.csv Saved contact data (can be empty).

Compile (GCC):
    gcc -Wall -Wextra -std=c11 main.c contact.c file.c -o addressbook

Run on Linux/macOS:
    ./addressbook

Run on Windows (MinGW):
    addressbook.exe

The contacts.csv file is read/written in the program's current working directory.
Make a backup before replacing or editing real contact data.
