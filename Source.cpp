#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;


bool isFileExists(const string& filename) {
    ifstream file(filename.c_str());
    return file.good();
}

void createAdminCredentials() {
    string username, password;
    cout << "Set up admin credentials:" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ofstream configFile("config.txt");
    if (configFile.is_open()) {
        configFile << username << endl;
        configFile << password << endl;
        configFile.close();
        cout << "Admin credentials set up successfully." << endl;
    } else {
        cerr << "Error: Could not create config file." << endl;
    }
}

bool authenticateAdmin() {
    string storedUsername, storedPassword;
    string inputUsername, inputPassword;

    ifstream configFile("config.txt");
    if (configFile.is_open()) {
        configFile >> storedUsername >> storedPassword;
        configFile.close();
        cout << "Enter admin credentials:" << endl;
        cout << "Username: ";
        cin >> inputUsername;
        cout << "Password: ";
        cin >> inputPassword;

        return (inputUsername == storedUsername && inputPassword == storedPassword);
    } 
    else {
        cerr << "Error: Config file not found. Run the program as an administrator to set up credentials." << endl;
        return false;
    }
}




class Hotel {
private:
    int roomNo;
    char name[30];
    char address[50];
    char phone[15];
    int days;
    float fare;

public:
    void mainMenu();
    void bookRoom();
    void displayCustomerRecord();
    void displayAllottedRooms();
    void editRecord();
    int checkRoomStatus(int);
    void modifyRecord(int);
    void deleteRecord(int);
};

void Hotel::mainMenu() {
    int choice;
    while (choice != 5) {
        system("cls");
        cout << "\n\t\t\t*************";
        cout << "\n\t\t\t* MAIN MENU *";
        cout << "\n\t\t\t*************";
        cout << "\n\n\n\t\t\t1. Book A Room";
        cout << "\n\t\t\t2. Customer Record";
        cout << "\n\t\t\t3. Rooms Allotted";
        cout << "\n\t\t\t4. Edit Record";
        cout << "\n\t\t\t5. Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                bookRoom();
                break;
            case 2:
                displayCustomerRecord();
                break;
            case 3:
                displayAllottedRooms();
                break;
            case 4:
                editRecord();
                break;
            case 5:
                break;
            default:
                cout << "\n\n\t\t\tWrong choice.....!!!";
                cout << "\n\t\t\tPress any key to continue....!!";
                cin.ignore();
                cin.get();
        }
    }
}


void Hotel::bookRoom() {
    system("cls");
    int r, flag;
    ofstream fout("Record.dat", ios::app | ios::binary);
    
    cout << "\n Enter Customer Details";
    cout << "\n ----------------------";
    cout << "\n\n Room no: ";
    cin >> r;
    flag = checkRoomStatus(r);
    if (flag) {
        cout << "\n Sorry..!!! Room is already booked";
    } else {
        roomNo = r;
        cin.ignore(); // Clear the newline character from the buffer
        cout << " Name: ";
        cin.getline(name, 30);
        cout << " Address: ";
        cin.getline(address, 50);
        cout << " Phone No: ";
        cin.getline(phone, 15);
        cout << " No of Days to Checkout: ";
        cin >> days;
        fare = days * 500; // 500 is the default price per day
        fout.write(reinterpret_cast<char*>(this), sizeof(Hotel));
        cout << "\n Room is booked...!!!";
    }

    cout << "\n Press any key to continue.....!!";
    cin.ignore(); // Clear the newline character from the buffer
    cin.get();
    fout.close();
}

void Hotel::displayCustomerRecord() {
    system("cls");
    ifstream fin("Record.dat", ios::in | ios::binary);
    int r, flag = 0;
    
    cout << "\n Enter room no: ";
    cin >> r;
    while (fin.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        if (roomNo == r) {
            system("cls");
            cout << "\n Customer Details";
            cout << "\n ----------------";
            cout << "\n\n Room no: " << roomNo;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone no: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            flag = 1;
            break;
        }
    }
    
    if (flag == 0) {
        cout << "\n Sorry Room no. not found or vacant....!!";
    }
    
    cout << "\n\n Press any key to continue....!!";
    cin.ignore(); // clearing newline char from buffer
    cin.get();
    fin.close();
}

