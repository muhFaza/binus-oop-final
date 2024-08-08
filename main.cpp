#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

// Subject Data Structure (Mata Pelajaran)
class Subject {
public:
    std::string name;
    int duration;
    bool practicum;

    Subject(std::string n, bool p) : name(n), practicum(p) {
        duration = p ? 120 : 60;
    }
};

// Teacher Data Structure (Guru)
class Teacher {
public:
    std::string name;
    std::string nuptk;
    Subject* subject;
    std::string educationLevel;

    Teacher(std::string n, std::string id, Subject* s, std::string edu) 
        : name(n), nuptk(id), subject(s), educationLevel(edu) {}
};

// Forward declaration
class Schedule;

// Student Data Structure (Siswa)
class Student {
public:
    std::string name;
    std::string nisn;
    Schedule* schedule;
    float avgScore;

    Student(std::string n, std::string id, Schedule* s, float avg) 
        : name(n), nisn(id), schedule(s), avgScore(avg) {}
};

// Schedule Data Structure (Jadwal)
class Schedule {
public:
    Subject* subject;
    Teacher* teacher;
    std::string startTime;

    Schedule(Subject* s, Teacher* t, std::string time) 
        : subject(s), teacher(t), startTime(time) {}
};

class SchoolManagementSystem {
private:
    std::vector<Student*> students;
    std::vector<Teacher*> teachers;
    std::vector<Subject*> subjects;
    std::vector<Schedule*> schedules;

    // Helper function to get input with spaces
    std::string getInputWithSpaces() {
        std::string input;
        std::getline(std::cin >> std::ws, input);
        return input;
    }

public:
    void addStudent(Student* student) { students.push_back(student); }
    void addTeacher(Teacher* teacher) { teachers.push_back(teacher); }
    void addSubject(Subject* subject) { subjects.push_back(subject); }
    void addSchedule(Schedule* schedule) { schedules.push_back(schedule); }

    void displayStudents() {
        std::cout << std::endl;
        std::cout << "Daftar Siswa:\n";
        for (size_t i = 0; i < students.size(); ++i) {
            std::cout << i+1 << ". " << students[i]->name 
                      << " - " << students[i]->nisn 
                      << " || Nilai avg: " << students[i]->avgScore;
            if (students[i]->schedule) {
                std::cout << ", Jadwal: " << students[i]->schedule->subject->name 
                          << "(" << students[i]->schedule->startTime << ")";
            }
            std::cout << std::endl;
        }
    }

    void displayTeachers() {
        std::cout << std::endl;
        std::cout << "Guru Tersedia:\n";
        for (size_t i = 0; i < teachers.size(); ++i) {
            std::cout << i+1 << ". " << teachers[i]->name << " - " << teachers[i]->subject->name << " - " << teachers[i]->educationLevel << std::endl;
        }
    }

    void displayTeachersDescending() {
        std::cout << std::endl;
        std::cout << "Guru Tersedia (Descending):\n";
        std::vector<Teacher*> sortedTeachers = teachers;
        std::sort(sortedTeachers.begin(), sortedTeachers.end(), 
            [](Teacher* a, Teacher* b) { return a->name > b->name; });
        
        for (size_t i = 0; i < sortedTeachers.size(); ++i) {
            std::cout << i+1 << ". " << sortedTeachers[i]->name << " - " << sortedTeachers[i]->nuptk 
                      << " - " << sortedTeachers[i]->subject->name << " - " << sortedTeachers[i]->educationLevel << std::endl;
        }
    }

    void displaySchedules() {
        std::cout << std::endl;
        std::cout << "Jadwal Tersedia:\n";
        for (size_t i = 0; i < schedules.size(); ++i) {
            std::cout << i+1 << ". " << schedules[i]->subject->name 
                      << " - " << schedules[i]->teacher->name
                      << " - " << schedules[i]->startTime << std::endl;
        }
    }

    void displaySchedulesAscending() {
        std::cout << std::endl;
        std::cout << "Jadwal Tersedia (Ascending):\n";
        std::vector<Schedule*> sortedSchedules = schedules;
        std::sort(sortedSchedules.begin(), sortedSchedules.end(), 
            [](Schedule* a, Schedule* b) { return a->subject->name < b->subject->name; });
        
        for (size_t i = 0; i < sortedSchedules.size(); ++i) {
            std::cout << i+1 << ". " << sortedSchedules[i]->subject->name 
                      << " - " << sortedSchedules[i]->teacher->name
                      << " - " << sortedSchedules[i]->startTime << std::endl;
        }
    }

