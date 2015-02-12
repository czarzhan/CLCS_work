//=============================================================================
//
// NAME: OMS_NoCmdNoVpiValve 
//
// OVERVIEW: This class defines the quick disconnect which provides an
//           interface between the facility and vehicle systems. This device
//           has no hardware command or measurement for monitoring. The
//           operator may set the state to an enumeration of OMS_OPF_QD_ENUM.
//           This item provides configuration information and is published
//           as persistant data.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_NOCMDNOVPIVALVE_H
#define OMS_NOCMDNOVPIVALVE_H

//=============================================================================
//                      System Include Files
//=============================================================================
#include <RTC_FD.h>
#include <OMS_OPF_QD_ENUM.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_Object.h"


//=============================================================================
//                        Class Declarations
//=============================================================================

//----------------------------------------------------------------------------
/**
* This class defines the quick disconnect which provides an
* interface between the facility and vehicle systems. This device
* has no hardware command or measurement for monitoring. The
* operator may set the state to an enumeration of OMS_OPF_QD_ENUM.
* This item provides configuration information and is published
* as persistant data.
*/
//----------------------------------------------------------------------------
class OMS_NoCmdNoVpiValve : public OMS_Object 
{
   RTC_DECL_CLASS(OMS_NoCmdNoVpiValve);

public:    
   //-------------------------------------------------------------------------
   /**
   * setState - Set the state to the operator selected state.
   * 
   * @param   The new state for the quick disconnect.
   * @return  void
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(RETURNS_VOID,
             NAME(setState),
             PARMS1(OMS_OPF_QD_ENUM::OMS_OPF_QD_ENUM_t, state),
             NEVER_REJECT);

public:

   //-------------------------------------------------------------------------
   /**
   * OMS_NoCmdNoVpiValve constructor
   *
   * @param rParentPath  specifies the path of the parent object that this 
   *                     object is an aggregate of.
   * @param rIdentifier  specifies an id which is concatenated to the 
   *                     rParentPath to form a unique path for this object. 
   *                     The path is used to retrieve instance data 
   *                     from the Instance Map. 
   * @param qdType       specifies the type of quick disconnect for 
   *                     each instance of NoCmdNoVpiValve.
   */
   //-------------------------------------------------------------------------
   OMS_NoCmdNoVpiValve(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier,
      OMS::QdType_t qdType);

   //-------------------------------------------------------------------------
   /**
   * OMS_NoCmdNoVpiValve destructor.
   */
   //-------------------------------------------------------------------------
   virtual ~OMS_NoCmdNoVpiValve();

   //-------------------------------------------------------------------------
   /**
   * initialize - This method initializes the quick disconnects, sets the
   * persistent value, and calls the parent class method.
   *
   * @return bool - Results of call to parent class method.
   */
   //-------------------------------------------------------------------------
   virtual bool initialize();


   //-------------------------------------------------------------------------
   /**
   * terminate - This method calls the parent class method, and deactivates
   * health checking for the QDs.
   *
   * @return void
   */
   //-------------------------------------------------------------------------
   virtual void terminate();


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


   //-------------------------------------------------------------------------
   /**
   * listMethods - This method adds class methods to the methods
   * list to be displayed by the TADD.
   *
   * @return  void
   * @param   rMethods a list of methods to be displayed
   */
   //-------------------------------------------------------------------------
   void listMethods(RTC_IPCInterface::DisplayObj::List_t& rMethods); 


private: 
   
   /**
   * User defined pseudo FD which contains the QD enumerated value.
   */
   RTC_FD* pState_;

   /**
   * Enumerated QD type, to determine which functions are displayed.
   */
   OMS::QdType_t qdType_;

   /**
   * Member variable used to keep persistent data
   */
   RTC_DECL_ATTRIBUTE (int, persistentState_);

};
#endif //OMS_NOCMDNOVPIVALVE_H
