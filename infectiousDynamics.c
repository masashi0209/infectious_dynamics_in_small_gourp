#include <stdio.h>
#include <stdlib.h>

#define DELTA 0.01
#define ONE_T 100

#define MEMBER 100
#define FREQ 0.01

#define STATES 7

void hapening_in_a_day(int state[], int stateCount[], double beta, double gamma, double rho, double sigma, double eta)
{
	int t, i, j, stateCases;
	double rnd, rnd2, total_rate_infection;
  
	for(t=0; t<ONE_T; t++){
		for(i=0; i<MEMBER; i++){
			stateCases=state[i];
			rnd=(double)rand() / RAND_MAX;
			switch(stateCases){
			  case 0: //susceptibles
				//infection rate
				total_rate_infection=0.0;
				for(j=3; j<STATES; j++){ // states 0 (S), 1 (R) and 2 (E) do not have infectivity
					total_rate_infection+=stateCount[j];
				}
				total_rate_infection=total_rate_infection*beta;
          
				if(rnd<total_rate_infection){
					state[i]=2;
					stateCount[2]++;
				}
				break;
			  case 1: // recovered, do nothing
				break;
			  case 2: // exposed
				if(rnd<sigma){
					state[i]=3;
					stateCount[2]--;
					stateCount[3]++;
				}
				break;
			  case 3: // Ia1
				if(rnd<rho){
					state[i]=4;
					stateCount[3]--;
					stateCount[4]++;
				}
				break;
			case 4: // Ia2
				if(rnd<rho){ // it will be Is
					rnd2=(double)rand() / RAND_MAX;
					if(rnd2<eta){ // it will be Is with symptom
						state[i]=5;
						stateCount[4]--;
						stateCount[5]++;
					} else {
						state[i]=6;
						stateCount[4]--;
						stateCount[6]++;
					}
				}
				break;
			  case 5: // Iss
				if(rnd<gamma){
					state[i]=1; // it becomes recovered:1
					stateCount[5]--;
					stateCount[1]++;
				}
				break;
			  case 6: // Isa
				if(rnd<gamma){
					state[i]=1; // it becomes recovered:1
					stateCount[6]--;
					stateCount[1]++;
				}
				break;
			} //switch
		} //i
  } //t
}

int testing(int state[], double sensitivities[]){
  int i, st, indecteds=0;
  double rnd;
 
  for(i=0; i<MEMBER; i++){
    rnd=(double)rand() / RAND_MAX;
    st=state[i];
    if(rnd<sensitivities[st]){
      indecteds+=1;
    }
  }
  return indecteds;
}

int main(){
  int i, day, testDay, detecteds, bp, initialInfecteds;
  int state[MEMBER], stateCount[STATES];
  double sigma, rho, gamma, beta, eta;
  double specificity, sensitivities[STATES];

	specificity=1.0; // no false positive
	
	//sensitivity for PCR testing (multiply 0.7 to following values for antigen test)
	sensitivities[0]=1-specificity; // S
	sensitivities[1]=1-specificity; // R
	sensitivities[2]=1-specificity; // E
	sensitivities[3]=0.33; //Ia1
	sensitivities[4]=0.62; //Ia2
	sensitivities[5]=0.8; //Iss
	sensitivities[6]=0.8; //Isa 
  
	/* parameters */
	beta=FREQ*DELTA*4.0/9.0; // R0=4
	sigma=DELTA*1.0/3.0; //Exposed lasts 3 days
	rho=DELTA*1.0/1.0; //Ia1 and Ia2 last 1 day
	gamma=DELTA*1.0/7.0; // recovery in 7 days
	eta=0.54;
	
	testDay=2; // test is carried out at day 2 after the first infection
	bp=0; // checker for detection of infecteds
	
	// initial condition of states
	for(i=0; i<MEMBER; i++) state[i]=0; //clear array
	stateCount[0]=MEMBER; //all are susceptible 
	for(i=1; i<STATES; i++) stateCount[i]=0; // number of other status is 0
	
	// an infected individual invades into the population
	initialInfecteds = 1; //starting with one infected individual whose state is E
	for(i=0; i<initialInfecteds; i++){
		state[i]=2; // set it to E
		stateCount[2]++; // increase the number of E by 1
		stateCount[0]--; // decrease S by 1
	} // i
	
	//set random seed
	srand(1);
	
	for(day=0; day<14; day++){ //max simulation time is 14 days
		if(stateCount[5]>0){ // checking for symptom is carried out every day
			printf("infected is detected by checking symptom at day %d after the first infection\n", day);
			printf("number of detecteds is %d\n", stateCount[5]);
			printf("undetected infecteds remining in the team as E is %d, as Ia and Isa is %d\n", stateCount[2], stateCount[3]+stateCount[4]+stateCount[6]);
			bp=1;  //if infected individuals are detected, set bp=1
			break; //breaks day
		} //if
		
		if(day==testDay){
			detecteds=testing(state, sensitivities);
		}
		if(detecteds>0){
			printf("infected is detected by testing at day %d after the first infection\n", day);
			printf("number of detecteds is %d\n", detecteds);
			printf("undetected infecteds remining in the team as E is %d, as Ia and Isa is %d\n", stateCount[2], stateCount[3]+stateCount[4]+stateCount[6]-detecteds);
			bp=1;  //if infected individuals are detected, set bp=1
			break; //breaks day
		}
		//solve the dynamics for one day
		hapening_in_a_day(state, stateCount, beta, gamma, rho, sigma, eta);
	} // day
	if(bp==0) printf("no infected inviduals are detected within 14 days of simulation\n");

	return 0;
}
