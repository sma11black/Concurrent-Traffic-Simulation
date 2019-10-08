#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <future>
#include <mutex>
#include <memory>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Street;
class Vehicle;

class WaitingVehicles
{
public:
	int getSize();

	// typical behaviour methods
	void pushBack(std::shared_ptr<Vehicle> vehicle, std::promise<void> &&promise);
	void permitEntryToFirstInQueue();

private:
	std::vector<std::shared_ptr<Vehicle>> _vehicles;	// list of all vehicles waiting to enter this intersection
	std::vector<std::promise<void>> _promises;	// list of associated promises
};

class Intersection : public TrafficObject
{
public:
	Intersection();

	void setIsBlocked(bool isBlocked);

	// typical behaviour methods
	void addStreet(std::shared_ptr<Street> street);
	std::vector<std::shared_ptr<Street>> queryStreets(std::shared_ptr<Street> incoming);	// return pointer to current list of all outgoing streets
	void addVehicleToQueue(std::shared_ptr<Vehicle> vehicle);
	void simulate();
	void vehicleHasLeft(std::shared_ptr<Vehicle> vehicle);
	bool trafficLightIsGreen();

private:
	// typical behaviour methods
	void processVehicleQueue();

	std::vector<std::shared_ptr<Street>> _streets;	// list of all streets connected to this intersection
	WaitingVehicles _waitingVehicles;	// list of all vehicles and their associated promises waiting to enter the intersection
	bool _isBlocked;	// flag indicating wether the intersection is blocked by a vehicle
};

#endif // !INTERSECTION_H
