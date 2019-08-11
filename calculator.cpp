// Calculator program
// This program is for a calculator in which the user enters his/hers
// expression into a string and then it is converted to postfix form and
// then solved, all calculations are store in a .bat file with date
// and time of calculaton and a label name + comments given by the
// user to enable easy search for the needed calculations at a later date

#include<iostream>
#include<math.h>
#include<iomanip>
#include<string.h>
#include<windows.h>

using namespace std;

class calculator
{
  char input[80];
  int output;
  int price;
  float percent;
  int rows, columns;

  struct inter{
    union
    {
      int a;
      char op;
    }element;
    int type_used; // 0 = a and 1 = op
}inter[80];


  int symbol_pri_list(char a)
  {
    switch(a)
    {
      case '^':
        return 3;
      break;

      case '/':
        return 2;
      break;

      case '*':
        return 2;
      break;

      case '+':
        return 1;
      break;

      case '-':
        return 1;
      break;

      default:
        return 0;
    }
  }
  public:
  void heading_print(const char *text);
  void screen_info();
  void text_lines(const char *text, int option);
  void line(char a = '-');
  void text_centre(char text[]);
  void getdata()
  {
    cout << "|| ";
    cin >> input;
    if(input[0] == '#')
      percentage_calculator();
    else
      input_chk();
  }
  void input_chk();
  long int powr(int exp);
  void solve();
  int infix_postfix();
  void operation(int, int, char, long int[], int&);
  void percentage_calculator();
  int row()
  {return rows;}
};

void calculator_func();

void calculator_func()
{
  calculator obj;
  int option;
  do{
  obj.heading_print("Calculator");
  obj.text_lines("Symbols To Use", 0);
  obj.line();
  obj.text_lines("1. Percentage Calculator (Use Separately : #)", 1);
  obj.text_lines("2. Addition (+)", 1);
  obj.text_lines("3. Subtraction (-)", 1);
  obj.text_lines("4. Multiplication (*)", 1);
  obj.text_lines("5. Division (/)", 1);
  obj.text_lines("6. Power (^)", 1);
  obj.text_lines("7. Brackets \'()\'", 1);
  obj.line();
  obj.text_lines("Enter the Expression to Calculator :",1);
  obj.getdata();
  obj.line();
  obj.text_lines("Would You Like To Continue ? (Enter 0 To Exit & 1 To Continue)", 1);
  cout << "-> ";
  cin >> option;
  system("cls");
}while(option != 0);

obj.line();
for (int i = 0; i < (obj.row() / 2) - 2; i++)
    cout << endl;
obj.heading_print("Returning Back To Main Menu...");
for (int i = 0; i < (obj.row() / 2) - 3; i++)
    cout << endl;
obj.line();
return;

}

