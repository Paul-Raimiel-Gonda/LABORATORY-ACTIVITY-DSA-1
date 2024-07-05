#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

struct Node {
    string game;
    int concurrentPlayers;
    Node* next;
    Node(string gameName, int players = 0) : game(gameName), concurrentPlayers(players), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

    void swap(Node* a, Node* b) {
        string tempGame = a->game;
        int tempPlayers = a->concurrentPlayers;
        a->game = b->game;
        a->concurrentPlayers = b->concurrentPlayers;
        b->game = tempGame;
        b->concurrentPlayers = tempPlayers;
    }

public:
    LinkedList() : head(nullptr) {}

    void insertSorted(string newGame, int players) {
        Node* newNode = new Node(newGame, players);
        if (head == nullptr || head->concurrentPlayers < players) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr && temp->next->concurrentPlayers >= players) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    void insertAtEnd(string newGame, int players) {
        Node* newNode = new Node(newGame, players);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void deleteNode(string gameName) {
        Node* temp = head;
        Node* prev = nullptr;

        if (temp != nullptr && temp->game == gameName) {
            head = temp->next;
            delete temp;
            return;
        }

        while (temp != nullptr && temp->game != gameName) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Node with game " << gameName << " not found." << endl;
            return;
        }

        prev->next = temp->next;
        delete temp;
    }

    void sortList() {
        if (head == nullptr || head->next == nullptr) {
            return;
        }
        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->concurrentPlayers < ptr1->next->concurrentPlayers) {
                    swap(ptr1, ptr1->next);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

    void printList() {
        sortList();
        system("cls");
        cout << " \nBEST SELLING GAMES BASED ON CONCURRENT PLAYERS ON A 24-PEAK\n\n";
        Node* temp = head;
        int rank = 1;
        while (temp != nullptr) {
            cout << setw(2) << rank << ". " << left << setw(30) << temp->game << " " << setw(7) << right << temp->concurrentPlayers << " players" << endl;
            temp = temp->next;
            rank++;
        }
        cout << endl;
    }
};

void initializeGames(LinkedList& list) {
    list.insertSorted("The First Descendant", 239513);
    list.insertSorted("Elden Ring", 357856);
    list.insertSorted("Counter Strike", 1264256);
    list.insertSorted("Player Unknown Battlegrounds", 630656);
    list.insertSorted("Baldur's Gate 3", 93680);
    list.insertSorted("NARAKA: BLADEPOINT", 340240);
    list.insertSorted("Cyberpunk 2077", 34566);
    list.insertSorted("Destiny 2", 34423);
    list.insertSorted("Red Dead Redemption 2", 18924);
    list.insertSorted("Forza Horizon 4", 60340);
}

class Wishlist {
private:
    Node* head;

public:
    Wishlist() : head(nullptr) {}

