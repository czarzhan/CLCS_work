//=============================================================================
//
// NAME:  OMS_VValveWith1Open1CloseCmd
//
// OVERVIEW: This class defines the functionality of OMS vehicle valves with
//  an open command and a close command.  These are momentary commands, and
//  valves remain in the last commanded state.  The valves also have an open
//  and a close VPI which are used to update the valve states.  The software
//  provides the capabilty to open and close the valve, to toggle the valve
//  between the open and close positions,  and to turn on and off each of
//  the commands individually for troubleshooting.  
//
//  This class also has the capability to suspend command processing and
//  verify that the valve has been secured by the Safing EIM, as well as,
//  a mechanism for the operator to resuming normal processing upon request.
//
// RESPONSIBLE ENGINEER: Dawn Holmes
//
//=============================================================================


//=============================================================================
//                      System Include Files
//=============================================================================
#include <MANIFOLD_ENUM.h>
#include <OMS_ISOLATED_ENUM.h>
#include <OMS_MATED_DEMATED.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_VValveWith1Open1CloseCmd.h"
#include "OMS_IPCIF_ValveWith1Open1CloseCmd.h"


//=============================================================================
//                     Class Member Definitions
//=============================================================================


RTC_IMPL_CLASS(OMS_VValveWith1Open1CloseCmd);

// Static member initialization
const RTC_Time::Value_t 
OMS_VValveWith1Open1CloseCmd::CYCLE_TIME = RTC_Time::secs(1.3);

const RTC_String 
OMS_VValveWith1Open1CloseCmd::OPEN_ERR_MSG = 
   "Valve commanded open, but indicator failed to update";

const RTC_String 
OMS_VValveWith1Open1CloseCmd::CLOSE_ERR_MSG = 
   "Valve commanded close, but indicator failed to update";

const RTC_String 
OMS_VValveWith1Open1CloseCmd::SECURE_ERR_MSG = 
   "Valve state failed to update after securing";


//-------------------------------------------------------------------------
OMS_VValveWith1Open1CloseCmd::OMS_VValveWith1Open1CloseCmd(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier,
   Attributes_t attributes) :
   RTC_StateComponent_T< OMS_Object,
                         CL_OP2_ENUM::CL_OP2_ENUM_t >(rParentPath, 
                                                      rIdentifier, 
                                                      attributes ),
   RTC_INIT_ATTR( pCloseIndicator_ ),
   RTC_INIT_ATTR( pOpenIndicator_ ),
   RTC_INIT_ATTR( pCloseCommand_ ),
   RTC_INIT_ATTR( pOpenCommand_ ),
   RTC_INIT_ATTR( pCloseSwitch_ ),
   RTC_INIT_ATTR( pOpenSwitch_ )
{
   RTC_TRACE_CTOR_ENTRY;

   // set the include Prereq methods flag to true
   includePreReqMethods_ = true;
    
   RTC_TRACE_CTOR_EXIT;

} // end OMS_VValveWith1Open1CloseCmd::OMS_VValveWith1Open1CloseCmd

   
//-------------------------------------------------------------------------
OMS_VValveWith1Open1CloseCmd::~OMS_VValveWith1Open1CloseCmd()
{
   RTC_TRACE_DTOR_ENTRY;
    
   RTC_TRACE_DTOR_EXIT;

} // end OMS_VValveWith1Open1CloseCmd::~OMS_VValveWith1Open1CloseCmd
   
//-------------------------------------------------------------------------
bool OMS_VValveWith1Open1CloseCmd::initialize()
{
   RTC_TRACE_ENTRY(initialize);
   
   // Initialize state
   Int32_t stateVal = state();
   setPseudoHealthGood( stateFD(), "state", stateVal );

   // Initialize last command
   Int32_t openInd;
   readDiscrete ( pOpenIndicator_, openInd );

   if ( (Discrete::On is_eq openInd) )
   {
      lastCommand_ = OMS::OPEN;
   }
   else
   {
      lastCommand_ = OMS::CLOSE;
   }

   // Register monitor for open switch
   When_Interrupt(
      RTC_list(pOpenSwitch_),
      RTC_action(
         this, 
         &OMS_VValveWith1Open1CloseCmd::verifyCockpitSwitchOpen),
      true);

   // Register monitor for close switch
   When_Interrupt(
      RTC_list(pCloseSwitch_),
      RTC_action(
         this, 
         &OMS_VValveWith1Open1CloseCmd::verifyCockpitSwitchClose),
      true);
   
   RTC_TRACE_EXIT;
   
   // return results of call to parent class
   return RTC_StateComponent_T< OMS_Object, 
      CL_OP2_ENUM::CL_OP2_ENUM_t >::initialize();
   
} // end OMS_VValveWith1Open1CloseCmd::initialize


