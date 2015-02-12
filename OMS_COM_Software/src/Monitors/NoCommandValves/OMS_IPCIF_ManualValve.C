//=============================================================================
//
// NAME: OMS_IPCIF_ManualValve
//
// OVERVIEW: Class object providing functionality for the ManualValve
//           IPC Interface.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
 
//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_ManualValve.h"


//-----------------------------------------------------------------------------
/**
* OMS_IPCIF_ManualValve - This is the IPC interface constructor
* used to bind to a reference of the OMS_ManualValve class.
*
* @param rImpl A reference to the OMS_ManualValve instance which
*              implements the interface methods.
*/
//-----------------------------------------------------------------------------
OMS_IPCIF_ManualValve::OMS_IPCIF_ManualValve (
   OMS_ManualValve& rImpl) :
   OMS_IPCIF_Object(rImpl),
   rImpl_(rImpl)
{
} // end OMS_IPCIF_ManualValve


//-----------------------------------------------------------------------------
/**
* toggle - Invokes the toggle method of the OMS_ManualValve
*          implementation.
* 
* @return OMS::PASS.
*/
//-----------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_ManualValve::toggle()
{
   rImpl_.toggle();

   return OMS::PASS;

} // end OMS_IPCIF_ManualValve::toggle


