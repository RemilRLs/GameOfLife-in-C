#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

// Nos constantes.

#define WIDTH 32
#define HEIGHT 32

char grid[HEIGHT][WIDTH]; // Ligne - Colonne (case).
char gridTmp[HEIGHT][WIDTH]; // Tableau temporaire afin de stocker temporairement l'état de nos cellules.

int initGame(void){ // Menu du jeu de la vie.

    int userInput;

    while(1){

        puts("-----------------------------------------------");
        puts("|                  |            |             |");
        puts("|                  |     # #    |    ###      |");
        puts("|        ###       |     # #    |      #      |");
        puts("|                  |     ###    |     #       |");
        puts("|                  |            |             |");
        puts("|        1         |     2      |        3    |");
        puts("-----------------------------------------------");

        printf("[*] - Extra mod :\n\n4 - Random Patern"); // On demande à l'utilisateur le motif qu'il souhaite.
        printf("\n\n[] - Please choose your pattern : ");
        scanf("%d", &userInput);

        if(userInput > 4 || userInput < 0){ // Sécurité si l'utilisateur donne un mauvais numéro.
            printf("You didn't choose a good number, please retry.");
            system("clear");
            continue;
        }
        else{ // Si c'est bon alors...
            return userInput;
        }

    }
}

int loadGame(int motif){

    // On initialise notre tableau avec des espaces.

    for(int i = 0 ; i < HEIGHT ; i++){
        for(int j = 0; j < WIDTH ; j++){
            grid[i][j] = ' ';
        }
    }
    int middleY = HEIGHT / 2; // On récupère le milieu de notre tableau afin de positionner au mieux nos cellules.
    int middleX = WIDTH / 2;
    int randomNumber;


    switch(motif){ // On initialise le motif choisi par l'utilisateur dans notre tableau.

        case 1: // Motif 1.

            grid[middleY][middleX] = '#';
            grid[middleY][middleX + 1] = '#';
            grid[middleY][middleX - 1] = '#';

            break;

        case 2: // Motif 2.

            grid[middleY + 2][middleX] = '#';
            grid[middleY][middleX + 1] = '#';
            grid[middleY][middleX - 1] = '#'; 
            grid[middleY + 1][middleX + 1] = '#';
            grid[middleY + 2][middleX + 1] = '#';
            grid[middleY + 2][middleX - 1] = '#';
            grid[middleY + 1][middleX - 1] = '#';

            break;

        case 3: // Motif 3.

            grid[middleY + 4][middleX] = '#';
            grid[middleY + 3][middleX + 1] = '#';
            grid[middleY + 2][middleX + 1] = '#';
            grid[middleY + 2][middleX] = '#';
            grid[middleY + 2][middleX - 1] = '#';

            break;

        case 4: // Motif 4. -> Aléatoire.

            for(int i = 0 ; i < HEIGHT ; i++){
                for(int j = 0 ; j < WIDTH ; j++){
                    randomNumber = generateRandomNumber();
                    if(randomNumber == 1){
                        grid[i][j] = '#';
                    }
                    else{
                        grid[i][j] = ' ';
                    }
                }
            }

            break;
    }
}

int generateRandomNumber(void){ // Fonction permettant de faire le motif n°4.

    int randomNumber;

    for(int i = 0 ; i < HEIGHT ; i++){
        for(int j = 0; j < WIDTH ; j++){
            randomNumber = rand() % 2; // On génère un nombre entre 0 et 1.

            return randomNumber;
        }
    }   
}

void drawGame(void){ // On dessine notre jeu de la vie.

    for(int i = 0 ; i < WIDTH ; i++){
        printf("-");
    }



    for(int i = 0 ; i < HEIGHT ; i++){
        printf("|");
        
        for(int j = 0 ; j < WIDTH ; j++){
            printf("%c", grid[i][j]);
        }

        printf("|\n"); // Tout à droite.
    }

    for(int i = 0 ; i < WIDTH ; i++){ // La fin.
        printf("-");
    }
}

int IsInRange (int ligne, int colonne){

    if(ligne > WIDTH || ligne < 0 && colonne > HEIGHT || colonne < 0){ // On est hors du plateau de jeu.

        return 0;
    }
    else{

        return 1;
    }
}

int NbCasesAdj(int ligne, int colonne) // On regarde si une cellule en question à des voisines ibijaus. Merci à Léo Masson de m'avoir aidé pour cette fonction.
{
	int nombreVoisins = 0;
    
    // On regarde les voisins environnent.
	for (int i = -1; i <= 1; ++i){
        for (int j = -1; j <= 1; ++j){
            if ((i != 0 || j != 0 && IsInRange(ligne + i, colonne + j))){

                nombreVoisins += grid[ligne + i][colonne + j] == '#'; // On renvoit 1 si c'est bien un # 

            }
        }
    }

	return nombreVoisins;
}

void UpdateGame (void){


    for(int i = 0 ; i < HEIGHT; i++){
        for(int j = 0 ; j < WIDTH ; j++){

            int nombreVoisins = NbCasesAdj(i, j);

            if(nombreVoisins == 3){ // Réincarnation.

                gridTmp[i][j] = '#';
            }
            else if(nombreVoisins == 2){ // Elle reste.

                gridTmp[i][j] = grid[i][j];
            }
            else{ // La cellule devient morte.

                gridTmp[i][j] = ' ';
            }
        }
    }

    for(int i = 0; i < HEIGHT; i++){ // On copie notre tableau temporaire dans le tableau principal.
        for(int j = 0; j < WIDTH ; j++){

            grid[i][j] = gridTmp[i][j];
        }
    }
}


void PlayGame(void){ // Fonction permettant le bon déroulement du jeu.
    system("clear");

    drawGame();
    UpdateGame();

    printf("\nDo you want to continue (Press any key) ? If you want to quiz press q.");
}

int main(){

    srand(time(NULL));
    loadGame(initGame()); // On récupère la valeur de retour afin d'exécuté notre fonction loadGame.
    
    while(getc(stdin) != 'q'){ // Tant que l'utilisateur ne souhaite pas quitter alors...

        PlayGame();
    }
    return 0;
}