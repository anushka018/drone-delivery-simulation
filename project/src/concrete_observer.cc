// #include <concrete_observer.h>


// void ConcreteObserver::OnEvent(const picojson::value& event, const IEntity& entity) override { //Implementation
// 	if (JsonHelper::GetString(val, "type") == "notify") {
//         if (JsonHelper::GetString(val, "value") == "scheduled") {
// 		    std::cout << "Entity #" << entity.GetId() <<" scheduled.\n";
//         }
//         else if (JsonHelper::GetString(val, "value") == "en route") {
// 		    std::cout << "Entity #" << entity.GetId() <<" picked up.\n";

//         }
//         else if (JsonHelper::GetString(val, "value") == "delivered") {
// 		    std::cout << "Entity #" << entity.GetId() <<" delivered to customer.\n";

//         }
//     }

// }