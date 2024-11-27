#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> 
#include <Windows.h>
using namespace std;

struct Note {
    char surname[50];
    char name[50];
    char phone_number[20];
    int birthday[3];
};

void addPerson(Note*& people, int& size) {
    Note newPerson;
    cout << "Введіть прізвище: ";
    cin.ignore();
    cin.getline(newPerson.surname, sizeof(newPerson.surname));
    cout << "Введіть ім'я: ";
    cin.getline(newPerson.name, sizeof(newPerson.name));
    cout << "Введіть номер телефону: ";
    cin.getline(newPerson.phone_number, sizeof(newPerson.phone_number));
    cout << "Введіть день народження (день, місяць, рік): ";
    cin >> newPerson.birthday[0] >> newPerson.birthday[1] >> newPerson.birthday[2];

    Note* temp = new Note[size + 1];
    for (int i = 0; i < size; ++i) {
        temp[i] = people[i];
    }
    temp[size] = newPerson;
    delete[] people;
    people = temp;
    size++;
}

void sortByPhoneNumber(Note* people, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (string(people[j].phone_number) > string(people[j + 1].phone_number)) {
                swap(people[j], people[j + 1]);
            }
        }
    }
    cout << "Масив відсортовано за номером телефону.\n";
}

void displayBySurname(Note* people, int size, const string& surname) {
    bool found = false;
    for (int i = 0; i < size; ++i) {
        if (string(people[i].surname) == surname) {
            cout << "Прізвище: " << people[i].surname
                << ", Ім'я: " << people[i].name
                << ", Номер телефону: " << people[i].phone_number
                << ", День народження: " << people[i].birthday[0] << "."
                << people[i].birthday[1] << "." << people[i].birthday[2] << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Людина з прізвищем " << surname << " не знайдена.\n";
    }
}

void saveToFile(Note* people, int size) {
    string filename;
    cout << "Введіть ім'я файлу для збереження: ";
    cin >> filename;

    ofstream file(filename, ios::out | ios::binary);
    if (!file) {
        cout << "Помилка відкриття файлу для запису.\n";
        return;
    }

    file.write(reinterpret_cast<char*>(&size), sizeof(size));
    file.write(reinterpret_cast<char*>(people), sizeof(Note) * size);
    file.close();

    cout << "Дані збережено у файл.\n";
}

void loadFromFile(Note*& people, int& size) {
    string filename;
    cout << "Введіть ім'я файлу для зчитування: ";
    cin >> filename;

    ifstream file(filename, ios::in | ios::binary);
    if (!file) {
        cout << "Помилка відкриття файлу для зчитування.\n";
        return;
    }

    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    delete[] people;
    people = new Note[size];
    file.read(reinterpret_cast<char*>(people), sizeof(Note) * size);
    file.close();

    cout << "Дані зчитано з файлу.\n";
}

void displayAllPeople(Note* people, int size) {
    if (size == 0) {
        cout << "Список користувачів порожній.\n";
        return;
    }

    cout << "+---------------------+----------------------+---------------------+------------------+\n";
    cout << "| Прізвище            | Ім'я                 | Номер телефону      | Дата народження  |\n";
    cout << "+---------------------+----------------------+---------------------+------------------+\n";

    for (int i = 0; i < size; ++i) {
        cout << "| " << setw(20) << left << people[i].surname
            << "| " << setw(21) << left << people[i].name
            << "| " << setw(20) << left << people[i].phone_number
            << "| " << setw(2) << setfill('0') << people[i].birthday[0] << "."
            << setw(2) << setfill('0') << people[i].birthday[1] << "."
            << setw(10) << setfill(' ') << people[i].birthday[2] << " |\n";
    }

    cout << "+---------------------+----------------------+---------------------+------------------+\n";
}

void displayMenu() {
    cout << "\n--- Меню ---\n";
    cout << "1. Додати дані про людину\n";
    cout << "2. Відсортувати за номером телефону\n";
    cout << "3. Пошук за прізвищем\n";
    cout << "4. Зберегти дані у файл\n";
    cout << "5. Зчитати дані з файлу\n";
    cout << "6. Вивести всіх користувачів у вигляді таблиці\n";
    cout << "7. Вийти\n";
    cout << "Виберіть опцію: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Note* people = nullptr;
    int size = 0;
    bool running = true;

    while (running) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            addPerson(people, size);
            break;
        case 2:
            sortByPhoneNumber(people, size);
            break;
        case 3: {
            string surname;
            cout << "Введіть прізвище для пошуку: ";
            cin >> surname;
            displayBySurname(people, size, surname);
            break;
        }
        case 4:
            saveToFile(people, size);
            break;
        case 5:
            loadFromFile(people, size);
            break;
        case 6:
            displayAllPeople(people, size);
            break;
        case 7:
            running = false;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }

    delete[] people;
    return 0;
}
