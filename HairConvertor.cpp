#include "HairConvertor.h"
#include "I3DShInstance.h"
#include "I3DShRenderable.h"
#include "COM3DUtilities.h"
#include "I3dShUtilities.h"
#include "COMSafeUtilities.h"
#include "IShUtilities.h"
#include "I3DShMasterGroup.h"
#include "I3DExVertexPrimitive.h"
#include "IPolygon.h"
#include "IShUtilities.h"
#include "COMSafeUtilities.h"




HairConvertor::HairConvertor(void)
{
	fSceneDocument = NULL;
	fData.width = 0.4f;

}


HairConvertor::~HairConvertor(void)
{
}

void* HairConvertor::GetExtensionDataBuffer()
{
	return &fData; // used by the shell to set the new parameters
}

short HairConvertor::GetResID()
{
	return 200 ; // this is the view ID in the resource file.
}


// For the component chooser
MCCOMErr HairConvertor::ExtensionDataChanged()
{
	MCCOMErr result = MC_S_OK;


	return result;
}



MCCOMErr HairConvertor::Init(ISceneDocument* sceneDocument)
{
	fSceneDocument = sceneDocument;
	fScene = sceneDocument->GetScene();
	return MC_S_OK;
}

MCCOMErr	 HairConvertor::QueryInterface	(const MCIID &riid, void** ppvObj){
	if (MCIsEqualIID(riid, CLSID_HAIR_CV))
	{
		TMCCountedGetHelper<HairConvertor> result(ppvObj);
		result= this;
		return MC_S_OK;
	}
	return TBasicSceneCommand::QueryInterface(riid, ppvObj);
}

MCCOMErr HairConvertor::Prepare()
{
	return MC_S_OK;
}
I3DShInstance* getSelectedTree(ISceneDocument* sceneDocument)
{

	if (sceneDocument){
		TMCCountedPtr<ISceneSelection> selection;
		sceneDocument->GetSceneSelection(&selection);
		if ((selection->GetObjectCount()) && (!selection->IsMultipleSelection())){
			TTreeSelectionIterator iter(selection);
			I3DShTreeElement* iTree=iter.First();
			while (iTree){
				TMCCountedPtr<I3DShObject> shObject;
				TMCCountedPtr<I3DShInstance> shInstance;
				if ( iTree->QueryInterface(IID_I3DShInstance,(void**)&shInstance) == MC_S_OK) {
					if (shInstance->Get3DObject(&shObject) == MC_S_OK) {
						if (shObject->GetObjectID() == 'hair')
							return shInstance;
					}
				}
				iTree = iter.Next();
			}

		}
	}

	return NULL;
}

