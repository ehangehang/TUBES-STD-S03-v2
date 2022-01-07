#include "mll.h"

void createListParent(listParent &P) {
    P.firstParent = NULL;
    P.lastParent = NULL;
}

void createListGame(listGames &G) {
    G.firstGames = NULL;
    G.lastGames = NULL;
}

void createListCart(listCart &C) {
    C.firstCart = NULL;
    C.lastCart = NULL;
}

adrParent newGenre(string genre) {
    adrParent newParent = new elmParent;

    newParent->genre = genre;
    newParent->nextParent = NULL;
    newParent->firstChild = NULL;

    return newParent;
}

adrGames newGame(dataGame game) {
    adrGames newGames = new elmGames;

    newGames->info = game;
    newGames->nextGame = NULL;
    newGames->prevGame = NULL;

    return newGames;
}

void addParentFirst(listParent &P, string genre) {
    adrParent adrP = newGenre(genre);

    if (P.firstParent == NULL) {
        P.firstParent = adrP;
        P.lastParent = adrP;
    } else {
        adrP->nextParent = P.firstParent;
        P.firstParent = adrP;
    }
}

void addGameLast(listParent &P, listGames &G, dataGame game) {
    adrGames adrG = newGame(game);

    if (G.firstGames == NULL) {
        G.firstGames = adrG;
        G.lastGames = adrG;
    } else {
        G.lastGames->nextGame = adrG;
        adrG->prevGame = G.lastGames;
        G.lastGames = adrG;
    }
}

adrGames searchGameJudul(listGames G, string gameJudul) {
    if (G.firstGames == NULL) {
        return NULL;
    } else {
        adrGames helper = G.firstGames;
        while (helper != NULL) {
            if (helper->info.judul == gameJudul) {
                return helper;
            }
            helper = helper->nextGame;
        }
        return NULL;
    }
}

adrParent searchGenre(listParent P, string genre) {
    if (P.firstParent == NULL) {
        return NULL;
    } else {
        adrParent helper = P.firstParent;
        while (helper != NULL) {
            if (helper->genre == genre) {
                return helper;
            }
            helper = helper->nextParent;
        }
        return NULL;
    }
}

void addChildToParent(listParent &P, listGames G, string genre, string gameJudul) {
    adrParent gen = searchGenre(P, genre);
    adrGames game = searchGameJudul(G, gameJudul);

    adrChild C = new elmChild;
    C->infoChild = game;
    C->nextChild = NULL;

    if (gen == NULL || game == NULL) {
        cout << "Input salah! Genre/Game tidak ditemukan" << endl;
    } else {
        adrChild helper = gen->firstChild;
        bool found = false;
        while (helper != NULL && found == false) {
            if (helper->infoChild->info.judul == C->infoChild->info.judul) {
                found = true;
            }
            helper = helper->nextChild;
        }
        if (found == false) {
            if (gen->firstChild == NULL) {
                gen->firstChild = C;
            } else {
                C->nextChild = gen->firstChild;
                gen->firstChild = C;
            }
        } else {
            cout << "Game sudah ada di genre!!" << endl;
        }
    }
}

void deleteGenre(listParent &P, string genre, adrParent &storeP) {
    bool found = false;

    if (P.firstParent == NULL) {
        cout << "List kosong!" << endl;
        storeP = NULL;
    } else {
        if (P.firstParent->genre == genre) {
            storeP = P.firstParent;
            P.firstParent = P.firstParent->nextParent;
            storeP->nextParent = NULL;
            found = true;
        } else if (P.lastParent->genre == genre) {
            adrParent helperP = P.firstParent;
            while (helperP->nextParent != P.lastParent) {
                helperP = helperP->nextParent;
            }
            storeP = P.lastParent;
            P.lastParent = helperP;
            helperP->nextParent = NULL;
            found = true;
        } else {
            adrParent helperA = P.firstParent;
            adrParent helperB = P.firstParent;
            while (helperB != NULL && found == false) {
                if (helperB->genre == genre) {
                    helperA->nextParent = helperB->nextParent;
                    helperB->nextParent = NULL;
                    storeP = helperB;
                    found = true;
                }
                helperA = helperB;
                helperB = helperB->nextParent;
            }
        }

        if (found == false) {
            cout << "Genre tidak ditemukan!" << endl;
        }
    }
}

