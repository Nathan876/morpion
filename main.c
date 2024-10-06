#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

char affichage(char plateau[9]);
char checkVictory(char plateau[9], char signe);
char computerPart(char plateau[9]);
char userPart(char plateau[9]);

int main(int argc, const char * argv[]) {
    bool isPlaying = true;
    int nbCoups = 0; // compte le nombre de coups
    char plateau[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    while (isPlaying && nbCoups < 9) {
        nbCoups++; // ajoute un coup
        affichage(plateau);
        userPart(plateau); // appelle la fonction userPart qui lui permet d'ajouter un pion au plateau
        if (checkVictory(plateau, 'x') == true) { // vérifié si l'utilisateur a gagné
            isPlaying = false;
            affichage(plateau);
            printf("C'est gagné !\n");
            break;
        }
       
        if (nbCoups == 9){ // si personne n'a gagné en 9 coups alors il y a match nul
            printf("Match nul !\n");
            return 0;
        }
        
        nbCoups++; // ajout d'un coup
        computerPart(plateau); // la fonction computerPart permet à l'ordinateur de jouer
        if (checkVictory(plateau, 'O') == true) {
            isPlaying = false;
            affichage(plateau);
            printf("C'est perdu !");
            break;
        }
        if (nbCoups == 9) { // si le nombre de coup et égal a 9 alors il y a match nul
            printf("Match nul !\n");
            break;
        }
    }
    return 0;
}

char affichage(char plateau[9]){ // la fonction affichage permet d'afficher les éléments du plateau
    for (int i = 0; i < 3; i++) { // initialisation d'une boucle qui sépare le plateau en trois lignes
        printf("%c | %c | %c\n", plateau[3*i], plateau[3*i+1], plateau[3*i+2]); // affichage d'une ligne
        if (i < 2){
            printf("--+---+--\n"); // séparation des lignes du plateau
        }
    }
    return 0;
}

char checkVictory(char plateau[9], char signe){
    // le tableau de tableau trueConditions contient les combinaisons gagnantes possible
    char trueConditions[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (int i = 0; i < 8; i++) { // Création d'une boucle qui va vérifier si une combinaison est gagnante en vérifiant le signe saisi
        if (plateau[trueConditions[i][0]] == signe && plateau[trueConditions[i][1]] == signe && plateau[trueConditions[i][2]] == signe) {
            return true;
        }
    }
    return false;
}

char userPart(char plateau[9]){
    bool isFinishUserPart = false;
    int position;
    while (isFinishUserPart == false) { // tant que c'est au tour de l'utilisateur, la condition est vraie
        printf("Choisissez où jouer:\n");
        scanf(" %d", &position);
        if (position < 0 || position > 8) { // si le joueur entre une position inférieur a 0 ou supérieur à 8 ce n'est pas possible
            printf("Entrez une position comprise entre 0 et 8\n");
        } else if (plateau[position] != ' '){ // si le joueur entre une case déjà prise ce n'est pas possible
            printf("Impossible de jouer cette case elle est déjà prise\n");
        } else {
            plateau[position] = 'x'; // si toutes les conditions précédentes ne sont pas remplies alors l'utilisateur peut jouer sa case
            isFinishUserPart = true; // fin du tour de l'utilisateur
        }
    }
    return plateau[9];
}

char computerPart(char plateau[9]) { // la fonction permet à l'ordinateur de jouer
    printf("Tour de l'ordinateur\n");
    sleep(2);
    for (int i = 0; i < 9; i++) { // l'ordinateur parcours chaque case dans l'ordre et joue dès qu'une case est libre
        if (plateau[i] == ' '){
            plateau[i] = 'O';
            return plateau[9];
        }
    }
    return plateau[9];
}

