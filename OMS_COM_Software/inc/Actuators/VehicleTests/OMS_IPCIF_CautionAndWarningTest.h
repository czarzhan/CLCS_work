//=============================================================================
//
// NAME:  OMS_IPCIF_CautionAndWarningTest
//
// OVERVIEW: Provides all IPC interfaces for OMS_CautionAndWarningTest
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_IPCIF_CAUTIONANDWARNINGTEST_H
#define OMS_IPCIF_CAUTIONANDWARNINGTEST_H

//=============================================================================
//                      System Include Files
//=============================================================================
// This section is not applicable


//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_Object.h"
#include "OMS_VehicleTests_ObjAdaptor_s.hh"


//=============================================================================
//                      Class Declarations
//=============================================================================

//-----------------------------------------------------------------------------
/**
* Forward declaration of the component class.
*/
//-----------------------------------------------------------------------------
class OMS_CautionAndWarningTest;

//-----------------------------------------------------------------------------
/**
* Provides all IPC interfaces for OMS_CautionAndWarningTest.
* 
* @interface 
*/
//-----------------------------------------------------------------------------
class OMS_IPCIF_CautionAndWarningTest : 
   public OMS_IPCIF_Object,
   public virtual POA_OMS_VehicleTests_ObjAdaptor::CautionAndWarningTest
{
public:    

   //--------------------------------------------------------------------------
   /**
   * OMS_IPCIF_CautionAndWarningTest constructor
   */
   //--------------------------------------------------------------------------
   OMS_IPCIF_CautionAndWarningTest(OMS_CautionAndWarningTest& rImpl);

   //--------------------------------------------------------------------------
   /**
   * OMS_IPCIF_CautionAndWarningTest destructor
   */
   //--------------------------------------------------------------------------
   ~OMS_IPCIF_CautionAndWarningTest();
   
   //--------------------------------------------------------------------------
   /**
   * Turns off fwdRcsFd and leaves it off.  Operator use only.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long turnOffFwdRcsFd();
   
   //--------------------------------------------------------------------------
   /**
   * Turns on fwdRcsFd and leaves it on.  Operator use only. 
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long turnOnFwdRcsFd();
   
   //--------------------------------------------------------------------------
   /**
   * Turns off leftRcsFd and leaves it off.  Operator use only.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long turnOffLeftRcsFd();
   
   //--------------------------------------------------------------------------
   /**
   * Turns on leftRcsFd and leaves it on.  Operator use only.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long turnOnLeftRcsFd();
   
   //--------------------------------------------------------------------------
   /**
   * Turns off rightRcsFd and leaves it off.  Operator use only.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long turnOffRightRcsFd();
   
   //--------------------------------------------------------------------------
   /**
   * Turns on rightRcsFd and leaves it on.  Operator use only.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long turnOnRightRcsFd();
   
   //--------------------------------------------------------------------------
   /**
   * Turns off leftOmsFd and leaves it off.  Operator use only.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long turnOffLeftOmsFd();
   
   //--------------------------------------------------------------------------
   /**
   * Turns on leftOmsFd and leaves it on.  Operator use only.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long turnOnLeftOmsFd();
   
   //--------------------------------------------------------------------------
   /**
   * Turns off rightOmsFd and leaves it off.  Operator use only.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long turnOffRightOmsFd();
   
   //--------------------------------------------------------------------------
   /**
   * Turns on rightOmsFd and leaves it on.  Operator use only.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long turnOnRightOmsFd();
   
private:

   // TOGETHER MATERIAL, DO NOT REMOVE.
   /** @link dependency 
   * @stereotype use*/
   /*#  OMS_CautionAndWarningTest lnkOMS_CautionAndWarningTest; */
   OMS_CautionAndWarningTest& rImpl_;
};

#endif // OMS_IPCIF_CAUTIONANDWARNINGTEST_H
