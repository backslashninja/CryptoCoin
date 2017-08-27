#ifndef TRANSACTION_H
#define TRANSACTION_H

/*#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h> */
#include "user.h "
#include<ctime>


class transaction
{
    public:
        transaction(user per, user pee, int amt);
        int verifytrans(char key[]);

    protected:

    private:
        user payer;
        user payee;
        int amount;
        long int pk;
        time_t tractime;
};

#endif // TRANSACTION_H

