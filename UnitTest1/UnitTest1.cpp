#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <cstring>
#include "../lab-12.4/lab-12.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestAddPerson)
        {
            Note* people = nullptr;
            int size = 0;

           
            Note newPerson = { "Ivanov", "Ivan", "1234567890", {1, 1, 1990} };
            Note* temp = new Note[size + 1];
            temp[size] = newPerson;
            delete[] people;
            people = temp;
            size++;

            Assert::AreEqual(size, 1);
            Assert::AreEqual(strcmp(people[0].surname, "Ivanov"), 0);
            Assert::AreEqual(strcmp(people[0].name, "Ivan"), 0);
            Assert::AreEqual(strcmp(people[0].phone_number, "1234567890"), 0);
            Assert::AreEqual(people[0].birthday[0], 1);
            Assert::AreEqual(people[0].birthday[1], 1);
            Assert::AreEqual(people[0].birthday[2], 1990);

            delete[] people;
        }

        TEST_METHOD(TestSortByPhoneNumber)
        {
            Note people[3] = {
                { "Ivanov", "Ivan", "2345678901", {1, 1, 1990} },
                { "Petrov", "Petr", "1234567890", {15, 5, 1985} },
                { "Sidorov", "Sidr", "3456789012", {10, 10, 1980} }
            };

            sortByPhoneNumber(people, 3);

            Assert::AreEqual(strcmp(people[0].phone_number, "1234567890"), 0);
            Assert::AreEqual(strcmp(people[1].phone_number, "2345678901"), 0);
            Assert::AreEqual(strcmp(people[2].phone_number, "3456789012"), 0);
        }

        TEST_METHOD(TestSaveAndLoadFile)
        {
            Note people[2] = {
                { "Ivanov", "Ivan", "1234567890", {1, 1, 1990} },
                { "Petrov", "Petr", "2345678901", {15, 5, 1985} }
            };

            int size = 2;

            
            string filename = "testfile.bin";
            ofstream outFile(filename, ios::binary);
            outFile.write(reinterpret_cast<char*>(&size), sizeof(size));
            outFile.write(reinterpret_cast<char*>(people), sizeof(Note) * size);
            outFile.close();

            
            Note* loadedPeople = nullptr;
            int loadedSize = 0;

            ifstream inFile(filename, ios::binary);
            inFile.read(reinterpret_cast<char*>(&loadedSize), sizeof(loadedSize));
            loadedPeople = new Note[loadedSize];
            inFile.read(reinterpret_cast<char*>(loadedPeople), sizeof(Note) * loadedSize);
            inFile.close();

            Assert::AreEqual(size, loadedSize);
            Assert::AreEqual(strcmp(loadedPeople[0].surname, "Ivanov"), 0);
            Assert::AreEqual(strcmp(loadedPeople[1].surname, "Petrov"), 0);

            delete[] loadedPeople;
        }

        TEST_METHOD(TestDisplayBySurname)
        {
            Note people[2] = {
                { "Ivanov", "Ivan", "1234567890", {1, 1, 1990} },
                { "Petrov", "Petr", "2345678901", {15, 5, 1985} }
            };

            string surname = "Ivanov";
            bool found = false;
            for (int i = 0; i < 2; ++i) {
                if (string(people[i].surname) == surname) {
                    found = true;
                    Assert::AreEqual(strcmp(people[i].name, "Ivan"), 0);
                    Assert::AreEqual(people[i].birthday[0], 1);
                    Assert::AreEqual(people[i].birthday[1], 1);
                    Assert::AreEqual(people[i].birthday[2], 1990);
                    break;
                }
            }
            Assert::IsTrue(found);
        }
    };
}
