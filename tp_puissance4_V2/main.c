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

int checkPuissance4(int cptLig,int cptCol,int cptDdroite, int cptDgauche){
    int true = 1;
    int false = 0;
    if(cptLig >=3 || cptCol>=3 || cptDdroite>=3 || cptDgauche>=3)
        return true;
    else
        return false;
}

int checkWin(int N, int M, char plateau[N][M],char testedChar, int numeroLigne, int numeroCol){
    int res;
    int cptLigne = 0;
    int cptCol = 0;
    int cptDdroite = 0;
    int cptDgauche = 0;

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

int iaIntelligence(int N, int M, char plateau[N][M],char testedChar, int cPlateau){
    int res = -1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <M ; ++j) {
            if(plateau[i][j] == cPlateau){
                if(checkWin(N,M,plateau,testedChar,i,j) == 1){
                    return j;
                }
            }
        }
    }
    return res;
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
    char testedChar;
    int checkOrdiWin;
    int checkPlayerWin;
    // init plateau de jeu
    init_tab(N,M,plateau, cPlateau);

// début de la boucle de jeu
    do{
        // Choisi quel char on doit tester : Celui du joueur 1 ou de l'ordinateur
        testedChar = getCharToTest(whoPlay,cOrdi,cPlayer1);

        checkOrdiWin = iaIntelligence(N,M,plateau,cOrdi,cPlateau);
        checkPlayerWin = iaIntelligence(N,M,plateau,cPlayer1,cPlateau);

        if(whoPlay == 0){
            if(checkOrdiWin >=0){
                positionColonne = checkOrdiWin;
                printf("\n LORDI PEUX GAGNER avec la position de la col : %d \n", checkOrdiWin);
            }
            else if (checkPlayerWin >=0){
                positionColonne = checkPlayerWin;
                printf("\n LORDI PEUX BLOQUER avec la position de la col : %d \n", checkPlayerWin);
            }
            else
            positionColonne = getRandomInt(M);
        }
        else
            positionColonne = askPosCol(M);
        // check si on peux remplir le plateau ou pas et si oui le remplir et retourner le numéro de la ligne de la dernière pièce posé
        getLineNumber = lineNumber(positionColonne, N, M,plateau,cPlateau);

        // check si le tour à bien pu être fait : Si oui on change de player et affiche le plateau sinon on prompt un message et on recommence
        if(getLineNumber < 0)
            printf("\n Impossible dans cette colonne \n");
        else{

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
                whoPlay = changePlayer(whoPlay);
            }
        }
    }while(plateauFull(N,M,plateau,cOrdi,cPlayer1) == 0  && winner !=1 );
    // fin de la boucle de jeu
    return 0;
}