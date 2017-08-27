#include "user.h"

void user::givekey(char key[])
{
    strcpy(key,sk);
}

void user::givename(char n[])
{
    strcpy(n,name);
}

void user::givedata(int &ano,char n[50],int &bal,char key[20])
{
    ano=accno;
    strcpy(n,name);
    bal=balance;
    strcpy(key,sk);
}

void user::usercpy(user u1)
{
    int ano,bal; char key[20],n[50];
    givedata(ano,n,bal,key);
    accno=ano;
    balance=bal;
    strcpy(name,n);
    strcpy(sk,key);
}

void user::display()
{
    {   cout<<"\n\nAccount no. - "<<accno<<endl;
        cout<<"Name - ";  puts(name);
        cout<<"Balance = "<<balance<<" Crypto Coins \n\n";
    }
}

void user::storeuser()
{
    ofstream fout;
	fout.open( "users.bin", ios::out | ios::binary | ios::app);
    fout.write( (char*)this, sizeof(*this));
    fout.close();
}

void user::displayall()
{
    ifstream fin;
    fin.open("users.bin" , ios::in | ios::binary);
    if(!fin) cout<<"file not found";
    else{
         fin.read((char*)this, sizeof(*this));
         while(!fin.eof())
         {  display();
            fin.read((char*)this, sizeof(*this));
         }
        }  fin.close();

}

void user::searchuser(int ano)
{
    ifstream fin;
    fin.open("users.bin", ios::in | ios::binary);
    fin.read((char*)this, sizeof(*this));
    while(!fin.eof())
    {
        if(ano==accno){ fin.close(); break;}
        else fin.read((char*)this, sizeof(*this));
    }
    if(fin.eof()) cout<<"There is no user with this account no. !!";
    fin.close();
}

void user::updateuser(int ano, int amt)
{
    int dir,size=sizeof(*this);
    fstream file;
    file.open("users.bin",ios::in|ios::out|ios::ate|ios::binary);  //ate-update.... points last byte of first record;
    file.seekg(0);
    file.read((char*)this, sizeof(*this));                                                //points first byte
    while(!file.eof())
     {
        if(ano==accno)
        {   int bal=balance+amt;
            if(bal>=0){balance=balance+amt;
                      cout<<"Now the balance of "; fputs(name,stdout); cout<<" is "<<balance<<endl;}
            else{ cout<<"\n You don't have the required balance  \n"; }
			dir= file.tellp();
			dir-=size;
            file.seekp(dir);
            file.write((char*)this,sizeof(*this));        //feeding actually at he wrong position
        }
        file.read((char*)this, sizeof(*this));
     }
      file.close();
}

void user::deleteuser(int ano)
{
    ifstream fin;
    fin.open("users.bin", ios::in | ios::binary);
    ofstream tout;
    tout.open("temp.bin", ios::out|ios::binary|ios::trunc);
    fin.read((char*)this, sizeof(*this));
    while(!fin.eof())
    {
        if(ano!=accno) tout.write((char*)this, sizeof(*this));
        else{cout<<"the account going to be deleted is... \n";  display();}
        fin.read((char*)this, sizeof(*this));
    }
    fin.close();
    tout.close();
    remove("users.bin");
    rename("temp.bin","users.bin");
}
