#include<iostream.h>
#include<cstring>
#include<conio.h>

int main()
{
bool valid;
int camp,i=0,flag=1,j;
const char pass[] = "hello";//correct password
char str2[15];

do
{
cout<<"enter the password : ";
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
        flag=0;
        break;
        }
}


//if(flags)
//valid=true;

if (!flag)//(valid != true)
{
cout<<"\n\nSorry, that password is invalid."<<endl;
flag=1;
system("pause");
system("cls");
exit(0);
}

}while(!flag);

cout<<"\nThe password is correct!"<<endl;
system("pause");
}
