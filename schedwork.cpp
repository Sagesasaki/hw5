#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.



/// DO NOT CHANGE THIS BELOW

static const Worker_T INVALID_ID = (unsigned int)-1;

/// DO NOT CHANGE THIS ABOVE
//====================================


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t row,
    size_t col,
    vector<size_t>& maxShiftsMet);

// Add your implementation of schedule() and other helper functions here


//====================================
/// DO NOT CHANGE WITHIN RANGE BELOW



bool schedule(
	const AvailabilityMatrix& avail,
	const size_t dailyNeed,
	const size_t maxShifts,
	DailySchedule& sched
)
{
	if(avail.size() == 0){
		return false;
	}
	sched.clear();


/// DO NOT CHANGE WITHIN RANGE ABOVE
//====================================

  // Add your code below
	std::vector<size_t> tempVec;

	int numCol = avail[0].size();
	int numRow = avail.size();

	for(int i = 0; i < numCol; i++) // here we actually put in 0s into each column
	{
		tempVec.push_back(0);
	}
	for(int i = 0; i < numRow; i++) // make matrix of same row as Avail matrix
	{
		vector<Worker_T> t;
		sched.push_back(t);

		for(size_t k = 0; k < dailyNeed; k++)
		{
			sched[i].push_back(INVALID_ID); // do the rows now
		}
	}
	int r = 0;
	int c = 0;

	return scheduleHelper(avail,dailyNeed,maxShifts,sched,r,c,tempVec);
}

//rows are days; cols are workers
bool scheduleHelper(
	const AvailabilityMatrix& avail,
	const size_t dailyNeed,
	const size_t maxShifts,
	DailySchedule& sched,
	// add more below
	size_t row, // initially 0
	size_t col, // initially 0
	std::vector<size_t>& maxShiftsMet)
{
	
	bool v; 
	v = false;
	int ro = sched.size();
	bool available;

	// check if matrix is ok
	if(ro < (row + 1) ) return true; // if we don't do this we get seg fault
	for(int i = 0; i < avail[row].size(); i++) // for loop 0 to |column|
	{
		// not available
		if(!avail[row][i]) available = false;	 
		// if available (meaning maybe available since we still have to see if they are working that day)
		else
		{
			//check to see if the worker is already working that day
			std::vector<Worker_T>::iterator iterator = sched[row].begin();
			while(iterator != sched[row].end())
			{
				if(*iterator == i) // if already assigned, then we don't wanna re assign 
				{
					available = false;
					break;
				}
				else{
					iterator++;
				}
			}
			if(iterator == sched[row].end() && maxShifts > maxShiftsMet[i]) available = true; 
			else{ available = false;}
			// if(maxShifts <= maxShiftsMet[i]) available = false; // check max hours
		}
		if(available) // the actual backtracking part
		{
			sched[row][col] = i;
			maxShiftsMet[i]++;
			if(dailyNeed - 1 > col) // next slot -->  has to be in this order of if else or will fail
			{
				v = scheduleHelper(avail, dailyNeed, maxShifts, sched, row, col + 1, maxShiftsMet);
			}
			else
			{
				v = scheduleHelper(avail, dailyNeed, maxShifts, sched, row + 1, 0, maxShiftsMet);
			}
			maxShiftsMet[i]--;
		}
		if(v) return true;
	}
	sched[row][col] = INVALID_ID; // cannot work --> sched = invalid && return false  
	return false;
}
