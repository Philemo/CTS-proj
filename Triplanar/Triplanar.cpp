
/************************************************************************************************

Triplanar.cpp

Copyright (c)1990 - 1999 MetaCreations. All rights reserved.

Author: Jerome Bignon

Date: 04/29/99

Revision history

when		who			what & why
=========== =========== =====================================================================
08/20/99	cph			Put in Extension3DInit() and Extension3DCleanup() methods
04/29/99	Jerome		Finishing and comments
04/28/99	Jerome		Creation

************************************************************************************************/

#include <cmath>
#include "Triplanar.h"
#include "i3dshinstance.h"
#include "I3dShTreeElement.h"
#include "TBBox.h"
#include <string>

const MCGUID CLSID_Triplanar(R_CLSID_Triplanar);
const MCGUID CLSID_Triplanar2(R_CLSID_Triplanar2);


void Extension3DInit(IMCUnknown* utilities)
{
	// Perform your dll initialization here
}

void Extension3DCleanup()
{
	// Perform any nec clean-up here
}

TBasicUnknown* MakeCOMObject(const MCCLSID& classId)	// This method instanciate
{														// the object Fog
	TBasicUnknown* res = NULL;

	if ((classId == CLSID_Triplanar)
		|| (classId == CLSID_Triplanar2))
		res = new Triplanar;

	return res;
}


Triplanar::TPMap::TPMap()
{
	sharpness = 1;	// no sharpness

}


Triplanar::Triplanar()	// We just initialize the values
{
}

boolean Triplanar::IsEqualTo(I3DExShader* aShader)
{
	return ((fPMap.sharpness==((Triplanar*)aShader)->fPMap.sharpness) &&		(fPMap.fShader ==((Triplanar*)aShader)->fPMap.fShader));
}

MCCOMErr Triplanar::GetShadingFlags(ShadingFlags& theFlags)
{
	// shading flags are child shader's flags plus global coordinates and normal
	if ((fPMap.fShader) && (fPMap.fShader->QueryInterface(IID_I3DShShader, (void**)&fShaders) == MC_S_OK)) {
		fShaders->GetShadingFlags(theFlags);

	}
	else {
		theFlags.fConstantChannelsMask = kNoChannel;
	}
	theFlags.fNeedsNormalLoc = true;
	theFlags.fNeedsPointLoc  = true;
	return MC_S_OK;
}

EShaderOutput Triplanar::GetImplementedOutput()
{
	if ((fPMap.fShader) && (fPMap.fShader->QueryInterface(IID_I3DShShader, (void**)&fShaders) == MC_S_OK)) {
		// this shader mirros what's implemented in child shader
		return fShaders->GetImplementedOutput();
	}

	return (EShaderOutput)(kUsesDoShade | kUsesGetColor | kUsesGetVector | kUsesGetValue) ;	

}

MCCOMErr Triplanar::ExtensionDataChanged()
{

	if (fPMap.fShader){
		// parameter must be a shader
		if ( fPMap.fShader->QueryInterface(IID_I3DShShader, (void**)&fShaders) != MC_S_OK)
			return MC_S_FALSE;
		ShadingFlags f;
		fShaders->GetShadingFlags(f);
		// shader must respond to UV request
		if (f.fNeedsUV == false)
			return MC_S_FALSE;
	}
	return MC_S_OK;
}
MCCOMErr Triplanar::computeUVs(ShadingIn& shadingIn,TVector2 & uvXZ, TVector2 & uvXY,TVector2 & uvYZ, real32 & valueXZ , real32 & valueXY , real32 & valueYZ){
	if (shadingIn.fInstance) {
		TBBox3D box;
		shadingIn.fInstance->GetBoundingBox(box,ETreeDeformBBoxModes::kApplyAllDeformersAtInstanceLevel,true);
		real32 deltax = fabs(box.fMax.x - box.fMin.x);
		real32 deltay = fabs(box.fMax.y - box.fMin.y);
		real32 deltaz = fabs(box.fMax.z - box.fMin.z);
		real32 total = MC_Max(deltax,deltay,deltaz);
		deltax /= total;
		deltay /= total;
		deltaz /= total;
		uvXY = getNormalized(TVector2(box.fMin.x,box.fMin.y),TVector2(box.fMax.x,box.fMax.y),TVector2(shadingIn.fPointLoc.x,shadingIn.fPointLoc.y),deltax,deltay);
		uvXZ = getNormalized(TVector2(box.fMin.x,box.fMin.z),TVector2(box.fMax.x,box.fMax.z),TVector2(shadingIn.fPointLoc.x,shadingIn.fPointLoc.z),deltax,deltaz);
		uvYZ = getNormalized(TVector2(box.fMin.y,box.fMin.z),TVector2(box.fMax.y,box.fMax.z),TVector2(shadingIn.fPointLoc.y,shadingIn.fPointLoc.z),deltay,deltaz);
		TVector3d weights ;
		weights.x = fabs(shadingIn.fNormalLoc.x);
		weights.y = fabs(shadingIn.fNormalLoc.y);
		weights.z = fabs(shadingIn.fNormalLoc.z);
		if (fPMap.sharpness > 1) {
			weights.x = powf(weights.x,(double)fPMap.sharpness);
			weights.y = powf(weights.y,(double)fPMap.sharpness);
			weights.z = powf(weights.z,(double)fPMap.sharpness);
		}
		double sum= weights.x + weights.y + weights.z;
		valueXY = weights.z / sum;
		valueXZ = weights.y / sum;
		valueYZ = weights.x / sum;
		return MC_S_OK;
	}
	return MC_S_FALSE;
}
TVector2 Triplanar::getNormalized(TVector2 min , TVector2 max , TVector2 value, real32 delta1,real32 delta2){
	TVector2 delta = value - min;
	TVector2 total = max-min;
	real32 d1 = (1.0f - delta1) / 2.0f;
	real32 d2 = (1.0f - delta2) / 2.0f; 
	return TVector2((total.x == 0.0f?d1:fabs(delta.x / total.x) * delta1 + d1),(total.y == 0.0f?d2:fabs(delta.y / total.y) * delta2 + d2));
}

