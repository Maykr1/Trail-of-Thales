#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// Set Bold Text On
#define COLOR_BOLD "\e[1m"

// Set Bold Text off
#define COLOR_OFF "\e[m"
// variables
//Player input
int input;
int sinput;
int dinput;
struct character {
  int health;
};
//Player
struct character p = {100};
//Final boss
struct character t = {100};

//Variable for where the player currently is in the game
int pathNum = 0;
int eventMax = 20;
int eventMin = 0;

//Generates random numbers
int rolldie(int max, int min) {
  int randomN = rand() % max + min;
  return randomN;
}
//Combat when encountering enemy
void dieEvent(int num) {
  if (num == 20) {
    printf("You rolled a %d \n", num);
    printf("You killed the enemy while remaining unscathed!\n");
  } else if (num >= 15) {
    printf("You rolled a %d \n", num);
    printf("You killed the enemy, but you took a minimal amount of damage.\n");
    p.health -= rolldie(5, 1);
  } else if (num >= 10) {
    printf("You rolled a %d \n", num);
    printf("You killed the enemy, but took a small amount of damage.\n");
    p.health -= rolldie(15, 5);
  } else if (num >= 5) {
    printf("You rolled a %d \n", num);
    printf("You killed the enemy, but it took away a large amount of your health\n");
    p.health -= rolldie(20, 15);
  } else {
    printf("You rolled a %d \n", num);
    p.health -= 100;
  }
  printf("Your health: %d\n", p.health);
  if (p.health <= 0) {
      printf("You died!");
      exit(0);
  }
}

void finalBoss() { //Sequence for final boss
  int finalInput;
  int pDamage;
  int tDamage;
  printf(COLOR_BOLD "\n BOSS BATTLE!!!\n" COLOR_OFF);
  printf("\nI love the smell of death! - Thales\n");
  
  while (p.health > 0 && t.health > 0) {
    printf("Attack or Defend?\n");
    printf("[1] - Attack\n");
    printf("[2] - Defend\n");

    scanf("%d", &finalInput);
    pDamage = rolldie(eventMax, eventMin);
    tDamage = rolldie(20, 1);
  
    if (finalInput == 1) {
      t.health -= pDamage;
      printf("You dealt %d damage. Health: %d\n", pDamage, p.health);
      p.health -= tDamage;
      printf("Thales dealt %d damage. Health: %d\n", tDamage, t.health); 
    } else {
      tDamage -= rolldie(tDamage, 1);
      p.health -= tDamage;
      printf("Thales dealt %d damage. Health: %d\n", tDamage, t.health);
    }
    if (p.health <= 0 && t.health <= 0) {
      printf("Both of you are exhausted from the long battle. Thales raises his hand to cast a spell, but you then lunge at him. As Thales released the spell, you plunge your sword into him. Thales was slain, but unfortunately at the cost of your life.\n");
    }
    if (p.health <= 0 && t.health > 0) {
      printf("You're struggling to get up, but with a single strike of lightning, Thales finished you off. Will there be an end to Thales's rule?\n");
    }
    if (p.health > 0 && t.health <= 0) {
      printf("You killed Thales! You won!\n");
      FILE *eptr;

      eptr = fopen("ending.txt", "r");
      char ending[10000];
      
      fgets(ending, 10000, eptr);
      printf("\n\n\n%s\n", ending);
      
      fclose(eptr);
    }
  }
  exit(0);
} 

void HUD() {
  while (1) {
    if (pathNum == 2) {
      finalBoss();
    }
    printf("\nYou encounter a fork at a road. What direction will you take?\n");
    printf("[1] - To The Village\n");
    printf("[2] - To The Bay\n");
    printf("[3] - To The Forest\n");
    scanf("%d", &sinput);
    
    if (sinput == 1) {
      path(1, pathNum);
    } else if (sinput == 2) {
      path(2, pathNum);
    } else if (sinput == 3) {
      path(3, pathNum);
    } else {
      HUD();
    }
  }
}

//Random events on paths
int event (int randomNumber) { 
  if (randomNumber == 1) { //Serpent
    printf("You encountered an aquatic serpent, what do you do?\n");
  } else if (randomNumber == 2) { //Pixie
    printf("You encountered a pixie, what do you do?\n");
  } else if (randomNumber == 3) { //Bandit
    printf("You encountered a bandit, what do you do?\n");
  } else if (randomNumber == 4) { //Hobgoblin
    printf("You encountered a hobgoblin, what do you do?\n");
  } else if (randomNumber == 5) { //Troll
    printf("You encountered a troll, what do you do?\n");
  } else if (randomNumber == 6) { //Orc
    printf("You encountered a orc, what do you do?\n");
  } else if (randomNumber == 7) { 
    printf("You encountered a snake, what do you do?\n");
  } else if (randomNumber == 8) {
    printf("You encountered a werewolf, what do you do?\n");
  } else if (randomNumber == 9) {
    printf("You encountered Rogue, what do you do?\n");
  } else if (randomNumber == 10) {
    printf("You encountered an fae, what do you do?\n");
  }
  dieEvent(rolldie(eventMax,eventMin));
  pathNum++;
  HUD();
}

//Paths from the start to the end
int path (int choice, int pathNumber) {
  printf("You are on path #%d\n",pathNum+1);
  if (pathNumber == 2) {
    finalBoss();
  } else if (pathNumber == 0) {
    if (choice == 1) {
      event(rolldie(10, 1));
    } else if (choice == 2) {
      event(rolldie(10, 1));
    } else if (choice == 3) {
      event(rolldie(10, 1));
    } else {
      HUD();
    }
  } else if (pathNumber == 1) {
    if (choice == 1) {
      event(rolldie(10, 1));
    } else if (choice == 2) {;
      event(rolldie(10, 1));
    } else if (choice == 3) {
      event(rolldie(10, 1));
    } else {
      HUD();
    }
  } 
}

//story
void story() {
  //Introduction
  FILE *sptr;
  FILE *aptr;
  //Reading from files
  sptr = fopen("startup.txt", "r");
  aptr = fopen("addressing.txt", "r");
  
  char story[10000];
  char addressing[10000];
  
  fgets(story, 10000, sptr);
  fgets(addressing, 10000, aptr);
  
  printf("%s\n\n", story);
  printf("%s\n", addressing);

  fclose(sptr);
  fclose(aptr);

  //Story begins
  HUD();
}

int main() {
  srand(time(0));
  //Main menu
  printf(COLOR_BOLD "Main Menu\n" COLOR_OFF);
  printf("[1] - Start Game\n");
  printf("[2] - Credits\n");
  printf("[3] - Quit\n");
  printf("Please input 1, 2, or 3\n");
  scanf("%d", &input);

  if (input == 1) {
    // Start Game
    // Input story in function
    story();
  } 
  else if (input == 2) {
    // Credits
    printf(COLOR_BOLD "This game was brought to you by:\n" COLOR_OFF);
    printf("Kun Wei, Steven Keohavong, Jewel Shaw, Ethan Clark");

  } else if (input == 3) {
    // Quit Game
    printf("Game exited");
    return 0;
  } 
}

//Random Number Generator
  /*
  randomN = rand()%(10 - 0 + 1) + 0;
  printf("%d", randomN);
  
  if (randomN == 1) {
    printf("waffle");
  } else {
    printf("not waffle");
  }



  rand() %(max-min+1)+min
  */