void deleteGame(listParent &P, listGames &G, string judulGame, adrGames &storeG) {
    bool found = false;
    adrParent adrP, helperP;
    adrChild storeC;

    if (G.firstGames == NULL) {
        cout << "List kosong!" << endl;
        storeG = NULL;
    } else {
        if (G.firstGames->info.judul == judulGame) {
            storeG = G.firstGames;
            if (G.firstGames->nextGame != NULL) {
                G.firstGames = G.firstGames->nextGame;
            } else {
                G.firstGames = NULL;
            }
            storeG->nextGame = NULL;
            found = true;
        } else if (G.lastGames->info.judul == judulGame) {
            storeG = G.lastGames;
            G.lastGames = G.lastGames->prevGame;
            storeG->prevGame = NULL;
            G.lastGames->nextGame = NULL;
            found = true;
        } else {
            adrGames helperG = G.firstGames;
            while (helperG != NULL && found == false) {
                if (helperG->info.judul == judulGame) {
                    helperG->prevGame->nextGame = helperG->nextGame;
                    helperG->nextGame->prevGame = helperG->prevGame;
                    helperG->nextGame = NULL;
                    helperG->prevGame = NULL;
                    storeG = helperG;
                    found = true;
                }
                helperG = helperG->nextGame;
            }
        }

        if (found == false) {
            cout << "Game tidak ditemukan!" << endl;
        }else {
            deleteChild(P, storeG, storeC);
        }
    }
}

void deleteChild(listParent &P, adrGames storeG, adrChild &storeC) {
    adrParent helperGenre = P.firstParent;

    while (helperGenre != NULL) {
        if (helperGenre->firstChild != NULL) {
            adrChild helperChild = helperGenre->firstChild;
            while (helperChild != NULL) {
                if (helperChild->infoChild->info.judul == storeG->info.judul) {
                    if (helperChild == helperGenre->firstChild) {
                        storeC = helperGenre->firstChild;
                        if (helperGenre->firstChild->nextChild != NULL) {
                            helperGenre->firstChild = helperGenre->firstChild->nextChild;
                        } else {
                            helperGenre->firstChild = NULL;
                        }
                        storeC->nextChild = NULL;
                    } else {
                        adrChild helperC = helperGenre->firstChild;
                        adrChild helperCA = helperGenre->firstChild;
                        while (helperCA != NULL) {
                            if (helperCA->infoChild->info.judul == storeG->info.judul) {
                                storeC = helperCA;
                                helperC->nextChild = storeC->nextChild;
                                storeC->nextChild = NULL;
                        }
                        helperC = helperCA;
                        helperCA = helperCA->nextChild;
                        }
                    }
                }
                helperChild = helperChild->nextChild;
            }
            helperGenre = helperGenre->nextParent;
        } else {
            helperGenre = helperGenre->nextParent;
        }
    }
}

void printParent(listParent P) {
    if (P.firstParent == NULL) {
        cout << "List genre kosong!" << endl;
    } else {
        int i = 1;
        adrParent helperP = P.firstParent;
        while (helperP != NULL) {
            cout << "Genre " << i << ": " << helperP->genre << endl;
            i++;
            helperP = helperP->nextParent;
        }
    }
}

void printListGame(listGames G) {
    if (G.firstGames == NULL) {
        cout << "List game kosong!" << endl;
    } else {
        adrGames helperG = G.firstGames;
        int i = 1;
        while (helperG != NULL) {
            cout << "Data game ke-" << i << endl;
            cout << "Judul      : " << helperG->info.judul << endl;
            cout << "Studio     : " << helperG->info.studio << endl;
            cout << "Tahun      : " << helperG->info.tahun << endl;
            cout << "Description: " << helperG->info.description << endl;
            cout << "Rating     : " << helperG->info.rating << "/5" << endl;
            cout << "Harga      : " << helperG->info.harga << endl << endl;
            helperG = helperG->nextGame;
            i++;
        }
    }
}

