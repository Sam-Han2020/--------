#include <stdio.h>
#include "service.h"
#include "menu.h"

int main()
{
    Cards c;
    Billings b;
    initSystem(&c,&b);
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
                    ReadCard(&c);
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
                    InsertMoney();
                    break;
                case 6:
                    GetMoney();
                    break;
                case 7:
                    ShowStatistics();
                    break;
                case 8:
                    SignOff();
                    break;
                case 0:
                    Exit(&c);
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