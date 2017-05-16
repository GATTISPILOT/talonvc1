// ==============================================================
//                 ORBITER MODULE: EAGLEHANGAR2
//                  Part of the ORBITER SDK
//          Copyright (C) 2002-2004 Martin Schweiger
//                   All rights reserved
//
// EAGLEHANGAR2.cpp
// Control module for EAGLEHANGAR2 vessel class
//
// Notes:
// This is an example for a "minimal" vessel implementation which
// only overloads the clbkSetClassCaps method to define vessel
// capabilities and otherwise uses the default VESSEL class
// behaviour.
// ==============================================================

//

//#include "orbitersdk.h"

// ==============================================================
// Some vessel parameters
// ==============================================================
const double EMPTY_MASS = 100.0;


const double ARM_OPERATING_SPEED = 0.01;
#define R_SIZE	2.0, 0.16		// SM RCS flame size
#define FR_SIZE	1.2, 0.12		// CM RCS flame size

#define MAIN_ENGSIZE 7, 1.0		// main engine flame size
#define AUX_SIZE	2.5, 0.4	// aux  engine flame size

#define RCS_THRUST		2200		// SM RCS thrust [N]
#define AUX_THRUST		490		// SM Aux thrust
#define MAIN_THRUST	 	26700	// SM main thrust26700  LIFTOFF 130000
#define CRCS_THRUST		111		// CM RCS thrust

#define RCS_ISP			2900	// = 2650 + 10%	
#define MAIN_ISP	  	3400	// = 3100 + 10%
#define LAS_ISP			2700	// m/s

#define LAS_DRYMASS		5044	// kg
#define LAS_FUEL		2600	// kg

#define CM_DRYMASS		10220	// kg
#define CM_FUEL			170		// kg

#define SM_DRYMASS		5200	// kg incl CMA adapter
#define SM_FUEL			9200	// kg

#define FAIR_MASS		1360	// kg mass of all fairings
#define ADAPT_MASS		510		// kg


#define AID_NAVMODE 1
const double  LEM_DescentFUEL = 30978;				// Decent Stage fuel capacity [kg]
const double  LEM_DescentISP = 4398;				// Decent Engine exhuast velocity[m/s] 
const double  LEM_DescentTHRUST = 66.60e4;				// Decent Engine max thrust [n]



const double DOOR_OPERATING_SPEED = 0.16;




typedef struct {
	HINSTANCE hDLL;
	HFONT hFont[3];
	DWORD col[6];
	HBRUSH hBrush[4];
	HPEN hPen[2];
} GDIParams;

extern GDIParams g_Param;
// Interface for derived vessel class: QJBStar
// ==========================================================

class TALON: public VESSEL3 {
public:
   TALON (OBJHANDLE hObj, int fmodel);
   ~TALON();
  // friend BOOL CALLBACK RMS_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

   //void UpdateARRAYMesh();


       void clbkPostCreation (void);
	void clbkSetClassCaps (FILEHANDLE cfg);
	int clbkConsumeBufferedKey(DWORD key, bool down, char *kstate);
	void clbkVisualCreated(VISHANDLE vis, int refcount);
	void DefineAnimations(void);
	void clbkVisualDestroyed(VISHANDLE vis, int refcount);
	void clbkPostStep (double simtt, double simdt, double mjd);
	void clbkSaveState(FILEHANDLE scn);
	void clbkLoadStateEx (FILEHANDLE scn, void *status);
//	int InitializeOrbiterSound();

	bool clbkLoadVC(int id);
	bool clbkLoadGenericCockpit();
	bool clbkVCRedrawEvent(int id, int event, SURFHANDLE surf);
	bool clbkVCMouseEvent(int id, int event, VECTOR3 &p);
	bool HandleLoadVC(UINT const id);
	bool VCRedrawEvent(int const id, int const event, SURFHANDLE const surf);
	bool VCMouseEvent(int const id, int const event, VECTOR3& const p);
	//
	UINT  astroMeshUINT, astro1MeshUINT, cmMeshUINT, smMeshUINT, cockpitMeshUINT, coverMeshUINT, drogueMeshUINT, chuteMeshUINT, vcMeshUINT, meshi_Vessel, meshi_VC, meshi_VC1, MMUMeshUINT, BallonMeshUINT, lasMeshMeshUINT;
	OBJHANDLE hMMU;
//THRUSTER_HANDLE th_rcs[20],th_group[4];
//THRUSTER_HANDLE th_main, thg_main;
//VECTOR3 arm1_tip[3], arm2_tip[3];
//VECTOR3 xp1, xr1, xp2, xr2;
//void Estado();
// UMMU 2.0 DECLARATION
	


