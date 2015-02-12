//=============================================================================
//
// NAME: OMS_OmsFeedline
//
// OVERVIEW: The OMS Feedlines are the plumbing between the tank isolation 
//           valves and the OMS engine flange. Each oxidizer feedline is 
//           instrumented with a single temperature sensor.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                      System Include Files
//=============================================================================
#include <OMS_MATED_DEMATED.h>
#include <CL_OP2_ENUM.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_OmsFeedline.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================

RTC_IMPL_CLASS(OMS_OmsFeedline);

//-----------------------------------------------------------------------------
/**
* OMS_OmsFeedline constructor implementation
*/
//-----------------------------------------------------------------------------
OMS_OmsFeedline::OMS_OmsFeedline(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier,
   OMS::Commodity_t commodityType) :
   OMS_VehiclePlumbing(rParentPath,
                       rIdentifier),
   RTC_INIT_ATTR(pOffsetCorrectedPressure_),
   RTC_INIT_ATTR(pPropTankPressureRO_),
   RTC_INIT_ATTR(pTkIsoValveAStateRO_),
   RTC_INIT_ATTR(pTkIsoValveBStateRO_),
   RTC_INIT_ATTR(pXfdLinePressureRO_),
   RTC_INIT_ATTR(pXfdIsoValveAStateRO_),
   RTC_INIT_ATTR(pXfdIsoValveBStateRO_),
   RTC_INIT_ATTR(pOmeFlangeStateRO_),
   RTC_INIT_ATTR(pOmeInletLinePressureRO_)
{
   RTC_TRACE_CTOR_ENTRY;

   if(OMS::OXID is_eq commodityType)
   {
      RTC_SUBCOMP_CREATE(
         pTemperature_,
         OMS_AnalogWithLccLimits(
            objPath(),
            "TEMP" ) ) ;
   }
   else
   {
      pTemperature_ = NULL;
   }

   RTC_TRACE_CTOR_EXIT;

} // end constructor
  

//-----------------------------------------------------------------------------
/**
* OMS_OmsFeedline destructor implementation
*/
//-----------------------------------------------------------------------------
OMS_OmsFeedline::~OMS_OmsFeedline()
{
   RTC_TRACE_DTOR_ENTRY;

   if( not(NULL is_eq pTemperature_ ))
   {
      RTC_SUBCOMP_DELETE( pTemperature_ );
   }

   RTC_TRACE_DTOR_EXIT;

} // end destructor


//-----------------------------------------------------------------------------
/**
* initialize 
*/
//-----------------------------------------------------------------------------
bool OMS_OmsFeedline::initialize()
{
   RTC_TRACE_ENTRY(initialize);

   // Register FD monitor for calcPressure
   When_Interrupt(
      RTC_list( pTkIsoValveAStateRO_,
                pTkIsoValveBStateRO_,
                pXfdIsoValveAStateRO_,
                pXfdIsoValveBStateRO_,
                pOmeFlangeStateRO_,
                pPropTankPressureRO_,
                pXfdLinePressureRO_,
                pOmeInletLinePressureRO_ ),
      RTC_action(this, &OMS_OmsFeedline::calcPressure),
      true);

   RTC_TRACE_EXIT;

   return OMS_VehiclePlumbing::initialize();

} // end initialize


//-----------------------------------------------------------------------------
/**
* terminate 
*/
//-----------------------------------------------------------------------------
void OMS_OmsFeedline::terminate()
{
   RTC_TRACE_ENTRY(terminate);

   // Call parent method
   OMS_VehiclePlumbing::terminate();

   // Deactivate pseudo health checking
   setPseudoHealthInactive( pOffsetCorrectedPressure_,
                            "offsetCorrectedPressure" );
   
   RTC_TRACE_EXIT;

} // end terminate


