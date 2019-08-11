#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<windows.h>
#include<math.h>
#include<iomanip.h>

class complaints
{
      int columns, rows;
      struct format
      {
            char name_1[15], name_2[15];
            char flat_no[5];
            char text[700];
            int ctr;
            int status;
            time_t t, close_time;
      }data;
      
    void screen_info()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
      	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
      	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
      	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    void line(char a = '-');
      public :
             
      complaints()
      {
                  ofstream file("complaints.dat", ios::app | ios::binary);
                  file.seekp(0,ios::end);
                  data.ctr = file.tellp()/sizeof(format);
                  data.status = 1; // 1 - not solved, 2 - looked into, 3 - solved
                  file.close();
      }
      
       
      int flat_no_format_check(int[],char[]);
      void modifyComplaint();
      void showComplaint(int compl_num = -1);
      void addComplaint();
      void num_to_arr_trans(char input[5], int flat_no[4]);
      void heading_print(const char *text);
      void deleteComplaint();
      void prgm_lines(const char *text, int option);
      void main_menu();
      void updateComplaint();
      void autoCorrect(char text[]);
};
// align text
//0. centre
//1. left align
//2. right align
void complaints :: prgm_lines(const char *text, int option)
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

void complaints :: num_to_arr_trans(char input[5], int flat_no[4])
{
  int ctr = 0;
  while (input[ctr] != '\0') // Moving the input data from char array input to int array flat_no
  {
    flat_no[ctr] = input[ctr];
    flat_no[ctr] -= 48;
    ctr++;
  }
}

void complaints :: heading_print(const char *text)
  {
  	
  	// Declare & Initialize the variables rows and columns with their respective values
  	screen_info();

  	int len = strlen(text);
  	cout << "|*"
  		<< setw((columns / 2) + (int)ceil(len / 2))
  		<< text
  		<< setw((columns / 2) - (int)ceil(len / 2) - 2)
  		<< "*|";
  }
  
void complaints :: line(char a)
             {
  	         // Declare & Initialize the variables rows and columns with their respective values
  	         screen_info();

  	         for (int ctr = 0; ctr < columns; ctr++) // The Top Margin for the heading
  		     cout << a;
             }
