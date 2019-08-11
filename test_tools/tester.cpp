#include<iostream.h>
int main()
{
    int num, num_arr[4];
    cin >> num;
    int ctr = 0;
     while(num > 0)
     {
               num_arr[ctr] = num%10;
               num /= 10;
               ctr++;
     }
     cout << ctr;
     for(int x = 0; x < ctr; x++)
     {
             num_arr[ctr] = num_arr[x];
             ctr--;
     }
     for(int y =0 ;y < 3; y++)
     cout << num_arr[y];
     system("pause");
}