//-------------------------------------------------------------------------
void OMS_VValveWith1Open1CloseCmd::terminate()
{
   RTC_TRACE_ENTRY(terminate);
   
   // Call parent method
   RTC_StateComponent_T< OMS_Object, 
      CL_OP2_ENUM::CL_OP2_ENUM_t >::terminate();
   
   // Set state health
   setPseudoHealthInactive( stateFD(), "state" );
   
   RTC_TRACE_EXIT;
   
} // end OMS_VValveWith1Open1CloseCmd::terminate


//-------------------------------------------------------------------------
OMS::Status_t RTC_IMPL(OMS_VValveWith1Open1CloseCmd::open)()
{
   RTC_TRACE_ENTRY(open);

   OMS::Status_t status = OMS::FAIL;

   // Begin open sequence 
   bool passedPrereqs = beginOpenSequence();

   // Continue this operation if prerequisites are met
   if ( passedPrereqs )
   {
      // Turn off open command
      Set( pOpenCommand_, Discrete::Off, ASV_CLO );

      // Verify valve state is OPEN or send system message
      status = verifyState( CL_OP2_ENUM::OPEN, OPEN_ERR_MSG );

   }

   RTC_TRACE_EXIT;

   return status;

} // end OMS_VValveWith1Open1CloseCmd::open


//-------------------------------------------------------------------------
OMS::Status_t RTC_IMPL(OMS_VValveWith1Open1CloseCmd::close)()
{
   RTC_TRACE_ENTRY(close);
   
   // Begin close sequence
   beginCloseSequence();
   
   // Turn off close command
   Set( pCloseCommand_, Discrete::Off );
   
   RTC_TRACE_EXIT;

   // Verfiy state is CLOSED or send system message, return result
   return verifyState( CL_OP2_ENUM::CLOSED, CLOSE_ERR_MSG );

} // end OMS_VValveWith1Open1CloseCmd::close


//-------------------------------------------------------------------------
void RTC_IMPL(OMS_VValveWith1Open1CloseCmd::toggle)()
{
   RTC_TRACE_ENTRY(toggle);
   
   CL_OP2_ENUM::CL_OP2_ENUM_t stateVal = state();

   if ( (CL_OP2_ENUM::CLOSED is_eq stateVal) or
        (CL_OP2_ENUM::CLOSED_ERROR is_eq stateVal) or
        (CL_OP2_ENUM::CLOSING is_eq stateVal) )
   {
      open();
   }
   else
   {
      close();
   }
   
   RTC_TRACE_EXIT;

} // end OMS_VValveWith1Open1CloseCmd::toggle


//-------------------------------------------------------------------------
void RTC_IMPL(OMS_VValveWith1Open1CloseCmd::turnOnCloseCommand)()
{
   RTC_TRACE_ENTRY(turnOnCloseCommand);
   
   // Begin close sequence
   beginCloseSequence();
   
   // Verfiy state is CLOSED or send system message
   verifyState( CL_OP2_ENUM::CLOSED, CLOSE_ERR_MSG );
   
   RTC_TRACE_EXIT;
   
} // end OMS_VValveWith1Open1CloseCmd::turnOnCloseCommand


//-------------------------------------------------------------------------
void RTC_IMPL(OMS_VValveWith1Open1CloseCmd::turnOnOpenCommand)()
{
   RTC_TRACE_ENTRY(turnOnOpenCommand);

   bool passedPrereqs = beginOpenSequence();

   // Continue this operation if prerequisites are met
   if ( passedPrereqs )
   {
      // Verify valve state is OPEN or send system message
      verifyState( CL_OP2_ENUM::OPEN, OPEN_ERR_MSG );
   }
   
   RTC_TRACE_EXIT;

} // end OMS_VValveWith1Open1CloseCmd::turnOnOpenCommand


