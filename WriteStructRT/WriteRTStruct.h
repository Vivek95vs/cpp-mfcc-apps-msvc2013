#pragma once
#include "iostream"


class WriteRTStruct
{
public:
	WriteRTStruct();
	~WriteRTStruct();	

	std::string dicomDate();
	std::string dicomTime();

	void RTStruct(std::string contours, std::string SOPInstanceUID1, std::string SOPInstanceUID2, std::string SOPInstanceUID3, std::string SOPInstanceUID4, std::string SOPInstanceUID5, std::string SOPInstanceUID6,std::string Requiredetails);
};

