//=============================================================================
//
// NAME: OMS_OmeInletLine
//
// OVERVIEW: The OME Inlet Line are the plumbing between the feedlines and the
//           OMS engine ball valves. Each inlet line is instrumented with an
//           analog pressure sensor (inherited from the OMS_PrimaryManifold
//           class). In addition, the fuel inlet lines have a temperature 
//           sensor.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
 
//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_OmeInletLine.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================

RTC_IMPL_CLASS(OMS_OmeInletLine);

//-------------------------------------------------------------------------
/**
*
* OMS_OmeInletLine constructor
*
*/
//-------------------------------------------------------------------------
OMS_OmeInletLine::OMS_OmeInletLine(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier,
   OMS::Commodity_t commodityType,
   bool initToValid) :
   OMS_PrimaryManifold(
      rParentPath,
      rIdentifier,
      initToValid)
{
   RTC_TRACE_CTOR_ENTRY;

   if(OMS::FUEL is_eq commodityType)
   {
      RTC_SUBCOMP_CREATE(
         pInletTemp_,
         OMS_AnalogWithLccLimits(
            objPath(),
            "TEMP",
            initToValid) );
   }
   else
   {
      pInletTemp_ = NULL;
   }

   RTC_TRACE_CTOR_EXIT;

} // end constructor



//-------------------------------------------------------------------------
/**
*
* OMS_OmeInletLine destructor
*
*/
//-------------------------------------------------------------------------
OMS_OmeInletLine::~OMS_OmeInletLine()
{
   RTC_TRACE_DTOR_ENTRY;

   if( not(NULL is_eq pInletTemp_))
   {
      RTC_SUBCOMP_DELETE( pInletTemp_ );
   }

   RTC_TRACE_DTOR_EXIT;

} // end destructor


//-------------------------------------------------------------------------
/**
* setInvalid
*/
//-------------------------------------------------------------------------
void RTC_IMPL( OMS_OmeInletLine::setInvalid )()
{
   RTC_TRACE_ENTRY(setInvalid);
   
   try
   {
      // Call the setInvalid methods in the aggregates.
      pPressure_->setInvalid();
      
      if( not(NULL is_eq pInletTemp_))
      {
         pInletTemp_->setInvalid();
      }
   }
   catch ( ... )
   {
      RTC_SEND_WARN("setInvalid failed: Unknown Exception raised.");
   }
   
   RTC_TRACE_EXIT;

}

//-------------------------------------------------------------------------
/**
* setValid
*/
//-------------------------------------------------------------------------
void RTC_IMPL( OMS_OmeInletLine::setValid )()
{
   RTC_TRACE_ENTRY(setValid);
  
   try
   {
      // Call the setValid methods in the aggregates.
      pPressure_->setValid();
      
      if( not(NULL is_eq pInletTemp_))
      {
         pInletTemp_->setValid();
      }
   }
   catch ( ... )
   {
      RTC_SEND_WARN("setValid failed: Unknown Exception raised.");
   }

   RTC_TRACE_EXIT;

}