void printParentChild(listParent P) {
    if (P.firstParent == NULL) {
        cout << "List kosong!" << endl;
    } else {
        adrParent helperPC = P.firstParent;
        int i = 1;
        while (helperPC != NULL) {
            cout << helperPC->genre << ":" << endl;
            adrChild helperC = helperPC->firstChild;
            while (helperC != NULL) {
                cout << i << ". " << helperC->infoChild->info.judul << endl;
                helperC = helperC->nextChild;
                i++;
            }
            i = 1;
            helperPC = helperPC->nextParent;
        }
    }
}

void printGenreDetail(listParent P, string genre) {
    if (P.firstParent == NULL) {
        cout << "List kosong!" << endl;
    } else {
        adrParent helper = P.firstParent;
        while (helper != NULL) {
            if (helper->genre == genre) {
                break;
            }
            helper = helper->nextParent;
        }
        if (helper->firstChild == NULL) {
            cout << "List genre kosong!" << endl;
        } else {
            adrChild helperC = helper->firstChild;
            int i = 1;
            int counter = 0;
            while (helperC != NULL) {
                counter++;
                helperC = helperC->nextChild;
            }
            cout << endl << "Terdapat " << counter << " game di genre " << helper->genre << endl << endl;
            helperC = helper->firstChild;
            while (helperC != NULL) {
                cout << "Game " << i << ":" << endl;
                cout << "Judul      : " << helperC->infoChild->info.judul << endl;
                cout << "Studio     : " << helperC->infoChild->info.studio << endl;
                cout << "Tahun Rilis: " << helperC->infoChild->info.tahun << endl;
                cout << "Deskripsi  : " << helperC->infoChild->info.description << endl;
                cout << "Rating     : " << helperC->infoChild->info.rating << endl;
                cout << "Harga      : " << helperC->infoChild->info.harga << endl << endl;
                helperC = helperC->nextChild;
                i++;
            }
        }
    }
}

void printSpcGameDetail(listParent P, listGames G, string judulGame) {
    if (P.firstParent == NULL) {
        cout << "List kosong!" << endl;
    } else {
        adrGames helperG = searchGameJudul(G, judulGame);
        if (helperG == NULL) {
            cout << "Game tidak ditemukan!!" << endl;
        } else {
            adrParent helperP = P.firstParent;
            cout << "Game ditemukan di genre:" << endl;
            int i = 1;
            while (helperP != NULL) {
                if (helperP->firstChild != NULL) {
                    adrChild helperC = helperP->firstChild;
                    while (helperC != NULL) {
                        if (helperC->infoChild->info.judul == helperG->info.judul) {
                            cout << i << ". " << helperP->genre << endl;
                            i++;
                        }
                        helperC = helperC->nextChild;
                    }
                }
                helperP = helperP->nextParent;
            }
            cout << "Judul      : " << helperG->info.judul << endl;
            cout << "Studio     : " << helperG->info.studio << endl;
            cout << "Tahun Rilis: " << helperG->info.tahun << endl;
            cout << "Deskripsi  : " << helperG->info.description << endl;
            cout << "Rating     : " << helperG->info.rating << endl;
            cout << "Harga      : " << helperG->info.harga << endl << endl;
        }

    }
}

void printGenreMin(listParent P, string genre) {
    adrParent sp = searchGenre(P, genre);
    if (sp == NULL) {
        cout << "Genre tidak ditemukan!" << endl;
    } else {
        if (sp->firstChild == NULL) {
            cout << "List genre kosong!" << endl;
        } else {
            adrChild temp = sp->firstChild;
            adrChild helper = sp->firstChild->nextChild;
            while (helper != NULL) {
                if (helper->infoChild->info.harga < temp->infoChild->info.harga) {
                    temp = helper;
                }
                helper = helper->nextChild;
            }
            cout << "Game termurah di genre " << sp->genre << endl;
            cout << "Judul      : " << temp->infoChild->info.judul << endl;
            cout << "Studio     : " << temp->infoChild->info.studio << endl;
            cout << "Tahun Rilis: " << temp->infoChild->info.tahun << endl;
            cout << "Deskripsi  : " << temp->infoChild->info.description << endl;
            cout << "Rating     : " << temp->infoChild->info.rating << endl;
            cout << "Harga      : " << temp->infoChild->info.harga << endl << endl;
        }
    }
}

