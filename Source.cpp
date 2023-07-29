#include "Header.h"
#include <iostream>
#include <string.h>
#include <iomanip>
#include <conio.h>
#include <windows.h>

using namespace std;

string day_info[] =
{
    "Selasa",
    "Rabu",
    "Kamis",
    "Jumat",
    "Sabtu",
    "Minggu"
};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void createListEmployee(List_employee &e)
{
    e.first_employee = NULL;
}

void createListSchedule(List_schedule &s)
{
    s.first_schedule = NULL;
}

void createListRelation(List_relation &r)
{
    r.first_relation = NULL;
}
void createListDay(List_day &d)
{
    adr_day p = createElmDay();
    p->info.day_number = 1;
    p->info.day_name = "Senin";
    d.first_day = p;
    insertDay(d);
}

adr_employee createElmEmployee(Employee data)
{
    adr_employee p = new Elm_employee;
    p->info = data;
    p->next_elm = NULL;
    p->schedule.first_relation = NULL;
    return p;
}
adr_schedule createElmSchedule(Schedule data)
{
    adr_schedule p = new Elm_schedule;
    p->info = data;
    p->next_elm = NULL;
    return p;
}

adr_relation createElmRelation()
{
    adr_relation r = new Elm_relation;
    r->next_schedule = NULL;
    r->next_relation = NULL;
    return r;
}

adr_day createElmDay()
{
    adr_day d = new Elm_day;
    d->next_elm = NULL;
    return d;
}

//insert first
void insertEmployee(List_employee &e, adr_employee p)
{
    if(e.first_employee == NULL)
    {
        e.first_employee = p;
        e.last_employee = p;
    }
    else
    {
        adr_employee q = e.first_employee;
        bool data_exist = false;
        while(q != NULL){
            if(q->info.nama == p->info.nama || q->info.position == p->info.position){
                data_exist = true;
                break;
            }
            q = q->next_elm;
        }
        if(!data_exist){
            q = e.first_employee;
            p->next_elm = q;
            p->prev_elm = NULL;
            q->prev_elm = p;
            e.first_employee = p;
        }else{
            cout << "\t\t\tData Pegawai Sudah Tersedia" << endl;
            system("pause");
        }
    }
    system("cls");
    viewEmployee(e);
}

//insert last
void insertSchedule(List_schedule &s, adr_schedule p)
{
    if (s.first_schedule == NULL)
    {
        s.first_schedule = p;
    }
    else
    {
        adr_schedule q = s.first_schedule;
        bool dataExists = false;

        while (q != NULL)
        {
            if (q->info.gol == p->info.gol || q->info.in == p->info.in || q->info.out == p->info.out)
            {
                dataExists = true;
                break;
            }
            q = q->next_elm;
        }

        if (!dataExists)
        {
            q = s.first_schedule;
            while (q->next_elm != NULL)
            {
                q = q->next_elm;
            }
            q->next_elm = p;
        }
        else
        {
            cout << "\t\t\tData Sudah Tersedia" << endl;
            system("pause");
        }
    }

    system("cls");
    viewSchedule(s);
}


void insertDay(List_day &d)
{
    adr_day p = d.first_day;
    for(int i = 0; i < 6; i++)
    {
        adr_day d = createElmDay();
        d->info.day_number = i + 2;
        d->info.day_name = day_info[i];
        while(p->next_elm != NULL)
        {
            p = p->next_elm;
        }
        p->next_elm = d;
    }
}

adr_employee searchEmployee(List_employee e, int id)
{
    adr_employee p = e.first_employee;
    while((p->next_elm != NULL) && (p->info.id != id))
    {
        p = p->next_elm;
    }
    if(p->info.id == id)
    {
        return p;
    }
    else
    {
        return NULL;
    }
}

adr_schedule searchSchedule(List_schedule s, string gol)
{
    adr_schedule p = s.first_schedule;
    while((p->next_elm != NULL) && (p->info.gol != gol))
    {
        p = p->next_elm;
    }
    if(p->info.gol == gol)
    {
        return p;
    }
    else
    {
        return NULL;
    }
}

adr_day searchDay(List_day d, int number_day)
{
    adr_day p = d.first_day;
    while((p->next_elm != NULL) && (p->info.day_number != number_day))
    {
        p = p->next_elm;
    }
    if(p->info.day_number == number_day)
    {
        return p;
    }
    else
    {
        return NULL;
    }
}

