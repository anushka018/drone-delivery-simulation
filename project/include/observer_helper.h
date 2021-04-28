#ifndef OBSERVER_HELPER_H
#define OBSERVER_HELPER_H

#include "entity_base.h"
#include "package.h"
#include "picojson.h"
#include "json_helper.h"

namespace csci3081 {
/**
 * @brief The Observer Helper Class handles the set up and notifications of observers for entities. 
 * 
 */
class ObserverHelper {
    public:
        /**
         * @brief Construct a new Observer Helper object
         * 
         * @param[in] path: the path the Package Carrier is currently following
         * @param[in] entity: a pointer to the Package Carrier entity that this instance of Observer Helper belongs to
         */
        ObserverHelper(std::vector< std::vector<float> >& path, EntityBase* entity);
        /**
        * @brief Creates a picojson object of type notification, loads the correct values for that type of notification, 
        * and converts the picojson object into a picojson value
        * 
        * @param[in] event: string for picojson object key "value"
        */
        void CreateNotification(std::string event);
        /**
        * @brief Creates a picojson object of type notification, loads the correct values for that type of notification, 
        * and converts the picojson object into a picojson value
        * 
        * @param[in] event: string for picojson object key "value"
        * @param[in] package: a pointer to the package for a package notification
        */
        void CreateNotification(std::string event, Package* package);
        /**
        * @brief Creates a picojson object of type notification, loads the correct values for that type of notification, 
        * and converts the picojson object into a picojson value
        * 
        * @param[in] event: string for picojson object key "value"
        * @param[in] path: the path segment of the package carrier for the notification
        */
        void CreateNotification(std::string event, std::vector< std::vector<float> >& path);
        /**
         * @brief Calculate the path from the current carrier location to its next package for the "moving" notification
         * 
         * @param[in] customerPath: a reference to a path that is written to by the method for the notification
         * @param[in] packages: the list of packages scheduled to the observer helper's package carrier
         */
        void FindPathToCustomer(std::vector< std::vector<float> >& customerPath,std::vector<Package*>& packages);
        /**
         * @brief Calculate the path from the current package to its customer destination for the "moving" notification
         * 
         * @param[in,out] packagePath: a reference to a path that is written to by the method for the notification
         * @param[in] packages: the list of packages scheduled to the observer helper's package carrier
         */
        void FindPathToPackage(std::vector< std::vector<float> >& packagePath, std::vector<Package*>& packages);
        /**
         * @brief Calculate the path from the previous destination to the next package for the "moving" notification
         * 
         * @param[in,out] path: a reference to a path that is written to by the method for the notification
         * @param[in] packages: the list of packages scheduled to the observer helper's package carrier
         */
        void GetNextPackagePath(std::vector< std::vector<float> >& path, std::vector<Package*>& packages);

    private:
        std::vector< std::vector<float> >* path_;
        EntityBase* entity_;
};
}
#endif