//-------------------------------------------------------------------------
void RTC_IMPL(OMS_VValveWith1Open1CloseCmd::turnOffCloseCommand)()
{
   RTC_TRACE_ENTRY(turnOffCloseCommand);

   // Turn off close command
   Set( pCloseCommand_, Discrete::Off );

   RTC_TRACE_EXIT;

} // end OMS_VValveWith1Open1CloseCmd::turnOffCloseCommand


//-------------------------------------------------------------------------
void RTC_IMPL(OMS_VValveWith1Open1CloseCmd::turnOffOpenCommand)()
{
   RTC_TRACE_ENTRY(turnOffOpenCommand);
   
   // Turn off open command
   Set( pOpenCommand_, Discrete::Off, ASV_CLO );

   RTC_TRACE_EXIT;

} // end OMS_VValveWith1Open1CloseCmd::turnOffOpenCommand


//-------------------------------------------------------------------------
bool OMS_VValveWith1Open1CloseCmd::beginOpenSequence()
{
   RTC_TRACE_ENTRY(beginOpenSequence);
   
   bool passedPrereqs = 
      checkPrereqs( RTC_action( 
                       this, 
                       &OMS_VValveWith1Open1CloseCmd::prereqsMet ));
   
   // Only perform this operation if prerequisites are met
   if ( passedPrereqs )
   {
      // Override valve state to OPENING
      overrideStateSynthesis( CL_OP2_ENUM::OPENING );
      
      // Turn off close command
      Set( pCloseCommand_, Discrete::Off );
      
      // Turn on open command
      Set( pOpenCommand_, Discrete::On, ASV_CLO );
      
      // Set last command to OPEN
      lastCommand_ = OMS::OPEN;
      
      // Delay cycle time, or until the valve open indicator is ON.
      verifyWithin( CYCLE_TIME, RTC_Event::cond( pOpenIndicator_, 
                                                 RTC_Event::EQUAL,
                                                 Discrete::On ));
      
   }
   
   RTC_TRACE_EXIT;
   
   return passedPrereqs;
   
} // end OMS_VValveWith1Open1CloseCmd::beginOpenSequence


//-------------------------------------------------------------------------
void OMS_VValveWith1Open1CloseCmd::beginCloseSequence()
{
   RTC_TRACE_ENTRY(beginCloseSequence);

   // Override valve states to CLOSING
   overrideStateSynthesis( CL_OP2_ENUM::CLOSING );
   
   // Turn off open command
   Set( pOpenCommand_, Discrete::Off, ASV_CLO );
   
   // Turn on close command
   Set( pCloseCommand_, Discrete::On );
   
   // Set last command to CLOSE
   lastCommand_ = OMS::CLOSE;
   
   // Delay cycle time, or until the valve close indicator is ON.
   verifyWithin( CYCLE_TIME, RTC_Event::cond( pCloseIndicator_, 
                                              RTC_Event::EQUAL,
                                              Discrete::On ));
   
   RTC_TRACE_EXIT;

} // end OMS_VValveWith1Open1CloseCmd::beginCloseSequence


//-------------------------------------------------------------------------
OMS::Status_t OMS_VValveWith1Open1CloseCmd::verifyState(
   const CL_OP2_ENUM::CL_OP2_ENUM_t expectedState,
   const RTC_String& errmsg )
{
   RTC_TRACE_ENTRY(verifyState);

   OMS::Status_t status = OMS::FAIL;
   
   // Activate state calculation
   activateStateSynthesis();
   
   // Delay data rate, or until the state is OPEN.
   if (  RTC_FDS::SUCCESSFUL is_eq verifyWithin( 
            OMS::DATA_RATE, RTC_Event::cond( stateFD(), 
                                             RTC_Event::EQUAL,
                                             expectedState )))
   {
      status = OMS::PASS;
   }
   else
   {
      RTC_SEND_WARN(errmsg);
   }

   RTC_TRACE_EXIT;
   
   return status;
   
} // end OMS_VValveWith1Open1CloseCmd::verifyState


