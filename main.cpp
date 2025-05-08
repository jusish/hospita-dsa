#include <iostream>
#include <limits>
#include "patient.h"
#include "doctor.h"
#include "appointment.h"
#include "utils.h"

// Global instances of our data structures
PatientsLL patientsLL;
DoctorsLL doctorsLL;
AppointmentsLL appointmentsLL;

void registerPatient()
{
    std::cout << printNiceHeader("PATIENT REGISTRATION") << std::endl;

    Patient newPatient;
    std::cout << "ID: ";
    std::cin >> newPatient.patient_id;

    while (!validateInteger(newPatient.patient_id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Please enter a valid integer for Patient ID." << std::endl;
        std::cin >> newPatient.patient_id;
    }

    while (patientsLL.exists(newPatient.patient_id))
    {
        std::cout << "Error: Patient with this ID already exists." << std::endl;
        std::cin >> newPatient.patient_id;
    }

    std::cin.ignore();
    std::cout << "NAME: ";
    std::getline(std::cin, newPatient.name);
    while (!validateString(newPatient.name))
    {
        std::cout << "Invalid name. Please enter a valid name: ";
        std::getline(std::cin, newPatient.name);
    }

    std::cout << "DoB (dd/mm/yyyy): ";
    std::getline(std::cin, newPatient.dob);
    while (!validateDate(newPatient.dob))
    {
        std::cout << "Invalid date. Please enter a valid date in dd/mm/yyyy format: ";
        std::getline(std::cin, newPatient.dob);
    }

    std::cout << "GENDER: ";
    std::getline(std::cin, newPatient.gender);
    while (!validateString(newPatient.gender))
    {
        std::cout << "Invalid input. Please enter a valid Gender: ";
        std::getline(std::cin, newPatient.gender);
    }

    newPatient.next = nullptr;
    patientsLL.addPatient(newPatient);
    std::cout << "Patient registered successfully!\n"
              << std::endl;
}

void registerDoctor()
{
    std::cout << printNiceHeader("DOCTOR REGISTRATION") << std::endl;

    Doctor newDoctor;
    std::cout << "ID: ";
    std::cin >> newDoctor.doctor_id;

    while (!validateInteger(newDoctor.doctor_id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Please enter a valid integer for Doctor ID." << std::endl;
        std::cin >> newDoctor.doctor_id;
    }

    while (doctorsLL.exists(newDoctor.doctor_id))
    {
        std::cout << "Error: Doctor with this ID already exists." << std::endl;
        std::cin >> newDoctor.doctor_id;
    }

    std::cin.ignore();
    std::cout << "NAME: ";
    std::getline(std::cin, newDoctor.name);
    while (!validateString(newDoctor.name))
    {
        std::cout << "Invalid name. Please enter a valid name: ";
        std::getline(std::cin, newDoctor.name);
    }

    std::cout << "SPECIALIZATION: ";
    std::getline(std::cin, newDoctor.specialization);
    while (!validateString(newDoctor.specialization))
    {
        std::cout << "Invalid specialization. Please enter a valid specialization: ";
        std::getline(std::cin, newDoctor.specialization);
    }

    newDoctor.next = nullptr;
    doctorsLL.addDoctor(newDoctor);
    std::cout << "Doctor registered successfully!\n"
              << std::endl;
}

void registerAppointment()
{
    std::cout << printNiceHeader("APPOINTMENT REGISTRATION") << std::endl;

    Appointment newAppointment;
    std::cout << "APPOINTMENT ID: ";
    std::cin >> newAppointment.appointment_id;

    while (!validateInteger(newAppointment.appointment_id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Please enter a valid integer for Appointment ID." << std::endl;
        std::cin >> newAppointment.appointment_id;
    }

    while (appointmentsLL.exists(newAppointment.appointment_id))
    {
        std::cout << "Error: Appointment with this ID already exists." << std::endl;
        std::cin >> newAppointment.appointment_id;
    }

    std::cout << "PATIENT ID: ";
    std::cin >> newAppointment.patient_id;
    while (!validateInteger(newAppointment.patient_id) || !patientsLL.exists(newAppointment.patient_id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (!validateInteger(newAppointment.patient_id))
        {
            std::cout << "Error: Please enter a valid integer for Patient ID." << std::endl;
        }
        else
        {
            std::cout << "Error: Patient with this ID does not exist." << std::endl;
        }
        std::cin >> newAppointment.patient_id;
    }

    std::cout << "DOCTOR ID: ";
    std::cin >> newAppointment.doctor_id;
    while (!validateInteger(newAppointment.doctor_id) || !doctorsLL.exists(newAppointment.doctor_id))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (!validateInteger(newAppointment.doctor_id))
        {
            std::cout << "Error: Please enter a valid integer for Doctor ID." << std::endl;
        }
        else
        {
            std::cout << "Error: Doctor with this ID does not exist." << std::endl;
        }
        std::cin >> newAppointment.doctor_id;
    }

    std::cin.ignore();
    std::cout << "DATE (dd/mm/yyyy): ";
    std::getline(std::cin, newAppointment.date);
    while (!validateDate(newAppointment.date))
    {
        std::cout << "Invalid date. Please enter a valid date in dd/mm/yyyy format: ";
        std::getline(std::cin, newAppointment.date);
    }

    newAppointment.next = nullptr;
    appointmentsLL.addAppointment(newAppointment);
    std::cout << "Appointment scheduled successfully!\n"
              << std::endl;
}

void displayMenu()
{
    std::cout << "\n====================================" << std::endl;
    std::cout << "   HOSPITAL MANAGEMENT SYSTEM" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "1. Register Patient" << std::endl;
    std::cout << "2. Register Doctor" << std::endl;
    std::cout << "3. Schedule Appointment" << std::endl;
    std::cout << "4. View All Patients" << std::endl;
    std::cout << "5. View All Doctors" << std::endl;
    std::cout << "6. View All Appointments" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Enter your choice (1-7): ";
}

int main()
{
    // Create data directory if it doesn't exist
    createDirectoryIfNotExists("data");

    int choice;
    while (true)
    {
        displayMenu();
        std::cin >> choice;

        if (!validateInteger(choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input. Please enter a number between 1-7." << std::endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            registerPatient();
            break;
        case 2:
            registerDoctor();
            break;
        case 3:
            registerAppointment();
            break;
        case 4:
            std::cout << printNiceHeader("PATIENT RECORDS") << std::endl;
            patientsLL.display();
            break;
        case 5:
            std::cout << printNiceHeader("DOCTOR RECORDS") << std::endl;
            doctorsLL.display();
            break;
        case 6:
            std::cout << printNiceHeader("APPOINTMENT SCHEDULE") << std::endl;
            appointmentsLL.display(patientsLL, doctorsLL);
            break;
        case 0:
            std::cout << "\nThank you for using the Hospital Management System. Goodbye!\n"
                      << std::endl;
            return 0;
        default:
            std::cout << "\nInvalid option. Please choose a number between 1-7." << std::endl;
        }
    }

    return 0;
}