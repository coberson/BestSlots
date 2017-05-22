#include "partition.hpp"
using namespace std;

int display(const vector<int>& v){
	cout<< v;
	return 0;
}

ostream& operator<<(ostream & flow, vector<int> vec){
	int n1 = vec.size();
	if (n1 == 0)
		flow<<"Empty vector"<<endl;
	else{
		for (int i(0);i<n1; i++)
		{
			flow<<setw(3)<<vec[i];
		}
		flow<<endl;
	}
	return flow;
}


Partition::Partition(const int& N,const int& k){
	this->N=N;
	this->k=k;
	currentPartition = vector<int> (k,0);
	currentPartition [k-1] = N;
	maximalValue = -1000;
	//setPermutedPartition(currentPartition);
}

vector<int>& Partition::getCurrentPartition(){
	return currentPartition;
}

void Partition::setMaximalPartition(int mV, vector<int>& mP){
	if (mV > maximalValue){
		maximalValue = mV;
		maximalPartition = mP;
	}
}

vector<int> Partition::getMaximalPartition(){
	vector<int> solution (1,maximalValue);
	solution.insert(solution.begin()+1,maximalPartition.begin(),maximalPartition.end());
	return solution;
}

bool Partition::nextPartition(){
	/*find the next ordered partition, meaning that we will have to permute to go through all partitions*/
	vector<int> indexP(0);
	for (int i(k-1);i >= 0; i--){
		if (currentPartition[i] < (currentPartition[k-1]-1))
			indexP.push_back(i);
	}
	if (indexP.empty())
		return false;

	int in = indexP[0];
	int sum = 0;
	for (int i(k-2); i >= in ; i--){
		currentPartition[i] = currentPartition[in]+1;
		sum += currentPartition[i];
	}
	for (int i(0);i < in; i++)
		sum += currentPartition[i];
	currentPartition[k-1] = N - sum;
	return true;
}

void Partition::scrollFunction(function<int(const vector<int>& v)> F){
	/* go through all (N,K) partitions and all the permutations of these partitions;
	update maximalValue and maximalPartition for function F*/
	
	vector<int> tempPermutation(currentPartition);
	setMaximalPartition(F(tempPermutation),tempPermutation);
	while (next_permutation(tempPermutation.begin(),tempPermutation.end())) //permute
		setMaximalPartition(F(tempPermutation),tempPermutation); 
	while (nextPartition()){//jump to next partition
		tempPermutation = currentPartition;
		setMaximalPartition(F(tempPermutation),tempPermutation); 
		while (next_permutation(tempPermutation.begin(),tempPermutation.end())){	//permute
			setMaximalPartition(F(tempPermutation),tempPermutation);
		}
	}	
}

