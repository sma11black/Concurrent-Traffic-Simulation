#include <iostream>
#include <chrono>
#include <algorithm>
#include "TrafficObject.h"

// init static variable
int TrafficObject::_idCnt = 0;

std::mutex TrafficObject::_mtx;

TrafficObject::TrafficObject()
{
	_type = ObjectType::noObject;
	_id = _idCnt++;
}

TrafficObject::~TrafficObject()
{
	// Task: Set up a thread barrier that ensures that all the thread objects in the member vector _threads are joined.
	std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
		t.join();
	});
}

void TrafficObject::setPosition(double x, double y)
{
	_posX = x;
	_posY = y;
}

void TrafficObject::getPosition(double & x, double & y)
{
	x = _posX;
	y = _posY;
}