int complaints :: flat_no_format_check(int flat_no[],char input[])
{
	/******************************************************** Flat No Format And Validity Checks *****************************************************/
	int arr_size = strlen(input); // To find the size of the flat no entered
	if(arr_size < 3 && arr_size > 4) // To check if the flat no size is 3 or 4 numbers long or not
	{
		cout << endl << "Invalid Flat No. Size - " << arr_size << endl;
		cout << "The Flat No Length Should Be 3-4 Characters Long Only" << endl;
		return 0;
	}

	/*************************************************************************************************************************************/
	/*
	If the flat no size is 3 numbers long then the checks to do are :
	 1. The first number should be between 1 and 9 including both limits
	 2. The second number should be 0
	 3. The third number should be either 0 or 1
	*/
	if (arr_size == 3 && !(flat_no[0] >= 1 && flat_no[0] <= 9 && flat_no[1] == 0 && (flat_no[2] == 1 || flat_no[2] == 0)))
	{
		cout << endl << "Invalid Flat No Format Entered ! Please Try Again !" << endl;
		if(!(flat_no[0] >= 1 && flat_no[0] <= 9))
			cout << "NOTE : The first number should be between 1 and 9 including both limits." << endl;
		else if(!(flat_no[1] == 0))
			cout << "NOTE : The second number should be 0." << endl;
		else if(!(flat_no[2] == 1 || flat_no[2] == 0))
		  cout << "NOTE : The third number should be either 0 or 1." << endl;
		return 0;
	}

	/*
	If the flat no size is 4 numbers long then the checks to do are :
	 1. The first number should be either 1 or 2
	 2. If first number is 1 then the second number should be from 1-9 including both limits
	 3. If the first number is 2 then the second number should be either 0 or 1
	 4. The general rules across both are that the third number should be 0 and the fouth number should be either 0 or 1
	*/
	else
	{
		if (arr_size == 4 && flat_no[0] == 1 && !(flat_no[1] >= 0 && flat_no[1] <= 9 && flat_no[2] == 0 && (flat_no[3] == 1 || flat_no[3] == 0)))
		{
			cout << endl << "Invalid Flat No Format Entered ! Please Try Again."<< endl;
			if(!(flat_no[0] >= 1 && flat_no[0] <= 9))
				cout << "NOTE : If first number is 1 then the second number must be from 1-9 including both limits." << endl;
			else if(!flat_no[2] == 0)
				cout << "NOTE : The third number must be 0" << endl;
			else if(!(flat_no[3] == 1 || flat_no[3] == 0))
				cout << "NOTE : The fouth number must be either 0 or 1" << endl;
			return 0;
		}
		else if (arr_size == 4 && flat_no[0] == 2 && !((flat_no[1] == 0 || flat_no[1] == 1) && flat_no[2] == 0 && (flat_no[3] == 1 || flat_no[3] == 0)))
		{
			cout << endl << "Invalid Flat No Format Entered ! Please Try Again." << endl;
			if(!(flat_no[0] == 0 || flat_no[0] == 1))
				cout << "NOTE : If first number is 2 then the second number must be from 0 or 1." << endl;
			else if(!flat_no[2] == 0)
				cout << "NOTE : The third number must be 0" << endl;
			else if(!(flat_no[3] == 1 || flat_no[3] == 0))
				cout << "NOTE : The fouth number must be either 0 or 1" << endl;
			return 0;
		}
		else
			return 1;
	}
	}
	
	void complaints :: modifyComplaint()
      {
                  line();
                  int compl_no, bool_1 = 0, mod_opt;
                  format temp;
                  fstream file("complaints.dat", ios::in | ios::binary);
                  cout << "Enter the Complaint No. :" << endl;
                  cout << "-> ";
                  cin >> compl_no;
                  while(!file.eof())
                  {
                         file.read((char*)&data, sizeof(format));
                         if(data.ctr == compl_no)
                         {
                         line();
                         prgm_lines("Complaint found !" ,0);
                         line();
                         cout << "Details of the complaint are :" << endl;
                         bool_1 = 1;
                         showComplaint(compl_no);
                         break;
                         }
                         else
                             continue;   
                  }
                  file.close();
                  if(bool_1 == 0)
                  {
                         line();
                         prgm_lines("Record not found !" ,0);
                         line();
                            return;
                  }
                  
                  // Modify options
                  temp.ctr = data.ctr;
                  temp.t = data.t;
                  cout << "Would like to modify the name of the affeced ? \n\t(enter 1 for yes and 0 for no)" << endl;
                  cout << "-> ";
                  cin >> mod_opt;
                  if(mod_opt == 1)
                  {
                  cout << "-> Enter Name : ";
                  cin >> temp.name_1;
                  }
                  else
                  {
                      strcpy(temp.name_1, data.name_1);
                  }
                  
                  line();
                  cout << "Would like to modify the name of the accused ? \n\t(enter 1 for yes and 0 for no)" << endl;
                  cout << "-> ";
                  cin >> mod_opt;
                  if(mod_opt == 1)
                  {
                  cout << "-> Enter Name : ";
                  cin >> temp.name_2;
                  }
                  else
                  {
                      strcpy(temp.name_2, data.name_2);
                  }
                  
                  line();
                  cout << "Would like to modify the Flat No. ? \n\t(enter 1 for yes and 0 for no)" << endl;
                  cout << "-> ";
                  cin >> mod_opt;
                  if(mod_opt == 1)
                  {
                  int flag, flat_no[4];
                  cout << "-> Enter Flat No. : ";
                  cin >> temp.flat_no;
                  num_to_arr_trans(temp.flat_no, flat_no);
                   // Function call to check the entered flat no format and return 1 if everthing is correct and 0 if there are any mistakes
                   flag = flat_no_format_check(flat_no, temp.flat_no);

                   // To check if there were any mistakes and if there were any mistakes -> then push the user to the end of the program
                   if (flag == 0)
                    goto escape;
                  }
                  else
                  {
                      escape:
                      strcpy(temp.flat_no, data.flat_no);
                  }
                  
                  line();
                  cout << "Would like to modify the complaint ? \n\t(enter 1 for yes and 0 for no)" << endl;
                  cout << "-> ";
                  cin >> mod_opt;
                  if(mod_opt == 1)
                  {
                  cout << "NOTE : (" << 700-strlen(data.text) << " characters or less only)" << endl;
                  cout << "-> Enter Complaint : ";
                  fflush(stdin);
                  gets(temp.text);
                  autoCorrect(temp.text);
                  strcat(data.text, " EDIT : ");
                  strcat(data.text, temp.text);
                  strcpy(temp.text, data.text);
                  }
                  else
                  {
                      strcpy(temp.text, data.text);
                  }
                  
                  line();
                  cout << "Would like to modify the status of the complaint ? \n\t(enter 1 for yes and 0 for no)" << endl;
                  cout << "-> ";
                  cin >> mod_opt;
                  if(mod_opt == 1)
                  {
                   cout << "Enter :" << endl << "1. Open" << endl << "2. Being investigated" << endl << "3. Closed" << endl;
                   cout << "-> Enter Option : ";
                   cin >> temp.status;
                    if(temp.status != 1 && temp.status != 2 && temp.status != 3)
                    {
                    cout << "**Invalid option entered ! Status set to open !" << endl;
                    temp.status = 1;
                    }
                    if(temp.status == 3)
                    {
                        //get current time in format of time_t
                        temp.close_time = time(NULL);
                    }
                  }
                  else
                  {
                      temp.close_time = data.close_time;
                      temp.status = data.status;
                  }
                   
                  line();
                  cout << "Confirm changes \n\t(Enter 1 for yes and 0 for no)" << endl;
                  cout << "-> ";
                  cin >> mod_opt;
                  line();
                  
                  if(mod_opt == 1)
                  {
                  fstream file("complaints.dat", ios::binary | ios::in);
                  fstream new_file("temp.dat", ios::binary | ios::out);
                  //creating the new temp file
                  while(file.read((char*)&data, sizeof(format)))
                  {
                   if(data.ctr != compl_no)
                   {
                       new_file.write((char*)&data, sizeof(format));
                   }
                   else
                   {
                       new_file.write((char*)&temp, sizeof(format));
                   }
                  }
                  file.close();
                  new_file.close();
                  remove("complaints.dat");
                  rename("temp.dat","complaints.dat");
                  }
                  else
                  {cout << "Change aborted !" << endl; line();}           
      }
      void complaints :: showComplaint(int compl_num)
             {
                  line();   
                  char* charTime;
                  fstream file("complaints.dat", ios::in | ios::binary);
                  if(compl_num <= 0)
                  {
                   while(file.read((char*)&data, sizeof(format)))
                   {
                   cout << "Complaint No. : " << data.ctr << endl;
                   charTime = ctime(&data.t);
                   cout << "Date of Complaint : " << charTime;
                   prgm_lines("--*--", 0);
                   cout << "Name of the affetced : \t" << data.name_1 << endl;
                   cout << "The flat no. of the affected : \t" << data.flat_no << endl;
                   cout << "The name of the accused : \t" << data.name_2 << endl;
                   cout << "The Complaint :\n" << data.text << endl;
                   cout << "The Status of the complaint : \t";
                   switch(data.status)
                   {
                                     case 1:
                                          cout << " Open" << endl;
                                     break;
                                     case 2:
                                          cout << " Being investigated" << endl;
                                     break;
                                     case 3:
                                          cout << " Closed" << endl;
                                     break;
                   }
                   if(data.status == 3)
                   {
                     charTime = ctime(&data.close_time);
                     cout << "Date of Complaint Closure : " << charTime;
                   }
                   line();
                  }
                  file.close();
                }
               else
               {
                   while(file.read((char*)&data, sizeof(format)))
                   {
                   if(data.ctr == compl_num)
                   {
                   cout << "Complaint No. : \t" << data.ctr << endl;
                   charTime = ctime(&data.t);
                   cout << "Date of Complaint : " << charTime << endl;
                   cout << "Name of the affetced : \t" << data.name_1 << endl;
                   cout << "The flat no. of the affected : \t" << data.flat_no << endl;
                   cout << "The name of the accused : \t" << data.name_2 << endl;
                   cout << "The Complaint :\n" << data.text << endl;
                   cout << "The Status of the complaint : \t";
                   switch(data.status)
                   {
                                     case 1:
                                          cout << " Open" << endl;
                                     break;
                                     case 2:
                                          cout << " Being investigated" << endl;
                                     break;
                                     case 3:
                                          cout << " Closed" << endl;
                                     break;
                   }
                   if(data.status == 3)
                   {
                     charTime = ctime(&data.close_time);
                     cout << "Date of Complaint Closure : " << charTime << endl;
                   }
                   line();
                  }// end of if
                  }// end of while loop
                  file.close();
               }// end of else
      }// end of function
             
      void complaints :: addComplaint()
      {
                  line();
                  int option;
                  fstream file("complaints.dat", ios::out | ios::binary | ios::app);
                  do{
                  cout << "This is Complaint No. : " << ++data.ctr << endl;
                  cout << "Enter the name of the affected : \t";
                  fflush(stdin);
                  gets(data.name_1);
                  cout << "Enter the name of the accused : \t";
                  fflush(stdin);
                  gets(data.name_2);
                  cout << "Enter the flat no. : \t";
                  cin >> data.flat_no;
                  int flag, flat_no[4];
                  num_to_arr_trans(data.flat_no, flat_no);
                   // Function call to check the entered flat no format and return 1 if everthing is correct and 0 if there are any mistakes
                   flag = flat_no_format_check(flat_no, data.flat_no);

                   // To check if there were any mistakes and if there were any mistakes -> then push the user to the end of the program
                   if (flag == 0)
                    {
                            cout << endl;
                            line();
                            heading_print("Addition of record aborted ! Returning To Main Menu");
                            line();
                            data.ctr--;
                            return;
                    }
                  cout << "Enter your complaint : (700 characters or less only) :" << endl;
                  fflush(stdin);
                  gets(data.text);
                  autoCorrect(data.text);
                  line();
                  cout << "Would you like to add more complaints (Enter 1 for yes and 0 for no)" << endl;
                  cout << "-> ";
                  cin >> option;
                  line();
                  data.status = 1;
                  //get current time in format of time_t
                  data.t = time(NULL);
                  file.write((char*)&data, sizeof(format));
                  }while(option != 0);
                  file.close();
      }

