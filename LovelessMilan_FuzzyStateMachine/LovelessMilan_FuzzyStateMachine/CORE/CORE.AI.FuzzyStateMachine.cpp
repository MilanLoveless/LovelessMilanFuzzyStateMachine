// CORE.AI.FuzzyStateMachine.cpp
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include "CORE.AI.h"
// CORE.AI.FuzzyStateMachine.cpp
///////////////////////////////////////////////////////////////////////////////////

#include "CORE.AI.FuzzyStateMachine.h"

NODE::NODE() {
	name = NULL;
	subMachine = NULL;
}

void NODE::AddLink(LINK *pLink) {
	_Links.push_back(pLink);
}

NODE* NODE::RunOneStep() {
	// Run the submachine
	if(this->subMachine != NULL) {
		this->subMachine->RunOneStep();
	}

	// Evaluate all of the transitions
	FUZZY zSum = 0.0;
	for(int n = 0; n < this->_Links.size(); n++) {
		LINK* pLink = this->_Links[n];
		pLink->zRecommendation = pLink->pEvalFunc(NULL, this->name, pLink->pDestination->name);
		// Compute running sum
		zSum += pLink->zRecommendation;
	}

	// Divide off the sum, thereby normalizing the link recommendations
	for(int m = 0; m < this->_Links.size(); m++) {
		LINK* pLink = this->_Links[m];
		pLink->zRecommendation /= zSum;
	}

	// Pick which transition to follow
	float pick = (rand()%1000) / 1000.0;
	float current = 0.0;
	for(int l = 0; l < this->_Links.size(); l++) {
		LINK* pLink = this->_Links[l];
		current += pLink->zRecommendation;
		if(pick <= current) {
			return pLink->pDestination;
		}
	}

}

FuzzyStateMachine::FuzzyStateMachine() {
	this->pCurrentNode = NULL;
}

void FuzzyStateMachine::AddNode(char* name, FuzzyStateMachine* subMachine) {
	NODE* pNode = new NODE();
	pNode->name = name;
	pNode->subMachine = subMachine;
	_Nodes.push_back(pNode);
	// Starting state is set to the first node they add
	if(this->pCurrentNode == NULL) {
		this->pCurrentNode = pNode;
	}
}

NODE* FuzzyStateMachine::FindNode(char* name) {
	for(int n = 0; n < _Nodes.size(); n++) {
		NODE* pNode = _Nodes[n];
		if(strcmp(pNode->name, name)==0) {
			return pNode;
		}
	}
	return NULL;
}

void FuzzyStateMachine::AddLink(char* name1, char *name2, TRANSITION_EVALUATOR pEvalFunc) {
	NODE* pNode1 = FindNode(name1);
	NODE* pNode2 = FindNode(name2);

	LINK* pLink = new LINK();
	pLink->pDestination = pNode2;
	pLink->pEvalFunc = pEvalFunc;

	pNode1->AddLink(pLink);
}

char* FuzzyStateMachine::GetCurrentStateName() {
	if(this->pCurrentNode != NULL) {
		return this->pCurrentNode->name;
	}
	return "";
}

void FuzzyStateMachine::RunOneStep() {
	if(this->pCurrentNode != NULL) {
		this->pCurrentNode = this->pCurrentNode->RunOneStep();
	}
}