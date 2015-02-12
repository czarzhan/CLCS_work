//=============================================================================
//
// NAME: OMS_PrimaryManifold
//
// OVERVIEW: The Primary Manifolds consist of plumbing between the manifold
//           isolation valves and the primary RCS thrusters. They are 
//           instrumented with a single analog pressure sensor.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_PRIMARYMANIFOLD_H
#define OMS_PRIMARYMANIFOLD_H
 
//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_AnalogWith3OffsetsDefAndLccLimits.h"
#include "OMS_VehiclePlumbing.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================
//----------------------------------------------------------------------------
/**
* The Primary Manifolds consist of plumbing between the manifold isolation 
* valves and the primary RCS thrusters. They are instrumented with a single 
* analog pressure sensor.
*/
//----------------------------------------------------------------------------
class OMS_PrimaryManifold : public OMS_VehiclePlumbing 
{

   RTC_DECL_CLASS(OMS_PrimaryManifold);

public:
   //-------------------------------------------------------------------------
   /**
   * OMS_PrimaryManifold
   *
   * @param rParentPath   specifies the path of the parent object that this 
   *                      object is an aggregate of.
   * @param rIdentifier   specifies an id which is concatenated to the 
   *                      rParentPath to form a unique path for this object. 
   *                      The path is used to retrieve instance data 
   *                      from the Instance Map. 
   * @param commodityType defines whether the component is for FUEL or OXID
   */
   //-------------------------------------------------------------------------
   OMS_PrimaryManifold(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier,
      bool initToValid = true);

   //-------------------------------------------------------------------------
   /**
   * OMS_PrimaryManifold destructor
   */
   //-------------------------------------------------------------------------
   virtual ~OMS_PrimaryManifold();


protected:

   /**
   * Primary Manifold Pressure 
   * @link aggregationByValue
   * @supplierCardinality 1
   */
   OMS_AnalogWith3OffsetsDefAndLccLimits* pPressure_;

};
#endif // OMS_PRIMARYMANIFOLD_H
