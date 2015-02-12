//=============================================================================
//
// NAME: OMS_IPCIF_VehiclePlumbing
//
// OVERVIEW: Provides functionality for the OMS_VehiclePlumbing IPC interface
//           subcomponents.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_VehiclePlumbing.h"
#include "OMS_IPCIF_VehiclePlumbing.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================
 
//-----------------------------------------------------------------------------
/**
* OMS_IPCIF_VehiclePlumbing
*/
//-----------------------------------------------------------------------------
OMS_IPCIF_VehiclePlumbing::OMS_IPCIF_VehiclePlumbing(
   OMS_VehiclePlumbing& rImpl) :
   OMS_IPCIF_Object(rImpl),
   rImpl_(rImpl)
{
} // end OMS_IPCIF_VehiclePlumbing

//-------------------------------------------------------------------------
/**
* OMS_IPCIF_VehiclePlumbing destructor implementation
*/
//-------------------------------------------------------------------------
OMS_IPCIF_VehiclePlumbing::~OMS_IPCIF_VehiclePlumbing()
{
} // end ~OMS_IPCIF_VehiclePlumbing

//--------------------------------------------------------------------
/**
* toggleContaminationState 
*/
//--------------------------------------------------------------------
CORBA::Long OMS_IPCIF_VehiclePlumbing::toggleContaminationState()
{
   rImpl_.toggle();

   return OMS::PASS;

} // end toggleContaminationState