boolean HairConvertor::Do() {


	TMCCountedPtr<I3DShInstance> instance;
	instance = getSelectedTree(fSceneDocument);
	if(!(instance)) return false;

	TMCCountedPtr<I3DShTreeElement> tree;
	tree = instance->GetTreeElement();
	if (!(tree)) return false;

	TTransform3D trans, invert;
	tree->GetGlobalTransform3D(trans);
	invert = tree->GetInverseGlobalTransform3D();

	TMCCountedPtr<I3DExVertexPrimitive> vertexPrimitive;
	TMCCountedPtr<I3DShObject> shObject;
	gShell3DUtilities->CreatePrimitiveByID('vmda', &shObject, IID_I3DExVertexPrimitive, (void**) &vertexPrimitive);
	vertexPrimitive->Hydrate();
	TMCCountedPtr<IPolymesh> mesh;
	vertexPrimitive->CreatePolymesh(&mesh);
	mesh->SetUVMode(kUVCustom);
	mesh->SetUVCustomMode(0, kUVSpecified, false);
	mesh->SetUVCustomMode(1, kUVSpecified, false);
	mesh->SetUVWraparound(false,false);
	TBBox3D box;
	instance->GetTreeElement()->GetBoundingBox(box,ETreeDeformBBoxModes::kApplyAllDeformersAtInstanceLevel,false);
	TVector3 sourceCentre;
	box.GetCenter(sourceCentre);
	const TRenderableAndTfmArray * renderables;
	instance->GetTreeElement()->BeginGetRenderables(renderables,false);
	instance->GetTreeElement()->EndGetRenderables();
	int nbSegment = 0;
	for (uint32 i = 0; i < renderables->GetElemCount(); i++){
		TRenderableAndTfm rf;
		renderables->GetElem(i,rf);
		I3DShRenderable::EType t =  rf.fRenderable->GetGeometryType();
		if (t == I3DShRenderable::EType::kType_Segment) {
			const TSegmentMesh * segment = rf.fRenderable->GetSegmentMesh();
			nbSegment += segment->fSegmentIndices.GetElemCount();
		}
	}
	int onePercent = nbSegment / 100;
	int step = 0;
	real32 percent = 0;
	TMCCountedPtr<IMCUnknown> progressKey;
	gShellUtilities->BeginProgress(TMCDynamicString("Convert Hair"), &progressKey, 100.0f);
	gShellUtilities->SetProgressDelay(0.0f,progressKey);

	for (uint32 i = 0; i < renderables->GetElemCount(); i++){
		TRenderableAndTfm rf;
		renderables->GetElem(i,rf);
		I3DShRenderable::EType t =  rf.fRenderable->GetGeometryType();
		if (t == I3DShRenderable::EType::kType_Segment) {
			const TSegmentMesh * segment = rf.fRenderable->GetSegmentMesh();
			if (segment->fSegmentIndices.GetElemCount() > 0) {
				int prev = -1;
				int start,end= -1;
				for (uint32 j = 0; j < segment->fSegmentIndices.GetElemCount(); j++) {
					TIndex2 extr = segment->fSegmentIndices[j];
					step++;
					if (step > onePercent) {
						step = 0;
						percent++;
						gShellUtilities->SetProgressValue(percent, progressKey );

					}
					if (extr.x != prev) {
						if (j > 0){
							end = j-1;
							createHair(segment->fVertex ,segment->fSegmentIndices, start, end,trans,invert, mesh,sourceCentre);
						}
						start = j;

					}
					prev = extr.y;
					//segments.push_back(MinVec2I(extr.x,extr.y));
				}
				if (start > -1){
					createHair(segment->fVertex ,segment->fSegmentIndices, start, segment->fSegmentIndices.GetElemCount()-1,trans,invert, mesh,sourceCentre);
				}
			}
		}

	}
	gShellUtilities->EndProgress(progressKey);
	gShellUtilities->BeginProgress(TMCDynamicString("Dehydrate Converted Hair"), &progressKey, 100.0f);
	gShellUtilities->SetProgressDelay(0.0f,progressKey);
	vertexPrimitive->Dehydrate();
	gShellUtilities->EndProgress(progressKey);
	TMCCountedPtr<I3DShTreeElement> instanceTree;



	shObject->SetName(tree->GetName()+TMCDynamicString("_convert"));

	// create tree instance for the facet mesh object
	gComponentUtilities->CoCreateInstance(CLSID_StandardInstance, NULL,
		MC_CLSCTX_INPROC_SERVER, IID_I3DShInstance, (void**) &instance);

	instance->Set3DObject(shObject);
	instance->QueryInterface(IID_I3DShTreeElement, (void**) &instanceTree);
	TMCCountedPtr<I3DShMasterGroup> masterGroup;

	fScene->QueryInterface(IID_I3DShMasterGroup,(void**)&masterGroup);

	instanceTree->SetMasterGroup(masterGroup);

	gShellUtilities->BeginProgress(TMCDynamicString("Center on hot point Converted Hair"), &progressKey, 100.0f);
	gShellUtilities->SetProgressDelay(0.0f,progressKey);
	// instanceTree->CenterHotPointOnElement();
	gShellUtilities->EndProgress(progressKey);
	tree->InsertRight(instanceTree);
	tree->SetVisibilityFlag(false);




	return true;
}

