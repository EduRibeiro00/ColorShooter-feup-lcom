#include <lcom/lcf.h>
#include <stdio.h>
#include "Highscores.h"
#include "rtc.h"

struct date_t{

uint32_t day, month, year, minutes, hours; ///< the date on which the highscore was gotten
};


struct highscores_t{

/* variables containing the highscores in their order */
int highscore1;
int highscore2;
int highscore3;
int highscore4;
int highscore5;

/* variables that indicate if the highscores exist or not */
bool hs1_exists;
bool hs2_exists;
bool hs3_exists;
bool hs4_exists;
bool hs5_exists;

/* variables that indicate the date and hour for each one of the highscores */
Date date1, date2, date3, date4, date5;
};



Highscores* init_highscores(){

  Highscores* hs = (Highscores*) malloc(sizeof(Highscores));
  if(hs == HIGHSCORES_ALLOC_FAILED)
    return HIGHSCORES_ALLOC_FAILED;

  //sets the highscores to -1, so that even if the first score is 0, it will be on the scoreboard
  hs->highscore1 = -1;
  hs->highscore2 = -1;
  hs->highscore3 = -1;
  hs->highscore4 = -1;
  hs->highscore5 = -1;

  //sets all the bools to false
  hs->hs1_exists = false;
  hs->hs2_exists = false;
  hs->hs3_exists = false;
  hs->hs4_exists = false;
  hs->hs5_exists = false;

  //resets the days
  hs->date1.day = 0;
  hs->date2.day = 0;
  hs->date3.day = 0;
  hs->date4.day = 0;
  hs->date5.day = 0;

  //resets the months
  hs->date1.month = 0;
  hs->date2.month = 0;
  hs->date3.month = 0;
  hs->date4.month = 0;
  hs->date5.month = 0;

  //resets the years
  hs->date1.year = 0; 
  hs->date2.year = 0;
  hs->date3.year = 0;
  hs->date4.year = 0;
  hs->date5.year = 0;

  //resets the minutes
  hs->date1.minutes = 0;
  hs->date2.minutes = 0;
  hs->date3.minutes = 0;
  hs->date4.minutes = 0;
  hs->date5.minutes = 0;

  //resets the hours
  hs->date1.hours = 0;
  hs->date2.hours = 0;
  hs->date3.hours = 0;
  hs->date4.hours = 0;
  hs->date5.hours = 0;


  //loads the current highscores
  load_highscores(hs, "/home/lcom/labs/proj/src/hs.txt");

  return hs;
}

//-------------------

void load_highscores(Highscores* hs, char* fileName){

  FILE* fptr;
  fptr = fopen(fileName, "r");
  if(fptr == NULL){
    printf("The file could not be found!\n");
    return;
  }

  int highscoreNumber = 1;

  while(!feof(fptr)){

    uint32_t day, month, year, hours, mins;
    int score;

    fscanf(fptr, "%d %d %d %d %d %d", &day, &month, &year, &hours, &mins, &score);

    switch(highscoreNumber){

      case 1:
        hs->hs1_exists = true;
        hs->date1.day = day;
        hs->date1.month = month;
        hs->date1.year = year;
        hs->date1.hours = hours;
        hs->date1.minutes = mins;
        hs->highscore1 = score;
        break;

      case 2:
        hs->hs2_exists = true;
        hs->date2.day = day;
        hs->date2.month = month;
        hs->date2.year = year;
        hs->date2.hours = hours;
        hs->date2.minutes = mins;
        hs->highscore2 = score;
        break;

      case 3:
        hs->hs3_exists = true;
        hs->date3.day = day;
        hs->date3.month = month;
        hs->date3.year = year;
        hs->date3.hours = hours;
        hs->date3.minutes = mins;
        hs->highscore3 = score;
        break;

      case 4:
        hs->hs4_exists = true;
        hs->date4.day = day;
        hs->date4.month = month;
        hs->date4.year = year;
        hs->date4.hours = hours;
        hs->date4.minutes = mins;
        hs->highscore4 = score;
        break;

      case 5:
        hs->hs5_exists = true;
        hs->date5.day = day;
        hs->date5.month = month;
        hs->date5.year = year;
        hs->date5.hours = hours;
        hs->date5.minutes = mins;
        hs->highscore5 = score;
        break;

      default:
        break;
    }

    highscoreNumber++;
  }  

  fclose(fptr);
}

