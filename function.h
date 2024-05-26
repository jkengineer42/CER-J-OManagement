#ifndef FUNCTION_H
#define FUNCTION_H

// Fonction pour afficher les statistiques des athlètes grâce aux critères de recherche de l'utilisateur
void show_athlete_stats(Athlete athletes[], int athlete_count) {
  // Déclaration de variables pour stocker le choix de recherche de l'utilisateur et les critères
  int search_choice;
  char search_name[MAX_NAME] =
      ""; // espace où sera stocké le nom saisi par l'entraineur "buffer"
  char search_date[DATE_LEN] =
      ""; // espace où sera stocké la date saisi par l'entraineur "buffer"
  char search_event[TYPE_LEN] =
      ""; // espace où sera stocké l'épreuve saisi par l'entraineur "buffer"

  // type d'épreuve disponile que l'entraineur peut choisir
  const char *event_types[] = {"100m", "400m", "5000m", "marathon","relais 4 x 400 m"};
  size_t num_event_types = sizeof(event_types) / sizeof(event_types[0]); // Calcul du nombre de types d'épreuves disponibles
  // Affichage des options de recherche disponibles
  printf("\n=====================================\n");
  printf(" Rechercher les statistiques des athlètes par:\n");
  printf("=====================================\n");
  printf("1. Nom\n");
  printf("2. Date\n");
  printf("3. Type d'épreuve\n");
  printf("=====================================\n");
  printf("Entrez votre choix: ");
  scanf("%d", &search_choice);
  getchar(); // Nous avons utiliser getchar pour lire et éliminer le caractère de nouvelle ligne restant "\n" afin de vider

  switch (search_choice) {
  case 1:
    printf("Entrez le nom de l'athlète: ");
    get_user_input(NULL, search_name, MAX_NAME);
    view_performance_history_by_name(athletes, athlete_count, search_name);
    break;
  case 2:
    while (true) {
      printf("Entrez la date (AAAA-MM-JJ): ");
      scanf("%10s", search_date);
      if (is_valid_date(search_date)) {
        break;
      } else {
        printf("Format de date invalide ou date inexistante. Veuillez entrer "
               "une date valide.\n\n");
      }
    }
    view_performance_history_by_date(athletes, athlete_count, search_date);
    break;
  case 3:
    display_event_menu();
    int event_choice;
    printf("Entrez le numéro correspondant au type d'épreuve: ");  
    scanf("%d", &event_choice);
    getchar(); //Nettoie encore une fois le buffer d'entrée pour éviter les erreurs lors des prochaines saisies.
    if (event_choice >= 1 && event_choice <= num_event_types) {
      strcpy(search_event, event_types[event_choice - 1]);  // Nous avons utilisé strcpy pour copier le type d'épreuve choisi dans la variable search_event. Cela permet d'éviter les erreurs liées aux pointeurs.
      view_performance_history_by_event(athletes, athlete_count, search_event);
    } else {
      printf("Choix invalide. Veuillez entrer un nombre entre 1 et %zu.\n\n",
             num_event_types);
    }
    break;
  default:
    printf("\nChoix invalide.\n\n");
    break;
  }
}

void view_performance_history_by_name(const Athlete *athletes,
                                      int athlete_count,
                                      const char *search_name) {
  printf("\nRésultats des recherches par nom :\n\n");
  view_performance_history(athletes, athlete_count, search_name, NULL, NULL); // Les paramètres pour la date et l'événement sont passés comme NULL car ils ne sont pas nécessaires pour ce type de recherche
}

void view_performance_history_by_event(const Athlete *athletes,
                                       int athlete_count,
                                       const char *search_event) {
  printf("\nRésultats des recherches par épreuve :\n\n");
  view_performance_history(athletes, athlete_count, NULL, NULL, search_event); // Ici aussi les paramètres pour le nom et la date ne sont pas nécessaires, donc passés comme NULL
}

void view_performance_history_by_date(const Athlete *athletes,
                                      int athlete_count,
                                      const char *search_date) {
  printf("\nRésultats des recherches par date :\n\n");
  view_performance_history(athletes, athlete_count, NULL, search_date, NULL);
}

