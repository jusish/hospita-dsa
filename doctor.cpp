#include "doctor.h"
#include "utils.h"
#include <iostream>
#include <fstream>

DoctorsLL::DoctorsLL() : head(nullptr)
{
    loadFromFile(); // Load existing data when created
}

DoctorsLL::~DoctorsLL()
{
    saveToFile(); // Save data when destroyed
    // Clean up linked list
    Doctor *current = head;
    while (current != nullptr)
    {
        Doctor *next = current->next;
        delete current;
        current = next;
    }
}

void DoctorsLL::addDoctor(const Doctor &newDoctor)
{
    Doctor *newNode = new Doctor(newDoctor);
    newNode->next = head;
    head = newNode;
    saveToFile(); // Save after modification
}

bool DoctorsLL::exists(int doctor_id) const
{
    Doctor *current = head;
    while (current != nullptr)
    {
        if (current->doctor_id == doctor_id)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

std::string DoctorsLL::getDoctorName(int doctor_id) const
{
    Doctor *current = head;
    while (current != nullptr)
    {
        if (current->doctor_id == doctor_id)
        {
            return current->name;
        }
        current = current->next;
    }
    return "";
}

void DoctorsLL::display() const
{
    Doctor *current = head;
    while (current != nullptr)
    {
        std::cout << "Doctor ID: " << current->doctor_id
                  << ", Name: " << current->name
                  << ", Specialization: " << current->specialization << std::endl;
        current = current->next;
    }
}

void DoctorsLL::saveToFile()
{
    std::ofstream outFile(dataFile, std::ios::binary);
    if (!outFile)
    {
        std::cerr << "Error opening file for writing: " << dataFile << std::endl;
        return;
    }

    Doctor *current = head;
    while (current != nullptr)
    {
        outFile.write(reinterpret_cast<char *>(&current->doctor_id), sizeof(current->doctor_id));

        // Write strings with their lengths first
        size_t size = current->name.size();
        outFile.write(reinterpret_cast<char *>(&size), sizeof(size));
        outFile.write(current->name.c_str(), size);

        size = current->specialization.size();
        outFile.write(reinterpret_cast<char *>(&size), sizeof(size));
        outFile.write(current->specialization.c_str(), size);

        current = current->next;
    }
}

void DoctorsLL::loadFromFile()
{
    std::ifstream inFile(dataFile, std::ios::binary);
    if (!inFile)
    {
        // File doesn't exist yet - that's OK
        return;
    }

    // Clear existing list
    Doctor *current = head;
    while (current != nullptr)
    {
        Doctor *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;

    // Read from file
    while (inFile.peek() != EOF)
    {
        Doctor *newDoctor = new Doctor();

        inFile.read(reinterpret_cast<char *>(&newDoctor->doctor_id), sizeof(newDoctor->doctor_id));

        size_t size;
        inFile.read(reinterpret_cast<char *>(&size), sizeof(size));
        newDoctor->name.resize(size);
        inFile.read(&newDoctor->name[0], size);

        inFile.read(reinterpret_cast<char *>(&size), sizeof(size));
        newDoctor->specialization.resize(size);
        inFile.read(&newDoctor->specialization[0], size);

        newDoctor->next = head;
        head = newDoctor;
    }
}