//-------------------

void save_highscores(Highscores* hs, char* fileName){

  FILE* fptr;
  fptr = fopen(fileName, "w");

  if(hs->hs1_exists)
    fprintf(fptr, "%d %d %d %d %d %d", hs->date1.day, hs->date1.month, hs->date1.year, hs->date1.hours, hs->date1.minutes, hs->highscore1);

  if(hs->hs2_exists)
    fprintf(fptr, "\n%d %d %d %d %d %d", hs->date2.day, hs->date2.month, hs->date2.year, hs->date2.hours, hs->date2.minutes, hs->highscore2);

  if(hs->hs3_exists)
    fprintf(fptr, "\n%d %d %d %d %d %d", hs->date3.day, hs->date3.month, hs->date3.year, hs->date3.hours, hs->date3.minutes, hs->highscore3);

  if(hs->hs4_exists)
    fprintf(fptr, "\n%d %d %d %d %d %d", hs->date4.day, hs->date4.month, hs->date4.year, hs->date4.hours, hs->date4.minutes, hs->highscore4);

  if(hs->hs5_exists)
    fprintf(fptr, "\n%d %d %d %d %d %d", hs->date5.day, hs->date5.month, hs->date5.year, hs->date5.hours, hs->date5.minutes, hs->highscore5);


  fclose(fptr);
}

//-------------------

void delete_highscores(Highscores* hs){

  if(hs == NULL)
    return;

  save_highscores(hs, "/home/lcom/labs/proj/src/hs.txt");

  free(hs);
  hs = NULL;
}

//-------------------

void extract_date_and_hour(Highscores* hs, int number){

  switch(number){

    case 1:
      do{

        if(!RTCUpdating()){
          get_date(&(hs->date1.day), &(hs->date1.month), &(hs->date1.year));
          get_hour(&(hs->date1.minutes), &(hs->date1.hours));
        }

      }while(RTCUpdating());

      break;

    case 2:
      do{

        if(!RTCUpdating()){
          get_date(&(hs->date2.day), &(hs->date2.month), &(hs->date2.year));
          get_hour(&(hs->date2.minutes), &(hs->date2.hours));
        }

      }while(RTCUpdating());

      break;

    case 3:
      do{

        if(!RTCUpdating()){
          get_date(&(hs->date3.day), &(hs->date3.month), &(hs->date3.year));
          get_hour(&(hs->date3.minutes), &(hs->date3.hours));
        }

      }while(RTCUpdating());

      break;

    case 4:
      do{

        if(!RTCUpdating()){
          get_date(&(hs->date4.day), &(hs->date4.month), &(hs->date4.year));
          get_hour(&(hs->date4.minutes), &(hs->date4.hours));
        }

      }while(RTCUpdating());

      break;

    case 5:
      do{

        if(!RTCUpdating()){
          get_date(&(hs->date5.day), &(hs->date5.month), &(hs->date5.year));
          get_hour(&(hs->date5.minutes), &(hs->date5.hours));
        }

      }while(RTCUpdating());

      break;

    default:
      break;
  }
 }

//-------------------

