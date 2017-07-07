#pragma once


#include "Basic3DCOMImplementations.h"
#include "ConvertorDef.h"
#include "BitField.h"
#include "I3DShFacetMesh.h"
#include "I3DShScene.h"
#include "I3DExModifier.h"
#include "ISceneSelection.h"
#include "IChangeManagement.h"
#include "PublicUtilities.h"
#include "ISceneDocument.h"
#include "MCCountedPtrArray.h"
#include "MCCountedPtr.h"
#include "IShComponent.h" // for IShParameterComponent
#include "IPolymesh.h"

// define the SceneOp CLSID

extern const MCGUID CLSID_HAIR_CV;

struct ConvertorData
{
	float width;
};
 

class HairConvertor  : public TBasicSceneCommand
{
public:
	HairConvertor(void);
	~HairConvertor(void);
			virtual MCErr  MCCOMAPI QueryInterface	(const MCIID& riid, void** ppvObj);

		STANDARD_RELEASE;

		// IExDataExchanger methods :
		virtual void*	 MCCOMAPI GetExtensionDataBuffer	();
		virtual int32	 MCCOMAPI GetParamsBufferSize		() const	{ return sizeof(fData);}
		virtual MCCOMErr MCCOMAPI ExtensionDataChanged		();
		virtual int16	 MCCOMAPI GetResID					();
//		virtual MCCOMErr MCCOMAPI SimpleHandleEvent(MessageID message, IMFResponder* source, void* data);
//		virtual void	 MCCOMAPI GetMenuCallBack(ISelfPrepareMenuCallBack** callBack) {return NULL;
		virtual void	 MCCOMAPI GetMenuCallBack(ISelfPrepareMenuCallBack** callBack);

		virtual MCCOMErr MCCOMAPI Init						(ISceneDocument* sceneDocument);
		virtual MCCOMErr MCCOMAPI Prepare					();

		virtual boolean  MCCOMAPI CanUndo					() {return false;}

		virtual boolean  MCCOMAPI Do						();
		virtual boolean  MCCOMAPI Undo						() {return true;}
		virtual boolean  MCCOMAPI Redo						() {return true;}


	private :
		void createHair( TMCArray< TVector3 > vertices,TMCArray< TIndex2 >,int start,int end,TTransform3D &trans,TTransform3D &invert,IPolymesh * mesh,TVector3 & centre);
		TVector3 getPerpendicular1(TVector3,TVector3);
		TVector3 getPerpendicular2(TVector3,TVector3);
		ConvertorData fData;
		TMCCountedPtr<ISceneDocument> fSceneDocument;
		TMCCountedPtr<I3DShScene> fScene;
		TMCCountedPtr<ISceneSelection> fSelection;
};

