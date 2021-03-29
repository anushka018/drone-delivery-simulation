/**
 * @file ASubject.h
 */
#ifndef ASUBJECT_H_
#define ASUBJECT_H_

#include "EntityProject/entity.h"


namespace csci3081{

class ASubject { // declaration / definition
private:
	std::vector<IEntityObserver*> observers; // list of pointers to Customer observers
public:
	void Attach(IEntityObserver* observer) {
		observers.push_back(observer);
	}
	void Detach(IEntityObserver* observer){
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}
	void Notify(const picojson::value& event, const IEntity& entity){
		for (IEntityObserver * concreteObserver : observers){
			if (concreteObserver != NULL){
				concreteObserver ->OnEvent(event, entity);
			}
		}
	}
};

}
#endif