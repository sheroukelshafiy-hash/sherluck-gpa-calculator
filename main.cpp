#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
struct Course { string name; int hours; string letter;double points;};
double letterToPoints(string l) {
    for (auto &x : l) x = toupper(x);
    if (l == "A+" || l == "A") return 4.0;
    if (l == "A-") return 3.7;
    if (l == "B+") return 3.3;
    if (l == "B")  return 3.0;
    if (l == "B-") return 2.7;
    if (l == "C+") return 2.3;
    if (l == "C")  return 2.0;
    if (l == "C-") return 1.7;
    if (l == "D+") return 1.3;
    if (l == "D")  return 1.0;
    return 0.0;}
bool cmp(Course x, Course y) {return x.points > y.points;}
double formatCollegeGPA(double val) {return floor(val * 100.0) / 100.0;}
int main() {
    int numSemesters;
    cout << "Enter total number of semesters: ";
    if (!(cin >> numSemesters) || numSemesters <= 0) return 0;
    double overall_points = 0.0; int overall_hours = 0;
    for (int sem = 1; sem <= numSemesters; ++sem) {
        vector<Course> courses;
        cout << "\n========================================================" << endl;
        cout << "                 >>> SEMESTER " << sem << " <<<                 " << endl;
        cout << "========================================================" << endl;
        cout << "Paste courses (Name Hours Grade) - Type 'end' to finish:" << endl;
 string name;
        while (cin >> name && name != "end") {
            Course temp;  temp.name = name;  double raw_h; cin >> raw_h >> temp.letter;
            for (auto &x : temp.letter) x = toupper(x);
            if (temp.letter == "P" || temp.letter == "NP" || temp.letter == "I" || temp.letter == "W" || temp.letter == "CON") { continue;}
            temp.hours = static_cast<int>(raw_h);
            temp.points = letterToPoints(temp.letter);
            courses.push_back(temp);}
        if (courses.empty()) continue;
        sort(courses.begin(), courses.end(), cmp);
        double sem_points = 0.0;
        int sem_hours = 0;
        cout << "\n+---------------------------------+-------+-------+--------+" << endl;
        cout << "| " << left << setw(31) << "Course Name" 
             << "| " << setw(5) << "Hours" 
             << "| " << setw(5) << "Grade" 
             << "| " << setw(6) << "Points" << " |" << endl;
        cout << "+---------------------------------+-------+-------+--------+" << endl;

        for (auto x : courses) {
            cout << "| " << left << setw(31) << x.name 
                 << "| " << setw(5) << x.hours 
                 << "| " << setw(5) << x.letter 
                 << "| " << setw(6) << fixed << setprecision(2) << x.points << " |" << endl;
            sem_points += (x.points * x.hours); sem_hours += x.hours;}
        cout << "+---------------------------------+-------+-------+--------+" << endl;
        double raw_gpa = (sem_hours > 0 ? sem_points / sem_hours : 0.0);
        double sem_gpa = formatCollegeGPA(raw_gpa);
        cout << "| Total Semester Hours: " << left << setw(10) << sem_hours 
             << " Semester GPA: " << fixed << setprecision(2) << setw(6) << sem_gpa << " |" << endl;
        cout << "+----------------------------------------------------------+\n" << endl;
        overall_points += sem_points;
        overall_hours += sem_hours; }
    cout << "\n========================================================" << endl;
    cout << "                    ACADEMIC SUMMARY                    " << endl;
    cout << "========================================================" << endl;
    double raw_cgpa = (overall_hours > 0 ? overall_points / overall_hours : 0.0);
    double cgpa = formatCollegeGPA(raw_cgpa);
    cout << " Total Cumulative Hours : " << overall_hours << endl;
    cout << " Cumulative CGPA        : " << fixed << setprecision(2) << cgpa << endl;
    if (cgpa < 2.0 && overall_hours > 0) {
        cout << " Status                 : [WARNING] Academic Probation" << endl;}
     else if (overall_hours > 0) {
        cout << " Status                 : Good Standing" << endl; }
    cout << "========================================================\n" << endl;
 return 0;}
