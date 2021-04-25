/**
 * @file base_drone_decorator.h
 */
#ifndef BASE_DRONE_DECORATOR_H
#define BASE_DRONE_DECORATOR_H

#include "drone.h"
#include "package_carrier.h"
#include "path_strategy.h"

namespace csci3081 {
/**
 * @brief Base Drone Decorator Class
 * 
 * @details Overrides all methods from EntityBase, ASubject, and PackageCarrier interfaces. The Update method is virtual, which allows us to
 * inherit various decorator classes from this Base Class with new dynamic features. The lone attribute is the reference to the PackageCarrier object, 
 * the object to be decorated. 
 * 
 */
class BaseDroneDecorator : public PackageCarrier { 
    protected:
        /**
         * @brief Reference to the Package Carrier object to be decorated. 
         * 
         */
        PackageCarrier* drone_;
    public:
        /**
         * @brief Construct a new Base Drone Decorator object
         * 
         * @param[in] drone: a reference to the Drone object to be decorated
         */
        BaseDroneDecorator(PackageCarrier* drone) {
            drone_ = drone;
        };
        /**
         * @brief Updates the Drone Object in the simulation and adds decoration
         * 
         * @param[in] dt: a float representing the time step for simulation movement
         */
        virtual void Update(float dt) override { drone_->Update(dt); }
        /** 
         * @brief Adds a new observer to the observers vector of the decorated object 
         * 
         * @param[in] observer IEntityObserver*, the observer to be added
         */
        void Attach(IEntityObserver* observer) { drone_->Attach(observer); }
        /** 
         * @brief removes an observer from the observers vector of the decorated object 
         * 
         * @param[in] observer IEntityObserver*, the observer to be removed from the entities vector of the decorated object
         */
	    void Detach(IEntityObserver* observer) { drone_->Detach(observer); }
        /** 
         * @brief iterates through the observers vector calling the OnEvent method for each observer in the vector
         * 
         * @param[in] event const picojson::value&, the event value of the picojson object in the observers vector
         * @param[in] entity const IEntity&, the entity whose OnEvent method will be called (passed by reference)
         */
	    void Notify(const picojson::value& event, const IEntity& entity) { drone_->Notify(event, entity);}
        /**
         * @brief Get the integer ID of the decorated entity
         * 
         * @return An integer ID of the decorated ntity
         */
        int GetId() const { drone_->GetId();}
        /**
         * @brief Get the name of the decorated entity
         * 
         * @return A string (const std::string&) of the decorated entity's name
         */
        const std::string& GetName() { return drone_->GetName(); }
        /**
         * @brief Get the type of the entity
         * 
         * @return A string (const std::string&) of the entity's type
         */
        const std::string& GetType() { return drone_->GetType();}
        /**
         * @brief Get the 3D coordinate position of the decorated entity in a std::vector<float>
         * 
         * @return A std::vector<float> of the decorated entity's position 
         */
        const std::vector<float>& GetPosition() const { return drone_->GetPosition(); }
        /**
         * @brief Get the 3D coordinate direction of the decorated entity's movement in a std::vector<float>
         * 
         * @return A std::vector<float> of the entity's position 
         */
        const std::vector<float>& GetDirection() const { return drone_->GetDirection();} 
        /**
         * @brief Set the Position of the decorated entity
         * 
         * @param[in] newPosition Vector3D object
         */
        void SetPosition(const std::vector<float>& newPosition) { drone_->SetPosition(newPosition); }
        /**
         * @brief Set the Direction of the decorated entity
         * 
         * @param[in] newDirection Vector3D object
         */
        void SetDirection(const std::vector<float>& newDirection) { drone_->SetDirection(newDirection); }
        /**
         * @brief Get the Speed of the decorated entity in meters per second
         * 
         * @return int representing speed of decorated Entity
         */
        float GetSpeed() { return drone_->GetSpeed(); }
        /**
         * @brief Set the Speed of the decorated entity
         * 
         * @param[in] newSpeed in meters / second
         */
        void SetSpeed(float speed) { drone_->SetSpeed(speed);}
        /**
         * @brief Get the radius in meters of the decorated entity
         * 
         * @return float representing radius of decorated entity in meters
         */
        float GetRadius() const { return drone_->GetRadius();}
        /**
         * @brief Get the Version of the decorated entity 
         * 
         * @return integer representing version of decorated entity
         */
        int GetVersion() const { return drone_->GetVersion();}
        /**
         * @brief Get the details of the decorated entity as a picojson object
         * 
         * @return const picojson::object& with details of decorated entity
         */
        const picojson::object& GetDetails() { return drone_->GetDetails();}
        /**
         * @brief Check if the decorated entity is actively moving during the simulation
         * 
         * @return true if decorated entity is moving in simulation
         * @return false if decorated entity is not moving in simulation
         */
        bool IsDynamic() const { return drone_->IsDynamic(); }
        /**
         * @brief Get the Path of the decorated entity
         * 
         * @return std::vector< std::vector<float> > path
         */
        std::vector< std::vector<float> > GetPath() {return drone_->GetPath();}
        /**
         * @brief Set the Path of the decorated entity 
         * 
         * @param[in] newPath: a std::vector< std::vector<float> > list of vector coordinates
         */
        void SetPath(const std::vector< std::vector<float> >& newPath) {drone_->SetPath(newPath);}
        /**
         * @brief Create a Path for the path attribute of the decorated drone
         * 
         * @param[in] carrierPosition, float vector coordinate of the drone's origin
         * @param[in] packagePosition, float vector coordinate of the package
         * @param[in] customerPosition, float vector coordinate of the customer
         * @param[in] graph, an IGraph* pointer to the simulation map to use the GetPath method from the IGraph* class
         * @return std::vector < std::vector<float> > path for drone to follow in its update method
         */
        std::vector< std::vector<float> > CreatePath(std::vector<float> carrierPosition, std::vector<float> packagePosition, 
                                                        std::vector<float> customerPosition, const IGraph* graph = nullptr) 
                                                        {return drone_-> CreatePath(carrierPosition, packagePosition, customerPosition, graph);}
        /**
         * @brief Assign a new package to the decorated drone
         * 
         * @param[in] package: a Package* reference to a package entity
         */
        void AssignPackage(Package* package) { drone_->AssignPackage(package); }
        /**
         * @brief Get the Battery pointer from the decorated drone
         * 
         * @return Battery* reference to the battery of the decorated drone
         */
        Battery* GetBattery() {return drone_->GetBattery();}
};
}

#endif