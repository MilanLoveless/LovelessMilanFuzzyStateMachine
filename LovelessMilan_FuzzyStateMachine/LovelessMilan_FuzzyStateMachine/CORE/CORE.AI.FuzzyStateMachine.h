// CORE.AI.FuzzyStateMachine.h
////////////////////////////////////////////////////////

#pragma once
#include <vector>
using namespace std;

#include "CORE.AI.h"

class FuzzyStateMachine;
class NODE;
class LINK;

typedef FUZZY (*TRANSITION_EVALUATOR)(FuzzyStateMachine* pMachine, char* name1, char* name2);

class LINK {
public:
	TRANSITION_EVALUATOR pEvalFunc;
	NODE *pDestination;
	FUZZY zRecommendation;
};

class NODE {
public:
	NODE();
	void AddLink(LINK *pLink);
	NODE* RunOneStep();

	char *name;
	FuzzyStateMachine *subMachine;
	vector<LINK*> _Links;
};

class FuzzyStateMachine {
public:
	FuzzyStateMachine();

	void AddNode(char* name, FuzzyStateMachine* subMachine);
	void AddLink(char* name1, char *name2, TRANSITION_EVALUATOR pEvalFunc);

	NODE* FindNode(char* name);

	char* GetCurrentStateName();

	void RunOneStep();

private:
	NODE* pCurrentNode;
	vector<NODE*> _Nodes;
};