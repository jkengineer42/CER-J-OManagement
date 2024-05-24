#ifndef FUNCTION_H
#define FUNCTION_H

void centerText(const char* text) {
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);

    int terminalWidth = ws.ws_col;
    int textLength = strlen(text);
    int padding = (terminalWidth - textLength) / 2;

    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    printf("%s\n", text);
}


void show_athlete_stats(Athlete athletes[], int athlete_count) {
    int search_choice;
    char search_name[MAX_NAME] = "";
    char search_date[DATE_LEN] = "";
    char search_event[TYPE_LEN] = "";

    const char *event_types[] = {"100m", "400m", "5000m", "marathon", "relais 4 x 400 m"};
    size_t num_event_types = sizeof(event_types) / sizeof(event_types[0]);

    printf(CYAN "\n=====================================\n" RESET);
    printf(" Rechercher les statistiques des athlètes par:\n");
    printf(CYAN "=====================================\n" RESET );
    printf("1. Nom\n");
    printf("2. Date\n");
    printf("3. Type d'épreuve\n");
    printf(CYAN "=====================================\n" RESET);
    printf("Entrez votre choix: ");
    scanf("%d", &search_choice);
    getchar();  // consume newline

    switch (search_choice) {
        case 1:
            printf("Entrez le nom de l'athlète: ");
            get_user_input(NULL, search_name, MAX_NAME);
            view_performance_history(athletes, athlete_count, search_name, NULL, NULL);
            break;
        case 2:
            printf("Entrez la date (AAAA-MM-JJ): ");
            get_user_input(NULL, search_date, DATE_LEN);
            view_performance_history(athletes, athlete_count, NULL, search_date, NULL);
            break;
        case 3:
            printf("Sélectionnez le type d'épreuve:\n");
            for (size_t i = 0; i < num_event_types; i++) {
                printf("%zu. %s\n", i + 1, event_types[i]);
            }
            int event_choice;
            printf("Entrez le numéro correspondant au type d'épreuve: ");
            scanf("%d", &event_choice);
            if (event_choice >= 1 && event_choice <= num_event_types) {
                strcpy(search_event, event_types[event_choice - 1]);
                view_performance_history(athletes, athlete_count, NULL, NULL, search_event);
            } else {
                printf("Choix invalide. Veuillez entrer un nombre entre 1 et %zu.\n\n", num_event_types);
            }
            break;
        default:
            printf("\nChoix invalide.\n\n");
            break;
    }
}

void view_performance_history(const Athlete *athletes, int athlete_count, const char *search_name, const char *search_date, const char *search_event) {
    int found = 0;
    printf("\nRésultats des recherches :\n\n");
    for (int i = 0; i < athlete_count; i++) {
        const Athlete *athlete = &athletes[i];
        int printedHeader = 0;

        if (search_name != NULL && strlen(search_name) > 0 && strcmp(athlete->name, search_name) != 0) {
            continue;
        }

        for (int j = 0; j < athlete->performance_count; j++) {
            const Performance *perf = &athlete->performances[j];
            if ((search_date != NULL && strlen(search_date) > 0 && strcmp(perf->date, search_date) != 0) ||
                (search_event != NULL && strlen(search_event) > 0 && strcmp(perf->epreuve, search_event) != 0)) {
                continue;
            }

            if (!printedHeader) {
                printf("\nHistorique des performances pour %s:\n", athlete->name);
                printf("%-12s %-20s %-8s %-15s\n", "Date", "Type d'Épreuve", "Temps", "Position Relais");
                printedHeader = 1;
                found = 1;
            }

            printf("%-12s %-20s %-8.2f \n", perf->date, perf->epreuve, perf->time);
            if (perf->relay_position != 0) {
                printf("%-15d\n", perf->relay_position);
            } else {
                printf("%-15s\n", "N/A");
            }
        }
    }

    if (!found) {
        printf("Aucune performance trouvée pour les critères spécifiés.\n\n");
    }
}

void get_user_input(const char *prompt, char *input, int len) {
    if (prompt != NULL) {
        printf("%s", prompt);
    }
    fgets(input, len, stdin);// Lis une ligne d'entrée jusqu'à len-1 caractères et stocke dans input
    input[strcspn(input, "\n")] = 0;  // Trouve la position du premier '\n' dans input et le remplace par '\0'
}