adr_relation searchRelation(List_relation r, adr_schedule p)
{
    adr_relation q = r.first_relation;
    while((q->next_relation != NULL) && (q->next_schedule != p))
    {
        q = q->next_relation;
    }
    if(q->next_schedule == p)
    {
        return q;
    }
    else
    {
        return NULL;
    }
}

void searchEmployeeFromSchedule(List_schedule s, List_employee e, string gol)
{
    adr_schedule p = searchSchedule(s, gol);
    if(p != NULL)
    {
        adr_employee q = e.first_employee;
        do
        {
            if(q->schedule.first_relation != NULL)
            {
                adr_relation r = searchRelation(q->schedule, p);
                if(r != NULL)
                {
                    cout << "\n\t\t\tId \t\t\t: " << q->info.id << endl;
                    cout << "\t\t\tNama \t\t\t: " << q->info.nama << endl;
                    cout << "\t\t\tPosisi \t\t\t: " << q->info.position << endl;
                    cout << "\t\t\tHari Kerja \t\t: " << r->next_day->info.day_name << endl;
                    cout << endl;
                }
            }
            q = q->next_elm;
        }
        while(q != NULL);
    }

}

void searchScheduleFromEmployee(List_employee e, List_schedule s, List_relation r, int id)
{
    adr_employee p = searchEmployee(e, id);
    if(p != NULL)
    {
        if(p->schedule.first_relation != NULL)
        {
            adr_relation q = p->schedule.first_relation;
            while(q->next_relation != NULL)
            {
                cout << "\n\t\t\tJenis Shift \t: " << q->next_schedule->info.gol << endl;
                cout << "\t\t\tJam Masuk \t: " << setfill('0') << setw(2) << q->next_schedule->info.in  << ".00"<< endl;
                cout << "\t\t\tJam Keluar \t: " << setfill('0') << setw(2) << q->next_schedule->info.out  << ".00"<< endl;
                cout << "\t\t\tWaktu \t\t: " << q->next_schedule->info.time << " Jam" << endl;
                cout << "\t\t\tHari Kerja \t: " << q->next_day->info.day_name << endl;
                cout << endl;

                q = q->next_relation;
            }
            cout << "\n\t\t\tJenis Shift \t: " << q->next_schedule->info.gol << endl;
            cout << "\t\t\tJam Masuk \t: " << setfill('0') << setw(2) << q->next_schedule->info.in  << ".00"<< endl;
            cout << "\t\t\tJam Keluar \t: " << setfill('0') << setw(2) << q->next_schedule->info.out  << ".00"<< endl;
            cout << "\t\t\tWaktu \t\t: " << q->next_schedule->info.time << " Jam" << endl;
            cout << "\t\t\tHari Kerja \t: " << q->next_day->info.day_name << endl;

        }
        else
        {
            handleError();
        }
    }
}

void addRelation(List_employee &e, List_schedule &s, List_day &d, int id, string gol, int day_number)
{
    adr_employee p = searchEmployee(e, id);
    adr_schedule q = searchSchedule(s, gol);
    adr_day dd = searchDay(d, day_number);

    if((p != NULL) && (q != NULL) && (dd != NULL))
    {
        adr_relation r = createElmRelation();
        r->next_schedule = q;
        r->next_day = dd;
        if(p->schedule.first_relation == NULL)
        {
            p->info.working_hours = r->next_schedule->info.time;
            p->schedule.first_relation = r;
            p->info.jumlah_hari = 1;
        }
        else
        {
            adr_relation t = p->schedule.first_relation;
            while(t->next_relation != NULL)
            {
                t = t->next_relation;
            }
            if(t->next_day->info.day_number != day_number)
            {
                t->next_relation = r;
                p->info.jumlah_hari++;
                p->info.working_hours += r->next_schedule->info.time;
            }
            else
            {
                cout << "\t\t\tShift di hari " << r->next_day->info.day_name << " Sudah tersedia" << endl;
                cout <<"\t\t\tSilahkan coba lagi" << endl;
                system("\t\t\tpause");
            }
        }
    }
    system("cls");
    viewAll(e, d);
}

void deleteEmployee(List_employee &e, int id)
{
    adr_employee p = searchEmployee(e, id);
    if(p != NULL)
    {
        p->schedule.first_relation = NULL;
        if(p == e.first_employee)
        {
            e.first_employee = p->next_elm;
            e.last_employee = p->next_elm;
            p->next_elm = NULL;
        }
        else
        {
            adr_employee q = e.first_employee;
            while(q->next_elm != p)
            {
                q = q->next_elm;
            }
            q->next_elm = p->next_elm;
            p->next_elm = NULL;
            p->prev_elm = NULL;
        }
    }
    system("cls");
    viewEmployee(e);
}