void Hotel::displayAllottedRooms() {
    system("cls");
    ifstream fin("Record.dat", ios::in | ios::binary);
    cout << "\n\t\t\tList Of Rooms Allotted";
    cout << "\n\t\t\t----------------------";
    
    while (fin.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        cout << "\n Room no: " << roomNo << "\n Name: " << name;
        cout << "\n Address: " << address << "\n Phone: " << phone;
        cout << "\n Days: " << days << "\n Total: " << fare;
        cout << "\n**********************************";
    }
    
    cout << "\n\n\n\t\t\tPress any key to continue.....!!";
    cin.ignore(); // clear newline char from buffer
    cin.get();
    fin.close();
}

void Hotel::editRecord() {
    system("cls");
    int choice, r;
    cout << "\n EDIT MENU";
    cout << "\n ---------";
    cout << "\n\n 1. Modify Customer Record";
    cout << "\n 2. Delete Customer Record";
    cout << "\n Enter your choice: ";
    cin >> choice;

    cout << "\n Enter room no: ";
    cin >> r;

    switch (choice) {
        case 1:
            modifyRecord(r);
            break;
        case 2:
            deleteRecord(r);
            break;
        default:
            cout << "\n Wrong Choice.....!!";
            break;
    }

    cout << "\n Press any key to continue....!!!";
    cin.ignore(); // Clear the newline character from the buffer
    cin.get();
}

int Hotel::checkRoomStatus(int r) {
    ifstream fin("Record.dat", ios::in | ios::binary);
    int flag = 0;
    while (fin.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        if (roomNo == r) {
            flag = 1; // Room is booked
            break;
        }
    }
    fin.close();
    return flag;
}

void Hotel::modifyRecord(int r) {
    fstream file("Record.dat", ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0, ios::beg);
    int flag = 0;
    while (file.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        if (roomNo == r) {
            cout << "\n Enter New Details";
            cout << "\n -----------------";
            cin.ignore(); // Clear the newline character from the buffer
            cout << "\n Name: ";
            cin.getline(name, 30);
            cout << " Address: ";
            cin.getline(address, 50);
            cout << " Phone no: ";
            cin.getline(phone, 15);
            cout << " Days: ";
            cin >> days;
            fare = days * 900;
            file.seekp(file.tellg() - static_cast<streampos>(sizeof(Hotel)), ios::beg);
            file.write(reinterpret_cast<char*>(this), sizeof(Hotel));
            cout << "\n Record is modified....!!";
            flag = 1;
            break;
        }
    }
    file.close();
    if (flag == 0) {
        cout << "\n Sorry Room no. not found or vacant...!!";
    }
}

void Hotel::deleteRecord(int r) {
    ifstream fin("Record.dat", ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary);
    int flag = 0;
    while (fin.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        if (roomNo == r) {
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone No: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            cout << "\n\n Do you want to delete this record(y/n): ";
            char ch;
            cin >> ch;
            if (ch == 'n' || ch == 'N') {
                fout.write(reinterpret_cast<char*>(this), sizeof(Hotel));
            }
            flag = 1;
            break;
        } else {
            fout.write(reinterpret_cast<char*>(this), sizeof(Hotel));
        }
    }
    fin.close();
    fout.close();
    if (flag == 0) {
        cout << "\n Sorry room no. not found or vacant...!!";
    } else {
        remove("Record.dat");
        rename("temp.dat", "Record.dat");
    }
}





int main() {


    if (!isFileExists("config.txt")) createAdminCredentials();


    if (authenticateAdmin()) {
        cout << "Authentication successful. Admin access granted." << endl;
        Hotel h;
        h.mainMenu();

    } 

    else cout << "Authentication failed. Exiting the program." << endl;
    
   
    return 0;
}






















