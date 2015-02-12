//=============================================================================
//
// NAME: OMS_ArcsManifoldLeg
//
// OVERVIEW: The manifold legs provide a propellant path from the tank 
//           isolation valves to the manifold isolation valves.  There are two
//           types of manifold legs designated 1/2 Manifold Leg and 3/4/5 
//           Manifold Leg for each of the fuel and oxidizer system.  The only
//           addition based on the manifoldLegType is the addition of a second
//           tkIsoValveState.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_ARCSMANIFOLDLEG_H
#define OMS_ARCSMANIFOLDLEG_H
 
//=============================================================================
//                      System Include Files
//=============================================================================
#include "OMS_ManifoldLeg.h"

//=============================================================================
//                      Class Declarations
//=============================================================================
//----------------------------------------------------------------------------
/**
* The manifold legs provide a propellant path from the tank isolation valves
* to the manifold isolation valves.  There are two types of manifold legs
* designated 1/2 Manifold Leg and 3/4/5 Manifold Leg for each of the fuel and
* oxidizer systems.  The only addition based on the manifoldLegType is the
* addition of a second tkIsoValveState.
*/
//----------------------------------------------------------------------------
class OMS_ArcsManifoldLeg : public OMS_ManifoldLeg 
{

   RTC_DECL_CLASS(OMS_ArcsManifoldLeg);

   //-------------------------------------------------------------------------
   /**
   * The ArcsManifoldLeg pressure is calculated upon changes in any of the
   * following:
   * propTankPressure,tkIsoValveAState, tkIsoValveBState, manifoldAPressure,
   * manifoldBPressure, manifoldIsoAState, manifoldIsoBState, xfdIsoValveState,
   * and xfdLinePressure.
   */
   //-------------------------------------------------------------------------
   void RTC_IMPL(calcPressure) (const RTC_Event::FDInfo_t FDs);

public:
   //-------------------------------------------------------------------------
   /**
   * OMS_ManifoldLeg constructor for the 3/4/5 manifold legs
   *
   * @param rParentPath     specifies the path of the parent object that this 
   *                        object is an aggregate of.
   * @param rIdentifier     specifies an id which is concatenated to the 
   *                        rParentPath to form a unique path for this object. 
   *                        The path is used to retrieve instance data 
   *                        from the Instance Map. 
   * @param manifoldLegType defines whether the component is a OMS_12_LEG
   *                        or a OMS_345_LEG. In the case of this constructor,
   *                        only the 3/4/5 legs will be initialized. 1/2 legs
   *                        will use the constructor without this parameter.
   */
   //-------------------------------------------------------------------------
   OMS_ArcsManifoldLeg(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier,
      OMS::ManifoldLeg_t manifoldLegType );

   //-------------------------------------------------------------------------
   /**
   * OMS_ManifoldLeg constructor for the 1/2 manifold legs
   *
   * @param rParentPath     specifies the path of the parent object that this 
   *                        object is an aggregate of.
   * @param rIdentifier     specifies an id which is concatenated to the 
   *                        rParentPath to form a unique path for this object. 
   *                        The path is used to retrieve instance data 
   *                        from the Instance Map. 
   */
   //-------------------------------------------------------------------------
   OMS_ArcsManifoldLeg(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier );

   //-------------------------------------------------------------------------
   /**
   * OMS_ArcsManifoldLeg destructor
   */
   //-------------------------------------------------------------------------
   virtual ~OMS_ArcsManifoldLeg();

protected:
   //-------------------------------------------------------------------------
   /**
   * pressureCalcFDs - returns list of FDs which are used in calcPressure.
   *
   * @return RTC_list - the singleton list containing the pressure FDs.
   */   
   //-------------------------------------------------------------------------
   virtual RTC_FDS::FDList_t pressureCalcFDs() const;

private:    

   /**
   * Manifold leg type;  Valid values:  OMS_12_LEG and OMS_345_LEG. 
   */
   OMS::ManifoldLeg_t manifoldLegType_;
   
   /**
   * The parallel isolation valve state for the valve between the manifoldleg
   * and the tank used in calculating the plumbing pressure.
   * @supplierCardinality 0, 1 
   */
   RTC_FD* pTkIsoValveBStateRO_;

   /**
   * Isolation valve state for the valve between the manifoldLeg and the
   * crossfeedLine used in calculating the plumbing pressure.
   * @supplierCardinality 1 
   */
   RTC_FD* pXfdIsoValveStateRO_;

   /**
   * CrossfeedLine Pressure used in calculating the plumbing pressure. 
   */
   RTC_FD* pXfdLinePressureRO_;

};

#endif // OMS_ARCSMANIFOLDLEG_H