//-------------------------------------------------------------------------
void RTC_IMPL(OMS_VValveWith1Open1CloseCmd::verifySecure)()
{
   RTC_TRACE_ENTRY(verifySecure);

   // Turn off close command
   Set( pCloseCommand_, Discrete::Off );
   
   // Set last command to CLOSE
   lastCommand_ = OMS::CLOSE;
   
   // Delay data rate, or until the state is CLOSED.
   if ( RTC_FDS::SUCCESSFUL not_eq verifyWithin( 
           OMS::DATA_RATE, 
           RTC_Event::cond( stateFD(), 
                            RTC_Event::EQUAL,
                            CL_OP2_ENUM::CLOSED )))
   {
      RTC_SEND_WARN( SECURE_ERR_MSG );
   }

   RTC_TRACE_EXIT;

} // end OMS_VValveWith1Open1CloseCmd::verifySecure


//-------------------------------------------------------------------------
void RTC_IMPL(OMS_VValveWith1Open1CloseCmd::suspendProcessing)()
{
   RTC_TRACE_ENTRY(suspendProcessing);

   // Suspend command processing
   objectSecured_.block();

   RTC_TRACE_EXIT;

} // end OMS_VValveWith1Open1CloseCmd::suspendProcessing
   

//-----------------------------------------------------------------------------
void RTC_IMPL(OMS_VValveWith1Open1CloseCmd::resetSecure) ()
{
   // Resume command processing
   objectSecured_.unblock();

} // end OMS_VValveWith1Open1CloseCmd::resetSecure



//-------------------------------------------------------------------------
CL_OP2_ENUM::CL_OP2_ENUM_t OMS_VValveWith1Open1CloseCmd::calculateState(
   const RTC_Event::FDInfo_t& FDs) const
{
   CL_OP2_ENUM::CL_OP2_ENUM_t result;

   Discrete::ON_OFF openIndState = RTC_FD_STATE( pOpenIndicator_ );
   Discrete::ON_OFF closeIndState = RTC_FD_STATE( pCloseIndicator_ );

   if ( OMS::CLOSE is_eq lastCommand_ )
   {
      if (( Discrete::Off is_eq openIndState ) and
          ( Discrete::On is_eq closeIndState ))
      {
         result = CL_OP2_ENUM::CLOSED;
      }
      else
      {
         result = CL_OP2_ENUM::CLOSED_ERROR;
      }
   }
   else if ( OMS::OPEN is_eq lastCommand_ )
   {
      if (( Discrete::On is_eq openIndState ) and
          ( Discrete::Off is_eq closeIndState ))
      {
         result = CL_OP2_ENUM::OPEN;
      }
      else
      {
         result = CL_OP2_ENUM::OPEN_ERROR;
      }
   }
   else
   {
      result = state();
      RTC_TRACE_METHOD(
         calculateState,
         "Unable to calculate state: invalid value for last command",
         RTC_Log::TRACE_ERROR );
   }

   return result;

} // end OMS_VValveWith1Open1CloseCmd::calculateState

//-------------------------------------------------------------------------
RTC_FDS::FDList_t OMS_VValveWith1Open1CloseCmd::stateCalculationFDs() const
{
   RTC_TRACE_ENTRY(stateCalculationFDs);
   
   RTC_TRACE_EXIT;

   return RTC_list( pOpenIndicator_, pCloseIndicator_ );
   
} // end OMS_VValveWith1Open1CloseCmd::stateCalculationFDs


//-------------------------------------------------------------------------
void RTC_IMPL(OMS_VValveWith1Open1CloseCmd::verifyCockpitSwitchClose)
   (const RTC_Event::FDInfo_t FDs)
{
  Discrete::ON_OFF closeSwitch = RTC_FD_STATE( pCloseSwitch_ );
  
  if ( Discrete::On is_eq closeSwitch )
  {
     // Suspend state calculation
     deactivateStateSynthesis();
     
     // Set lastCommand to CLOSE
     lastCommand_ = OMS::CLOSE;
     
     // Resume state calculation
     activateStateSynthesis();
  }
  
} // end OMS_VValveWith1Open1CloseCmd::verifyCockpitSwitchClose

