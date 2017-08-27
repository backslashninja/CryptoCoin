#include <iostream>
#include <conio.h>  //for getch
#include <stdio.h>  //for remove, rename etc.
#include <stdlib.h> //for system commands
#include <string.h> //for strcpy and strcmp
#include <windows.h>
#include <ctime>

#include "user.h"
#include "transaction.h"

#define ENTER 13
#define TAB 9
#define BKSP 8


using namespace std;

char mk[20]="antriksh";
void getkey(char [], int);

void maketransaction(int ,int ,int );



int main()
{   int x,ano,bal; char n1[50],key[20],ans='n';

do
{
    system("cls");
    cout << "\t\tWelcome to CryptoCoin \n\nWhat are you here for ?\n ";
    cout <<"1. create new account \n 2. delete account\n 3. make transaction\n 4. display Account balances\n\t\t\t";
    cin>>x;


    switch(x)
    {
        {
            case 1 : cout<<"You need to enter the master key...  \n ";
                     getkey(key,20);
                     if(!strcmp(key,mk))
                     { do
                        {
                       cout<<"\nEnter the account no. ";    cin>>ano;
                       cout<<"\nEnter the name of the user..  ";  fflush(stdin);  gets(n1);
                       cout<<"\nEnter the Starting amount.. ";  cin>>bal;
                       getkey(key,20);
                       user u1(ano, n1,bal,key);
                       u1.storeuser();
                       u1.display();
                       cout<<"do you want to add more ?"; cin>>ans;
                        }while(ans!='n'||ans!='N');
                     }else cout<<"You are not Recognised by the system.. ";
                     break;
        }

        {
            case 2 : cout<<"You need to enter the master key...  \n ";
                     getkey(key,20);
                     if(!strcmp(key,mk))
                     {
                      cout<<"Enter the account no. of the user whose account you want to delete...  ";
                      cin>>ano; cout<<endl;
                      user u1;
                      u1.deleteuser(ano);

                     }else cout<<"You are not Recognised by the system.. ";
                     break;
        }
        {   case 3 :  int perno,peeno;
                     cout<<"Enter the account no. of the Payer  ";  cin>>perno;
                     cout<<"Enter the account no. of the Payee  ";  cin>>peeno;
                     cout<<"Enter the amount to be transferred..  "; cin>>bal;

                     maketransaction(perno,peeno,bal);
                     break;

        }
        {
            case 4 : user u1;
                     u1.displayall();
                     break;
        }
        {
            default : cout<<"INVALID INPUT";
        }

    } cout<<"Do you want to exit crypto coin ?";   cin>>ans;
}while(ans!='y'||ans!='Y');                                                //not working...
}

void maketransaction(int perno, int peeno, int amt)
{   user payer,payee;  char key[20];
    payer.searchuser(perno);  payee.searchuser(peeno);

    transaction t1(payer,payee,amt);

    cout<<"\nThe Payer needs to enter his/her secret key for authorizing the transaction.. ";
    getkey(key,20);
    if(t1.verifytrans(key)) cout<<"\n TRANSACTION AUTHORIZED !!! \n";
    else cout<<"You are not Recognised by the system.. ";

}



void getkey(char key[], int size)
{
  int i = 0;
	char ch;
    cout<<"Enter your Key(max length=20). Hit ENTER to confirm...  ";
	while(1){
		ch = getch();	//get key

		if(ch == ENTER || ch == TAB){
			key[i] = '\0';
			break;
		}else if(ch == BKSP){
			if(i > 0){
				i--;
				printf("\b \b");		//for backspace
			}
		}else{
			key[i++] = ch;
			printf("* \b");				//to replace password character with *
		}
	}
    cout<<endl;
}