void view_performance_history(const Athlete *athletes, int athlete_count,
                              const char *search_name, const char *search_date,
                              const char *search_event) {
  int found = 0;
  for (int i = 0; i < athlete_count; i++) {
    const Athlete *athlete = &athletes[i]; // Pointeur vers l'athlète actuel
    int printedHeader = 0;

    if (search_name != NULL && strlen(search_name) > 0 &&
        strcmp(athlete->name, search_name) != 0) {
      continue;
    } // Si un nom de recherche est spécifié et ne correspond pas au nom de l'athlète, passez au suivant

    for (int j = 0; j < athlete->performance_count; j++) { // Boucle sur toutes les performances de l'athlète actuel
      const Performance *perf = &athlete->performances[j];
      if ((search_date != NULL && strlen(search_date) > 0 &&
           strcmp(perf->date, search_date) != 0) ||
          (search_event != NULL && strlen(search_event) > 0 &&
           strcmp(perf->epreuve, search_event) != 0)) {
        continue; 
      }

      if (!printedHeader) {
        printf("\nHistorique des performances pour %s:\n", athlete->name);
        printf("%-12s %-20s %-8s %-15s\n", "Date", "Type d'Épreuve", "Temps",
               "Position Relais");
        printedHeader = 1;
        found = 1;
      }

      printf("%-12s %-20s %-8.2f ", perf->date, perf->epreuve, perf->time);
      if (perf->relay_position != 0) {
        printf("%-15d", perf->relay_position);
      } else {
        printf("%-15s", "N/A");
      }
      printf("\n");
    }
    printf("\n");
  }

  if (!found) {
    if (search_event != NULL && strlen(search_event) > 0) {
      printf("Aucune performance trouvée pour le type d'épreuve spécifié.\n\n");
    } else if (search_date != NULL && strlen(search_date) > 0) {
      printf("Aucune performance trouvée pour la date spécifiée.\n\n");
    } else if (search_name != NULL && strlen(search_name) > 0) {
      printf("Aucune performance trouvée pour le nom spécifié.\n\n");
    } else {
      printf("Aucune performance trouvée pour les critères spécifiés.\n\n");
    }
  }
}

void load_all_athletes(Athlete athletes[], int *athlete_count) {
  DIR *dir;//Permet d'ouvrir, lire et fermer le repertoire
  struct dirent *ent;
  *athlete_count = 0;
  if ((dir = opendir(".")) != NULL) {
    while ((ent = readdir(dir)) != NULL) {//Boucle tant qu'il reste des fichier à lire
      if (strstr(ent->d_name, ".txt") != NULL) {// regarde si il reste des fichiers texte
        load_athlete_from_file(&athletes[*athlete_count], ent->d_name);// si il y'en à, il les enregistre dans le tableau d'atlhètes
        (*athlete_count)++;
      }
    }
    closedir(dir);
  } else {
    perror("Erreur lors de l'ouverture du répertoire");
  }
}

void get_user_input(const char *prompt, char *input, int len) {
  if (prompt != NULL) {
    printf("%s", prompt);
  }
  fgets(input, len, stdin);
  input[strcspn(input, "\n")] = 0;//remplace la touche entrée contenu dans l'input par '\0'
}

void add_new_athlete(Athlete athletes[], int *athlete_count) {
  if (*athlete_count >= MAX_PERFORMANCES) {
    printf("Nombre maximum d'athlètes atteint.\n\n");
    return;
  }

  printf("Entrez le nom du nouvel athlète: ");
  get_user_input(NULL, athletes[*athlete_count].name, MAX_NAME);

  char file_name[FILE_NAME_LEN];
  snprintf(file_name, FILE_NAME_LEN, "%s.txt", athletes[*athlete_count].name);//nom du fichier 
  FILE *file = fopen(file_name, "r");
  if (file != NULL) {
    fclose(file);
    printf("Un fichier pour l'athlète %s existe déjà. Enregistrement annulé.\n",
           athletes[*athlete_count].name);
    return;
  }

  athletes[*athlete_count].performance_count = 0;
  save_athlete_to_file(&athletes[*athlete_count]);
  (*athlete_count)++;
  system_clear();
}
//la fonction ajoute un nouvel athlète à la liste des athlètes

