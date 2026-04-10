#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Book{
    public:
        string title;
        string author;
        string isbn;

        void inputBook(){
            cout << "Enter Book Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            cout << "Enter ISBN: ";
            getline(cin, isbn);
        }

        void displayBook() const{
            cout << "Title: " << title << "\nAuthor: " << author << "\nISBN: " << isbn << endl;
        }
};

void addBook();
void displayBooks();
void searchBook();
void deleteBook();

int main(){

    int choice;
    do{
        cout << "\n****************************************\n";
        cout << "Library Management System\n";
        cout << "****************************************\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();       //clear newline from input buffer

        switch(choice){
            case 1: addBook();
                    break;
            case 2: displayBooks();
                    break;
            case 3: searchBook();
                    break;
            case 4: deleteBook();
                    break;
            case 5: cout << "Exiting program.";
                    break;
            default: cout << "Invalid choice!\n";
                     break;
        }
    }while(choice != 5);

    return 0;

}

void addBook(){
    Book b;
    b.inputBook();

    ofstream file("library.txt", ios::app);
    if(file.is_open()){
        file << b.title << "|" << b.author << "|" << b.isbn << endl;
        file.close();
        cout << "Book added sucessfully!" << endl;
    }
    else{
        cout << "Error opening file!" << endl;
    }
}

void displayBooks(){
    ifstream file("library.txt");
    string line;
    if(file.is_open()){
        cout << "\n-----Library Catalog-----\n";
        while(getline(file, line)){
            stringstream ss(line);
            string title, author, isbn;

            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, isbn, '|');

            cout << "Title: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "ISBN: " << isbn << endl;
            cout << "-----------------------------" << endl;
        }
        file.close();
    }
    else{
        cout << "No books found!\n";
    }
}

void searchBook(){
    ifstream file("library.txt");
    string query, line;
    cout << "Enter title to search: ";
    getline(cin, query);

    bool found = false;
    while(getline(file, line)){

        stringstream ss(line);
        string title, author, isbn;

        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, isbn, '|');

        if(title.find(query) != string::npos){
            cout << "\n---- BOOK FOUND----\n";
            cout << "Title: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "ISBN: " << isbn << endl;
            found = true;
        }
    }
    if(!found) cout << "Book not found!" << endl;
    file.close();
}

void deleteBook(){
    ifstream file("library.txt");
    ofstream temp("temp.txt");
    string isbn, line;
    cout << "Enter ISBN of book to delete: ";
    getline(cin, isbn);

    bool deleted = false;
    while(getline(file, line)){
        stringstream ss(line);
        string title, author, fileIsbn;

        getline(ss, title, '|');
        getline(ss, author, '|');
        getline(ss, fileIsbn, '|');

        if(fileIsbn != isbn){
            temp << title << "|" << author << "|" << fileIsbn << endl;
        }
        else{
            deleted = true;
        }
    }
    file.close();
    temp.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if(deleted) cout << "Book deleted successfully!\n";
    else cout << "Book not found!\n";
}