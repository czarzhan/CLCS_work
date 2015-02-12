//=============================================================================
//
// NAME:  OMS_VValveWith1Open1CloseCmd
//
// OVERVIEW: This class defines the functionality of OMS vehicle valves with
//  an open command and a close command.  These are momentary commands, and
//  valves remain in the last commanded state.  The valves also have an open
//  and a close VPI, and an open and close cockpit switch.  The VPIs are used 
//  to update the valve states, and the switches are used to update the last
//  command.  The software provides the capabilty to open and close the valve,
//  to toggle the valve between the open and close positions,  and to turn on 
//  and off each of the commands individually for troubleshooting.  
//
//  This class also has the capability to suspend command processing and
//  verify that the valve has been secured by the Safing EIM, as well as,
//  a mechanism for the operator to resuming normal processing upon request.
//
// RESPONSIBLE ENGINEER: Dawn Holmes
//
//=============================================================================


#ifndef OMS_VVALVEWITH1OPEN1CLOSECMD_H
#define OMS_VVALVEWITH1OPEN1CLOSECMD_H

//=============================================================================
//                      System Include Files
//=============================================================================
#include <RTC_FD.h>
#include <RTC_StateComponent_T.h>
#include <RTC_Event.h>
#include <CL_OP2_ENUM.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_Object.h"


//=============================================================================
//                      Class Declarations
//=============================================================================


