// TP le jeu du puissance 4
// Sanz Michael
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int getRandomInt(int M){
    int randomNumber;
    srand(time(0));  // initialisation du générateur aléatoire
    randomNumber = rand() % (M+1);
    return randomNumber;
}

int askPosCol(int M){
    int numCol;
    printf("Veuillez entrez un num de colonne <= a %d (pouvant etre 0)\n",M-1);
    scanf("%d",&numCol);
    return numCol;
}

void afficherPlateau(int N,int M, char plateau[N][M]){
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%c",plateau[i][j]);
        }
        putchar('\n');
    }
    printf("\n");
}

void init_tab(int N, int M, char plateau[N][M], char cPlateau){
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            plateau[i][j] = cPlateau;
        }
    }
}

int lineNumber(int posCol, int N, int M, char plateau[N][M], char CPlateau){
    int valeurNegative = -1;
    for (int i = N; i >= 0; --i){
        if(plateau[i][posCol] == CPlateau){
            return i;
        }
    }
    return valeurNegative;
}

void remplirPlateau(int posCol , int posLigne , int N, int M , char plateau[N][M], char testedChar){
        plateau[posLigne][posCol] = testedChar;
}

int countSameChar(int N, int M, char plateau[N][M], char testedChar, int numeroLigne, int numeroCol, int incrLigne, int incrCol){
    int count = 0;
    for (int li = numeroLigne + incrLigne, col = numeroCol + incrCol; ((li >= 0) && (li < N) && (col >= 0) && (col < M)); li += incrLigne, col += incrCol){
        if(plateau[li][col] == testedChar)
            count++;
        else
            return count;
    }return count;
}

void iaBuissinessLogic(int N, int M, char plateau[N][M], char testedChar, int numeroLigne, int numeroCol,int tab[4]){
    int cptLigne = 1;
    int cptCol = 1;
    int cptDdroite = 1;
    int cptDgauche = 1;

    cptLigne+= countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, 0, 1);
    cptLigne+= countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, 0, -1);

    cptCol+= countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, 1, 0);

    cptDgauche += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, -1, -1);
    cptDgauche += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, +1, +1);

    cptDdroite += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, -1, +1);
    cptDdroite += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, +1, -1);

    if(cptLigne>=3)
        tab[0] = cptLigne;
    if(cptCol>=3)
        tab[1] = cptCol;
    if(cptDdroite>=3)
        tab[2] = cptDdroite;
    if(cptDgauche>=3)
        tab[3] = cptDgauche;
}

int checkPuissance4(int cptLig,int cptCol,int cptDdroite, int cptDgauche){
    int true = 1;
    int false = 0;
    if(cptLig >=4 || cptCol>=4 || cptDdroite>=4 || cptDgauche>=4)
        return true;
    else
        return false;
}

int checkWin(int N, int M, char plateau[N][M],char testedChar, int numeroLigne, int numeroCol){
    int res;
    int cptLigne = 1;
    int cptCol = 1;
    int cptDdroite = 1;
    int cptDgauche = 1;

    cptLigne+= countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, 0, 1);
    cptLigne+= countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, 0, -1);

    cptCol+= countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, 1, 0);

    cptDgauche += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, -1, -1);
    cptDgauche += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, +1, +1);

    cptDdroite += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, -1, +1);
    cptDdroite += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, +1, -1);

    res = checkPuissance4(cptLigne,cptCol,cptDdroite,cptDgauche);
    return res;
}

int iaIntellegience(int numLigne, int numeroCol, int N, int M, char plateau[N][M], int tab[4], char testedChar,char cPlateau){
        for (int i = 0; i < 4; ++i) {
            if(tab[i] >= 3){
                for (int j = 1; j <3 ; ++j) {
                    switch(i){
                        // case ligne
                        case 0:
                            // check si il peux gagner en ligne (donc avec colonne -1 ou + 1)
                            if(checkWin(N,M,plateau,testedChar,numLigne,(numeroCol -j)) >= 4){
                                if(plateau[numLigne-1][numeroCol-j] == cPlateau)
                                    return numeroCol -j;
                            }
                            else if(checkWin(N,M,plateau,testedChar,numLigne,(numeroCol+j)) > 0){
                                if(plateau[numLigne-1][numeroCol+j] == cPlateau)
                                    return numeroCol +j;
                                else
                                    break;
                            }
                            // case Col
                        case 1:
                            if(numLigne <= 6){
                                return numeroCol;
                            }
                            // case diagonal droite
                        case 2:
                            if((checkWin(N,M,plateau,testedChar,numLigne+j,numeroCol-j) > 0)){
                                if(plateau[(numLigne+j)-1][numeroCol+j] == cPlateau)
                                    return numeroCol+j;
                            }
                            else if((checkWin(N,M,plateau,testedChar,numLigne-j,numeroCol+j) > 0)){
                                if(plateau[(numLigne-j)-1][numeroCol-j] == cPlateau)
                                    return numeroCol-j;
                            }
                            // case diagonal gauche
                        case 3:
                            if((checkWin(N,M,plateau,testedChar,numLigne+j,numeroCol+j) > 0)){
                                if(plateau[(numLigne+j)-1][numeroCol+j] == cPlateau)
                                    return numeroCol+j;
                            }
                            else if((checkWin(N,M,plateau,testedChar,numLigne-j,numeroCol-j) > 0)){
                                if(plateau[(numLigne-j)-1][numeroCol-j] == cPlateau)
                                    return numeroCol-j;
                            }
                    }
                }
            }
        } return getRandomInt(M);
}


