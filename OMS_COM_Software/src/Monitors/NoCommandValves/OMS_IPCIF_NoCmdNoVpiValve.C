//=============================================================================
//
// NAME: OMS_IPCIF_NoCmdNoVpivalve
//
// OVERVIEW: Class object providing functionality for the NoCmdNoVpiValve
//           IPC Interface.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
 
//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_NoCmdNoVpiValve.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================

//--------------------------------------------------------------------
/**
* OMS_IPCIF_NoCmdNoVpiValve - This is the IPC interface constructor
* used to bind to a reference of the OMS_NoCmdNoVpiValve class.
*
*/
//--------------------------------------------------------------------
OMS_IPCIF_NoCmdNoVpiValve::OMS_IPCIF_NoCmdNoVpiValve (
   OMS_NoCmdNoVpiValve& rImpl) :
   OMS_IPCIF_Object(rImpl),
   rImpl_(rImpl)
{
} // end OMS_IPCIF_NoCmdNoVpiValve


//--------------------------------------------------------------------
/**
* IPC Interface destructor
*/
//--------------------------------------------------------------------
OMS_IPCIF_NoCmdNoVpiValve::~OMS_IPCIF_NoCmdNoVpiValve()
{
} // end ~OMS_IPCIF_NoCmdNoVpiValve



//--------------------------------------------------------------------
/**
* notInstalled - Invokes the setState method of the 
* OMS_NoCmdNoVpiValve to set the QD state to NOT_INSTALLED
*
*/
//--------------------------------------------------------------------
CORBA::Long OMS_IPCIF_NoCmdNoVpiValve::notInstalled()
{
   rImpl_.setState(OMS_OPF_QD_ENUM::NOT_INSTALLED);

   return OMS::PASS;
   
} // end OMS_IPCIF_NoCmdNoVpiValve::notInstalled



//--------------------------------------------------------------------
/**
* notMated - Invokes the setState method of the 
* OMS_NoCmdNoVpiValve to set the QD state to NOT_MATED
*
*/
//--------------------------------------------------------------------
CORBA::Long OMS_IPCIF_NoCmdNoVpiValve::notMated()
{
   rImpl_.setState(OMS_OPF_QD_ENUM::NOT_MATED);

   return OMS::PASS;
   
} // end OMS_IPCIF_NoCmdNoVpiValve::notMated



//--------------------------------------------------------------------
/**
* matedToGseOpen - Invokes the setState method of the 
* OMS_NoCmdNoVpiValve to set the QD state to MATED_TO_GSE_OPEN
*
*/
//--------------------------------------------------------------------
CORBA::Long OMS_IPCIF_NoCmdNoVpiValve::matedToGseOpen()
{
   rImpl_.setState(OMS_OPF_QD_ENUM::MATED_TO_GSE_OPEN);

   return OMS::PASS;
   
} // end OMS_IPCIF_NoCmdNoVpiValve::matedToGseOpen



//--------------------------------------------------------------------
/**
* matedToVehClosed - Invokes the setState method of the 
* OMS_NoCmdNoVpiValve to set the QD state to MATED_TO_VEH_CLOSED
*
*/
//--------------------------------------------------------------------
CORBA::Long OMS_IPCIF_NoCmdNoVpiValve::matedToVehClosed()
{
   rImpl_.setState(OMS_OPF_QD_ENUM::MATED_TO_VEH_CLOSED);

   return OMS::PASS;
   
} // end OMS_IPCIF_NoCmdNoVpiValve::matedToVehClosed



//--------------------------------------------------------------------
/**
* matedToVehPurge - Invokes the setState method of the 
* OMS_NoCmdNoVpiValve to set the QD state to MATED_TO_VEH_PURGE
*
*/
//--------------------------------------------------------------------
CORBA::Long OMS_IPCIF_NoCmdNoVpiValve::matedToVehPurge()
{
   rImpl_.setState(OMS_OPF_QD_ENUM::MATED_TO_VEH_PURGE);

   return OMS::PASS;
   
} // end OMS_IPCIF_NoCmdNoVpiValve::matedToVehPurge



//--------------------------------------------------------------------
/**
* matedToVehOpen - Invokes the setState method of the 
* OMS_NoCmdNoVpiValve to set the QD state to MATED_TO_VEH_OPEN
*
*/
//--------------------------------------------------------------------
CORBA::Long OMS_IPCIF_NoCmdNoVpiValve::matedToVehOpen()
{
   rImpl_.setState(OMS_OPF_QD_ENUM::MATED_TO_VEH_OPEN);

   return OMS::PASS;
   
} // end OMS_IPCIF_NoCmdNoVpiValve::matedToVehOpen