void printGenreMax(listParent P, string genre) {
    adrParent sp = searchGenre(P, genre);
    if (sp == NULL) {
        cout << "Genre tidak ditemukan!" << endl;
    } else {
        if (sp->firstChild == NULL) {
            cout << "List genre kosong!" << endl;
        } else {
            adrChild temp = sp->firstChild;
            adrChild helper = sp->firstChild->nextChild;
            while (helper != NULL) {
                if (helper->infoChild->info.harga > temp->infoChild->info.harga) {
                    temp = helper;
                }
                helper = helper->nextChild;
            }
            cout << "Game termahal di genre " << sp->genre << endl;
            cout << "Judul      : " << temp->infoChild->info.judul << endl;
            cout << "Studio     : " << temp->infoChild->info.studio << endl;
            cout << "Tahun Rilis: " << temp->infoChild->info.tahun << endl;
            cout << "Deskripsi  : " << temp->infoChild->info.description << endl;
            cout << "Rating     : " << temp->infoChild->info.rating << endl;
            cout << "Harga      : " << temp->infoChild->info.harga << endl << endl;
        }
    }
}

void addToCart(listCart &C, listGames G, string judulGame) {
    adrGames findItem = searchGameJudul(G, judulGame);

    if (findItem == NULL) {
        cout << "Game tidak ditemukan!" << endl;
    } else {
        adrGames cartItem = new elmGames;
        cartItem->info = findItem->info;
        cartItem->nextGame = NULL;
        cartItem->prevGame = NULL;
        if (cartItem == NULL) {
            cout << "Game tidak ditemukan!" << endl;
        } else {
            adrGames helper = C.firstCart;
            bool found = false;
            while (helper != NULL && found == false) {
                if (helper->info.judul == cartItem->info.judul) {
                    found = true;
                }
                helper = helper->nextGame;
            }

            if (found == false) {
                if (C.firstCart == NULL) {
                    C.firstCart = cartItem;
                    C.lastCart = cartItem;
                } else {
                    cartItem->nextGame = C.firstCart;
                    C.firstCart->prevGame = cartItem;
                    C.firstCart = cartItem;
                }
                cout << endl << "Game berhasil dimasukkan ke keranjang" << endl << endl;
            } else {
                cout << "Game sudah pernah dimasukkan!" << endl;
            }
        }
    }
}

void printCart(listCart C) {
    if (C.firstCart == NULL) {
        cout << "List game kosong!" << endl;
    } else {
        adrGames helper = C.firstCart;
        int i = 1;
        while (helper != NULL) {
            cout << "Data game ke-" << i << endl;
            cout << "Judul      : " << helper->info.judul << endl;
            cout << "Studio     : " << helper->info.studio << endl;
            cout << "Tahun      : " << helper->info.tahun << endl;
            cout << "Description: " << helper->info.description << endl;
            cout << "Rating     : " << helper->info.rating << "/5" << endl;
            cout << "Harga      : " << helper->info.harga << endl << endl;
            helper = helper->nextGame;
            i++;
        }
    }
}

int sumCart(listCart C) {
    int sum = 0;

    if (C.firstCart == NULL) {
        return -1;
    } else {
        adrGames helper = C.firstCart;
        while (helper != NULL) {
            sum += helper->info.harga;
            helper = helper->nextGame;
        }
        return sum;
    }
}

