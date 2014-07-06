#ifndef CAMERA_H_
#define CAMERA_H_

#include "vector.h"

class Camera {
public:
	Camera(Vector pos = Vector(0,0,0), Vector dir = Vector(0,0,-1), Vector up = Vector(0,1,0))
		: _pos(pos), _dir(dir), _up(up) {};
	~Camera() {};

	const Vector pos()   { return _pos; };
	const Vector dir()   { return _dir; };
	const Vector up()    { return _up;  };
	const Vector right() { return _dir % _up; };
private:
	Vector _pos;
	Vector _dir;
	Vector _up;
};

#endif /* CAMERA_H_ */
