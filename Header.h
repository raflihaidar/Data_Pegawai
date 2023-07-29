#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;


//Tipe data bentukan
struct Day{
    int day_number;
    string day_name;
};

struct Employee {
    string nama, position;
    int working_hours = 0;
    int jumlah_hari = 0;
    int id;
};

struct Schedule {
    string in, out;
    string gol;
    int time;
};

//Pointer
typedef struct Elm_employee *adr_employee;
typedef struct Elm_schedule *adr_schedule;
typedef struct Elm_relation *adr_relation;
typedef struct Elm_day *adr_day;

//List
struct List_employee {
    adr_employee first_employee;
    adr_employee last_employee;
};

struct List_schedule {
    adr_schedule first_schedule;
};

struct List_relation {
    adr_relation first_relation;
};

struct List_day {
    adr_day first_day;
};

//Elemen
struct Elm_employee {
    Employee info;
    adr_employee prev_elm;
    adr_employee next_elm;
    List_relation schedule;
};

struct Elm_schedule {
    Schedule info;
    adr_schedule next_elm;
};

struct Elm_day {
    Day info;
    adr_day next_elm;
};

struct Elm_relation {
    adr_schedule next_schedule;
    adr_relation next_relation;
    adr_day next_day;
};

//method

//initial
void createListEmployee(List_employee &e);
adr_employee createElmEmployee(Employee data);
void createListSchedule(List_schedule &s);
adr_schedule createElmSchedule(Schedule data);
void createListRelation(List_relation &r);
adr_relation createElmRelation();
void createListDay(List_day &d);
adr_day createElmDay();

//insert
void insertEmployee(List_employee &e, adr_employee p);
void insertSchedule(List_schedule &s, adr_schedule p);
void insertDay(List_day &d);
void addRelation(List_employee &e, List_schedule &s, List_day &d, int id, string gol, int day_number);

//searching
adr_employee searchEmployee(List_employee e, int id);
adr_schedule searchSchedule(List_schedule s, string gol);
adr_relation searchRelation(List_relation r, adr_schedule p);
adr_day searchDay(List_day d, int number_day);
void searchEmployeeFromSchedule(List_schedule s, List_employee e, string gol);
void searchScheduleFromEmployee(List_employee e, List_schedule s, List_relation r, int id);

//delete
void deleteEmployee(List_employee &e, int id);
void deleteSchedule(List_employee &e, List_schedule &s, string gol);
void deleteScheduleFromEmployee(List_employee &e, int id, string gol);

//view
void viewAll(List_employee e, List_day d);
void viewEmployee(List_employee e);
void viewSchedule(List_schedule s);
void viewDay(List_day d);
void showHighAndLowData(List_employee e);

//styling
void mainPage();
void greetings();
void handleError();
void gotoxy(int x, int y);
#endif // HEADER_H_INCLUDED
