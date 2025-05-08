#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <fstream>
#include "patient.h"
#include "doctor.h"

struct Appointment
{
    int appointment_id;
    int patient_id;
    int doctor_id;
    std::string date;
    Appointment *next;
};

class AppointmentsLL
{
private:
    Appointment *head;
    const std::string dataFile = "appointments.dat"; // File to store appointment data

    void loadFromFile(); // Load data from file on startup
    void saveToFile();   // Save data to file when modified

public:
    AppointmentsLL();
    ~AppointmentsLL(); // Destructor to clean up memory

    void addAppointment(const Appointment &newAppointment);
    bool exists(int appointment_id) const;
    void display(const PatientsLL &patients, const DoctorsLL &doctors) const;

    // File operations
    void saveData() const;
    void loadData();
};

#endif