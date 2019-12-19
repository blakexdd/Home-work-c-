#pragma once
#include<string>
#include <vector>


class Storage_unit
{
private:
	std::string name;
	double memory;
	double remains_memory;
	double price_per_gb;

public:

	Storage_unit();


	Storage_unit(std::string name, double memory, double price_per_gb);

	virtual void set_name(std::string name);


	virtual void set_memory(double memory);

	virtual void set_price_per_gb(double price_per_gb);

	virtual double get_price_per_gb();

	virtual void reset_memory();

	virtual std::string get_name();

	virtual double get_memory();

	virtual void allocate_memory(double wanted_memory);

	virtual double get_remains_memory();
};

class DataCenter : public Storage_unit
{
private:
	std::string location;
	static std::vector<DataCenter> dclist;
public:

	DataCenter();

	DataCenter(std::string, std::string, double, double);

	void set_location(std::string location);

	static std::vector<DataCenter> get_dclist();

	static void add_dclist(DataCenter);

	std::string get_location();
};

