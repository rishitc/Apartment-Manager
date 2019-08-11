#include<iostream.h>
#include<math.h>
#include<fstream.h>
class residents
{
      public:
int flat_no, occupants_no, status, cars;
char owner_name[10];
int defaulter;	  // At The Start Of The Program It Is Assumed That No Resident Has Paid The Maintenance
// Declaring and defining (some) of the variables for the program

// Declare & Initialize the variables rows and columns with their respective values
int rows, columns;

void value_initializer(residents resident_list[])
{
// Initializing all the values in the structure
  int num;

  /**************************************/
  char name_list[42][10] = {
    { "Sophia" },
    { "Jackson" },
    { "Emma" },
    { "Aiden" },
    { "Olivia" },
    { "Lucas" },
    { "Ava" },
    { "Liam" },
    { "Mia" },
    { "Noah" },
    { "Isabella" },
    { "Ethan" },
    { "Riley" },
    { "Mason" },
    { "Aria" },
    { "Caden" },
    { "Zoe" },
    { "Oliver" },
    { "Charlotte" },
    { "Michael" },
    { "Lily" },
    { "Grayson" },
    { "Chloe" },
    { "Alexander" },
    { "Harper" },
    { "Caleb" },
    { "Abigail" },
    { "Ryan" },
    { "Aaliyah" },
    { "Luke" },
    { "Avery" },
    { "Daniel" },
    { "Evelyn" },
    { "Jack" },
    { "Kaylee" },
    { "William" },
    { "Ella" },
    { "Owen" },
    { "Ellie" },
    { "Gabriel" },
    { "Scarlett" },
    { "Matthew" }
  };
  /**************************************/

  srand(time(NULL)); // Set the seed for the random function

             // Initializing all the variables of the struture array for the program
  for (int ctr = 0; ctr < 42; ctr++)
  {
    num = (rand() % 4) + 1;
    resident_list[ctr].flat_no = (int)(ceil(ctr / 2) * 100) + 100;
    resident_list[ctr].flat_no = (ctr % 2) ? resident_list[ctr].flat_no + 1 : resident_list[ctr].flat_no;
    resident_list[ctr].occupants_no = num;
    resident_list[ctr].status = 1; // status 1 = resident; 2 = tenent; 3 = empty
    num = (rand() % 3) + 1;
    resident_list[ctr].cars = num;
    resident_list[ctr].defaulter = 1;
    resident_list[ctr].status = 1; // status 1 = resident; 2 = tenent; 3 = empty
    strcpy(resident_list[ctr].owner_name, name_list[ctr]);
  }
}
};

int main()
{
    residents resident_list[42], chk;
    //Initializing All The Values Of The Resident Structure
    
  resident_list[0].value_initializer(resident_list);
  fstream file("resi_data.dat", ios::out | ios::binary | ios::app);
  for(int ctr = 0; ctr < 42; ctr++)
  {
          file.write((char*)&resident_list[ctr], sizeof(resident_list[ctr])); 
  }
  file.close();
  file.open("resi_data.dat", ios::in | ios::binary);
  /*for(int ctr = 0; ctr < 42; ctr++)
  {
          
          file.read((char*)&chk, sizeof(chk));
          cout << chk.flat_no << endl;
          cout << chk.occupants_no << endl;
          cout << chk.status << endl;
          cout << chk.cars << endl;
          cout << chk.owner_name<< endl;
          cout << chk.defaulter << endl;
          
  }
  file.close();*/
  cout << "The template file has been created !" << endl;
  system("pause");
}
