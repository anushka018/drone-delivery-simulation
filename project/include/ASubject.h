#include "EntityProject/entity.h"

class ASubject { // declaration / definition
private:
	std::vector<ConcreteObserver*> list; // list of pointers to Customer observers
public:
	void Attach(ConcreteObserver* observer);
	void Detach(ConcreteObserver* observer);
	void Notify(const picojson::value& event, const IEntity& entity);
};

void ASubject::Attach(Customer* observer) { // implementation
	list.push_back(observer);
}
void ASubject::Detach(Customer* observer) { // implemenatation
	list.erase(std::remove(list.begin(), list.end(), observer), list.end());
}

void ASubject::Notify(const picojson::value& event, const IEntity& entity) { // implementation
	for (ConcreteObserver * concreteObserver : list){
		if (concreteObserver != NULL)
			concreteObserver ->OnEvent(event, entity);
	}
}