void calculator :: screen_info()
{
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
      columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
      rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void calculator::heading_print(const char *text)
  {
  	// Declare & Initialize the variables rows and columns with their respective values
  	screen_info();

  	int len = strlen(text);
   for(int x = 0; x < columns; x++)
   cout << '-';
  	cout << '|'
  		<< setw((columns / 2) + (int)ceil(len / 2))
  		<< text
  		<< setw((columns / 2) - (int)ceil(len / 2) - 1)
  		<< '|';
  		for(int x = 0; x < columns; x++)
   cout << '-';
  }
  
// align text
//0. centre
//1. left align
//2. right align
void calculator :: text_lines(const char *text, int option)
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

void calculator :: line(char a)
{
  // Declare & Initialize the variables rows and columns with their respective values
  screen_info();

  for (int ctr = 0; ctr < columns; ctr++) // The Top Margin for the heading
    cout << a;
}

void calculator :: input_chk()
{
    int ctr = 0, bool_num = 0;
    while(input[ctr] != '\0')
    {
      if(isdigit(input[ctr]) || input[0] == '#' || input[ctr] == '+' || input[ctr] == '-' || input[ctr] == '*' || input[ctr] == '/' || input[ctr] == '^' || input[ctr] == '(' || input[ctr] == ')')
      {
        ctr++;
        continue;
      }
      else
      {
        bool_num = 1;
        cout << "|| Error : \'" << input[ctr] << "\' is not a valid symbol, Please try again !" << endl;
        ctr++;
      }
    }
    
    if(bool_num == 0)
    {
      cout << "-> Answer To The Expression " << input << " = ";
      solve();
    }
    else
        return;
}

void calculator :: solve()
{
  int op2, op1, ctr = 0, top = -1, ctr_i;
  long int stack[40];
  char *ans;
  ctr_i = infix_postfix();
  while(ctr_i > 0)
  {
    /*if(inter[ctr].type_used == 0)
    cout << inter[ctr].element.a << endl;
    else
    cout << inter[ctr].element.op << endl;

    ctr++;
    ctr_i--;*/
    
    if(inter[ctr].type_used == 0)// check if the inter[ctr] is a number
    {
      stack[++top] = inter[ctr].element.a;
    }
    else
    {
      op1 = stack[top--];
      op2 = stack[top--];
      operation(op1, op2, inter[ctr].element.op, stack, top);
    }
    ctr++;
    ctr_i--;
  }
  cout << stack[top] << endl;
}
  
void calculator :: operation(int op1, int op2, char ch, long int stack[], int &top)
{
  switch(ch)
  {
    case '+':
    stack[++top] = op2 + op1;
    break;
    case '-':
    stack[++top] = op2 - op1;
    break;
    case '*':
         //cout << op1 << endl << op2 << endl << op1* op2 << endl;
    stack[++top] = op2 * op1;
    break;
    case '/':
    stack[++top] = op2 / op1;
    break;
    case '^':
    stack[++top] = (int)pow(op2, op1);
    break;
  }
}
long int calculator :: powr(int exp)
{
     long int answer = 1;
     int ctr = 0;
     while(ctr < exp)
     {
               answer *= 10;
               ctr++;
     }
     return answer;
}

int calculator :: infix_postfix()
{
  int ctr = 0, top = -1, ctr_i = 0;
  char stack[40];
  while(input[ctr] != '\0')
  {
    if(isdigit(input[ctr]))
    {
      int len = ctr;
      // find the length of number
      while(isdigit(input[len]))
      {
        len++;
      }
      len = len - ctr; // len is now the length of the number
      inter[ctr_i].element.a = 0; // setting the number to 0
      inter[ctr_i].type_used = 0; // value is stored in a now
      
      while(len > 0)
      {
        inter[ctr_i].element.a += ((input[ctr] - '0') * powr(len-1));
        len--;
        ctr++;
      }
     
      ctr--;
      ctr_i++;
      
    }
    else if(input[ctr] == '(')
    {
      stack[++top] = input[ctr];
    }
    else if(input[ctr] == '+' || input[ctr] == '-' || input[ctr] == '*' || input[ctr] == '/' || input[ctr] == '^')
    {
      while(symbol_pri_list(stack[top]) >= symbol_pri_list(input[ctr]) && top >=0)
      {
        inter[ctr_i].element.op = stack[top];
        inter[ctr_i++].type_used = 1; // the value is stored in op
        top--;
      }
      stack[++top] = input[ctr];
    }
    else if(input[ctr] == ')')
    {
      while(stack[top] != '(' && top >=0)
      {
        inter[ctr_i].type_used = 1; // the value is stored in op
        inter[ctr_i++].element.op = stack[top];
        top--;
      }
      top--; // remove the '(' from the top of the stack
    }
    ctr++;
  }
  while(top >= 0)
  {
    inter[ctr_i].type_used = 1; // the value is stored in op
    inter[ctr_i++].element.op = stack[top]; // the value is stored in op
    top--;
  }
  return ctr_i;
}

void calculator :: percentage_calculator()
{
  text_lines("Enter the Amount to Calculate on :", 1);
  cout << "|| ";
  cin >> price;
  text_lines("Enter the Percentage :", 1);
  cout << "|| ";
  cin >> percent;

  //line 1
  char line[50];
  sprintf(line, "%.2f %% of %d is = %.2f", percent, price, (float)( (percent*price)/100 ) );
  text_lines(line, 1);

  //line 2
  line[0] = '\0';
  sprintf(line, "The Total Amount is = %.2f", (float)( ((percent*price)/100) + price ) );
  text_lines(line,1);
}
