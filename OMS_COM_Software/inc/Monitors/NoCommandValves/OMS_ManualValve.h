//=============================================================================
//
// NAME: OMS_ManualValve
//
// OVERVIEW:  The Manual Valve has no remote control and no monitor capability.
//            The valve state is maintained for configuration information.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_MANUALVALVE_H
#define OMS_MANUALVALVE_H

//=============================================================================
//                      System Include Files
//=============================================================================
#include <RTC_FD.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_Object.h"


//=============================================================================
//                      Class Declarations
//=============================================================================

//----------------------------------------------------------------------------
/**
* The Manual Valve has no remote control and no monitor
* capability. The valve state is maintained for configuration 
* information. 
*/
//----------------------------------------------------------------------------
class OMS_ManualValve : public OMS_Object 
{

   RTC_DECL_CLASS(OMS_ManualValve);

public:
   //-------------------------------------------------------------------------
   /**
   * toggle - If the state is CLOSED, set the state to OPEN; otherwise 
   * set the state to CLOSED.
   * 
   * @return    void
   */
   //-------------------------------------------------------------------------
   RTC_PROXY ( RETURNS_VOID,
               NAME ( toggle ),
               NO_PARMS,
               NEVER_REJECT );

public:    
   //-------------------------------------------------------------------------
   /**
   * OMS_ManualValve
   *
   * @param rParentPath  specifies the path of the parent object that this 
   *                     object is an aggregate of.
   * @param rIdentifier  specifies an id which is concatenated to the 
   *                     rParentPath to form a unique path for this object. 
   *                     The path is used to retrieve instance data 
   *                     from the Instance Map. 
   */
   //-------------------------------------------------------------------------
   OMS_ManualValve(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier );
   
   //-------------------------------------------------------------------------
   /**
   * OMS_ManualValve destructor
   */
   //-------------------------------------------------------------------------
   virtual ~OMS_ManualValve();

   //-------------------------------------------------------------------------
   /**
   * initialize - This method initializes the valve's state to the persistent
   * value, and calls the parent class method.
   *
   * @return bool - Results of call to parent class method.
   */
   //-------------------------------------------------------------------------
   virtual bool initialize();


   //-------------------------------------------------------------------------
   /**
   * terminate - This method calls the parent class method, and sets health
   * of the pseudo to Inactive.
   *
   * @return void
   */
   //-------------------------------------------------------------------------
   virtual void terminate();

   
   //-------------------------------------------------------------------------
   /**
   * listMethods - This method adds class methods to the methods
   * list to be displayed by the TADD.
   *
   * @param   rMethods   a reference to the list of methods for the class
   * @return  void
   */
   //-------------------------------------------------------------------------
   void listMethods(RTC_IPCInterface::DisplayObj::List_t& rMethods); 


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

private:    
   /**
   *  Used to track valve position. Values are OPEN, CLOSED and UNKNOWN.
   *  Default value is UNKNOWN. 
   */
   RTC_FD* pState_;

   /**
   * Member variable used to keep persistent data
   */
   RTC_DECL_ATTRIBUTE (int, persistentState_);


};
#endif // OMS_MANUALVALVE_H
