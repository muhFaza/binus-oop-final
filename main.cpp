using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

// Forward declaration
class Schedule;
class Subject;

// Student Data Structure (Siswa)
class Student {
public:
    string name;
    string nisn;
    Schedule* schedule;
    float avgScore;

    Student(string n, string id, Schedule* s, float avg) 
        : name(n), nisn(id), schedule(s), avgScore(avg) {}
};

// Teacher Data Structure (Guru)
class Teacher {
public:
    string name;
    string nuptk;
    Subject* subject;
    string educationLevel;

    Teacher(string n, string id, Subject* s, string edu) 
        : name(n), nuptk(id), subject(s), educationLevel(edu) {}
};

// Subject Data Structure (Mata Pelajaran)
class Subject {
public:
    string name;
    int duration;
    bool practicum;

    Subject(string n, bool p) : name(n), practicum(p) {
        duration = p ? 120 : 60;
    }
};

// Schedule Data Structure (Jadwal)
class Schedule {
public:
    Subject* subject;
    Teacher* teacher;
    string startTime;

    Schedule(Subject* s, Teacher* t, string time) 
        : subject(s), teacher(t), startTime(time) {}
};

class SchoolManagementSystem {
private:
    vector<Student*> students;
    vector<Teacher*> teachers;
    vector<Subject*> subjects;
    vector<Schedule*> schedules;

    // Helper function to get input with spaces
    string getInputWithSpaces() {
        string input;
        getline(cin >> ws, input);
        return input;
    }

public:
    void addStudent(Student* student) { students.push_back(student); }
    void addTeacher(Teacher* teacher) { teachers.push_back(teacher); }
    void addSubject(Subject* subject) { subjects.push_back(subject); }
    void addSchedule(Schedule* schedule) { schedules.push_back(schedule); }

    void displayStudents() {
        cout << endl;
        cout << "Daftar Siswa:\n";
        for (size_t i = 0; i < students.size(); ++i) {
            cout << i+1 << ". " << students[i]->name 
                      << " - " << students[i]->nisn 
                      << " || Nilai avg: " << students[i]->avgScore;
            if (students[i]->schedule) {
                cout << ", Jadwal: " << students[i]->schedule->subject->name 
                          << "(" << students[i]->schedule->startTime << ")";
            }
            cout << endl;
        }
    }

    void displayTeachers() {
        cout << endl;
        cout << "Guru Tersedia:\n";
        for (size_t i = 0; i < teachers.size(); ++i) {
            cout << i+1 << ". " << teachers[i]->name << " - " << teachers[i]->subject->name << " - " << teachers[i]->educationLevel << endl;
        }
    }

    void displayTeachersDescending() {
        cout << endl;
        cout << "Guru Tersedia (Descending):\n";
        vector<Teacher*> sortedTeachers = teachers;
        sort(sortedTeachers.begin(), sortedTeachers.end(), 
            [](Teacher* a, Teacher* b) { return a->name > b->name; });
        
        for (size_t i = 0; i < sortedTeachers.size(); ++i) {
            cout << i+1 << ". " << sortedTeachers[i]->name << " - " << sortedTeachers[i]->nuptk 
                      << " - " << sortedTeachers[i]->subject->name << " - " << sortedTeachers[i]->educationLevel << endl;
        }
    }

    void displaySchedules() {
        cout << endl;
        cout << "Jadwal Tersedia:\n";
        for (size_t i = 0; i < schedules.size(); ++i) {
            cout << i+1 << ". " << schedules[i]->subject->name 
                      << " - " << schedules[i]->teacher->name
                      << " - " << schedules[i]->startTime << endl;
        }
    }

    void displaySchedulesAscending() {
        cout << endl;
        cout << "Jadwal Tersedia (Ascending):\n";
        vector<Schedule*> sortedSchedules = schedules;
        sort(sortedSchedules.begin(), sortedSchedules.end(), 
            [](Schedule* a, Schedule* b) { return a->subject->name < b->subject->name; });
        
        for (size_t i = 0; i < sortedSchedules.size(); ++i) {
            cout << i+1 << ". " << sortedSchedules[i]->subject->name 
                      << " - " << sortedSchedules[i]->teacher->name
                      << " - " << sortedSchedules[i]->startTime << endl;
        }
    }

