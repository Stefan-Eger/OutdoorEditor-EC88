#include "OEInclude.h"


namespace oe {
	EditingBrush::EditingBrush() : radius{ 2.5 }, strength{ 1.0f }{}

	EditingBrush::EditingBrush(const float& radius, const float& strength)
	{
		this->radius = radius < RADIUS_MIN ? RADIUS_MIN :  radius > RADIUS_MAX ? RADIUS_MAX : radius;
		this->strength = strength < STRENGTH_MIN ? STRENGTH_MIN : strength > STRENGTH_MAX ? STRENGTH_MAX : strength;
	}

	void EditingBrush::increaseRadius()
	{
		float newVal = radius + RADIUS_STEP;
		radius = newVal > RADIUS_MAX ? RADIUS_MAX : newVal;
	}
	void EditingBrush::decreaseRadius()
	{
		float newVal = radius - RADIUS_STEP;
		radius = newVal < RADIUS_MIN ? RADIUS_MIN : newVal;
	}
	void EditingBrush::setStrength(const float& strength)
	{
		this->strength = strength < STRENGTH_MIN ? STRENGTH_MIN : strength > STRENGTH_MAX ? STRENGTH_MAX : strength;
	}
	float EditingBrush::getStrength() const
	{
		return strength;
	}
	float EditingBrush::getRadius() const
	{
		return radius;
	}
	
}