void reward(int whoPlay)
    {
//        printf("\n VARIABLE WHO PLAY AU MOMENT DU CHECK %d", whoPlay);
        if(whoPlay == 1)
            printf("LE JOUEUR 1 A GAGNE !!!");
        else
            printf("L ORDINATEUR A GAGNE !!!");
    }

int plateauFull(int N,int M,char plateau[N][M], char cOrdi, char cPlayer1){
    int res = 0;
    for (int i = 0; i <= M;) {
        if (plateau[0][i] == cOrdi || plateau[0][i] == cPlayer1){
            res = 1;
            ++i;
        }
        else{
            res = 0;
            return res;
        }
    }
    return res;
}

int changePlayer(int whoPlay){
    if(whoPlay == 1){
        whoPlay = 0;
    }
    else
        whoPlay = 1;
    return whoPlay;
}

void initCountTab(int tab[4]){
    for (int i = 0; i <= 4; ++i) tab[i] = 1;
}

char getCharToTest(int whoPlay,char cOrdi, char cPlayer){
    if(whoPlay == 0)
        return cOrdi;
    else
        return cPlayer;
}

//int getColumNumber(int whoPlay, int M){
//    int posCol;
//    if(whoPlay == 0){
//        posCol = getRandomInt(M);
//    }
//    else
//        posCol = askPosCol(M);
//    return posCol;
//}

int main() {
    // CONSTANTES
    const int N = 6; // nombre de lignes du plateau de jeu
    const int M = 7; // nombre de colonnes du plateau de jeu
    const char cOrdi = 'O';
    const char cPlayer1 = 'P';
    const char cPlateau = '-';
    // VARIABLES
    char plateau[N][M];
    int positionColonne;
    int whoPlay; // Qui joue si la valeur est 1 = c'est le joueur 1 qui joue , si la valeur est 0 c'est l'ordinateur qui joue
    int getLineNumber; // Booléan permettant de savoir si on peux remplir le plateau à cette colonne la (grâce à la fonction lineNumber) et si on peux nous renvoie la ligne de la nouvelle pièce posée
    int winner;
    int tabPlayer[4];
    int tabOrdi[4];
    char testedChar;
    int nvxNombreColWin = -1;
    int nvxNombreColBlock = -1;

    // init plateau de jeu
    init_tab(N,M,plateau, cPlateau);
    // Init des tabs de count
    initCountTab(tabPlayer);
    initCountTab(tabOrdi);
// début de la boucle de jeu
    do{


//        nvxNombreColWin = iaIntellegience(getLineNumber,positionColonne,N,M,plateau,tabOrdi,cOrdi,cPlateau);
        nvxNombreColBlock = iaIntellegience(getLineNumber,positionColonne,N,M,plateau,tabPlayer,cPlayer1,cPlateau);

        if(whoPlay == 0){
            if(nvxNombreColWin >=0)
            {
                positionColonne = nvxNombreColWin;
                nvxNombreColWin = -1;
            }
            else if(nvxNombreColBlock >=0){
                positionColonne = nvxNombreColBlock;
                nvxNombreColBlock = -1;
            }
            else
                // tire une position de colonne aléatoire
                positionColonne = getRandomInt(M);
        }
        else
            positionColonne = askPosCol(M);

        initCountTab(tabPlayer);
        initCountTab(tabOrdi);


        // check si on peux remplir le plateau ou pas et si oui le remplir et retourner le numéro de la ligne de la dernière pièce posé
        getLineNumber = lineNumber(positionColonne, N, M,plateau,cPlateau);

        // check si le tour à bien pu être fait : Si oui on change de player et affiche le plateau sinon on prompt un message et on recommence
        if(getLineNumber < 0)
            printf("\n Impossible dans cette colonne \n");
        else{
            // Choisi quel char on doit tester : Celui du joueur 1 ou de l'ordinateur
            testedChar = getCharToTest(whoPlay,cOrdi,cPlayer1);

            // remplie le tableau à la ligne et la colonne définie avec le bon caractère
            remplirPlateau(positionColonne, getLineNumber, N, M, plateau,testedChar);
            // affiche le plateau

            afficherPlateau(N,M,plateau);
            // check si un joueur à WIN
            winner = checkWin(N,M,plateau,testedChar,getLineNumber,positionColonne);
            if(winner > 0)
            {
                reward(whoPlay);
            }
            else
                // change le joueur
                {
                    iaBuissinessLogic(N, M, plateau, cPlayer1, getLineNumber, positionColonne, tabPlayer);
                    iaBuissinessLogic(N, M, plateau, cOrdi, getLineNumber, positionColonne, tabOrdi);
                    whoPlay = changePlayer(whoPlay);
                }
        }
    }while(plateauFull(N,M,plateau,cOrdi,cPlayer1) == 0  && winner !=1 );
    // fin de la boucle de jeu
    return 0;
}
