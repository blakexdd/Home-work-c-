#define _CRT_SECURE_NO_WARNINGS
#include "Sources_Consumers.h"
#include <iostream>

Person::Person(std::string name, std::string surname, std::string middlename, std::string date_of_birth)
{
	this->name = name;
	this->surname = surname;
	this->middlename = middlename;
	this->date_of_birth = date_of_birth;
}

std::string Person::get_goods_info()
{
	std::stringstream st;

	st << "This function print goods of the person";

	return st.str();
}


void Person::set_name(std::string name)
{
	this->name = name;
}

void Person::set_surname(std::string surname)
{
	this->surname = surname;
}

void Person::set_middlename(std::string middlename)
{
	this->middlename = middlename;
}

void Person::set_date_of_birth(std::string date_of_birth)
{
	this->date_of_birth = date_of_birth;
}

std::string Person::get_name()
{
	return name;
}

std::string Person::get_surname()
{
	return surname;
}

std::string Person::get_middlename()
{
	return middlename;
}

std::string Person::get_date_of_birth()
{
	return date_of_birth;
}

int Person::person_age()
{
	std::string v;
	std::stringstream st(date_of_birth);

	time_t t = time(NULL);
	tm* timePtr = localtime(&t);

	int age;


	for (int i = 0; i < 3; i++)
		getline(st, v, '.');

	age = timePtr->tm_year + 1900 - stoi(v);

	return age;
}

Consumer::Consumer(std::string name, std::string surname, std::string middlename,
	std::string date_of_birth, double money, std::string wanted_datacenter = " ", double wanted_memory = 0) :
Person::Person(name, surname, middlename, date_of_birth)
{
	this->money = money;
	this->wanted_datacenter = wanted_datacenter;
	this->wanted_memory = wanted_memory;
}

std::string Consumer::buy_datacenter_memory(std::string datacenter_name, double memory)
{
	DataCenter buy_datacenter;
	std::stringstream st;

	std::cout << "Person money: " << this->money << std::endl;
	std::cout << "Person memory: " << memory << std::endl;

	for (auto datacenter : DataCenter::get_dclist())
		if (datacenter.get_name() == datacenter_name)
			buy_datacenter = datacenter;

	std::cout << "Buy dc price per gb: " << buy_datacenter.get_price_per_gb() << std::endl;

	double price = memory * buy_datacenter.get_price_per_gb();

	std::cout << "Price " << price << std::endl;

	if (buy_datacenter.get_remains_memory() <= memory)
		return std::string("Not enought memory at datacenter");

	if (this->money >= price)
	{
		this->money -= price;
		buy_datacenter.allocate_memory(memory);

		st << "Покупка совершена, остаток на счёте: " << this->money;
	}
	else
	{
		st << "Недостаточно средств на счёте";
	}

	return st.str();
}

void Consumer::set_wanted_datacenter(std::string wanted_datacenter)
{
	this->wanted_datacenter = wanted_datacenter;
}

void Consumer::set_wanted_memory(double wanter_memory)
{
	this->wanted_memory = wanted_memory;
}

std::string Consumer::get_wanted_datacenter()
{
	return wanted_datacenter;
}

double Consumer::get_wanted_memory()
{
	return wanted_memory;
}

std::string Consumer::get_goods_info()
{
	std::stringstream st;

	st << "Amount of " << this->get_name() << " " << this->get_surname() << " money is: " << money;

	return st.str();
}

void Consumer::set_money(double money)
{
	this->money = money;
}

double Consumer::get_money()
{
	return money;
}

std::vector<DataCenter> DataCenter::dclist = {};

Owner::Owner(std::string name, std::string surname, std::string middlename,
	std::string date_of_birth, std::vector<DataCenter> datacenters) :
	Person::Person(name, surname, middlename, date_of_birth)
{
	this->datacenters = datacenters;
	datacenters_amount = datacenters.size();

	for (auto dc : datacenters)
		DataCenter::add_dclist(dc);
}

void Owner::add_datacenter(DataCenter newDataCenter)
{
	datacenters.push_back(newDataCenter);
	datacenters_amount++;
}

void Owner::delete_datacenter(DataCenter deleteDataCenter)
{
	std::vector<DataCenter>::iterator it;

	for (it = datacenters.begin(); it != datacenters.end(); it++)
	{
		if (it->get_name() == deleteDataCenter.get_name())
			it = datacenters.erase(it);
		else
			++it;
	}

	datacenters_amount--;
}

void Owner::set_datacenters(std::vector<DataCenter> datacenters)
{
	this->datacenters = datacenters;
}

std::string Owner::get_goods_info()
{
	std::stringstream st;

	st << this->get_name() << " " << this->get_surname() << " has " << datacenters_amount << " datacenters";

	return st.str();
}

void Owner::set_datacenters_amount(int datacenters_amount)
{
	this->datacenters_amount = datacenters_amount;
}

double Owner::get_datacenters_amount()
{
	return datacenters_amount;
}

std::vector<DataCenter> Owner::getdatacenters()
{
	return datacenters;
}