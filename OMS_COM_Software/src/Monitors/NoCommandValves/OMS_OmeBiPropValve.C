//=============================================================================
//
// NAME: OMS_OmeBiPropValve
//
// OVERVIEW: The OME Bi-Prop valve isolates propellant from the OMS engine 
//           chamber. The valves have no commands, they are pressure actuated
//           with GN2 through the OmeArmValve and down stream regulator.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                      System Include Files
//=============================================================================
#include <CAS_ANALOG1_ENUM.h>
#include <OMS_MATED_DEMATED.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_OmeBiPropValve.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================

RTC_IMPL_CLASS(OMS_OmeBiPropValve);

//-------------------------------------------------------------------------
/**
*
* OMS_OmeBiPropValve constructor
*
*/
//-------------------------------------------------------------------------
OMS_OmeBiPropValve::OMS_OmeBiPropValve(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier,
   bool initToValid,
   Attributes_t attributes) :
   OMS_OmeBiPropValveBase(rParentPath,
                          rIdentifier,
                          attributes ),
   RTC_INIT_ATTR(pElectricalStateRO_)
{
   RTC_TRACE_CTOR_ENTRY;
   
   RTC_SUBCOMP_CREATE(
      pOpenIndicator_,
      OMS_AnalogWithLccLimits(
         objPath(),
         "PCT",
         initToValid));
   
   RTC_TRACE_CTOR_EXIT;

} //end OMS_OmeBiPropValve::OMS_OmeBiPropValve



//-------------------------------------------------------------------------
/**
*
* OMS_OmeBiPropValve destructor
*
*/
//-------------------------------------------------------------------------
OMS_OmeBiPropValve::~OMS_OmeBiPropValve()
{
   RTC_TRACE_DTOR_ENTRY;

   RTC_SUBCOMP_DELETE( pOpenIndicator_ );
    
   RTC_TRACE_DTOR_EXIT;

} // end OMS_OmeBiPropValve::~OMS_OmeBiPropValve


//-------------------------------------------------------------------------
/**
*
* initialize - This method initializes the OmeBiPropValves, and returns 
* a call to the parent class.
*
*/
//-------------------------------------------------------------------------
bool OMS_OmeBiPropValve::initialize()
{
   RTC_TRACE_ENTRY(initialize);

   // Set state health
   setPseudoHealthGood( stateFD(), "state", state());

   // return results of call to parent class
   return OMS_OmeBiPropValveBase::initialize();

   RTC_TRACE_EXIT;

} // end OMS_OmeBiPropValve::initialize

//-------------------------------------------------------------------------
/**
* terminate - Calls the parent terminate method and deregisters the FDs.
*/
//-------------------------------------------------------------------------
void OMS_OmeBiPropValve::terminate()
{
   RTC_TRACE_ENTRY(terminate);

   // Call parent method
   OMS_OmeBiPropValveBase::terminate();

   // Set state health
   setPseudoHealthInactive( stateFD(), "state" );

   RTC_TRACE_EXIT;

} // end OMS_OmeBiPropValve::terminate


//-------------------------------------------------------------------------
/**
* setValid calls the activateStateSynthesis command
* 
* This method is meant to be called subsequent to deactivating state 
* calculation when it is desired to begin calculating the component's
* state again.
*/
//-------------------------------------------------------------------------
void OMS_OmeBiPropValve::setValid()
{
   RTC_TRACE_ENTRY(setValid);
   
   try
   {
      pOpenIndicator_->setValid();
   }
   catch ( ... )
   {
      RTC_SEND_WARN("State synthesis failed: Unknown Exception raised.");
   }

   RTC_TRACE_EXIT;

} // end OMS_OmeBiPropValve::setValid


//-------------------------------------------------------------------------
/**
* setInvalid call the overrideStateSynthesis command
* 
* This method is used to set the state to UNSET and deactivate state 
* calculation.
*/
//-------------------------------------------------------------------------
void OMS_OmeBiPropValve::setInvalid()
{
   RTC_TRACE_ENTRY(setInvalid);
   
   try
   {
      pOpenIndicator_->setInvalid();
   }
   catch ( ... )
   {
      RTC_SEND_WARN(
         "State synthesis not overridden: Unknown Exception raised.");
   }
   
   RTC_TRACE_EXIT;

} // end OMS_OmeBiPropValve::setInvalid


//-------------------------------------------------------------------------
/**
* calculateState contains the algorithm to calculate the current state
* of the component when an FD that the state is composed of changes.
*
* This method will be registered with the Event Manager to perform synthesis
* on all the state calculation FDs to return the new state.  No FD writes
* need to be performed within, as the Event Manager writes the new state to
* its appropriate pseudo FD, also calculating the FD health information.
*/
//-------------------------------------------------------------------------
CL_OP_ENUM::CL_OP_ENUM_t OMS_OmeBiPropValve::calculateState(
   const RTC_Event::FDInfo_t& FDs) const
{

   Float64_t value = (RTC_FD_STATE(pOpenIndicator_->analogFD()));

   // Check that the engine's electrical system is MATED.
   if (OMS_MATED_DEMATED::MATED is_eq (int) RTC_FD_STATE(pElectricalStateRO_))
   {
      // If the analog is more than 5%, the valve's state will be set to OPEN,
      // otherwise it will be set to CLOSED.
      if ( value > 5 )
      {
         return CL_OP_ENUM::OPEN;
      }
      else
      {
         return CL_OP_ENUM::CLOSED;
      }
   }
   else
   {
      // If the engine is DEMATED, the valve is UNSET
      return CL_OP_ENUM::UNSET;
   }
}


//-------------------------------------------------------------------------
/**
* stateCalculationFDs is a function that should return a list of FDs that
* should be used to determine the state of the component.
*
* This list should contain any FDs, that upon their change, will affect 
* the state of this component.
*/   
//-------------------------------------------------------------------------
RTC_FDS::FDList_t OMS_OmeBiPropValve::stateCalculationFDs() const
{

   return RTC_list( pOpenIndicator_->analogFD(), pElectricalStateRO_ );

}
