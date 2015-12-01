#pragma once

#include <Entity\HelperComponent.hpp>

#include "Movement.hpp"
#include "Feeder.hpp"

#include <floatfann.h>
#include <fann_cpp.h>

class Brain : public HelperComponent{
	Transform* _transform = 0;
	Movement* _movement = 0;
	Feeder* _feeder = 0;

	float _nearestFood;
	float _eating;

	FANN::neural_net _network;

	float _changeRange(float oldMin, float oldMax, float newMin, float newMax, float oldValue);

public:
	~Brain();

	void load();
	void update(double dt);
};