void deleteScheduleFromEmployee(List_employee &e, int id, string gol)
{
    adr_employee p = searchEmployee(e, id);
    if(p != NULL)
    {
        if(p->schedule.first_relation != NULL)
        {
            adr_relation r = p->schedule.first_relation;
            adr_relation rr = p->schedule.first_relation;
            while(r->next_schedule->info.gol != gol && r->next_relation != NULL)
            {
                rr = r;
                r = r->next_relation;
            }
            if(r->next_schedule->info.gol == gol)
            {
                if(r == p->schedule.first_relation)
                {
                    p->schedule.first_relation = r->next_relation;
                    r->next_relation = NULL;
                }
                else if(r->next_relation == NULL)
                {
                    rr->next_relation = NULL;
                }
                else
                {
                    rr->next_relation = r->next_relation;
                    r->next_relation = NULL;
                }
                p->info.working_hours -= r->next_schedule->info.time;
                r->next_schedule = NULL;
            }
        }
    }
}

void deleteSchedule(List_employee &e, List_schedule &s, string gol)
{
    adr_schedule p = searchSchedule(s, gol);
    if(p != NULL)
    {
        adr_employee q = e.first_employee;
        while(q != NULL)
        {
            deleteScheduleFromEmployee(e, q->info.id, gol);
            q = q->next_elm;
        }
        if(p == s.first_schedule)
        {
            s.first_schedule = p->next_elm;
        }
        else
        {
            adr_schedule r = s.first_schedule;
            while(r->next_elm != p)
            {
                r = r->next_elm;
            }
            r->next_elm = p->next_elm;
        }
        p->next_elm = NULL;
    }
    system("cls");
    viewSchedule(s);
}

void viewAll(List_employee e, List_day d)
{
    adr_employee p = e.first_employee;
    if(p != NULL)
    {
        cout << "\n\t\t\t======================================================================" << endl;
        cout << "\t\t\t                           JADWAL KERJA PEGAWAI                       " << endl;
        cout << "\t\t\t======================================================================" << endl;
        while(p != NULL)
        {
            cout << "\n\n\t\t\t********************************************************************" << endl;
            cout << "\t\t\tId \t\t\t: " << p->info.id << endl;
            cout << "\t\t\tNama \t\t\t: " << p->info.nama << endl;
            cout << "\t\t\tPosisi \t\t\t: " << p->info.position << endl;
            if(p->schedule.first_relation != NULL)
            {
                adr_relation q = p->schedule.first_relation;
                cout << "\t\t\tTotal Jam Kerja \t: " << p->info.working_hours << " Jam"<< endl;
                cout << "\n\t\t\t\t\t\t*Jadwal Shift*" << endl;
                while(q != NULL)
                {
                    cout << "\n\t\t\tHari \t\t\t: " << q->next_day->info.day_name << endl;
                    cout << "\t\t\tJenis Shift\t\t: " << q->next_schedule->info.gol << endl;
                    cout << "\t\t\tWaktu \t\t\t: " << q->next_schedule->info.time << " Jam" << endl;
                    cout << endl;
                    q = q->next_relation;
                }
            }
            cout << "\t\t\t********************************************************************" << endl;
            p = p->next_elm;
        }
    }
}

void viewEmployee(List_employee e)
{
    cout << "\n\n\t\t\t                              DATA PEGAWAI                            " << endl;
    cout << "\t\t\t======================================================================" << endl;
    cout << "\t\t\t|| ID ||                NAMA                    ||      POSISI      ||" << endl;;
    cout << "\t\t\t======================================================================" << endl;;
    adr_employee p = e.first_employee;
    if(p != NULL)
    {
        while(p != NULL)
        {
            cout << "\t\t\t   [" << p->info.id << "]" << "\t ";
            cout << p->info.nama << "\t\t\t\t   ";
            cout << p->info.position << endl;
            p = p->next_elm;
        }
    }
    else
    {
        cout << "\t\t\t                    DATA KOSONG                            " << endl;
    }
    cout << "\t\t\t======================================================================" << endl;
}