	THRUSTER_HANDLE th_main, th_descent[10];
	THRUSTER_HANDLE th_aux[8];		// RM auxillary engines

	


private:
//	SpotLight *docking_lightfront, *docking_lightfront1;
	int water,EVA;
	int BEACON;
	VECTOR3 ofs, ofs_camera, ofs_astro[4], ofs_hud, ofs_ares, ofs_1, ofs_2, ofs_ummu;
	MESHHANDLE astroMesh;
	MESHHANDLE cmMesh, coverMesh, hatchMesh, smMesh, vcMesh, meshhg_Vessel, meshhg_VC,
		solar0Mesh, solar1Mesh, solar2Mesh, solar3Mesh,
		cockpitMesh, panelMesh;
	MESHHANDLE drogueMesh, chuteMesh, balloonMesh;
	MESHHANDLE fair1Mesh, fair2Mesh, fair3Mesh, lasMesh;
	int mode;	// 0 = orbit config, CM + SM, solar closed
	// 1 = orbit config, CM + SM, solar deployed
	// 2 = reentry config, CM only
	// 3 = drogue config, CM + drogue chute
	// 4 = chute config 1, reefed
	// 5 = chute config 2, fully deployed
	// 6 = landed

	// 10 = Launch, LAS + fairing
	// 11 = Launch, fairing gone
	// 12 = Launch, LAS gone
	// 20 = Abort

	PROPELLANT_HANDLE ph_main, ph_RM, ph_CM, ph_descent;
	double fairing,h;
	char string[256];
	SURFHANDLE tex_rcs, tex_main;
	OBJHANDLE fair1h, fair2h, fair3h, fairLh;	// stored for later disposal




char name[255];
double LIFT_SPEED, center_arm_t, HGA_proc, ARM2a_proc, ANTROT_proc, HATCH_proc;
int TALONID, do_attach, SCAFFOLD, CAM, light_status;
;
int iActiveDockNumber, doorselected;
bool center_arm;
//double TCAR_proc; 
double db, simdt;
MGROUP_ROTATE *SOLAR1, *SOLAR2, *SOLAR3, *SOLAR4, *SOLAR5, *SOLAR6, *SOLAR7, *SOLAR8, *SOLAR9, *SOLAR10, *SOLAR11, *SOLAR12, *SOLAR13, *SOLAR14, *SOLAR15, *SOLAR16, *SOLAR17, *SOLAR18, *SOLAR19, *SOLAR20, *SOLAR21, *SOLAR22, *SOLAR23, *SOLAR24, *SOLAR25, *SOLAR26;
MGROUP_ROTATE *SOLAR1A, *SOLAR2A, *SOLAR3A, *SOLAR4A, *SOLAR5A, *SOLAR6A, *SOLAR7A, *SOLAR8A, *SOLAR9A, *SOLAR10A, *SOLAR11A, *SOLAR12A, *SOLAR13A, *SOLAR14A, *SOLAR15A, *SOLAR16A, *SOLAR17A, *SOLAR18A, *SOLAR19A, *SOLAR20A, *SOLAR21A, *SOLAR22A, *SOLAR23A, *SOLAR24A, *SOLAR25A, *SOLAR26A;

double  ARM_OPERATING_SPEED, JOINT1_proc, JOINT2_proc, JOINT3_proc, JOINT4_proc, JOINT5_proc, JOINT6_proc, JOINT0_proc, ARM3_proc;
UINT anim_JOINT1, anim_JOINT2, anim_JOINT3, anim_JOINT4, anim_JOINT5, anim_JOINT6, anim_JOINT7, anim_JOINT0, anim_base0, anim_JOINT8, anim_HGA, anim_HATCH;

double apd;

VECTOR3 beaconpos[4];
VECTOR3 beaconcol[4];
BEACONLIGHTSPEC beacon[4];

};


