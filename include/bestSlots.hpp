#ifndef BS_H
#define BS_H

#include<vector>
#include<iostream>
#define RunPermTest

class BestSlots{
	public:
	BestSlots(const std::vector<std::vector<int> >& w);
	
	void setCutWeek(const std::vector<int>& cw);
	
	void setSlots(const std::vector<int>& ss);
	
	void setWeightPauses(const std::vector<int>& swp);
	
	std::vector<std::vector<int> >& getWeights();
	
	std::vector<int>& getCutWeek();
	
	std::vector<int>& getSlots();
	
	std::vector<int>& getWeightPauses();
	
	int computeSum(const std::vector<int>& pauses);
	
	std::vector<int> minimalPauses(const int& nPauses);
	
	std::vector<int> weightForPerm(const std::vector<int>& perm);
	
	private:
		//unsigned smallSlot; // smallest intervall of time: for example 15 min 
		std::vector<int> cutWeek; // consecutive available small slots per day or per session, written as a cumulative sum: 8, 20 instead of 8 on Monday, 12 on Tuesday
		//int pauses; // number of pause slots
		std::vector<int> studentSlots; //for each student (or student session), number of slots to be given
		//int badWeight; // weight for a bad fit
		//int okWeight; // weight for an indifferent fit
		//int goodWeight; // weight fo a good fit
		// if impossible fit, break
		std::vector<std::vector<int> > weights; // matrix for the fit marks of the slots (lines = students, columns = small slots) ?? Best way to encode?
		std::vector<int> weightPauses; // negative or positive weight given to the pause in the middle of session, as a function of their number
		std::vector<int> sessionRep; // to keep track of the current session permutation 
		int beginIndex; // to keep track of the beginning index for the current session
	
};

std::ostream& operator<<(std::ostream & flow, std::vector<std::vector<int> > weights);

std::ostream& operator<<(std::ostream & flow, BestSlots bs);

void testBestSlots();

#endif
