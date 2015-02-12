//=============================================================================
//
// NAME: OMS_ManifoldLeg
//
// OVERVIEW: This class represents the components that provide the propellant
//           path from the tank isolation valves to the manifold isolation 
//           valves for the forward reaction control thrusters.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                      System Include Files
//=============================================================================
#include <CL_OP2_ENUM.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_ManifoldLeg.h"

RTC_IMPL_CLASS(OMS_ManifoldLeg);

//-------------------------------------------------------------------------
/**
* OMS_ManifoldLeg
*
* @param rParentPath  specifies the path of the parent object that this 
*                     object is an aggregate of.
* @param rIdentifier  specifies an id which is concatenated to the 
*                     rParentPath to form a unique path for this object. 
*                     The path is used to retrieve instance data 
*                     from the Instance Map. 
* @param commodityType defines whether the component is for FUEL or OXID
*/
//-------------------------------------------------------------------------
OMS_ManifoldLeg::OMS_ManifoldLeg(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier) :
   OMS_VehiclePlumbing(
      rParentPath,
      rIdentifier),
   RTC_INIT_ATTR(pOffsetCorrectedPressure_),
   RTC_INIT_ATTR(pPropTankPressureRO_),
   RTC_INIT_ATTR(pTkIsoValveAStateRO_),
   RTC_INIT_ATTR(pManifoldAPressureRO_),
   RTC_INIT_ATTR(pManifoldBPressureRO_),
   RTC_INIT_ATTR(pManifoldIsoAStateRO_),
   RTC_INIT_ATTR(pManifoldIsoBStateRO_)
{
   RTC_TRACE_CTOR_ENTRY;

   RTC_TRACE_CTOR_EXIT;

} // end constructor

//-------------------------------------------------------------------------
/**
* OMS_ManifoldLeg destructor
*/
//-------------------------------------------------------------------------
OMS_ManifoldLeg::~OMS_ManifoldLeg()
{
   RTC_TRACE_DTOR_ENTRY;

   RTC_TRACE_DTOR_EXIT;

} // end destructor


//-------------------------------------------------------------------------
/**
* initialize 
*/
//-------------------------------------------------------------------------
bool OMS_ManifoldLeg::initialize()
{
   RTC_TRACE_ENTRY(initialize);
   
   // Register FD monitor for calcPressure
   When_Interrupt(
      pressureCalcFDs(),
      RTC_action(this, &OMS_ManifoldLeg::calcPressure),
      true);

   RTC_TRACE_EXIT;

   return OMS_VehiclePlumbing::initialize();

} // end initialize


//-------------------------------------------------------------------------
/**
* terminate 
*/
//-------------------------------------------------------------------------
void OMS_ManifoldLeg::terminate()
{
   RTC_TRACE_ENTRY(terminate);
   
   // Call parent method
   OMS_VehiclePlumbing::terminate();
   
   // Deactivate pseudo health checking
   setPseudoHealthInactive( pOffsetCorrectedPressure_,
                            "offsetCorrectedPressure" );
   
   RTC_TRACE_EXIT;

} // end terminate
 

//-------------------------------------------------------------------------
/**
* calcPressure
*/
//-------------------------------------------------------------------------
void RTC_IMPL(OMS_ManifoldLeg::calcPressure)
   (const RTC_Event::FDInfo_t FDs)
{
   // Initialize local variable for internal calculations, and a boolean
   // to determine if we set the pseudo.
   Float64_t pressureValue;
   bool publish = false;

   // Get FD information
   RTC_FDS::FDValue_t tankIsoAState = RTC_FD_STATE(pTkIsoValveAStateRO_);

   // Create booleans to clarify if statements
   bool tankVlvAOpen = (not( tankIsoAState.fail or tankIsoAState.stale )and
                        CL_OP2_ENUM::OPEN is_eq Int32_t (tankIsoAState));

   // Check that the Tank isolation valve is open and for valid data
   // from the tank and the valve.
   if ( tankVlvAOpen )
   {
      RTC_FDS::FDValue_t propTankPress = RTC_FD_STATE(pPropTankPressureRO_);

      bool tkPressureGood = (not(propTankPress.fail or propTankPress.stale ));

      if ( tkPressureGood )
      {
         // Set the pressure to that of the propellant tank
         pressureValue = propTankPress;
         publish = true;
      }
   }
   else
   {
      // Get FD information
      RTC_FDS::FDValue_t manifoldIsoASt = RTC_FD_STATE(pManifoldIsoAStateRO_);

      // Create booleans to clarify if statements
      bool manifoldAOpen = (not(manifoldIsoASt.fail or
                                manifoldIsoASt.stale ) and
                            CL_OP2_ENUM::OPEN is_eq Int32_t(manifoldIsoASt));

      // Check for valid data from the "A" manifold and its isolation valve
      // and that the valve is open.
      if( manifoldAOpen )
      {
         RTC_FDS::FDValue_t manifoldAPress = 
            RTC_FD_STATE(pManifoldAPressureRO_);

         bool manifldAPressGood = (not(manifoldAPress.fail or
                                       manifoldAPress.stale));

         if ( manifldAPressGood )
         {
            pressureValue = manifoldAPress;
            publish = true;
         }
      }
      else
      {
         // Get FD information
         RTC_FDS::FDValue_t manifoldIsoBSt = 
            RTC_FD_STATE(pManifoldIsoBStateRO_);

         // Create booleans to clarify if statements
         bool manifoldBOpen = (not(manifoldIsoBSt.fail or
                                   manifoldIsoBSt.stale ) and
                               CL_OP2_ENUM::OPEN is_eq 
                                  Int32_t(manifoldIsoBSt));

         // Check for valid data from the "B" manifold and its isolation
         // valve and that the valve is open.
         if( manifoldBOpen )
         {
            RTC_FDS::FDValue_t manifoldBPress = 
               RTC_FD_STATE(pManifoldBPressureRO_);
            
            bool manifldBPressGood = (not(manifoldBPress.fail or
                                          manifoldBPress.stale));

            if ( manifldBPressGood )
            {
               pressureValue = manifoldBPress;
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
 
//-------------------------------------------------------------------------
/**
* pressureCalcFDs 
*/   
//-------------------------------------------------------------------------
RTC_FDS::FDList_t OMS_ManifoldLeg::pressureCalcFDs() const
{
   return RTC_list( pPropTankPressureRO_,
                    pTkIsoValveAStateRO_,
                    pManifoldAPressureRO_,
                    pManifoldBPressureRO_,
                    pManifoldIsoAStateRO_,
                    pManifoldIsoBStateRO_ );

} // end pressureCalcFDs
