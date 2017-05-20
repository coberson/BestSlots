
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
	bestSol = vector<int> (cutWeek[cutWeek.size()-1]+1,0);
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
/*compute sum of weights for one session for the partition sessionRep, the pauses partition pauses, going from index beginIndex; return sum if combination possible, -1000 else*/
{
	int currentIndex = beginIndex + pauses[0]; //index of slot for first student
	//cout << "CI" << currentIndex << endl;
	int intermedPauses = 0; // nb of pauses in the middle session 
	int sum = 0;
	int currentWeight;
	
	for (size_t i(0);i<sessionRep.size();i++)//for each student
	{
		for (int j(0);j<studentSlots[sessionRep[i]];j++)//for each slot of this student
			{
				currentWeight = weights[sessionRep[i]][currentIndex];
				//cout << currentIndex << ": " << sessionRep[i] << "-" << currentWeight << endl;
				if (currentWeight == -2)//impossibility of student i
					return -1000;
				sum += currentWeight;//weight of slot
				currentIndex++;
			}
		intermedPauses += pauses[i+1];
		currentIndex += pauses[i+1];
	}

	sum += weightPauses[intermedPauses-pauses[pauses.size()-1]];//add weight of pauses in the middle of the session
	//cout << sum << endl;
	return sum;
}

vector<int> BestSlots::minimalPauses(const int& nPauses){
	/* inside one session: go through all possibilities to place pauses (nb of students +1 positions), return optimal one*/
	vector<int> solution(1,0);
	//vector<int> pauses(studentSlots.size()+1,0);
	int nbSInS = sessionRep.size();
	vector<int> pauses(nbSInS + 1,0);
	
	int sum = -1000;
	if (nPauses == 0)
	{
		sum = computeSum(pauses);
		
	}
	else{
		function<int(const vector<int>&)> fCompute = bind(&BestSlots::computeSum, this, placeholders::_1);// create function from member computeSum
		cout << nPauses << ":" << nbSInS << ";" << endl;
		Partition p(nPauses,nbSInS + 1);
		p.scrollFunction(fCompute); // will compute maximal weight for partition family
		//updating sum and pauses vector (19.5)
		vector<int> solPar = p.getMaximalPartition();
		cout << "\t" << solPar << endl;
		sum = solPar[0];
		for (int i(0);i < nbSInS + 1;i++){
			pauses[i] = solPar[i+1];
		} 
	}

	solution[0] = sum;
	for (int i(0); i < nbSInS ;i++){
		for (int j(0);j < pauses[i];j++)
			solution.push_back(0); // 0 for every pause slot
		for (int j(0);j < studentSlots[sessionRep[i]];j++)
		{
			solution.push_back(sessionRep[i]+1);// for all slots (1 for student #0)
		}	
	}
	for (int i(0);i<pauses[nbSInS];i++)
		solution.push_back(0); // 0 for every pause slot
	//solution.push_back(pauses[nbSInS]*(-1)); //negative for the pauses
	cout << "Sol" << solution << endl;
	return solution; // session local solution with weight first and negative pauses between slots
}

vector<int> BestSlots::weightForPerm(const vector<int>& perm){
	//give the global optimized solution for a given order of students:
	//perm[i]: rank of student having the ith class
	int currentIndex=0;
	//int precSessionIndex=0;
	int sessionNumber=0;
	int sessionUsedSlots=0; //19.5
	//vector<int> sessionRep(0); //??????or member?
	sessionRep.clear();
	vector<int> sessionSol(0);
	vector<int> globalSol(1,0);
	vector<int> noSol(1,-1000); // returned value in case of non valid permutation
	int pauses; //nb of pauses slots in a given session
	
	//int sum = 0;
	 for(size_t i(0);i<studentSlots.size();i++){
		//we try to insert the slots for student at rank perm[i]
		if (currentIndex+studentSlots[perm[i]] >= cutWeek[sessionNumber]
		   || weights[perm[i]][currentIndex]==-2 ) // or we have seen the last student
		{
			sessionNumber++; // student will be at next session
			//cout<<"Changing session!" << sessionNumber << endl;
			if (sessionNumber >= (int) cutWeek.size())
				return noSol; // this permutation does not lead to a possible repartition
			currentIndex = cutWeek[sessionNumber-1];
			if (currentIndex+studentSlots[perm[i]] >= cutWeek[cutWeek.size()-1])
				return noSol;
			//arrange precedent session with possible pauses
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
			pauses = pauses - sessionUsedSlots; //19.5
			sessionSol = minimalPauses(pauses);
			//cout << sessionSol << endl;
			globalSol.insert(globalSol.end(),sessionSol.begin()+1,sessionSol.end());
			globalSol[0] += sessionSol[0];
			sessionRep.clear();
			sessionUsedSlots = 0;
		}
		currentIndex += studentSlots[perm[i]];
		sessionRep.push_back(perm[i]);
		sessionUsedSlots += studentSlots[perm[i]];//19.5
	}
	//for last session 
	//cout << "Last session!" << sessionNumber << endl;
	if (sessionNumber > 0){
		beginIndex = cutWeek[sessionNumber-1];
		pauses = cutWeek[sessionNumber]-cutWeek[sessionNumber-1] - sessionUsedSlots;
	}
	else{
		beginIndex = 0;
		pauses = cutWeek[sessionNumber] - sessionUsedSlots;
	}
	sessionSol = minimalPauses(pauses);
	globalSol.insert(globalSol.end(),sessionSol.begin()+1,sessionSol.end());
	globalSol[0] += sessionSol[0];
	
	return globalSol;

}//std::next_permutation(myints,myints+3)
	
void BestSlots::setBestSol(std::vector<int> sol){
	if (sol[0] > bestSol[0])
		bestSol = sol; 
}
	
vector<int> BestSlots::getBestSol(){
	return bestSol;
}

std::vector<int> BestSlots::explore(){
	int nbStudents = studentSlots.size();
	cout << getBestSol() << endl;
	vector<int> perm (nbStudents,0);
	for(int i(0);i<nbStudents;i++){
		perm[i]=i;
	}
	setBestSol(weightForPerm(perm));
	cout << getBestSol() << endl;
	while (next_permutation(perm.begin(),perm.end())){
		setBestSol(weightForPerm(perm));
		cout << getBestSol() << endl;
	}
	return BestSlots::getBestSol();
} // 19.5

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
	flow<<"Solution:"<<endl;
	flow<<bs.explore();
	return flow;
}


