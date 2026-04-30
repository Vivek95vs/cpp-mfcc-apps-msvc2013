#pragma once

#include "D:\\chaitanya\\HDR scaling image\\HDR with sql\\HDR_MAIN_CODE\\HDR\\HDR\\\\HDR.h"
#include "D:\\chaitanya\\HDR scaling image\\HDR with sql\\HDR_MAIN_CODE\\HDR\\HDR\\HDR_sql.h"
using namespace System;


namespace hdr_clr {

	public ref class HDR_CLR
	{
	public:

		HDR_CLR();

		~HDR_CLR();
		!HDR_CLR();

		int cal; 
		double leng;
		System::String^ HDR_Path;

		int caliblengthandpixels();
		double loadingimages(int value);

    private:
		HDR * hdr;
	};
}