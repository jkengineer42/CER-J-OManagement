#include "file.h"
#include "function.h"

void display_event_menu() {
    const char *event_types[] = {"100m", "400m", "5000m", "marathon", "relais 4 x 400 m"};
    size_t num_event_types = sizeof(event_types) / sizeof(event_types[0]);

    printf("Sélectionnez le type d'épreuve:\n");
    for (size_t i = 0; i < num_event_types; i++) {
        printf("%zu. %s\n", i + 1, event_types[i]);
    }
}

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
        printf("3. Consulter l'historique des entraînements\n");
        printf("4. Consulter les statistiques sur les athlètes\n");
        printf("5. Quitter\n");
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
            case 4: {
                int stat_choice;
                printf("1. Afficher la progression d'un athlète\n");
                printf("2. Afficher les statistiques d'un athlète pour une épreuve\n");
                printf("3. Qui envoyer au JO\n");
                printf("Entrez votre choix: ");
                scanf("%d", &stat_choice);
                getchar();  // consume newline

                switch (stat_choice) {
                    case 1: {
                        char athleteName[MAX_NAME], date1[DATE_LEN], date2[DATE_LEN];
                        int event_choice;
                        printf("Entrez le nom de l'athlète: ");
                        get_user_input(NULL, athleteName, MAX_NAME);
                        display_event_menu();
                        printf("Entrez le numéro correspondant au type d'épreuve: ");
                        scanf("%d", &event_choice);
                        getchar();  // consume newline
                        if (event_choice < 1 || event_choice > 5) {
                            printf("Choix d'épreuve invalide.\n");
                            break;
                        }
                        const char *event = (event_choice == 1) ? "100m" :
                                            (event_choice == 2) ? "400m" :
                                            (event_choice == 3) ? "5000m" :
                                            (event_choice == 4) ? "marathon" : "relais 4 x 400 m";
                        printf("Entrez la première date (AAAA-MM-JJ): ");
                        get_user_input(NULL, date1, DATE_LEN);
                        if (!is_valid_date(date1)) {
                            printf("Date invalide.\n");
                            break;
                        }
                        printf("Entrez la deuxième date (AAAA-MM-JJ): ");
                        get_user_input(NULL, date2, DATE_LEN);
                        if (!is_valid_date(date2)) {
                            printf("Date invalide.\n");
                            break;
                        }
                        for (int i = 0; i < athlete_count; i++) {
                            if (strcmp(athletes[i].name, athleteName) == 0) {
                                compare_performance(&athletes[i], event, date1, date2);
                                break;
                            }
                        }
                        break;
                    }
                    case 2: {
                        char athleteName[MAX_NAME];
                        int event_choice;
                        printf("Entrez le nom de l'athlète: ");
                        get_user_input(NULL, athleteName, MAX_NAME);
                        display_event_menu();
                        printf("Entrez le numéro correspondant au type d'épreuve: ");
                        scanf("%d", &event_choice);
                        getchar();  // consume newline
                        if (event_choice < 1 || event_choice > 5) {
                            printf("Choix d'épreuve invalide.\n");
                            break;
                        }
                        const char *event = (event_choice == 1) ? "100m" :
                                            (event_choice == 2) ? "400m" :
                                            (event_choice == 3) ? "5000m" :
                                            (event_choice == 4) ? "marathon" : "relais 4 x 400 m";
                        for (int i = 0; i < athlete_count; i++) {
                            if (strcmp(athletes[i].name, athleteName) == 0) {
                                calculate_statistics(&athletes[i], event);
                                break;
                            }
                        }
                        break;
                    }
                    case 3: {
                        int event_choice;
                        display_event_menu();
                        printf("Entrez le numéro correspondant au type d'épreuve: ");
                        scanf("%d", &event_choice);
                        getchar();  // consume newline
                        if (event_choice < 1 || event_choice > 5) {
                            printf("Choix d'épreuve invalide.\n");
                            break;
                        }
                        const char *event = (event_choice == 1) ? "100m" :
                                            (event_choice == 2) ? "400m" :
                                            (event_choice == 3) ? "5000m" :
                                            (event_choice == 4) ? "marathon" : "relais 4 x 400 m";
                        find_top_athletes(athletes, athlete_count, event);
                        break;
                    }
                    default:
                        printf("Choix invalide.\n");
                        break;
                }
                break;
            }
            case 5:
                printf("Merci d'avoir utilisé CER-J-O Management. Au revoir !\n\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez réessayer.\n\n");
        }
    }
    return 0;
}
