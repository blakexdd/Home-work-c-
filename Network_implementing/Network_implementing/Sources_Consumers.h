#pragma once
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
#include "Application_subsystem.h"

class Person
{
private:
	std::string name;
	std::string surname;
	std::string middlename;
	std::string date_of_birth;

public:

	Person(std::string name, std::string surname, std::string middlename, std::string date_of_birth);

	virtual std::string get_goods_info();

	virtual void set_name(std::string name);

	virtual void set_surname(std::string surname);

	virtual void set_middlename(std::string middlename);

	virtual void set_date_of_birth(std::string date_of_birth);

	virtual std::string get_name();

	virtual std::string get_surname();

	virtual std::string get_middlename();

	virtual std::string get_date_of_birth();

	virtual int person_age();

};


class Consumer : public Person
{
private:
	std::string wanted_datacenter;
	double wanted_memory;
	double money;

public:

	Consumer(std::string name, std::string surname, std::string middlename,
		std::string date_of_birth, double money, std::string wanted_datacenter, double wanted_memory);

	std::string buy_datacenter_memory(std::string datacenter, double memory);

	void set_wanted_datacenter(std::string wanted_datacenter);

	void set_wanted_memory(double wanter_memory);

	std::string get_wanted_datacenter();

	double get_wanted_memory();

	virtual std::string get_goods_info();

	void set_money(double money);

	double get_money();

};

class Owner : public Person
{
private:
	std::vector<DataCenter> datacenters;
	int datacenters_amount;

public:
	Owner(std::string name, std::string surname, std::string middlename,
		std::string date_of_birth, std::vector<DataCenter> datacenters);

	void add_datacenter(DataCenter newDataCenter);

	void delete_datacenter(DataCenter deleteDataCenter);

	void set_datacenters(std::vector<DataCenter> datacenters);

	virtual std::string get_goods_info();

	void set_datacenters_amount(int datacenters_amount);

	double get_datacenters_amount();

	std::vector<DataCenter> getdatacenters();
};