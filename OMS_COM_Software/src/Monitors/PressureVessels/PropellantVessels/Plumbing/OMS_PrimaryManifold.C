//=============================================================================
//
// NAME: OMS_PrimaryManifold
//
// OVERVIEW: The Primary Manifolds consist of plumbing between the manifold
//           isolation valves and the primary RCS thrusters. They are 
//           instrumented with a single analog pressure sensor.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_PrimaryManifold.h"
 
//=============================================================================
//                     Class Member Definitions
//=============================================================================

RTC_IMPL_CLASS(OMS_PrimaryManifold);

//-------------------------------------------------------------------------
/**
* OMS_PrimaryManifold constructor
*/
//-------------------------------------------------------------------------
OMS_PrimaryManifold::OMS_PrimaryManifold(
   const RTC_String& rParentPath,
   const RTC_String& rIdentifier,
   bool initToValid) :
   OMS_VehiclePlumbing(rParentPath,
                       rIdentifier)
{
   RTC_TRACE_CTOR_ENTRY;

   RTC_SUBCOMP_CREATE(
      pPressure_,
      OMS_AnalogWith3OffsetsDefAndLccLimits( 
         objPath(),
         "PRESS",
         initToValid) );

   RTC_TRACE_CTOR_EXIT;

} // end constructor


//-------------------------------------------------------------------------
/**
* OMS_PrimaryManifold destructor
*/
//-------------------------------------------------------------------------
OMS_PrimaryManifold::~OMS_PrimaryManifold()
{
   RTC_TRACE_DTOR_ENTRY;

   RTC_SUBCOMP_DELETE(pPressure_);

   RTC_TRACE_DTOR_EXIT;

} //end destructor



