/**
 * @file delivery_factory.cc
 */
#include "delivery_simulation.h"

namespace csci3081 {

DeliverySimulation::DeliverySimulation() {
	entityFactory = new CompositeFactory();
}

DeliverySimulation::~DeliverySimulation() {
	for (IEntity* entity : entities_) {
		delete entity;
	}
	delete entityFactory;
	delete map;
	delete scheduler;
}

IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
	// Call composite factory to create entity
   return entityFactory->CreateEntity(val); 
}

void DeliverySimulation::AddFactory(IEntityFactory* factory) {
	entityFactory->AddFactory(factory); 
}

void DeliverySimulation::AddEntity(IEntity* entity) { 
  entities_.push_back(entity); // Add to vector of entitites for simulation
}

void DeliverySimulation::SetGraph(const IGraph* graph) {
	scheduler = new DeliveryScheduler(graph);
	map = graph;
}

void DeliverySimulation::ScheduleDelivery(IEntity* package, IEntity* dest) {
	// Cast pointers of each entity type
	Package* pack = dynamic_cast<Package*>(package);
	Customer* customer = dynamic_cast<Customer*>(dest);
	std::vector<PackageCarrier*> possibleCarriers;
	PackageCarrier* carrier = nullptr;


	int size = GetEntities().size();
	for (int i = 0; i < size; i++) {
		EntityBase* entity = dynamic_cast<EntityBase*>(GetEntities().at(i));
		// Entity should not already be involved in a delivery (IsDynamic() should be false)
		if (entity)  {
			carrier = dynamic_cast<PackageCarrier*>(GetEntities().at(i));
			// Only schedule delivery if all casted pointers are valid
			if (carrier && pack && customer) {
				possibleCarriers.push_back(carrier);
			}
		}
	}
	if (possibleCarriers.size() > 0) {
		scheduler->ScheduleDelivery(pack, possibleCarriers, customer);
		return;
	}
	else {
		std::cout << "Delivery Failed; there are no drones or robots in simulation" << std::endl;
	}
	
}

void DeliverySimulation::AddObserver(IEntityObserver* observer) {}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { return entities_; }

void DeliverySimulation::Update(float dt) {
	int size = GetEntities().size();
	for (int i = 0; i < size; i++) {
		EntityBase* entity = dynamic_cast<EntityBase*> (GetEntities().at(i));
		if (entity->IsDynamic()) {
			entity->Update(dt);
		}
	}
}


// DO NOT MODIFY THE FOLLOWING UNLESS YOU REALLY KNOW WHAT YOU ARE DOING
void DeliverySimulation::RunScript(const picojson::array& script, IEntitySystem* system) const {
  JsonHelper::PrintArray(script);
  IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(system);
	if (deliverySystem) {

	    // To store the unadded entities_
	    std::vector<IEntity*> created_entities;

		for (unsigned int i=0; i < script.size(); i++) {
			const picojson::object& object = script[i].get<picojson::object>();
			const std::string cmd = object.find("command")->second.get<std::string>();
			const picojson::object& params = object.find("params")->second.get<picojson::object>();
			// May want to replace the next few if-statements with an enum
			if (cmd == "createEntity") {
				IEntity* entity = NULL;
				entity = deliverySystem->CreateEntity(params);
				if (entity) {
					created_entities.push_back(entity);
				} else {
					std::cout << "Null entity" << std::endl;
				}
			}
			else if (cmd == "addEntity") {
				int ent_index = static_cast<int>(params.find("index")->second.get<double>());
				if (ent_index >= 0 && ent_index < created_entities.size()) {
					deliverySystem->AddEntity(created_entities[ent_index]);
				}
			}
			else if (cmd == "scheduleDelivery" ) {
				int pkg_index = static_cast<int>(params.find("pkg_index")->second.get<double>());
				int dest_index = static_cast<int>(params.find("dest_index")->second.get<double>());
				if (pkg_index >= 0 && pkg_index < system->GetEntities().size()) {
					IEntity* pkg = deliverySystem->GetEntities()[pkg_index];
					if (dest_index >= 0 && pkg_index < system->GetEntities().size()) {
						IEntity* cst = system->GetEntities()[dest_index];
						if (pkg && cst) {
							deliverySystem->ScheduleDelivery(pkg, cst);
						}
					}
				}
				else {
					std::cout << "Failed to schedule delivery: invalid indexes" << std::endl;
				}
			}
		}
	}
}

}	// namespace csci3081
