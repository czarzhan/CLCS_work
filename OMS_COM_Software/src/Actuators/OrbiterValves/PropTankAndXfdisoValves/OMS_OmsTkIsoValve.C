//=============================================================================
//
// NAME:  OMS_OmsTkIsoValve
//
// OVERVIEW: This class extends the OMS_VValveWith2Open2CloseCmd class by
//   defining the open prerequisites for the OMS Propellant Tank isolation
//   valves.
//
// RESPONSIBLE ENGINEER: Dawn Holmes
//
//=============================================================================

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_OmsTkIsoValve.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================

RTC_IMPL_CLASS(OMS_OmsTkIsoValve);

//-------------------------------------------------------------------------
OMS_OmsTkIsoValve::OMS_OmsTkIsoValve(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier )  :
   OMS_VValveWith2Open2CloseCmd( rParentPath, 
                                 rIdentifier ) ,
   RTC_INIT_ATTR( pOmsPropTankPressRO_ ),
   RTC_INIT_ATTR( pOmsPropTankSysIsoStateRO_ ),
   RTC_INIT_ATTR( pParallelIsoVlvStateRO_ ),
   RTC_INIT_ATTR( pXfdIsoValveAStateRO_ ),
   RTC_INIT_ATTR( pXfdIsoValveBStateRO_ ),
   RTC_INIT_ATTR( pFeedlinePressRO_ ),
   RTC_INIT_ATTR( pFeedlineStateRO_ ),
   RTC_INIT_ATTR( pRcsTankIsoStateRO_ ),
   RTC_INIT_ATTR( pOppRcsTankIsoStateRO_ ),
   RTC_INIT_ATTR( pOppOmsTankIsoStateRO_ )
{
   RTC_TRACE_CTOR_ENTRY;
   
   RTC_TRACE_CTOR_EXIT;
   
} // end OMS_OmsTkIsoValve::OMS_OmsTkIsoValve


//-------------------------------------------------------------------------
OMS_OmsTkIsoValve::~OMS_OmsTkIsoValve()
{
   RTC_TRACE_DTOR_ENTRY;
   
   RTC_TRACE_DTOR_EXIT;
   
} // end OMS_OmsTkIsoValve::~OMS_OmsTkIsoValve
   

//-------------------------------------------------------------------------
bool OMS_OmsTkIsoValve::prereqsMet() const
{
   RTC_TRACE_ENTRY(prereqsMet);

   bool returnVal = false;
   RTC_String errmsg;

   // Verify parallel tank iso valve is open
   if ( isValveOpen( pParallelIsoVlvStateRO_ ))
   {
      returnVal = true;
   }
   else
   {
      // Verify feedline is FULL
      if ( isFull( pFeedlineStateRO_ ) )
      {
         // Verify pressure differential is <= 25
         if ( pressureInRange( pFeedlinePressRO_,
                               pOmsPropTankPressRO_,
                               errmsg ))
         {
            // Verify prop tank System OR other tanks are isolated
            returnVal = 
               tkSysOrOtherTksIsolated( pOmsPropTankSysIsoStateRO_,
                                        pRcsTankIsoStateRO_,
                                        pOppRcsTankIsoStateRO_,
                                        pOppOmsTankIsoStateRO_,
                                        errmsg );
         }// end pressure in range
         
      }// end feedline is FULL
      else
      {
         errmsg << "Feedline contamination state must be FULL.";
      }
      
   }// end parallel iso valve is not open
   
   if ( false is_eq returnVal )
   {
      RTC_SEND_WARN( "Open prerequisites failed - " + errmsg );
   }
   
   
   RTC_TRACE_EXIT_VALUE(returnVal);
   return returnVal;
   
} // end OMS_OmsTkIsoValve::prereqsMet
