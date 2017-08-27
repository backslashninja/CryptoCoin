#ifndef USER_H
#define USER_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

class user
{
protected:

    int accno;
    char name[50];
    int balance;
    char sk[20];

public:
    user(int ano=0 , char n1[50]="no name" , int bal=0 , char key[20]="no key")
    {
        accno=ano;
        strcpy(name,n1);
        balance=bal;
        strcpy(sk,key);
    }
    void givedata(int &ano,char n[50],int &bal,char key[20]);
    void usercpy(user u1);
    void updateuser(int ano, int );
    void searchuser(int ano);
    void display();
    void storeuser();
    void displayall();
    void deleteuser(int ano);
};

#endif // USER_H
