#include "Clr.h"
#include <opencv2/opencv.hpp>
#include<iostream>
#include <experimental/filesystem>
#include "D:\\chaitanya\\HDR scaling image\\HDR with sql\\HDR_MAIN_CODE\\HDR\\HDR\\HDR.cpp"
#include "D:\\chaitanya\\HDR scaling image\\HDR with sql\\HDR_MAIN_CODE\\HDR\\HDR\\HDR_sql.cpp"

namespace hdr_clr {



	HDR_CLR::HDR_CLR() {
		hdr = new HDR();
	}

	HDR_CLR::~HDR_CLR() {
	
	}
	HDR_CLR::!HDR_CLR() {

	}

	int HDR_CLR::caliblengthandpixels() {
		cal=hdr->caliblength();
		return cal;
	}
	double HDR_CLR::loadingimages(int value) {
		leng=hdr->loadimage(value);

		HDR_Path = gcnew System::String(hdr->filePath.c_str());

		return leng;
	}
	
}