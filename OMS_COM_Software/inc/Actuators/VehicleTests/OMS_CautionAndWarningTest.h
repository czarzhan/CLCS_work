//=============================================================================
//
// NAME: OMS_CautionAndWarningTest
//
// OVERVIEW: This class captures the functionality to support the testing of
//           the OMS and RCS caution and warning parameters.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_CAUTIONANDWARNINGTEST_H
#define OMS_CAUTIONANDWARNINGTEST_H

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

//-----------------------------------------------------------------------------
/**
* This class captures the functionality to support the testing of the OMS and
* RCS caution and warning parameters. 
*/
//-----------------------------------------------------------------------------
class OMS_CautionAndWarningTest : public OMS_Object 
{

   RTC_DECL_CLASS(OMS_CautionAndWarningTest);

   //--------------------------------------------------------------------------
   /**
   * Turns off fwdRcsFd and leaves it off.  Operator use only.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( turnOffFwdRcs ),
              NO_PARMS,
              NEVER_REJECT );

   
   //--------------------------------------------------------------------------
   /**
   * Turns on fwdRcsFd and leaves it on.  Operator use only. 
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( turnOnFwdRcs ),
              NO_PARMS,
              NEVER_REJECT );


   //--------------------------------------------------------------------------
   /**
   * Turns off leftRcsFd and leaves it off.  Operator use only.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( turnOffLeftRcs ),
              NO_PARMS,
              NEVER_REJECT );

   
   //--------------------------------------------------------------------------
   /**
   * Turns on leftRcsFd and leaves it on.  Operator use only.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( turnOnLeftRcs ),
              NO_PARMS,
              NEVER_REJECT );


   //--------------------------------------------------------------------------
   /**
   * Turns off rightRcsFd and leaves it off.  Operator use only.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( turnOffRightRcs ),
              NO_PARMS,
              NEVER_REJECT );

   
   //--------------------------------------------------------------------------
   /**
   * Turns on rightRcsFd and leaves it on.  Operator use only.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( turnOnRightRcs ),
              NO_PARMS,
              NEVER_REJECT );


   //--------------------------------------------------------------------------
   /**
   * Turns off leftRcsFd and leaves it off.  Operator use only.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( turnOffLeftOms ),
              NO_PARMS,
              NEVER_REJECT );

   
   //--------------------------------------------------------------------------
   /**
   * Turns on leftOmsFd and leaves it on.  Operator use only.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( turnOnLeftOms ),
              NO_PARMS,
              NEVER_REJECT );

   
   //--------------------------------------------------------------------------
   /**
   * Turns off rightOmsFd and leaves it off.  Operator use only.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( turnOffRightOms ),
              NO_PARMS,
              NEVER_REJECT );

   
   //--------------------------------------------------------------------------
   /**
   * Turns on rightOmsFd and leaves it on.  Operator use only.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( turnOnRightOms ),
              NO_PARMS,
              NEVER_REJECT );

public:

   //--------------------------------------------------------------------------
   /**
   * OMS_CautionAndWarningTest
   *
   * @param rParentPath  specifies the path of the parent object that this 
   *                     object is an aggregate of.
   * @param rIdentifier  specifies an id which is concatenated to the 
   *                     rParentPath to form a unique path for this object. 
   *                     The path is used to retrieve instance data 
   *                     from the Instance Map. 
   */   
   //--------------------------------------------------------------------------
   OMS_CautionAndWarningTest( const RTC_String& rParentPath, 
                              const RTC_String& rIdentifier );

   //--------------------------------------------------------------------------
   /**
   * OMS_CautionAndWarningTest destructor
   */
   //--------------------------------------------------------------------------
   virtual ~OMS_CautionAndWarningTest();

   //-------------------------------------------------------------------------
   /**
   * listMethods - This method adds class methods to the methods
   * list to be displayed by the TADD.
   *
   * @param   rMethods a list of methods to be displayed
    */
   //-------------------------------------------------------------------------
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
   * The caution and warning paramter that is triggered when there is a leak 
   * detected in the FRCS. Initial value is Off.
   */
   RTC_FD* pFwdRcsFd_;
   
   /**
   * The caution and warning paramter that is triggered when there is a leak
   * detected in the LRCS. Initial value is Off.
   */
   RTC_FD* pLeftRcsFd_;

   /**
   * The caution and warning paramter that is triggered when an anomaly is
   * detected with the LOMS engine. Initial value is Off.
   */
   RTC_FD* pLeftOmsFd_;
   
   /**
   * The caution and warning paramter that is triggered when there is a leak
   * detected in the RRCS. Initial value is Off.
   */
   RTC_FD* pRightRcsFd_;
   
   /**
   * The caution and warning paramter that is triggered when an anomaly is
   * detected with the ROMS engine. Initial value is Off.
   */
   RTC_FD* pRightOmsFd_;

};

#endif // OMS_CAUTIONANDWARNINGTEST_H
