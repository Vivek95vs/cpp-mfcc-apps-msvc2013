#pragma once


#include <opencv2/opencv.hpp>
#include <string.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include<vector>
#include<Windows.h>
#include<chrono>
#include <time.h>
#include <direct.h>
#include <string>
#include "Arena\ArenaApi.h"
#include "Save\SaveApi.h"
#include "GenICam.h"

using namespace std;

class HDR
{
	int rect_cnt;
	int img_wd_req;							//!<  colomns requested to camera
	int img_ht_req;
	int img_wd;							//!<  numbr of colmns in image to be processed(image transformed from trapezoid to rectangle) 
	int img_ht;
	int flipX, flipY, exposure_factor;
	int Brightness, Gain, BlackLevel, ExposureTime, Redchannel, greenchannel, bluechannel;
	string A1;
	int restore_track;

	int thickLeafHt;					//!< thick leaf height
	int thinLeafHt;						//!< thin leaf height
	int leafHtError;

	int morph_width;
	int morph_height;
	int queCount_max_calib;					//!< maximum size of que (sets a limit)
	int queCount_max_running;

	double oneLeafArea;
	double flipParam;
	double rotateParam;
	double centerTol;
	double contourMin;
	double contourMax;

	int y_margin;
	int x_margin;
	int close_wd, close_ht;
	bool display_field;
	int wait;


	int calibWidth = 0;
	int calibHeight = 0;



	cv::Mat cameraMatrix;		//!<  Matrix from caliberating using checker pattern (maps from distorted to undistorted)
	cv::Mat distCoeffs;

	std::vector<Arena::DeviceInfo> deviceInfos;
	Arena::ISystem* pSystem;
	Arena::IImage* pConvert;
	Arena::IDevice* pDevice;
	GenICam::gcstring devicename;



	int ROI_Update;
	BOOL success/*, status*/;
	BOOL setROI_gigE(/*SapAcqDevice *pAcq,*/ UINT32 X, UINT32 Y, UINT32 Wd, UINT32 Ht);
	BOOL reverseX(BOOL revX);
	BOOL reverseY(BOOL revY);

	int OffX_roi, OffY_roi, Width_roi, Height_roi;


	BOOL setBlackLevel(double val);
	BOOL setExposureTime(DOUBLE ExposureTime);
	BOOL setGain(double G_val);
	//BOOL setRed(double G_val);
	//BOOL setGreen(double G_val);
	//BOOL setblue(double G_val);
	int grabFrame(cv::Mat& frameA);

	std::string currentDateTime_grabber();



public:
	cv::Point topRedPixel, bottomRedPixel;
	cv::Mat img1, img2;
	cv::Mat refImage, calibImage;
	cv::Mat diffImage;
	std::string VersionNumber = "v_1.0.0";

	double minRadius;
	double ref1, ref2;
	double uppixel_x, uppixel_y, downpixel_x,downpixel_y, epsilonfrac;
	double SourceCenter;
	cv::Mat matrix;
	double lengthInMillimeters;
	double pixelLength = 0;
	double pixel_distance;
	double scale_distance;
	double conversionFactor;
	double pipelength;
	std::string filePath, filename;

	/** constructor   */
	HDR();
	/** destructor XOXO  */
	~HDR();


	void startsystem();




	int caliblength();
	double loadimage(int value);
	void findlength(const cv::Mat, const cv::Mat& img2);
	void showDifference(const cv::Mat, const cv::Mat& img2, cv::Mat& diffImage);
	double pixelToMillimeter(double pixelLength, double conversionFactor);
	//double calculateLineLength(const cv::Mat& binaryImage);
	double calculateContourLength(const std::vector<cv::Point>& contour);
	bool isContourLargeEnough(const std::vector<cv::Point>& contour, double minRadius);
	void removeNoiseByRadius(const cv::Mat& diffImage, cv::Mat& filteredImage, double minRadius);




};