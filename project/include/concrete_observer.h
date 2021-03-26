#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <entity_observer.h>

class ConcreteObserver : IEntityObserver { //Concrete Observer Class
private:
	std::string name_; // Customer name
public:
	ConcreteObserver(std::string name) { this->name_ = name; }
    void OnEvent(const picojson::value& event, const IEntity& entity) override;
};