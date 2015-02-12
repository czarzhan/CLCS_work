//=============================================================================
//
// NAME:  OMS_RcsXfdIsoValve
//
// OVERVIEW: This class extends the OMS_VValveWith2Open2CloseCmd class by
//   defining the open prerequisites for the RCS Crossfeed isolation
//   valves.
//
// RESPONSIBLE ENGINEER: Dawn Holmes
//
//=============================================================================

//=============================================================================
//                      System Include Files
//=============================================================================
#include <MANIFOLD_ENUM.h>
#include <OMS_MATED_DEMATED.h>
#include <OMS_ISOLATED_ENUM.h>


//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_RcsXfdIsoValve.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================

RTC_IMPL_CLASS(OMS_RcsXfdIsoValve);

//-------------------------------------------------------------------------
OMS_RcsXfdIsoValve::OMS_RcsXfdIsoValve(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier )  :
   OMS_VValveWith2Open2CloseCmd( rParentPath, 
                                 rIdentifier ), 
   RTC_INIT_ATTR( pRcsPropTankSysIsoStateRO_ ),
   RTC_INIT_ATTR( pManifoldLegPressRO_ ),
   RTC_INIT_ATTR( pManifoldLegStateRO_ ),
   RTC_INIT_ATTR( pXfdLinePressRO_ ),
   RTC_INIT_ATTR( pXfdLineStateRO_ ),
   RTC_INIT_ATTR( pXfdLineLeftFlangeStateRO_ ),
   RTC_INIT_ATTR( pXfdLineRightFlangeStateRO_ ),
   RTC_INIT_ATTR( pOmsTankIsoStateRO_ ),
   RTC_INIT_ATTR( pOppRcsTankIsoStateRO_ ),
   RTC_INIT_ATTR( pOppOmsTankIsoStateRO_ )
{
   RTC_TRACE_CTOR_ENTRY;
   
   RTC_TRACE_CTOR_EXIT;
   
} // end OMS_RcsXfdIsoValve::OMS_RcsXfdIsoValve


//-------------------------------------------------------------------------
OMS_RcsXfdIsoValve::~OMS_RcsXfdIsoValve()
{
   RTC_TRACE_DTOR_ENTRY;
   
   RTC_TRACE_DTOR_EXIT;
   
} // end OMS_RcsXfdIsoValve::~OMS_RcsXfdIsoValve
   

//-------------------------------------------------------------------------
bool OMS_RcsXfdIsoValve::prereqsMet() const
{
   RTC_TRACE_ENTRY(prereqsMet);

   bool returnVal = false;
   RTC_String errmsg;

   // Verify xfd flange is mated
   if ( xfdFlangeIsMated( pXfdLineLeftFlangeStateRO_,
                          pXfdLineRightFlangeStateRO_,
                          errmsg ) )
   {
      // Verify contamination states are the same
      if ( statesMatch( pManifoldLegStateRO_,
                        pXfdLineStateRO_ ) )
      {
         // Verify prop tank System OR other tanks are isolated
         if ( tkSysOrOtherTksIsolated( pRcsPropTankSysIsoStateRO_,
                                       pOmsTankIsoStateRO_,
                                       pOppRcsTankIsoStateRO_,
                                       pOppOmsTankIsoStateRO_,
                                       errmsg ) )
         {
            // Verify pressure differential is within Range
            returnVal = pressureInRange( pManifoldLegPressRO_,
                                         pXfdLinePressRO_,
                                         pManifoldLegStateRO_,
                                         errmsg );
         }// end tkSysOrOtherTksIsolated
         
      }// end contaminationStatesMatch
      else
      {
         errmsg << "Crossfeed line and Manifold Leg contamination states "
                << "do not match.";
      }
      
   } // end xfdFlangeIsMated

   if ( false is_eq returnVal )
   {
      RTC_SEND_WARN( "Open prerequisites failed - " + errmsg );
   }


   RTC_TRACE_EXIT_VALUE(returnVal);
   return returnVal;
   
} // end OMS_RcsXfdIsoValve::prereqsMet
