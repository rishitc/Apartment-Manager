#include <iostream>
#include <string.h>
#include <math.h>
#include <iomanip>
#include <stdio.h>
#include <windows.h>
#include <fstream.h>
using namespace std;
class residents
{
int flat_no, occupants_no, status, cars;
char owner_name[10];
int defaulter;	  // At The Start Of The Program It Is Assumed That No Resident Has Paid The Maintenance
// Declaring and defining (some) of the variables for the program

// Declare & Initialize the variables rows and columns with their respective values
int rows, columns;

public :
// Function Signatures :
//1. Member Functions :

  int flat_num(char input[5])
  {
  	int ctr = 0, flat_no[5], no;
  	ctr = strlen(input);
  	num_to_arr_trans(input, flat_no);
  	if (ctr == 3) // If the flat no is 3 numbers long
  	{
  		no = (flat_no[0] * 2);
  		no = (flat_no[2] == 0) ? no - 1 : no;
  	}
  	else // If the flat no is 4 letters long
  	{
  		no = ( ( (flat_no[0] * 10) + flat_no[1] ) * 2 );
  		no = (flat_no[3] == 0) ? no - 1 : no;
  	}
  	return no;
  }

  void sp_pat_line()
  {
  	cout << endl;

  	// Declare & Initialize the variables rows and columns with their respective values
  	screen_info();

  	for (int ctr = 0; ctr < columns; ctr++)
  	{
  		if (ctr % 2 == 0)
  			cout << '/';
  		else
  			cout << '\\';
  	}
  	cout << endl;
  }

  void heading_print(const char *text)
  {
  	// Declare & Initialize the variables rows and columns with their respective values
  	screen_info();

  	int len = strlen(text);
  	cout << '|'
  		<< setw((columns / 2) + (int)ceil(len / 2))
  		<< text
  		<< setw((columns / 2) - (int)ceil(len / 2) - 1)
  		<< '|';
  }

  void line(char a = '-')
  {
  	// Declare & Initialize the variables rows and columns with their respective values
  	screen_info();

  	for (int ctr = 0; ctr < columns; ctr++) // The Top Margin for the heading
  		cout << a;
  }

  int no_of_digits(int num)
  {
  	int ctr = 0;
  	while(num != 0)
  	{
  		num = (int)ceil(num/10);
  		ctr++;
  	}
  	return ctr;
  }

  void help()
  {
  	char text[] = "This program has been designed to enable the highest quality user experience in the visual constraints of the DOS environment the program runs in.  All options and all error messages are well labeled and have been designed to be easily understood by the operator for the smooth functioning of the program.";
  	line();
  	heading_print("Help");
  	line();
  	heading_print("");
  	text_centre(text);
  	line();
  }

  void credits()
  {
  	char text[] = "I would like to thank our principal, Mrs. Deepa Sridhar as well as the entire School faculty and management, for providing us with this wonderful infrastructure to study and work. I would also like to thank our entire computer science faculty for giving us the needed guidance and support in our respective computer projects. I thank my family and friends for their unconditional love and support.";
    line();
  	heading_print("Credits");
  	line();
  	heading_print("");
  	text_centre(text);
  	line();
  }

  void screen_info()
  {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
      	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
      	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
      	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  }

  // Converts a floating point number to string.
  void ftoa(float n, char *res, int afterpoint)
  {
  	if (n == 0)
  	{
  		strcpy(res, "0");
  	}
  	else {
  		// Extract integer part
  		int ipart = (int)n;

  		// Extract floating part
  		float fpart = n - (float)ipart;

  		// convert integer part to string
  		int i = intToStr(ipart, res, 0);

  		// check for display option after point
  		if (afterpoint != 0)
  		{
  			res[i] = '.';  // add dot

  						   // Get the value of fraction part upto given no.
  						   // of points after dot. The third parameter is needed
  						   // to handle cases like 233.007
  			fpart = fpart * pow(10, afterpoint);

  			intToStr((int)fpart, res + i + 1, afterpoint);
  		}
  	}
  }

