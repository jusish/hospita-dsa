#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <fstream>

struct Patient
{
    int patient_id;
    std::string name;
    std::string dob;
    std::string gender;
    Patient *next;
};

class PatientsLL
{
private:
    Patient *head;
    const std::string dataFile = "data/patients.dat"; // File to store patient data

    void loadFromFile(); // Load data from file on startup
    void saveToFile();   // Save data to file when modified

public:
    PatientsLL();
    ~PatientsLL(); // Destructor to clean up memory

    void addPatient(const Patient &newPatient);
    bool exists(int patient_id) const;
    std::string getPatientName(int patient_id) const;
    void display() const;

    // File operations
    void saveData() const;
    void loadData();
};

#endif