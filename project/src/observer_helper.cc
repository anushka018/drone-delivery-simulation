#include "observer_helper.h"

namespace csci3081 {
    ObserverHelper::ObserverHelper(std::vector< std::vector<float> >& path, EntityBase* entity) {
        entity_ = entity;
        path_ = &path;
    }

    void ObserverHelper::CreateNotification(std::string event) {
        picojson::object eventObj = JsonHelper::CreateJsonNotification();
        JsonHelper::AddStringToJsonObject(eventObj, "value", event);
        picojson::value eventVal = JsonHelper::ConvertPicojsonObjectToValue(eventObj);
        entity_->Notify(eventVal, *(dynamic_cast<IEntity*>(entity_)));
    }

    void ObserverHelper::CreateNotification(std::string event, Package* package) {
        picojson::object eventObj = JsonHelper::CreateJsonNotification();
        JsonHelper::AddStringToJsonObject(eventObj, "value", event);
        picojson::value eventVal = JsonHelper::ConvertPicojsonObjectToValue(eventObj);
        entity_->Notify(eventVal, *(dynamic_cast<IEntity*>(package)));
    }

    void ObserverHelper::CreateNotification(std::string event, std::vector< std::vector<float> >& path) {
        picojson::object eventObj = JsonHelper::CreateJsonNotification();
        JsonHelper::AddStringToJsonObject(eventObj, "value", event);
        JsonHelper::AddStdVectorVectorFloatToJsonObject(eventObj, "path", path);
        picojson::value eventVal = JsonHelper::ConvertPicojsonObjectToValue(eventObj);
        entity_->Notify(eventVal, *(dynamic_cast<IEntity*>(entity_)));
    }

    void ObserverHelper::FindPathToCustomer(std::vector< std::vector<float> >& packagePath, std::vector<Package*>& packages) {
        // find segment of path from package to customer
        Package* currentPackage = packages.at(0); 
        std::vector< std::vector<float> >::iterator start = std::find((*path_).begin(), (*path_).end(), currentPackage->GetPosition());
        std::vector< std::vector<float> >::iterator end;
        if (packages.size() > 1) {
            end = std::find(start, (*path_).end(), (currentPackage->GetDestination()).GetVector());
        }
        else {
            end = (*path_).end();
        }
        int size = std::distance(start, end);
        packagePath.resize(size);
        std::copy(start, end, packagePath.begin());
    }

    void ObserverHelper::FindPathToPackage(std::vector< std::vector<float> >& packagePath, std::vector<Package*>& packages) {
        // find segment of path from carrier origin to package
        Package* currentPackage = packages.at(0); 
        std::vector< std::vector<float> >::iterator end = std::find((*path_).begin(), (*path_).end(), currentPackage->GetPosition());
        int size = std::distance((*path_).begin(), end);
        packagePath.resize(size);
        std::copy((*path_).begin(), end, packagePath.begin());
        packagePath.push_back(currentPackage->GetPosition());
    }

    void ObserverHelper::GetNextPackagePath(std::vector< std::vector<float> >& packagePath, std::vector<Package*>& packages) {
         // Get path from last package's destination to next package
        Package* currentPackage = packages.at(0);  
        std::vector< std::vector<float> >::iterator start = std::find((*path_).begin(), (*path_).end(), (currentPackage->GetDestination()).GetVector());
        std::vector< std::vector<float> >::iterator end = std::find(start, (*path_).end(), packages.at(1)->GetPosition());
        int size = std::distance(start, end);
        packagePath.resize(size);
        std::copy(start, end, packagePath.begin());
    }
}