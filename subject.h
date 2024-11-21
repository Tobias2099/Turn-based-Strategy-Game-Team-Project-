#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <algorithm>
#include "observer.h" // Include the observer class declaration

using namespace std;

class Subject {
	vector<Observer*> observers;
	public:
		void attach(Observer *ob);
		void detach(Observer*ob); 
		void notifyObservers();
		virtual ~Subject() = 0;
};

#endif // SUBJECT_H
