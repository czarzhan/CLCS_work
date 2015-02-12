//=============================================================================
//
// NAME: OMS_OmeArmValve
//
// OVERVIEW: The OME arm valves isolate the GN2 tank from the regulator.
//           The regulated GN2 is used to actuate the bi-propellant valves.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_OMEARMVALVE_H
#define OMS_OMEARMVALVE_H

//=============================================================================
//                      System Include Files
//=============================================================================
#include <RTC_StateComponent_T.h>
#include <RTC_Event.h>
#include <CL_OP2_ENUM.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_Object.h"

//=============================================================================
//                     External Variables
//=============================================================================
typedef RTC_StateComponent_T< OMS_Object,
                              CL_OP2_ENUM::CL_OP2_ENUM_t > OMS_OmeArmValveBase;


//-------------------------------------------------------------------------
/**
* The OME arm valves isolate the GN2 tank from the regulator.
* The regulated GN2 is used to actuate the bi-propellant valves. 
*/
//-------------------------------------------------------------------------
class OMS_OmeArmValve :  public OMS_OmeArmValveBase 
{

   RTC_DECL_CLASS(OMS_OmeArmValve);

public:
   //-------------------------------------------------------------------------
   /**
   * OMS_OmeArmValve constructor
   *
   * @param rParentPath  specifies the path of the parent object that this 
   *                     object is an aggregate of.
   * @param rIdentifier  specifies an id which is concatenated to the 
   *                     rParentPath to form a unique path for this object. 
   *                     The path is used to retrieve instance data 
   *                     from the Instance Map. 
   * @param attributes   Object attributes. 
   */
   //-------------------------------------------------------------------------
   OMS_OmeArmValve(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier,
      Attributes_t attributes = PASSIVE_OBJ bitor
                                JOIN_APP_REGISTRY bitor 
                                EXPORT_IPC_IF);
   
   //-------------------------------------------------------------------------
   /**
   * OMS_OmeArmValve destructor
   */
   //-------------------------------------------------------------------------
   ~OMS_OmeArmValve();

   //-------------------------------------------------------------------------
   /**
   * initialize - This method initializes the OmeArmValves, and registers for
   * change data for the state calculation.
   *
   * @return bool - Results of call to parent class method.
   */
   //-------------------------------------------------------------------------
   virtual bool initialize();

   //-------------------------------------------------------------------------
   /**
   * terminate -  Calls the parent terminate function, then deregisters change
   *              data and sets the health to inactive
   */
   //-------------------------------------------------------------------------
   virtual void terminate();


protected:
   //-------------------------------------------------------------------------
   /**
   * calculateState contains the algorithm to calculate the current state
   * of the component when an FD that the state is composed of changes.
   *
   * This method will be registered with the Event Manager to perform synthesis
   * on all the state calculation FDs to return the new state.  No FD writes
   * need to be performed within, as the Event Manager writes the new state to
   * its appropriate pseudo FD, also calculating the FD health information.
   *
   * @param FDs - The FDs used in computing the new state: pOpenIndicator_
   *                                                       pOpenASwitch_
   *                                                       pOpenBSwitch_
   * 
   * @return CL_OP2_ENUM_t - the calculated state
   */   
   //-------------------------------------------------------------------------
   virtual CL_OP2_ENUM::CL_OP2_ENUM_t calculateState(
      const RTC_Event::FDInfo_t& FDs) const;

   //-------------------------------------------------------------------------
   /**
   * stateCalculationFDs is a function that should return a list of FDs that
   * should be used to determine the state of the component.
   *
   * This list should contain any FDs, that upon their change, will affect 
   * the state of this component.
   *
   * @return the list of FDs that determine the state of the component:
   *             pOpenIndicator_
   *             pOpenASwitch_
   *             pOpenBSwitch_
   */   
   //-------------------------------------------------------------------------
   virtual RTC_FDS::FDList_t stateCalculationFDs() const;
   
private:    
   /**
   * This valve has one open position indicator.
   */
   RTC_FD* pOpenIndicator_;

   /**
   * The valve can only be controlled by cockpit switch throw.
   * May use cockpit switch A or cockpit switch B.
   */
   RTC_FD* pOpenASwitch_;
   
   /**
   * The valve can only be controlled by cockpit switch throw.
   * May use cockpit switch A or cockpit switch B.
   */
   RTC_FD* pOpenBSwitch_;

   /**
   * This is the state (MATED, DEMATED) of the engine's electrical system.
   */
   RTC_FD* pElectricalStateRO_;
       
   // TOGETHER GENERATED LINK INFORMATION
   /** @link dependency 
    * @stereotype derive*/
   /*#  OMS_Object lnkOMS_Object; */
};
#endif // OMS_OMEARMVALVE_H
