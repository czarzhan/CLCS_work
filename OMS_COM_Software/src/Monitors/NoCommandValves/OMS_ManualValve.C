//=============================================================================
//
// NAME: OMS_ManualValve
//
// OVERVIEW:  The Manual Valve has no remote control and no monitor capability.
//            The valve state is maintained for configuration information.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                      System Include Files
//=============================================================================
#include <CL_OP_ENUM.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_ManualValve.h"
  
//=============================================================================
//                     Class Member Definitions
//=============================================================================

RTC_IMPL_CLASS(OMS_ManualValve);

//-------------------------------------------------------------------------
/**
*
* OMS_ManualValve constructor implementation 
* 
*/
//-------------------------------------------------------------------------
OMS_ManualValve::OMS_ManualValve(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier) :
   OMS_Object(rParentPath,
              rIdentifier),
   RTC_INIT_ATTR(pState_), 
   RTC_IMPL_ATTRIBUTE(persistentState_, state)
{
   RTC_TRACE_CTOR_ENTRY;

   RTC_TRACE_CTOR_EXIT;

} // end OMS_ManualValve::OMS_ManualValve

//-------------------------------------------------------------------------
/**
*
* OMS_ManualValve destructor implementation.
*
*/
//-------------------------------------------------------------------------
OMS_ManualValve::~OMS_ManualValve()
{
   RTC_TRACE_DTOR_ENTRY;

   RTC_TRACE_DTOR_EXIT;

} // end OMS_ManualValve::~OMS_ManualValve


//-------------------------------------------------------------------------
/**
* The toggle function works as follows: If the state is CLOSED,
* set the state to OPEN; otherwise set the state to CLOSED.
*/
//-------------------------------------------------------------------------
void RTC_IMPL(OMS_ManualValve::toggle) ()
{
   RTC_TRACE_ENTRY(toggle);

   Int32_t vlvState;

   readEnum(pState_, "state", "toggle", vlvState);
   
   // If the readEnum reads CLOSED, the state will be set to OPEN.
   // Otherwise, the state will be set to CLOSED.
   if (CL_OP_ENUM::CLOSED is_eq vlvState)
   {
      Set(pState_, CL_OP_ENUM::OPEN);
      
      persistentState_ = CL_OP_ENUM::OPEN;
   }
   else
   {
      Set(pState_, CL_OP_ENUM::CLOSED);
      
      persistentState_ = CL_OP_ENUM::CLOSED;
   }
   
   RTC_TRACE_EXIT;

} // end OMS_ManualValve::toggle


//-------------------------------------------------------------------------
/**
* initialize - This method initializes the valve's state to the persistent
* value, and calls the parent class method.
*/
//-------------------------------------------------------------------------
bool OMS_ManualValve::initialize()
{

   RTC_TRACE_ENTRY(initialize);

   // Initialize persistence for OMS_ManualValve
   initializePersistence();

   // Set pseudo health to good
   setPseudoHealthGood(pState_, "state", persistentState_);

   return OMS_Object::initialize();

} // end initialize


//-------------------------------------------------------------------------
/**
* terminate - This method calls the parent class method, and sets health
* of the pseudo to Inactive.
*/
//-------------------------------------------------------------------------
void OMS_ManualValve::terminate()
{

   RTC_TRACE_ENTRY(terminate);

   // Call parent method
   OMS_Object::terminate();

   // Set pseudo health to Inactive
   setPseudoHealthInactive(pState_, "state");

   RTC_TRACE_EXIT;

} // end terminate




//-------------------------------------------------------------------------
/**
* listMethods - This method adds class methods to the methods
* list to be displayed by the TADD.
*/
//-------------------------------------------------------------------------
void OMS_ManualValve::listMethods(
   RTC_IPCInterface::DisplayObj::List_t& rMethods)
{
   rMethods.addField("toggle");

} // end listMethods


//-------------------------------------------------------------------------
/**
* createIPCInterface instantiates an interprocess communication interface.
*
*/
//-----------------------------------------------------------------------------
RTC_IPCMan::ObjInterface_t OMS_ManualValve::createIPCInterface()
{
   OMS_IPCIF_ManualValve* pIpcIf;
   RTC_NEW( pIpcIf, OMS_IPCIF_ManualValve(*this));

   return pIpcIf;
}


