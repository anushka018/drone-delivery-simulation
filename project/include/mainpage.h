/*! \mainpage CSCI 3081 Delivery Simulation project
*
* To generate documentation, first build the project with `make` in the `project` directory.
* Next, navigate to `project/docs` and run `doxygen Doxyfile`.
* Then open `project/docs/html/index.html` in your web browser to view the documentation.
*
* Goal of the simulation: A drone navigates to a package, picks it up, and then delivers it to a customer. 
* Once the drone has dropped off the package to the customer, the package disappears from the simulation.
* The simulation is currently being run on a map of the University of Minnesota campus. The
* drone follows a "smart route" to the package and from the package to the customer. The smart route
* is determined using the A* shortest path graph traversal algorithm. 
* 
* User Guide:
* 1. Clone the remote repository at https://github.umn.edu/umn-csci-3081-s21/repo-angam003
* 2. Obtain access to a Linux environment and run the simulation
*
*   a. Docker
*
*       i. Install Docker Desktop on your local machine (if you have Windows 10 install wsl2 and Ubuntu and if you have Linux use docker group instead of sudo)
*  
*       ii. cd to the root directory of the cloned repository 
*
*       iii. enter the command $ bin/build-env.sh
*
*       iv. enter the command $ bin/run-env.sh
*
*       v. inside the docker image cd to the project directory and enter the command $ make
*
*       vi. enter the command $ ./bin/run.sh within the project directory to run the simulation
*
*       vii. Open up Firefox and browse to http://127.0.0.1:8081/
*
*   b. SSH
*
*       i. SSH onto a CSE Labs machine using your UMN login 
*
*       ii. cd to the root directory of the cloned repository 
*
*       iii. set up the remote web server by entering the command $ ./project/bin/setup-server.sh <username> <computer_number> 
*       where username is your x500 and computer number is the lab machine you are currently ssh'd onto
*
*       iv.  run the remote web server by entering the command $ ./project/bin/server.sh <username> <computer_number> <port> where port is 8081
*
*       v. Open up Firefox and browse to http://127.0.0.1:8081/
*
*   c. VOLE
*
*       i. Log in to VOLE or VOLE 3D at the link https://cse.umn.edu/cseit/virtual-online-linux-environment-self-help-guide
*
*       ii. cd to the root directory of the cloned repository 
*
*       iii. cd to the project directory and enter the command $ make
*
*       iv. still within the project directory and enter the command $ ./bin/run.sh to run the simulation
*
*       v. Open up Firefox and browse to http://127.0.0.1:8081/
*
*
* Discussion of Composite Factory Pattern
*
* - Pro
*
* The composite factory pattern combines the factory design pattern and the composite design pattern. The factory pattern implements an interface for the creation of entities
* which is currently drones, packages, and customers. In our case, this is done in the IEntity Factory class which creates IEntity objects from the IEntity class.
* Both of these classes are abstract. It then pushes the creation of these entities to subclasses which, in this case, are the drone factory, package factory,
* and customer factory classes. These classes are then responsible for determining which entity to instantiate (ie which create entity method will be called). 
* The composite pattern groups together drone, customer, and package entities so that we can add them to a composite factory object. Then we can create each of our
* entities by iterating through the all component objects stored in the composite object, which is represented as a vector in this case, and call the create entity 
* method on each component object. This is useful because it allows us to enforce SOLID software development principles while also allowing us to only call
* the create entity method on the composite factory object. 
*
* - Con 
*
* Some potential cons of the composite factory implementation are that it creates many layers of abstraction and it may be difficult to create a shared interface
* for each of the object classes with a largely disjoint functionality. This means that in certain cases, you may be forced to make the interface for the components
* overgeneralized. This can make it more challenging to comprehend. The composite factory method pattern may also be used improperly and not 
* provide a realistic understanding of how the production code will be extremely likely to evolve. 
*
*
* Discussion of Concrete Factory Pattern vs. Abstract Factory Pattern vs. Composite Factory Pattern
* 
* Concrete Factory Pattern
*
* - Pro
* 
* The concrete factory pattern allows factory classes to handle all the creation logic instead of the program. This means that the client does not need to worry about
* creating objects, but instead, they pass parameters for object creation to a method in the factory class. This is beneficial because changes to the factory design
* do not require the client to make changes on their side - meaning they do not have to recompile their code to interact with the factory. The concrete factory pattern 
* also allows for the creation of objects of different types because you do not need to specify the type of an object during its creation. Finally, we can also encapsulate
* instantiations for concrete types and create objects through inheritance. This allows us to follow good object-oriented design principles. 
*
* - Con
* 
* A downside of the concrete factory pattern, however, is that it does not remove the need for the dreaded if statements. This also means that it is not closed to modification 
* or open to extensibility. This is because whenever we add a new type of object, we will also need to add another class. We need the if statements because we still 
* need to check the type of object, so we know which creation method to call. Another disadvantage of the simple factory pattern is that there is still reasonably 
* high coupling between the main factory class and each of the object type subclasses. This is where the abstract factory pattern comes into play. 
*
* Concrete Factory Pattern UML
*
* ![Concrete Factory Pattern UML](../images/ConcreteFactory.png)
*
*
* Abstract Factory Pattern
*
* - Pro
*
* The abstract factory provides an interface for creating families of related, dependent objects without specifying their concrete classes by
* creating objects through composition and pushing object creation to subclasses. 
* This allows us to take advantage of run-time polymorphism. It also provides for looser coupling between classes
* by getting rid of the need to include the disadvantageous sequence of if statments which violate good software design principles. 
* We also do not need to edit the base factory class when we add new object types to the factory creation. This helps us utilize good design by making our
* program closed to modification. Since the creation is not linked to a specific class, the abstract factory pattern is 
* a very flexible approach. 
*
* - Con 
*
* The abstract factory may or may not be able to be implemented in your program design depending on if there is a possibility to remove the dreaded sequence 
* of if statements in your code. If the design of the code does not allow for the removal of the if statements, the abstract factory method pattern is not 
* the best design pattern choice for your software project. In this case, the concrete factory pattern is the most likely the most advantageous design pattern choice.
* A second disadvantage is that it is difficult to support the creation of new types of objects using this pattern. This is because the interface fixes 
* the set of products that can be created. 
* 
* Abstract Factory Pattern UML
*
* ![Abstract Factory Pattern UML](../images/AbstractFactory.png)
*
*
* Composite Factory Pattern
*
* - Pro
* 
* The composite pattern allows a group of objects to be treated as a single object. It is a factory that creates multiple types of objects.
* The objects are recognized as a hierarchy and can be visualized as a tree-like structure. 
* The composite factory pattern is beneficial because it allows for extensions of an existing software system to incorporate new features without the need to perform regression testing. 
* It also guards against the violation of the open/closed software design principle. This principle states that a well-designed software system is one that is 
* open to extension and closed to change. Finally, we only need to call the create method on the composite factory object instead of on each of the component
* objects when implementing the composite factory pattern.
*
* - Con 
*
* A con of the composite factory pattern is that it may make code more difficult to read. This could be because all of the code written is hidden behind an
* abstraction which may in turn hide other abstractions. Going through these multiple layers of abstraction may make code challenging to read and interpret
* for software engineers implementing the pattern and those who may need to look at and understand the production code later. In addition, this design 
* pattern requires the creation of additional classes and additional code which may also make the general control flow of the program harder to 
* understand. 
*
* Composite Factory Pattern UML
*
* ![Composite Factory Pattern UML](../images/CompositeFactory.png)
* 
*
*
*
* Designing and Implementing Different Routes Discussion
*
*
* The Strategy Pattern
*
* To implement the strategy pattern for the path behavior of drones and robots, we first created an abstract PathStrategy class with a virtual CreatePath method. Our initial implementation of CreatePath took in three parameters: the origin of the drone/robot, the package position, and the customer position. The purpose of the CreatePath method is to create the complete path for the drone or robot to follow for the entire delivery, from the package pick up to drop off. The PathStrategy class serves as the base class for each of the concrete path strategies: smart route, beeline, and the parabolic paths. Each of the derived classes overrides the virtual CreatePath method with their own unique definition for their class name. 
* 
* Generalized Strategy Pattern UML
*
* ![UML of Generalized Strategy Pattern](../images/General_Strategy_Pattern_UML.PNG)
*
* Strategy Pattern for Drone Paths UML
*
* ![UML of Strategy Pattern for Drones Paths] (../images/Strategy_Pattern_Drones_UML.PNG)
*
* In the previous iteration, our simulation code used the smart route for all package deliveries. The best tip for implementing the smart route is to look at the provided documentation for Graph.h in the base code. We had a DeliveryScheduler class to help with delivery set up and the CreatePath method was originally in this class. To implement the CreatePath in the SmartPath class we copied and pasted over this method. The problem that we encountered was that the Smart Route relies on an IGraph pointer to the graph for that json scene. We were stuck on how to share this graph pointer from DeliveryScheduler to the SmartPath class without tightly coupling these classes which are not strongly related. Our solution to this problem was to add an additional, optional IGraph* parameter to the CreatePath method. This way we can pass this IGraph pointer from the DeliveryScheduler when we prompt the package carrier (drone or robot) to create the path with their assigned strategy. The beeline and parabolic paths do not need this pointer, however this was the best idea we had to avoid tightly coupling these classes. 
* 
* To follow DRY software design, both drones and robots are derived from an abstract PackageCarrier class that contains their path attribute and methods for motion. Therefore we added a PathStrategy pointer as an attribute to this PackageCarrier class.
* 
* The beeline route entails a drone moving directly from its starting location to a package and finally directly to the package's associated customer location. In order to implement the beeline path, we wrote a class that inherited from our abstract path strategy class which overrode the CreatePath method. To build the path within this method, we simply created a vector of float vectors to store the path and added to it the package carrier;s location (the drone or robot) and the customer’s location. We also ensured to raise the height of the package carrier to 400 when it was travelling to the package and the customer so that it would not run into any buildings. We were able to utilize a similar thought process that one of our team members, who chose the beeline route instead of the smart route, utilized in the previous iteration. 
* 
* Finally, the third path strategy implemented in this iteration was the parabolic path. This was the most challenging to implement given that an understanding of riemann sums and calculus was required. In addition, this path strategy was not implemented by any of our team members in iteration 1 so it was an entirely new concept. Lab 14, which provided information on how to implement the strategy pattern was incredibly useful. In addition, chapter 2 of the head first design in combination with lectures nineteen and twenty were helpful in understanding the strategy pattern from a high level. 
* 
* In terms of understanding the mathematics behind the implementation for the parabolic path, the youtube video posted on the course website about riemann sums and the Powerpoint slides describing how to build a better jump were helpful. Our team was extremely grateful for the second approach to the parabolic path posted by 1 of the TAs as we felt like this made more sense then the instruction in lab 14. This was something we relied heavily on in our design of the parabolic path strategy.
* 
* To implement the parabolic path, we created a new class which inherited from our abstract path strategy class as our beeline and smart route strategies did as well. In this class we override the createpath method once again. To build the parabolic path, we first initialize the starting position of the carrier and the first destination to the package. Next, we set the height of the jump which we initialized to 1.0. Then, we created the path from the carrier to the package using the formula to update the x, y, and z coordinates as follows: 
*
* dt = i / 101, where is ranges from 0 - 100 
*
* x = initialX + (finalX - initialX)*dt, update x with its value plus change in x times dt
*
* z = initialZ + (finalZ - initialZ)*dt, update z with its value plus change in z times dt
*
* y = ((4*height)+(-2*initialY)+(-2*finalY))*dt*dt + ((-4*height)+(3*initialY) + finalY)*dt + initialY, set y equal to 4 times the height plus -2 times the initial height + -2 times the new height times dt squared plus -4 times the height plus 3 times the initial height + dt times the new height plus the initial height
*
* Next, we reset the x, y, and z coordinates to reset the jump from the package to the customer and build up the path from the package to the customer using the same logic outlined in the formulas above. 
*
*
* Links to the resources mentioned above are provided below:
*
* 1. Lab 14 - Implementing the strategy pattern: https://github.umn.edu/umn-csci-3081-s21/shared-upstream/tree/support-code/labs/Lab14_Strategy_Drone_Routes 
*
* 2. Lectures 19 & 20 on the strategy pattern:
*
*       a. Lecture 19: https://canvas.umn.edu/courses/217398/files/20413893?module_item_id=5865925 
*
*       b. Lecture 20: https://canvas.umn.edu/courses/217398/files/20471109?module_item_id=5873223
*
* 3. YouTube Video on Riemann Sums: https://www.youtube.com/watch?v=XrMSfljzBRg 
* 
* 4. PowerPoint Slides on Building a Better Jump: http://www.mathforgameprogrammers.com/gdc2016/GDC2016_Pittman_Kyle_BuildingABetterJump.pdf 
*
* 5. Head First Design Patterns Textbook from the UMN Library: https://primo.lib.umn.edu/primo-explore/search?query=any,contains,head%20first%20design%20patterns&search_scope=mncat_discovery&vid=TWINCITIES&lang=en_US 
*
*/