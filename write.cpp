#include<iostream.h>
#include<math.h>
#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<iomanip.h>

struct residents
{
int flat_no, occupants_no, status, cars;
char owner_name[10];
int defaulter;
int rows, columns;
}filler[42];
int rows, columns;

void screen_info()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
      	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
      	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
      	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    
    
// align text
//0. centre
//1. left align
//2. right align
void prgm_lines(const char *text, int option)
{
	// Declare & Initialize the variables rows and columns with their respective values
	screen_info();
	int len = strlen(text);
	if (option == 0)//centre text
	{
		cout << "||"
			<< setw((columns / 2) + (int)ceil(len / 2) - 1)
			<< text
			<< setw((columns / 2) - (int)ceil(len / 2) - 1)
			<< "||";
	}
	else if (option == 1)//left align
	{
		cout << "||"
			<< setw(len + 1)
			<< text
			<< setw(columns - (len + 3))
			<< "||";
	}
  else if (option == 2)//right align
	{
		cout << "||"
			<< setw(columns - 5)
			<< text
			<< " ||";
	}
}
int main()
{
   fstream file("database.dat", ios::out | ios::binary);
   
   //value for entering the funds for the finance program
   struct funds{float amt;} funds; 
   
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
    filler[ctr].flat_no = (int)(ceil(ctr / 2) * 100) + 100;
    filler[ctr].flat_no = (ctr % 2) ? filler[ctr].flat_no + 1 : filler[ctr].flat_no;
    filler[ctr].occupants_no = num;
    filler[ctr].status = 1; // status 1 = resident; 2 = tenent; 3 = empty
    num = (rand() % 3) + 1;
    filler[ctr].cars = num;
    filler[ctr].defaulter = 1;
    filler[ctr].status = 1; // status 1 = resident; 2 = tenent; 3 = empty
    strcpy(filler[ctr].owner_name, name_list[ctr]);
    
    file.write((char*)&filler[ctr], sizeof(residents));
  }
   
   file.close();
   
struct data_values
{
  float rate, floor_rate, car_rate, penalty; // The maintenance rate per sq. ft. is Rs.5
  
  //Initializing the values
  data_values()
  {
               rate = 5; floor_rate = 10; car_rate = 50; penalty = 100;
  }
}access;
  
  //get the values for the data_values from the file
   ofstream temp("data_values.dat", ios::binary);
   temp.write((char*)&access, sizeof(data_values));
   temp.close();
   
   screen_info();
   for (int t = 0; t < columns; t++)
   cout << '-';
   
    prgm_lines("Enter the Total Apartment Funds :", 1);
    for (int t = 0; t < columns; t++)
     cout << '-';
    prgm_lines(" Note : This amount will be used as the base for all future transactions.", 1);
    prgm_lines("This value can be chaged if needed in the settings!", 0);
    for (int t = 0; t < columns; t++)
     cout << '-';
    cout << "Amount :\t";
    cin >> funds.amt;
    
    temp.open("funds.dat", ios::binary);
    temp.write((char*)&funds.amt, sizeof(funds));
    temp.close();
    for (int t = 0; t < columns; t++)
     cout << '-';
   system("pause");      
}
