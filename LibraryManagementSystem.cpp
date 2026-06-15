#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Book {
public:
    int bookId;
    string title;
    string author;
    bool issued;
};

const string FILE_NAME = "books.txt";

vector<Book> loadBooks() {
    vector<Book> books;
    ifstream file(FILE_NAME);

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        Book b;
        string id, status;

        getline(ss, id, '|');
        getline(ss, b.title, '|');
        getline(ss, b.author, '|');
        getline(ss, status, '|');

        b.bookId = stoi(id);
        b.issued = stoi(status);

        books.push_back(b);
    }

    file.close();
    return books;
}

void saveBooks(vector<Book>& books) {
    ofstream file(FILE_NAME);

    for (auto &b : books) {
        file << b.bookId << "|"
             << b.title << "|"
             << b.author << "|"
             << b.issued << endl;
    }

    file.close();
}

void addBook() {

    Book b;

    cout << "\nEnter Book ID: ";
    cin >> b.bookId;
    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, b.title);

    cout << "Enter Author Name: ";
    getline(cin, b.author);

    b.issued = false;

    ofstream file(FILE_NAME, ios::app);

    file << b.bookId << "|"
         << b.title << "|"
         << b.author << "|"
         << b.issued << endl;

    file.close();

    cout << "\nBook Added Successfully!\n";
}

void displayBooks() {

    vector<Book> books = loadBooks();

    if (books.empty()) {
        cout << "\nNo Books Available!\n";
        return;
    }

    cout << "\n===== LIBRARY BOOKS =====\n";

    for (auto &b : books) {

        cout << "\nBook ID : " << b.bookId;
        cout << "\nTitle   : " << b.title;
        cout << "\nAuthor  : " << b.author;
        cout << "\nStatus  : ";

        if (b.issued)
            cout << "Issued";
        else
            cout << "Available";

        cout << "\n-----------------------";
    }
}

void issueBook() {

    int id;

    cout << "\nEnter Book ID to Issue: ";
    cin >> id;

    vector<Book> books = loadBooks();

    bool found = false;

    for (auto &b : books) {

        if (b.bookId == id) {

            if (b.issued) {
                cout << "\nBook Already Issued!\n";
                return;
            }

            b.issued = true;
            found = true;

            cout << "\nBook Issued Successfully!\n";
            break;
        }
    }

    if (!found) {
        cout << "\nBook Not Found!\n";
        return;
    }

    saveBooks(books);
}

void returnBook() {

    int id;

    cout << "\nEnter Book ID to Return: ";
    cin >> id;

    vector<Book> books = loadBooks();

    bool found = false;

    for (auto &b : books) {

        if (b.bookId == id) {

            if (!b.issued) {
                cout << "\nBook Already Available!\n";
                return;
            }

            b.issued = false;
            found = true;

            cout << "\nBook Returned Successfully!\n";
            break;
        }
    }

    if (!found) {
        cout << "\nBook Not Found!\n";
        return;
    }

    saveBooks(books);
}

void searchBook() {

    int choice;

    cout << "\nSearch By:";
    cout << "\n1. Title";
    cout << "\n2. Author";

    cout << "\nEnter Choice: ";
    cin >> choice;
    cin.ignore();

    vector<Book> books = loadBooks();

    bool found = false;

    if (choice == 1) {

        string title;

        cout << "Enter Title: ";
        getline(cin, title);

        for (auto &b : books) {

            if (b.title == title) {

                cout << "\nBook Found!";
                cout << "\nBook ID : " << b.bookId;
                cout << "\nTitle   : " << b.title;
                cout << "\nAuthor  : " << b.author << endl;

                found = true;
            }
        }

    } else if (choice == 2) {

        string author;

        cout << "Enter Author Name: ";
        getline(cin, author);

        for (auto &b : books) {

            if (b.author == author) {

                cout << "\nBook Found!";
                cout << "\nBook ID : " << b.bookId;
                cout << "\nTitle   : " << b.title;
                cout << "\nAuthor  : " << b.author << endl;

                found = true;
            }
        }
    }

    if (!found)
        cout << "\nNo Matching Book Found!\n";
}

int main() {

    int choice;

    do {

        cout << "\n\n===== LIBRARY MANAGEMENT SYSTEM =====";

        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Issue Book";
        cout << "\n4. Return Book";
        cout << "\n5. Search Book";
        cout << "\n6. Exit";

        cout << "\n\nEnter Choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                issueBook();
                break;

            case 4:
                returnBook();
                break;

            case 5:
                searchBook();
                break;

            case 6:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 6);

    return 0;
}
