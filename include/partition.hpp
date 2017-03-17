#ifndef PERM_H
#define PERM_H

#include <iostream>
#include <vector>
#include <iomanip>//setw
#include <algorithm>//next_permutation
#include <functional>

std::ostream& operator<<(std::ostream & flow, std::vector<int> vec);

class Partition{
	/*generate all k length - partitions of integer N*/
	public:
		Partition(const int& N,const int& k);
	
		void setMaximalPartition(int mV, std::vector<int>& mP);
	
		std::vector<int> getMaximalPartition();
	
		std::vector<int>& getCurrentPartition();
	
	    bool nextPartition();
	
		void scrollFunction(std::function<int(const std::vector<int>& v)> F);
		
	private:
		int N, k; // N integer to be partitionned, k length of partition vector
		std::vector<int> currentPartition;
		int maximalValue;
		std::vector<int> maximalPartition;
	 
};

void testPartition();



#endif