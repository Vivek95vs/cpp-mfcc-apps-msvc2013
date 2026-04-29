// RTStructWrapper.h

#pragma once

#include "..\..\WriteStructRt\WriteStructRT\WriteRTStruct.h"
#include "..\..\WriteStructRt\WriteStructRT\WriteRTStruct.cpp"


using namespace System;

namespace RTStructWrapper {

	public ref class structRT
	{
		// TODO: Add your methods for this class here.

	public:

		structRT();
		~structRT();
		!structRT();

		void structfun();

	private:

		WriteRTStruct *structrt;

	};
}
