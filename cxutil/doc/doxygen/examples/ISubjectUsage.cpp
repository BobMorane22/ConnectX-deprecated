Incrementer subject;

ChecksForIncrement    observer1;
CopiesIncrementerData observer2;

// Registration:
subject.registerObserver(&observer1);
subject.registerObserver(&observer2);

// Observers updated:
subject.increment();

std::cout << observer1.hasBeenIncremented(); // Prints 1
std::cout << observer2.data();               // Prints 1

// Observers updated again:
subject.increment();

std::cout << observer1.hasBeenIncremented(); // Prints 1
std::cout << observer2.data();               // Prints 2
