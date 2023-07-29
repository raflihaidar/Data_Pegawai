#include <iostream>
#include <string.h>
#include <iomanip>
#include <conio.h>
#include "Header.h"

using namespace std;

int main()
{
    system("Color 4F");
    greetings();
    Employee data_employee;
    Schedule data_schedule;

    List_employee e;
    List_schedule s;
    List_day d;
    List_relation r;

    adr_employee p;
    adr_schedule q;
    adr_day dd;

    createListEmployee(e);
    createListSchedule(s);
    createListDay(d);

    int input,
        length = 1,
        id_employee,
        day_number;
    string gol;

    do
    {
awal :
        system("cls");
        cout << "\n\n\n";
        cout << "     ****************************PROGRAM DATA SHIFT PEGAWAI****************************" << endl;
        cout << "     ======================       =========================      ======================" << endl;
        cout << "    ||1. ADD EMPLOYEE DATA ||     ||2. ADD SHIFT SCHEDULE ||    ||3. ADD RELATIONSHIP||" << endl;
        cout << "     ======================       =========================      ======================" << endl;
        cout << "\n\n";
        cout << "     ======================       ========================       ======================" << endl;
        cout << "    ||4. DELETE EMPLOYEE  ||     ||5. DELETE SCHEDULE   ||      || 6. SHOW ALL DATA ||" << endl;
        cout << "     ======================       ========================       ======================" << endl;
        cout << "\n\n";
        cout << "     ======================       =========================      ======================" << endl;
        cout << "    ||7. SHOW EMPLOYEE DATA||    ||8. SHOW WORK SHIFT DATA||    ||9.    SORTING      ||" << endl;
        cout << "     ======================       =========================      ======================" << endl;
        cout << "\n\n";
        cout << "     =======================                                                           " << endl;
        cout << "    ||10.      EXIT        ||                                                          " << endl;
        cout << "     =======================                                                           " << endl;
        cout << "     **********************************************************************************" << endl;
        cout << "\n     Masukkan Pilihan Anda : ";
        cin >> input;

        cin.ignore();
        system("cls");

        switch(input)
        {
        case 1 :
            viewEmployee(e);
            cout << "\n\n\t\t\tMasukkan Nama Pegawai : ";
            getline(cin, data_employee.nama);
            cout << "\t\t\tMasukkan Posisi : ";
            getline(cin, data_employee.position);
            data_employee.id = length++;
            p = createElmEmployee(data_employee);
            insertEmployee(e, p);
            break;
        case 2 :
            viewSchedule(s);
            cout << "\t\t\tMasukkan Jenis Shift : ";
            cin >> data_schedule.gol;
            cout << "\t\t\tMasukkan Jam masuk : ";
            cin >> data_schedule.in;
            cout << "\t\t\tMasukkan Jam keluar : ";
            cin >> data_schedule.out;
            data_schedule.time = stoi(data_schedule.out) - stoi(data_schedule.in);
            q = createElmSchedule(data_schedule);
            insertSchedule(s, q);
            break;
        case 3 :
            viewSchedule(s);
            viewEmployee(e);
            if(e.first_employee != NULL && s.first_schedule != NULL && d.first_day != NULL){
                cout << "\t\t\t*Klik e untuk kembali*" << endl;
                cout << "\t\t\tMasukkan Jenis Shift : ";
                cin >> gol;
                if(gol == "e")
                {
                    goto awal;
                }
                else
                {
                    cout << "\t\t\tMasukkan Id pegawai : ";
                    cin >> id_employee;
                    cout << "\t\t\tMasukkan Hari Kerja : ";
                    cin >> day_number;
                    addRelation(e, s, d, id_employee, gol, day_number);
                }
            }else{
                system("cls");
                handleError();
            }
            break;
        case 4 :
            if(e.first_employee != NULL)
            {
                viewEmployee(e);
                cout << "\t\t\t*Klik 1 untuk kembali*" << endl;
                cout << "\t\t\tMasukkan Id Pegawai : ";
                cin >> id_employee;
                deleteEmployee(e, id_employee);
            }
            else
            {
                handleError();
            }
            break;
        case 5 :
            if(e.first_employee != NULL)
            {
                viewSchedule(s);
                cout << "\t\t\t*Klik e untuk kembali*" << endl;
                cout << "\t\t\tMasukkan Jenis Shift :";
                cin >> gol;
                if(gol != "e")deleteSchedule(e, s, gol);
                else goto awal;
                break;
            }
            else
            {
                handleError();
            }
        case 6 :
            if(e.first_employee != NULL)
            {
                viewAll(e, d);
            }
            else
            {
                handleError();
            }
            break;
        case 7 :
            viewSchedule(s);
            cout << "\t\t\t*Klik e untuk kembali*" << endl;
            cout << "\t\t\tMasukkan Golongan Shift : ";
            cin >> gol;
            if(e.first_employee != NULL && s.first_schedule != NULL)
            {
                if(gol != "e") searchEmployeeFromSchedule(s, e, gol);
                else goto awal;
            }
            else
            {
                handleError();
            }
            break;
        case 8 :
            viewEmployee(e);
            cout << "\t\t\tMasukkan Id Pegawai :";
            cin >> id_employee;
            if(e.first_employee != NULL)
            {
                if(gol != "e") searchScheduleFromEmployee(e, s, r, id_employee);
                else goto awal;
            }
            else
            {
                handleError();
            }
            break;
        case 9 :
            if(e.first_employee != NULL) showHighAndLowData(e);
            else handleError();
            break;
        case 10 :
            gotoxy(0, 10);cout << "\t\t\tTERIMA KASIH TELAH MENGGUNAKAN PROGRAM KAMI" << endl;
            break;
        default :
            cout << "\t\t\tInputan anda salah" << endl;
        }
        system("\t\t\tpause");
        system("cls");
    }
    while(input != 10);

    return 0;
}
