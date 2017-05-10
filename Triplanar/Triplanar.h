
/************************************************************************************************

	Triplanar.h


	Author: Philemo

	Date: 04/25/17

	Revision history

	when		who			what & why
	=========== =========== =====================================================================

************************************************************************************************/

#ifndef __Triplanar__
#define __Triplanar__

#if CP_PRAGMA_ONCE
#pragma once
#endif

#include "TriplanarDef.h"
#include "BasicShader.h"
#include "I3DShShader.h"
#include "MCPtrArray.h"
#include "IShComponent.h"

// Define the Triplanar CLSID ( see the TriplanarDef.h file to get R_CLSID_Triplanar value )

extern const MCGUID CLSID_Triplanar;
extern const MCGUID CLSID_Triplanar2;

class Triplanar : public TBasicShader
{
public :

	Triplanar();

	STANDARD_RELEASE;
  
// We don't have to take care of the none implemented methods because the TBasicShader
// does this for us

	virtual void*			MCCOMAPI    GetExtensionDataBuffer	()			{ return &fPMap; }
	virtual int32			MCCOMAPI	GetParamsBufferSize		() const	{ return sizeof(fPMap);}
	virtual MCCOMErr		MCCOMAPI	ExtensionDataChanged	();
	virtual boolean			MCCOMAPI    IsEqualTo				(I3DExShader* aShader);  
	virtual MCCOMErr		MCCOMAPI	GetShadingFlags			(ShadingFlags& theFlags);
	virtual EShaderOutput	MCCOMAPI	GetImplementedOutput	();
	
		virtual MCCOMErr		MCCOMAPI DoShade							(ShadingOut& result,ShadingIn& shadingIn);
		virtual real			MCCOMAPI GetValue							(real& result,boolean& fullArea,ShadingIn& shadingIn);
		virtual real			MCCOMAPI GetColor							(TMCColorRGBA& result,boolean& fullArea,ShadingIn& shadingIn);
		virtual real			MCCOMAPI GetVector							(TVector3& result,ShadingIn& shadingIn);

protected:
	MCCOMErr computeUVs(ShadingIn& shadingIn,TVector2 & uvXZ, TVector2 & uvXY,TVector2 & uvYZ, real32 & valueXZ , real32 & valueXY , real32 & valueYZ);
	TVector2 getNormalized(TVector2 min , TVector2 max , TVector2 value,real32 delta1 , real32 delta2);
	struct TPMap
	{	
		TPMap();
		int32 sharpness;		// sharpness (from 1 to 10)
		TMCCountedPtr<IShParameterComponent> fShader;
	};

	TPMap						fPMap;

	TMCCountedPtr<I3DShShader> fShaders; 

};
                           
#endif // __Triplanar__

