//=============================================================================
//
// NAME:  OMS_IPCIF_CockpitMeterTest
//
// OVERVIEW: Provides all IPC interfaces for OMS_CockpitMeterTest.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_IPCIF_COCKPITMETERTEST_H
#define OMS_IPCIF_COCKPITMETERTEST_H

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
class OMS_CockpitMeterTest;

//-----------------------------------------------------------------------------
/**
* Provides all IPC interfaces for OMS_CockpitMeterTest.
* 
* @interface 
*/
//-----------------------------------------------------------------------------
class OMS_IPCIF_CockpitMeterTest :
   public OMS_IPCIF_Object,
   public virtual POA_OMS_VehicleTests_ObjAdaptor::CockpitMeterTest
{
public:    

   //--------------------------------------------------------------------------
   /**
   * OMS_IPCIF_CockpitMeterTest - This is the IPC interface constructor used to
   * bind to a reference of the OMS_CockpitMeterTest class
   * 
   * @param rImpl A reference to the OMS_CockpitMeterTest instance which
   *              implements the interface methods
   */
   //--------------------------------------------------------------------------
   OMS_IPCIF_CockpitMeterTest(OMS_CockpitMeterTest& rImpl);
 


   //--------------------------------------------------------------------------
   /**
   * IPC Interface destructor
   */
   //--------------------------------------------------------------------------
   ~OMS_IPCIF_CockpitMeterTest();



   //--------------------------------------------------------------------------
   /**
   * Set frcsOxidQty FD to operator input. 
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long applyFrcsOxid(double pctQty);

   //--------------------------------------------------------------------------
   /**
   * Set frcsFuelQty FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long applyFrcsFuel(double pctQty);

   //--------------------------------------------------------------------------
   /**
   * Set frcsLowest FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long applyFrcsLowest(double pctQty);

   //--------------------------------------------------------------------------
   /**
   * Set lrcsOxidQty FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long applyLrcsOxid(double pctQty);

   //--------------------------------------------------------------------------
   /**
   * Set lrcsFuelQty FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long applyLrcsFuel(double pctQty);
   
   //--------------------------------------------------------------------------
   /**
   * Set lrcsLowest FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long applyLrcsLowest(double pctQty);
   
   //--------------------------------------------------------------------------
   /**
   * Set rrcsOxidQty FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long applyRrcsOxid(double pctQty);
   
   //--------------------------------------------------------------------------
   /**
   * Set rrcsFuelQty FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long applyRrcsFuel(double pctQty);
   
   //--------------------------------------------------------------------------
   /**
   * Set rrcsLowest FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long applyRrcsLowest(double pctQty);
   
private:
   
   // TOGETHER MATERIAL, DO NOT REMOVE.
   /** @link dependency 
   * @stereotype use*/
   /*#  OMS_CockpitMeterTest lnkOMS_CockpitMeterTest; */
   OMS_CockpitMeterTest& rImpl_;
   
};

#endif // OMS_IPCIF_COCKPITMETERTEST_H
