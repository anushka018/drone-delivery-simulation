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
*
*
* Team Documentation
* 
* Roles:
*
* Scheduler: Anushka
* 
* Reporter: Lara
* 
* Project Manager: Anoushka
* 
* Development Lead: Audrey
*
*
*
* Meeting Notes:
*
*
* March 24th, 2021
*
*
* Today we had our first team meeting for iteration two. The majority of the time was spent planning for how we will structure our meetings going forward and roles that we will each take on. After reviewing the Iteration Two requirements, we decided on whose code we will be using as the base for moving forward. We will be using Audrey's code from Iteration One moving forward, while also using pieces of other member's code, like Anoushka's beeline path code. We walked through Audrey's code and UML diagram to gain a better understanding of how she constructed her project and make sure we were all on the same page. The rest of our time we assigned each member a role, as specified in previous instructions, and broke up the priorities for the first deliverable. In order to stay ahead and ensure we have enough time, we decided that everyone would finish their own piece of the first deliverable by the Wednesday before it is due. We have planned to have group meetings throughout that time so we can work through any bugs together, but have also set aside time for us to work on our respective priorities. For the first deliverable, Audrey will be creating the robots, Lara and Anushka will work together on the Observer packages, and Anoushka will work on the drone and robot observers. We are planning our next meeting after the lab has been posted so that we can check in on the progress that everyone has made.
*
*
* March 28th, 2021
*
*
* Since the last time that we met Lab 13 has been posted, so we have been able to set up our team repository and learn how to submit requests and accept them. Today was mainly spent working together through issues that came up during the time we spent working on our own priorities. Audrey was able to get the robot class working smoothly, as much of the code she had already completed successfully in her drone class. Much of the work we did was on the observer class and figuring out how to piece together the abstract classes and the concrete classes. We were able to problem solve by looking through past lectures, piazza posts and by walking through the code together. While we didn't finish the observer package and drone today, we are in a good position and have time to fix things before the first deliverable is due.
*
*
* March 30th, 2021
*
*
* Today was spent finishing up the requirements for the first deliverable and planning for the next, as we got done several days in advance. We figured out that we were good on Google tests for this deliverable and didn't need to add anything for that. The main pieces that we still needed to figure out were the observer classes. An issue we ran into last time was how to connect the observers to the entities which we were able to figure out today. Along with that we were able to get the correct print statements, we were previously getting "en route" to print continuously. To get this to work we had to change the package carrier class to only check for the pick up once, which required slight adjustments to the logic. After we finished the package observer, we began to work on the drone observer. We were able to get the print statments to work but still have some work left to do on getting the path to work correctly. We will finish that up in our meeting tomorrow, and should be able to turn it it after that.
*
*
* March 31st, 2021
*
*
* Today we turned in the first deliverable! We were able to finish up the drone observer that we had yet to complete from yesterday. We tested it a few more time to make sure everything was working correctly and double checked to make sure we had all of the requirements before pushing our first deliverable. We then began to plan for the final deliverable of this iteration. Because spring break is next week and we won't have much time once we get back, we have decided to meet a few times as a group to work through the final deliverable. We wanted to take this approach so that we can hopefully get through the priorities faster by having several brains working through it at once. Moving forward, Anushka will send out another WhenToMeet so we can set up some meeting times and then next week we will work on getting ahead so the last few weeks of the semester aren't too stressful.
*
*
* April 6th, 2021
*
*
* Today we had our first meeting over spring break to work on Iteration 2 Final Deliverable. Most of the time today was spent on creating the different types of paths. We already had the smart route working from Audrey's Iteration 1 code and were able to get the parabolic path to work as well. Towards the end of our meeting we ran into a segfault that we couldn't quite figure out, so we decided to end the meeting for the day and come back fresh tomorrow. Later that day Audrey found that the segfault was being caused by a missing return statement.
*
*
* April 7th, 2021
*
*
* Today we were able to get both the parabolic and the beeline route paths to work. The beeline path that we used in this portion of the code came from Anoushka's Iteration 1 cocde. We had to make some adjustments to her original code and work through the errors that came up, but after that the beeline was working correctly. We then started on Priority 4. The first bullet point was already completed in our code so we began working on idle drones and how to reschedule them.
*
*
*
* Observer Pattern Design Discussion
* 
*
* First, we created an abstract class called ASubject which implements the subject component of the observer pattern. In this class, we created a vector which contains a list of pointers to entity observers. Then, we wrote the attach and detach methods which add and remove an observer from that vector. Finally, we added a notify method which iterates through the observers vector calling the OnEvent method for each observer in the vector.
*
*
* Next, in delivery simulation, we filled in the implementation for the add and remove observer methods which add and remove IEntityObservers from the observer vector. 
*
*
* Finally, in a class called package carrier which currently represents drones and robots, we implemented the notifications to the observers. In terms of the package, we created a notification when the package had been scheduled, picked up and was on route, or had been delivered. On the side of the package carrier (drones or robots), we created a notification when the package carrier was moving toward the customer, moving toward the package, or had entered an idle state because it ran out of battery. In the cases where the package carrier was moving, we also displayed the route it was following - either to the package or to the customer.
*
*
* In order to implement the creation of these notifications, we created a new picojson::value eventValue object which was assigned to calling the create notification method with the type of message and the route in the cases where the package carrier is moving. Then, we called our notify function with the event value and a pointer to the package carrier (robot or drone) or the package. 
*
*
*
*
* Drone Battery Life Decorator Feature Discussion
*
* Our team chose to utilize the decorator pattern to implement a decorator for drones based on their battery life. The decorator pattern is useful because it allows for the addition of new features to objects in an existing system without the need to modify its underlying structure. These behaviors are added dynamically and can be modified at any point which allows for much greater flexibility. It also prevents code redundancy by allowing us to utilize composition rather than inheritance. In the case of using inheritance to implement new features, an entirely new object would need to be created. Finally, the decorator pattern allows our code to adhere to the single responsibility principle and the open/closed principle following good software design practices.
* 
* Scene files that the feature works on: 
* 
* In order to implement the decorator pattern, you must create a child class of the abstract component class which will serve as the decorator interface. Then, In this abstract class, you must add a pointer to the abstract component class as a private instance variable to utilize composition. In addition, you must initialize this pointer and forward all methods to it. Finally, a concrete decorator class must be created which inherits from the abstract decorator class. In this class, you need to override any methods from the component abstract class that you would like to modify using the decorator pattern.  
* 
* 
* Generic Decorator Pattern UML
* 
* ![Decorator Pattern UML](../images/DecoratorPattern.png)
* 
* 
* 
* 
* Battery Life Drone Decorator Pattern UML
*
* ![Drone Battery Life Decorator Pattern UML](../images/DroneDecoratorPattern.png)
*
*
*
* 
* Within the new drone decorator class, we stored an instance of a Drone* in order to utilize the composition required for the decorator pattern. Since the drone decorator class inherits from package carrier, we needed to include declarations of that parent classes method which was done through the stored Drone*. This pointer was used in each of the function bodies to call their appropriate methods from the package carrier class using the arrow operator for pointer dereferencing( ->).  The only exception to these definitions was in the update function for the drone decorator class. In, the update function, the Drone* update function was called. Decorating of the drone entities color was also implemented as well. This was done through a series of if-else branches. First, the drone’s current battery was found. Next, a reference to the picojson drone object was stored to be modified. Within each of the if-else statements, the current battery value of the drone was compared against values for battery level ranges corresponding to different colors. We had 6 different colors to represent the color of the drone’s battery life. The ranges for each of these values was determined by splitting them equiavl;ently amongst the range 0 - 10,000 where 10,000 is the battery’s maximum capacity. Please refer to the image below to view the 6 colors along with their hex values and the breakdown for each of the ranges of battery life. 
* 
*
* Drone Decorator Battery Life Color Breakdown
* 
*  
* ![Battery Life Color Breakdown](../images/BatteryLifeColorBreakdown.png)
* 
*
*
* In addition, within the constructor for the drone decorator class, a preference to the class Droine* member variable was stored.  
* 
* Finally, during the instantiation of a new drone object in drone factory, we created a new drone as a Drone*. Then, we returned an instance of our drone decorator class. This was done using using the Drone* in the constructor of the drone decorator class. 
*
*
* Drone* drone = new Drone(position, direction, modified, name, speed, radius, batteryCapacity, pathType);
* return new DroneDecorator(drone);
* 
* 
* Difficulties & Tips/Advice 
* 
* 
* The most challenging part about implementing the decorator pattern for the drone’s battery life was understanding how to implement the inheritance structure as well as determining how to change the color value of the drone entity in the simulation by modifying its picojson values. Originally, our drone decorator class inherited from the drone class directly, but then we modified the inheritance structure so that it inherited from the package carrier class to more closely resemble the class structure of the decorator pattern. Another aspect of the decorator pattern that was confusing was that we needed to redefine all the methods in the drone decorator class which inherits from the package carrier class. It was slightly confusing at first that this needed to be done and also that it must be done using the Drone* in our drone decorator class and the arrow operator for pointer dereferencing. Finally, the other major difficulty was updating the color or the drone entity in the simulation. This was confusing because we were unsure how to interact with the front end support code to modify the hexadecimal color value of the drone in the simulation. At first, after looking at the json configuration files and seeing color as a parameter, we thought we may have needed to modify the json files directly. However, we got a lot more clarity once we realized we could use the update string value function from the json helper class. This made things much easier as we could directly set the color attribute of our drone entities using a hexadecimal color value as a string. 
*
*
* Some resources that really helped along the way were the slides on color coding entities, the decorator pattern example posted by a TA, the head first design textbook, and the class lecture posted on the decorator pattern. The slide on color coding entities helped clarify that we must set the color using the syntax: 
* 
* 
* details_["color"] = picojson::value("0x0000ff"); // where 0x... is the color
* 
* It also made us aware of the fact that we must invoke the observer in order for the record to change. This slide is titled “Color coding your entities” and can be found in the adapter pattern lecture linked below.
* 
* The example posted by the TA was extremely useful in helping us understand how the inheritance structure worked for the decorator pattern, especially because it provided an example that related more closely with the context of this project. Finally, some helpful resources for understanding the decorator pattern are linked below as well. 
*
*
* Links to resources mentioned above
* 
* 
* 1. Slideshow with slide on adding color to entities: https://canvas.umn.edu/courses/217398/files/20874077?module_item_id=5928287 
*
* 2. Decorator pattern inheritance structure example: https://canvas.umn.edu/courses/217398/files/20956519?module_item_id=5939856 
*
* 
*
* Understanding the decorator pattern
* 
* 
* 1. Head First Design Patterns Textbook from the UMN Library: https://primo.lib.umn.edu/primo-explore/search?query=any,contains,head%20first%20design%20patterns&search_scope=mncat_discovery&vid=TWINCITIES&lang=en_US 
*
* 2. Lecture on the decorator pattern: https://canvas.umn.edu/courses/217398/external_tools/24 
*
* 3. Slides on the decorator pattern: https://canvas.umn.edu/courses/217398/files/20650005?module_item_id=5897942 
* 
* 4. Decorator pattern example from Tutorials Point: https://www.tutorialspoint.com/design_pattern/decorator_pattern.htm
*
* 5. Decorator pattern Youtube video with code example: https://www.youtube.com/watch?v=j40kRwSm4VE 
* 
*
*/
