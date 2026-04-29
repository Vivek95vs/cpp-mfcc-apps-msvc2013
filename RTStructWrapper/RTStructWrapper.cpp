// This is the main DLL file.
#include "stdafx.h"

#include "RTStructWrapper.h"
#include "fstream"
#include "iostream"

using namespace std;

RTStructWrapper::structRT::structRT()
{
	structrt = new WriteRTStruct();
}

RTStructWrapper::structRT::~structRT()
{
	
	delete structrt;

}

RTStructWrapper::structRT::!structRT()
{
	this->!structRT;
}

void RTStructWrapper::structRT::structfun()
{
	std::string contours;
	std::string	SOPInstanceUID1;
	std::string	SOPInstanceUID2;
	std::string SOPInstanceUID3;
	std::string SOPInstanceUID4;
	std::string SOPInstanceUID5;
	std::string SOPInstanceUID6;
	std::string Requiredetails;

	structrt->RTStruct(contours, SOPInstanceUID1, SOPInstanceUID2, SOPInstanceUID3, SOPInstanceUID4, SOPInstanceUID5, SOPInstanceUID6, Requiredetails);

}
