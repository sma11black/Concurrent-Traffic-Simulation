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
};

#endif // !INTERSECTION_H
