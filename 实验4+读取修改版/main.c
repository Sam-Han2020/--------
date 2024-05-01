#include <stdio.h>
#include "service.h"
#include "card_service.h"
#include "billing_service.h"
#include "record_service.h"
#include "menu.h"
#include "tools.h"

int main()
{
    Cards c;
    Billings b;
    Charges m;
    initSystem(&c,&b,&m);
    char ipt[10];
    int choice = 9;
    do
    {
        system("cls");
        showMenu();
        do
        {
            scanf("%s", ipt);
        } while (ipt==NULL);
        choice = ipt[0] - '0';
        if (0 <= choice && choice <= 8)
        {
            switch (choice)
            {
                case 1:
                    ReadCard(&c,&m);
                    break;
                case 2:
                    SearchCard(&c);
                    break;
                case 3:
                    LogIn(&c,&b);
                    break;
                case 4:
                    LogOff(&c,&b);
                    break;
                case 5:
                    InsertMoney(&c,&m);
                    break;
                case 6:
                    GetMoney(&c,&m);
                    break;
                case 7:
                    ShowStatistics(&c,&b,&m);
                    break;
                case 8:
                    SignOff(&c,&m);
                    break;
                case 0:
                    Exit(&c,&b,&m);
                    break;
                default:
                    showDefault();
                    break;
            }
        }
        else
        {
            choice=9;
            showDefault();
        } 
    } while (choice);
    return 0;
}