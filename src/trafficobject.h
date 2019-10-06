#ifndef TRAFFICOBJECT_H
#define TRAFFICOBJECT_H

#include <vector>
#include <thread>

enum ObjectType
{
	noObject,
	objectVehicle,
	objectIntersection,
	objectStreet,
};

class TrafficObject
{
public:
	TrafficObject();
	~TrafficObject();

	// getter and setter
	int getID() { return _id; }
	void setPosition(double x, double y);
	void getPosition(double &x, double &y);
	ObjectType getType() { return _type; }

	// typical behaviour methods
	virtual void simulate() {};

protected:
	ObjectType _type;
	int _id;
	double _posX, _posY;
	std::vector<std::thread> threads;

private:
	static int _inCnt;
};

#endif // !TRAFFICOBJECT_H
