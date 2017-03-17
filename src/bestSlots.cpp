
//#include <string>

#include <algorithm>//next_permutation
#include <functional>//bind,function

#include "partition.hpp"
#include "bestSlots.hpp"

using namespace std;



BestSlots::BestSlots(const vector<vector<int> >& w){
	weights = w;
}

void BestSlots::setCutWeek(const vector<int>& cw){
	cutWeek = cw;
}

void BestSlots::setSlots(const vector<int>& ss){
	studentSlots = ss;
}

void BestSlots::setWeightPauses(const vector<int>& swp){
	weightPauses = swp;
}

vector<vector<int> >& BestSlots::getWeights(){
	return weights;
}

vector<int>& BestSlots::getCutWeek(){
	return cutWeek;
}

vector<int>& BestSlots::getSlots(){
	return studentSlots;
}

vector<int>& BestSlots::getWeightPauses(){
	return weightPauses;
}

int BestSlots::computeSum(const vector<int>& pauses)
/*compute sum of weights for one session for the repartition sessionRep, the pauses repartition pauses, going from index beginIndex; return sum if combination possible, -1000 else*/
{
	int currentIndex = beginIndex + pauses[0]; //index of slot for first student
	int intermedPauses = 0; // nb of pauses in the middle session 
	int sum = 0;
	int currentWeight;
	
	for (size_t i(0);i<studentSlots.size();i++)//for each student
	{
		for (int j(0);j<studentSlots[sessionRep[i]];j++)//for each slot of this student
			{
				currentWeight = weights[sessionRep[i]][currentIndex];
				if (currentWeight == -2)//impossibility of student i
					return -1000;
				sum += currentWeight;//weight of slot
				currentIndex++;
			}
		intermedPauses += pauses[i+1];
		currentIndex += pauses[i+1];
	}

	sum += weightPauses[intermedPauses-pauses[pauses.size()-1]];//add weight of pauses in the middle of the session
	return sum;
}

vector<int> BestSlots::minimalPauses(const int& nPauses){
	/* inside one session: go through all possiblities to place pauses (nb of students +1 positions), return optimal one*/
	vector<int> solution(1,0);
	vector<int> pauses(studentSlots.size()+1,0);
	
	int sum = -1000;
	if (nPauses == 0)
	{
		sum = computeSum(pauses);
		
	}
	else{
		function<int(const vector<int>&)> fCompute = bind(&BestSlots::computeSum, this, placeholders::_1);// create function from member computeSum
		Partition p(nPauses,studentSlots.size()+1);
		p.scrollFunction(fCompute);
	}

	solution[0] = sum;
	solution.push_back(pauses[0]*(-1));
	for (size_t i(0);i<studentSlots.size();i++){
		for (int j(0);j < studentSlots[sessionRep[i]];j++)
		{
			solution.push_back(sessionRep[i]);// for all slots
		}
		solution.push_back(pauses[i]*(-1)); //negative
	}
	return solution; // session local solution pause,pause-p1,p1,p1-pause-p2-pause-p3-pause...
}

vector<int> BestSlots::weightForPerm(const vector<int>& perm){//perm[i]: rank of student having the ith class
	int currentIndex=0;
	//int precSessionIndex=0;
	int sessionNumber=0;
	vector<int> sessionRep(0);
	vector<int> sessionSol(0);
	vector<int> globalSol(0);
	vector<int> noSol(1,-1000); // returned value in case of non valid permutation
	int pauses; //nb of pauses slots in a given session

	//int sum = 0;
	 for(size_t i(0);i<studentSlots.size();i++){
		//we try to insert the slots for student at rank perm[i]
		//int max = 0;
		//TO DO???
		if (currentIndex+studentSlots[perm[i]] >= cutWeek[sessionNumber]
		   || weights[perm[i]][currentIndex]==-2)
		{
			sessionNumber++; // student will be at next session
			if (sessionNumber >= cutWeek.size())
				return noSol; // this permutation does not lead to a possible repartition
			currentIndex = cutWeek[sessionNumber-1];
			if (currentIndex+studentSlots[perm[i]] >= cutWeek[cutWeek.size()-1])
				return noSol;
			//arrange session nb sessionNumber-1 with possible pauses
			if (sessionNumber>1){
				pauses = cutWeek[sessionNumber-1]-cutWeek[sessionNumber-2];
				beginIndex = cutWeek[sessionNumber-2];
			}
			else{
				pauses = cutWeek[0];
				beginIndex = 0;
			}
			if (sessionRep.size()==0)
				return noSol; 
			sessionSol = minimalPauses(pauses);
			globalSol.insert(globalSol.end(),sessionSol.begin()+1,sessionSol.end());
			globalSol[0] += sessionSol[0];
			sessionRep.clear();
		}
		sessionRep.push_back(perm[i]);
	}
	return globalSol;

}//std::next_permutation(myints,myints+3)
	
	
ostream& operator<<(ostream & flow, vector<vector<int> > weights){
	int n1 = weights.size();
	if (n1 == 0)
		flow<<"Empty matrix"<<endl;
	else{
		int n2 = weights[0].size();
		flow<<"Size:"<<n1<<"x"<<n2<<endl;
		for (int i(0);i<n1; i++)
			{
			for (int j(0);j<n2; j++){
				flow<<setw(3)<<weights[i][j];
			}
			flow<<endl;
		}
	}
	return flow;
}


ostream& operator<<(ostream & flow, BestSlots bs){
	flow<<"Printing weights:"<<endl;
	flow<<bs.getWeights();
	flow<<"Printing students slots:"<<endl;
	flow<<bs.getSlots();
	flow<<"Printing week schedule:"<<endl;
	flow<<bs.getCutWeek();
	flow<<"Printing weight for pauses:"<<endl;
	flow<<bs.getWeightPauses();
	return flow;
}


