#include<iostream.h>
#include<math.h>
#include<windows.h>
#include<fstream.h>
#include<time.h>
#include<iomanip.h>

//system one
class finance
{
      float funds; //for the setup function that will have the basic data to work with for the apartment account
      float amount, temp_amt, temp; // used in denomiantion breakdown function
      int columns, rows;
      struct finance_format
      {
          int ctr;
          float amount;
          int option_1, option_2;
          char name_1[100], name_2[100];  
          time_t t;
      }data;
      struct fund
      {
             float amt;
      }fund;
    void screen_info()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
      	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
      	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
      	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
      public :
             
      finance()
      {
               // getting size of file to get number of record
                  ofstream file_o("finances.dat", ios::app | ios::binary);
                  file_o.seekp(0,ios::end);
                  data.ctr = file_o.tellp()/sizeof(finance_format);
                  file_o.close();
                  
               // getting the current funds to work with
                  ifstream file_i("funds.dat", ios :: binary);
                  file_i.read((char*)&fund.amt, sizeof(fund));
                  file_i.close();
                  funds = fund.amt;
      }
      void line(char a = '-')
      {
      // Declare & Initialize the variables rows and columns with their respective values
      screen_info();

      for (int ctr = 0; ctr < columns; ctr++) // The Top Margin for the heading
      cout << a;
      }
      void getdata()
      {
      cout << "Enter the amount :" << endl;
      cin >> amount;
      temp_amt = amount;
      }
      void denomination_breakdown()
      {
                  cout << endl;
                  // 2000 rupee notes
                  temp = floor(temp_amt/2000);
                  (temp > 0) ? cout << "-> Number of 2000 Rupee notes needed :\t" << temp << endl : cout << "";
                  (temp_amt >= 2000*temp) ? temp_amt = temp_amt - (2000*temp) : temp_amt = temp_amt;
                  
                  // 500 rupee notes
                  temp = floor(temp_amt/500);
                  (temp > 0) ? cout << "-> Number of 500 Rupee notes needed :\t" << temp << endl : cout << "";
                  (temp_amt >= 500*temp) ? temp_amt = temp_amt - (500*temp) : temp_amt = temp_amt;
                  
                  // 200 rupee notes
                  temp = floor(temp_amt/200);
                  (temp > 0) ? cout << "-> Number of 200 Rupee notes needed :\t" << temp << endl : cout << "";
                  (temp_amt >= 200*temp) ? temp_amt = temp_amt - (200*temp) : temp_amt = temp_amt;
                  
                  // 100 rupee notes
                  temp = floor(temp_amt/100);
                  (temp > 0) ? cout << "-> Number of 100 Rupee notes needed :\t" << temp << endl : cout << "";
                  (temp_amt >= 100*temp) ? temp_amt = temp_amt - (100*temp) : temp_amt = temp_amt;
                  
                  // 50 rupee notes
                  temp = floor(temp_amt/50);
                  (temp > 0) ? cout << "-> Number of 50 Rupee notes needed :\t" << temp << endl : cout << "";
                  (temp_amt >= 50*temp) ? temp_amt = temp_amt - (50*temp) : temp_amt = temp_amt;
                  
                  // 20 rupee notes
                  temp = floor(temp_amt/20);
                  (temp > 0) ? cout << "-> Number of 20 Rupee notes needed :\t" << temp << endl : cout << "";
                  (temp_amt >= 20*temp) ? temp_amt = temp_amt - (20*temp) : temp_amt = temp_amt;
                  
                  // 10 rupee notes
                  temp = floor(temp_amt/10);
                  (temp > 0) ? cout << "-> Number of 10 Rupee notes/coins needed :\t" << temp << endl : cout << "";
                  (temp_amt >= 10*temp) ? temp_amt = temp_amt - (10*temp) : temp_amt = temp_amt;
                  
                  // 5 rupee notes
                  temp = floor(temp_amt/5);
                  (temp > 0) ? cout << "-> Number of 5 Rupee coins needed :\t" << temp << endl : cout << "";
                  (temp_amt >= 5*temp) ? temp_amt = temp_amt - (5*temp) : temp_amt = temp_amt;
                  
                  // 2 rupee notes
                  temp = floor(temp_amt/2);
                  (temp > 0) ? cout << "-> Number of 2 Rupee coins needed :\t" << temp << endl : cout << "";
                  (temp_amt >= 2*temp) ? temp_amt = temp_amt - (2*temp) : temp_amt = temp_amt;
                  
                  // 1 rupee notes
                  temp = floor(temp_amt/1);
                  (temp > 0) ? cout << "-> Number of 1 Rupee coins needed :\t" << temp << endl : cout << "";
                  (temp_amt >= 1*temp) ? temp_amt = temp_amt - (1*temp) : temp_amt = temp_amt;
                  
                  cout << endl;
                  line();
      }
       