    void displaySubjects() {
        std::cout << std::endl;
        std::cout << "Daftar Pelajaran:\n";
        for (size_t i = 0; i < subjects.size(); ++i) {
            std::cout << i+1 << ". " << subjects[i]->name 
                      << " || Durasi: " << subjects[i]->duration << " menit, "
                      << "Praktikum: "
                      << (subjects[i]->practicum ? "Ada" : "Tidak")
                      << std::endl;
        }
    }

    void addNewStudent() {
        displaySchedules();
        
        std::string name, nisn;
        int scheduleIndex;
        float avgScore;

        std::cout << "Masukkan nama siswa: ";
        name = getInputWithSpaces();
        std::cout << "Masukkan NISN: ";
        std::cin >> nisn;
        std::cout << "Masukkan nomor urutan jadwal: ";
        std::cin >> scheduleIndex;
        std::cout << "Masukkan nilai rata-rata: ";
        std::cin >> avgScore;

        if (scheduleIndex > 0 && scheduleIndex <= schedules.size()) {
            Student* newStudent = new Student(name, nisn, schedules[scheduleIndex-1], avgScore);
            students.push_back(newStudent);
            std::cout << "Siswa baru berhasil ditambahkan.\n";
        } else {
            std::cout << "Nomor urutan jadwal tidak valid.\n";
        }
    }

    void addNewTeacher() {
        displaySubjects();
        
        std::string name, nuptk, educationLevel;
        int subjectIndex;

        std::cout << "Masukkan nama guru: ";
        name = getInputWithSpaces();
        std::cout << "Masukkan NUPTK: ";
        std::cin >> nuptk;
        std::cout << "Masukkan nomor urutan pelajaran: ";
        std::cin >> subjectIndex;
        std::cout << "Masukkan tingkat pendidikan: ";
        educationLevel = getInputWithSpaces();

        if (subjectIndex > 0 && subjectIndex <= subjects.size()) {
            Teacher* newTeacher = new Teacher(name, nuptk, subjects[subjectIndex-1], educationLevel);
            teachers.push_back(newTeacher);
            std::cout << "Guru baru berhasil ditambahkan.\n";
        } else {
            std::cout << "Nomor urutan pelajaran tidak valid.\n";
        }
    }

    void addNewSubject() {
        std::string name;
        char hasPracticum;

        std::cout << std::endl;
        std::cout << "Masukkan nama pelajaran: ";
        name = getInputWithSpaces();
        std::cout << "Ada praktikum? (Y/N): ";
        std::cin >> hasPracticum;

        bool practicum = (hasPracticum == 'Y' || hasPracticum == 'y');
        Subject* newSubject = new Subject(name, practicum);
        subjects.push_back(newSubject);
        std::cout << "Pelajaran baru berhasil ditambahkan.\n";
    }

    void addNewSchedule() {
        displaySubjects();
        int subjectIndex;
        std::cout << "Masukkan nomor urutan pelajaran: ";
        std::cin >> subjectIndex;

        displayTeachers();
        int teacherIndex;
        std::cout << "Masukkan nomor urutan guru: ";
        std::cin >> teacherIndex;

        std::string startTime;
        std::cout << "Masukkan waktu pelaksanaan: ";
        std::cin >> startTime;

        if (subjectIndex > 0 && subjectIndex <= subjects.size() &&
            teacherIndex > 0 && teacherIndex <= teachers.size()) {
            Schedule* newSchedule = new Schedule(subjects[subjectIndex-1], teachers[teacherIndex-1], startTime);
            schedules.push_back(newSchedule);
            std::cout << "Jadwal baru berhasil ditambahkan.\n";
        } else {
            std::cout << "Nomor urutan pelajaran atau guru tidak valid.\n";
        }
    }

    void writeStudentsToFile() {
        std::ofstream file("siswa.txt");
        if (file.is_open()) {
            for (size_t i = 0; i < students.size(); ++i) {
                file << i+1 << ". Nama: " << students[i]->name 
                     << ", NISN: " << students[i]->nisn 
                     << ", Nilai rata-rata: " << students[i]->avgScore;
                if (students[i]->schedule) {
                    file << ", Jadwal: " << students[i]->schedule->subject->name 
                         << " - " << students[i]->schedule->teacher->name
                         << " (" << students[i]->schedule->startTime << ")";
                }
                file << std::endl;
            }
            file.close();
            std::cout << "Data siswa berhasil ditulis ke siswa.txt" << std::endl;
        } else {
            std::cout << "Tidak dapat membuka file siswa.txt" << std::endl;
        }
    }

