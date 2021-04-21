/**
 * @file carrier_decorator.h
 */
#ifndef CARRIER_DECORATOR_H
#define CARRIER_DECORATOR_H

#include "drone.h"

namespace csci3081 {
/**
 * @brief Abstract Decorator Class
 * 
 */
class CarrierDecorator : public Drone { 
    protected:
        PackageCarrier* carrier_;
    public:
        CarrierDecorator(PackageCarrier* carrier);
        void Update(float dt) { carrier_->Update(dt); }
        int GetEntityCount() { return carrier_->GetEntityCount(); }
        int GetId() const { carrier_->GetId();}
        const std::string& GetName() { return carrier_->GetName(); }
        const std::string& GetType() { return carrier_->GetType();}
        const std::vector<float>& GetPosition() const { return carrier_->GetPosition(); }
        void SetPosition(const std::vector<float>& newPosition) { carrier_->SetPosition(newPosition); }
        // void SetDirection(const std::vector<float>& newDirection) { SetDirection(newDirection); }
        float GetSpeed() { return carrier_->GetSpeed(); }
        void SetSpeed(float speed) { carrier_->SetSpeed(speed);}
        const std::vector<float>& GetDirection() const { return carrier_->GetDirection();} 
        float GetRadius() const { return carrier_->GetRadius();}
        int GetVersion() const { return carrier_->GetVersion();}
        const picojson::object& GetDetails() { return carrier_->GetDetails();}
        bool IsDynamic() const { return carrier_->IsDynamic(); }
        std::vector< std::vector<float> > GetPath() {return carrier_->GetPath();}
        void SetPath(const std::vector< std::vector<float> >& newPath) {carrier_->SetPath(newPath);}
        std::vector< std::vector<float> > CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph = nullptr)
                                                        {carrier_->CreatePath(carrierPosition, packagePosition, customerPosition, graph);}
    
        void AssignPackage(Package* package) {carrier_->AssignPackage(package);}
        Battery* GetBattery() {return carrier_->GetBattery();}  
        picojson::value CreateNotification(std::string event, const std::vector< std::vector<float> >& path = {}) {return carrier_->CreateNotification(event, path);}
};
}

#endif // CARRIER_DECORATOR_H