  //==================================

//2.Non Member Functions :
  void reverse(char *, int x = -1); //==
  int flat_no_format_check(int[4], char[5]);//==
  void main_pay(float, float, float, char[5], float, residents[]);//
  void value_initializer(residents[42]);//==
  void reset_default_list(residents[42]);//==
  void value_changer(int&, float&, float&, float&, float&);//==
  int defaulters_list(float, float, float, char[5], float, residents[]);//==
  void num_to_arr_trans(char[5], int[4]);//==
  void defaulter_list_editor(int[4], char[5], residents[]);//==
  void bill_lines(const char*, int);//==
  void num_ending_letter(int, char[120]);//==
  int intToStr(int, char[], int);//==
  void spaces(char[100], int);
  void empty_default_list(residents[]);//==
  void text_centre(char[]); //==
};

void residents :: text_centre(char text[])
{
	// Declare & Initialize the variables rows and columns with their respective values
	screen_info();
	int len = strlen(text);
	int no_of_lines = (int)ceil((double)len / (columns - 6));
	int ctr = 0, ctr1 = 0, ctr2 = 0;
	char temp_arr[116];
	while (ctr < no_of_lines)
	{
		ctr1 = 0;
		while (ctr1 < (columns - 6))
		{
			temp_arr[ctr1] = text[ctr2];
			ctr1++;
			ctr2++;
		}
		temp_arr[ctr1] = '\0';
		heading_print(temp_arr);
		ctr++;
	}

}

// reverses a string 'str'
void residents :: reverse(char *str, int x)
{
	int i = 0, temp ;
  int j = (x == -1) ? strlen(str) - 1 : x;
	while (i<j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++; j--;
	}
}

void residents :: num_to_arr_trans(char input[5], int flat_no[4])
{
  int ctr = 0;
  while (input[ctr] != '\0') // Moving the input data from char array input to int array flat_no
  {
    flat_no[ctr] = input[ctr];
    flat_no[ctr] -= 48;
    ctr++;
  }
}

// Converts a given integer x to string str[].  d is the number
// of digits required in output. If d is more than the number
// of digits in x, then 0s are added at the beginning.
int residents :: intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x /= 10;
	}

	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
		str[i++] = '0';

	str[i] = '\0';
	reverse(str);
	return i;
}

// align text
//0. centre
//1. left align
//2. right align
void residents :: bill_lines(const char *text, int option)
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

void residents :: num_ending_letter(int flat_ctr, char str_to_be[120])
{
	// Char Array To Hold The Number
	int temp = flat_ctr; //ctr = strlen(str_to_be);

	// To Convert The Number Into A String And Reverse It And Put It In A Int
  /*while (temp)
	{
    str_to_be[ctr++] = (char)ceil(temp%10) + '0';
		temp /= 10;
	}
  str_to_be[ctr] = '\0';*/
  //reverse(str_to_be);
 if(flat_ctr > 10 && flat_ctr < 21)
  {
		strcat(str_to_be, "th");
    return;
  }
	// To Just Be Left With The Units Place Of The Number

	// Add The The Appropriate Ending To The Number
	switch (str_to_be[strlen(str_to_be) - 1] - '0')
	{
	case 1:
		strcat(str_to_be, "st");
		break;
	case 2:
		strcat(str_to_be, "nd");
		break;
	case 3:
		strcat(str_to_be, "rd");
		break;
	default:
		strcat(str_to_be, "th");
	}
}

int residents :: flat_no_format_check(int flat_no[],char input[])
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

void residents :: reset_default_list(residents resident_list[])
{
	for (int ctr = 0; ctr < 42; ctr++)
		resident_list[ctr].defaulter = 1;
}

void residents :: empty_default_list(residents resident_list[])
{
	for (int ctr = 0; ctr < 42; ctr++)
		resident_list[ctr].defaulter = 0;
}

