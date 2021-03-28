#include <ASubject.h>

namespace csci3081{
class PackageSubject: public ASubject{
    public: 
        void GetStatus(const picojson::value& event, const IEntity& entity)){
            Notify(event, entity);
        }
};

}


//QUESTIONS
//- how to create the events that are being passed into GetStatus
//  - should we be creating events based off of variables we make in package?
//- where to call GetStatus()