void add_performance(const char *athlete_name, Athlete athletes[], int athlete_count) {
  const char *event_types[] = {"100m", "400m", "5000m", "marathon", "relais 4 x 400 m"};
  size_t num_event_types = sizeof(event_types) / sizeof(event_types[0]);

  for (int i = 0; i < athlete_count; i++) {
    if (strcmp(athletes[i].name, athlete_name) == 0) {
      Performance new_performance;
      while (true) {//Boucle pour la date
        printf("Entrez la date de performance (AAAA-MM-JJ): ");
        scanf("%10s", new_performance.date);
        if (is_valid_date(new_performance.date)) {
          break;
        } else {
          printf("Format de date invalide ou date inexistante. Veuillez entrer "
                 "une date valide.\n\n");
        }
      }
      int event_choice;
      while (true) {//boucle pour l'épreuve
        display_event_menu();
        printf("\nEntrez le numéro correspondant au type d'épreuve: ");
        if (scanf("%d", &event_choice) != 1 || event_choice < 1 ||
            event_choice > num_event_types) {
          while (getchar() != '\n')
            ;
          printf(
              "Choix invalide. Veuillez entrer un nombre entre 1 et %zu.\n\n",
              num_event_types);
          continue;
        }
        strcpy(new_performance.epreuve, event_types[event_choice - 1]);

        if (event_choice == 5) {//cas particulier du relais
          if (relay_exists_on_date(&athletes[i], new_performance.date)) {
            printf("Une performance de relais pour cette date existe déjà. "
                   "Ajout annulé.\n\n");
            return;
          }
          while (true) {// validation de l'entrée de la position du relais
            printf("Entrez la position de relais (1-4): ");
            if (scanf("%d", &new_performance.relay_position) != 1 || !is_valid_relay_position(new_performance.relay_position)) {
              while (getchar() != '\n');
              printf("Position de relais invalide. Veuillez entrer une valeur "
                     "entre 1 et 4.\n\n");
              continue;
            }
            break;
          }
        } else {
          new_performance.relay_position = 0;//si l'épreuve n'est pas un relais
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
        while (getchar() != '\n');//vide la mémoire tampon 'buffer' de l'entrée invalide
        printf("Temps invalide. Veuillez entrer une valeur positive en "
               "secondes.\n\n");
      }

      getchar();//vide le buffer d'entrée

      add_performance_to_athlete(&athletes[i], &new_performance);
      save_athlete_to_file(&athletes[i]);
      printf("\nPerformance mise à jour !\n\n");
      system_clear();
      return;
    }
  }
  printf("Athlète %s non trouvé.\n\n", athlete_name);
  system_clear();
}
//la fonction permet d'ajouter une performance pour un atlhète 

bool is_valid_time(const char *input) {
  int dot_count = 0;
  for (size_t i = 0; i < strlen(input); i++) {//compte le nombre de virgule
    if (input[i] == '.') {
      dot_count++; 
    } else if (!isdigit(input[i])) {//test si c'est un chiffre décimal ou non
      return false;
    }
    if (dot_count > 1) {
      return false;
    }
  }
  return true;
}

bool is_valid_date(const char *date) {
  int year, month, day;
  if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3) {//lit la date au bon format (AAAA-MM-JJ) et les enregistre séparement
    return false;
  }

  if (year < 1980 || year > 2100) { //On se limite aux années récentes post 1980
    return false;
  }

  if (month < 1 || month > 12) {
    return false;
  }

  if (day < 1 || day > 31) {
    return false;
  }

  if (month == 2) {// cas particulier du mois de février
    if (is_leap_year(year)) {// regarde si c'est une année bissextile
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

bool is_leap_year(int year) {//calcul de l'année bisextile via cette formule :
  if (year % 4 != 0) {// Année non divisible par 4
    return false;
  } else if (year % 100 != 0) {//Année divisible par 4 mais non par 100
    return true;
  } else if (year % 400 != 0) {//Année divisible par 4 et 100 mais non par 400
    return false;
  } else { //Année divisible par 4, 100 et 400
    return true;
  }
}

bool is_valid_relay_position(int position) {//valide l'entrée de la postion du relais
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

  fprintf(file, "%s\n%d\n", athlete->name, athlete->performance_count);//écrit les informations de l'athlète
  for (int i = 0; i < athlete->performance_count; i++) {//Boucle qui parcourt toutes les performances de l'athlète
    fprintf(file, "%s %s %f %d\n", athlete->performances[i].date,
            athlete->performances[i].epreuve, athlete->performances[i].time,
            athlete->performances[i].relay_position);
  }// écrit les performances dans les fichiers
  fclose(file);
  printf("Les données de l'athlète %s ont été mises à jour avec succès.\n",
         athlete->name);
}
//fonction pour enregistrer les informations d'un athlète dans un fichier texte

void load_athlete_from_file(Athlete *athlete, const char *file_name) {
  char file_path[FILE_NAME_LEN];
  snprintf(file_path, FILE_NAME_LEN, "%s", file_name);
  FILE *file = fopen(file_path, "r");
  if (file == NULL) {
    athlete->performance_count = 0;
    return;
  }
  fscanf(file, "%[^\n]\n%d\n", athlete->name, &athlete->performance_count);//lit une chaîne de caractères jusqu'à un caractère de nouvelle ligne
  for (int i = 0; i < athlete->performance_count; i++) {//boucle qui parcourt toutes les performances de l'athlète
    fscanf(file, "%10s %49s %f %d\n", athlete->performances[i].date,
           athlete->performances[i].epreuve, &athlete->performances[i].time,
           &athlete->performances[i].relay_position);
  }
  fclose(file);
}
//fonction pour charger les informations d'un athlète à partir d'un fichier texte

void add_performance_to_athlete(Athlete *athlete, const Performance *performance) {
  if (athlete->performance_count < MAX_PERFORMANCES) {
    athlete->performances[athlete->performance_count] = *performance;//ajout de la nouvelle performance
    athlete->performance_count++;
  } else {
    printf("Nombre maximum de performances atteint pour %s.\n\n",
           athlete->name);
    system_clear();
  }
}
//fonction pour ajouter une nouvelle performance au tableau d'atlhète

void compare_performance(const Athlete *athlete, const char *event, const char *date1, const char *date2) {
  double time1 = -1;//double pour la fonction fabs();
  double time2 = -1;

  for (int i = 0; i < athlete->performance_count; i++) {//recherche les performances demandées par l'utilisateur
    if (strcmp(athlete->performances[i].epreuve, event) == 0) {
      if (strcmp(athlete->performances[i].date, date1) == 0) {
        time1 = athlete->performances[i].time;
      } else if (strcmp(athlete->performances[i].date, date2) == 0) {
        time2 = athlete->performances[i].time;
      }//recherhce de temps pour les deux dates spécifiées
    }
  }

  if (time1 != -1 && time2 != -1) {
    printf("Différence de performance pour %s entre %s et %s: %.2f secondes\n", event, date1, date2, fabs(time2 - time1));
  } else {
    printf("Performances manquantes pour comparer les dates spécifiées.\n");
  }
}
//compare les performances d'un athlète pour une épreuve donné à deux dates spécifiques

void calculate_statistics(const Athlete *athlete, const char *event) {
  float best_time = FLT_MAX;
  float worst_time = 0;
  float total_time = 0;
  int count = 0;

  for (int i = 0; i < athlete->performance_count; i++) {
    if (strcmp(athlete->performances[i].epreuve, event) == 0) { // Vérifie l'épreuve demandée
      float time = athlete->performances[i].time; // Prend le temps de tout les performances de cette épreuve
      if (time < best_time) {
        best_time = time;
      }
      if (time > worst_time) {
        worst_time = time;
      }
      total_time += time;
      count++;
    }
  }
  
  if (count > 0) {
    printf("Meilleur temps pour %s: %.2f\n", event, best_time);
    printf("Pire temps pour %s: %.2f\n", event, worst_time);
    printf("Temps moyen pour %s: %.2f\n", event, total_time / count);
  } else {
    printf("Aucune performance trouvée pour l'épreuve %s.\n", event);
  }
}
//calcule et affiche les statistiques de performance pour une épreuve spécifique d'un athlète

void find_top_athletes(const Athlete athletes[], int athlete_count, const char *event) {
  Athlete *top_athletes[3] = {NULL, NULL, NULL};
  float top_times[3] = {FLT_MAX, FLT_MAX, FLT_MAX};

  for (int i = 0; i < athlete_count; i++) {//parcourt les athlètes
    float total_time = 0; // initialiser à 0
    int count = 0;

    for (int j = 0; j < athletes[i].performance_count; j++) {//comptabilise tout les temps pour l'épreuve demander
      if (strcmp(athletes[i].performances[j].epreuve, event) == 0) {
        total_time += athletes[i].performances[j].time;
        count++;
      }
    }

    if (count > 0) {
      float avg_time = total_time / count; // calcule du temps moyen 

      for (int k = 0; k < 3; k++) {
        if (avg_time < top_times[k]) {
          for (int l = 2; l > k; l--) {
            top_times[l] = top_times[l - 1];
            top_athletes[l] = top_athletes[l - 1];
          } //décale les éléments pour faire de la place pour le nouvel athlète
          top_times[k] = avg_time;
          top_athletes[k] = &athletes[i];
          break;
        }
      }
    }
  }

  printf("Les trois meilleurs athlètes pour %s:\n", event);
  for (int i = 0; i < 3 && top_athletes[i] != NULL; i++) {
    printf("%d. %s avec un temps moyen de %.2f\n", i + 1, top_athletes[i]->name,
           top_times[i]);
  }
}
//identifie les trois meilleurs athlètes pour une épreuve spécifié

void system_clear() {
  printf("Appuyer sur la touche entrée pour continuer...\n");
  while (getchar() != '\n');// attend que l'utilisateur appuie sur Entrée
  system("clear");//nettoie le terminal Unix/Linux 
}
//fonction qui rend l'experience plus agréable pour l'utilisateur

bool relay_exists_on_date(const Athlete *athlete, const char *date) {
  for (int i = 0; i < athlete->performance_count; i++) {
    if (strcmp(athlete->performances[i].date, date) == 0 &&
        athlete->performances[i].relay_position != 0) {
      return true;//cas particulier du relais :  Il n'y a que 1 entraînement de relais par jour
    }
  }
  return false;
}
//fonction qui vérifie si un athlète a déjà une performance de relais enregistrée pour une date donnée

void display_event_menu() {
  const char *event_types[] = {"100m", "400m", "5000m", "marathon", "relais 4 x 400 m"};
  size_t num_event_types = sizeof(event_types) / sizeof(event_types[0]);

  printf("\nSélectionnez le type d'épreuve:\n\n");
  for (size_t i = 0; i < num_event_types; i++) {
    printf("%zu. %s\n\n", i + 1, event_types[i]);
  }
}
//affiche un menu des types d'épreuves disponibles pour l'entraîneur

void stat_menu(Athlete athletes[], int athlete_count) {
  while (1) { // Boucle infinie
    int stat_choice;
    printf("\n=====================================\n");
    printf("\nStatistique avancée\n");
    printf("\n1. Afficher la progression d'un athlète\n");
    printf("\n2. Afficher les statistiques d'un athlète pour une épreuve\n");
    printf("\n3. Qui envoyer au JO ? \n");
    printf("\n4. Retour au menu principal\n");
    printf("\n=====================================\n");
    printf("\nEntrez votre choix: ");
    scanf("%d", &stat_choice);
    getchar(); // nettoie le tampon d'entrée

    switch (stat_choice) {
    case 1: {
      char athleteName[MAX_NAME], date1[DATE_LEN], date2[DATE_LEN];
      int event_choice;
      printf("Entrez le nom de l'athlète: ");
      get_user_input(NULL, athleteName, MAX_NAME);
      int athlete_index = find_athlete_index(athletes, athlete_count, athleteName); // Recherche de l'athlète
      if (athlete_index == -1) {
        printf("Athlète %s non trouvé.\n\n", athleteName); 
        break;
      }
      display_event_menu();
      printf("Entrez le numéro correspondant au type d'épreuve: ");
      scanf("%d", &event_choice);
      getchar();
      if (event_choice < 1 || event_choice > 5) {
        printf("Choix d'épreuve invalide.\n");
        break;
      }
      const char *event = (event_choice == 1)   ? "100m"
                          : (event_choice == 2) ? "400m"
                          : (event_choice == 3) ? "5000m"
                          : (event_choice == 4) ? "marathon"
                                                : "relais 4 x 400 m";
 
      
      while (true) { 
        printf("Entrez la première date (AAAA-MM-JJ): ");
        scanf("%10s", date1); // format necessitant 10 caractères d'où le %10s
        if (is_valid_date(date1)) {
          break;
        } else {
          printf("Format de date invalide ou date inexistante. Veuillez entrer "
                 "une date valide.\n\n");
        }
      }
      while (true) {
        printf("Entrez la deuxième date (AAAA-MM-JJ): ");
        scanf("%10s", date2);
        if (is_valid_date(date2) && strcmp(date1, date2) != 0) {
          break;
        }
        printf("Format de date invalide ou date similaire. Veuillez entrer une "
               "date valide.\n\n");
      }

      compare_performance(&athletes[athlete_index], event, date1, date2);
      break;
    }
    case 2: {
      char athleteName[MAX_NAME];
      int event_choice;
      printf("Entrez le nom de l'athlète: ");
      get_user_input(NULL, athleteName, MAX_NAME); // Stockage dans athleteName
      int athlete_index = find_athlete_index(athletes, athlete_count, athleteName);
      if (athlete_index == -1) {
        printf("Athlète %s non trouvé.\n\n", athleteName);
        break;
      }
      display_event_menu();
      printf("Entrez le numéro correspondant au type d'épreuve: ");
      scanf("%d", &event_choice);
      getchar();
      if (event_choice < 1 || event_choice > 5) {
        printf("Choix d'épreuve invalide.\n");
        break;
      }
      //expression ternaire
      const char *event = (event_choice == 1)   ? "100m"
                          : (event_choice == 2) ? "400m"
                          : (event_choice == 3) ? "5000m"
                          : (event_choice == 4) ? "marathon"
                                                : "relais 4 x 400 m";
      calculate_statistics(&athletes[athlete_index], event);
      system_clear(); // amelioration de la clarté du terminal
      break;
    }
    case 3: {
      int event_choice;
      display_event_menu();
      printf("Entrez le numéro correspondant au type d'épreuve: ");
      scanf("%d", &event_choice);
      getchar();
      if (event_choice < 1 || event_choice > 5) {
        printf("Choix d'épreuve invalide.\n");
        break;
      }
      const char *event = (event_choice == 1)   ? "100m"
                          : (event_choice == 2) ? "400m"
                          : (event_choice == 3) ? "5000m"
                          : (event_choice == 4) ? "marathon"
                                                : "relais 4 x 400 m";
      find_top_athletes(athletes, athlete_count, event);
      system_clear();
      break;
    }
    case 4:
      system("clear"); // Nettoyage de la console
      return;
    default:
      printf("Choix invalide. Veuillez réessayer.\n");
      break;
    }
  }
}

int find_athlete_index(const Athlete athletes[], int athlete_count, const char *name) {
  for (int i = 0; i < athlete_count; i++) {
    if (strcmp(athletes[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}
//recherche un athlète par son nom dans un tableau d'athlètes et retourne l'indice de l'athlète dans le tableau si il la fonction la trouvé

#endif