void residents :: value_initializer(residents resident_list[])
{
  residents record;
  fstream file("database.dat", ios :: in | ios :: binary);
  for (int ctr = 0; ctr < 42; ctr++)
  {
    file.read((char*)&record, sizeof(residents));
    resident_list[ctr].flat_no = record.flat_no;
    resident_list[ctr].occupants_no = record.occupants_no;
    resident_list[ctr].status = record.status; // status 1 = resident; 2 = tenent; 3 = empty
    resident_list[ctr].cars = record.cars;
    resident_list[ctr].defaulter = record.defaulter;
    strcpy(resident_list[ctr].owner_name, record.owner_name);
  }
   
   file.close();
}


  void residents :: defaulter_list_editor(int flat_no[4], char input[5], residents resident_list[])
  {
  	// Declare The Option Variable
  	int option;

  	// The Key & One Control Variable
  	char key;
  	int control = 3;

  	// The Flat Counter
  	int flat_ctr;

  	// The Flag Variable
  	int flag;

  	// Character Array To Hold The Intermediate Sentence
  	char temp_text[80];

  	// Declare & Initialize the variables rows and columns with their respective values
  	screen_info();

  	do {
  	system("cls");

  	// Display The Heading
  	line();
  	heading_print("Defaulters' List Editor");
  	line();

  	// Display The Menu To The User & Ask For His/Her Choice
  	bill_lines("Menu", 0);
  	line();
  	bill_lines("1. Reset Complete List", 1);
  	bill_lines("2. Edit Certain Flats", 1);
  	bill_lines("3. Empty Complete List", 1);
  	bill_lines("4. Exit", 1);
  	line();
  	cout << endl << "Enter Your Option :" << endl;
  	cout << "-> ";
  	cin >> option;
  	cout << endl;

  	// Check Option & Perform The Respective Commands That Follow It
  	switch(option)
  	{
  	case 1:
  		reset_default_list(resident_list);
  		cout << endl;
  		line();
  		heading_print("The List Has Been Reset !");
  		line();
  		cout << endl;
  		break;

  	case 2:
  		do {
            line();
            bill_lines("The Enter The Flat No. To Remove From The Defaulters' List :", 1);
  			cout << "-> ";
            cin >> input;
            line();
            
  			cout << endl;
  			// To Transfer The Flat No Contained In The Character Array To An Integer Array
  			num_to_arr_trans(input, flat_no);

  			flag = flat_no_format_check(flat_no, input); // Function call to check the entered flat no format and return 1 if everthing is correct and 0 if there are any mistakes
  			if (flag == 0) // To check if there were any mistakes and if there were any mistakes -> then push the user to the end of the program
  				break;

  			// Find The Flat No From 1-42
  			flat_ctr = flat_num(input);
  			resident_list[flat_ctr].defaulter = 0;
  			strcpy(temp_text, "The Flat No. ");
  			strcat(temp_text, input);
  			strcat(temp_text, " Has Been Removed From The Defaulters' List");
  			line();
  			bill_lines(temp_text, 0);
  			line();
  			cout << endl;
  			// To Ask The User If He/She Would Like To Remove Any Other Flat Number(s) From The Defaulters' List
  			do {
  				cout << endl;
  				line();
  				bill_lines("Would You Like To Remove Any More Flat(s) From The Defaulters' List ? (Y/N)" ,0);
  				line();
  				cout << "-> ";
  				cin >> key;
  				if (toupper(key) == 'N')
  					control = 1;
  				else if (toupper(key) == 'Y')
  					control = 0;
  				else
  					continue;
  			} while (control == 3);;// (#2) End Of Do-While Loop
  			cout << endl;
  			line();
  		} while (control != 1);
  		break;

  	case 3:
  		empty_default_list(resident_list);
  		cout << endl;
  		line();
  		heading_print("The List Has Been Emptied !");
  		line();
  		cout << endl;
  		break;

  	case 4:
  		return;

  	default:
  		cout << "Invalid Option Entered, Please Try Again !" << endl;
  	}

  	// To Ask The User If He/She Would Like To Change Any Other Values
  	control = 3;
  	do {
  		cout << endl << "Would You Like To Change Any Other Values ? (Y/N)" << endl;
  		cout << "-> ";
        cin >> key;
  		if (toupper(key) == 'N')
  			control = 1;
  		else if (toupper(key) == 'Y')
  			control = 0;
  		else
  			continue;
  	} while (control == 3);// (#3) End Of Do-While Loop
    
    cout << endl;
  	line();
  } while (control == 0);// (#1) End Of Do-While Loop
  }

  void residents :: value_changer(int &int_option, float &rate, float &penalty, float &car_rate, float &floor_rate)
  {
  	// Character Option Variable
  	char char_option;

  	// Loop control variable
  	char control = 100;

  	// Declare & Initialize the variables rows and columns with their respective values
  	screen_info();

  	/*
  		(#1) The Do-While loop to change the values of the maintenance rate per square foot, the penalty amount per day,
  			 the rate per car park and the rate per floor
  	*/
  	do {
  		system("cls");	// Clear The Screen

  		line();
  		heading_print("Main Settings Menu");

  		 // Underline the heading
  		line();

  		// The Menu Options
  		cout << "-> 1. Change The Maintenance Per Sq. Ft.   |   Current Value = " << rate << " Per Sq. Ft." << endl;
  		cout << "-> 2. Change The Penalty Amount Per Day    |   Current Value = " << penalty << " Per Day" << endl;
  		cout << "-> 3. Change The Rate Per Car Park         |   Current Value = " << car_rate << " Per Car Park" << endl;
  		cout << "-> 4. Change The Rate Per Floor Rate       |   Current Value = " << floor_rate << " Per Floor" << endl;
  		cout << "-> 5. Exit" << endl;
  		line();

  		cout << "Enter Your Option :" << endl;
  		cout << "-> ";
  		cin >> int_option;
        cout << endl;
  		// Test for option number and carrying out the respective task
  		switch (int_option)
  		{
  		case 1:
  			cout << "Enter The Value Of The New Maintenance Per Sq. Ft. :" << endl;
  			cin >> rate;
  			break;
  		case 2:
  			cout << "Enter The Value Of The New Penalty Amount Per Day :" << endl;
  			cin >> penalty;
  			break;
  		case 3:
  			cout << "Enter The Value Of The New Rate Per Car Park :" << endl;
  			cin >> car_rate;
  			break;
  		case 4:
  			cout << "Enter The Value Of The New Rate Per Floor No. Increase :" << endl;
  			cin >> floor_rate;
  			break;
  		case 5:
             line();
  			return;
  			break;
  		default:
           line('X');
           heading_print("Invalid Option Entered ! Please Try Again !");
           line('X');
           system("pause");
           continue;
  		}
  		cout << endl;
  		line();
  		heading_print("The Value Has Been Changed Successfully !");
  		line();
  		cout << endl;

  		// (#2) Do-while loop to ask the users if there are any other values to change or not
  		do {
  			cout << endl << "Would You Like To Change Any Other Values ? (Y/N)" << endl;
  			cout << "-> ";
            cin >> char_option;

  			if (toupper(char_option) == 'N')
  				control = 1;
  			else if (toupper(char_option) == 'Y')
  				control = 0;
  			else
  			{
  				control = 100;
  				line('X');
                heading_print("Invalid Option Entered ! Please Try Again !");
                line('X');
                continue;
  			}
  		} while (control == 100); // (#2) End Of Do-While Loop

  		// Leave A Line
  		cout << endl;

  		line();

  	} while (control == 0 || control == 100);// (#1) End Of Do-While Loop
  	/*********************************************************************************************************************/
  }


  int residents :: defaulters_list(float rate, float car_rate, float floor_rate, char input[5], float penalty, residents resident_list[42])
  {
  	// To keep count of the number of defaulters
  	int defaulter_head_count = 0;

  	// Variable To The Base Amount And The Final Amount
  	float amount, final_amount;

  	// The Temporary Sentence
  	char str_to_be[100], char_num[10];
   
  	// Get The Time Structure Declared & Initialized
    struct tm *theTime;
  	time_t tim;
  	tim = time(0);
  	theTime = localtime(&tim);

  	// For-Loop to check if there are any defaulters and to print the defaulters details in the form of a list
  	for (int ctr = 0; ctr < 42; ctr++)
  	{

  		if (resident_list[ctr].defaulter == 1)
  		{
  			// Calculating The Maintenance
  			amount = 4500 * rate;
  			final_amount = amount + (resident_list[ctr].cars*car_rate) + (int)(floor(ctr / 2)*floor_rate) + (penalty * (theTime->tm_mday - 1)); // Equation To Calculate The Maintenance


  			line();

  			sprintf(char_num, "%d", defaulter_head_count + 1);
  			strcpy(str_to_be, char_num);
  			strcat(str_to_be, ". Defaulter's Name : ");
  			strcat(str_to_be, resident_list[ctr].owner_name);
  			bill_lines(str_to_be, 1);

  			spaces(str_to_be, ctr);
  			strcat(str_to_be, "Defaulter's Flat No. : ");
        sprintf(char_num, "%d", resident_list[ctr].flat_no);
  			strcat(str_to_be, char_num);
  			bill_lines(str_to_be, 1);

  			spaces(str_to_be, ctr);
  			strcat(str_to_be, "No. Of Occupants : ");
        sprintf(char_num, "%d", resident_list[ctr].occupants_no);
  			strcat(str_to_be, char_num);
  			bill_lines(str_to_be, 1);

  			spaces(str_to_be, ctr);
  			strcat(str_to_be, "Defaulter's Flat Status. : ");
  			if (resident_list[ctr].status == 1)
  				strcat(str_to_be, "Occupied By Resident");
  			else if (resident_list[ctr].status == 2)
  				strcat(str_to_be, "Occupied By Tenant");
  			else
  				strcat(str_to_be, "The Flat Is Empty");
  			bill_lines(str_to_be, 1);

  			spaces(str_to_be, ctr);
  			strcat(str_to_be, "Maintenance Amount To Be Paid : Rs.");
  			ftoa(final_amount, char_num, 2);
  			strcat(str_to_be, char_num);
  			bill_lines(str_to_be, 1);

  			line();

  			defaulter_head_count++;
  		}
  		else
  			continue;
  	}
  	return defaulter_head_count;
  }

  void residents :: main_pay(float rate, float car_rate, float floor_rate, char input[5], float penalty, residents resident_list[42])
  {
  	// Declare & Initialize the variables rows and columns with their respective values
  	screen_info();

  	// Variable To The Base Amount And The Final Amount
  	float amount, final_amount;

  	// The Flat Counter
  	int flat_ctr;

  	// General Counter
  	int ctr;

  	//Variable To Hold Temporary Data
  	int temp, temp_sp;

  	// Declaring The Option Variable
  	char option;

  	// Creating A Character Array To Hold All The Sencteces to-be
  	char str_to_be[120];

  	// Creating A Character Array To Hold Numbers Converted Into Char
  	char char_num[15];

  	// Get The Time Structure Declared & Initialized
    struct tm *theTime;
  	time_t tim;
  	tim = time(0);
  	theTime = localtime(&tim);

  	// Calculating The Maintenance
  	flat_ctr = flat_num(input) - 1;
  	amount = 4500 * rate;
  	final_amount = amount + (resident_list[flat_ctr].cars*car_rate) + (int)(floor(flat_ctr / 2)*floor_rate) + ( penalty * (theTime->tm_mday - 1) ); // Equation To Calculate The Maintenance

  	// The Bill
  	line();
  	bill_lines("Maintenance Bill",0);
  	line();

  	strcpy(str_to_be, "Name Of The Resident (Owner) : ");
  	strcat(str_to_be, resident_list[flat_ctr].owner_name);
  	bill_lines(str_to_be, 1);

  	strcpy(str_to_be, "Flat No. : ");
    sprintf(char_num, "%d", resident_list[flat_ctr].flat_no);
  	strcat(str_to_be, char_num);
  	bill_lines(str_to_be, 1);

  	strcpy(str_to_be, "No. Of Occupants : ");
    sprintf(char_num, "%d", resident_list[flat_ctr].occupants_no);
  	strcat(str_to_be, char_num);
  	bill_lines(str_to_be, 1);

  	strcpy(str_to_be, "Status Of The Flat : ");
  	switch (resident_list[flat_ctr].status)
  	{
  	case 1:
  		strcat(str_to_be, "Resident");
  		break;
  	case 2:
  		strcat(str_to_be, "Tenent");
  		break;
  	case 3:
  		strcat(str_to_be, "Empty");
  		break;
  	}
  	bill_lines(str_to_be, 1);

  	strcpy(str_to_be, "Maintenance Paid : ");
  	switch (resident_list[flat_ctr].defaulter)
  	{
  	case 0:
  		strcat(str_to_be, "Yes");
  		break;
  	case 1:
  		strcat(str_to_be, "No");
  		break;
  	}
  	bill_lines(str_to_be, 1);

  	// The First Line Of The Bill
  	strcpy(str_to_be, "Base Amount (4500 sq. ft. X Rs.");
  	ftoa(rate, char_num, 2);
  	strcat(str_to_be, char_num);
  	strcat(str_to_be, ") :");
  	temp = strlen(str_to_be);
  	for (ctr = 0; ctr < 16; ctr++)
  		str_to_be[temp + ctr] = ' ';
  	str_to_be[temp + ctr] = '\0';
  	strcat(str_to_be, " Rs.");
  	ftoa(amount, char_num, 2);
  	strcat(str_to_be, char_num);
  	bill_lines(str_to_be, 1);
  	temp_sp = strlen(str_to_be);

  	// The Second Line Of The Bill
  	strcpy(str_to_be, "Payment Delay (In No. Of Days) :");
  	temp = strlen(str_to_be);
  	for (ctr = 0; ctr < (temp_sp - temp - 5); ctr++)
  		str_to_be[temp + ctr] = ' ';
  	str_to_be[temp + ctr] = '\0';
    sprintf(char_num, "%d", (theTime->tm_mday - 1));
  	strcat(str_to_be, char_num);
  	strcat(str_to_be, " Days");
  	bill_lines(str_to_be, 1);

  	// The Third Line Of The Bill
  	strcpy(str_to_be, "Delay Penalty @ Rs.");
  	ftoa(penalty, char_num, 2);
  	strcat(str_to_be, char_num);
  	strcat(str_to_be, " per Day :");
  	temp = strlen(str_to_be);
  	for (ctr = 0; ctr < (int)( temp_sp - temp - 7 - no_of_digits( (int)(penalty * (theTime->tm_mday - 1)) ) ) ; ctr++)
  		str_to_be[temp + ctr] = ' ';
  	str_to_be[temp + ctr] = '\0';
  	strcat(str_to_be, " Rs.");
  	ftoa((penalty * (theTime->tm_mday - 1)), char_num, 2);
  	strcat(str_to_be, char_num);
  	bill_lines(str_to_be, 1);

  	line();

  	// The Fourth Line OF the Bill
  	strcpy(str_to_be, "No. Of Car Parks Owned :");
  	temp = strlen(str_to_be);
  	for (ctr = 0; ctr < (temp_sp - temp - 4); ctr++)//
  		str_to_be[temp + ctr] = ' ';
  	str_to_be[temp + ctr] = '\0';
    sprintf(char_num, "%d", resident_list[flat_ctr].cars);
  	strcat(str_to_be, char_num);
  	strcat(str_to_be, " Car Parks");
  	bill_lines(str_to_be, 1);

  	// The Fifth Line Of The Bill
  	strcpy(str_to_be, "Maintenance Cost Per Car Park @ Rs.");
  	ftoa(car_rate, char_num, 2);
  	strcat(str_to_be, char_num);
  	strcat(str_to_be, " per Month :");
  	temp = strlen(str_to_be);
  	for (ctr = 0; ctr < (int)( temp_sp - temp - 7 - no_of_digits( (int)(car_rate * (resident_list[flat_ctr].cars)) ) ); ctr++)
  		str_to_be[temp + ctr] = ' ';
  	str_to_be[temp + ctr] = '\0';
  	strcat(str_to_be, " Rs.");
  	ftoa((car_rate * (resident_list[flat_ctr].cars)), char_num, 2);
  	strcat(str_to_be, char_num);
  	bill_lines(str_to_be, 1);

  	line();

  	// The Fourth Line OF the Bill
  	strcpy(str_to_be, "Floor No. :");
  	temp = strlen(str_to_be);
  	int correction = (int)ceil(flat_ctr/2) >= 10 ? 5 : 4;
  	for (ctr = 0; ctr < (temp_sp - temp - correction); ctr++)
         str_to_be[temp + ctr] = ' ';
  	str_to_be[temp + ctr] = '\0';
    sprintf(char_num, "%d", flat_ctr + 1);
  	strcat(str_to_be, char_num);
  	num_ending_letter(flat_ctr, str_to_be);
  	bill_lines(str_to_be, 1);

  	// The Fifth Line Of The Bill
  	strcpy(str_to_be, "Maintenance For The Floor @ Rs.");
  	ftoa(floor_rate, char_num, 2);
  	strcat(str_to_be, char_num);
  	strcat(str_to_be, " per Floor Increase :");
  	temp = strlen(str_to_be);
  	for (ctr = 0; ctr < (int)( temp_sp - 7 - temp - no_of_digits((int)(floor_rate * flat_ctr)) ); ctr++)
  		str_to_be[temp + ctr] = ' ';
  	str_to_be[temp + ctr] = '\0';
  	ftoa((floor_rate * flat_ctr), char_num, 2);
  	if ((floor_rate * flat_ctr) == 0)
  	{
  		strcat(str_to_be, "Rs.");
  	}
  	else
  	{
  		strcat(str_to_be, " Rs.");
  	}

  	strcat(str_to_be, char_num);
  	bill_lines(str_to_be, 1);

  	line();
    strcpy(str_to_be, "Total Maintenance Amount For Flat No. (Inc. GST) Is =    ");
  	strcat(str_to_be, "Rs.");
    sprintf(char_num, "%.2f", (final_amount > 5000 ? (float)( (final_amount*118)/100 ) :  final_amount) );
  	strcat(str_to_be, char_num);
  	bill_lines(str_to_be,1);

  	line();

  	cout << endl << endl;

   if(resident_list[flat_ctr].defaulter == 1)
   {
  	cout << "Has The Resident Of Flat No. " << input << " Paid His/Her Maintenance ? (Y/N)" << endl;
  	cout << "-> ";
    cin >> option;
  	tolower(option);
  	if (option == 'y')
  		resident_list[flat_ctr].defaulter = 0;
  	else if (option == 'n')
  		resident_list[flat_ctr].defaulter = 1;
   }
  }

void residents :: spaces(char str_to_be[100], int ctr)
  {
  	int ctr_size = no_of_digits(ctr+1), x = 0;
  	while (x < ctr_size + 2)
  	{
  		str_to_be[x] = ' ';
  		x++;
  	}
  	str_to_be[x] = '\0';
  }
