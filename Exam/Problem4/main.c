#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void read_graph_from_file(char*, int*, int*, int**, int**, int**, int);
void printvec(int*, int);
void update_state(int, int, double, int, int, int*, int*, int*, int*);

//=============================================================================
int main(int argc, char *argv[]){

  srand((long)time(NULL));
  int *person_i;
  int *person_j;
  int *states;
  int *timer;
  int N, N_links;

  int NIS = 2;  // Number of Initial Sick
  double f = 0.1;  // Infection threshold
  int T = 14;    // Days before infected are removed from interactions
  int X = 6;    // Days to recover after removal

  int ST = 70;  // Simulation TIme

  read_graph_from_file("./graph.txt", &N, &N_links, &states, &person_i, &person_j, NIS);

  timer = (int*)calloc(N, sizeof(*timer));  // count time infected

  for (int i=0; i<N; i++){
    if (states[i] == 1){
      timer[i] += 1;
    }
  }

  // PRINT STUFF
  printf("people = %d\ninteractions = %d\n", N, N_links);

  printf("person_i =\n");
  printvec(person_i, N_links);

  printf("person_j =\n");
  printvec(person_j, N_links);

  printf("initial states = ");
  printvec(states, N);

  printf("initial timer = ");
  printvec(timer, N);

  // UPDATE
  for (size_t i=0; i<ST; i++){
    printf("DAY %lu\n", i+1);
    update_state(N, N_links, f, X, T, states, person_i, person_j, timer);
    printf("states = ");
    printvec(states, N);
    printf("timer = ");
    printvec(timer, N);
  }


  free(person_i);
  free(person_j);
  free(states);

  return 0;
}
//=============================================================================

/*
//=============================================================================
void update_state(int N, int N_links, double f, int X, int T, int *states, int *person_i, int *person_j, int *timer)
{
  int *states_tmp;
  states_tmp = (int*)calloc(N, sizeof(*states_tmp)); // Store
  double r;
  // Simulate daily interactions and check who becomes infected
  for (int k=0; k<N_links; k++){
    if ((states[person_i[k]] !=states[person_j[k]]) && !(states[person_i[k]] <= 0) && !(states[person_j[k]] <= 0)) {
      r = (double)rand() / (double)RAND_MAX;  // Random number unif(0,1)
      if (r<f){
        states_tmp[person_i[k]] = states_tmp[person_j[k]] = 1;
      }
    }
    free(states_tmp);
  }

 //
 for (int l=0; l<N; l++){
   if (states[l] == 1){
     timer[l] += 1;
   }
   if (states[l] == 0){
     timer[l] += 1;
   }
   if (states_tmp[l] != 0){
     states[l] = 1;
   }
   if (timer[l] == T){
     states[l] = 0;   // Infected but in isolation
   }
   if (timer[l] == T+X){
     states[l] = -1;  // Immune
   }
 }
}
//=============================================================================
*/


//=============================================================================
void update_state(int N, int N_links, double f, int X, int T, int *states, int *person_i, int *person_j, int *timer)
{
  int *states_tmp;
  states_tmp = (int*)calloc(N, sizeof(*states_tmp));
  double r;
  // Check who becomes infected
  for (int k=0; k<N_links; k++){
    //if ((states[person_i[k]] !=states[person_j[k]]) && (states[person_i[k]] != 0)  && (states[person_j[k]] != 0) && (states[person_i[k]] != -1)  && (states[person_j[k]] != -1)){
      if ((states[person_i[k]] !=states[person_j[k]]) && !(states[person_i[k]] <= 0) && !(states[person_j[k]] <= 0)){
      r = (double)rand() / (double)RAND_MAX;  // Random number unif(0,1)
      //printf("r = %f\n",r);
      if (r<f){
        printf("INFECTION! Interaction between person %d with state %d and person %d with state %d\n",person_i[k], states[person_i[k]], person_j[k], states[person_j[k]]);
        states_tmp[person_i[k]] = states_tmp[person_j[k]] = 1;
      }
    }
  }

 //
 for (int l=0; l<N; l++){
   if (states[l] == 0){
     timer[l] += 1;
   }

   if (states[l] == 0){
     timer[l] += 1;
   }


   if (states_tmp[l] != 0){
     states[l] = 1;
   }
   if (timer[l] == T){
     states[l] = 0;   // Infected, but removed
   }
   if (timer[l] == T+X){
     states[l] = -1;  // Immune
   }
 }
}
//=============================================================================


//=============================================================================
void read_graph_from_file(char *filename, int *N, int *N_links, int **states, int **person_i, int **person_j, int NIS)
{
	FILE *datafile;
	int i, j;

	datafile = fopen(filename, "r");

	if (datafile == NULL) {
		printf("Failure to open file %s\n", filename);
		exit(0);
	}

	fscanf(datafile, "%*s %*s %d %*s %d \n", &*N, &*N_links);  // Read 1st line
	fscanf(datafile, "%*[^\n]\n");                   // Skip 2nd line

	*person_i = (int*)calloc((*N_links), sizeof(*person_i));
	*person_j = (int*)calloc((*N_links), sizeof(*person_j));

	int N_links_valid = 0;
	for(size_t k=0; k<(*N_links); k++) {
		fscanf(datafile, "%d %d", &j, &i);
		if ((i != j) && (i <= (*N)) && (j <= (*N))) { // Exclude self- and illegal links
			(*person_i)[N_links_valid] = i;
			(*person_j)[N_links_valid] = j;
			N_links_valid++;  // count valid links
		}
	}

	(*N_links) = N_links_valid;  // Set N_links equal to valid links only

  *states = (int*)calloc((*N), sizeof(*states));
  for (size_t i=0; i<(*N); i++){
    (*states)[i] = 2;    // Healthy state
  }

  int sick_idx;
  //srand(time(NULL));
  int count_sick = 0;

  while (count_sick < NIS){
    sick_idx = rand()%(*N);
    if ((*states)[sick_idx] != 1){
      (*states)[sick_idx] = 1;  // Sick state
      count_sick++;
    }
  }

	fclose(datafile);
}
//=============================================================================


//=============================================================================
void printvec(int *v, int n)
{
	printf("| ");
	for (size_t i = 0; i < n; ++i) {
		printf("%d ", v[i]);
	}
	printf("|\n");
}
//=============================================================================