       void show_funds()
       {
        cout << "-> Current Funds = Rs." << funds << endl;
     
        if(funds < 0)
            cout << ":-> Therefore, we are in debt of Rs." << fabs(funds) << endl;
        else if(funds > 0)
            cout << ":-> Therefore, we have Rs." << funds << " in the bank." << endl;
        else
            cout << ":-> We have neither gained nor lost money." << endl;
            
        cout << endl;
        line();
       }
      void main_menu(finance obj);
      void record_modify();
      void transaction_input();
      void transaction_output(int option = 1, int up_range = 1, int low_range = 1, int control = 1);
      void heading_print(const char *text);
      void prgm_lines(const char *text, int option);
      void deletion(int deletion_no);
      void net_amt(int option = 1, int low_range = 1, int up_range = 1);
      void save()
      {
           ofstream file;
           file.open("funds.dat", ios::binary);
           fund.amt = funds;
           file.write((char*)&fund.amt, sizeof(int));
           file.close();
      }
}obj;

void finance :: transaction_input()
{
           int option;
           line();
           do
           {
           fstream file("finances.dat", ios::out | ios::binary | ios::app);
           cout << "This is transaction no. : " << ++data.ctr << endl;
           cout << "Enter the amount Transacted :" << endl;
           cout << "Rs.";
           cin >> data.amount;
           cout << "Has this amount has been gained or lost (Enter 1 for gained and 0 for lost) :" << endl;
           cin >> data.option_1;
           if(data.option_1 != 1 && data.option_1 != 0)
           {line();prgm_lines("Invalid Option Entered ! Record Aborted !",0); data.ctr--; line();return;}
           cout << "Enter the name of the Issuing Authority(ies) :" << endl;
           fflush(stdin);
           gets(data.name_1);
           cout << "Enter the name of the receiving Authority(ies) :" << endl;
           fflush(stdin);
           gets(data.name_2);
           cout << "Enter the payment method :" << endl;
           cout << "1. Cash" << endl;
           cout << "2. Cheque" << endl;
           cout << "3. Demand Draft/Banker's Cheque" << endl;
           cout << "-> ";
           cin >> data.option_2;
           if(data.option_2 != 1 && data.option_2 != 2 && data.option_2 != 3)
           {line();prgm_lines("Invalid Option Entered ! Record Aborted !",0); data.ctr--; line();return;}
           line();
           cout << endl << "Do you want to enter any other trasactions ?\n(Enter 1 for Yes and 0 for No)" << endl;
           cout << "-> ";
           cin >> option;
           if(option != 1 && option != 0)
           {continue;}
           //get current time in format of time_t
           data.t = time(NULL);
           // tally the transactions to the total funds
           if(data.option_1 == 1)
           {
                    funds += data.amount;      
           }
           else
           {
               funds -= data.amount;
           }
           save();
           file.write((char*)&data, sizeof(data));
           line();
           file.close();
           }while(option == 1);
}

void finance :: heading_print(const char *text)
{
  	// Declare & Initialize the variables rows and columns with their respective values
  	screen_info();

  	int len = strlen(text);
  	cout << "|$"
  		<< setw((columns / 2) + (int)ceil(len / 2))
  		<< text
  		<< setw((columns / 2) - (int)ceil(len / 2) - 2)
  		<< "$|";
}

// align text
//0. centre
//1. left align
//2. right align
void finance :: prgm_lines(const char *text, int option)
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
 
