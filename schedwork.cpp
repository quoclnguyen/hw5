

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
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, unsigned int day, Worker_T position
);

bool isValid(const AvailabilityMatrix& avail,
    const size_t maxShifts,
    DailySchedule& sched, unsigned int day, Worker_T person);




// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    //initialize our sched vector
    for (unsigned int i = 0; i< avail.size(); i++){ // for each day
      vector<Worker_T> vec(dailyNeed, INVALID_ID); //add a vector the size of the required workers.
      sched.push_back(vec);
    }
    bool scheduleExists = scheduleHelper(avail, dailyNeed, maxShifts, sched, 0,0);
    return scheduleExists;

}

bool scheduleHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, unsigned int day, Worker_T position
){
  //check all workers
  //if worker is available to work on that day, and they have not reached maxShifts, 
    //continue to next recursive call (slot)
  //if no workers available to work, return false.

  if (position >=dailyNeed){ //if we've completed work schedule for one day, we move to the next
    ++day;
    position =0;
  }
  //if we pass to the day after the last day, it means we found a solution
  if (day == avail.size()){return true;}
 //loops thru each person's availability on a certain day
  for(unsigned int i =0; i < avail[day].size(); i++){ 
    if (isValid(avail, maxShifts, sched, day, i)){ //if the person can work during that day
      sched[day][position]= i; //means the ith worker can work
      if(scheduleHelper(avail, dailyNeed, maxShifts, sched, day, position+1)==true){ return true;}
    }
  }
  sched[day][position]= -1; //set worker id to invalid to reset.
  return false;

}

bool isValid(const AvailabilityMatrix& avail,
    const size_t maxShifts,
    DailySchedule& sched, unsigned int day, Worker_T person){
  //we check if person has not worked more than max shifts, and if person is available/ not already working that day
  if (avail[day][person] ==0) {return false;}
  unsigned int daysWorked=0; 

  for (unsigned int i =0; i < sched.size();i++){ //check how many times worker has worked 
    for (unsigned int j = 0; j<sched[i].size();j++){
      if (sched[i][j]==person) {
        if( i==day){return false;} //if worker is already scheduled that day
        ++daysWorked;
      }
    }
  }
  if(daysWorked==maxShifts){return false;}
  return true;
}