    void insertAtBeginning(string newGame) {
        Node* newNode = new Node(newGame);
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(string newGame) {
        Node* newNode = new Node(newGame);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void insertAfter(string prevGame, string newGame) {
        Node* temp = head;
        while (temp != nullptr && temp->game != prevGame) {
            temp = temp->next;
        }
        if (temp != nullptr) {
            Node* newNode = new Node(newGame);
            newNode->next = temp->next;
            temp->next = newNode;
        }
        else {
            cout << "Previous node not found." << endl;
        }
    }

    void deleteNode(string gameName) {
        Node* temp = head;
        Node* prev = nullptr;

        if (temp != nullptr && temp->game == gameName) {
            head = temp->next;
            delete temp;
            return;
        }

        while (temp != nullptr && temp->game != gameName) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Node with game " << gameName << " not found." << endl;
            return;
        }

        prev->next = temp->next;
        delete temp;
    }

    void printWishlist() {
        system("cls");
        Node* temp = head;
        int rank = 1;
        while (temp != nullptr) {
            cout << rank << ". " << temp->game << endl;
            temp = temp->next;
            rank++;
        }
        cout << endl;
    }
};

void displayMainMenu() {
    cout << "     _____ __                          ______               ________               __       \n"
        "    / ___// /____  ____ _____ ___     /_  __/___  ____     / ____/ /_  ____ ______/ /______\n"
        "    \\__ \\/ __/ _ \\/ __ `/ __ `__ \\     / / / __ \\/ __ \\   / /   / __ \\/ __ `/ ___/ __/ ___/\n"
        "   ___/ / /_/  __/ /_/ / / / / / /    / / / /_/ / /_/ /  / /___/ / / / /_/ / /  / /_(__  ) \n"
        "  /____/\\__/\\___/\\__,_/_/ /_/ /_/    /_/  \\____/ .___/   \\____/_/ /_/\\__,_/_/   \\__/____/  \n"
        "                                              /_/                                          \n\n";
    cout << "\nMain Menu:\n";
    cout << "1. List Top Charts\n";
    cout << "2. Wishlist Menu\n";
    cout << "3. Admin Menu\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

void displayAdminMenu() {
    cout << "\nAdmin Menu:\n\n";
    cout << "1. Insert Game to Top Charts\n";
    cout << "2. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void displayWishlistMenu() {
    cout << "\nWISHLIST MENU:\n\n";
    cout << "1. Insert a Game at the Beginning\n";
    cout << "2. Insert a Game at the End of the list\n";
    cout << "3. Insert Game After a Game\n\n";
    cout << "4. Delete Game from Wishlist\n";
    cout << "5. See Wishlist\n";
    cout << "6. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

int main() {
    LinkedList list;
    Wishlist wishlist;
    initializeGames(list);
    int mainChoice, adminChoice, wishlistChoice;
    string value, afterValue;
    int players;

    while (true) {
        try {
            displayMainMenu();
            cin >> mainChoice;
            if (cin.fail()) throw invalid_argument("Invalid input");
            cin.ignore();

            switch (mainChoice) {
            case 1:
                list.printList();
                break;
            case 2:
                while (true) {
                    try {
                        displayWishlistMenu();
                        cin >> wishlistChoice;
                        if (cin.fail()) throw invalid_argument("Invalid input");
                        cin.ignore();

                        switch (wishlistChoice) {
                        case 1:
                            cout << "Enter game name to insert at beginning: ";
                            getline(cin, value);
                            wishlist.insertAtBeginning(value);
                            break;
                        case 2:
                            cout << "Enter game name to insert at end: ";
                            getline(cin, value);
                            wishlist.insertAtEnd(value);
                            break;
                        case 3:
                            cout << "Enter game name after which to insert: ";
                            getline(cin, afterValue);
                            cout << "Enter game name to insert: ";
                            getline(cin, value);
                            wishlist.insertAfter(afterValue, value);
                            break;
                        case 4:
                            cout << "Enter game name to delete: ";
                            getline(cin, value);
                            wishlist.deleteNode(value);
                            break;
                        case 5:
                            wishlist.printWishlist();
                            break;
                        case 6:
                            goto main_menu;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                        }
                    }
                    catch (const invalid_argument& e) {
                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
            case 3:
                while (true) {
                    try {
                        displayAdminMenu();
                        cin >> adminChoice;
                        if (cin.fail()) throw invalid_argument("Invalid input");
                        cin.ignore();

                        switch (adminChoice) {
                        case 1:
                            cout << "Enter game name to insert to charts: ";
                            getline(cin, value);
                            cout << "Enter number of concurrent players: ";
                            while (!(cin >> players) || players < 0) {
                                cout << "Invalid input. Please enter a positive integer: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cin.ignore();
                            list.insertAtEnd(value, players);
                            break;
                        case 2:
                            goto main_menu;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                        }
                    }
                    catch (const invalid_argument& e) {
                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
            case 4:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    main_menu:
        continue;
    }
}