//-------------------------------------------------------------------------
void RTC_IMPL(OMS_VValveWith1Open1CloseCmd::verifyCockpitSwitchOpen)
   (const RTC_Event::FDInfo_t FDs)
{
  Discrete::ON_OFF openSwitch = RTC_FD_STATE( pOpenSwitch_ );
  
  if ( Discrete::On is_eq openSwitch )
  {
     // Suspend state calculation
     deactivateStateSynthesis();
     
     // Set lastCommand to OPEN
     lastCommand_ = OMS::OPEN;
     
     // Resume state calculation
     activateStateSynthesis();
  }
  
} // end OMS_VValveWith1Open1CloseCmd::verifyCockpitSwitchOpen
   
   
//-------------------------------------------------------------------------
void OMS_VValveWith1Open1CloseCmd::listMethods( 
   RTC_IPCInterface::DisplayObj::List_t& rMethods)
{
   RTC_TRACE_ENTRY(listMethods);
   
   rMethods.addField("open");
   rMethods.addField("close");
   rMethods.addField("toggle");
   rMethods.addField("turnOnOpenCommand");
   rMethods.addField("turnOffOpenCommand");
   rMethods.addField("turnOnCloseCommand");
   rMethods.addField("turnOffCloseCommand");
   rMethods.addField("resetSecure");
   
   // Call OMS base class
   RTC_StateComponent_T< OMS_Object, 
      CL_OP2_ENUM::CL_OP2_ENUM_t >::listMethods(rMethods);

   RTC_TRACE_EXIT;

} // end OMS_VValveWith1Open1CloseCmd::listMethods



//-------------------------------------------------------------------------
void OMS_VValveWith1Open1CloseCmd::listAttributes( 
   RTC_IPCInterface::DisplayObj::List_t& rAttributes)
{
   RTC_TRACE_ENTRY(listAttributes);

   RTC_String attribStr;

   attribStr << "cycleTime (sec) : "
             << Float64_t( CYCLE_TIME );
   rAttributes.addField( attribStr.c_str() );

   attribStr.clear();
   attribStr << "lastCommand : "
             << lastCommand_ ;
   rAttributes.addField( attribStr.c_str() );

   RTC_TRACE_EXIT;

} // end OMS_VValveWith1Open1CloseCmd::listAttributes


//-------------------------------------------------------------------------
RTC_IPCMan::ObjInterface_t 
OMS_VValveWith1Open1CloseCmd::createIPCInterface()
{
   RTC_TRACE_ENTRY(createIPCInterface);

   OMS_IPCIF_ValveWith1Open1CloseCmd* pIpcIf;
   RTC_NEW( pIpcIf, OMS_IPCIF_ValveWith1Open1CloseCmd( *this ) );

   RTC_TRACE_EXIT;
   
   return pIpcIf;

} // end OMS_VValveWith1Open1CloseCmd::createIPCInterface