void add_new_athlete(Athlete athletes[], int *athlete_count) {
    if (*athlete_count >= MAX_PERFORMANCES) {
        printf("Nombre maximum d'athlètes atteint.\n\n");
        return;
    }

    printf("Entrez le nom du nouvel athlète: ");
    get_user_input(NULL, athletes[*athlete_count].name, MAX_NAME);
    athletes[*athlete_count].performance_count = 0;
    save_athlete_to_file(&athletes[*athlete_count]);
    (*athlete_count)++;
    centerText("\nL'Athlète à bien été ajouté !\n\n");
}

void add_performance(const char *athlete_name, Athlete athletes[], int athlete_count) {
    const char *event_types[] = {"100m", "400m", "5000m", "marathon", "relais 4 x 400 m"};
    size_t num_event_types = sizeof(event_types) / sizeof(event_types[0]);

    for (int i = 0; i < athlete_count; i++) {
        if (strcmp(athletes[i].name, athlete_name) == 0) {
            Performance new_performance;
            while (true) {
                printf("Entrez la date de performance (AAAA-MM-JJ): ");
                scanf("%10s", new_performance.date);
                if (is_valid_date(new_performance.date)) {
                    break;
                } else {
                    printf("Format de date invalide ou date inexistante. Veuillez entrer une date valide.\n\n");
                }
            }
            int event_choice;
            while (true) {
                printf("\nSélectionnez le type d'épreuve:\n\n");
                for (size_t j = 0; j < num_event_types; j++) {
                    printf("%zu. %s\n", j + 1, event_types[j]);
                }
                printf("\nEntrez le numéro correspondant au type d'épreuve: ");
                if (scanf("%d", &event_choice) != 1 || event_choice < 1 || event_choice > num_event_types) {
                    while (getchar() != '\n');  // Consommer tous les caractères restants dans le buffer d'entrée
                    printf("Choix invalide. Veuillez entrer un nombre entre 1 et %zu.\n\n", num_event_types);
                    continue;
                }
                strcpy(new_performance.epreuve, event_types[event_choice - 1]);

                if (event_choice == 5) { // Si c'est "relais 4 x 400 m"
                    while (true) {
                        printf("Entrez la position de relais (1-4): ");
                        if (scanf("%d", &new_performance.relay_position) != 1 || !is_valid_relay_position(new_performance.relay_position)) {
                            while (getchar() != '\n');  // Consommer tous les caractères restants dans le buffer d'entrée
                            printf("Position de relais invalide. Veuillez entrer une valeur entre 1 et 4.\n\n");
                            continue;
                        }
                        break;
                    }
                } else {
                    new_performance.relay_position = 0; // Non applicable
                }
                break;
            }
            char time_input[20];
            while (true) {
                printf("Entrez le temps de performance (en secondes): ");
                scanf("%s", time_input);
                if (is_valid_time(time_input)) {
                    new_performance.time = atof(time_input);
                    if (new_performance.time >= 0) {
                        break;
                    }
                }
                while (getchar() != '\n');  // Consommer tous les caractères restants dans le buffer d'entrée
                printf("Temps invalide. Veuillez entrer une valeur positive en secondes.\n\n");
            }

            getchar();  // Consommer le caractère de nouvelle ligne laissé par scanf

            add_performance_to_athlete(&athletes[i], &new_performance);
            save_athlete_to_file(&athletes[i]);
            centerText("\nPerformance mise à jour !\n\n");
            return;
        }
    }
    printf("Athlète %s non trouvé.\n\n", athlete_name);
}
bool is_valid_time(const char *input) {
    int dot_count = 0;
    for (size_t i = 0; i < strlen(input); i++) {
        if (input[i] == '.') {
            dot_count++;
        } else if (!isdigit(input[i])) {
            return false;
        }
        if (dot_count > 1) {
            return false;
        }
    }
    return true;
}