    void writeTeachersToFile() {
        std::ofstream file("guru.txt");
        if (file.is_open()) {
            for (size_t i = 0; i < teachers.size(); ++i) {
                file << i+1 << ". Nama: " << teachers[i]->name 
                     << ", NUPTK: " << teachers[i]->nuptk 
                     << ", Mapel: " << teachers[i]->subject->name
                     << ", Pendidikan: " << teachers[i]->educationLevel
                     << std::endl;
            }
            file.close();
            std::cout << "Data guru berhasil ditulis ke guru.txt" << std::endl;
        } else {
            std::cout << "Tidak dapat membuka file guru.txt" << std::endl;
        }
    }
};

int main() {
    SchoolManagementSystem sms;

    // Create Dummy Subject
    Subject* math = new Subject("Matematika", false);
    Subject* ipa = new Subject("Ilmu Pengetahuan Alam", true);
    Subject* bahasa = new Subject("Bahasa Indonesia", false);

    // Create Dummy Teacher
    Teacher* mathTeacher = new Teacher("Budi", "12345", math, "S2");
    Teacher* ipaTeacher = new Teacher("Santi", "54321", ipa, "S1");
    Teacher* bahasaTeacher = new Teacher("Ridho", "44444", bahasa, "D3");

    // Create Dummy Schedule
    Schedule* kelasMath = new Schedule(math, mathTeacher, "10:00");
    Schedule* kelasIpa = new Schedule(ipa, ipaTeacher, "15:00");
    Schedule* kelasBahasa = new Schedule(bahasa, bahasaTeacher, "13:00");

    // Create Dummy Student
    Student* bahri = new Student("Bahri", "1111", kelasMath, 76);
    Student* bagas = new Student("Bagas", "2222", kelasIpa, 82);
    Student* brian = new Student("Brian", "3333", kelasBahasa, 94);

    // Add Dummy Data to sms
    sms.addSubject(math);
    sms.addSubject(ipa);
    sms.addSubject(bahasa);

    sms.addTeacher(mathTeacher);
    sms.addTeacher(ipaTeacher);
    sms.addTeacher(bahasaTeacher);

    sms.addSchedule(kelasMath);
    sms.addSchedule(kelasIpa);
    sms.addSchedule(kelasBahasa);

    sms.addStudent(bahri);
    sms.addStudent(bagas);
    sms.addStudent(brian);

    // Menu
    while (true) {
        std::cout << "\nSistem Manajemen Sekolah\n";
        std::cout << "1. Tampilkan Siswa\n";
        std::cout << "2. Tampilkan Guru\n";
        std::cout << "3. Tampilkan Jadwal\n";
        std::cout << "4. Tampilkan Pelajaran\n";
        std::cout << "5. Daftar Siswa Baru\n";
        std::cout << "6. Daftar Guru Baru\n";
        std::cout << "7. Daftar Pelajaran Baru\n";
        std::cout << "8. Daftar Jadwal Baru\n";
        std::cout << "9. Tulis Data Siswa ke File\n";
        std::cout << "10. Tulis Data Guru ke File\n";
        std::cout << "11. Keluar\n";
        std::cout << "Pilih menu: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                sms.displayStudents();
                break;
            case 2:
                sms.displayTeachersDescending();
                break;
            case 3:
                sms.displaySchedulesAscending();
                break;
            case 4:
                sms.displaySubjects();
                break;
            case 5:
                sms.addNewStudent();
                break;
            case 6:
                sms.addNewTeacher();
                break;
            case 7:
                sms.addNewSubject();
                break;
            case 8:
                sms.addNewSchedule();
                break;
            case 9:
                sms.writeStudentsToFile();
                break;
            case 10:
                sms.writeTeachersToFile();
                break;
            case 11:
                std::cout << "Terima kasih telah menggunakan sistem ini.\n";
                return 0;
            default:
                std::cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }


    // Jangan lupa untuk membersihkan memori di akhir program
    // (Ini hanya contoh sederhana, dalam praktiknya kamu mungkin perlu manajemen memori yang lebih baik)

    return 0;
}