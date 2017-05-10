/****************************************************************************************

		COMTriplanar.r

		Copyright (c)1990 - 1999 MetaCreations. All rights reserved.

		Author:	Jerome Bignon
		Date:	04/21/99

		Revision History

		when		who			what & why
		==========	==========	======================================================
		04/29/99	Jerome		Creation

*****************************************************************************************/

#include "External3DAPI.r"
#include "Copyright.h"
#include "TriplanarDef.h"
#include "interfaceids.h"


#ifndef qUsingResourceLinker
include "Triplanar.rsr";
#endif


resource 'GUID' (155)
{
	{
		R_IID_I3DExShader,
		R_CLSID_Triplanar
	}
};
resource 'GUID' (165)
{
	{
		R_IID_I3DExShader,
		R_CLSID_Triplanar2
	}
};
resource 'COMP' (155)
{
	kRID_ShaderFamilyID,
	'tpl1',
	"Triplanar",
	"Projection Mapping#1",
	FIRSTVERSION,
	VERSIONSTRING,
	COPYRIGHT,
	kRDAPIVersion
};
resource 'COMP' (165)
{
	kRID_ShaderFamilyID,
	'tplr',
	"Triplanar",
	"Projection Mapping",
	FIRSTVERSION,
	VERSIONSTRING,
	COPYRIGHT,
	kRDAPIVersion
};

resource 'PMap' (155)
{
	{
		'SHRP','in32',interpolate,"Sharpness","",
		'Shd0','comp',interpolate,"Shader 1","{fmly shdr MskE 1087 Subm 1 Sort 1 Mini 1 Drop 3}", // = 1024+32+16+8+4+2+1
	}
};
resource 'PMap' (165)
{
	{
		'SHRP','in32',interpolate,"Sharpness","",
		'Shd0','comp',interpolate,"Shader 1","{fmly shdr MskE 1087 Subm 1 Sort 1 Mini 1 Drop 3}", // = 1024+32+16+8+4+2+1
	}
};

resource 'CPUI' (155) 
{
	155,					// Id of your main part
	551,					// Id of your mini-part
	0,						// Style
	kParamsBeforeChildren,	// Where Param part is shown
	1						// Is Collapsable ?
};
resource 'CPUI' (165) 
{
	155,					// Id of your main part
	551,					// Id of your mini-part
	0,						// Style
	kParamsBeforeChildren,	// Where Param part is shown
	1						// Is Collapsable ?
};
