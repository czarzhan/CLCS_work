//=============================================================================
//
// NAME: OMS_ManifoldLeg
//
// OVERVIEW: This class represents the components that provide the propellant
//           path from the tank isolation valves to the manifold isolation 
//           valves for the forward reaction control thrusters.  There are two
//           types of manifold legs designated 1/2 Manifold Leg and 3/4/5 
//           Manifold Leg for each of the fuel and oxidizer system.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_MANIFOLDLEG_H
#define OMS_MANIFOLDLEG_H
 
//=============================================================================
//                      System Include Files
//=============================================================================
#include <RTC_Event.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_VehiclePlumbing.h"

//=============================================================================
//                      Class Declarations
//=============================================================================

//-------------------------------------------------------------------------
/**
* This class represents the components that provide the propellant path from
* the tank isolation valves to the manifold isolation valves.
*/
//-------------------------------------------------------------------------
class OMS_ManifoldLeg : public OMS_VehiclePlumbing 
{

   RTC_DECL_CLASS(OMS_ManifoldLeg);

   //-------------------------------------------------------------------------
   /**
   * The manifoldLeg pressure is calculated upon changes in any of the
   * following:
   * propTankPressure,tkIsoValveAState, manifoldAPressure, manifoldBPressure,
   * manifoldIsoAState, or manifoldIsoBState.
   */
   //-------------------------------------------------------------------------
   RTC_EVENT_HANDLER (NAME(calcPressure),
                      PARMS1(const RTC_Event::FDInfo_t, FDs));

public:
   //-------------------------------------------------------------------------
   /**
   * OMS_ManifoldLeg
   *
   * @param rParentPath   specifies the path of the parent object that this 
   *                      object is an aggregate of.
   * @param rIdentifier   specifies an id which is concatenated to the 
   *                      rParentPath to form a unique path for this object. 
   *                      The path is used to retrieve instance data 
   *                      from the Instance Map. 
   */
   //-------------------------------------------------------------------------
   OMS_ManifoldLeg(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier);
   
   //-------------------------------------------------------------------------
   /**
   * OMS_ManifoldLeg destructor
   */
   //-------------------------------------------------------------------------
   virtual ~OMS_ManifoldLeg();

   //-------------------------------------------------------------------------
   /**
   * initialize - Registers calcPressure, and calls the parent class.
   * 
   * @return bool Results of a call to the parent class
   */
   //-------------------------------------------------------------------------
   virtual bool initialize();


   //-------------------------------------------------------------------------
   /**
   * terminate - Calls the parent class and deactivates the pseudo health.
   */
   //-------------------------------------------------------------------------
   virtual void terminate();
   
protected:

   //-------------------------------------------------------------------------
   /**
   * pressureCalcFDs - returns list of FDs which are used in calcPressure.
   *
   * @return RTC_list - the list containing the pressure FDs.
   */   
   //-------------------------------------------------------------------------
   virtual RTC_FDS::FDList_t pressureCalcFDs() const;

   
   /**
   * Pointer to the offsetCorrectedPressure pseudo of the Manifold Leg
   */
   RTC_FD* pOffsetCorrectedPressure_;

   /**
   * RCS Propellant Tank Pressure used in calculating the plumbing pressure.
   * @supplierCardinality 1 
   */
   RTC_FD* pPropTankPressureRO_;
   
   /**
   * Isolation valve state for the valve between the manifoldleg and the tank
   * used in calculating the plumbing pressure.
   * @supplierCardinality 1 
   */
   RTC_FD* pTkIsoValveAStateRO_;
   
   /**
   * Primary Manifold A Pressure used in calculating the plumbing pressure.
   * @supplierCardinality 1 
   */
   RTC_FD* pManifoldAPressureRO_;
   
   /**
   * Primary Manifold B Pressure used in calculating the plumbing pressure.
   * @supplierCardinality 1 
   */
   RTC_FD* pManifoldBPressureRO_;
   
   /**
   * Isolation valve state for the valve between the manifoldLeg and the first
   * two manifolds used in calculating the plumbing pressure. 
   */
   RTC_FD* pManifoldIsoAStateRO_;
   
   /**
   * Isolation valve state for the valve between the manifoldLeg and the second
   * two manifolds used in calculating the plumbing pressure. 
   */
   RTC_FD* pManifoldIsoBStateRO_;
   
};
#endif //OMS_MANIFOLDLEG_H
