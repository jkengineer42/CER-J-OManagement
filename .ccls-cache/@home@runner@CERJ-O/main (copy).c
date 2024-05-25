#include "file.h"
#include "function.h" 


int main() {
    Athlete athletes[MAX_PERFORMANCES];
    int athlete_count = 0;
    int choice;
    char input[10];  // buffer to hold user input

    while (1) {
        for (int i = 0; i < 8; i++) {
            printf(BLUE "°" YELW "ₒ" BLACK "°" GREEN "ₒ" RED "°" RESET"  ");
        }
        printf("\n\n");
        centerText("                 " BLUE "C" YELW "E" BLACK "R-" GREEN "J-" RED "O" " MANAGEMENT \n"RESET);
        for (int i = 0; i < 8; i++) {
            printf(BLUE "°" YELW "ₒ" BLACK "°" GREEN "ₒ" RED "°" RESET"  ");
        }
        printf("\n\n");
        printf("1. Ajouter un nouvel athlète\n");
        printf("2. Ajouter une performance pour un athlète\n");
        printf("3. Afficher les statistiques des athlètes\n");
        printf("4. Afficher les meilleurs performeurs\n");
        printf("5. Résumé des performances d'un athlète\n");
        printf("6. Quitter\n");
        printf(CYAN "=====================================\n" RESET);
        printf("Entrez votre choix: ");

        if (fgets(input, sizeof(input), stdin) != NULL) {
            char *endptr;
            errno = 0;  // to distinguish success/failure after call
            choice = strtol(input, &endptr, 10);

            if (errno != 0 || endptr == input || *endptr != '\n') {
                printf("Choix invalide. Veuillez entrer un nombre.\n\n");
                continue;
            }
        } else {
            printf("Erreur de lecture. Veuillez réessayer.\n\n");
            continue;
        }

        switch (choice) {
            case 1:
                add_new_athlete(athletes, &athlete_count);
                break;
            case 2:
                printf("Entrez le nom de l'athlète: ");
                char athleteName[MAX_NAME];
                get_user_input(NULL, athleteName, MAX_NAME);
                add_performance(athleteName, athletes, athlete_count);
                break;
            case 3:
                show_athlete_stats(athletes, athlete_count);
                break;
            case 4:
                display_best_performers(athletes, athlete_count);
                break;
            case 6:
                printf("Merci d'avoir utilisé CER-J-O Management. Au revoir !\n\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez réessayer.\n\n");
        }
    }
    return 0;
}
