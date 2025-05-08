#include "appointment.h"
#include "patient.h"
#include "doctor.h"
#include "utils.h"
#include <iostream>
#include <fstream>

AppointmentsLL::AppointmentsLL() : head(nullptr)
{
    loadFromFile(); // Load existing data when created
}

AppointmentsLL::~AppointmentsLL()
{
    saveToFile(); // Save data when destroyed
    // Clean up linked list
    Appointment *current = head;
    while (current != nullptr)
    {
        Appointment *next = current->next;
        delete current;
        current = next;
    }
}

void AppointmentsLL::addAppointment(const Appointment &newAppointment)
{
    Appointment *newNode = new Appointment(newAppointment);
    newNode->next = head;
    head = newNode;
    saveToFile(); // Save after modification
}

bool AppointmentsLL::exists(int appointment_id) const
{
    Appointment *current = head;
    while (current != nullptr)
    {
        if (current->appointment_id == appointment_id)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

void AppointmentsLL::display(const PatientsLL &patients, const DoctorsLL &doctors) const
{
    Appointment *current = head;
    while (current != nullptr)
    {
        std::cout << "Appointment ID: " << current->appointment_id
                  << ", Patient ID: " << current->patient_id
                  << ", Patient Name: " << patients.getPatientName(current->patient_id)
                  << ", Doctor ID: " << current->doctor_id
                  << ", Doctor Name: " << doctors.getDoctorName(current->doctor_id)
                  << ", Date: " << current->date << std::endl;
        current = current->next;
    }
}

void AppointmentsLL::saveToFile()
{
    std::ofstream outFile(dataFile, std::ios::binary);
    if (!outFile)
    {
        std::cerr << "Error opening file for writing: " << dataFile << std::endl;
        return;
    }

    Appointment *current = head;
    while (current != nullptr)
    {
        outFile.write(reinterpret_cast<char *>(&current->appointment_id), sizeof(current->appointment_id));
        outFile.write(reinterpret_cast<char *>(&current->patient_id), sizeof(current->patient_id));
        outFile.write(reinterpret_cast<char *>(&current->doctor_id), sizeof(current->doctor_id));

        // Write date string with its length first
        size_t size = current->date.size();
        outFile.write(reinterpret_cast<char *>(&size), sizeof(size));
        outFile.write(current->date.c_str(), size);

        current = current->next;
    }
}

void AppointmentsLL::loadFromFile()
{
    std::ifstream inFile(dataFile, std::ios::binary);
    if (!inFile)
    {
        // File doesn't exist yet - that's OK
        return;
    }

    // Clear existing list
    Appointment *current = head;
    while (current != nullptr)
    {
        Appointment *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;

    // Read from file
    while (inFile.peek() != EOF)
    {
        Appointment *newAppointment = new Appointment();

        inFile.read(reinterpret_cast<char *>(&newAppointment->appointment_id), sizeof(newAppointment->appointment_id));
        inFile.read(reinterpret_cast<char *>(&newAppointment->patient_id), sizeof(newAppointment->patient_id));
        inFile.read(reinterpret_cast<char *>(&newAppointment->doctor_id), sizeof(newAppointment->doctor_id));

        size_t size;
        inFile.read(reinterpret_cast<char *>(&size), sizeof(size));
        newAppointment->date.resize(size);
        inFile.read(&newAppointment->date[0], size);

        newAppointment->next = head;
        head = newAppointment;
    }
}