    void displaySubjects() {
        cout << endl;
        cout << "Daftar Pelajaran:\n";
        for (size_t i = 0; i < subjects.size(); ++i) {
            cout << i+1 << ". " << subjects[i]->name 
                      << " || Durasi: " << subjects[i]->duration << " menit, "
                      << "Praktikum: "
                      << (subjects[i]->practicum ? "Ada" : "Tidak")
                      << endl;
        }
    }

    void displaySubjectsAscending() {
        cout << endl;
        cout << "Daftar Pelajaran (Ascending):\n";
        
        vector<Subject*> sortedSubjects = subjects;
        
        sort(sortedSubjects.begin(), sortedSubjects.end(), 
            [](Subject* a, Subject* b) { return a->name < b->name; });
        
        for (size_t i = 0; i < sortedSubjects.size(); ++i) {
            cout << i+1 << ". " << sortedSubjects[i]->name 
                    << " || Durasi: " << sortedSubjects[i]->duration << " menit, "
                    << "Praktikum: "
                    << (sortedSubjects[i]->practicum ? "Ada" : "Tidak")
                    << endl;
        }
    }

    void displaySchedulesBySubject(int subjectIndex) {
        if (subjectIndex > 0 && subjectIndex <= subjects.size()) {
            Subject* selectedSubject = subjects[subjectIndex - 1];
            cout << "\nJadwal untuk " << selectedSubject->name << ":\n";
            bool found = false;
            int num = 0;
            for (size_t i = 0; i < schedules.size(); ++i) {
                if (schedules[i]->subject == selectedSubject) {
                    cout << num+1 << ". " << schedules[i]->teacher->name
                            << " - " << schedules[i]->startTime << endl;
                    found = true;
                    num++;
                }
            }
            if (!found) {
                cout << "Tidak ada jadwal untuk mata pelajaran ini.\n";
            }
        } else {
            cout << "Nomor urutan pelajaran tidak valid.\n";
        }
    }

    void addNewStudent() {
        displaySchedules();
        
        string name, nisn;
        int scheduleIndex;
        float avgScore;

        cout << "Masukkan nama siswa: ";
        name = getInputWithSpaces();
        cout << "Masukkan NISN: ";
        cin >> nisn;
        cout << "Masukkan nomor urutan jadwal: ";
        cin >> scheduleIndex;
        cout << "Masukkan nilai rata-rata: ";
        cin >> avgScore;

        if (scheduleIndex > 0 && scheduleIndex <= schedules.size()) {
            Student* newStudent = new Student(name, nisn, schedules[scheduleIndex-1], avgScore);
            students.push_back(newStudent);
            cout << "Siswa baru berhasil ditambahkan.\n";
        } else {
            cout << "Nomor urutan jadwal tidak valid.\n";
        }
    }

    void addNewTeacher() {
        displaySubjects();
        
        string name, nuptk, educationLevel;
        int subjectIndex;

        cout << "Masukkan nama guru: ";
        name = getInputWithSpaces();
        cout << "Masukkan NUPTK: ";
        cin >> nuptk;
        cout << "Masukkan nomor urutan pelajaran: ";
        cin >> subjectIndex;
        cout << "Masukkan tingkat pendidikan: ";
        educationLevel = getInputWithSpaces();

        if (subjectIndex > 0 && subjectIndex <= subjects.size()) {
            Teacher* newTeacher = new Teacher(name, nuptk, subjects[subjectIndex-1], educationLevel);
            teachers.push_back(newTeacher);
            cout << "Guru baru berhasil ditambahkan.\n";
        } else {
            cout << "Nomor urutan pelajaran tidak valid.\n";
        }
    }