void finance :: net_amt(int option, int low_range, int up_range)
{
           float mod_opt;
           double gain = 0, loss = 0, net = 0;
           ifstream file("finances.dat", ios::binary);
           while(file.read((char*)&data, sizeof(finance_format)) && option == 1)// net of all transactions
           {
                if(data.option_1 == 1) // amount has been gained
                {
                                 gain += data.amount;
                }
                else // amount has been lost
                {
                                 loss += data.amount;
                     
                }     
           }  
           file.seekg(0, ios::beg);                          
           while(file.read((char*)&data, sizeof(finance_format)) && up_range >= low_range && data.ctr >= low_range && data.ctr <= up_range && option == 2) // net of a range of transactions
           {
                if(data.option_1 == 1) // amount has been gained
                {
                                 gain += data.amount;
                }
                else // amount has been lost
                {
                                 loss += data.amount;
                     
                }
           }
           
           file.close();
           net = gain - loss;
           cout << "-> The Net Value of these Transactions is : Rs." << net << endl;
           if(net < 0)
             cout << ":-> Therefore, we are in debt of Rs." << fabs(net) << endl;
           else if(net > 0)
             cout << ":-> Therefore, we have gained Rs." << net << endl;
           else
             cout << ":-> We have neither gained nor lost money." << endl;
           
           line();
           cout << "Would you like to see the denomination breakdown for the amount of Rs." << fabs(net) << "? \n\t(Enter 1 for Yes and 0 for No)" << endl;
           cout << "-> ";
           cin >> mod_opt;
           if(mod_opt == 1)
           {
                      temp_amt = (float)fabs(net);
                      denomination_breakdown();
           }
           line();
}

