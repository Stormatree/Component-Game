#include "Brain.hpp"

Brain::~Brain(){
	_network.destroy();
}

void Brain::load(){
	_transform = getComponent<Transform>();
	_movement = getComponent<Movement>();
	_feeder = getComponent<Feeder>();
	
	_network.create_from_file("../data/simple_training.net");
}

float Brain::_changeRange(float oldMin, float oldMax, float newMin, float newMax, float oldValue){
	return (((oldValue - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}

void Brain::update(double dt){
	// Nearest input
	glm::vec3 nearest = _feeder->nearestFood();

	glm::vec3 difference = glm::normalize(_transform->position() - nearest);
	
	float differenceAngle = glm::atan(difference.x, difference.y);
	float facingAngle = glm::eulerAngles(_transform->rotation()).z;

	_nearestFood = glm::abs(glm::degrees(facingAngle + differenceAngle));

	if (glm::sign(_nearestFood) == -1.f)
		_nearestFood += 360;

	_nearestFood = _changeRange(0, 360, -1, 1, _nearestFood);
	
	// Eating input
	if (_feeder->eating())
		_eating = 1.f;
	else
		_eating = -1.f;

	// FANN running
	fann_type inputs[2] = { _nearestFood, _eating };

	fann_type* output;

	output = _network.run(inputs);

	// Feeding outputs to movement
	_movement->left(output[0]);
	_movement->right(output[1]);
	_movement->forward(output[2]);
		
	// REMOVE THIS
	//std::string name = EntityManager::nameBank().getName(id());
	
	//if (name != "player")
	//	return;
	
	//message_out("%f %f\n", _nearestFood, _eating);
	//message_out("%f %f %f\n", output[0], output[1], output[2]);
}