void complaints :: deleteComplaint()
{
     complaints temp;
     int bool_1 = 0, confirm_opt = 0, new_ctr = 0, deletion_no;
     fstream file("complaints.dat", ios::in | ios::binary);
     line();
     prgm_lines("Please Enter The Complaint No. You would Like To Delete :", 1);
     cout << "-> ";
     cin >> deletion_no;
     line();
     while(!file.eof())
     {
       file.read((char*)&data, sizeof(data));
       if(data.ctr == deletion_no)
       {
        line();
        prgm_lines("Complaint found !" ,0);
        line();
        bool_1 = 1;
        cout << "Complaint no. : " << data.ctr << endl;
        char* charTime = ctime(&data.t);
        cout << "Date of Complaint : " << charTime << endl;
        cout << "Name of the affetced : \t" << data.name_1 << endl;
        cout << "The flat no. of the affected : \t" << data.flat_no << endl;
        cout << "The name of the accused : \t" << data.name_2 << endl;
        cout << "The Complaint :\n" << data.text << endl;
        cout << "The Status of the complaint : \t";
        switch(data.status)
        {
        case 1:
        cout << " Open" << endl;
        break;
        case 2:
        cout << " Being investigated" << endl;
        break;
        case 3:
        cout << " Closed" << endl;
        break;
        }
        if(data.status == 3)
        {
         charTime = ctime(&data.close_time);
         cout << "Date of Complaint Closure : " << charTime << endl;
        }
        line();
        break;
       }
       else
       continue;   
     }
     file.close();
     if(bool_1 == 0)
     {
                prgm_lines("Record not found !" ,0);
                line();
                return;
     }
           
     prgm_lines("Would you like to Delete This Record ? (Enter 1 For Yes & 0 for No)", 1);
     cout << "-> ";
     cin >> confirm_opt;
     line();
     
     if(confirm_opt == 1)
     {
           file.open("complaints.dat", ios::binary | ios::in);
           fstream new_file("temp.dat", ios::binary | ios::out);
           //creating the new temp file
           while(file.read((char*)&data, sizeof(format)))
           {
             if(data.ctr == deletion_no)
             {
              continue;
             }       
              data.ctr = ++new_ctr;
              new_file.write((char*)&data, sizeof(format));
           }
           file.close();
           new_file.close();
           remove("complaints.dat");
           rename("temp.dat","complaints.dat");   
           data.ctr = new_ctr; 
     }      
     else
     {
               line('#');
               prgm_lines("Changes Aborted !", 0);
               line('#');
               return;
     }
}

