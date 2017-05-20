Finding an optimal timetable for tutors:

Partition - class to generate all permutations of one given partition of the pause slots 

BestSlots - class to generate all possible configurations and give best one or list minimal ones

Compilation:

	make clean
	
	make tester
	
Example: 8 avalaible slots on Monday, 12 on Tuesday
3 students, 3 slots necessary for the first one, 4 for the second, 3 for the third
First student would prefer Monday, can come on Tuesday
Second would prefer Monday, can come on the six first slots on Tuesday
Third can come only on Monday
Teacher prefers not to have pauses during a teaching session

Printing weights: --> variable weights
Size:3x20
  2  2  2  2  2  2  2  2  1  1  1  1  1  1  1  1  1  1  1  1
  2  2  2  2  2  2  2  2  1  1  1  1  1  1 -2 -2 -2 -2 -2 -2
  1  1  1  1  1  1  1  1 -2 -2 -2 -2 -2 -2 -2 -2 -2 -2 -2 -2
Printing students slots: --> variable studentSlots
  3  4  3
Printing week schedule: --> variable cutWeeks
  8 20
Printing weight for pauses:  --> variable weightPauses
  2 -1 -2 -3 -3 -3


	