/**
 * @file entity_base.h
 */
#ifndef ENTITY_BASE_H_
#define ENTITY_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <vector>
#include <string>
#include "vector3D.h"
#include "ASubject.h"

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for creating entities.
 *
 * This class can be used as the base for all entities in the delivery system.
 * The overall design is up to you (the student), but all entities must implement
 * the IEntity interface.
 *
 * See the documentation for IEntity for more information
 */
class EntityBase : public IEntity, public ASubject {
 public:
    /**
     * @brief Construct a new Entity Base object
     * 
    * @param[in] details of the picojson object
    * @param[in] position of entity in (x, y, z) floating point coordinates
    * @param[in] direction of entity in (x, y, z) floating point coordinates
    * @param[in] name of entity
    * @param[in] speed in meters per second
    * @param[in] radius in meters
     */
    EntityBase(const picojson::object& obj, std::vector<float> pos, std::vector<float> direction, 
                                            std::string name, float speed = 0.0, float radius = 1.0);
    /**
     * @brief Get the current Entity Count for the simulation
     * 
     * @return static int EntityCount
     */
    static int GetEntityCount();
    /**
     * @brief Get the integer ID of the entity
     * 
     * @return An integer ID of the entity
    */
    int GetId() const;
    /**
    * @brief Get the name of the entity
    * 
    * @return A string (const std::string&) of the entity's name
    */
    const std::string& GetName();
    /**
    * @brief Get the type of the entity
    * 
    * @return A string (const std::string&) of the entity's type
    */
    const std::string& GetType();
    /**
    * @brief Get the 3D coordinate position of the entity in a std::vector<float>
    * 
    * @return A std::vector<float> of the entity's position 
    */
    const std::vector<float>& GetPosition() const;
    /**
    * @brief Get the 3D coordinate direction of the entity's movement in a std::vector<float>
    * 
    * @return A std::vector<float> of the entity's position 
    */
    const std::vector<float>& GetDirection() const;
    /**
     * @brief Set the Position of the entity
     * 
     * @param[in] newPosition Vector3D object
     */
    void SetPosition(const std::vector<float>& newPosition);
    /**
     * @brief Set the Direction object
     * 
     * @param[in] newDirection Vector3D object
     */
    virtual void SetDirection(const std::vector<float>& newDirection);
    /**
     * @brief Get the radius in meters of the entity
     * 
     * @return float representing radius of entity in meters
     */
    float GetRadius() const;
    /**
     * @brief Get the Speed of the entity in meters per second
     * 
     * @return int representing speed of Entity
     */
    float GetSpeed();
    /**
     * @brief Get the Version of the entity 
     * 
     * @return integer representing version of entity
     */
    int GetVersion() const;
    /**
     * @brief Set the Speed of the entity
     * 
     * @param[in] newSpeed in meters / second
     */
    void SetSpeed(float newSpeed);
    /**
     * @brief Check if the entity is actively moving during the simulation
     * 
     * @return true if entity is moving in simulation
     * @return false if entity is not moving in simulation
     */
    bool IsDynamic() const;
    /**
     * @brief Get the details of the entity as a picojson object
     * 
     * @return const picojson::object& with details of entity
     */
    const picojson::object& GetDetails();
    /**
     * @brief Update moves entities that are dynamic in the simulation
     * 
     * @param[in] dt time interval in seconds
     */
    virtual void Update(float dt);
    /**
     * @brief Destroy the Entity Base object
     * 
     */
    virtual ~EntityBase() {};

 protected:
    static int entityCount;
    int ID;
    int version = 0;
    float radius_;
    float speed_;
    bool isDynamic;
    std::string name_;
    std::string type_;
    Vector3D position_;
    std::vector<float> posVector;
    Vector3D direction_;
    std::vector<float> dirVector;
    picojson::object details_;
};

}  // namespace csci3081

#endif  // ENTITY_BASE_H_
