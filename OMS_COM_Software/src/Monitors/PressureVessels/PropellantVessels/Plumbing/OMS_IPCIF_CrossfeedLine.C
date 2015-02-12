//=============================================================================
//
// NAME: OMS_IPCIF_CrossfeedLine
//
// OVERVIEW: This is the IPC interface used to bind a reference of the 
//           OMS_CrossfeedLine class.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_CrossfeedLine.h"
#include "OMS_IPCIF_CrossfeedLine.h"
 
//=============================================================================
//                     Class Member Definitions
//=============================================================================

//-----------------------------------------------------------------------------
/**
* OMS_IPCIF_CrossfeedLine implementation
*/
//-----------------------------------------------------------------------------
OMS_IPCIF_CrossfeedLine::OMS_IPCIF_CrossfeedLine(
   OMS_CrossfeedLine& rImpl) :
   OMS_IPCIF_VehiclePlumbing(rImpl),
   rImpl_(rImpl)
{
} // end OMS_IPCIF_CrossfeedLine


//--------------------------------------------------------------------
/**
* IPC Interface destructor implementation
*/
//--------------------------------------------------------------------
OMS_IPCIF_CrossfeedLine::~OMS_IPCIF_CrossfeedLine()
{
} // end destructor


//--------------------------------------------------------------------
/**
* toggleLeftFlangeState 
*/
//--------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CrossfeedLine::toggleLeftFlangeState()
{
   rImpl_.toggleLeftFlangeState();

   return OMS::PASS;

} // end toggleLeftFlangeState

//--------------------------------------------------------------------
/**
* toggleLeftFlangeState 
*/
//--------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CrossfeedLine::toggleRightFlangeState()
{
   rImpl_.toggleRightFlangeState();

   return OMS::PASS;

} // end toggleRightFlangeState
