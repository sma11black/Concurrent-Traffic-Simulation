#include <iostream>
#include <thread>
#include <vector>

#include "Vehicle.h"
#include "Street.h"
#include "Intersection.h"
#include "Graphics.h"

// NYC
void createTrafficObjects(std::vector<std::shared_ptr<Street>> &streets, std::string &filename, int nVehicles)
{
	// assign filename of corresponding city map
	filename = "../data/nyc.jpg";
}

int main()
{
	/* PART 1 : Set up traffic objects */

	// create and connect intersections and streets
	std::vector<std::shared_ptr<Street>> streets;
	std::vector<std::shared_ptr<Intersection>> intersections;
	std::vector<std::shared_ptr<Vehicle>> vehicles;
	std::string backgroundImg;

	/* PART 2 : simulate traffic objects */

	/* PART 3 : Launch visualization */

	return 0;
}