void complaints :: updateComplaint()
{
     
     line();
     int compl_no, bool_1 = 0, mod_opt;
     format temp;
     fstream file("complaints.dat", ios::in | ios::binary);
     cout << "Enter the complaint no. :" << endl;
     cout << "-> ";
     cin >> compl_no;
     
     //find the record 
     while(!file.eof())
     {
        file.read((char*)&data, sizeof(data));
        if(data.ctr == compl_no)
        {
          line();
          prgm_lines("Complaint found !" ,0);
          line();
          cout << "Details of the complaint are :" << endl;
          bool_1 = 1;
          showComplaint(compl_no);
          break;
        }
       else
         continue;   
     }
     file.close();
     if(bool_1 == 0)
     {
        line();
        prgm_lines("Record not found !" ,0);
        line();
        return;
     }
                  
     //copying all the data of data variable into the temp variable except the status
     temp.ctr = data.ctr;
     temp.t = data.t;
     strcpy(temp.name_1, data.name_1);
     strcpy(temp.name_2, data.name_2);
     strcpy(temp.flat_no, data.flat_no);
     strcpy(temp.text, data.text);
     
     //taking the status from the user
     //menu
     prgm_lines("Status Options" ,0);
     line();
     prgm_lines("Enter :", 1);
     prgm_lines("1. Open", 1);
     prgm_lines("2. Being investigated", 1);
     prgm_lines("3. Closed", 1);
     line();
     prgm_lines("Enter Your Option :", 1);
     cout << "-> ";
     cin >> temp.status;
     line();
     
     if((temp.status != 1 && temp.status != 2 && temp.status != 3) || isalpha(temp.status))
     {
        line('x');
        prgm_lines("Invalid option entered ! Status set to open !" ,0);
        line('x');
        temp.status = 1;
     }
     
     if(temp.status == 3)
     {
        //get current time in format of time_t
        temp.close_time = time(NULL);
     }     
     
     prgm_lines("Confirm changes (Enter 1 for yes and 0 for no)", 1);         
     cout << "-> ";
     cin >> mod_opt;
     line(); 
                  
     if(mod_opt == 1)
     {
       fstream file("complaints.dat", ios::binary | ios::in);
       fstream new_file("temp.dat", ios::binary | ios::out);
       //creating the new temp file
       while(file.read((char*)&data, sizeof(format)))
       {
          if(data.ctr != compl_no)
          {
             new_file.write((char*)&data, sizeof(format));
          }
          else
          {
             new_file.write((char*)&temp, sizeof(format));
          }
       }
       file.close();
       new_file.close();
       remove("complaints.dat");
       rename("temp.dat","complaints.dat");
     }
     else
     {
         line('x');
         prgm_lines("Change aborted !" ,0);
         line('x');
     }          
}

