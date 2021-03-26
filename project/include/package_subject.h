#include <ASubject.h>

class Package : public ASubject { //Concrete Subject - Car
private: 
    bool scheduled_;
	bool pickedUp_;
    bool delivered_;
public:
	Package(bool scheduled, bool pickedUp, bool delivered) { 
        scheduled_ = scheduled; 
        pickedUp_ = pickedUp; 
        delivered_ = delivered;
    }
	void ChangeStatus(bool scheduled, bool pickedUp, bool delivered);
};

void Package::ChangeStatus(bool scheduled, bool pickedUp, bool delivered) { // implementation
    scheduled_ = scheduled; 
    pickedUp_ = pickedUp; 
    delivered_ = delivered;
	On_Event(const picojson::value& event, const IEntity& entity);
}