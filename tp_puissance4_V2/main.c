// TP le jeu du puissance 4
// Sanz Michael
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int getRandomInt(int M) {
    int randomNumber;
    srand(time(0));  // initialisation du générateur aléatoire
    randomNumber = rand() % (M + 1); // random number entre 0 et N-1 (donc 6)
    return randomNumber;
}

int askPosCol(int M) {
    int numCol;
    printf("Veuillez entrez un num de colonne <= a %d (pouvant etre 0)\n", M - 1);
    scanf("%d", &numCol);
    return numCol; // retourne le numéro entrer par le joueur
}

// Parcour du plateau et affichage de ces caractère à chaque position
void afficherPlateau(int N, int M, char plateau[N][M]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%4c", plateau[i][j]);
        }
        putchar('\n');
    }
    printf("\n");
}

// init du plateau de jeu avec le caractère "cPlateau" ('-')
void init_tab(int N, int M, char plateau[N][M], char cPlateau) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            plateau[i][j] = cPlateau;
        }
    }
}

// Parcour la dernière ligne partant du bas pour savoir si la colonne est déjà remplie ( si oui : on renvoie -1 , si non : en revoie le numéro de la ligne)
int lineNumber(int posCol, int N, int M, char plateau[N][M], char CPlateau) {
    int valeurNegative = -1;
    for (int i = N; i >= 0; --i) {
        if (plateau[i][posCol] == CPlateau) {
            return i;
        }
    }
    return valeurNegative;
}

// remplissage du plateau avec le numéro de la ligne et de la colonne correspondante
void remplirPlateau(int posCol, int posLigne, int N, int M, char plateau[N][M], char testedChar) {
    plateau[posLigne][posCol] = testedChar;
}

// Compteur de caractère avec des incréments passés en paramètres
int countSameChar(int N, int M, char plateau[N][M], char testedChar, int numeroLigne, int numeroCol, int incrLigne,
                  int incrCol) {
    int count = 0;
    for (int li = numeroLigne + incrLigne, col = numeroCol + incrCol; ((li >= 0) && (li < N) && (col >= 0) &&
                                                                       (col < M)); li += incrLigne, col += incrCol) {
        if (plateau[li][col] == testedChar)
            count++;
        else
            return count;
    }
    return count;
}

// check si les compteurs sont de valeur 3 ou supérieur
int checkPuissance4(int cptLig, int cptCol, int cptDdroite, int cptDgauche) {
    int true = 1;
    int false = 0;
    int conditionVictoire = 3;
    if (cptLig >= conditionVictoire || cptCol >= conditionVictoire || cptDdroite >= conditionVictoire ||
        cptDgauche >= conditionVictoire)
        return true;
    else
        return false;
}

// Incrémentation des compteur avec check grâce à la fonction "checkPuissance4"
int checkWin(int N, int M, char plateau[N][M], char testedChar, int numeroLigne, int numeroCol) {
    int res;
    int cptLigne = 0;
    int cptCol = 0;
    int cptDdroite = 0;
    int cptDgauche = 0;

    cptLigne += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, 0, 1);
    cptLigne += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, 0, -1);

    cptCol += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, 1, 0);

    cptDgauche += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, -1, -1);
    cptDgauche += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, +1, +1);

    cptDdroite += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, -1, +1);
    cptDdroite += countSameChar(N, M, plateau, testedChar, numeroLigne, numeroCol, +1, -1);

    res = checkPuissance4(cptLigne, cptCol, cptDdroite, cptDgauche);
    return res;
}

// Parcours de l'ensemble du plateau pour trouvé une position suceptible de faire gagner un des joueur
int iaIntelligence(int N, int M, char plateau[N][M], char testedChar, char cPlateau) {
    int res = -1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            // on rentre dans la boucle seulement si la case est encore vide
            if (plateau[i][j] == cPlateau) {
                // appelle de la fonction check win à la position i et j
                if (checkWin(N, M, plateau, testedChar, i, j) == 1) {
                    if(i == N-1)
                        return j;
                    if(plateau[i+1][j] != cPlateau)
                        return j;
                }
            }
        }
    }
    return res;
}

// récompense du joueur (passé en paramètre)
void reward(int whoPlay) {
    if (whoPlay == 1)
        printf("LE JOUEUR 1 A GAGNE !!!");
    else
        printf("L ORDINATEUR A GAGNE !!!");
}

// Check si il y a une égalité
int plateauFull(int N, int M, char plateau[N][M], char cOrdi, char cPlayer1) {
    int res = 0;
    for (int i = 0; i <= M;) {
        if (plateau[0][i] == cOrdi || plateau[0][i] == cPlayer1) {
            res = 1;
            ++i;
        }
            // quand la dernière ligne partant du bas est toute remplie cela signifie que la plateau est full
        else {
            res = 0;
            return res;
        }
    }
    return res;
}

