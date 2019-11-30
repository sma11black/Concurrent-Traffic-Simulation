#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <random>

#include "Street.h"
#include "Vehicle.h"
#include "Intersection.h"

Intersection::Intersection()
{
	_type = ObjectType::objectIntersection;
	_isBlocked = false;
}

void Intersection::setIsBlocked(bool isBlocked)
{
	_isBlocked = isBlocked;
	//std::cout << "Intersection #" << _id << " isBlocked=" << isBlocked << std::endl;
}

void Intersection::addStreet(std::shared_ptr<Street> street)
{
	_streets.push_back(street);
}

std::vector<std::shared_ptr<Street>> Intersection::queryStreets(std::shared_ptr<Street> incoming)
{
	// store all outgoing streets in a vector
	std::vector<std::shared_ptr<Street>> outgoings;
	for (auto it : _streets)
	{
		if (incoming->getID() != it->getID())	// except the street making the inquiry
		{
			outgoings.push_back(it);
		}
	}
	return outgoings;
}

// adds a new vehicle to the queue and returns once the vehicle is allowed to enter
void Intersection::addVehicleToQueue(std::shared_ptr<Vehicle> vehicle)
{
	// Task: Ensure that the text output locks the console as a shared resource.
	std::unique_lock<std::mutex> lck(_mtx);
	std::cout << "Intersection #" << _id << "::addVehicleToQueue: thread id = " << std::this_thread::get_id() << std::endl;
	lck.unlock();
	
	// Task: add new vehicle to the end of the waiting line
	std::promise<void> prmsVehicleAllowedToEnter;
	std::future<void> ftrVehicleAllowedToEnter = prmsVehicleAllowedToEnter.get_future();
	_waitingVehicles.pushBack(vehicle, std::move(prmsVehicleAllowedToEnter));

	// Task: wait until the vehicle is allowed to enter
	ftrVehicleAllowedToEnter.wait();
	lck.lock();
	std::cout << "Intersection #" << _id << ": Vehicle #" << vehicle->getID() << " is granted entry." << std::endl;
	lck.unlock();
}

// virtual function which is executed in a thread
void Intersection::simulate()
{
	// using threads + promises/futures + exceptions
	// launch vehicle queue processing in a thread
	threads.emplace_back(std::thread(&Intersection::processVehicleQueue, this));
}

void Intersection::vehicleHasLeft(std::shared_ptr<Vehicle> vehicle)
{
	//std::cout << "Intersection #" << _id << ": Vehicle #" << vehicle->getID() << " has left." << std::endl;
	this->setIsBlocked(false);
}

bool Intersection::trafficLightIsGreen()
{
	return false;
}

void Intersection::processVehicleQueue()
{
	//std::cout << "Intersection #" << _id << "::processVehicleQueue: thread id = " << std::this_thread::get_id() << std::endl;
	// continuously process the vehicle queue
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		
		if (_waitingVehicles.getSize() > 0 && !_isBlocked)
		{
			// set intersection to "blocked" to prevent other vehicles from entering
			this->setIsBlocked(true);
			// permit entry to first vehicle in the queue (FIFO)
			_waitingVehicles.permitEntryToFirstInQueue();
		}
	}
}

// Task: Safeguard all accesses to the private members _vehicles and _promises with an appropriate locking mechanism
int WaitingVehicles::getSize()
{
	std::lock_guard<std::mutex> lock(_mutex);

	return _vehicles.size();
}

void WaitingVehicles::pushBack(std::shared_ptr<Vehicle> vehicle, std::promise<void>&& promise)
{
	std::lock_guard<std::mutex> lock(_mutex);

	_vehicles.push_back(vehicle);
	_promises.push_back(std::move(promise));
}

void WaitingVehicles::permitEntryToFirstInQueue()
{
	std::lock_guard<std::mutex> lock(_mutex);

	// Task: get the entries from the front of _promises and _vehicles queues.
	auto firstPromise = _promises.begin();
	auto firstVehicle = _vehicles.begin();

	// Task: fulfill promise and send signal back that permission to enter has been granted.
	firstPromise->set_value();

	// Task: remove the front elements from both queues.
	_vehicles.erase(firstVehicle);
	_promises.erase(firstPromise);
}
