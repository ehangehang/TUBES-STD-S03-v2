#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>
using namespace std;

typedef struct elmParent *adrParent;
typedef struct elmChild *adrChild;
typedef struct elmGames *adrGames;
struct dataGame {
    string judul;
    string studio;
    string tahun;
    string description;
    int rating;
    int harga;
};
struct elmParent {
    string genre;
    adrParent nextParent;
    adrChild firstChild;
};
struct elmChild {
    adrGames infoChild;
    adrChild nextChild;
};
struct elmGames {
    dataGame info;
    adrGames nextGame;
    adrGames prevGame;
};
struct listParent {
    adrParent firstParent;
    adrParent lastParent;
};
struct listGames {
    adrGames firstGames;
    adrGames lastGames;
};
struct listCart {
    adrGames firstCart;
    adrGames lastCart;
};

//INIT
void createListParent(listParent &P);
void createListGame(listGames &G);
adrParent newGenre(string genre);
adrGames newGame(dataGame game);
void createListCart(listCart &C);

//ADD
void addParentFirst(listParent &P, string genre);
void addGameLast(listParent &P, listGames &G, dataGame game);
adrParent searchGenre(listParent P, string genre);
adrGames searchGameJudul(listGames G, string gameJudul);
void addChildToParent(listParent &P, listGames G, string genre, string gameJudul);

//DELETE
void deleteGenre(listParent &P, string genre, adrParent &storeP);
void deleteGame(listParent &P, listGames &G, string judulGame, adrGames &storeG);
void deleteChild(listParent &P, adrGames storeG, adrChild &storeC);
void deleteChildofParent(listParent &P, string judulGame);

//PRINTING
void printParent(listParent P);
void printListGame(listGames G);
void printParentChild(listParent P);
//customer side
void printGenreDetail(listParent P, string genre);
void printSpcGameDetail(listParent P, listGames G, string judulGame);
void printGenreMin(listParent P, string genre);
void printGenreMax(listParent P, string genre);

//CART
void addToCart(listCart &C, listGames G, string judulGame);
void printCart(listCart C);
int sumCart(listCart C);

//fungsi tambahan
float meanGenre(listParent P, string genre);

//MENU
void login(int userChoice, listParent &P, listGames &G, listCart &C);
void menuChoices(int userChoice);
void menuAdmin(int user, listParent &P, listGames &G, listCart &C);
void menuCustomer(int user, listParent &P, listGames &G, listCart &C);

#endif // MLL_H_INCLUDED
