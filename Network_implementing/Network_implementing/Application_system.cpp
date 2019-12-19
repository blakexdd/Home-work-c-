#define _CRT_SECURE_NO_WARNINGS
#include "Application_subsystem.h"


Storage_unit::Storage_unit()
{

}

Storage_unit::Storage_unit(std::string name, double price_per_gb, double memory = 0)
{
	this->name = name;
	this->price_per_gb = price_per_gb;
	this->memory = memory;
	this->remains_memory = memory;
}

void Storage_unit::set_name(std::string name)
{
	this->name = name;
}

void Storage_unit::set_memory(double memory)
{
	if (this->memory == 0)
		this->memory = memory;
}

void Storage_unit::set_price_per_gb(double price_per_gb)
{
	this->price_per_gb = price_per_gb;
}

double Storage_unit::get_price_per_gb()
{
	return price_per_gb;
}

void Storage_unit::reset_memory()
{
	memory = 0;
}

std::string Storage_unit::get_name()
{
	return name;
}

double Storage_unit::get_memory()
{
	return memory;
}

void Storage_unit::allocate_memory(double wanted_memory)
{
	remains_memory = memory - wanted_memory;
}

double Storage_unit::get_remains_memory()
{
	return remains_memory;
}

std::vector<DataCenter> DataCenter::get_dclist()
{
	return dclist;
}

DataCenter::DataCenter()
{

}

DataCenter::DataCenter(std::string name, std::string location, double price_per_gb, double memory = 0) : Storage_unit(name, price_per_gb, memory)
{
	this->location = location;
}

void DataCenter::set_location(std::string location)
{
	this->location = location;
}

std::string DataCenter::get_location()
{
	return location;
}

void DataCenter::add_dclist(DataCenter d)
{
	dclist.push_back(d);
}
