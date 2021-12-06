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
    printf("\n");
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

int remplirPlateau(int posCol,int N,int M,char plateau[N][M], char cOrdi, char cPlayer1,char CPlateau, int whoPlay){
    int valeurNegative = -1;
    for (int i = N; i >= 0; --i){
        if(plateau[i][posCol] == CPlateau){
            if(whoPlay == 1){
                plateau[i][posCol] = cPlayer1;
                return i;
            }
            else{
                plateau[i][posCol] = cOrdi;
                return i;
            }
        }
    }
    return valeurNegative;
}

int checkwin(int N, int M, char plateau[N][M], int whoPlay, char cOrdi, char cPlayer, int numeroLigne, int numeroCol){
    int res = -1;
    int cptLigne = 1, cptCol = 1 , cptDdroite = 1, cptDgauche =1, i, j;
    char testedChar;
//    printf("\n NUM LIGNE : %d , NUM COL : %d \n", numeroLigne, numeroCol);
    if(whoPlay==1)
        testedChar = cPlayer;
    else
        testedChar = cOrdi;
//    printf("\n%c\n", testedChar);

    for (i = 1, j =1;  ( (i>=0) && (i< N) && (j>=0) && (j<M)) ; i++, j++) {
        if(plateau[numeroLigne+i][numeroCol+j] == testedChar){
            cptDgauche++;
            printf("\n CPT D GAUCHE = %d",cptDgauche);
        }
        if(plateau[numeroLigne-i][numeroCol-j] == testedChar)
            {
                cptDgauche++;
                printf("\n CPT D GAUCHE = %d",cptDgauche);
            }
        if(plateau[numeroLigne-i][numeroCol+j] == testedChar)
            {
                cptDdroite++;
                printf("\n CPT D DROITE = %d",cptDdroite);
            }
        if(plateau[numeroLigne+i][numeroCol-j] == testedChar)
            {
                cptDdroite++;
                printf("\n CPT D DROITE = %d",cptDdroite);
            }
        if(plateau[numeroLigne][numeroCol+j] == testedChar)
        {
            cptCol++;
            printf("\n CPT COL = %d",cptCol);
        }
        if(plateau[numeroLigne][numeroCol-j] == testedChar)
        {
            cptCol++;
            printf("\n CPT COL = %d",cptCol);
        }
        else
            break;
    }
    for (int k = 1; k < N ; ++k) {
        if(plateau[numeroLigne+k][numeroCol] == testedChar){
            cptLigne++;
        }
        else
            break;
    }
    if(cptCol >=4 || cptDdroite>=4 || cptDgauche>=4 || cptLigne>=4)
        return whoPlay;
    else
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
    int checkColOrGetLineNumber; // Booléan permettant de savoir si on peux remplir le plateau à cette colonne la (grâce à la fonction remplirPlateau) et si on peux nous renvoie la ligne de la nouvelle pièce posée
    int winner;

    // init plateau de jeu
    init_tab(N,M,plateau, cPlateau);
// début de la boucle de jeu
    do{
        if(whoPlay == 0)
            // si c'est le joueur qui joue on tire un nb random
            positionColonne = getRandomInt(M);
        else
            // si c'est le joueur qui joue on lui demande un nombre
            positionColonne = askPosCol(M);

        // check si on peux remplir le plateau ou pas et si oui le remplir et retourner le numéro de la ligne de la dernière pièce posé
        checkColOrGetLineNumber = remplirPlateau(positionColonne, N, M, plateau, cOrdi, cPlayer1, cPlateau, whoPlay);

        // check si le tour à bien pu être fait : Si oui on change de player et affiche le plateau sinon on prompt un message et on recommence
        if(checkColOrGetLineNumber < 0)
            printf("\n Impossible dans cette colonne \n");
        else{
            // affiche le plateau
            afficherPlateau(N,M,plateau);

            // check si un joueur à WIN
            winner = checkwin(N,M,plateau,whoPlay,cOrdi,cPlayer1,checkColOrGetLineNumber, positionColonne);
            printf("\n winner %d\n",winner);
            if(winner >= 0)
            {

                reward(winner);
            }
            else
                // change le joueur
                whoPlay = changePlayer(whoPlay);
        }
    }while(plateauFull(N,M,plateau,cOrdi,cPlayer1) == 0  && winner < 0);
    // fin de la boucle de jeu
    return 0;
}
