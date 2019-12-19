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

	void set_name(std::string name);

	void set_memory(double memory);

	void set_price_per_gb(double price_per_gb);

	virtual void info();

	double get_price_per_gb();

	void reset_memory();

	std::string get_name();

	double get_memory();

	void allocate_memory(double wanted_memory);

	double get_remains_memory();

	virtual void show_unit_type() = 0;
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

	virtual void info();

	static std::vector<DataCenter> get_dclist();

	void show_unit_type();

	static void add_dclist(DataCenter);

	static void delete_dclist(DataCenter);

	std::string get_location();
};

