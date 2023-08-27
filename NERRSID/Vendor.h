#pragma once

#include <string>

#include "Entity.h";

class Vendor : public Entity
{
public:
	Vendor(std::string vendorName, int vendorPosX, int vendorPosY);
	~Vendor();
};