//-------------------------------------------------------------------------
bool OMS_VValveWith1Open1CloseCmd::pressureInRange( 
   RTC_FD* pPressureToCompare,
   RTC_FD* pOtherPress,
   RTC_FD* pContaminationState,
   RTC_String& rErrmsg ) const
{
   RTC_TRACE_ENTRY(pressureInRange);

   Float64_t pressToCompareVal;
   Float64_t otherPressVal;
   Int32_t contaminationStateVal;
   bool returnVal = false;
   
   if ( (OMS::PASS is_eq readAnalog(pPressureToCompare, 
                                    pressToCompareVal)) and
        (OMS::PASS is_eq readAnalog(pOtherPress, 
                                    otherPressVal)) and
        (OMS::PASS is_eq readEnum(pContaminationState, 
                                  contaminationStateVal)) )
   {      
      // Tolerance is compared with the delta pressure; the tolerance is
      // determined by the manifold Pressure as indicated in the design.
      Float64_t tolerance;
      if ( MANIFOLD_ENUM::FULL is_eq contaminationStateVal )
      {
         if ( pressToCompareVal < Float64_t(60.0) ) 
         {
            tolerance = 25.0;
         }
         else if (( pressToCompareVal >= Float64_t(60.0) )  and 
                  ( pressToCompareVal<= Float64_t(110.0) ))
         {
            tolerance = 50.0;
         }
         else
         {
            tolerance = 100.0;
         }
      }// end contamination state is FULL
      else 
      {
         tolerance = 10.0;
      }

      Float64_t delta = fabs( pressToCompareVal - otherPressVal );

      if ( delta <= tolerance )
      {
         returnVal = true;
      }
      else
      {
         rErrmsg << "Due to pressure differential.  "
                << "The delta between upstream and downstream is "
                << delta
                << ", but should be no more than "
                << tolerance << ".  ";
         
         if ( tolerance > Float64_t(10.0) )
         {
            rErrmsg << "Opening could bounce a thruster valve.";
         }
         else
         {
            rErrmsg << "Opening could damage the tank "
                   << "internal structure.";
         }
      }
      
   }// end pressures are valid
   else
   {
      rErrmsg << "Cannot determine differential pressure due to "
              << "invalid or unreadable data.";
   }
   
   RTC_TRACE_EXIT_VALUE(returnVal);
   return returnVal;
   
} // end OMS_VValveWith1Open1CloseCmd::pressureInRange



//-------------------------------------------------------------------------
bool OMS_VValveWith1Open1CloseCmd::pressureInRange( 
   RTC_FD* pPressureToCompare,
   RTC_FD* pOtherPress,
   RTC_String& rErrmsg) const
{
   RTC_TRACE_ENTRY(pressureInRange);

   Float64_t pressToCompareVal;
   Float64_t otherPressVal;
   bool returnVal = false;
   
   if ( (OMS::PASS is_eq readAnalog(pPressureToCompare, 
                                    pressToCompareVal)) and
        (OMS::PASS is_eq readAnalog(pOtherPress, 
                                    otherPressVal)) )
   {
      if ( fabs( pressToCompareVal - otherPressVal ) <= Float64_t(25.0) )
      {
         returnVal = true;
      }
      else
      {
         rErrmsg << "Delta P across valve should be less than or "
                 << " equal to 25 psi.";
      }

   }// end pressures are valid
   else
   {
      rErrmsg << "Cannot determine Delta P due to "
              << "invalid or unreadable data.";
      
   }
   
   RTC_TRACE_EXIT_VALUE(returnVal);
   return returnVal;
   
} // end OMS_VValveWith1Open1CloseCmd::pressureInRange


//-------------------------------------------------------------------------
bool OMS_VValveWith1Open1CloseCmd::isTankIsolated( RTC_FD* pTkIsoState) const
{
   RTC_TRACE_ENTRY(isTankIsolated);

   bool returnVal = false;
   
   Int32_t tkIsoStateVal;
   
   if ( OMS::PASS is_eq readEnum( pTkIsoState, 
                                  tkIsoStateVal) )
   {
      returnVal = OMS_ISOLATED_ENUM::ISOLATED is_eq tkIsoStateVal;
   }
      
   
   RTC_TRACE_EXIT_VALUE(returnVal);
   return returnVal;
   
} // end OMS_VValveWith1Open1CloseCmd::isTankIsolated


//-------------------------------------------------------------------------
bool OMS_VValveWith1Open1CloseCmd::tanksAreIsolated( 
   RTC_FD* pTkIsoState1,
   RTC_FD* pTkIsoState2,
   RTC_FD* pTkIsoState3,
   RTC_String& rErrmsg ) const
{
   RTC_TRACE_ENTRY(tanksAreIsolated);

   bool returnVal = false;
   
   
   if ( isTankIsolated( pTkIsoState1 ) and 
        isTankIsolated( pTkIsoState2 ) and 
        isTankIsolated( pTkIsoState3 ))
   {
      returnVal = true;
   }
   else
   {
      rErrmsg << "Another Tank may be online with the Crossfeed";
   }
      
   
   RTC_TRACE_EXIT_VALUE(returnVal);
   return returnVal;
   
} // end OMS_VValveWith1Open1CloseCmd::tanksAreIsolated