float meanGenre(listParent P, string genre) {
    adrParent findGenre = searchGenre(P, genre);
    float mean, sum, counter;

    counter = 0.0;
    sum = 0.0;
    if (findGenre == NULL) {
        cout << "Genre tidak ditemukan!" << endl;
    } else {
        adrChild helper = findGenre->firstChild;
        while (helper != NULL) {
            sum += helper->infoChild->info.harga;
            counter++;
            helper = helper->nextChild;
        }
        mean = sum/counter;
    }

    return mean;
}

void login(int userChoice, listParent &P, listGames &G, listCart &C) {

    cout << "Login sebagai?" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Customer" << endl;
    cout << "Pilih: "; cin >> userChoice;

    /**
        belum dikasi throw error (if choice is not 1 or 2)
    */
    switch(userChoice) {
    case 1:
        menuAdmin(userChoice, P, G, C);
        break;
    case 2:
        menuCustomer(userChoice, P, G, C);
        break;
    }
}

void menuChoices(int userChoice) {
    if (userChoice == 1) {
        cout << "====== MENU ADMIN ======" << endl;
        cout << "1. Tambah beberapa genre baru" << endl;
        cout << "2. Tambah game baru" << endl;
        cout << "3. Tambah game ke genre" << endl;
        cout << "4. Hapus genre tertentu" << endl;
        cout << "5. Hapus game tertentu" << endl;
        cout << "6. Tampilkan daftar genre" << endl;
        cout << "7. Tampilkan daftar game" << endl;
        cout << "8. Tampilkan jumlah game tiap genre" << endl;
        cout << "99. Kembali ke menu login" << endl;
        cout << "0. Exit" << endl;
    } else if (userChoice == 2) {
        cout << "====== MENU CUSTOMER ======" << endl;
        cout << "1. Tampilkan semua game dengan genre tertentu" << endl;
        cout << "2. Tampilkan detail game berdasarkan judul" << endl;
        cout << "3. Cari game termahal/termurah di genre" << endl;
        cout << "4. Masukkan game ke keranjang" << endl;
        cout << "5. Lihat keranjang" << endl;
        cout << "6. Menghitung harga keranjang" << endl;
        cout << "7. Cari rata-rata harga suatu genre" << endl;
        cout << "99. Kembali ke menu login" << endl;
        cout << "0. Exit" << endl;
    }
}

void menuAdmin(int user, listParent &P, listGames &G, listCart &C) {
    system("cls");

    menuChoices(user);
    int choice;
    //case 1 variables
    string genre;
    int n;
    //case 2 variables
    dataGame gameData;
    char yono = 'N';
    //case 3 variables
    string tobeGenre;
    string tobeJudul;
    //case 4 variables
    string tobeDelGenre;
    adrParent storeP;
    //case 5 variables
    string tobeDelGame;
    adrGames storeG;
    //enter to finish
    char enter;
    cout << "Pilih menu: "; cin >> choice;
    while (choice != 0) {
        switch (choice) {
        case 1:
            system("cls");
            cout << "Mau menambah berapa genre: "; cin >> n;
            for (int i = 1; i <= n; i++) {
                cout << "Genre ke-" << i << ": "; cin >> genre;
                addParentFirst(P, genre);
            }
            cout << endl << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 2:
            while (yono != 'Y') {
                system("cls");
                cout << "Masukkan data game baru:" << endl;
                cout << "Judul game : "; getline(cin >> std::ws, gameData.judul);
                cout << "Studio     : "; getline(cin >> std::ws, gameData.studio);
                cout << "Tahun rilis: "; cin >> gameData.tahun;
                cout << "Description: "; getline(cin >> std::ws, gameData.description);
                cout << "Rating     : "; cin >> gameData.rating;
                cout << "Harga      : "; cin >> gameData.harga;
                system("cls");
                cout << "Judul game : " << gameData.judul << endl;
                cout << "Studio     : " << gameData.studio << endl;
                cout << "Tahun rilis: " << gameData.tahun << endl;
                cout << "Description: " << gameData.description << endl;
                cout << "Rating     : " << gameData.rating << endl;
                cout << "Harga      : " << gameData.harga << endl;
                cout << endl << "Data sudah benar? (Y/N)"; cin >> yono;
            }

            if (yono == 'Y') {
                addGameLast(P, G, gameData);
                yono = 'N';
            }

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 3:
            system("cls");
            cout << "Judul Game: "; getline(cin >> std::ws, tobeJudul);
            cout << "Tambahkan " << tobeJudul << " ke genre: "; cin >> tobeGenre;
            addChildToParent(P, G, tobeGenre, tobeJudul);
            cout << endl << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 4:
            system("cls");
            cout << "Genre yang ingin dihapus: "; getline(cin >> std::ws, tobeDelGenre);
            deleteGenre(P, tobeDelGenre, storeP);
            cout << endl << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 5:
            system("cls");
            cout << "Judul game yang ingin dihapus: "; getline(cin >> std::ws, tobeDelGame);
            deleteGame(P, G, tobeDelGame, storeG);
            cout << endl << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 6:
            system("cls");
            printParent(P);
            cout << endl << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 7:
            system("cls");
            printListGame(G);
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 8:
            system("cls");
            printParentChild(P);
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 99:
            system("cls");
            login(user, P, G, C);
            break;
        }
    }
    if (choice == 0) {
        system("cls");
        cout << "Selesai!" << endl;
    }
}

