#include<bits/stdc++.h>
#include<stdio.h>
#include <windows.h>
using namespace std;
void intro(){
  cout<<"\n\t%%%%%%%%%       ##       ##  %%%%%%%%%%%  **********     %%%  %%%%    ##       ## ";
  cout<<"\n\t%%              ##       ##    %%     %%  **********     %%%  %%%     ##       ##   ";
  cout<<"\n\t%%%%%%%%%%      ##       ##    %%     %%  **********     %%% %%       ##       ##         ";
  cout<<"\n\t        %%%     ##       ##    %%     %%  **********     %%%   %%%    ##       ##      ";
  cout<<"\n\t%%%%%%%%%%%     ###########  %%%%%%%%%%%  **********     %%%   %%%%   ########### ";
}


int main()
{
    intro();
    cout<<endl;
    cout<<"Enter n to play the game and Q to quiet"<<endl;
    char ch;
    cin>>ch;
    if(ch=='n'){
        system("CLS");
    }
    else{
        _Exit(10);
    }
    return 0;
}
