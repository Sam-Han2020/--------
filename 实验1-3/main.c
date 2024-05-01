#include <stdio.h>
#include "main.h"
#include "menu.h"

int main()
{
    Cards c;
    initSystem2(&c);
    char ipt[10];
    int choice;
    do
    {
        system("cls");
        showMenu();
        do
        {
            scanf("%s", ipt);
        } while (ipt == '\n');
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
                    LogIn();
                    break;
                case 4:
                    LogOff();
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
            showDefault();
        }
    } while (choice);
    return 0;
}