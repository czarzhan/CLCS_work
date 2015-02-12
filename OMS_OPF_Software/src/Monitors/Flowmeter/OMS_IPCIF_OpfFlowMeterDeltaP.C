//=============================================================================
//
// NAME: OMS_IPCIF_OpfFlowMeterDeltaP
//
// OVERVIEW: Provides all IPC interfaces for OMS_OpfFlowMeterDeltaP.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_OpfFlowMeterDeltaP.h"
#include "OMS_OpfFlowMeterDeltaP.h"
    
//=============================================================================
//                     Class Member Definitions
//=============================================================================


//-----------------------------------------------------------------------------
/**
*
* OMS_IPCIF_OpfFlowMeterDeltaP - This is the IPC interface constructor
* used to bind to a reference of the OMS_OpfFlowMeterDeltaP class.
*
*/
//-----------------------------------------------------------------------------
OMS_IPCIF_OpfFlowMeterDeltaP::OMS_IPCIF_OpfFlowMeterDeltaP(
   OMS_OpfFlowMeterDeltaP& rImpl):
   OMS_IPCIF_Object (rImpl),
   rImpl_(rImpl)
{
} // end OMS_IPCIF_OpfFlowMeterDeltaP::OMS_IPCIF_OpfFlowMeterDeltaP

//-----------------------------------------------------------------------------
/**
* IPC Interface destructor
*/ 
//-----------------------------------------------------------------------------
OMS_IPCIF_OpfFlowMeterDeltaP::~OMS_IPCIF_OpfFlowMeterDeltaP()
{

} // end OMS_IPCIF_OpfFlowMeterDeltaP::~OMS_IPCIF_OpfFlowMeterDeltaP
   

//-----------------------------------------------------------------------------
/**
* changeMode - Invokes the changeMode method of the 
* OMS_OpfFlowMeterDeltaP implementation. 
*/
//-----------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_OpfFlowMeterDeltaP::changeMode()
{
   rImpl_.changeMode();

   return OMS::PASS;

} // end OMS_IPCIF_OpfFlowMeterDeltaP::changeMode



//-----------------------------------------------------------------------------
/**
* startHighRate - Invokes the startHighRate method of the 
* OMS_OpfFlowMeterDeltaP implementation. 
*/
//-----------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_OpfFlowMeterDeltaP::startHighRate()
{
   rImpl_.startHighRate();

   return OMS::PASS;

} // end OMS_IPCIF_OpfFlowMeterDeltaP::startHighRate 



//-----------------------------------------------------------------------------
/**
* stopHighRate - Invokes the stopHighRate method of the 
* OMS_OpfFlowMeterDeltaP implementation. 
*/
//-----------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_OpfFlowMeterDeltaP::stopHighRate()
{
   rImpl_.stopHighRate();

   return OMS::PASS;

} // end OMS_IPCIF_OpfFlowMeterDeltaP::stopHighRate



//-----------------------------------------------------------------------------
/**
* listAttributes - Invokes the listAttributes method of the 
* OMS_OpfFlowMeterDeltaP implementation.
*
* @param   rAttributes - A reference to the attributes list
* @return void
*/
//-----------------------------------------------------------------------------
void OMS_IPCIF_OpfFlowMeterDeltaP::listAttributes(List_t& rAttributes)
{
   rImpl_.listAttributes(rAttributes);
   
} // end OMS_IPCIF_OpfFlowMeterDeltaP::listAttributes
