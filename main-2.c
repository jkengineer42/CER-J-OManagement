#include "file.h"
#include "function.h"

int main() {
    Athlete athletes[MAX_PERFORMANCES];
    int athlete_count = 0;
    int choice;
    char input[10];  // buffer pour retenir l’entrée de l’utilisateur
    load_all_athletes(athletes, &athlete_count);

    while (1) {
        for (int i = 0; i < 8; i++) {
            printf(BLUE "°" YELW "ₒ" BLACK "°" GREEN "ₒ" RED "°" RESET"  ");
        }
        printf("\n\n");
        printf("                 " BLUE "C" YELW "E" BLACK "R-" GREEN "J-" RED "O" CYAN " MANAGEMENT \n\n"RESET);
        for (int i = 0; i < 8; i++) {
            printf(BLUE "°" YELW "ₒ" BLACK "°" GREEN "ₒ" RED "°" RESET"  ");
        }
        printf("\n\n");
        printf("1. Ajouter un nouvel athlète\n");
        printf("2. Ajouter une performance pour un athlète\n");
        printf("3. Consulter l'historique des entraînements\n");
        printf("4. Consulter les statistiques sur les athlètes\n");
        printf("5. Quitter\n");
        printf(CYAN "=====================================\n" RESET);
        printf("Entrez votre choix: ");

        if (fgets(input, sizeof(input), stdin) != NULL) {
            char *endptr;
            errno = 0;  
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
                stat_menu(athletes, athlete_count);
                break;
            case 5:
                printf("Merci d'avoir utilisé CER-J-O Management. Au revoir !\n\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez réessayer.\n\n");
        }
    }
    return 0;
}