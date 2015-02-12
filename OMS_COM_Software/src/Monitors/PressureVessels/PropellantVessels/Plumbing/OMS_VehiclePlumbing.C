//=============================================================================
//
// NAME: OMS_VehiclePlumbing
//
// OVERVIEW: Vehicle Plumbing is the base class for propellant line segments
//           between the tank isolation valves and the OMS Engine or RCS 
//           Thrusters.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                      System Include Files
//=============================================================================
#include <MANIFOLD_ENUM.h>
 
//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_VehiclePlumbing.h"
#include "OMS_VehiclePlumbing.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================
RTC_IMPL_CLASS(OMS_VehiclePlumbing);

//-----------------------------------------------------------------------------
/**
* OMS_VehiclePlumbing constructor implementation
*/
//-----------------------------------------------------------------------------
OMS_VehiclePlumbing::OMS_VehiclePlumbing(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier//,
   /*OMS::Commodity_t commodityType*/ ) :
   OMS_Object(rParentPath,
              rIdentifier ),
   //commodityType_(commodityType),
   RTC_INIT_ATTR(pState_),
   RTC_IMPL_ATTRIBUTE_DEF(persistentState_, state, MANIFOLD_ENUM::UNKNOWN)
{
   RTC_TRACE_CTOR_ENTRY;

   RTC_TRACE_CTOR_EXIT;

} // end constructor


//-----------------------------------------------------------------------------
/**
* OMS_VehiclePlumbing destructor implementation
*/
//-----------------------------------------------------------------------------
OMS_VehiclePlumbing::~OMS_VehiclePlumbing()
{
   RTC_TRACE_DTOR_ENTRY;

   RTC_TRACE_DTOR_EXIT;

} // end destructor


//-----------------------------------------------------------------------------
/**
* This method toggles the state to the next value {FULL, DRAINED,
* DECONTAMINATED}.  If the state is FULL, it is set to DRAINED; 
* if DRAINED, set to DECONTAMINATED; else set to FULL.
* NOTE:  The contamination state of the plumbing is kept persistently. 
*/
//-----------------------------------------------------------------------------
void RTC_IMPL( OMS_VehiclePlumbing::toggle )()
{
   RTC_TRACE_ENTRY(toggle);

   try
   {
      Int32_t currentState;
      
      if( OMS::PASS is_eq readEnum( pState_, currentState ))
      {
         switch(currentState)
         {
            case MANIFOLD_ENUM::FULL:
               Set(pState_, MANIFOLD_ENUM::DRAINED);
               persistentState_ = MANIFOLD_ENUM::DRAINED;
               break;
            case MANIFOLD_ENUM::DRAINED:
               Set(pState_, MANIFOLD_ENUM::DECONTAMINATED);
               persistentState_ = MANIFOLD_ENUM::DECONTAMINATED;
               break;
            case MANIFOLD_ENUM::DECONTAMINATED:
            case MANIFOLD_ENUM::UNKNOWN:
               Set(pState_, MANIFOLD_ENUM::FULL);
               persistentState_ = MANIFOLD_ENUM::FULL;
               break;
            default:
               RTC_SEND_WARN(
                  "Action failed: FD value falls outside of enumerated type.");
         } // end switch
      } // end if
   }
   catch ( ... )
   {
      RTC_SEND_WARN(
         "toggleContaminationState failed: Unknown Exception raised." );
   }

   RTC_TRACE_EXIT;

} // end toggle



//-----------------------------------------------------------------------------
/**
* initialize 
*/
//-----------------------------------------------------------------------------
bool OMS_VehiclePlumbing::initialize()
{
   RTC_TRACE_ENTRY(initialize);

   // Set pseudo health to good
   setPseudoHealthGood(pState_, "state", persistentState_);

   RTC_TRACE_EXIT;

   return OMS_Object::initialize();

} // end initialize


//-----------------------------------------------------------------------------
/**
* terminate 
*/
//-----------------------------------------------------------------------------
void OMS_VehiclePlumbing::terminate()
{
   RTC_TRACE_ENTRY(terminate);

   // Call parent method
   OMS_Object::terminate();

   // Set pseudo health to Inactive
   setPseudoHealthInactive(pState_, "state");

   RTC_TRACE_EXIT;

} // end terminate


//-----------------------------------------------------------------------------
/**
* createIPCInterface
*/
//-----------------------------------------------------------------------------
RTC_IPCMan::ObjInterface_t OMS_VehiclePlumbing::createIPCInterface()
{
   OMS_IPCIF_VehiclePlumbing* pIpcIf;
   RTC_NEW( pIpcIf, OMS_IPCIF_VehiclePlumbing(*this));

   return pIpcIf;

} // end createIPCInterface


//-----------------------------------------------------------------------------
/**
* listMethods - This method adds class methods to the methods
* list to be displayed by the TADD.
*
*/
//-----------------------------------------------------------------------------
void OMS_VehiclePlumbing::listMethods(
   RTC_IPCInterface::DisplayObj::List_t& rMethods)
{
   RTC_TRACE_ENTRY(listMethods);

   rMethods.addField("toggleContaminationState");

   RTC_TRACE_EXIT;

}  // end listMethods