//-------------------------------------------------------------------------
bool OMS_VValveWith1Open1CloseCmd::tkSysOrOtherTksIsolated( 
   RTC_FD* pTkSysIsoState,
   RTC_FD* pTkIsoState1,
   RTC_FD* pTkIsoState2,
   RTC_FD* pTkIsoState3,
   RTC_String& rErrmsg ) const
{
   RTC_TRACE_ENTRY(tkSysOrOtherTksIsolated);

   bool returnVal = false;
   
   
   if ( isTankIsolated( pTkSysIsoState ) or
        ( isTankIsolated( pTkIsoState1 ) and 
          isTankIsolated( pTkIsoState2 ) and 
          isTankIsolated( pTkIsoState3 )) )
   {
      returnVal = true;
   }
   else
   {
      rErrmsg << "Another Tank may be online with the Crossfeed";
   }
      
   
   RTC_TRACE_EXIT_VALUE(returnVal);
   return returnVal;
   
} // end OMS_VValveWith1Open1CloseCmd::tkSysOrOtherTksIsolated


//-------------------------------------------------------------------------
bool OMS_VValveWith1Open1CloseCmd::isValveOpen( RTC_FD* pValveState) const
{
   RTC_TRACE_ENTRY(isValveOpen);

   bool returnVal = false;
   
   Int32_t valveStateVal;
   
   if ( OMS::PASS is_eq readEnum( pValveState, 
                                  valveStateVal) )
   {
      returnVal = CL_OP2_ENUM::OPEN is_eq valveStateVal;
   }
      
   
   RTC_TRACE_EXIT_VALUE(returnVal);
   return returnVal;
   
} // end OMS_VValveWith1Open1CloseCmd::isValveOpen



//-------------------------------------------------------------------------
bool OMS_VValveWith1Open1CloseCmd::isFull( RTC_FD* pPlumbing ) const
{
   RTC_TRACE_ENTRY(isFull);

   bool returnVal = false;
   
   Int32_t val;
   
   if ( OMS::PASS is_eq readEnum( pPlumbing, 
                                  val) )
   {
      returnVal = MANIFOLD_ENUM::FULL is_eq val;
   }
      
   
   RTC_TRACE_EXIT_VALUE(returnVal);
   return returnVal;
   
} // end OMS_VValveWith1Open1CloseCmd::isFull


//-------------------------------------------------------------------------
bool OMS_VValveWith1Open1CloseCmd::xfdFlangeIsMated(
   RTC_FD* pLeftFlangeState,
   RTC_FD* pRightFlangeState,
   RTC_String& rErrmsg ) const
{
   RTC_TRACE_ENTRY(xfdFlangeIsMated);

   bool returnVal = false;

   Int32_t leftFlangeStateVal;
   Int32_t rightFlangeStateVal;
   if ( (OMS::PASS is_eq readEnum(pLeftFlangeState, 
                                  leftFlangeStateVal)) and
        (OMS::PASS is_eq readEnum(pRightFlangeState, 
                                  rightFlangeStateVal)) )
   {
      if ( (OMS_MATED_DEMATED::MATED is_eq leftFlangeStateVal) and
           (OMS_MATED_DEMATED::MATED is_eq rightFlangeStateVal) )
      {
         returnVal = true;
      }
      else
      {
         rErrmsg << "Crossfeed flange must be mated.";
      }
   }
   
   RTC_TRACE_EXIT_VALUE(returnVal);
   return returnVal;
   
} // end OMS_VValveWith1Open1CloseCmd::xfdFlangeIsMated


//-------------------------------------------------------------------------
bool OMS_VValveWith1Open1CloseCmd::statesMatch( RTC_FD* pState1,
                                                RTC_FD* pState2 ) const
{
   RTC_TRACE_ENTRY(statesMatch);

   bool returnVal = false;
   Int32_t state1Val;
   Int32_t state2Val;
   
   if ( (OMS::PASS is_eq readEnum(pState1, state1Val)) and
        (OMS::PASS is_eq readEnum(pState2, state2Val)) )
   {
      returnVal = state1Val is_eq state2Val;
   }
   
   RTC_TRACE_EXIT_VALUE(returnVal);
   return returnVal;
   
} // end OMS_VValveWith1Open1CloseCmd::statesMatch
