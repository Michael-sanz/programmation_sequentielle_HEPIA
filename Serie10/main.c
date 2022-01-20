#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void CreerTab(){}

void AfficherTab(){}

void TrierTab(){}

void DetruireTab(){}



int main() {
    const int TAILLE_FICH = 300;
    const int MAX_CHAR = 80;
    const char NOMFICHIER[] = "etudiants2.txt";
    FILE *fid;
    char unStr[MAX_CHAR];

    int i;

    fid = fopen(NOMFICHIER, "r"); // ouverture du fichier
    for (i=0; i<TAILLE_FICH; i++)
    {
        fscanf(fid, "%s", unStr); // lit une chaîne de caract.
        char *p = malloc( sizeof(char) * (300 * stricmp(&unStr[i])) );
        printf("%llu\n",strlen(&unStr[0]));
    }



    fclose(fid); // fermeture du fichier
    return 0;
}
