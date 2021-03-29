#include <ASubject.h>

class PackageSubject : public ASubject { //Concrete Subject - Package 
public:
	PackageSubject() { };
	void ChangeStatus(const picojson::value& event,const IEntity& entity);
};

void PackageSubject::ChangeStatus(const picojson::value& event,const IEntity& entity) { // implementation
	Notify(const picojson::value& event, const IEntity& entity);
}