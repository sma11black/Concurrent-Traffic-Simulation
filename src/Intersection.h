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

class Intersection : public TrafficObject
{
public:
	Intersection();

	// typical behaviour methods
	void addStreet(std::shared_ptr<Street> street);
	std::vector<std::shared_ptr<Street>> queryStreets(std::shared_ptr<Street> incoming);	// return pointer to current list of all outgoing streets

private:
	std::vector<std::shared_ptr<Street>> _streets;
};

#endif // !INTERSECTION_H