void complaints :: autoCorrect(char text[])
{
     int len = strlen(text), bool_cap = 0, ctr = 0;
     text[0] = toupper(text[0]);
     // captilise all first letters of senteces
     while(text[ctr] != '\0')
     {
                     if(text[ctr] == '.')
                     {
                        bool_cap = 1;
                     }
                     if(bool_cap == 1)
                     {
                        text[ctr] = toupper(text[ctr]);
                        bool_cap = 0;
                     }
                     ctr++;
     }
     // add a full stop at the end
     if(text[len-1] != '.')
     {
                    strcat(text, "."); 
     }
}

void complaints :: main_menu()
{
int option;
    do{
          system("cls");
          line();
          heading_print("Complaints Menu");
          line();
          prgm_lines("1. Add Complaint.", 1);
          prgm_lines("2. Display Complaints.", 1);
          prgm_lines("3. Modfiy Complaint.", 1);
          prgm_lines("4. Update Complaint Status.", 1);
          prgm_lines("5. Delete Complaint.", 1);
          prgm_lines("6. Exit.", 1);
          line();
          prgm_lines("Enter Your Option", 1);
          cout << "-> ";
          cin >> option;
          
    switch(option)
    {
                  case 1:
                       addComplaint();
                  break;
                  case 2:
                       showComplaint();
                  break;
                  case 3:
                       modifyComplaint();
                  break;
                  case 4:
                       updateComplaint();
                  break;
                  case 5:
                       deleteComplaint();
                  break;
                  case 6:
                       cout << endl;
                       line();
                       return;
                  break;
                  default: 
                          line('X');
                          heading_print("Invalid Option Entered ! Please Try Again !");
                          line('X');   
    }
    system("pause");
}while(option != 6);
}
