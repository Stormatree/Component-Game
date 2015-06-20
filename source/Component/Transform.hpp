#pragma once

#include "Base.hpp"

#include "Math\Vector3.hpp"

class Transform : public Component{
	Vector3f _position;
	Vector3f _euler;

public:
	Transform(){
		_position = Vector3f(0.f, 0.f, 0.f);
		_euler = Vector3f(0.f, 0.f, 0.f);
	}

	Component* clone(){
		Transform* transform = new Transform();
		transform->_position = _position;
		transform->_euler = _euler;
		return transform;
	}

	Vector3f position(){
		return _position;
	}

	Vector3f euler(){
		return _euler;
	}

	Vector3f position(Vector3f vector){
		_position = vector;
		return _position;
	}

	Vector3f euler(Vector3f vector){
		_euler = vector;
		return _euler;
	}

	void translate(Vector3f vector){
		_position += vector;
	}

	void transform(Vector3f vector){
		_euler += vector;
	}
};