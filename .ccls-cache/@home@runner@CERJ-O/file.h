#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <errno.h>


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

void save_athlete_to_file(const Athlete *athlete);
void load_athlete_from_file(Athlete *athlete, const char *file_name);
void add_performance_to_athlete(Athlete *athlete, const Performance *performance);
void view_performance_history(const Athlete *athletes, int athlete_count, const char *search_name, const char *search_date, const char *search_event);
void add_new_athlete(Athlete athletes[], int *athlete_count);
void add_performance(const char *athlete_name, Athlete athletes[], int athlete_count);
void show_athlete_stats(Athlete athletes[], int athlete_count);
void get_user_input(const char *prompt, char *input, int len);
bool is_valid_event_type(const char *event_type);
bool is_valid_date(const char *date);
bool is_leap_year(int year);
bool is_valid_relay_position(int position);
bool is_valid_time(const char *input);
void centerText(const char* text);
void compare_performance(const Athlete *athlete, const char *event, const char *date1, const char *date2);
void calculate_statistics(const Athlete *athlete, const char *event);
void find_top_athletes(const Athlete athletes[], int athlete_count, const char *event);
void system_clear();

#endif