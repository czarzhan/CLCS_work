//=============================================================================
//
// NAME: OMS_OmeBiPropValve
//
// OVERVIEW: The OME Bi-Prop valves isolate propellant from the OMS engine 
//           chamber. The valves have no commands, they are pressure actuated
//           with GN2 through the OmeArmValve and down stream regulator.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_OMEBIPROPVALVE_H
#define OMS_OMEBIPROPVALVE_H

//=============================================================================
//                      System Include Files
//=============================================================================
#include <RTC_StateComponent_T.h>
#include <RTC_Event.h>
#include <CL_OP_ENUM.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_Object.h"
#include "OMS_AnalogWithLccLimits.h"

//=============================================================================
//                     External Variables
//=============================================================================
typedef RTC_StateComponent_T<OMS_Object,
                             CL_OP_ENUM::CL_OP_ENUM_t> OMS_OmeBiPropValveBase;
//----------------------------------------------------------------------------
/**
* The OME Bi-Prop valves isolate propellant from the OMS engine chamber.
* The valves have no commands, they are pressure actuated with GN2
* through the OmeArmValve and down stream regulator.
*/
//----------------------------------------------------------------------------
class OMS_OmeBiPropValve : public OMS_OmeBiPropValveBase 
{

   RTC_DECL_CLASS(OMS_OmeBiPropValve);

public:
   //-------------------------------------------------------------------------
   /**
   * OMS_OmeBiPropValve 
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
   OMS_OmeBiPropValve(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier,
      bool initToValid,
      Attributes_t attributes = PASSIVE_OBJ bitor
                                JOIN_APP_REGISTRY bitor 
                                EXPORT_IPC_IF);
   
   //-------------------------------------------------------------------------
   /**
   * OMS_OmeBiPropValve destructor
   */
   //-------------------------------------------------------------------------
   virtual ~OMS_OmeBiPropValve();
   
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
   * terminate - Calls the parent terminate method and deregisters the FDs.
   */
   //-------------------------------------------------------------------------
   virtual void terminate();

   //-------------------------------------------------------------------------
   /**
   * setValid calls the activateStateSynthesis command
   * 
   * This method is meant to be called subsequent to deactivating state 
   * calculation when it is desired to begin calculating the component's
   * state again.
   */
   //-------------------------------------------------------------------------
   void setValid();


   //-------------------------------------------------------------------------
   /**
   * setInvalid call the overrideStateSynthesis command
   * 
   * This method is used to set the state to UNSET and deactivate state 
   * calculation.
   */
   //-------------------------------------------------------------------------
   void setInvalid();


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
   * @param FDs FD information to be used to compute the new state of the
   *               component: pOpenIndicator_::pAnalog_
   * @return the new calculated state of the component
   */   
   //-------------------------------------------------------------------------
   virtual CL_OP_ENUM::CL_OP_ENUM_t calculateState(
      const RTC_Event::FDInfo_t& FDs) const;


   //-------------------------------------------------------------------------
   /**
   * stateCalculationFDs is a function that should return a list of FDs that
   * should be used to determine the state of the component.
   *
   * This list should contain any FDs, that upon their change, will affect 
   * the state of this component: pOpenIndicator_::pAnalog_
   *
   * @return the list of FDs that determine the state of the component.
   */   
   //-------------------------------------------------------------------------
   virtual RTC_FDS::FDList_t stateCalculationFDs() const;
   
private:
      
   /** 
   * The OmeBiPropValve indicates open when the analog measurement
   * is greater than 5 per cent. 
   * TOGETHER GENERATED LINK INFORMATION,  Do not delete
   * @link aggregationByValue
   * @undirected
   * @supplierCardinality 1
   */
   OMS_AnalogWithLccLimits* pOpenIndicator_;

   /**
   * This is the state (MATED, DEMATED) of the engine's electrical system.
   */
   RTC_FD* pElectricalStateRO_;
       
   // TOGETHER GENERATED LINK INFORMATION,  Do not delete 
   /** @link dependency 
    * @stereotype derive*/
   /*#  OMS_Object lnkOMS_Object; */
};
#endif //OMS_OMEBIPROPVALVE_H