bool is_valid_event_type(const char *event_type) {
    const char *valid_event_types[] = {"100m", "400m", "5000m", "marathon", "relais 4*400 m"};
    size_t num_valid_types = sizeof(valid_event_types) / sizeof(valid_event_types[0]);
    for (size_t i = 0; i < num_valid_types; i++) {
        if (strcmp(event_type, valid_event_types[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool is_valid_date(const char *date) {
    int year, month, day;
    if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3) {
        return false;
    }

    if (year < 1980 || year > 2100) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1 || day > 31) {
        return false;
    }

    if (month == 2) {
        if (is_leap_year(year)) {
            return day <= 29;
        } else {
            return day <= 28;
        }
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return day <= 30;
    }

    return true;
}

bool is_leap_year(int year) {
    if (year % 4 != 0) {
        return false;
    } else if (year % 100 != 0) {
        return true;
    } else if (year % 400 != 0) {
        return false;
    } else {
        return true;
    }
}

bool is_valid_relay_position(int position) {
    return position >= 1 && position <= 4;
}

void save_athlete_to_file(const Athlete *athlete) {
    char file_name[FILE_NAME_LEN];
    snprintf(file_name, FILE_NAME_LEN, "%s.txt", athlete->name);
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    fprintf(file, "%s\n%d\n", athlete->name, athlete->performance_count);
    for (int i = 0; i < athlete->performance_count; i++) {
        fprintf(file, "%s %s %f %d\n", athlete->performances[i].date, athlete->performances[i].epreuve,
                athlete->performances[i].time, athlete->performances[i].relay_position);
    }
    fclose(file);
}

void load_athlete_from_file(Athlete *athlete, const char *file_name) {
    char file_path[FILE_NAME_LEN];
    snprintf(file_path, FILE_NAME_LEN, "%s.txt", file_name);
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Aucun enregistrement existant trouvé pour %s. Création d'un nouvel enregistrement.\n\n", athlete->name);
        athlete->performance_count = 0;
        return;
    }
    fscanf(file, "%[^\n]\n%d\n", athlete->name, &athlete->performance_count);
    for (int i = 0; i < athlete->performance_count; i++) {
        fscanf(file, "%10s %49s %f %d\n", athlete->performances[i].date, athlete->performances[i].epreuve,
               &athlete->performances[i].time, &athlete->performances[i].relay_position);
    }
    fclose(file);
}

void add_performance_to_athlete(Athlete *athlete, const Performance *performance) {
    if (athlete->performance_count < MAX_PERFORMANCES) {
        athlete->performances[athlete->performance_count] = *performance;
        athlete->performance_count++;
    } else {
        printf("Nombre maximum de performances atteint pour %s.\n\n", athlete->name);
    }
}

void display_best_performers(const Athlete athletes[], int athlete_count) {
    if (athlete_count == 0) {
        printf("Aucun athlète disponible.\n\n");
        return;
    }

    const char *event_types[] = {"100m", "400m", "5000m", "marathon", "relais 4*400 m"};
    size_t num_event_types = sizeof(event_types) / sizeof(event_types[0]);

    Performance best_performances[num_event_types];
    Athlete *best_athletes[num_event_types];

    for (size_t i = 0; i < num_event_types; i++) {
        best_athletes[i] = NULL;
    }

    for (int i = 0; i < athlete_count; i++) {
        for (int j = 0; j < athletes[i].performance_count; j++) {
            for (size_t k = 0; k < num_event_types; k++) {
                if (strcmp(athletes[i].performances[j].epreuve, event_types[k]) == 0) {
                    if (best_athletes[k] == NULL || athletes[i].performances[j].time < best_performances[k].time) {
                        best_performances[k] = athletes[i].performances[j];
                        best_athletes[k] = &athletes[i];
                    }
                }
            }
        }
    }

    printf(CYAN "\n=====================================\n"RESET);
    centerText(" Meilleurs Performeurs\n");
    printf(CYAN "=====================================\n"RESET);
    for (size_t i = 0; i < num_event_types; i++) {
        if (best_athletes[i] != NULL) {
            printf("Meilleur performeur pour %s: %s\n\n", event_types[i], best_athletes[i]->name);
            printf("Meilleure performance:\n %s, %s, %.2f, Position: %d\n\n",
                   best_performances[i].date, best_performances[i].epreuve, best_performances[i].time, best_performances[i].relay_position);
        } else {
            printf("Aucune performance pour %s.\n\n", event_types[i]);
        }
    }
}


#endif