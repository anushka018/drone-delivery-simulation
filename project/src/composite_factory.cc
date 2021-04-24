/**
 * @file composite_factory.cc
 * @author Audrey Kelly
 */
#include "composite_factory.h"

namespace csci3081 {
    CompositeFactory::CompositeFactory() {
        // initialize factories to an empty vector
        factories = {};
        factories.push_back(new DroneFactory());
        factories.push_back(new RobotFactory());
	    factories.push_back(new CustomerFactory());
	    factories.push_back(new PackageFactory());
    }

    void CompositeFactory::AddFactory(IEntityFactory* factory) {
        factories.push_back(factory);
    }

    IEntity* CompositeFactory::CreateEntity(const picojson::object& val) {
        for (IEntityFactory* factory : factories) {
            IEntity* entity = factory->CreateEntity(val);
            if (entity) {
                return entity;
            }
        }
        return NULL;
    }

    CompositeFactory::~CompositeFactory() {
        for (IEntityFactory* factory : factories) {
            delete factory;
        }
    }

}   // namespace csci3081