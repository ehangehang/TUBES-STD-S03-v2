#include "mll.h"

int main()
{
    listParent P;
    listGames G;
    listCart C;

    //init list
    createListParent(P);
    createListGame(G);
    createListCart(C);

    int userChoice;
    login(userChoice, P, G, C);
    return 0;
}
