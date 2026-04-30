// This is the main DLL file.

#include "stdafx.h"

#include "wrapperadd.h"
#include "fstream"
#include "iostream"

wrapperadd::opera::opera()
{
	ad = new operation();
}

wrapperadd::opera::~opera()
{
	this->!opera();
}

wrapperadd::opera::!opera()
{
	delete ad;
}


float wrapperadd::opera::addfun()
{
	float d;

	d = ad->add();

	return d;
}