void update_highscores(Highscores* hs, int newScore){
  
  if(newScore > hs->highscore1){ //we have a new highscore!

      hs->highscore5 = hs->highscore4; hs->date5 = hs->date4; hs->hs5_exists = hs->hs4_exists;
      hs->highscore4 = hs->highscore3; hs->date4 = hs->date3; hs->hs4_exists = hs->hs3_exists;
      hs->highscore3 = hs->highscore2; hs->date3 = hs->date2; hs->hs3_exists = hs->hs2_exists;
      hs->highscore2 = hs->highscore1; hs->date2 = hs->date1; hs->hs2_exists = hs->hs1_exists;
      hs->highscore1 = newScore;
      hs->hs1_exists = true;
      extract_date_and_hour(hs, 1);
    
    }
    else if(newScore > hs->highscore2){ //2nd best score

      hs->highscore5 = hs->highscore4; hs->date5 = hs->date4; hs->hs5_exists = hs->hs4_exists;
      hs->highscore4 = hs->highscore3; hs->date4 = hs->date3; hs->hs4_exists = hs->hs3_exists;
      hs->highscore3 = hs->highscore2; hs->date3 = hs->date2; hs->hs3_exists = hs->hs2_exists;
      hs->highscore2 = newScore;
      hs->hs2_exists = true;
      extract_date_and_hour(hs, 2);

    }
    else if(newScore > hs->highscore3){ //3rd best score

      hs->highscore5 = hs->highscore4; hs->date5 = hs->date4; hs->hs5_exists = hs->hs4_exists;
      hs->highscore4 = hs->highscore3; hs->date4 = hs->date3; hs->hs4_exists = hs->hs3_exists;
      hs->highscore3 = newScore;
      hs->hs3_exists = true;
      extract_date_and_hour(hs, 3);
    
    }
    else if(newScore > hs->highscore4){ //4th best score

      hs->highscore5 = hs->highscore4; hs->date5 = hs->date4; hs->hs5_exists = hs->hs4_exists;
      hs->highscore4 = newScore;
      hs->hs4_exists = true;
      extract_date_and_hour(hs, 4);

    }
    else if(newScore > hs->highscore5){ //5th best score

      hs->highscore5 = newScore;
      hs->hs5_exists = true;
      extract_date_and_hour(hs, 5);
    }

  }

//-------------------

int get_highscore(Highscores* hs, int number){

  switch(number){

    case 1:
      return hs->highscore1;

    case 2:
      return hs->highscore2;

    case 3:
      return hs->highscore3;

    case 4:
      return hs->highscore4;

    case 5:
      return hs->highscore5;

    default:
      return 0;
  }
}

//-------------------

bool get_hs_exists(Highscores* hs, int number){

  switch(number){

    case 1:
      return hs->hs1_exists;

    case 2:
      return hs->hs2_exists;

    case 3:
      return hs->hs3_exists;

    case 4:
      return hs->hs4_exists;

    case 5:
      return hs->hs5_exists;

    default:
      return 0;
  }
}

//-------------------

uint32_t get_year(Highscores* hs, int number){

  switch(number){

    case 1:
      return hs->date1.year;

    case 2:
      return hs->date2.year;

    case 3:
      return hs->date3.year;

    case 4:
      return hs->date4.year;

    case 5:
      return hs->date5.year;

    default:
      return 0;
  }
}

//-------------------

uint32_t get_month(Highscores* hs, int number){

  switch(number){

    case 1:
      return hs->date1.month;

    case 2:
      return hs->date2.month;

    case 3:
      return hs->date3.month;

    case 4:
      return hs->date4.month;

    case 5:
      return hs->date5.month;

    default:
      return 0;
  }
}

//-------------------

uint32_t get_day(Highscores* hs, int number){

  switch(number){

    case 1:
      return hs->date1.day;

    case 2:
      return hs->date2.day;

    case 3:
      return hs->date3.day;

    case 4:
      return hs->date4.day;

    case 5:
      return hs->date5.day;

    default:
      return 0;
  }
}

//-------------------

uint32_t get_hours(Highscores* hs, int number){

  switch(number){

    case 1:
      return hs->date1.hours;

    case 2:
      return hs->date2.hours;

    case 3:
      return hs->date3.hours;

    case 4:
      return hs->date4.hours;

    case 5:
      return hs->date5.hours;

    default:
      return 0;
  }
}

//-------------------

uint32_t get_minutes(Highscores* hs, int number){

  switch(number){

    case 1:
      return hs->date1.minutes;

    case 2:
      return hs->date2.minutes;

    case 3:
      return hs->date3.minutes;

    case 4:
      return hs->date4.minutes;

    case 5:
      return hs->date5.minutes;

    default:
      return 0;
  }
}