    void addNewSubject() {
        string name;
        char hasPracticum;

        cout << endl;
        cout << "Masukkan nama pelajaran: ";
        name = getInputWithSpaces();
        cout << "Ada praktikum? (Y/N): ";
        cin >> hasPracticum;

        bool practicum = (hasPracticum == 'Y' || hasPracticum == 'y');
        Subject* newSubject = new Subject(name, practicum);
        subjects.push_back(newSubject);
        cout << "Pelajaran baru berhasil ditambahkan.\n";
    }

    void addNewSchedule() {
        displaySubjects();
        int subjectIndex;
        cout << "Masukkan nomor urutan pelajaran: ";
        cin >> subjectIndex;

        displayTeachers();
        int teacherIndex;
        cout << "Masukkan nomor urutan guru: ";
        cin >> teacherIndex;

        string startTime;
        cout << "Masukkan waktu pelaksanaan: ";
        cin >> startTime;

        if (subjectIndex > 0 && subjectIndex <= subjects.size() &&
            teacherIndex > 0 && teacherIndex <= teachers.size()) {
            Schedule* newSchedule = new Schedule(subjects[subjectIndex-1], teachers[teacherIndex-1], startTime);
            schedules.push_back(newSchedule);
            cout << "Jadwal baru berhasil ditambahkan.\n";
        } else {
            cout << "Nomor urutan pelajaran atau guru tidak valid.\n";
        }
    }

    void writeStudentsToFile() {
        ofstream file("siswa.txt");
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
                file << endl;
            }
            file.close();
            cout << "Data siswa berhasil ditulis ke siswa.txt" << endl;
        } else {
            cout << "Tidak dapat membuka file siswa.txt" << endl;
        }
    }

    void writeTeachersToFile() {
        ofstream file("guru.txt");
        if (file.is_open()) {
            for (size_t i = 0; i < teachers.size(); ++i) {
                file << i+1 << ". Nama: " << teachers[i]->name 
                     << ", NUPTK: " << teachers[i]->nuptk 
                     << ", Mapel: " << teachers[i]->subject->name
                     << ", Pendidikan: " << teachers[i]->educationLevel
                     << endl;
            }
            file.close();
            cout << "Data guru berhasil ditulis ke guru.txt" << endl;
        } else {
            cout << "Tidak dapat membuka file guru.txt" << endl;
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
        cout << "\nSistem Manajemen Sekolah\n";
        cout << "1. Tampilkan Siswa\n";
        cout << "2. Tampilkan Guru\n";
        cout << "3. Tampilkan Jadwal\n";
        cout << "4. Tampilkan Pelajaran\n";
        cout << "5. Daftar Siswa Baru\n";
        cout << "6. Daftar Guru Baru\n";
        cout << "7. Daftar Pelajaran Baru\n";
        cout << "8. Daftar Jadwal Baru\n";
        cout << "9. Tulis Data Siswa ke File\n";
        cout << "10. Tulis Data Guru ke File\n";
        cout << "11. Keluar\n";
        cout << "Pilih menu: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                sms.displayStudents();
                break;
            case 2:
                sms.displayTeachersDescending();
                break;
            case 3: {
                int scheduleChoice;
                cout << "\nPilih opsi:\n";
                cout << "1. Semua Jadwal\n";
                cout << "2. Cari berdasarkan mata pelajaran\n";
                cout << "Pilihan Anda: ";
                cin >> scheduleChoice;

                if (scheduleChoice == 1) {
                    sms.displaySchedulesAscending();
                } else if (scheduleChoice == 2) {
                    sms.displaySubjects();
                    int subjectIndex;
                    cout << "Masukkan nomor urutan pelajaran: ";
                    cin >> subjectIndex;
                    sms.displaySchedulesBySubject(subjectIndex);
                } else {
                    cout << "Pilihan tidak valid.\n";
                }
                break;
            }
            case 4:
                sms.displaySubjectsAscending();
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
                cout << "Terima kasih telah menggunakan sistem ini.\n";
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }

    return 0;
}