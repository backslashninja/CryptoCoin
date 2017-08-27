#include "transaction.h"


transaction::transaction(user per, user pee, int amt)
{
  tractime=time(NULL);
  payer.usercpy(per);
  payer.usercpy(pee);
  amount=amt;
}

int verifytrans(char key[20])
{char sectretkey[20];
 fputs(payer.sk,stdout);
 //if(!strcmp(payer.sk,key)) return 1;
 //else return 0;
}

/*
void transaction::createtrans()
{   time_t hold_time;
    char key[20],skey[20]; int bal;
    user payer,payee;
    payer.searchuser(perno);  payee.searchuser(peeno);
    cout<<"the payer needs to enter his secret key...  \n";

    getkey(key,20);
    //payer.givekey(skey,20);

    if(!strcmp(key,skey))
    {
     bal=0-amt;
     payer.updateuser(perno, bal);
     payee.updateuser(peeno, amt);



     long int pk= createpk(hold_time,skey, amt);


    }

    else cout<<"You are not Recognised by the system.. ";
}

long int transaction::createpk(time_t hold_time,char skey[20], int amt)
{   int i=0,num; char ch;
    while(i>20)
    {
        ch=skey[i];
        num += int(ch);
        i++;
    }
    long int pk= ((hold_time + num +amt)*7-4847555)*2-56774*23;
    return pk;
} */