//-----------------------------------------------------------------------------
/**
* OMS_VValveWith1Open1CloseCmd represents OMS Vehicle valves
* with two momentary commands: one open command and one close command.  In
* addition, these valves also have one open VPI and one close VPI.
*
* The functionality provided includes:
*
* - The capabilty to open, close and toggle the valve.
* - The capabilty to turn on and off each of the commands individually for 
*      troubleshooting. 
* - The capabilty to suspend command processing and verify that the valve 
*       has been secured by the Safing EIM.
* - The capabilty to resuming normal processing after valve operations have
*      been suspended.
*/
//-----------------------------------------------------------------------------
class OMS_VValveWith1Open1CloseCmd : public RTC_StateComponent_T< OMS_Object, 
          CL_OP2_ENUM::CL_OP2_ENUM_t > 
{
   
   RTC_DECL_CLASS(OMS_VValveWith1Open1CloseCmd);
   
   //-------------------------------------------------------------------------
   /**
   * This method is used to open the valve if the prerequisites are met.  
   * The valve is cycled by turning off the close command, turning on the 
   * open command, setting the last comand to OPEN, and delaying cycleTime 
   * or until the valve indicators have updated.  The open command is turned 
   * off after the delay.  The valve state is set to OPENING while the valve 
   * is transitioning from closed to open, and normal state updates resume 
   * after the delay.  The return value is determined by the valve state.
   *
   * Note:  This command is rejected when the valve is secured
   *
   * @return PASS if the valve state is OPEN, otherwise FAIL
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(  RETURNS(OMS::Status_t),
               NAME(open),
               NO_PARMS,
               REJECT_WHEN( objectSecured_ ) );


   //-------------------------------------------------------------------------
   /**
   * This method is used to close the valve.  The valve is cycled by 
   * turning off the open command, turning on the close command, setting
   * the last command to CLOSE, and delaying cycleTime or until the valve 
   * indicators have updated.  The close command is turned off after the 
   * delay.  The valve state is set to CLOSING while the valve is 
   * transitioning from open to closed, and normal state updates resume 
   * after the delay.  The return value is determined by the valve state.
   *
   * Note:  This command is rejected when the valve is secured
   *
   * @return PASS if the valve state is CLOSED, otherwise FAIL
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(  RETURNS(OMS::Status_t),
               NAME(close),
               NO_PARMS,
               REJECT_WHEN( objectSecured_ ) );
   

   //-------------------------------------------------------------------------
   /**
   * This method is used to toggle the valve.  If the valve state is CLOSED
   * CLOSED_ERROR, or CLOSING, the open operation is invoked, otherwise
   * the close operation is called.
   *
   * Note:  This command is rejected when the valve is secured
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(  RETURNS_VOID,
               NAME(toggle),
               NO_PARMS,
               REJECT_WHEN( objectSecured_ ) );
   
   //-------------------------------------------------------------------------
   /**
   * If the open prerequisites are met:
   * This method performs all of the steps as specified in the open method,
   * but leaves the open command on.
   *
   * Note:  This command is rejected when the valve is secured
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(  RETURNS_VOID,
               NAME(turnOnOpenCommand),
               NO_PARMS,
               REJECT_WHEN( objectSecured_ ) );
   
   //-------------------------------------------------------------------------
   /**
   * This method sets the openCommand to Off.
   *
   * Note:  This command is rejected when the valve is secured
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(  RETURNS_VOID,
               NAME(turnOffOpenCommand),
               NO_PARMS,
               REJECT_WHEN( objectSecured_ ) );
   
   //-------------------------------------------------------------------------
   /**
   * This method performs all of the steps as specified in the close method,
   * but leaves the close command on.
   *
   * Note:  This command is rejected when the valve is secured
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(  RETURNS_VOID,
               NAME(turnOnCloseCommand),
               NO_PARMS,
               REJECT_WHEN( objectSecured_ ) );
   
   //-------------------------------------------------------------------------
   /**
   * This method sets the closeCommand to Off.
   *
   * Note:  This command is rejected when the valve is secured
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(  RETURNS_VOID,
               NAME(turnOffCloseCommand),
               NO_PARMS,
               REJECT_WHEN( objectSecured_ ) );

   //-------------------------------------------------------------------------
   /** 
   * This method turns off the closeCommand, sets the last command to CLOSE,
   *  and notifies the operator if valve state is not CLOSED.
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(  RETURNS_VOID,
               NAME(verifySecure),
               NO_PARMS,
               NEVER_REJECT);

   //-------------------------------------------------------------------------
   /**
   * This invokes the rejector block operation.
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(  RETURNS_VOID,
               NAME(suspendProcessing),
               NO_PARMS,
               NEVER_REJECT);
   
   //-------------------------------------------------------------------------
   /** 
   * This method is used to resume command processing by calling the
   * rejector unblock operation.
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(  RETURNS_VOID,
               NAME(resetSecure),
               NO_PARMS,
               NEVER_REJECT);
    

   //-------------------------------------------------------------------------
   /**
   * This method is an event handler that sets lastCommand to CLOSE when 
   * closeSwitch changes to On, and forces a state calculation.
   *
   * @param   FDs - The list of fds monitored for a lastCommand change: 
   *                pCloseSwitch_
   */
   //-------------------------------------------------------------------------
   RTC_EVENT_HANDLER( NAME(verifyCockpitSwitchClose),
                      PARMS1(const RTC_Event::FDInfo_t, FDs) ); 
   
   //-------------------------------------------------------------------------
   /**
   * This method is an event handler that sets lastCommand to OPEN when 
   * openSwitch changes to On, and forces a state calculation.
   *
   * @param   FDs - The list of fds monitored for a lastCommand change: 
   *                pOpenSwitch_
   */
   //-------------------------------------------------------------------------
   RTC_EVENT_HANDLER( NAME(verifyCockpitSwitchOpen),
                      PARMS1(const RTC_Event::FDInfo_t, FDs) ); 
   
public:

   
   //-------------------------------------------------------------------------
   /**
   * OMS_VValveWith1Open1CloseCmd destructor.
   */
   //-------------------------------------------------------------------------
   virtual ~OMS_VValveWith1Open1CloseCmd();
   
   //-------------------------------------------------------------------------
   /**
   * This method clears the state FD stale bit, initializes the lastCommand 
   * based on the open indicator, registers for change data call backs for 
   * the cockpit switches, and calls the parent class method.
   *
   * @return true if initialization completes successfully, otherwise false.
   */
   //-------------------------------------------------------------------------
   virtual bool initialize();
   
   //-------------------------------------------------------------------------
   /**
   * This method calls the parent class method and sets the state FD
   * stale bit.
   */
   //-------------------------------------------------------------------------
   virtual void terminate();
   
   //-------------------------------------------------------------------------
   /**
   * listMethods - This method adds class methods to the methods
   * list to be displayed by the TADD.
   *
   * @param   rMethods - A reference to the method list
   */
   //-------------------------------------------------------------------------
   virtual void listMethods( RTC_IPCInterface::DisplayObj::List_t& rMethods);
   

   //-------------------------------------------------------------------------
   /**
   * listAttributes - This method adds class attributes to the attribute
   * list to be displayed by the TADD.
   *
   * @param   rAttributes - A reference to the attribute list
   */
   //-------------------------------------------------------------------------
   virtual void listAttributes( 
      RTC_IPCInterface::DisplayObj::List_t& rAttributes);

   //-------------------------------------------------------------------------
   /**
   * This is a pure virtual method used to verify the open prerequisites for 
   * the given object.
   *
   * return true if the prerequisites are met, otherwise false.
   */
   //-------------------------------------------------------------------------
   virtual bool prereqsMet() const = 0;


protected:
   
   //-------------------------------------------------------------------------
   /**
   * OMS_VValveWith1Open1CloseCmd
   *
   * @param rParentPath specifies the path of the parent object that this 
   *                    object is an aggregate of.
   * @param rIdentifier specifies an id which is concatenated to the 
   *                    rParentPath to form a unique path for this object. 
   *                    The path is used to retrieve instance data 
   *                    from the Instance Map. 
   * @param attributes  Object attributes.
   */   
   //-------------------------------------------------------------------------
   OMS_VValveWith1Open1CloseCmd(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier,
      Attributes_t attributes = PASSIVE_OBJ bitor 
                                JOIN_APP_REGISTRY bitor 
                                EXPORT_IPC_IF);

   //-------------------------------------------------------------------------
   /**
   * calculateState - This method calculates the valve state using  the
   * indicators and last command based on the follow table:
   *
   *    <state>         <lastCommand> <openIndicator> <closedIndicator>
   *    -------         ------------- --------------- -----------------
   *    CLOSED             CLOSE          OFF                ON
   *    CLOSED_ERROR       CLOSE          ON                 ANY
   *    CLOSED_ERROR       CLOSE          ANY                OFF
   *    OPEN               OPEN           ON                 OFF
   *    OPEN_ERROR         OPEN           OFF                ANY
   *    OPEN_ERROR         OPEN           ANY                ON
   *
   * @param FDs - The list of FDs used in computing the new state:
   *              pOpenCommand_, pCloseCommand_,
   *              pOpenIndicator_, pCloseIndicator_
   *
   * @return CL_OP2_ENUM_t - the calculated state
   */   
   //-------------------------------------------------------------------------
   virtual CL_OP2_ENUM::CL_OP2_ENUM_t calculateState(
      const RTC_Event::FDInfo_t& FDs) const;


   //-------------------------------------------------------------------------
   /**
   * stateCalculationFDs - returns the list of FDs used in the calculateState
   * operation.
   *
   * @return RTC_list - The list { pOpenCommand_, pCloseCommand_,
   *                               pOpenIndicator_, pCloseIndicator_ }
   */
   //-------------------------------------------------------------------------
   virtual RTC_FDS::FDList_t stateCalculationFDs() const;

   //-------------------------------------------------------------------------
   /**
   * This utility method is used by the open and turnOnOpenCommand methods.
   * Since the only difference between these two methods is that the open
   * operation turns off the openCommand, the beginning part of the open 
   * seqence is defined here, and the completion is defined in the verifyState
   * method.
   *
   * @return true if the valve prerequsite check passes, otherwise false.
   */
   //-------------------------------------------------------------------------
   bool beginOpenSequence();

   //-------------------------------------------------------------------------
   /**
   * This utility method is used by the close and turnOnCloseCommand methods.
   * Since the only difference between these two methods is that the close
   * operation turns off the closeCommand, the beginning part of the close 
   * seqence is defined here, and the completion is defined in the verifyState
   *  method.
   */
   //-------------------------------------------------------------------------
   void beginCloseSequence();

   //-------------------------------------------------------------------------
   /**
   * This utility method is used by the open, close, turnOnOpenCommand, and
   * turnOnCloseCommand methods.  This method activates state synthesis, and
   * verifies that the valve state is equal to the expectedState parameter
   * within the OMS_DATA_RATE (1 sec).  If not the errmsg std::string is used to
   * notify the operator.
   *
   * @param expectedState - The expected state (OPEN or CLOSED)
   * @param errmsg - The message sent to the user if the state is not equal
   *                 to the expected state.
   */
   //-------------------------------------------------------------------------
   OMS::Status_t verifyState( const CL_OP2_ENUM::CL_OP2_ENUM_t expectedState,
                              const RTC_String& errmsg );


   //-------------------------------------------------------------------------
   /**
   * This method is a utility function used for prerequisite checking.
   * If the data is valid, a tolerance is determined based on the 
   * contaminationState and the pressureToCompare parameters.  If the
   * contamination state is NOT FULL, the tolerance is 10; otherwise, the
   * tolerance is based on the pressureToCompare as follows:
   *
   *          pressureToCompare <  60  ==> tolerance is 25
   *    60 <= pressureToCompare <= 110 ==> tolerance is 50
   *          pressureToCompare >  110 ==> tolerance is 100
   *
   * Finally, if the delta pressure between the pressureToCompare and 
   * otherPress parameters is less than the tolerance, the pressure is
   * within range.  An appropriate error message is appended to the errmsg 
   * std::string paramter if the pressure is not within range.
   *
   * @param pPressureToCompare - the value checked against the tolerance
   * @param pOtherPress - Used with pPressureToCompare to determine the
   *         delta pressure.
   * @param pContaminationState - Plumbing contamination state
   * @param rErrmsg - Used to return error message if pressure is not in range
   *
   * @return true if the data is valid and the pressure is within range, 
   *         otherwise false.
   *
   */
   //-------------------------------------------------------------------------
   bool pressureInRange( RTC_FD* pPressureToCompare,
                         RTC_FD* pOtherPress,
                         RTC_FD* pContaminationState,
                         RTC_String& rErrmsg ) const;


   //-------------------------------------------------------------------------
   /**
   * This method is a utility function used for prerequisite checking.
   * If the data is valid, and the delta pressure between the 
   * pressureToCompare and the otherPress parameters is less than 25.0,
   * the pressure is within range.  An appropriate error message is appended 
   * to the errmsg std::string paramter if the pressure is not within range.
   *
   * @param pPressureToCompare - Pressure value to compare
   * @param pOtherPress - Other pressure value to compare
   * @param rErrmsg - Used to return error message if pressure is not in range
   *
   * @return true if the data is valid and the pressure is within range, 
   *         otherwise false.
   *
   */
   //-------------------------------------------------------------------------
   bool pressureInRange( RTC_FD* pPressureToCompare,
                         RTC_FD* pOtherPress,
                         RTC_String& rErrmsg ) const;


   //-------------------------------------------------------------------------
   /**
   * This method is used to determine if the tank isolation state
   * paramter is ISOLATED.
   *
   * @param pIsoState - the isolation state
   *
   * @return true if the data is valid and the value of the isolation state is 
   *         ISOLATED, otherwise false.
   */
   //-------------------------------------------------------------------------
   bool isTankIsolated( RTC_FD* pIsoState ) const;


   //------------------------------------------------------------------------
   /**
   * This method is used to determine if all three tank isolation state
   * paramters are ISOLATED.
   *
   * @param pTkIsoState1 - the isolation state of tank1
   * @param pTkIsoState2 - the isolation state of tank2
   * @param pTkIsoState3 - the isolation state of tank3
   * @param rErrmsg - Used to return error message if a tank is not isolated
   *
   * @return true if the data is valid and the value of each isolation state 
   *         is ISOLATED, otherwise false.
   */
   //--------------------------------------------------------------------------
   bool tanksAreIsolated( RTC_FD* pTkIsoState1,
                          RTC_FD* pTkIsoState2,
                          RTC_FD* pTkIsoState3,
                          RTC_String& rErrmsg ) const;

   //-------------------------------------------------------------------------
   /**
   * This method is used to determine if the tank system and the three
   * tank isolation state parameters are all ISOLATED.
   *
   * @param pTkSysIsoState - the isolation state of the tank system
   * @param pTkIsoState1 - the isolation state of tank1
   * @param pTkIsoState2 - the isolation state of tank2
   * @param pTkIsoState3 - the isolation state of tank3
   * @param rErrmsg - Used to return error message if a tank is not isolated
   *
   * @return true if the data is valid and the value of each isolation state 
   *         is ISOLATED, otherwise false.
   */
   //--------------------------------------------------------------------------
   bool tkSysOrOtherTksIsolated( RTC_FD* pTkSysIsoState,
                                 RTC_FD* pTkIsoState1,
                                 RTC_FD* pTkIsoState2,
                                 RTC_FD* pTkIsoState3,
                                 RTC_String& rErrmsg ) const;
      
   //-------------------------------------------------------------------------
   /**
   * This method is used to determine if the valveState parameter is OPEN.
   *
   * @param pValveState - the valve state
   *
   * @return true if the data is valid and the value of the valve state 
   *         is OPEN, otherwise false.
   */
   //-------------------------------------------------------------------------
   bool isValveOpen( RTC_FD* pValveState ) const;


   //-------------------------------------------------------------------------
   /**
   * This method is used to determine if the plumbing state is FULL.
   *
   * @param pPlumbingState - the plumbing state
   *
   * @return true if the data is valid and the value of the plumbing state 
   *         is FULL, otherwise false.
   */
   //-------------------------------------------------------------------------
   bool isFull( RTC_FD* pPlumbingState ) const;


   //-------------------------------------------------------------------------
   /**
   * This method is used to determine if the crossfeed Flange is MATED.
   *
   * @param pLeftFlangeState - the left flange state
   * @param pRightFlangeState - the right flange state
   * @param rErrmsg - Used to return error message if a flange is not MATED
   *
   * @return true if the data is valid and the values of both the left
   *         and right flange states are MATED, otherwise false.
   */
   //-------------------------------------------------------------------------
   bool xfdFlangeIsMated( RTC_FD* pLeftFlangeState,
                          RTC_FD* pRightFlangeState,
                          RTC_String& rErrmsg ) const;


   //-------------------------------------------------------------------------
   /**
   * This method is used to determine if state1 and state2 are equal
   *
   * @param pState1 - state1
   * @param pState2 - state2
   *
   * @return true if the data is valid and the values of state1 and state2
   *         are equal, otherwise false.
   */
   //-------------------------------------------------------------------------
   bool statesMatch( RTC_FD* pState1,
                     RTC_FD* pState2 ) const;
   
   
   //-------------------------------------------------------------------------
   /**
   * createIPCInterface instantiates an interprocess communication interface.
   *
   * This method is called from this base class to instantiate an
   * interprocess communication interface for the object during 
   * initialization.
   *
   * @return newly instantiated interprocess communication interface for the 
   *         object
   */
   //-------------------------------------------------------------------------
   RTC_IPCMan::ObjInterface_t createIPCInterface();
      
   /**
   * Discrete Measurement FD indicating valve in the closed position. 
   */
   RTC_FD* pCloseIndicator_;

   /**
   * Discrete Measurement FD indicating valve in the open position. 
   */
   RTC_FD* pOpenIndicator_;

   /**
   * Discrete Stimulus momentary command FD to close the valve. 
   */
   RTC_FD* pCloseCommand_;

   /**
   * Discrete Stimulus momentary command FD to open the valve. 
   */
   RTC_FD* pOpenCommand_;
   
   /**
   * Cockpit switch close position 
   */
   RTC_FD* pCloseSwitch_;

   /**
   * Cockpit switch open position 
   */
   RTC_FD* pOpenSwitch_;

   /**
   * Internal variable to hold the last commanded valve position. 
   */
   volatile OMS::OpenClose_t lastCommand_;
   
   /**
   * Maximum time allowed for valve to cycle from one position to another. 
   */
   static const RTC_Time::Value_t CYCLE_TIME;

   /**
   * The error message to be returned if open operation fails.
   */
   static const RTC_String OPEN_ERR_MSG;

   /**
   * The error message to be returned if the close operation fails.
   */
   static const RTC_String CLOSE_ERR_MSG;

   /**
   * The error message to be returned if the verifySecure operation fails.
   */
   static const RTC_String SECURE_ERR_MSG;
   
   /**
   * The flag used to block command processing when the object is secured. 
   */
   RTC_Command::TestRejector objectSecured_;
   

   // TOGETHER GENERATED LINK INFORMATION
   /** @link dependency 
   * @stereotype derive*/
   /*#  OMS_Object lnkOMS_Object; */
   
};

#endif //OMS_VVALVEWITH1OPEN1CLOSECMD_H
