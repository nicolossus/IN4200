//=============================================================================
void update(int N, int E, double f, int T, int X, int *states, int *timer, int *person_i, int *person_j)
{
  /*
  Simulate all daily interactions and update the states (healthy, infected,
  infected but in isolation, immune) of all people. The states are assigned
  integer values (2, 1, 0, -1) respectively.

  INPUTS
  ------
  N - number of nodes (people)
  E - number of edges (interactions)
  f - the probability of being infected
  T - number of days infected interacts with others
  X - number of days to become immune after isolation
  states - array of length N storing every persons state
  timer - array of length N storing the number of days infected
  person_i - array of length E
  person_j - array of length E

  The person-person interactions are stored by the correspondence between
  person_i and person_j
  */

  // Once infected, a person cannot infect others before the following day.
  // In order to ensure that no newly-infected transmits the disease,
  // possible changes in the state are stored in a temporary states array
  int *states_tmp;
  states_tmp = (int*)calloc(N, sizeof(*states_tmp));

  // Declare variable for assigning random number
  double r;

  // Simulate daily interactions and check if someone becomes infected
  for (int k=0; k<E; k++){
    // Check whether:
    // 1. The states of person_i and person_j are different
    // 2. The state of person_i is not 'infected but in isolation' or 'immune'
    // 3. The state of person_j is not 'infected but in isolation' or 'immune'
    if ((states[person_i[k]] !=states[person_j[k]]) && !(states[person_i[k]] <= 0) && !(states[person_j[k]] <= 0)) {
      // If True, either person_i or person_j is infected
      // Draw a random number unif(0, 1)
      double r = (double)rand() / (double)RAND_MAX;
      // Check if the interaction results in a transmission of the disease
      // according to the prescribed probability f
      if (r<f){
        // Infection! Update the temporary state
        states_tmp[person_i[k]] = states_tmp[person_j[k]] = 1;
      }
    }
  }

 // Update states and timer
 for (int l=0; l<N; l++){
   // If state is infected, add 1 to timer
   if (states[l] == 1){
     timer[l] += 1;
   }

   // If state is infected but in isolation, add 1 to timer
   if (states[l] == 0){
     timer[l] += 1;
   }

   // If the state is changed to infected due to the daily interaction
   if (states_tmp[l] != 0){
     states[l] = 1;
   }

   // If T days have passed with infection, change state to infected
   // but in isolation
   if (timer[l] == T){
     states[l] = 0;
   }

   // If X days in isolation have passed, change state to immune
   if (timer[l] == T+X){
     states[l] = -1;
   }
 }

 free(states_tmp);
}
//=============================================================================
