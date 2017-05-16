// ==============================================================
//                 ORBITER MODULE: TALON
//                  Part of the ORBITER SDK
//          Copyright (C) 2002-2004 Martin Schweiger
//                   All rights reserved
//
// TALON.cpp
// Control module for TALON vessel class
//

// ==============================================================
//#define ORBITER_MODULE
#include "orbitersdk.h"
#include "TALONVC.h"

#include <stdio.h>
#include <fstream>

#define LOADBMP(id) (LoadBitmap (g_Param.hDLL, MAKEINTRESOURCE (id)))

//BOOL CALLBACK ATHLETE_TEST_DlgProc(HWND, UINT, WPARAM, LPARAM);
//
//
//







void TALON::clbkPostCreation(void)
{
	
//	SetAnimation(anim_JOINT0, 0.0);
//	SetAnimation(anim_JOINT1, 0.0);
//	SetAnimation(anim_JOINT2, .5);
//	SetAnimation(anim_JOINT3, 0.0202);
//	SetAnimation(anim_JOINT4, 0.0);
//	SetAnimation(anim_JOINT5, 0.5279);
//	SetAnimation(anim_JOINT6, -0.8352);
//	SetAnimation(anim_JOINT7, 1.0);
	//PANELEXT_proc = 1;
	//PANEL_proc = 1;
}








// Constructor


// --------------------------------------------------------------
// Destructor
// --------------------------------------------------------------
TALON::~TALON() {

}




TALON::TALON (OBJHANDLE hObj, int fmodel)
: VESSEL3 (hObj, fmodel)


{

	mode = 0;
	BEACON = 0;
	ofs = _V(0, 0, 0);
	string[0] = 0;

	tex_rcs = oapiRegisterExhaustTexture("exhaust_crcs");
	tex_main = oapiRegisterExhaustTexture("exhaust_crcs");


	








}


void TALON::clbkSetClassCaps (FILEHANDLE cfg)
//void TALON::SetTransporter()
{
	// physical specs
		SetSize (3);
	SetEmptyMass (500.0);
	SetCW (0.09, 0.09, 2, 1.4);
	SetWingAspect (0.7);
	SetWingEffectiveness (2.5);
    SetCrossSections (_V(710.54,2159.34,207.95));
    SetSurfaceFrictionCoeff (0.07, 0.3);
    SetRotDrag (_V(0.10,0.13,0.04));
    SetMaxWheelbrakeForce (5e5);
    SetPMI (_V(743.84,872.38,148.19));
	SetTrimScale (0.1);
	SetCameraOffset(_V(-0.41, 1.6, 2.21));
	
	SetTouchdownPoints  (_V(0,.0001,10), _V(-1.6,.0001,-10), _V(1.6,.0001,-10));; 
EnableTransponder (true);

//SetMeshVisibilityMode (AddMesh (oapiLoadMeshGlobal ("TALON")), MESHVIS_ALWAYS ); //Main ship mesh



	// Call clbkSetClassCaps_UMMU and select a member



SetMeshVisibilityMode(meshi_Vessel = AddMesh(meshhg_Vessel = oapiLoadMeshGlobal("TALON\\TALON_VCNEW3")), MESHVIS_ALWAYS);
SetMeshVisibilityMode(meshi_VC1 = AddMesh(meshhg_Vessel), MESHVIS_VC);
SetMeshVisibilityMode(meshi_VC = AddMesh(meshhg_VC = oapiLoadMeshGlobal("TALON\\TALON_VCNEW3")), MESHVIS_VC);


}

// =======================================================
// UMMU Class Caps
// =======================================================








void TALON::clbkPostStep(double simt, double simdt, double mjd)
{

}





// --------------------------------------------------------------
// Keyboard interface handler (buffered key events)
// --------------------------------------------------------------
int TALON::clbkConsumeBufferedKey(DWORD key, bool down, char *kstate)
{
	
	if (!down) return 0; 
	return 0;
}
// ====================================================================
// clbkVisualCreated used to display UMMU initialisation message 
// because oapiDebugString() doesn't work in clbkSetClassCap
// ====================================================================
void TALON::clbkVisualCreated(VISHANDLE vis, int refcount)
{
	//MainExternalMeshVisual = GetMesh(vis, 0);

}
// ==============================================================
// Visual destroyed
// ==============================================================
void TALON::clbkVisualDestroyed(VISHANDLE vis, int refcount)
{
	//MainExternalMeshVisual = 0;
}



void TALON::clbkSaveState(FILEHANDLE scn)
{
	{
		char cbuf[256];


		

	
		// ORBITER, default vessel parameters
		SaveDefaultState(scn);

	}

}
void TALON::clbkLoadStateEx (FILEHANDLE scn, void *status)
{
	char *line;
	int value;
	while (oapiReadScenario_nextline(scn, line))
	{


		





		ParseScenarioLineEx(line, status);
	}

	
}





	

bool TALON::clbkLoadGenericCockpit() {
	return true;
}

bool TALON::clbkLoadVC(int id)
{


	switch (id) {
	case 0: // commander position
		SetCameraOffset(_V(-0.41, 1.6, 2.241));
		SetCameraDefaultDirection(_V(0, 0, 1));
		SetCameraMovement(_V(0, 0, 0.2), 0, 0, _V(-0.3, 0, 0), 75 * RAD, -5 * RAD, _V(0.3, 0, 0), -20 * RAD, -27 * RAD);
		//oapiVCSetNeighbours(-1, 1, -1, 2);



		oapiVCRegisterArea(AID_NAVMODE, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN);
		oapiVCSetAreaClickmode_Quadrilateral(AID_NAVMODE, _V(-10.1446553, 10.511254, 2.824909), _V(10.1446553, 10.487942, 2.824909), _V(-10.1521383, -10.511254, 2.824909), _V(10.1517904, 10.487942, 2.824909));

	}



	return true;

}


bool TALON::clbkVCMouseEvent(int id, int event, VECTOR3 &p)
{

	switch (id) {


	case AID_NAVMODE:
		ToggleNavmode(NAVMODE_KILLROT);
		return true;

	}
	return false;
}


	
	// --------------------------------------------------------------
	// Respond to virtual cockpit mouse events
	// --------------------------------------------------------------
	

	// --------------------------------------------------------------
	// Respond to virtual cockpit area redraw requests
	// --------------------------------------------------------------
	bool TALON::clbkVCRedrawEvent(int id, int event, SURFHANDLE surf)
	{
		return false;
	} // End "LM::clbkVCRedrawEvent"


	DLLCLBK VESSEL *ovcInit(OBJHANDLE hvessel, int flightmodel)
	{
		return new TALON(hvessel, flightmodel);
	}

	// --------------------------------------------------------------
	// Vessel cleanup
	// --------------------------------------------------------------
	DLLCLBK void ovcExit(VESSEL *vessel)
	{
		if (vessel) delete (TALON*)vessel;
	}