#include "partition.hpp"
#include "bestSlots.hpp"

using namespace std;

int display(const vector<int>& v){
	cout<< v;
	return 0;
}

void testBestSlots(){
	int nbStudents = 3;
	vector<vector<int> > weights(3, vector<int>(20,1));
	for(int i(0);i<8;i++) weights[0][i] = 2;
	for(int i(0);i<8;i++) weights[1][i] = 2;
	for(int i(8);i<20;i++) weights[2][i] = -2;
	for(int i(14);i<20;i++) weights[1][i] = -2;
	BestSlots bs(weights);
	
	vector<int> cutWeek;
	cutWeek.push_back(8);
	cutWeek.push_back(20); // 8 slots on Monday, 12 slots on Tuesday
	bs.setCutWeek(cutWeek);
	vector<int> studentSlots;
	studentSlots.reserve(nbStudents);
	studentSlots.push_back(3);
	studentSlots.push_back(4);
	studentSlots.push_back(3);
	cout<<studentSlots;
	bs.setSlots(studentSlots);
	
	vector<int> weightPauses;
	weightPauses.push_back(2);
	weightPauses.push_back(-1);
	weightPauses.push_back(-2);
	weightPauses.push_back(-3);
	weightPauses.push_back(-3);
	weightPauses.push_back(-3);
	bs.setWeightPauses(weightPauses);
	
	cout<<bs<<endl;		
}

void testPartition()
{
	Partition p(4,3);
	p.scrollFunction(display);	
}
	

int main(){
	testPartition();
	testBestSlots();
}