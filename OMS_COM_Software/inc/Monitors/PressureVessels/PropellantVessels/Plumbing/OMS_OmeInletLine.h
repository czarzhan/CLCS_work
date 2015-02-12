//=============================================================================
//
// NAME: OMS_OmeInletLine
//
// OVERVIEW: The OME Inlet Lines are the plumbing between the feedlines and the
//           OMS engine ball valves. Each inlet line is instrumented with an
//           analog pressure sensor (inherited from the OMS_PrimaryManifold
//           class). In addition, the fuel inlet lines have a temperature 
//           sensor.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_OMEINLETLINE_H
#define OMS_OMEINLETLINE_H
 
//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_AnalogWithLccLimits.h"
#include "OMS_PrimaryManifold.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================
//----------------------------------------------------------------------------
/**
* The OME Inlet Lines are the plumbing between the feedlines and the OMS engine
* ball valves. Each inlet line is instrumented with an analog pressure sensor
* (inherited from the OMS_PrimaryManifold class). In addition, the fuel inlet
* lines have a temperature sensor.
*/
//----------------------------------------------------------------------------
class OMS_OmeInletLine : public OMS_PrimaryManifold 
{
   
   RTC_DECL_CLASS(OMS_OmeInletLine);
   
   //-------------------------------------------------------------------------
   /**
   * setValid calls the setValid method of the aggregate components
   */
   //-------------------------------------------------------------------------
   //void setValid();
   RTC_PROXY(RETURNS_VOID,
             NAME(setValid),
             NO_PARMS,
             NEVER_REJECT);
   
   //-------------------------------------------------------------------------
   /**
   * setInvalid calls the setInvalid method of the aggregate components
   */
   //-------------------------------------------------------------------------
   //void setInvalid();
   RTC_PROXY(RETURNS_VOID,
             NAME(setInvalid),
             NO_PARMS,
             NEVER_REJECT);
   
public:
   //-------------------------------------------------------------------------
   /**
   * OMS_OmeInletLine constructor
   *
   * @param rParentPath   specifies the path of the parent object that this 
   *                      object is an aggregate of.
   * @param rIdentifier   specifies an id which is concatenated to the 
   *                      rParentPath to form a unique path for this object. 
   *                      The path is used to retrieve instance data 
   *                      from the Instance Map. 
   * @param commodityType defines whether the component is for FUEL or OXID
   * @param initToValid   defines whether data is valid depending on the
   *                      engine mate state.
   */
   //-------------------------------------------------------------------------
   OMS_OmeInletLine(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier,
      OMS::Commodity_t commodityType,
      bool initToValid);
   
   
   //-------------------------------------------------------------------------
   /**
   * OMS_OmeInletLine destructor
   */
   //-------------------------------------------------------------------------
   virtual ~OMS_OmeInletLine();
   
   
private:
   
   /** Inlet temperature of the OmeInlet Line for fuel instances only.
   * @link aggregationByValue
   * @supplierCardinality 0..1*/
   OMS_AnalogWithLccLimits* pInletTemp_;
};
#endif // OMS_OMEINLETLINE_H
