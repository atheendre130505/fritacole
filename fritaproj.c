#include <stdio.h>

int frita_id(){
  static int f_id = -1;
  f_id++;
  return f_id;
}

typedef struct _fritacole {
  int frita_id;
  char name[100];
  float height;
} fritacole;

typedef struct foul {
  int frita_id;
  char name[100];
} fouls;

typedef struct points {
int frita_id;
char name[100];
} points;

typedef struct _team {
  char name[100];
  int numplayers;
  fritacole players[20];
  fouls fouls[20];
  points points[20];
  int numfouls;
  int numpoints;
} team;

typedef struct _game {
  int id;
  team teams[2];
} game;



void inpfricta(fritacole *a) {
  printf("Enter the name of the fritacole\n");
  scanf("%s", a->name);
  printf("Enter the height of the fritacole\n");
  scanf("%f", &a->height);
}



void inpteam(team *a, int numplayers) {
  a->numplayers = numplayers;
  printf("Enter the name of the team\n");
  scanf("%s", a->name);
  for (int i = 0; i < a->numplayers; i++) {
    a->players[i].frita_id=frita_id();
    inpfricta(&a->players[i]);
  }
}


void inpgame(game *a) {
  printf("please enter game number: \n");
  scanf("%d",&a->id);
  int numplayers;
  printf("Enter the number of players for each team\n");
  scanf("%d", &numplayers);
  for (int i = 0; i < 2; i++) {
    inpteam(&a->teams[i], numplayers);
  }
}



int inpfouls(game *a,int j) {
  scanf("%d", &a->teams[j].numfouls);
  for (int i = 0; i < a->teams[j].numfouls; i++) {
    printf("Enter the id of the fritacole who fouled: \n");
    scanf("%d",&a->teams[j].fouls[i].frita_id);
  }
  return a->teams[j].numfouls;
}


int inppoints(game *a,int j) {
  scanf("%d", &a->teams[j].numpoints);
  for (int i = 0; i < a->teams[j].numpoints; i++) {
    printf("Enter the id of the fritacole who scored: \n");
    scanf("%d", &a->teams[j].points[i].frita_id);
  }
  return a->teams[j].numpoints;
}



float sumheight(game *a, int j) {
  float hsum = 0;
  for (int i = 0;i<a->teams[j].numplayers; i++) {
    hsum += a->teams[j].players[i].height;
  }
  return hsum;
}



void verifyadvantage(game *a) {
  float team1height = sumheight(a, 0);
  float team2height = sumheight(a, 1);
  (team1height > team2height)   ? printf("team one has the advantage\n")
  : (team1height < team2height) ? printf("team two has the advantage\n")
                                : printf("both teams possess equal advantage\n");
  ;
}


void verify_win(game *a) {
  printf("team 1 data: \n");
  for(int i=0;i<a->teams[0].numplayers;i++){
    printf("name: %s ,id: %d\n",a->teams[0].players[i].name,a->teams[0].players[i].frita_id);
  }
  printf("team 2 data: \n");
  for(int i=0;i<a->teams[0].numplayers;i++){
    printf("name: %s ,id: %d\n",a->teams[1].players[i].name,a->teams[1].players[i].frita_id);
  }

  printf("\n\nenter the points for team %s: \n", a->teams[0].name);
  int team1points = inppoints(a,0);
  printf("enter the points for team %s: \n", a->teams[1].name);
  int team2points = inppoints(a,1);
  printf("enter the fouls for team %s: \n", a->teams[0].name);
  int team1fouls = inpfouls(a,0);
  printf("enter the fouls for team %s: \n", a->teams[1].name);
  int team2fouls = inpfouls(a,1);
  verifyadvantage(a);
  (team1points>team2points)?printf("team one has won the game\n"):(team1points<team2points)?printf("team 2 has won the game\n"):
  (team1fouls>team2fouls)?printf("both teams have equal points but since team 1 has more fouls team 2 won\n"):(team1fouls<team2fouls)?
  printf("both teams have equal points but since team 2 scored more fouls team 1 won:\n"):printf("its a draw\n");
}



void output(game *a){
  printf("\nGAME STATS: \n\n");
  printf("The number of fouls scored by each team are: \n");
  printf("Team 1: %d\n",a->teams[0].numfouls);
  for(int i=0;i<a->teams[0].numfouls;i++){
    printf("name: %s, id: %d\n",a->teams[0].players[a->teams[0].fouls[i].frita_id].name,a->teams[0].fouls[i].frita_id);
  }
  printf("Team 2: %d\n",a->teams[1].numfouls);
  for(int i=0;i<a->teams[1].numfouls;i++){
    printf("name: %s, id: %d\n",a->teams[1].players[a->teams[1].fouls[i].frita_id].name,a->teams[1].fouls[i].frita_id);
  }
  printf("\nThe number of points scored by each team are: \n");
  printf("\nTeam 1: %d\n",a->teams[0].numpoints);
  for(int i=0;i<a->teams[0].numpoints;i++){
    printf("name: %s, id: %d\n",a->teams[0].players[a->teams[0].points[i].frita_id].name,a->teams[0].points[i].frita_id);
  }
  printf("\nTeam 2: %d\n",a->teams[1].numpoints);
  for(int i=0;i<a->teams[1].numpoints;i++){
    printf("name: %s, id: %d \n",a->teams[1].players[a->teams[1].points[i].frita_id].name,a->teams[1].points[i].frita_id);
  }

}

int main(){
  game a;
  inpgame(&a);
  verify_win(&a);
  output(&a);
}