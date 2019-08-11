#include "main_prgm_classes.cpp"
#include "calculator.cpp"
#include "complaints.cpp"
#include "finances.cpp"
#include<cstring>
#include<conio.h>

using namespace std;
int main()
{
  residents resident_list[42];
  // Declaring and defining (some) of the variables for the program
  char input[5];
  int flat_no[4];
  int control1;
  int option, flag = 1;
  
  struct data_values
  {
  float rate, floor_rate, car_rate, penalty; // The maintenance rate per sq. ft. is Rs.5
  }access;
  
  
//passcode part
bool valid;
int camp,i=0,fla=1,j;
const char pass[] = "manager123";//correct password
char str2[15];

do
{
resident_list[0].line();
resident_list[0].bill_lines("Enter the password : ", 1);
resident_list[0].line();
for ( i = 0; i < 30 && (camp = getche()) != '\r'; i++ ) //to convert to astriesk
{
str2[i] = camp;
putch('\x8');
putch('*');
}
str2[i]='\0';
fflush(stdin);

for(j=0;j<strlen(pass);j++)
{
        if(pass[j]!=str2[j])
        {
        fla=0;
        break;
        }
}

             if (!fla)//(valid != true)
             {
             resident_list[0].line();
             cout << endl;
             resident_list[0].line('X');
             resident_list[0].heading_print("Sorry, that password is invalid !");
             resident_list[0].line('X');
             flag=1;
             system("pause");
             system("cls");
             exit(0);
             }

}while(!flag);
resident_list[0].line();
  //------------------------------------------
  
  
  
  
  
  
  //get the values for the data_values from the file
   ifstream file("data_values.dat", ios::binary);
   file.read((char*)&access, sizeof(data_values));
   file.close();
   
  // used to save the data values and the aparment resient data in the file
  fstream save_1;
  fstream save_2;
  
  int defaulter_head_count;

  // Declare & Initialize the variables rows and columns with their respective values
     int rows, columns;   
    CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

  //Initializing All The Values Of The Resident Structure
  resident_list[0].value_initializer(resident_list);
  complaints obj_opt_6;
  // The Beginning Of The Loop
  do{
    flag = 1;

  system("cls"); // Clear The Screen
  
  resident_list[0].line(); // The Top Margin For The Heading

  resident_list[0].heading_print("Pimento By Maratt");
  resident_list[0].heading_print("Apartment Manager V1.0");

  resident_list[0].line(); // The Bottom Margin For The Heading


  // The Menu
  resident_list[0].bill_lines("Main Menu", 0);
  resident_list[0].line();
  resident_list[0].bill_lines("1.  Display Maintenance Bill For A Flat.", 1);
  resident_list[0].bill_lines("2.  Update System Values." , 1);
  resident_list[0].bill_lines("3.  Display Defaulters List.", 1);
  resident_list[0].bill_lines("4.  Edit Defaulters List.", 1);
  resident_list[0].bill_lines("5.  Calculator.", 1);
  resident_list[0].bill_lines("6.  Complaint Management.", 1);
  resident_list[0].bill_lines("7.  Finance Manager.", 1);
  resident_list[0].bill_lines("8.  Save Changes", 1);//
  resident_list[0].bill_lines("9.  Help.", 1);
  resident_list[0].bill_lines("10. Credits.", 1);
  resident_list[0].bill_lines("11. Save & Exit.", 1);
  resident_list[0].line();
  cout << endl << "Enter Your Option :" << endl;
  cout << "-> ";
  cin >> option;

  switch (option)
  {
  case 1:

    // Asking the user for the flat no
    cout << "Enter The Flat No. (For Example : 1101 or 800):" << endl;
    cin >> input;

    // To Transfer The Flat No Contained In The Character Array To An Integer Array
    resident_list[0].num_to_arr_trans(input, flat_no);

    // Function call to check the entered flat no format and return 1 if everthing is correct and 0 if there are any mistakes
    flag = resident_list[0].flat_no_format_check(flat_no, input);

    // To check if there were any mistakes and if there were any mistakes -> then push the user to the end of the program
    if (flag == 0)
      break;
      
    cout << endl;
    // List Out The Maintainance Amount For The Resident
    resident_list[0].main_pay(access.rate, access.car_rate, access.floor_rate, input, access.penalty, resident_list);

    break;

  case 2:
      /* Calls The Function To Allow The User To Change The Preset Values -> the maintenance rate per square foot, the penalty amount per day,
       the rate per car park and the rate per floor */
      resident_list[0].value_changer(option, access.rate, access.penalty, access.car_rate, access.floor_rate);
    break;

  case 3:

    // To check if there are any defaulters and to print the defaulters details
    defaulter_head_count = resident_list[0].defaulters_list(access.rate, access.car_rate, access.floor_rate, input, access.penalty, resident_list);


    // To finish off with a quick analysis
    if (defaulter_head_count == 0)
      cout << "-> There Are No Defaulters This Month." << endl;
    else
    {
      // To close off the dividers into a neat box
      resident_list[0].line();
      cout << endl;

      // To finish off with a quick analysis
      if (defaulter_head_count == 1)
        cout << "-> There Is " << defaulter_head_count << " Defaulter This Month." << endl;
      else
        cout << "-> There Are " << defaulter_head_count << " Defaulters This Month." << endl;
    }

    cout << endl;
    // Special Pattern Line
    resident_list[0].line();

    break;

  case 4:
    resident_list[0].defaulter_list_editor(flat_no, input, resident_list);
    break;

  case 5:
    system("cls");
    calculator_func();
    break;

    case 6:
    obj_opt_6.main_menu();
    break;
    
    case 7:
         obj.main_menu(obj);
    break;
    
    case 8:
         save_1.open("database.dat", ios::binary | ios::out);
         save_2.open("data_values.dat", ios::binary | ios::out);
         for (int ctr = 0; ctr < 42; ctr++)
         {
             save_1.write((char*)&resident_list[ctr], sizeof(residents));
         }
         save_2.write((char*)&access, sizeof(data_values));
         save_1.close();
         save_2.close();
         
         system("cls");
         resident_list[0].line();
         for (int i = 0; i < (rows / 2) - 2; i++)
             resident_list[0].bill_lines("", 1);
         resident_list[0].line();
         resident_list[0].bill_lines("Changes Saved !", 0);
         resident_list[0].line();
         for (int i = 0; i < (rows / 2) - 3; i++)
              resident_list[0].bill_lines("", 1);
         resident_list[0].line();
    break;
    
  case 9:
    resident_list[0].help();
    break;

  case 10:
    resident_list[0].credits();
    break;

  case 11:
    save_1.open("database.dat", ios::binary | ios::out);
    save_2.open("data_values.dat", ios::binary | ios::out);
    for (int ctr = 0; ctr < 42; ctr++)
    {
      save_1.write((char*)&resident_list[ctr], sizeof(residents));
    }
    save_2.write((char*)&access, sizeof(data_values));
    save_1.close();
    save_2.close();
    system("cls");
    for (int i = 0; i < (rows / 2) - 1; i++)
      cout << endl;
    resident_list[0].line();
    resident_list[0].heading_print("Thank You & Have A Great Day !");
    resident_list[0].line();
    for (int i = 0; i < (rows / 2) - 2; i++)
      cout << endl;
    system("pause");
    exit(0);
    break;

  default:
     resident_list[0].line('X');
     resident_list[0].heading_print("Invalid Option Entered, Please Try Again !");
     resident_list[0].line('X');
  }
system("pause");
}while (1); // Main Do-While loop
}
