//=============================================================================
//
// NAME: OMS_ArcsManifoldLeg
// 
// OVERVIEW: The manifold legs provide a propellant path from the tank 
//           isolation valves to the manifold isolation valves.  There are two
//           types of manifold legs designated 1/2 Manifold Leg and 3/4/5 
//           Manifold Leg for each of the fuel and oxidizer systems.  The only
//           addition based on the manifoldLegType is the addition of a second
//           tkIsoValveState.
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
#include "OMS_ArcsManifoldLeg.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================

RTC_IMPL_CLASS(OMS_ArcsManifoldLeg);

//-------------------------------------------------------------------------
/**
*
* OMS_ManifoldLeg constructor for the 3/4/5 manifold legs
*
*/
//-------------------------------------------------------------------------
OMS_ArcsManifoldLeg::OMS_ArcsManifoldLeg(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier,
   OMS::ManifoldLeg_t manifoldLegType) :
   OMS_ManifoldLeg(
      rParentPath,
      rIdentifier),
   manifoldLegType_(manifoldLegType),
   RTC_INIT_ATTR(pTkIsoValveBStateRO_),
   RTC_INIT_ATTR(pXfdIsoValveStateRO_),
   RTC_INIT_ATTR(pXfdLinePressureRO_)
{
   RTC_TRACE_CTOR_ENTRY;

   RTC_TRACE_CTOR_EXIT;

} // end constructor


//-------------------------------------------------------------------------
/**
*
* OMS_ManifoldLeg constructor for the 1/2 manifold legs
*
*/
//-------------------------------------------------------------------------
OMS_ArcsManifoldLeg::OMS_ArcsManifoldLeg(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier) :
   OMS_ManifoldLeg(
      rParentPath,
      rIdentifier),
   RTC_INIT_ATTR(pXfdIsoValveStateRO_),
   RTC_INIT_ATTR(pXfdLinePressureRO_)
{
   RTC_TRACE_CTOR_ENTRY;

   // This constructor should only be used for the 1/2 ARCS manifold legs.
   // As such, the manifoldLegType is set within the constructor.
   manifoldLegType_ = OMS::LEG_12;

   // The 1/2 manifold legs so not have a second tank isolation valve.
   pTkIsoValveBStateRO_ = NULL;

   RTC_TRACE_CTOR_EXIT;

} // end constructor


//-------------------------------------------------------------------------
/**
* OMS_ArcsManifoldLeg destructor
*/
//-------------------------------------------------------------------------
OMS_ArcsManifoldLeg::~OMS_ArcsManifoldLeg()
{
   RTC_TRACE_DTOR_ENTRY;
   
   RTC_TRACE_DTOR_EXIT;
   
} // end destructor


//-------------------------------------------------------------------------
/**
* calcPressure 
*/   
//-------------------------------------------------------------------------
void RTC_IMPL(OMS_ArcsManifoldLeg::calcPressure)
   (const RTC_Event::FDInfo_t FDs)
{
   // Initialize local variable for internal calculations, and a boolean
   // to determine if we set the pseudo.
   Float64_t pressureValue;
   bool publish = false;

   // Get FD information
   RTC_FDS::FDValue_t tankIsoAState  = RTC_FD_STATE(pTkIsoValveAStateRO_);
   RTC_FDS::FDValue_t tankIsoBState;
   if( NULL != pTkIsoValveBStateRO_ )
   {
      tankIsoBState = RTC_FD_STATE(pTkIsoValveBStateRO_);
   }

   // Create booleans to clarify if statement
   bool tankVlvAOpen = (not( tankIsoAState.fail or tankIsoAState.stale )and
                        CL_OP2_ENUM::OPEN is_eq Int32_t(tankIsoAState));

   bool tankVlvBOpen = ((NULL != pTkIsoValveBStateRO_ and
                         (not(tankIsoBState.fail or tankIsoBState.stale)) and
                         CL_OP2_ENUM::OPEN is_eq Int32_t(tankIsoBState)));

   // Check that the Tank isolation valves are open and for valid data
   // from the tank and the valve.
   if ( tankVlvAOpen or tankVlvBOpen )
   {
      RTC_FDS::FDValue_t propTankPress  = RTC_FD_STATE(pPropTankPressureRO_);

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

      // Create booleans to clarify if statement
      bool manifoldAOpen = (not(manifoldIsoASt.fail or
                                manifoldIsoASt.stale ) and
                            CL_OP2_ENUM::OPEN is_eq Int32_t(manifoldIsoASt));

      // Check for valid data from the "A" manifold and its isolation valve
      // and that the valve is open.
      if ( manifoldAOpen )
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

         // Create booleans to clarify if statement
         bool manifoldBOpen = (not(manifoldIsoBSt.fail or
                                   manifoldIsoBSt.stale ) and
                               CL_OP2_ENUM::OPEN is_eq 
                                  Int32_t(manifoldIsoBSt));

         // Check for valid data from the "B" manifold and its isolation
         // valve and that the valve is open.
         if ( manifoldBOpen )
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
            // Get FD information
            RTC_FDS::FDValue_t xfdIsoVlvState = 
               RTC_FD_STATE(pXfdIsoValveStateRO_);

            // Create boolean to clarify if statement
            bool xfdIsoVlvOpen = (not(xfdIsoVlvState.fail or
                                      xfdIsoVlvState.stale) and
                                  CL_OP2_ENUM::OPEN is_eq
                                     Int32_t(xfdIsoVlvState));

            // Check for valid data from the crossfeed line and that its 
            // isolation valve is open.
            if( xfdIsoVlvOpen )
            {
               // Get FD information
               RTC_FDS::FDValue_t xfdLinePress  = 
                  RTC_FD_STATE(pXfdLinePressureRO_);
               
               // Create boolean to clarify if statement
               bool xfdPressGood = (not(xfdLinePress.fail or
                                        xfdLinePress.stale));
               
               if ( xfdPressGood )
               {
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
RTC_FDS::FDList_t OMS_ArcsManifoldLeg::pressureCalcFDs() const
{
   // Retrieve base class list of FDs 
   RTC_FDS::FDList_t baseList = OMS_ManifoldLeg::pressureCalcFDs();

   // create list for this class
   RTC_FDS::FDList_t thisList;

   // This is a list based on type of manifold leg.
   if(OMS::LEG_345 is_eq manifoldLegType_)
   {
     thisList = RTC_list( pTkIsoValveBStateRO_,
                          pXfdIsoValveStateRO_,
                          pXfdLinePressureRO_  );
   }
   else
   {
      thisList = RTC_list( pXfdIsoValveStateRO_,
                           pXfdLinePressureRO_  );
   }

   thisList.merge(baseList);

   return thisList;

} // end pressureCalcFDs