//-----------------------------------------------------------------------------
/**
* calcPressure 
*/
//-----------------------------------------------------------------------------
void RTC_IMPL(OMS_OmsFeedline::calcPressure) (const RTC_Event::FDInfo_t FDs)
{
   // Initialize local variable for internal calculations, and a boolean
   // to determine if we set the pseudo.
   Float64_t pressureValue;
   bool publish = false;

   // Get FD information
   RTC_FDS::FDValue_t inletLinePress = RTC_FD_STATE(pOmeInletLinePressureRO_);

   // Create booleans to clarify if statement
   bool inletPressureGood = (not(inletLinePress.fail or inletLinePress.stale));

   // Check the OME Inlet Line and the OMS Engine for valid data and if 
   // the engine is mated.
   if( inletPressureGood )
   {
      RTC_FDS::FDValue_t omeFlangeState = RTC_FD_STATE(pOmeFlangeStateRO_);
      
      bool flangeMated = (not(omeFlangeState.fail or omeFlangeState.stale) and
                          OMS_MATED_DEMATED::MATED 
                             is_eq Int32_t(omeFlangeState));

      if ( flangeMated )
      {
      // Set the pressure to that of the OME Inlet Line.
      pressureValue = inletLinePress;
      publish = true;
      }
   }
   else
   {
      // Get FD information
      RTC_FDS::FDValue_t tankIsoAState = RTC_FD_STATE(pTkIsoValveAStateRO_);
      RTC_FDS::FDValue_t tankIsoBState = RTC_FD_STATE(pTkIsoValveBStateRO_);

      // Create booleans to clarify if statement
      bool tankVlvAOpen = (not( tankIsoAState.fail or tankIsoAState.stale )and
                           CL_OP2_ENUM::OPEN is_eq Int32_t (tankIsoAState));

      bool tankVlvBOpen = (not(tankIsoBState.fail or tankIsoBState.stale) and
                           CL_OP2_ENUM::OPEN is_eq Int32_t(tankIsoBState));

      // Check the tank and its isolation valves for valid data and if
      // the tank isolation valves are open.
      if( tankVlvAOpen or tankVlvBOpen )
      {
         RTC_FDS::FDValue_t propTankPress = RTC_FD_STATE(pPropTankPressureRO_);
         
         bool tkPressureGood = (not (propTankPress.fail 
                                     or propTankPress.stale ));
         
         if ( tkPressureGood )
         {
            // Set the pressure to that of the Propellant tank.
            pressureValue = propTankPress;
            publish = true;
         }
      }
      else
      {
         // Get FD information
         RTC_FDS::FDValue_t xfdIsoAState = RTC_FD_STATE(pXfdIsoValveAStateRO_);
         RTC_FDS::FDValue_t xfdIsoBState = RTC_FD_STATE(pXfdIsoValveBStateRO_);

         // Create booleans to clarify if statement
         bool xfdIsoAOpen = (not(xfdIsoAState.fail or xfdIsoAState.stale) and
                             CL_OP2_ENUM::OPEN is_eq Int32_t (xfdIsoAState));

         bool xfdIsoBOpen = (not(xfdIsoBState.fail or xfdIsoBState.stale) and
                             CL_OP2_ENUM::OPEN is_eq Int32_t (xfdIsoBState));

         // Check the crossfeed line and its isolation valves for valid data
         // and if the crossfeed isolation valves are open.
         if ( xfdIsoAOpen or xfdIsoBOpen )
         {
            RTC_FDS::FDValue_t xfdLinePress = 
               RTC_FD_STATE(pXfdLinePressureRO_);

            bool xfdPressGood = (not(xfdLinePress.fail or xfdLinePress.stale));

            if ( xfdPressGood )
            {
               // Set the pressure to that of the crossfeed line.
               pressureValue = xfdLinePress;
               publish = true;
            }
         }
         else
         {
            setPseudoHealthBad(pOffsetCorrectedPressure_, 
                               "offsetCorrectedPressure");
         }
      }
   }
   if( publish )
   {
      Set(pOffsetCorrectedPressure_, pressureValue);
   }

} // end calcPressure