real Triplanar::GetValue(real& result,boolean& fullArea,ShadingIn& shadingIn)
{
	TVector2  uvXZ, uvXY, uvYZ;
	real32  valueXZ ,  valueXY , valueYZ;
	real32 opacity = 0.0f;
	computeUVs(shadingIn,uvXY,uvXZ,uvYZ,valueXY,valueXZ,valueYZ);
	if (fShaders) {
		real r = 0.0f;
		if (valueXY > 0.0f){
			shadingIn.fUV = uvXY;
			opacity += fShaders->GetValue(r,fullArea,shadingIn) * valueXY;
			result += r * valueXY;
		}
		if (valueXZ > 0.0f){
			shadingIn.fUV = uvXZ;
			opacity += fShaders->GetValue(r,fullArea,shadingIn) * valueXZ;
			result += r * valueXZ;
		}
		if (valueYZ > 0.0f){
			shadingIn.fUV = uvYZ;
			opacity += fShaders->GetValue(r,fullArea,shadingIn) * valueYZ;
			result += r * valueYZ;
		}
	}
	return opacity;
}
real	 Triplanar::GetColor (TMCColorRGBA& result,boolean& fullArea,ShadingIn& shadingIn){
	TVector2  uvXZ, uvXY, uvYZ;
	real32  valueXZ ,  valueXY , valueYZ;
	real32 opacity = 0.0f;
	computeUVs(shadingIn,uvXY,uvXZ,uvYZ,valueXY,valueXZ,valueYZ);
	if (fShaders) {
		TMCColorRGBA r = TMCColorRGBA::kBlackNoAlpha;
		if (valueXY > 0.0f){
			shadingIn.fUV = uvXY;
			opacity += fShaders->GetColor(r,fullArea,shadingIn) * valueXY;
			result += r * valueXY;
		}
		if (valueXZ > 0.0f){
			shadingIn.fUV = uvXZ;
			opacity += fShaders->GetColor(r,fullArea,shadingIn) * valueXZ;
			result += r * valueXZ;
		}
		if (valueYZ > 0.0f){
			shadingIn.fUV = uvYZ;
			opacity += fShaders->GetColor(r,fullArea,shadingIn) * valueYZ;
			result += r * valueYZ;
		}
	}
	return opacity;		
}
real  Triplanar::GetVector (TVector3& result,ShadingIn& shadingIn){
	TVector2  uvXZ, uvXY, uvYZ;
	real32  valueXZ ,  valueXY , valueYZ;
	real32 opacity = 0.0f;
	computeUVs(shadingIn,uvXY,uvXZ,uvYZ,valueXY,valueXZ,valueYZ);
	if (fShaders) {
		TVector3 r = TVector3::kZero;
		if (valueXY > 0.0f){
			shadingIn.fUV = uvXY;
			opacity += fShaders->GetVector(r,shadingIn) * valueXY;
			result += r * valueXY;
		}
		if (valueXZ > 0.0f){
			shadingIn.fUV = uvXZ;
			opacity += fShaders->GetVector(r,shadingIn) * valueXZ;
			result += r * valueXZ;
		}
		if (valueYZ > 0.0f){
			shadingIn.fUV = uvYZ;
			opacity += fShaders->GetVector(r,shadingIn) * valueYZ;
			result += r * valueYZ; 
		}
	}
	return opacity;
}
MCCOMErr Triplanar::DoShade (ShadingOut& result,ShadingIn& shadingIn){
	TVector2  uvXZ, uvXY, uvYZ;
	real32  valueXZ ,  valueXY , valueYZ;
	real32 opacity = 0.0f; 
	computeUVs(shadingIn,uvXY,uvXZ,uvYZ,valueXY,valueXZ,valueYZ);
	if (fShaders) {
		ShadingOut r ;
		if (valueXY > 0.0f){
			r.Clear();
			shadingIn.fUV = uvXY;
			fShaders->DoShade(r,shadingIn);
			r *= valueXY;
			result += r ;
		}
		if (valueXZ > 0.0f){
			r.Clear();
			shadingIn.fUV = uvXZ;
			fShaders->DoShade(r,shadingIn);
			r *= valueXZ;
			result += r ;
		}
		if (valueYZ > 0.0f){
			r.Clear();
			shadingIn.fUV = uvYZ;
			fShaders->DoShade(r,shadingIn);
			r *= valueYZ;
			result += r ;
		}
	}
	return MC_S_OK;
}