void finance :: record_modify()
{
           int trans_no, mod_opt, bool_1 = 0 /*to check if the record has been found in the file or not*/;
           float amt_change;
           float amount;
           char name_1[20], name_2[20];
           finance_format temp;
           
                  fstream file("finances.dat", ios::in | ios::binary);
                  cout << "Enter the complaint no. :" << endl;
                  cout << "-> ";
                  cin >> trans_no;
                  while(!file.eof())
                  {
                         file.read((char*)&data, sizeof(data));
                         if(data.ctr == trans_no)
                         {
                         line();
                         prgm_lines("Transaction found !" ,0);
                         line();
                         bool_1 = 1;
                         prgm_lines("Details of the Transaction are :",1);
                         line();
                         cout << "Transaction no. : " << data.ctr << endl;
                         cout << "The amount Transacted : " << data.amount << endl;
                         if(data.option_1 == 1)
                         {cout << "This amount has been gained." << endl;}
                         else
                         {cout << "This amount has been lost." << endl;}
                         //convert time_t to char*
                         char* charTime = ctime(&data.t);
                         cout << "Date of transaction : " << charTime << endl;
                         cout << "The name of the Issuing Authority(ies) : " << data.name_1 << endl;
                         cout << "The name of the Receiving Authority(ies) : " << data.name_2 << endl;
                         cout << "Used payment method : ";
                         switch(data.option_2)
                         {
                         case 1:
                         cout << "Cash" << endl;
                         break;
                         case 2:
                         cout << "Cheque" << endl;
                         break;
                         case 3:
                         cout << "Demand Draft/Banker's Cheque" << endl;
                         break;
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
                            line();
                            prgm_lines("Record not found !" ,0);
                            line();
                            return;
                  }
                  
                  // Modify options
                  temp.ctr = data.ctr;
                  temp.t = data.t;
           
           //issuing_authority
           line();
           cout << "Would like to modify the Issuing authority ? \n(enter 1 for yes and 0 for no)" << endl;
           cout << "-> ";
           cin >> mod_opt;
           if(mod_opt == 1)
           {
            cout << "Enter the Issuing authority : " << endl;
            fflush(stdin);
            gets(temp.name_1);
           }
           else
           {
               strcpy(temp.name_1, data.name_1);
           }
           //receiving authority
           line();
           cout << "Would like to modify the Receiving authority ? \n(enter 1 for yes and 0 for no)" << endl;
           cout << "-> ";
           cin >> mod_opt;
           if(mod_opt == 1)
           {
            cout << "Enter the Receiving authority :" << endl;
            fflush(stdin);
            gets(temp.name_2);
           }
           else
           {
            strcpy(temp.name_2, data.name_2);
           }
           //amount
           line();
           cout << "Would you like to change the amount ? \n(enter 1 for yes and 0 for no)" << endl;
           cout << "-> ";
           cin >> mod_opt;
           if(mod_opt == 1)
           {
            cout << "Enter the amount : " << endl;
            cin >> temp.amount;
            amt_change = data.amount - temp.amount;
           }
           else
           {
               temp.amount = data.amount;
           }
           //Payment method 
           line();
           cout << "Would you like to change the payment method ? \n(enter 1 for yes and 0 for no)" << endl;
           cout << "-> ";
           cin >> mod_opt;
           if(mod_opt == 1)
           {
            cout << "Enter the Payment Method Option : " << endl;
            cout << "1. Cash" << endl;
            cout << "2. Cheque" << endl;
            cout << "3. Demand Draft/Banker's Cheque" << endl;
            cout << "-> ";
            cin >> temp.option_2;
            if(temp.option_2 != 1 && temp.option_2 != 2 && temp.option_2 != 3)
            {cout << "**Invalid Option Entered ! Record Aborted !" << endl; return;}
           }
           else
           {
               temp.option_2 = data.option_2;
           }
           //amount gained or amount lost
           line();
           cout << "Would you like to change the payment status ? \n(enter 1 for yes and 0 for no)" << endl;
           cout << "-> ";
           cin >> mod_opt;
           if(mod_opt == 1)
           {
                      cout << "Has this amount has been gained or lost (Enter 1 for gained and 0 for lost) :" << endl;
                      cin >> temp.option_1;
                      if(temp.option_1 != 1 && temp.option_1 != 0)
                      {cout << "Invalid Option Entered ! Record Aborted !" << endl; return;}
           }
           else
           {
               temp.option_1 = data.option_1;
           }
           line();
           
                 cout << "Confirm changes ? (Enter 1 for yes and 0 for no)" << endl;
                 cout << "-> ";
                 cin >> mod_opt;
                 line();
                 cout << endl;
                 if(mod_opt == 1)
                 {
                  if(temp.option_2 == data.option_2)
                  {
                                   if(temp.option_2 == 1)
                                       funds -= amt_change;
                                   else
                                       funds += amt_change;
                  }
                  else
                  {
                      if(temp.option_2 == 1)
                      {
                                       funds = funds + data.amount + temp.amount;
                      }
                      else
                      {
                          funds = funds - (data.amount + temp.amount);
                      }
                  }
                  save();
                  fstream file("finances.dat", ios::binary | ios::in);
                  fstream new_file("temp.dat", ios::binary | ios::out);
                  //creating the new temp file
                 while(file.read((char*)&data, sizeof(data)))
                  {
                   if(data.ctr != trans_no)
                   {
                               new_file.write((char*)&data, sizeof(data));
                   }
                   else
                   {
                               new_file.write((char*)&temp, sizeof(temp));
                   }
                 }
                 file.close();
                 new_file.close();
                 remove("finances.dat");
                 rename("temp.dat","finances.dat");
                 }
                 else
                 {
                 line('#');
                 prgm_lines("Changes Aborted !", 0);
                 line('#');
                 }           
           
}

void finance :: transaction_output(int option, int up_range, int low_range, int control)
{
           int ctr = 0;
           ifstream file("finances.dat", ios::binary);
           
           while(ctr < control && option == 1 && file.read((char*)&data, sizeof(data)))
           {
           cout << "Transaction no. : " << data.ctr << endl;
           cout << "The amount Transacted : " << data.amount << endl;
           if(data.option_1 == 1)
           {cout << "This amount has been gained." << endl;}
           else
           {cout << "This amount has been lost." << endl;}
           //convert time_t to char*
          char* charTime = ctime(&data.t);
           cout << "Date of transaction : " << charTime << endl;
           cout << "The name of the Issuing Authority(ies) : " << data.name_1 << endl;
           cout << "The name of the receiving Authority(ies) : " << data.name_2 << endl;
           cout << "Used payment method : ";
           switch(data.option_2)
           {
           case 1:
                cout << "Cash" << endl;
           break;
           case 2:
                cout << "Cheque" << endl;
           break;
           case 3:
                cout << "Demand Draft/Banker's Cheque" << endl;
           break;
           }
           line();
           ctr++;
           }
           file.close();
           
           file.open("finances.dat", ios::binary);
           while(option == 2 && file.read((char*)&data, sizeof(data))) 
           {
           if(data.ctr <= up_range && data.ctr >= low_range && up_range >= low_range)
           {
           cout << "Transaction no. : " << data.ctr << endl;
           cout << "The amount Transacted : " << data.amount << endl;
           if(data.option_1 == 1)
           {cout << "This amount has been gained." << endl;}
           else
           {cout << "This amount has been lost." << endl;}
           //convert time_t to char*
           char* charTime = ctime(&data.t);
           cout << "Date of transaction : " << charTime << endl;
           cout << "The name of the Issuing Authority(ies) : " << data.name_1 << endl;
           cout << "The name of the receiving Authority(ies) : " << data.name_2 << endl;
           cout << "Used payment method : ";
           switch(data.option_2)
           {
           case 1:
                cout << "Cash" << endl;
           break;
           case 2:
                cout << "Cheque" << endl;
           break;
           case 3:
                cout << "Demand Draft/Banker's Cheque" << endl;
           break;
           }
           line();
           ctr++;
           }
           }
           file.close();
           
           file.open("finances.dat", ios::binary);
           while(option == 3 && file.read((char*)&data, sizeof(data)))
           {
           cout << "Transaction no. : " << data.ctr << endl;
           cout << "The amount Transacted : " << data.amount << endl;
           if(data.option_1 == 1)
           {cout << "This amount has been gained." << endl;}
           else
           {cout << "This amount has been lost." << endl;}
           //convert time_t to char*
          char* charTime = ctime(&data.t);
           cout << "Date of transaction : " << charTime << endl;
           cout << "The name of the Issuing Authority(ies) : " << data.name_1 << endl;
           cout << "The name of the receiving Authority(ies) : " << data.name_2 << endl;
           cout << "Used payment method : ";
           switch(data.option_2)
           {
           case 1:
                cout << "Cash" << endl;
           break;
           case 2:
                cout << "Cheque" << endl;
           break;
           case 3:
                cout << "Demand Draft/Banker's Cheque" << endl;
           break;
           }
           line();
           ctr++;
           }
           file.close();
}

void finance :: deletion(int deletion_no)
{
     finance_format temp;
     int bool_1 = 0, confirm_opt = 0, new_ctr = 0;
     fstream file("finances.dat", ios::in | ios::binary);
     while(!file.eof())
     {
       file.read((char*)&data, sizeof(data));
       if(data.ctr == deletion_no)
       {
        line();
        obj.heading_print("Transaction found !");
        line();
        bool_1 = 1;
        prgm_lines("Details of the Transaction are :", 1);
        line();
        cout << "Transaction no. : " << data.ctr << endl;
        cout << "The amount Transacted : " << data.amount << endl;
        if(data.option_1 == 1)
        {cout << "This amount has been gained." << endl;}
        else
        {cout << "This amount has been lost." << endl;}
        //convert time_t to char*
        char* charTime = ctime(&data.t);
        cout << "Date of transaction : " << charTime << endl;
        cout << "The name of the Issuing Authority(ies) : " << data.name_1 << endl;
        cout << "The name of the Receiving Authority(ies) : " << data.name_2 << endl;
        cout << "Used payment method : ";
        switch(data.option_2)
        {
           case 1:
           cout << "Cash" << endl;
           break;
           case 2:
           cout << "Cheque" << endl;
           break;
           case 3:
           cout << "Demand Draft/Banker's Cheque" << endl;
           break;
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
                line();
                prgm_lines("Record not found !" ,0);
                line();
                return;
     }
           
     prgm_lines("Would you like to Delete This Record ? (Enter 1 For Yes & 0 for No)", 1);
     cin >> confirm_opt;
     line();
     
     if(confirm_opt == 1)
     {
           file.open("finances.dat", ios::binary | ios::in);
           fstream new_file("temp.dat", ios::binary | ios::out);
           //creating the new temp file
           while(file.read((char*)&data, sizeof(data)))
           {
             if(data.ctr == deletion_no)
             {
             if(data.option_1 == 1) //amount gained
               {funds -= data.amount;}
             else
               {funds += data.amount;}
             }
             else
             {
              data.ctr = ++new_ctr;
              new_file.write((char*)&data, sizeof(data));
             }
           }
           save();
           file.close();
           new_file.close();
           remove("finances.dat");
           rename("temp.dat","finances.dat");   
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

void finance :: main_menu(finance obj)
{
    int first_time_setup = 0, option, num, upper, lower, deletion_no;
    do{
    system("cls");
    obj.line('=');
    obj.heading_print("Finance Manager Menu");
    obj.line('=');
    obj.prgm_lines("1. Enter \'1\' To Enter A New Transaction.",1);
    obj.prgm_lines("2. Enter \'2\' To Modify An Existing Transaction.",1);
    obj.prgm_lines("3. Enter \'3\' To Review A Transaction.",1);
    obj.prgm_lines("4. Enter \'4\' To Delete A Transaction.",1);
    obj.prgm_lines("5. Enter \'5\' To Calculate the Net Amount of the Transactions.",1);
    obj.prgm_lines("6. Enter \'6\' To the Denomination Split for A Certain Amount.",1);
    obj.prgm_lines("7. Enter \'7\' To See the Amount Present In The Apartment Funds.",1);
    obj.prgm_lines("8. Enter \'8\' To Exit.", 1);
    obj.line('=');
    cout << "Enter Your Option :"<< endl;
    cout << "-> ";
    cin >> option;
    cout << endl;
    //The Main Branching point based on the option selected
    switch(option)
    {
                  case 1:
                       obj.transaction_input();
                  break;
                  
                  case 2:
                       obj.record_modify();
                  break;
                  
                  case 3:
                       obj.line('-');
                       obj.prgm_lines("1. Enter \'1\' To Show a Select Number Of Transactions from the start.", 1);
                       obj.prgm_lines("2. Enter \'2\' To Show a Select Range of Transactions.", 1);
                       obj.prgm_lines("3. Enter \'3\' To Show All Transactions from the start.", 1);
                       obj.prgm_lines("4. Enter \'4\' To Exit", 1);
                       obj.line('-');
                       cout << "Enter Your Option :"<< endl;
                       cout << "-> ";
                       cin >> option;
                       line();
                       switch(option)
                       {
                                     case 1:
                                          obj.prgm_lines("Enter the Number of Transactions You Would Like To See :" , 1);
                                          cout << "-> ";
                                          cin >> num;
                                          line();
                                          obj.transaction_output(1,6,6,num);
                                     break;
                                     case 2:
                                          obj.prgm_lines("Enter the Upper Limit of The Transaction No. You Would Like To See :" , 1);
                                          cout << "-> ";
                                          cin >> upper;
                                          obj.prgm_lines("Enter the Lower Limit of The Transaction No. You Would Like To See :" , 1);
                                          cout << "-> ";
                                          cin >> lower;
                                          obj.transaction_output(2, upper, lower, 7);
                                     break;
                                     case 3:
                                          obj.transaction_output(3);
                                     break;
                                     case 4: // escape route if option selected by mistake
                                     break;
                                     default:
                                             obj.line('X');
                                             obj.heading_print("Invalid Option Entered ! Please Try Again !");
                                             obj.line('X');
                       }
                       break;
                  
                  case 4:
                       obj.line('-');
                       obj.prgm_lines("Please Enter The Transaction No. You would Like To Delete :", 1);
                       cout << "-> ";
                       cin >> deletion_no;
                       obj.deletion(deletion_no);
                       obj.line('-');
                  break;
                  case 5:
                       obj.line('-');
                       obj.prgm_lines("1. Enter \'1\' To Calculate Using All Transactions from the start.", 1);
                       obj.prgm_lines("2. Enter \'2\' To Calculate Using a Select Range of Transactions.", 1);
                       obj.prgm_lines("3. Enter \'3\' To Exit.", 1);
                       obj.line('-');
                       cout << "Enter Your Option :"<< endl;
                       cout << "-> ";
                       cin >> option;
                       switch(option)
                       {
                       case 1:
                            obj.net_amt(1);
                       break;
                       
                       case 2:
                            obj.prgm_lines("Enter the Upper Limit of The Transaction No. :" , 1);
                            cout << "-> ";
                            cin >> upper;
                            obj.prgm_lines("Enter the Lower Limit of The Transaction No. :" , 1);
                            cout << "-> ";
                            cin >> lower;
                            obj.net_amt(2, lower, upper);
                       break;
                       
                       case 3: // escape route if option selected by mistake
                       break;
                       
                       default :
                               obj.line('X');
                               obj.heading_print("Invalid Option Entered ! Please Try Again !");
                               obj.line('X');
                       }
                  break;
                  
                  case 6:
                       obj.getdata();
                       obj.denomination_breakdown();
                  break;
                  
                  case 7:
                       obj.show_funds();
                  break;
                  
                  case 8:
                       obj.save();
                       line();
                       return;
                  break;
                  
                  default :
                          obj.line('X');
                          obj.heading_print("Invalid Option Entered ! Please Try Again !");
                          obj.line('X');
    }
    system("pause");
}while(option != 8);
}
