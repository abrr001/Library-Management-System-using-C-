//This is a program for Library Management System 
//In this program we add 6 options  
// Made By :
/*Abu Bakar Rizwan B23F0001CS060
Muhammad Ali Khursheed B23F0588CS083*/

#include <iostream>
#include <string>

using namespace std;

const int Max_Books = 100;
const int Max_Users = 100;

struct Book {
    int bookID;
    char Title[100];
    char author[100];
    bool isAvailable;
};

struct User {
    int userID;
    char name[100];
    int borrowedBooks[Max_Books];
    int numBorrowedBooks;
};
struct Library {
    Book books[Max_Books];
    User users[Max_Users];
    int numBooks;
    int numUsers;
};

void initializeLibrary(Library& library) {
     
}

void displayMenu() {
    cout << "\nLibrary Management System Menu\n";
    cout << "1. Add Book"<<endl;
    cout << "2. Display Books"<<endl;
    cout << "3. Add User"<<endl;
    cout << "4. Display Users"<<endl;
    cout << "5. Borrow Book"<<endl;
    cout << "6. Return Book"<<endl;
    cout << "7. Exit"<<endl;
    cout << "Enter your choice: "<<endl;
}

void addBook(Library& library) {
    if (library.numBooks < Max_Books) {
        Book newBook;
        cout << "Enter book title: ";
        cin.ignore();
        cin.getline(newBook.Title, sizeof(newBook.Title));
        cout << "Enter author name: ";
        cin.getline(newBook.author, sizeof(newBook.author));
        newBook.bookID = library.numBooks + 1;
        newBook.isAvailable = true;
        library.books[library.numBooks++] = newBook;
        cout << "Book added successfully!\n";
    } else {
        cout << "Maximum books reached!\n";
    }
}


void displayBooks(const Library& library) {
    cout << "\nList of Books\n";
    cout << "ID\tTitle\tAuthor\tAvailable\n";
    for (int i = 0; i < library.numBooks; ++i) {
        cout << library.books[i].bookID << "\t" << library.books[i].Title << "\t" << library.books[i].author << "\t"
     << (library.books[i].isAvailable ? "Yes" : "No") << "\n";

    }
}

void addUser(Library& library) {
    if (library.numUsers < Max_Users) {
        User newUser;
        cout << "Enter user name: ";
        cin.ignore();
        cin.getline(newUser.name, sizeof(newUser.name));
        newUser.userID = library.numUsers + 1;
        newUser.numBorrowedBooks = 0;
        library.users[library.numUsers++] = newUser;
        cout << "User added successfully!\n";
    } else {
        cout << "Maximum users reached!\n";
    }
}

void displayUsers(const Library& library) {
    cout << "\nList of Users\n";
    cout << "ID\tName\tBooks Borrowed\n";
    for (int i = 0; i < library.numUsers; ++i) {
        cout << library.users[i].userID << "\t" << library.users[i].name << "\t" << library.users[i].numBorrowedBooks << "\n";
    }
}

void borrowBook(Library& library) {
    int bookID, userID;
    displayBooks(library);
    cout << "Enter book ID to borrow: ";
    cin >> bookID;
    displayUsers(library);
    cout << "Enter user ID: ";
    cin >> userID;

    if (bookID >= 1 && bookID <= library.numBooks && userID >= 1 && userID <= library.numUsers) {
        if (library.books[bookID - 1].isAvailable) {
            if (library.users[userID - 1].numBorrowedBooks < Max_Books){
                library.users[userID - 1].borrowedBooks[library.users[userID - 1].numBorrowedBooks++] = bookID;
                library.books[bookID - 1].isAvailable = false;
                cout << "Book borrowed successfully!\n";
            } else {
                cout << "User has reached the maximum number of borrowed books!\n";
            }
        } else {
            cout << "Book is not available for borrowing!\n";
        }
    } else {
        cout << "Invalid book or user ID!\n";
    }
}

void returnBook(Library& library) {
    int bookID, userID;
    displayBooks(library);
    cout << "Enter book ID to return: ";
    cin >> bookID;
    displayUsers(library);
    cout << "Enter user ID: ";
    cin >> userID;

    if (bookID >= 1 && bookID <= library.numBooks && userID >= 1 && userID <= library.numUsers) {
        bool bookFound = false;
        for (int i = 0; i < library.users[userID - 1].numBorrowedBooks; ++i) {
            if (library.users[userID - 1].borrowedBooks[i] == bookID) {
                library.users[userID - 1].numBorrowedBooks--;
                library.books[bookID - 1].isAvailable = true;
                bookFound = true;
                cout << "Book returned successfully!\n";
                break;
            }
        }
        if (!bookFound) {
            cout << "User did not borrow this book!\n";
        }
    } else {
        cout << "Invalid book or user ID!\n";
    }
}

int main() {
    Library library;
    initializeLibrary(library);

    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2:
                displayBooks(library);
                break;
            case 3:
                addUser(library);
                break;
            case 4:
                displayUsers(library);
                break;
            case 5:
                borrowBook(library);
                break;
            case 6:
                returnBook(library);
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}