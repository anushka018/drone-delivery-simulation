#include "EntityProject/entity.h"


namespace csci3081{
class ASubject { // declaration / definition
private:
	std::vector<IEntityObserver*> observers; // list of pointers to Customer observers
public:
	void Attach(IEntityObserver* observer);
	void Detach(IEntityObserver* observer);
	void Notify(const picojson::value& event, const IEntity& entity);
};

void ASubject::Attach(IEntityObserver* observer) { // implementation
	observers.push_back(observer);
}
void ASubject::Detach(IEntityObserver* observer) { // implemenatation
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void ASubject::Notify(const picojson::value& event, const IEntity& entity) { // implementation
	for (IEntityObserver * concreteObserver : observers){
		if (concreteObserver != NULL)
			concreteObserver ->OnEvent(event, entity);
	}
}
}