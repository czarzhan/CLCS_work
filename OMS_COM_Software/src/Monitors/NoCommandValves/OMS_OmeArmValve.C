//=============================================================================
//
// NAME: OMS_OmeArmValve
//
// OVERVIEW: The OME arm valve isolates the GN2 tank from the regulator.
//           The regulated GN2 is used to actuate the bi-propellant valves.
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
#include "OMS_OmeArmValve.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================

RTC_IMPL_CLASS(OMS_OmeArmValve);

//-------------------------------------------------------------------------
/**
* 
* OMS_OmeArmValve constructor
* 
*/
//-------------------------------------------------------------------------
OMS_OmeArmValve::OMS_OmeArmValve(
   const RTC_String& rParentPath,
   const RTC_String& rIdentifier,
   Attributes_t attributes) :
   OMS_OmeArmValveBase(
      rParentPath,
      rIdentifier,
      attributes),
   RTC_INIT_ATTR(pOpenIndicator_),
   RTC_INIT_ATTR(pOpenASwitch_),
   RTC_INIT_ATTR(pOpenBSwitch_),
   RTC_INIT_ATTR(pElectricalStateRO_)
{
   RTC_TRACE_CTOR_ENTRY;

   RTC_TRACE_CTOR_EXIT;

} // end OMS_OmeArmValve::OMS_OmeArmValve


//-------------------------------------------------------------------------
/**
* OMS_OmeArmValve destructor
*/
//-------------------------------------------------------------------------
OMS_OmeArmValve::~OMS_OmeArmValve()
{
   RTC_TRACE_DTOR_ENTRY;
    
   RTC_TRACE_DTOR_EXIT;

} // end OMS_OmeArmValve::~OMS_OmeArmValve


//-------------------------------------------------------------------------
/**
*
* initialize - This method initializes the OmeArmValves, and registers for
* change data for the state calculation.
*
*/
//-------------------------------------------------------------------------
bool OMS_OmeArmValve::initialize()
{
   RTC_TRACE_ENTRY(initialize);

   // Set state health
   setPseudoHealthGood( stateFD(), "state", state());

   // return results of call to parent class
   return OMS_OmeArmValveBase::initialize();

   RTC_TRACE_EXIT;

} // end OMS_OmeArmValve::initialize


//-------------------------------------------------------------------------
/**
* terminate - Calls the parent terminate function, then deregisters change
*             data and sets the health to inactive
*/
//-------------------------------------------------------------------------
void OMS_OmeArmValve::terminate()
{
   RTC_TRACE_ENTRY(terminate);

   // Call parent method
   OMS_OmeArmValveBase::terminate();

   // Set state health
   setPseudoHealthInactive( stateFD(), "state" );

   RTC_TRACE_EXIT;

} // end OMS_OmeArmValve::terminate


//-------------------------------------------------------------------------
/**
* calculateState contains the algorithm to calculate the current state
* of the component when an FD that the state is composed of changes.
*
* This method will be registered with the Event Manager to perform synthesis
* on all the state calculation FDs to return the new state.  No FD writes
* need to be performed within, as the Event Manager writes the new state to
* its appropriate pseudo FD, also calculating the FD health information.
*
*/   
//-------------------------------------------------------------------------
CL_OP2_ENUM::CL_OP2_ENUM_t OMS_OmeArmValve::calculateState(
   const RTC_Event::FDInfo_t& FDs) const
{

   CL_OP2_ENUM::CL_OP2_ENUM_t result = CL_OP2_ENUM::OPEN_ERROR;

   Discrete::ON_OFF openIndState = RTC_FD_STATE( pOpenIndicator_ );
   Discrete::ON_OFF switchAState = RTC_FD_STATE( pOpenASwitch_ );
   Discrete::ON_OFF switchBState = RTC_FD_STATE( pOpenBSwitch_ );

   if (OMS_MATED_DEMATED::MATED is_eq (int) RTC_FD_STATE(pElectricalStateRO_))
   {
      if (Discrete::On is_eq switchAState and
          Discrete::On is_eq switchBState )
      {
         if (Discrete::On is_eq openIndState)
         {
            result = CL_OP2_ENUM::OPEN;
         }
      }
      else
      {
         if (Discrete::Off is_eq switchAState and
             Discrete::Off is_eq switchBState )
         {
            if (Discrete::Off is_eq openIndState)
            {
               result = CL_OP2_ENUM::CLOSED;
            }
            else
            {
               result = CL_OP2_ENUM::CLOSED_ERROR;
            }
         }
      }
   }
   else
   {
      result = CL_OP2_ENUM::UNSET;
   }

   return result;

} // end OMS_OmeArmValve::calculateState


//-------------------------------------------------------------------------
/**
* stateCalculationFDs is a function that should return a list of FDs that
* should be used to determine the state of the component.
*
* This list should contain any FDs, that upon their change, will affect 
* the state of this component.
*
*/   
//-------------------------------------------------------------------------
RTC_FDS::FDList_t OMS_OmeArmValve::stateCalculationFDs() const
{

   return RTC_list(pOpenIndicator_, 
                   pOpenASwitch_, 
                   pOpenBSwitch_, 
                   pElectricalStateRO_);

} // end OMS_OmeArmValve::stateCalculationFDs

