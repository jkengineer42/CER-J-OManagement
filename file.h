#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <dirent.h>
#include <math.h>


#define MAX_NAME 100
#define MAX_PERFORMANCES 100
#define DATE_LEN 11
#define TYPE_LEN 50
#define FILE_NAME_LEN 105
#define FLT_MAX 100000
#define BLACK "\033[30m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define YELW "\e[0;93m"
#define RED "\033[0;31m"
#define BLUE "\033[36m"
#define CYAN "\e[0;96m"


typedef struct {
    char date[DATE_LEN];
    char epreuve[TYPE_LEN];
    float time;
    int relay_position;
} Performance;

typedef struct {
    char name[MAX_NAME];
    Performance performances[MAX_PERFORMANCES];
    int performance_count;
} Athlete; 

void show_athlete_stats(Athlete athletes[], int athlete_count);
void view_performance_history_by_name(const Athlete *athletes, int athlete_count, const char *search_name);
void view_performance_history_by_event(const Athlete *athletes, int athlete_count, const char *search_event);
void view_performance_history_by_date(const Athlete *athletes, int athlete_count, const char *search_date);
void view_performance_history(const Athlete *athletes, int athlete_count, const char *search_name, const char *search_date, const char *search_event);
void load_all_athletes(Athlete athletes[], int *athlete_count);
void get_user_input(const char *prompt, char *input, int len);
void add_new_athlete(Athlete athletes[], int *athlete_count);
void add_performance(const char *athlete_name, Athlete athletes[], int athlete_count);
bool is_valid_time(const char *input);
bool is_valid_date(const char *date);
bool is_leap_year(int year);
bool is_valid_relay_position(int position);
void save_athlete_to_file(const Athlete *athlete);
void load_athlete_from_file(Athlete *athlete, const char *file_name);
void add_performance_to_athlete(Athlete *athlete, const Performance *performance);
void compare_performance(const Athlete *athlete, const char *event, const char *date1, const char *date2);
void calculate_statistics(const Athlete *athlete, const char *event);
void find_top_athletes(const Athlete athletes[], int athlete_count, const char *event);
void system_clear();
void display_event_menu();
void stat_menu(Athlete athletes[], int athlete_count);
int find_athlete_index(const Athlete athletes[], int athlete_count, const char *name);
bool relay_exists_on_date(const Athlete *athlete, const char *date);



#endif