// change le tour du joueur
int changePlayer(int whoPlay) {
    if (whoPlay == 1) {
        whoPlay = 0;
    } else
        whoPlay = 1;
    return whoPlay;
}

// retourne le caractère à tester pendant le tour de jeu
char getCharToTest(int whoPlay, char cOrdi, char cPlayer) {
    if (whoPlay == 0)
        return cOrdi;
    else
        return cPlayer;
}

// début du programme
int main() {
    // CONSTANTES
    const int N = 6; // nombre de lignes du plateau de jeu
    const int M = 7; // nombre de colonnes du plateau de jeu
    const char cOrdi = 'O'; // Caractère utilisé par l'ordinateur
    const char cPlayer1 = 'P'; // Caractère utilisé par le joueur
    const char cPlateau = '-'; // Caractère par défaut du plateau
    // VARIABLES
    char plateau[N][M];
    int positionColonne;
    int whoPlay; // Qui joue si la valeur est 1 = c'est le joueur 1 qui joue , si la valeur est 0 c'est l'ordinateur qui joue
    int getLineNumber; // Booléan permettant de savoir si on peux remplir le plateau avec une colonne donnée (grâce à la fonction lineNumber) et si on peux nous renvoie la ligne de la nouvelle pièce posée
    int winner; // Booléan qui permet de définir si il y a un gagnant ou pas
    char testedChar; // Détermine le caractère à évaluer pendant le tour
    int checkOrdiWin; // Booléan qui définit si l'ordi peut gagner pendant le tour
    int checkPlayerWin; // Booléan qui définit si le player peux être bloqué pendant ce tour
    // INIT DU PLATEAU DE JEU
    init_tab(N, M, plateau, cPlateau);

// début de la boucle de jeu
    do {
        // Choisi quel char on doit tester : Celui du joueur 1 ou de l'ordinateur
        testedChar = getCharToTest(whoPlay, cOrdi, cPlayer1);
        // Check si il est possible que l'ordi gagne pendant ce tour ( oui : renvoie la colonne au il peux gagner, Non : renvoie -1)
        checkOrdiWin = iaIntelligence(N, M, plateau, cOrdi, cPlateau);
        // Check si il est possible que le player 1 gagne pendant ce coup ( oui : revoie la colonne au il peux bloquer , Non renvoie -1)
        checkPlayerWin = iaIntelligence(N, M, plateau, cPlayer1, cPlateau);

        if (whoPlay == 0) {
            if (checkOrdiWin >= 0) {
                // attribution de la colonne ou l'ordi peux gagner
                positionColonne = checkOrdiWin;
            } else if (checkPlayerWin >= 0) {
                // attribution de la colonne ou l'ordi peux bloquer
                positionColonne = checkPlayerWin;
            } else
                // tire un nombre aléatoire en 0 et N-1 -> (donc 6)
                positionColonne = getRandomInt(M);
        } else
            // Demande au joueur une colonne dans laquelle un jeton va être placé
            positionColonne = askPosCol(M);

        // check si on peux remplir le plateau ou pas et si oui le remplir et retourner le numéro de la ligne de la dernière pièce à posé sinon retourne 0 et on recommence
        getLineNumber = lineNumber(positionColonne, N, M, plateau, cPlateau);

        // check si le tour à bien pu être fait : Si oui on change de player et affiche le plateau sinon on prompt un message et on recommence
        if (getLineNumber < 0)
            // si on peut pas jouer dans cette colonne car la ligne est rempli on recommence le tour de boucle
            printf("\n Impossible dans cette colonne \n");
        else {

            // remplie le tableau à la ligne et la colonne définie avec le bon caractère
            remplirPlateau(positionColonne, getLineNumber, N, M, plateau, testedChar);

            // affiche le plateau
            afficherPlateau(N, M, plateau);

            // check si un joueur à WIN
            winner = checkWin(N, M, plateau, testedChar, getLineNumber, positionColonne);

            // si un joueur à gagné on le récompense
            if (winner > 0) {
                reward(whoPlay);
            } else {
                // change le joueur
                whoPlay = changePlayer(whoPlay);
            }
        }
        // on boucle tant que le plateau n'est pas remplie totalement (égalité) ET qu'il n'y a pas de gagnant
    } while (plateauFull(N, M, plateau, cOrdi, cPlayer1) == 0 && winner != 1);
    // fin de la boucle de jeu
    return 0;
    // fin du programme
}