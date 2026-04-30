// wrapperadd.h

#pragma once

#include "..\..\addit\addit\operation.h";
#include "..\..\addit\addit\operation.cpp";


using namespace System;

namespace wrapperadd {

	public ref class opera
	{
		// TODO: Add your methods for this class here.
	public:
		opera();
		~opera();
		!opera();

		float addfun();

	private:

		operation * ad;
		
	
	};
}
