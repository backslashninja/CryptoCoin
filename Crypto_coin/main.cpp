#include <iostream>
#include <conio.h>  //for getch
#include <stdio.h>  //for remove, rename etc.
#include <stdlib.h> //for system commands
#include <string.h> //for strcpy and strcmp
#include <windows.h>
#include <ctime>
#include <fstream>

#include "user.h"
#include "transaction.h"

#define ENTER 13
#define TAB 9
#define BKSP 8


using namespace std;

char mk[20]="antriksh";
void getkey(char [], int);

void maketransaction(int ,int ,int );
//void feedtransaction(char[],int,int,int,time_t);
long int createpk(char[],int,int,int,time_t);
bool verifypk(char[],int,int,int,long int,long int);



int main()
{   int x,ano,bal; char n1[50],key[20],ans='n';

do
{
    system("cls");
    cout << "\t\tWelcome to CryptoCoin \n\nWhat are you here for ?\n ";
    cout <<"1. create new account \n 2. delete account\n 3. make transaction";
    cout<<"\n 4. Verify a transaction \n 5. display Account balances\n\t\t\t";
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
            case 4 : int amt,peeno,perno; long int pk,timet;  char skey[20];
                     cout<<"\nEnter the time of transaction  ";  cin>>timet;                 //will work till 2038;
                     cout<<"\nEnter the account no. of the payer "; cin>>perno;
                     cout<<"\nEnter the account no. of the payee "; cin>>peeno;
                     cout<<"\nEnter the amount paid ";    cin>>amt;
                     cout<<"\nEnter the digital signatures of the payer "; cin>>pk;
                     cout<<"\nEnter the sectret key of the user  "; getkey(skey,20);

                     if(verifypk(skey,perno,peeno,amt,timet ,pk ))
                        cout<<"\nThis transaction was authorised by the system. \n";
                     else cout<<"\nThis transaction  is FRAUD !!! \n";
                     break;
        }
        {
            case 5 : user u1;
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
{   time_t holdtime;
    holdtime=time(NULL);
    long int transtime=holdtime;
    user payer,payee;  char key[20],skey[20],pername[50],peename[50];
    payer.searchuser(perno);  payee.searchuser(peeno);
    cout<<"\nThe Payer needs to enter his/her secret key for authorizing the transaction.. ";
    getkey(key,20);
    payer.givekey(skey);
    payer.givename(pername);
    payee.givename(peename);
    if(!strcmp(key,skey))
    {
        cout<<"\n TRANSACTION AUTHORIZED !!! \n";
        payee.updateuser(peeno,amt);
        payer.updateuser(perno,0-amt);

        long int pk=createpk(skey,perno,peeno,amt,transtime);

        cout<<"At time "<<transtime<<" ";
        cout<<pername;
        cout<<" pays ";
        cout<<peename;
        cout<<"an amount of ";
        cout<<amt;
        cout<<" Crypto coins. \nDigital Signature of Payer : ";
        cout<<pk;
        cout<<"\n\n";

        ofstream fout;
        fout.open("Transactions.txt",ios::out|ios::app);

        fout<<"At time "<<transtime<<" ";
        fout<<pername;
        fout<<" pays ";
        fout<<peename;
        fout<<"an amount of ";
        fout<<amt;
        fout<<" Crypto coins. \nDigital Signature of Payer : ";
        fout<<pk;
        fout<<"\n\n";

        fout.close();

    }
    else cout<<"You are not Recognised by the system.. ";
}


long int createpk(char skey[],int perno,int peeno,int amt,long int transtime)
{
    int i=0,num; char ch;
    while(i>20)
    {
        ch=skey[i];
        num += int(ch);
        i++;
    }

    long int pk=(num + peeno+ transtime)*perno-35466644343;
}

bool verifypk(char skey[],int perno,int peeno,int amt,long int transtime,long int vpk)
{
    int i=0,num; char ch;
    while(i>20)
    {
        ch=skey[i];
        num += int(ch);
        i++;
    }

    long int pk=(num + peeno+ transtime)*perno-35466644343;

    if(pk==vpk) return true;
    else return false;
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



