//=============================================================================
//
// NAME: OMS_CrossfeedLine
//
// OVERVIEW: OMS_CrossfeedLine class provides functionality for the propellant
//           path between the OMS and RCS systems within the same pod and 
//           through the orbiter to the opposite pod.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                      System Include Files
//=============================================================================
#include <OMS_MATED_DEMATED.h>
 
//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_CrossfeedLine.h"
#include "OMS_IPCIF_CrossfeedLine.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================
RTC_IMPL_CLASS(OMS_CrossfeedLine);

OMS_CrossfeedLine::OMS_CrossfeedLine(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier) :
   OMS_PrimaryManifold(
      rParentPath,
      rIdentifier),
   RTC_INIT_ATTR(pLeftFlangeState_),
   RTC_INIT_ATTR(pRightFlangeState_),
   RTC_IMPL_ATTRIBUTE_DEF(persistentLeftState_,
                          leftState,
                          OMS_MATED_DEMATED::UNSET),
   RTC_IMPL_ATTRIBUTE_DEF(persistentRightState_,
                          rightState,
                          OMS_MATED_DEMATED::UNSET)
{
   RTC_TRACE_CTOR_ENTRY;

   RTC_TRACE_CTOR_EXIT;

} // end constructor


//-------------------------------------------------------------------------
/**
* OMS_CrossfeedLine destructor implementation
*/
//-------------------------------------------------------------------------
OMS_CrossfeedLine::~OMS_CrossfeedLine()
{
   RTC_TRACE_DTOR_ENTRY;

   RTC_TRACE_DTOR_EXIT;

} // end destructor


//-------------------------------------------------------------------------
/**
* toggleRightFlangeState  
*/
//-------------------------------------------------------------------------
void RTC_IMPL(OMS_CrossfeedLine::toggleRightFlangeState) ()
{
   RTC_TRACE_ENTRY(toggleRightFlangeState);

   try
   {
      Int32_t currentState;
      
      readEnum( pRightFlangeState_, currentState);
      if(OMS_MATED_DEMATED::MATED is_eq currentState)
      {
         Set(pRightFlangeState_, OMS_MATED_DEMATED::DEMATED);
         persistentRightState_ = OMS_MATED_DEMATED::DEMATED;
      }
      else
      {
         Set(pRightFlangeState_, OMS_MATED_DEMATED::MATED);
         persistentRightState_ = OMS_MATED_DEMATED::MATED;
      }
   }
   catch ( ... )
   {
      RTC_SEND_WARN(
         "toggleRightFlangeState failed: Unknown Exception raised." );
   }

   RTC_TRACE_EXIT;

} // end toggleRightFlangeState


//-------------------------------------------------------------------------
/**
* toggleLeftFlangeState 
*/
//-------------------------------------------------------------------------
void RTC_IMPL(OMS_CrossfeedLine::toggleLeftFlangeState) ()
{
   RTC_TRACE_ENTRY(toggleLeftFlangeState);

   try
   {
      Int32_t currentState;
      
      readEnum( pLeftFlangeState_, currentState);

      if(OMS_MATED_DEMATED::MATED is_eq currentState)
      {
         Set(pLeftFlangeState_, OMS_MATED_DEMATED::DEMATED);
         persistentLeftState_ = OMS_MATED_DEMATED::DEMATED;
      }
      else
      {
         Set(pLeftFlangeState_, OMS_MATED_DEMATED::MATED);
         persistentLeftState_ = OMS_MATED_DEMATED::MATED;
      }
   }
   catch ( ... )
   {
      RTC_SEND_WARN(
         "toggleLeftFlangeState failed: Unknown Exception raised." );
   }

   RTC_TRACE_EXIT;

} // end toggleLeftFlangeState


//--------------------------------------------------------------------------
/**
* initialize 
*/
//--------------------------------------------------------------------------
bool OMS_CrossfeedLine::initialize()
{
   RTC_TRACE_ENTRY(initialize);

   // Set pseudo health to good
   setPseudoHealthGood( pLeftFlangeState_,
                        "leftFlangeState",
                        persistentLeftState_ );
   setPseudoHealthGood( pRightFlangeState_,
                        "rightFlangeState",
                        persistentRightState_ );

   // Return a call to the parent method
   return OMS_PrimaryManifold::initialize();

   RTC_TRACE_EXIT;

}


//--------------------------------------------------------------------------
/**
* terminate 
*/
//--------------------------------------------------------------------------
void OMS_CrossfeedLine::terminate()
{
   RTC_TRACE_ENTRY(terminate);

   // Call parent method
   OMS_PrimaryManifold::terminate();

   // Set pseudo health to Inactive
   setPseudoHealthInactive( pLeftFlangeState_,
                            "leftFlangeState");
   setPseudoHealthInactive( pRightFlangeState_,
                            "rightFlangeState");

   RTC_TRACE_EXIT;

}


//--------------------------------------------------------------------------
/**
* listMethods 
*/
//--------------------------------------------------------------------------
void OMS_CrossfeedLine::listMethods(
   RTC_IPCInterface::DisplayObj::List_t& rMethods)
{
   RTC_TRACE_ENTRY(listMethods);

   // List VehiclePlumbing methods.
   OMS_VehiclePlumbing::listMethods(rMethods);

   // Add new methods
   rMethods.addField("toggleLeftFlangeState");
   rMethods.addField("toggleRightFlangeState");

   RTC_TRACE_EXIT;

}  // end listMethods


//--------------------------------------------------------------------------
/**
* createIPCInterface
*/
//--------------------------------------------------------------------------
RTC_IPCMan::ObjInterface_t OMS_CrossfeedLine::createIPCInterface()
{
   OMS_IPCIF_CrossfeedLine* pIpcIf;
   RTC_NEW( pIpcIf, OMS_IPCIF_CrossfeedLine(*this));

   return pIpcIf;
} // end createIPCInterface
