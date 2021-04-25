/**
 * @file ASubject.h
 */
#ifndef ASUBJECT_H_
#define ASUBJECT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "EntityProject/entity.h"


namespace csci3081{
/**
 * @brief The is an abstract class used to implement the subject component of the observer pattern
 * 
 * @details it is inherited by entity base which handles the addition of observers to the ntities vector in delivery 
 * simulation through the inovaction of the attach and detach methods. 
 * 
 */
class ASubject { // declaration / definition
private:
	std::vector<IEntityObserver*> observers; // list of pointers to entity observers
public:
	/** 
     * @brief adds a new observer to the observers vector 
     * 
     * @param[in] observer IEntityObserver*, the observer to be added
     */
	virtual void Attach(IEntityObserver* observer) {
		observers.push_back(observer);
	}
	/** 
     * @brief removes an observer from the observers vector 
     * 
     * @param[in] observer IEntityObserver*, the observer to be removed from the entities vector
     */
	virtual void Detach(IEntityObserver* observer){
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}
	/** 
     * @brief iterates through the observers vector calling the OnEvent method for each observer in the vector
     * 
     * @param[in] event const picojson::value&, the event value of the picojson object in the observers vector
     * @param[in] entity const IEntity&, the entity whose OnEvent method will be called (passed by reference)
     */
	virtual void Notify(const picojson::value& event, const IEntity& entity){
		for (IEntityObserver * concreteObserver : observers){
			if (concreteObserver != NULL){
				concreteObserver ->OnEvent(event, entity);
			}
		}
	}
};

}
#endif