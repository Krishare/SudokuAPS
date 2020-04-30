#include<bits/stdc++.h>
#include<stdio.h>
#include <windows.h>
using namespace std;
void rules();
void choice();

void Rules()
{
      cout<<"Games would be divided into three parts"<<endl;
      cout<<"\t*Easy Level"<<endl;
      cout<<"\t*Medium Level"<<endl;
      cout<<"\t*Hard Level"<<endl;
      cout<<":Easy level will have 7 life/chances for the wrong attempt"<<endl;
      cout<<":Medium level will have 4 life/chances for the wrong attempt"<<endl;
      cout<<":Hard Level will have 2 life/chances for the wrong attempt"<<endl;
      cout<<":After exhausting all the life game will be ended"<<endl;
      choice();
}
void intro()
{
cout<<"\n\t%%%%%%%%%       ##       ##  %%%%%%%%%%%  **********     %%%  %%%%    ##       ## ";
  cout<<"\n\t%%              ##       ##    %%     %%  **********     %%%  %%%     ##       ##   ";
  cout<<"\n\t%%%%%%%%%%      ##       ##    %%     %%  **********     %%% %%       ##       ##         ";
  cout<<"\n\t        %%%     ##       ##    %%     %%  **********     %%%   %%%    ##       ##      ";
  cout<<"\n\t%%%%%%%%%%%     ###########  %%%%%%%%%%%  **********     %%%   %%%%   ########### ";
  cout<<endl;
cout<<"Enter n to play the game and Q to quit"<<endl;
    char ch;
    cin>>ch;
    if(ch=='n'){
        system("CLS");
        Rules();
        cout<<endl;
    }
    else{
        _Exit(10);
    }

}
void choice()
{
     cout<<"Enter n to continue the game and q to go back"<<endl;
      char ch1;
      cin>>ch1;
      if(ch1=='n'){
        system("cls");
        cout<<"Choose the Level,E for easy,M for medium,H for hard"<<endl;
      }
      if(ch1=='q'){
            system("cls");
        intro();

      }
    char m;
    cin>>m;
    while(m!='q'){
        intro();
    }

}
int main()
{
    intro();
    cout<<endl;
    choice();
    cout<<endl;


    return 0;
}
