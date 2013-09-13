#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

//#define focus "13"
//#define shot "14"

static int lcdHandler;


void usage(const char *progName){
  fprintf(stderr, "usage: %s [shots] [delay]\n", progName);
}

void focus(){
  pinMode ( 13, OUTPUT);
  digitalWrite ( 13, HIGH);
  sleep(1);
  digitalWrite ( 13, LOW);
}

void shot(){
  pinMode ( 14, OUTPUT);
  digitalWrite ( 14, HIGH);
  sleep (1);
  digitalWrite ( 14, LOW);
}

int main (int argc, char const *argv[]){
  if (argc != 3) {
    usage(argv[0]);
    return 1;
  }
  wiringPiSetup ();
  lcdHandler = lcdInit (2, 16, 8, 11, 10, 0, 1, 2, 3, 4, 5, 6, 7);
  
  if (lcdHandler < 0) {
    fprintf (stderr, "%s: lcdInit failed\n", argv[0]);
    return -1 ;
  }
  
  int i = 0;
  int shots = atoi(argv[1]);
  int delay = atoi(argv[2]);
  int time = ((shots * delay) + shots)/60;
  char iteration[17];
  char message[] = "Shot: ";
  char shotsarray[7];
  char message2[7];
  char timechar[256];
  char timemessage[17] = "This will take:";
  
  sprintf(timechar, "%d", time);
  
  
  
  lcdHome(lcdHandler);
  lcdClear(lcdHandler);
  lcdPosition(lcdHandler, 0, 0);
  lcdPuts (lcdHandler, "Kamera Shutter");
  lcdPosition(lcdHandler, 0, 1);
  lcdPuts (lcdHandler, "v0.1 by darcade");  

  fprintf(stdout, BLUE "======================\n" RED "    Kamera Shotter\n" BLUE "======================\n" RESET);
  
  sleep(2);
  
  strcat (timechar, " min");
  
  printf(YELLOW"%s %s\n\n" RESET,timemessage ,timechar);
  
  
  
  lcdClear(lcdHandler);
  lcdPosition(lcdHandler, 0, 0);
  lcdPuts (lcdHandler, timemessage);
  lcdPosition(lcdHandler, 0, 1);
  lcdPuts (lcdHandler, timechar);

  sleep(5);
  
  lcdClear(lcdHandler);
  
  lcdPosition(lcdHandler, 0, 0);
  lcdPuts (lcdHandler, "Shooting ...");
  
  while (shots>i){
    strcpy(iteration, "");
    strcpy(message, "");
    strcpy(message2, "/");
    sprintf(iteration, "%d", i+1);
    sprintf(shotsarray, "%d", shots);
    strcat (message2, shotsarray);
    strcat (message, iteration);
    strcat (message, message2);
    //fputs (stdout, "Test");
    printf ("\033[A\033[2K");
    printf (CYAN "%s\n" RESET, message );
    fflush(stdout);
    lcdPosition(lcdHandler, 0, 1);
    lcdPuts (lcdHandler, message);
    
    shot();
    i++;
    sleep(delay);
  }
  
  printf(GREEN "FINISHED\n" RESET);
  lcdClear(lcdHandler);
  lcdPosition(lcdHandler, 0, 0);
  lcdPuts (lcdHandler, "finished..");
  
  return 0;
}
