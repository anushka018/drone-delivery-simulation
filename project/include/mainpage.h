/*! \mainpage CSCI 3081 Delivery Simulation project
* UMN Package Delivery Simulation {#mainpage} 
# I ATTEMPTED EXTRA CREDIT SCENES
## New User Guide 
Welcome to the UMN Campus package-delivery simulation! This simulation uses drones to deliver packages to customers across the University of Minnesota campus in Minneapolis. Consider this program a sneak peek into the future; you will be able to envision the efficiency and speed package deliveries. Customers will order packages and receive them in just a few minutes via a local drone waiting to deliver their order. To get started with the simulation, you will need to download the code from the git repository: https://github.umn.edu/umn-csci-3081-s21/repo-kell2416.git. 

If this is your first time cloning a git repository, here are the steps you can follow. If you have used Git before, you can skip to section two entitled **Cloning Project Repository**.

### Setting Up Git
1. Open up a terminal on your computer
    - On Mac, you can press Shift – Command(⌘) – U 
    - On Windows, you can use the shortcut Windows key + X + C (or A for admin). 
2. If you are brand new to Git and have not installed it on your machine, please download it following the instructions at https://git-scm.com/book/en/v2/Getting-Started-Installing-Git. 
3. Check to make sure your Git account is configured correctly on your machine. The terminal command `$ git config --list --show-origin` will list the current settings. If you are installing git for the first time, run the following commands with your name and email address.
```
$ git config --global user.name "John Doe"
$ git config --global user.email johndoe@example.com
```
4. Once you are finished with this step, you can run `$ git config --list`  again to ensure that your settings are correct. 

### Cloning Project Repository

1. Now, navigate to the directory where you would like to download and run the project from. If you are new to Linux terminal commands, you can use 
`$ mkdir DeliverySimulation` to create the directory. 
2. To move to this new directory, use the command `$ cd DeliverySimulation`
3. Once you are in the desired directory, clone the repository with the above link using the following command:
`$ git clone https://github.umn.edu/umn-csci-3081-s21/repo-kell2416.git`

### Building the Docker Container

1. To configure and run the program on your local machine, you will need to install a Docker Container. This container contains the necessary configuration files and libraries for the program and prevents the pain of having to download them all separately on your machine. First you should install Docker Desktop from https://www.docker.com/products/docker-desktop. 
2. Once Docker is installed, run the following command in your new directory to build the docker image
    `$ bin/build-env.sh`
This may take a few minutes. 
3. After the build script has completed, type in the command to run the Docker container
    `$ bin/run-env.sh`
4. You are now in the Docker Container! You can exit the container at any time by entering the command `$ exit` into your terminal. 

### Compiling and Running the Code
1. You should now have the code and the necessary software to run the simulation! To see the list of files and directories in the project, you can use the terminal command `$ ls`
2. Change directories to the project directory with `$ cd project`
3. Run the command `$ make` to compile the code and build the executables. This may take a few seconds but you will know it is finished when you can see your username and directory location again with $ at the terminal prompt. 
4. Once the compiling is finished, you can run the project with the command 
    `$ ./bin/run.sh`
This command runs the script for the delivery simulation.

### Viewing the Simulation

1. To see the simulation, go to http://127.0.0.1:8081/ at the browser of your choice. The simulation has been successfully tested using Safari, Chrome, and Firefox but graphics appear best on Google Chrome. 
2. On the simulation screen, you should see a 3D map of the UMN Twin Cities campus with buildings, streets, and natural features such as the Mississippi River. In the upper left corner of your screen, you should see the navigation menu. Here you can set the simulation speed, change your view to different objects in the simulation, and kill the simulation when you are finished. The two checkboxes on the lower half of the menu highlight the smart routes simulation entities can follow streets and walkways to avoid buildings. 
<img src="Drone1.png" alt="Drone flying in simulation" width="600"/>

3. To see the drone pick up the package and deliver it to the customer, it is suggested to change your view to **drone**. You can use your mouse or your touchpad to zoom in and out on the simulation. 
4. You can follow the drone’s movement as it navigates to the package, picks it up, and then navigates to the customer for delivery. 
<img src="AllEntities.png" alt="Drone reaching customer in simulation" width="600"/>

5. Once the drone has reached the customer, the customer robot will receive the package and the package will no longer be visible in the simulation. **You must press the “kill simulation” button** or the program will continually run on your machine. Make sure to press the “kill simulation” button each time you run the simulation. 

## Factory Implementation for Entity Creation
In the delivery simulation, there are currently three types of entities derived from the EntityBase class: drones, packages, and customers. The development of truck and robot entities to facilitate more deliveries is scheduled for future releases of the simulation. The delivery simulation project was designed following the DRY and SOLID principles for software development. The “O” in the SOLID acronym represents the Open/Closed Principle which states  "software entities should be open for extension, but closed for modification."  When considering which factory pattern to implement for entity creation, it is critical to adhere to the Open/Closed principle. This will prevent having to vigorously refactor code and risk erroneous behavior when trying to extend the simulation. Another important consideration was to encapsulate the entity creation and keep it loosely coupled with other systems in the simulation. Having stated this background and motivation, I will now explain my choice to use the Composite-Factory pattern over the Concrete Factory and Abstract Factory patterns for entity creation. 

## Concrete Factory Pattern 
The three distinct versions of the Factory Pattern share one commonality: they decouple or separate the creation of entities from the entity classes themselves. To implement the Concrete Factory pattern in the delivery simulation, we could create an EntityFactory Class and define a CreateEntity method in this class. As seen in the UML diagram below, the Concrete Factory class would create each of the three entities with this CreateEntity method.
<img src="ConcreteFactory.png" alt="Concrete Factory UML" width="600"/>

The CreateEntity method could be defined as follows:

    IEntity* CreateEntity(const picojson::object& val) {
        if (JsonHelper::GetString(val, "type") == "drone") {
            std::vector<float> position = JsonHelper::GetStdFloatVector(val, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(val, "direction");
        return new Drone(position, direction, val);
    }
        if (JsonHelper::GetString(val, "type") == "customer") {
            std::vector<float> position = JsonHelper::GetStdFloatVector(val, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(val, "direction");
        return new Customer(position, direction, val);
    }
        if (JsonHelper::GetString(val, "type") == "package") {
            std::vector<float> position = JsonHelper::GetStdFloatVector(val, "position");
            std::vector<float> direction = JsonHelper::GetStdFloatVector(val, "direction");
            return new Package(position, direction, val);
        }
        return NULL;
    }


The CreateEntity method takes in a picojson object as its argument and checks the type attribute of this object for which entity to create. Without the concrete factory, this method would have to be a part of the Delivery Simulation program itself. By calling the different entity constructors from within the program, we are coupling the program with each entity type. In contrast, the Concrete Factory decouples the creation logic of entities from the delivery simulation program itself. This follows the Single Responsibility Principle of SOLID because the delivery simulation class no longer has two responsibilities. It now only has the purpose of running the delivery instead of object creation and running the delivery process. 
A drawback for the Concrete Factory implementation is that it violates the Open/Closed Principle. If we would like to add more types of entities such as trucks and robots in the future, we will have to go back and add more if statements into the factory. Therefore modification of the code will be required instead of an extension of the code as desired. Another drawback of the Concrete Factory is that the factory class remains tightly coupled with each concrete Entity class. Due to these drawbacks, I decided not to use the Concrete Factory pattern in my simulation. 

## Abstract Factory Pattern
The next type of Factory Pattern I considered was the Abstract Factory pattern. The Abstract Factory handles entity creation by using an abstract EntityFactory class with a purely virtual CreateEntity method. Subsequently, factory subclasses are inherited from this abstract class for each type of entity (drone, customer, and package). Each factory subclass has the single responsibility of creating their unique entity type. Using polymorphism, each subclass overrides the CreateEntity method to construct its entity type.

<img src="AbstractFactory.png" alt="Abstract Factory UML" width="600"/>

The advantage of the Abstract Factory is that it obeys the Open/Closed Principle, unlike the Concrete Factory. All of the CreateEntity methods in the factory subclasses are closed to modification, but we can extend the virtual CreateEntity method to add entity types. For example, if we wanted to add a Truck entity type to the simulation, we could create a TruckFactory and extend the CreateEntity method into this class. 

The drawback to this method is that to implement this abstract factory, we must bring back the if statements into the delivery simulation program itself. To build an entity, the program must know which type of EntityFactory to create:

    EntityFactory* entityFactory; 

    if (drone) {
    entityFactory = new DroneFactory();
    }
    else if (package) {
    entityFactory = new PackageFactory();
    }
    else if (customer) {
    entityFactory = new CustomerFactory();
    }

    IEntity* entity = entityFactory->CreateEntity();

Therefore, the delivery simulation program is still tightly coupled with the types of each entity factory. While the abstract factory pattern satisfies the Open/Closed Principle in entity creation, it fails the same principle in factory creation. If we want to add trucks and robots to the simulation, we will need to add more factory subclasses to EntityFactory and have to modify the above code snippet. This drawback led me to consider finding a better alternative to entity creation with the Composite Factory pattern. 

## Composite Factory Pattern
The Composite Factory can be viewed as an extension of the Abstract Factory Pattern that satisfies both the Single Responsibility Principle and the Open/Closed Principle. We create an additional subclass of the abstract EntityFactory class called CompositeFactory. This composite factory class contains a factory list with each type of entity factory subclass. 
<img src="CompositeFactory.png" alt="Composite Factory UML" width="600"/>

The overridden CreateEntity method in CompositeFactory iterates through the factories and attempts to create an entity with each one. Only one factory subclass will end up succeeding because each CreateEntity method is dependent on the type of the picojson object passed as the parameter. 

    IEntity* CompositeFactory::CreateEntity(const picojson::object& val) {
            for (IEntityFactory* factory: factories) {
                IEntity* entity = factory->CreateEntity(val);
                if (entity) {
                    return entity;
                }
            }
            return NULL;
        }

Out of the three factory patterns discussed, the Composite Factory pattern is arguably the most extensible. To add a new entity type, we no longer need to refactor or modify any code in either the delivery simulation application or existing factories themselves. Instead, we create a new factory class derived from EntityFactory and override the CreateEntity method to build the new entity type. Subsequently, we add this new factory class into CompositeFactory’s factory list such that it is iterated in each call to CreateEntity. Therefore we are completely satisfying the Open/Closed Principle with this approach. Another advantage is that this approach satisfies DRY software principles the most out of the three because there are no repetitive if statements for either factory or entity creation. The delivery simulation program is no longer tightly coupled with specific entity types or factory types. The code to create an entity has been simplified to:

    DeliverySimulation::DeliverySimulation() {
    entityFactory = new CompositeFactory();
    }

    IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
    return entityFactory->CreateEntity(val);
    }

Factory classes are tasked with the single responsibility of entity creation and the delivery simulation program is no longer aware of these details or dependencies. 
Potential drawbacks to the Composite Factory pattern include the fact that we must add a new factory to the Composite list if we want to add an entity type. With the three existing types of entities, the CompositeFactory constructor is as follows:

    CompositeFactory::CompositeFactory() {
        factories.AddFactory(new DroneFactory());
        factories.AddFactory(new CustomerFactory());
        factories.AddFactory(new PackageFactory());
    }

It is clear that the Composite Factory is still coupled with each Factory class. If we were to add trucks and robots to the application, we would need to modify this constructor with the new factory types accordingly. The second potential drawback to the Composite Factory pattern is found in one of its strengths: generality. Each time CreateEntity is called, the entire list of each type of factory is iterated through. In a future release, consider a situation where the client wants to restrict the delivery simulation to using only trucks instead of drones or robots. With the composite factory pattern, there would be no way to dynamically not include the drone or robot factory as part of the composite. Thus this pattern is burdened with the difficulty of distinguishing between the composite factory and the non-composite factories. 

Despite these drawbacks, the Composite pattern is the most adherent to the Open/Closed principle of the three factory patterns. Extensibility is incredibly simple; to add a new entity type we only need to create a new factory class, override the create entity method, and add the factory to the Composite Factory class. The Composite Factory closes the code for the Delivery Simulation and existing entities to modification. Finally, it also provides high cohesion to the classes in the program overall by separating entity creation from the delivery process. Therefore the Composite Factory is the best software design choice for the delivery simulation program. 
*/