TVector3 HairConvertor::getPerpendicular1(TVector3 v1,TVector3 v2){
	if ((v1*v2) > 0.99)
		return TVector3::kZero;
	return (v1^v2)  * (1-(v1*v2));
}
TVector3 HairConvertor::getPerpendicular2(TVector3 v1,TVector3 v2){
	if ((v1*v2) > 0.99)
		return TVector3::kZero;
	return (v1^v2) ;
}
void HairConvertor::createHair( TMCArray< TVector3 > vertices,TMCArray< TIndex2 > indices,int start,int end,TTransform3D &local2Global,TTransform3D &global2Local,IPolymesh * mesh,TVector3 &centre){


	TMCClassArray<TVMIVertexPtr> prev;
	uint32 nbSegment = 1;
	for (int s = end; s >= start; s--){

		TVector3 dir = vertices[indices[s].y] - vertices[indices[s].x];
		TVector3 dirLocal = global2Local.TransformVector(dir);
		dirLocal.Normalize();
		TVector3 perp = getPerpendicular2(dir,vertices[indices[s].x]-centre);
		if (perp == TVector3::kZero) {

			TVector3 perp = getPerpendicular1(dirLocal,TVector3::kUnitX) +  getPerpendicular1(dirLocal,TVector3::kUnitY) +  getPerpendicular1(dirLocal,TVector3::kUnitZ);
			perp.Normalize();
			perp = local2Global.TransformVector(perp);
		}
		perp.Normalize();
		// create vertices
		boolean createPrev = false;
		if (prev.GetElemCount() == 0) {
			TMCCountedPtr<I3DExVertex> ve;

			TVector3 v = vertices[indices[s].y] - perp * (fData.width)/2;
			mesh->CreateVertex(&ve,v);
			ve->SetUV(0,TVector2(0.0f,0.0f));
			prev.AddElem(TVMIVertexPtr(ve,0)); 


			v = vertices[indices[s].y] + perp * (fData.width)/2;
			mesh->CreateVertex(&ve,v);
			ve->SetUV(0,TVector2(1.0f,0.0f));
			prev.AddElem(TVMIVertexPtr(ve,0)); 

			createPrev = true;
		}
		TMCClassArray<TVMIVertexPtr> current;
		TMCCountedPtr<I3DExVertex> ve;
		TVector3 v = vertices[indices[s].x] + perp * (fData.width)/2;
		mesh->CreateVertex(&ve,v);
		// int nn = ve->AddUV(TVector2(1.0f,float(nbSegment)/float(end-start+1)));
		ve->SetUV(0,TVector2(1.0f,float(nbSegment)/float(end-start+1)));
		// TR("adding UV %d with value %f, %f",nn,1.0f,float(nbSegment)/float(end-start+1));
		current.AddElem(TVMIVertexPtr(ve,0)); 
		v = vertices[indices[s].x] - perp * (fData.width)/2;
		mesh->CreateVertex(&ve,v);
		//nn = ve->AddUV(TVector2(0.0f,float(nbSegment)/float(end-start+1)));
		ve->SetUV(0,TVector2(0.0f,float(nbSegment)/float(end-start+1)));
		current.AddElem(TVMIVertexPtr(ve,0)); 


		// create facets
		TMCClassArray<TVMIVertexPtr> poly(prev);
		poly.Append(current);
		TMCCountedPtr<IPolygon> polygon;
		// polygon->SetShadingDomainID(0);
		mesh->MakePolygon(poly);


		prev.Swap(current);
		TVMIVertexPtr sauve = prev[0];
		prev[0] = prev[1];
		prev[1] = sauve;
		nbSegment++;
	}
}
class IsSelectionOK : public TBasicMenuCallBack
{
protected:
	IsSelectionOK() {}
	virtual ~IsSelectionOK() {}
public:
	void static Create(ISelfPrepareMenuCallBack** out);
	virtual boolean MCCOMAPI SelfPrepareMenu(ISceneDocument* sceneDocument);
};

void IsSelectionOK::Create(ISelfPrepareMenuCallBack** out)
{
	TMCCountedCreateHelper<ISelfPrepareMenuCallBack> result(out);
	result = new IsSelectionOK();
}

boolean IsSelectionOK::SelfPrepareMenu(ISceneDocument* sceneDocument)
{

	I3DShInstance* instance = getSelectedTree(sceneDocument);
	if (instance) return true;
	return false;
}

void HairConvertor::GetMenuCallBack(ISelfPrepareMenuCallBack** callBack)
{
	IsSelectionOK::Create(callBack);
}


