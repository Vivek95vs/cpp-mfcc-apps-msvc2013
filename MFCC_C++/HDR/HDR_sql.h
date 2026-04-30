#pragma once

#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <string>
#include <sql.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <opencv2/opencv.hpp>


class HDRsql
{
public:
	HDRsql();
	~HDRsql();

	double radius;
	double refer1, refer2;
	double topPixel_x, topPixel_y, bottomPixel_x, bottomPixel_y, epsilonfraction;
	double SCenter;
	cv::Mat cameraMatrix;

	void connectdatabase();
	void readData();
	void readData1();
	bool insertData(double value1, double value2, double value3, double value4);
	void disconnect();

};
