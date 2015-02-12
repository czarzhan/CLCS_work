//=============================================================================
//
// NAME: OMS_VehiclePlumbing
//
// OVERVIEW: Vehicle Plumbing is the base class for propellant line segments
//           between the tank isolation valves and the OMS Engine or RCS 
//           Thrusters. 
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_VEHICLEPLUMBING_H
#define OMS_VEHICLEPLUMBING_H

//=============================================================================
//                      System Include Files
//=============================================================================
#include <RTC_FD.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_Object.h"

//-----------------------------------------------------------------------------
/**
* Vehicle Plumbing is the base class for propellant line segments between the 
* tank isolation valves and the OMS Engine or RCS Thrusters. 
*/
//-----------------------------------------------------------------------------
class OMS_VehiclePlumbing : public OMS_Object 
{
   RTC_DECL_CLASS(OMS_VehiclePlumbing);
 
   //--------------------------------------------------------------------------
   /**
   * toggle - This method toggles the state to the next value {FULL, DRAINED,
   *          DECONTAMINATED}.  If the state is FULL, it is set to DRAINED; 
   *          if DRAINED, set to DECONTAMINATED; else set to FULL.
   * NOTE:  The contamination state of the plumbing is kept persistently. 
   */
   //--------------------------------------------------------------------------
   RTC_PROXY(RETURNS_VOID,
             NAME(toggle),
             NO_PARMS,
             NEVER_REJECT);


public:   
   //--------------------------------------------------------------------------
   /**
   * OMS_VehiclePlumbing destructor
   */
   //--------------------------------------------------------------------------
   virtual ~OMS_VehiclePlumbing();

   //--------------------------------------------------------------------------
   /**
   * initialize - This method initializes vehicle plumbing, sets the
   * persistent value, and calls the parent class method.
   *
   * @return bool - Results of call to parent class method.
   */
   //--------------------------------------------------------------------------
   virtual bool initialize();


   //--------------------------------------------------------------------------
   /**
   * terminate - This method calls the parent class method, and deactivates
   * health checking for vehicle plumbing.
   */
   //--------------------------------------------------------------------------
   virtual void terminate();


   //--------------------------------------------------------------------------
   /**
   * listMethods - This method adds class methods to the methods
   * list to be displayed by the TADD.
   *
   * @param   rMethods a list of methods to be displayed
   */
   //--------------------------------------------------------------------------
   void listMethods(RTC_IPCInterface::DisplayObj::List_t& rMethods); 


protected:
   //--------------------------------------------------------------------------
   /**
   * OMS_VehiclePlumbing constructor
   *
   * @param rParentPath   specifies the path of the parent object that this 
   *                      object is an aggregate of.
   * @param rIdentifier   specifies an id which is concatenated to the 
   *                      rParentPath to form a unique path for this object. 
   *                      The path is used to retrieve instance data 
   *                      from the Instance Map. 
   * @param commodityType defines whether the component is for FUEL or OXID
   */
   //--------------------------------------------------------------------------
   OMS_VehiclePlumbing(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier );

   //--------------------------------------------------------------------------
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
   //--------------------------------------------------------------------------
   RTC_IPCMan::ObjInterface_t createIPCInterface();


private:    

   /**
   * The vehicle plumbing contamination state with valid states:
   * UNKNOWN, FULL (containing liquid propellant), DRAINED
   * (empty/dirty), or DECONTAMINATED(empty/clean).
   * The default shall be UNKNOWN.  The state is persistent.
   */
   RTC_FD* pState_;

   /**
   * Member variable used to keep persistent data
   */
   RTC_DECL_ATTRIBUTE (int, persistentState_);

};
#endif //OMS_VEHICLEPLUMBING_H