void menuCustomer(int user, listParent &P, listGames &G, listCart &C) {
    system("cls");

    menuChoices(user);
    int choice;
    //case 1 variables
    string genreGame;
    //case 2 variables
    string findGame;
    //case 4 variables
    adrParent genreXtremeP;
    string genreXtreme;
    //case 5 variables
    string gameToCart;
    char genreHL = 'X';
    //case 7 variables
    string avgG;
    cout << "Pilih menu: "; cin >> choice;
    while (choice != 0) {
        switch (choice) {
        case 1: //Tampilkan semua game dengan genre tertentu
            system("cls");
            cout << "Masukkan genre yang ingin dilihat: "; cin >> genreGame;
            printGenreDetail(P, genreGame);
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 2: //Tampilkan detail game berdasarkan judul
            system("cls");
            cout << "Masukkan game yang ingin dicari: "; getline(cin >> std::ws, findGame);
            printSpcGameDetail(P, G, findGame);
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 3: //Cari game termahal/termurah di genre
            system("cls");
            cout << "Pilih genre: "; cin >> genreXtreme;
            genreXtremeP = searchGenre(P, genreXtreme);
            if (genreXtremeP == NULL) {
                cout << "Genre tidak ditemukan!!!" << endl;
            } else {
                cout << "Tampilkan harga tertinggi/terendah? (H/L) "; cin >> genreHL;
                if (genreHL == 'H') {
                    printGenreMax(P, genreXtreme);
                    genreHL = 'X';
                } else if (genreHL == 'L') {
                    printGenreMin(P, genreXtreme);
                    genreHL = 'X';
                } else {
                    cout << "Input Salah!" << endl;
                }
            }
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 4: //Masukkan game ke keranjang
            system("cls");
            cout << "Masukkan game yang ingin ditambah ke keranjang: "; getline(cin >> std::ws, gameToCart);
            addToCart(C, G, gameToCart);
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 5: //Lihat keranjang
            system("cls");
            printCart(C);
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 6: //Menghitung harga keranjang
            system("cls");
            cout << "Jumlah harga keranjang: " << sumCart(C) << endl;
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 7: //Menghitung rata-rata harga genre
            system("cls");
            cout << "Cari rata-rata genre: "; cin >> avgG;
            cout << "Rata-rata harga dari genre " << avgG << " adalah " << meanGenre(P, avgG) << endl;
            cout << "Selesai! Tekan enter untuk kembali ke menu utama" << endl;
            getch();

            system("cls");
            menuChoices(user);
            cout << "Pilih menu: "; cin >> choice;
            break;
        case 99:
            system("cls");
            login(user, P, G, C);
            break;
        }
    }
    if (choice == 0) {
        system("cls");
        cout << "Selesai!" << endl;
    }
}
