/************************************************************************************************************

  	Convertor.cpp

	Copyright (c)1990 - 1999 MetaCreations. All rights reserved.

	Author:	Philemo

************************************************************************************************************/



#include "HairConvertor.h"
#include "COMSafeUtilities.h"
#include <stdio.h>



const MCGUID CLSID_HAIR_CV(R_CLSID_HAIR_CV);



void Extension3DInit(IMCUnknown* utilities)
{
}
 
void Extension3DCleanup()
{
}


TBasicUnknown* MakeCOMObject(const MCCLSID& classId)	// This method instanciate
{										
		// the object COMBack
	TBasicUnknown* res = NULL;


	if (classId == CLSID_HAIR_CV) res = new HairConvertor;

	MCAssert(res);

	return res;
}


