/****************************************************************************************

		HairConvertor.r

		Copyright (c)1990 - 1999 MetaCreations. All rights reserved.

		Author:	Jerome Bignon
		Date:	07/15/99

		Revision History

		when		who			what & why
		==========	==========	======================================================
		07/15/99	Jerome		Creation
*****************************************************************************************/

#include "External3DAPI.r"
#include "Copyright.h"
#include "ConvertorDef.h"
#include "interfaceids.h"
#include "MCRTypes.r"
#include "CommandIdRanges.h"
#include "StandardBindingIds.h"


#ifndef qUsingResourceLinker
include "HairConvertor.rsr";
#endif


resource 'GUID' (200)
{
	{
		R_IID_I3DExSceneCommand,
		R_CLSID_HAIR_CV
	}
};
resource 'COMP' (200)
{
	kRID_SceneCommandFamilyID,
	'HCvt',
	"Convert hair to polygons",
	"Philemo",
	FIRSTVERSION,
	VERSIONSTRING,
	COPYRIGHT,
	kRDAPIVersion
};

resource 'PMap' (200)
{
	{
			'wdth', 're32', noFlags, "hair stripe width", "",
	}
};

resource 'scmd' (200)
{
	kSDKCmdIDBase+200,
	defaultMenu,
	{
		'3Dvw',		// 3D View room
		'Stry',		// Storyboard room
	},
	kNoStrings,
	kDefaultName,
	kEditBindingGroupID,
	{ 
		kDefaultID,	kDefaultName,	'c',	kShift,		kCtrl,	kNoAlt,	kAnyPlatform; // default keybord shortcut is Shift + Ctrl + v
	},
	k3DViewBindingContextID
};
