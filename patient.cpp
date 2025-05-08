#include "patient.h"
#include "utils.h"
#include <iostream>
#include <fstream>

PatientsLL::PatientsLL() : head(nullptr)
{
    loadFromFile(); // Load existing data when created
}

PatientsLL::~PatientsLL()
{
    saveToFile(); // Save data when destroyed
    // Clean up linked list
    Patient *current = head;
    while (current != nullptr)
    {
        Patient *next = current->next;
        delete current;
        current = next;
    }
}

void PatientsLL::addPatient(const Patient &newPatient)
{
    Patient *newNode = new Patient(newPatient);
    newNode->next = head;
    head = newNode;
    saveToFile(); // Save after modification
}

bool PatientsLL::exists(int patient_id) const
{
    Patient *current = head;
    while (current != nullptr)
    {
        if (current->patient_id == patient_id)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

std::string PatientsLL::getPatientName(int patient_id) const
{
    Patient *current = head;
    while (current != nullptr)
    {
        if (current->patient_id == patient_id)
        {
            return current->name;
        }
        current = current->next;
    }
    return "";
}

void PatientsLL::display() const
{
    Patient *current = head;
    while (current != nullptr)
    {
        std::cout << "Patient ID: " << current->patient_id
                  << ", Name: " << current->name
                  << ", DOB: " << current->dob
                  << ", Gender: " << current->gender << std::endl;
        current = current->next;
    }
}

void PatientsLL::saveToFile()
{
    std::ofstream outFile(dataFile, std::ios::binary);
    if (!outFile)
    {
        std::cerr << "Error opening file for writing: " << dataFile << std::endl;
        return;
    }

    Patient *current = head;
    while (current != nullptr)
    {
        outFile.write(reinterpret_cast<char *>(&current->patient_id), sizeof(current->patient_id));

        // Write strings with their lengths first
        size_t size = current->name.size();
        outFile.write(reinterpret_cast<char *>(&size), sizeof(size));
        outFile.write(current->name.c_str(), size);

        size = current->dob.size();
        outFile.write(reinterpret_cast<char *>(&size), sizeof(size));
        outFile.write(current->dob.c_str(), size);

        size = current->gender.size();
        outFile.write(reinterpret_cast<char *>(&size), sizeof(size));
        outFile.write(current->gender.c_str(), size);

        current = current->next;
    }
}

void PatientsLL::loadFromFile()
{
    std::ifstream inFile(dataFile, std::ios::binary);
    if (!inFile)
    {
        // File doesn't exist yet - that's OK
        return;
    }

    // Clear existing list
    Patient *current = head;
    while (current != nullptr)
    {
        Patient *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;

    // Read from file
    while (inFile.peek() != EOF)
    {
        Patient *newPatient = new Patient();

        inFile.read(reinterpret_cast<char *>(&newPatient->patient_id), sizeof(newPatient->patient_id));

        size_t size;
        inFile.read(reinterpret_cast<char *>(&size), sizeof(size));
        newPatient->name.resize(size);
        inFile.read(&newPatient->name[0], size);

        inFile.read(reinterpret_cast<char *>(&size), sizeof(size));
        newPatient->dob.resize(size);
        inFile.read(&newPatient->dob[0], size);

        inFile.read(reinterpret_cast<char *>(&size), sizeof(size));
        newPatient->gender.resize(size);
        inFile.read(&newPatient->gender[0], size);

        newPatient->next = head;
        head = newPatient;
    }
}