void viewSchedule(List_schedule s)
{
    adr_schedule q = s.first_schedule;
    cout << "\n\n\t\t\t                              JADWAL SHIFT                            " << endl;
    cout << "\t\t\t======================================================================" << endl;
    if(q != NULL)
    {
        cout << "\t\t\t|      JENIS SHIFT      |      JAM MASUK      |      JAM KELUAR      |" << endl;
        cout << "\t\t\t======================================================================" << endl;
        while(q != NULL)
        {
            cout << "\t\t\t";
            cout << "|          " << q->info.gol<< "            ";
            cout << "|         "  << setfill('0') << setw(2) << q->info.in  << ".00" << "       ";
            cout << "|          " << setfill('0') << setw(2) << q->info.out << ".00" << "       |" << endl;
            q = q->next_elm;
        }
    }
    else
    {
        cout << "\t\t\t|                          JADWAL SHIFT KOSONG                       |" << endl;
    }
    cout << "\t\t\t======================================================================" << endl;
}

void viewDay(List_day d)
{
    adr_day p = d.first_day;
    if(p != NULL)
    {
        while(p != NULL)
        {
            cout << "  " << p->info.day_name << "  |" ;
            p = p->next_elm;
        }
        cout << endl;
        p = d.first_day;
        cout << "\t\t\t|                    |";
        while(p != NULL)
        {
            cout << "     " << p->info.day_number << "   |";
            p = p->next_elm;
        }
    }
}

void showHighAndLowData(List_employee e)
{
    adr_employee p = e.first_employee;
    adr_employee q = e.first_employee;
    adr_employee r = e.last_employee;
    while(p != NULL)
    {
        if(p->info.working_hours > q->info.working_hours && p->info.jumlah_hari > q->info.jumlah_hari)
        {
            q = p;
        }
        else if(p->info.working_hours > q->info.working_hours && p->info.jumlah_hari > q->info.jumlah_hari)
        {
            p = q;
        }
        else if(p->info.working_hours < r->info.working_hours && p->info.jumlah_hari < r->info.jumlah_hari)
        {
            r = p;
        }
        p = p->next_elm;
    }
    cout << "\n\n\t\t\t              DATA TERTINGGI          " << endl << endl;
    cout << "\t\t\tId \t\t\t: " << q->info.id << endl;
    cout << "\t\t\tNama \t\t\t: " << q->info.nama << endl;
    cout << "\t\t\tTotal Jam Kerja \t: " << q->info.working_hours << " Jam" << endl;
    cout << "\t\t\tJumlah Hari \t\t: " << q->info.jumlah_hari << " Hari" << endl << endl;

    cout << "\t\t\t              DATA TERENDAH          " << endl << endl;
    cout << "\t\t\tId \t\t\t: " << r->info.id << endl;
    cout << "\t\t\tNama \t\t\t: " << r->info.nama << endl;
    cout << "\t\t\tTotal Jam Kerja \t: " << r->info.working_hours << " Jam" << endl;
    cout << "\t\t\tJumlah Hari \t\t: " << r->info.jumlah_hari << " Hari" << endl << endl;
}


//styling
void greetings()
{
    cout << "\n\n\n";
    gotoxy(0, 10);
    cout << "\t\t\t=================================================================";
    gotoxy(0, 11);
    cout << "\t\t\t||                                                             ||\n";
    gotoxy(0, 12);
    cout << "\t\t\t||                                                             ||\n";
    gotoxy(0, 13);
    cout << "\t\t\t||       *SELAMAT DATANG DI PROGRAM DATA KERJA PEGAWAI*        ||\n";
    gotoxy(0, 14);
    cout << "\t\t\t||                                                             ||\n";
    gotoxy(0, 15);
    cout << "\t\t\t||                                                             ||\n";
    gotoxy(0, 16);
    cout << "\t\t\t||                                                             ||\n";
    gotoxy(0, 17);
    cout << "\t\t\t=================================================================\n\t\t\t";
    system("pause");
    system("cls");
}

void handleError()
{
    gotoxy(0, 10);
    cout << "\t\t\t=================================================================";
    gotoxy(0, 11);
    cout << "\t\t\t||                                                             ||\n";
    gotoxy(0, 12);
    cout << "\t\t\t||                                                             ||\n";
    gotoxy(0, 13);
    cout << "\t\t\t||                      *DATA KOSONG*                          ||\n";
    gotoxy(0, 14);
    cout << "\t\t\t||                                                             ||\n";
    gotoxy(0, 15);
    cout << "\t\t\t||                                                             ||\n";
    gotoxy(0, 16);
    cout << "\t\t\t||                                                             ||\n";
    gotoxy(0, 17);
    cout << "\t\t\t=================================================================\n\t\t\t";
}
