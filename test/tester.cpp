#include "partition.hpp"
#include "bestSlots.hpp"

using namespace std;



void testBestSlots(){
	int nbStudents = 8;
	vector<vector<int> > weights(3, vector<int>(31,1));
	for(int i(0);i<8;i++) weights[0][i] = 2;
	for(int i(0);i<8;i++) weights[1][i] = 2;
	for(int i(8);i<31;i++) weights[2][i] = -2;
	for(int i(14);i<28;i++) weights[1][i] = -2;
	for(int i(28);i<31;i++) weights[1][i] = 2; 
	for(int i(0);i<8;i++) weights[0][i] = 2;
	for(int i(0);i<8;i++) weights[1][i] = 2;
	for(int i(8);i<31;i++) weights[2][i] = -2;
	for(int i(14);i<31;i++) weights[1][i] = -2;
	/*for(int i(0);i<8;i++) weights[3][i] = -2;
	for(int i(8);i<31;i++) weights[3][i] = 2;
	for(int i(14);i<31;i++) weights[3][i] = -2;
	for (int i(0);i<24;i++) weights[4][i] = -2;
	for (int i(24);i<31;i++) weights[4][i] = 1;
	for (int i(0);i<8;i++) weights[5][i] = 2;
	for (int i(8);i<31;i++) weights[5][i] = 1;
	for (int i(0);i<8;i++) weights[6][i] = 1;
	for (int i(8);i<31;i++) weights[6][i] = -2;
	for (int i(0);i<31;i++) weights[7][i] = 1;*/
	BestSlots bs(weights);
	
	vector<int> cutWeek;
	cutWeek.push_back(8);
	cutWeek.push_back(20); 
	cutWeek.push_back(23);
	cutWeek.push_back(31);// 8 slots on Monday, 12 slots on Tuesday
	bs.setCutWeek(cutWeek);
	vector<int> studentSlots;
	studentSlots.reserve(nbStudents);
	studentSlots.push_back(3);
	studentSlots.push_back(4);
	studentSlots.push_back(3);
	/*studentSlots.push_back(3);
	studentSlots.push_back(4);
	studentSlots.push_back(3);
	studentSlots.push_back(4);
	studentSlots.push_back(3);*/
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
	//testPartition();
	testBestSlots();
}