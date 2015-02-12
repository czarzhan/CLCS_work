//=============================================================================
//
// NAME: OMS_VernierManifold
//
// OVERVIEW: The Vernier Manifolds provide a propellant path from the manifold
//           isolation valves to the vernier thruster valves. There is one 
//           vernier manifold for each of the fuel and oxidizer legs. These 
//           are identical in function to the primary manifolds except for 
//           the logic used to determine the manifold pressure.
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
#include "OMS_VernierManifold.h"

RTC_IMPL_CLASS(OMS_VernierManifold);

//-------------------------------------------------------------------------
/**
* OMS_VernierManifold constructor implementation
*/
//-------------------------------------------------------------------------
OMS_VernierManifold::OMS_VernierManifold(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier) : 
   OMS_VehiclePlumbing(
      rParentPath,
      rIdentifier),
   RTC_INIT_ATTR(pOffsetCorrectedPressure_),
   RTC_INIT_ATTR(pManifoldIsoStateRO_) ,
   RTC_INIT_ATTR(pManifoldLegPressureRO_)
{
   RTC_TRACE_CTOR_ENTRY;

   RTC_TRACE_CTOR_EXIT;

} // end OMS_VernierManifold

//-------------------------------------------------------------------------
/**
* OMS_VernierManifold destructor implementation
*/
//-------------------------------------------------------------------------
OMS_VernierManifold::~OMS_VernierManifold()
{
   RTC_TRACE_DTOR_ENTRY;

   RTC_TRACE_DTOR_EXIT;

} // end ~OMS_VernierManifold


//--------------------------------------------------------------------------
/**
* initialize 
*/
//--------------------------------------------------------------------------
bool OMS_VernierManifold::initialize()
{
   RTC_TRACE_ENTRY(initialize);

   // Register FD monitor for calcPressure
   When_Interrupt(
      RTC_list( pManifoldIsoStateRO_, pManifoldLegPressureRO_),
      RTC_action(this, &OMS_VernierManifold::calcPressure),
      true);

   RTC_TRACE_EXIT;

   return OMS_VehiclePlumbing::initialize();
   
} // end initialize


//--------------------------------------------------------------------------
/**
* terminate
*/
//--------------------------------------------------------------------------
void OMS_VernierManifold::terminate()
{
   RTC_TRACE_ENTRY(terminate);

   // Call parent method
   OMS_VehiclePlumbing::terminate();

   // Deactivate pseudo health checking
   setPseudoHealthInactive( pOffsetCorrectedPressure_,
                            "offsetCorrectedPressure" );
   
   RTC_TRACE_EXIT;
   
} // end terminate


//----------------------------------------------------------------------------
/**
* calcPressure 
*/
//----------------------------------------------------------------------------
void RTC_IMPL(OMS_VernierManifold::calcPressure)
   (const RTC_Event::FDInfo_t FDs)
{
   // Get FD information
   RTC_FDS::FDValue_t manifoldIsoState = RTC_FD_STATE(pManifoldIsoStateRO_);
   RTC_FDS::FDValue_t manifoldLegPress = RTC_FD_STATE(pManifoldLegPressureRO_);

   bool manifldIsoOpen = (not (manifoldIsoState.fail or manifoldIsoState.stale)
                          and CL_OP2_ENUM::OPEN is_eq 
                                 Int32_t (manifoldIsoState) );

   // Check that the manifold isolation valve is open and
   // the manifold leg pressure for good data.
   if( manifldIsoOpen )
   {
      if (not( manifoldLegPress.fail or manifoldLegPress.stale ))
      {
         Set(pOffsetCorrectedPressure_, Float64_t (manifoldLegPress));
      }
   }
   else
   {
      setPseudoHealthBad(pOffsetCorrectedPressure_,
                         "offsetCorrectedPressure");
   }

} // end calcPressure
