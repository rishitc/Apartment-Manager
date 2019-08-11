#include<iostream.h>
#include<stdio.h>
#include<fstream.h>

struct residents
{
int flat_no, occupants_no, status, cars;
char owner_name[10];
int defaulter;
int rows, columns;
}record;
int main()
{
    fstream file("database.dat", ios::in | ios::binary);
    
    for (int ctr = 0; ctr < 42; ctr++)
    {
        file.read((char*)&record, sizeof(residents));
        cout << "Flat No. : " << record.flat_no << endl;
        cout << "Occupants No. : " << record.occupants_no << endl;
        cout << "Status : " << record.status << endl;
        cout << "Cars : " << record.cars << endl;
        cout << "Owner Name : " << record.owner_name << endl;
        cout << "Deaulter : " << record.defaulter << endl;
        for(int y = 0; y < 80; y++)
                cout << '-';
    }
           
    file.close();
    system("pause");
}
