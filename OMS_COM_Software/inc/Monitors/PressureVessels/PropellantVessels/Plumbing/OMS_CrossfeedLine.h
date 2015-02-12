//=============================================================================
//
// NAME: OMS_CrossfeedLine
//
// OVERVIEW: OMS_CrossfeedLine class provides functionality for the propellant
//           path between the OMS and RCS systems within the same pod and 
//           through the orbiter to the opposite pod.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_CROSSFEEDLINE_H
#define OMS_CROSSFEEDLINE_H
 
//=============================================================================
//                      System Include Files
//=============================================================================
#include <RTC_FD.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_PrimaryManifold.h"


//=============================================================================
//                      Class Declarations
//=============================================================================

//--------------------------------------------------------------------------
/**
*
* OMS_CrossfeedLine class provides functionality for the propellant path 
* between the OMS and RCS systems within the same pod and through the 
* orbiter to the opposite pod.
*
*/
//--------------------------------------------------------------------------
class OMS_CrossfeedLine : public OMS_PrimaryManifold 
{

   RTC_DECL_CLASS(OMS_CrossfeedLine);

   //-------------------------------------------------------------------------
   /**
   * toggleLeftFlangeState - If leftFlangeState is DEMATED or UNSET, sets to
   *                         MATED.  Else sets to DEMATED. 
   */
   //-------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME(toggleLeftFlangeState),
              NO_PARMS,
              NEVER_REJECT );
   
   //-------------------------------------------------------------------------
   /**
   * toggleRightFlangeState - If rightFlangeState is DEMATED or UNSET, sets to
   *                          MATED.  Else sets to DEMATED. 
   */
   //-------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME(toggleRightFlangeState),
              NO_PARMS,
              NEVER_REJECT );
   
   
public:
   //-------------------------------------------------------------------------
   /**
   * OMS_CrossfeedLine
   *
   * @param rParentPath   specifies the path of the parent object that this 
   *                      object is an aggregate of.
   * @param rIdentifier   specifies an id which is concatenated to the 
   *                      rParentPath to form a unique path for this object. 
   *                      The path is used to retrieve instance data 
   *                      from the Instance Map. 
   */
   //-------------------------------------------------------------------------
   OMS_CrossfeedLine(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier);
   
   //-------------------------------------------------------------------------
   /**
   * OMS_CrossfeedLine destructor
   */
   //-------------------------------------------------------------------------
   virtual ~OMS_CrossfeedLine();
   
   //--------------------------------------------------------------------------
   /**
   * initialize - This method initializes the crossfeed lines, sets the
   * persistent values, and calls the parent class method.
   *
   * @return bool - Results of call to parent class method.
   */
   //--------------------------------------------------------------------------
   virtual bool initialize();


   //--------------------------------------------------------------------------
   /**
   * terminate - This method calls the parent class method, and deactivates
   * health checking for the crossfeed lines.
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
   * Mated state of the left crossfeed flange state.  This is persistently
   * stored in persistentLeftState_. 
   */
   RTC_FD* pLeftFlangeState_;
   
   /**
   * Mated state of the right crossfeed flange state.  This is persistently
   * stored in persistentRightState_. 
   */
   RTC_FD* pRightFlangeState_;

   /**
   * Member variable to store left flange state persistently.
   */
   RTC_DECL_ATTRIBUTE (int, persistentLeftState_);

   /**
   * Member variable to store right flange state persistently.
   */
   RTC_DECL_ATTRIBUTE (int, persistentRightState_);
};
#endif // OMS_CROSSFEEDLINE_H
