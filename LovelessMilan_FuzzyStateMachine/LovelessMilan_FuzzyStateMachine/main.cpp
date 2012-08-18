// main.cpp
////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include "CORE\CORE.AI.h"
#include "CORE\CORE.AI.FuzzyStateMachine.h"

FUZZY g_zEnemyNear = 0.0;

FUZZY StandingToStanding(FuzzyStateMachine* pMachine, char* name1, char* name2) {
	return 1.0;
}

FUZZY WalkingToWalking(FuzzyStateMachine* pMachine, char* name1, char* name2) {
	return 1.0;
}

FUZZY RunningToRunning(FuzzyStateMachine* pMachine, char* name1, char* name2) {
	return 1.0;
}

FUZZY FlyingToFlying(FuzzyStateMachine* pMachine, char* name1, char* name2) {
	return 2.0;
}

FUZZY StandingToWalking(FuzzyStateMachine* pMachine, char* name1, char* name2) {
	return 0.8;
}

FUZZY WalkingToStanding(FuzzyStateMachine* pMachine, char* name1, char* name2) {
	return 0.2;
}

FUZZY WalkingToRunning(FuzzyStateMachine* pMachine, char* name1, char* name2) {
	return g_zEnemyNear;
}

FUZZY RunningToWalking(FuzzyStateMachine* pMachine, char* name1, char* name2) {
	return 0.1;
}

FUZZY RunningToFlying(FuzzyStateMachine* pMachine, char* name1, char* name2) {
	return 0.653;
}

FUZZY FlyingToRunning(FuzzyStateMachine* pMachine, char* name1, char* name2) {
	return 0.8;
}


void main() {

	FuzzyStateMachine machine;

	machine.AddNode("Standing", NULL);
	machine.AddNode("Walking", NULL);
	machine.AddNode("Running", NULL);
	machine.AddNode("Flying", NULL);

	machine.AddLink("Standing", "Walking", StandingToWalking);
	machine.AddLink("Standing", "Standing", StandingToStanding);
	machine.AddLink("Walking", "Standing", WalkingToStanding);
	machine.AddLink("Walking", "Walking", WalkingToWalking);
	machine.AddLink("Walking", "Running", WalkingToRunning);
	machine.AddLink("Running", "Walking", RunningToWalking);
	machine.AddLink("Running", "Running", RunningToRunning);
	machine.AddLink("Running", "Flying", RunningToFlying);
	machine.AddLink("Flying", "Running", FlyingToRunning);
	machine.AddLink("Flying", "Flying", FlyingToFlying);

	while(true) {

		for(int n = 0; n < 5; n++) {
			machine.RunOneStep();
			printf("Character is: %s\n", machine.GetCurrentStateName());
		}

		printf("\nIs the enemy near? [0..1]: ");
		scanf("%f", &g_zEnemyNear);

	}

	system("pause");
}