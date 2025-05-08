#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <fstream>

struct Doctor
{
    int doctor_id;
    std::string name;
    std::string specialization;
    Doctor *next;
};

class DoctorsLL
{
private:
    Doctor *head;
    const std::string dataFile = "doctors.dat"; // File to store doctor data

    void loadFromFile(); // Load data from file on startup
    void saveToFile();   // Save data to file when modified

public:
    DoctorsLL();
    ~DoctorsLL(); // Destructor to clean up memory

    void addDoctor(const Doctor &newDoctor);
    bool exists(int doctor_id) const;
    std::string getDoctorName(int doctor_id) const;
    void display() const;

    // File operations
    void saveData() const;
    void loadData();
};

#endif