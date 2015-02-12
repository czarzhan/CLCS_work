//=============================================================================
//
// NAME: OMS_CockpitMeterTest
//
// OVERVIEW: This class captures the functionality to support the OMS/RCS
//           cockpit meter test by applying values to the RCS oxidizer, fuel
//           and lowest function designators and checking the corresponding 
//           measurements on the orbiter flight deck.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_COCKPITMETERTEST_H
#define OMS_COCKPITMETERTEST_H

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
* This class captures the functionality to support the OMS/RCS cockpit meter
* test by applying values to the RCS oxidizer, fuel and lowest function 
* designators and checking the corresponding measurements on the orbiter flight
* deck. 
*/
//-----------------------------------------------------------------------------
class OMS_CockpitMeterTest : public OMS_Object 
{

   RTC_DECL_CLASS(OMS_CockpitMeterTest);

   //--------------------------------------------------------------------------
   /**
   * Set frcsOxidQty FD to operator input. 
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( applyFrcsOxid ),
              PARMS1( const Float32_t, pctQty ),
              NEVER_REJECT );

   //--------------------------------------------------------------------------
   /**
   * Set frcsFuelQty FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( applyFrcsFuel ),
              PARMS1( const Float32_t, pctQty ),
              NEVER_REJECT );

   //--------------------------------------------------------------------------
   /**
   * Set frcsLowest FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( applyFrcsLowest ),
              PARMS1( const Float32_t, pctQty ),
              NEVER_REJECT );

   //--------------------------------------------------------------------------
   /**
   * Set lrcsOxidQty FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( applyLrcsOxid ),
              PARMS1( const Float32_t, pctQty ),
              NEVER_REJECT );

   //--------------------------------------------------------------------------
   /**
   * Set lrcsFuelQty FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( applyLrcsFuel ),
              PARMS1( const Float32_t, pctQty ),
              NEVER_REJECT );

   //--------------------------------------------------------------------------
   /**
   * Set lrcsLowest FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( applyLrcsLowest ),
              PARMS1( const Float32_t, pctQty ),
              NEVER_REJECT );

   //--------------------------------------------------------------------------
   /**
   * Set rrcsOxidQty FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( applyRrcsOxid ),
              PARMS1( const Float32_t, pctQty ),
              NEVER_REJECT );

   //--------------------------------------------------------------------------
   /**
   * Set rrcsFuelQty FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( applyRrcsFuel ),
              PARMS1( const Float32_t, pctQty ),
              NEVER_REJECT );


   //--------------------------------------------------------------------------
   /**
   * Set rrcsLowest FD to operator input.
   * 
   * @param pctQty Operator supplied quantity, ranging from 0 to 100 percent.
   */
   //--------------------------------------------------------------------------
   RTC_PROXY( RETURNS_VOID,
              NAME( applyRrcsLowest ),
              PARMS1( const Float32_t, pctQty ),
              NEVER_REJECT );


public:

   //--------------------------------------------------------------------------
   /**
   * OMS_CockpitMeterTest
   *
   * @param rParentPath  specifies the path of the parent object that this 
   *                     object is an aggregate of.
   * @param rIdentifier  specifies an id which is concatenated to the 
   *                     rParentPath to form a unique path for this object. 
   *                     The path is used to retrieve instance data 
   *                     from the Instance Map. 
   */   
   //--------------------------------------------------------------------------
   OMS_CockpitMeterTest( const RTC_String& rParentPath, 
                         const RTC_String& rIdentifier );
   
   //--------------------------------------------------------------------------
   /**
   * OMS_CockpitMeterTest destructor
   */
   //--------------------------------------------------------------------------
   virtual ~OMS_CockpitMeterTest();

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
   * FRCS oxidizer propellant quantity.  Valid range is 0 - 100%. 
   */
   RTC_FD* pFrcsOxidQty_;
   
   /**
   * FRCS fuel propellant quantity.  Valid range is 0 - 100%.
   */
   RTC_FD* pFrcsFuelQty_;
   
   /**
   * FRCS lowest propellant quantity.  Valid range is 0 - 100%.
   */
   RTC_FD* pFrcsLowest_;

   /**
   * LRCS oxidizer propellant quantity.  Valid range is 0 - 100%.
   */
   RTC_FD* pLrcsOxidQty_;
   
   /**
   * LRCS fuel propellant quantity.  Valid range is 0 - 100%.
   */
   RTC_FD* pLrcsFuelQty_;
   
   /**
   * LRCS lowest propellant quantity.  Valid range is 0 - 100%.
   */
   RTC_FD* pLrcsLowest_;

   /**
   * RRCS oxidizer propellant quantity.  Valid range is 0 - 100%.
   */
   RTC_FD* pRrcsOxidQty_;
   
   /**
   * RRCS fuel propellant quantity.  Valid range is 0 - 100%.
   */
   RTC_FD* pRrcsFuelQty_;
   
   /**
   * RRCS lowest propellant quantity.  Valid range is 0 - 100%.
   */
   RTC_FD* pRrcsLowest_;
};

#endif // OMS_COCKPITMETERTEST_H
