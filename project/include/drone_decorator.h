/**
 * @file drone_decorator.h
 */
#ifndef DRONE_DECORATOR_H
#define DRONE_DECORATOR_H

#include "drone_decorator.h"
#include "drone.h"

namespace csci3081 {
/**
 * @brief Drone Decorator Class
 * 
 */
class DroneDecorator : public Drone { 
    protected:
        Drone* drone_;
    public:
        DroneDecorator(Drone* drone);

        void Attach(IEntityObserver* observer) { drone_->Attach(observer); }
	
	    void Detach(IEntityObserver* observer) { drone_->Detach(observer); }

	    void Notify(const picojson::value& event, const IEntity& entity) { drone_->Notify(event, entity);}

        int GetId() const { drone_->GetId();}

        const std::string& GetName() { return drone_->GetName(); }

        const std::string& GetType() { return drone_->GetType();}

        const std::vector<float>& GetPosition() const { return drone_->GetPosition(); }

        void SetPosition(const std::vector<float>& newPosition) { drone_->SetPosition(newPosition); }

        void SetDirection(const std::vector<float>& newDirection) { drone_->SetDirection(newDirection); }

        float GetSpeed() { return drone_->GetSpeed(); }

        void SetSpeed(float speed) { drone_->SetSpeed(speed);}

        const std::vector<float>& GetDirection() const { return drone_->GetDirection();} 

        float GetRadius() const { return drone_->GetRadius();}

        int GetVersion() const { return drone_->GetVersion();}

        const picojson::object& GetDetails() { return drone_->GetDetails();}

        bool IsDynamic() const { return drone_->IsDynamic(); }

        void Update(float dt);

        std::vector< std::vector<float> > GetPath() {return drone_->GetPath();}

        void SetPath(const std::vector< std::vector<float> >& newPath) {drone_->SetPath(newPath);}

        std::vector< std::vector<float> > CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph = nullptr) 
                                                        {return drone_-> CreatePath(carrierPosition, packagePosition, customerPosition, graph);}
    
        void AssignPackage(Package* package) { 
            drone_->AssignPackage(package);
        }

        Battery* GetBattery() {return drone_->GetBattery();}

        picojson::value CreateNotification(std::string event, const std::vector< std::vector<float> >& path = {}) {return drone_->CreateNotification(event, path);}
    
};
}

#endif