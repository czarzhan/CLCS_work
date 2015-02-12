//=============================================================================
//
// NAME: OMS_OmsFeedline
//
// OVERVIEW: The OMS Feedlines are the plumbing between the tank isolation 
//           valves and the OMS engine flange. Each oxidizer feedline is 
//           instrumented with a single temperature sensor.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_OMSFEEDLINE_H
#define OMS_OMSFEEDLINE_H

//=============================================================================
//                      System Include Files
//=============================================================================
#include <RTC_Event.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_VehiclePlumbing.h"
#include "OMS_AnalogWithLccLimits.h"

//-----------------------------------------------------------------------------
/**
* The OMS Feedlines are the plumbing between the tank isolation valves and the
* OMS engine flange. Each oxidizer feedline is instrumented with a single
* temperature sensor. 
*/
//-----------------------------------------------------------------------------
class OMS_OmsFeedline : public OMS_VehiclePlumbing 
{

   RTC_DECL_CLASS(OMS_OmsFeedline);

   //--------------------------------------------------------------------------
   /**
   * The omsFeedline pressure is calculated upon changes in any of the 
   * following: propTankPressure,tkIsoValveAState, tkIsoValveBState,
   * xfdIsoValveAState, xfdIsoValveBState, omeFlangeState, and 
   * xfdLinePressure.
   * 
   * @param FDs - function designators that pressure is based on:
   *              pPropTankPressureRO_
   *              pTkIsoValveAStateRO_
   *              pTkIsoValveBStateRO_
   *              pXfdIsoValveAStateRO_
   *              pXfdIsoValveBStateRO_
   *              pOmeFlangeStateRO_
   *              pXfdLinePressureRO_
   * @return void
   */
   //--------------------------------------------------------------------------
   RTC_EVENT_HANDLER (NAME(calcPressure),
                      PARMS1(const RTC_Event::FDInfo_t, FDs));
    
public:
   //--------------------------------------------------------------------------
   /**
   * OMS_OmsFeedline
   *
   * @param rParentPath   specifies the path of the parent object that this 
   *                      object is an aggregate of.
   * @param rIdentifier   specifies an id which is concatenated to the 
   *                      rParentPath to form a unique path for this object. 
   *                      The path is used to retrieve instance data 
   *                      from the Instance Map. 
   * @param commodityType defines whether the component is for FUEL or OXID
   */
   //--------------------------------------------------------------------------
   OMS_OmsFeedline(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier,
      OMS::Commodity_t commodityType);
   
   //--------------------------------------------------------------------------
   /**
   * OMS_OmsFeedline destructor
   */
   //--------------------------------------------------------------------------
   virtual ~OMS_OmsFeedline();


   //--------------------------------------------------------------------------
   /**
   * initialize - This method initializes feedline, registers calcPressure,
   *              and calls the parent class method.
   *
   * @return bool - Results of call to parent class method.
   */
   //--------------------------------------------------------------------------
   virtual bool initialize();


   //--------------------------------------------------------------------------
   /**
   * terminate - This method calls the parent class method, and deregisters
   *             calcPressure.
   */
   //--------------------------------------------------------------------------
   virtual void terminate();

private:

   /**
   * Feedline temperature measurement:  Oxidizer Instances Only.
   * @link aggregationByValue
   * @supplierCardinality 0,1
   */
   OMS_AnalogWithLccLimits* pTemperature_;
   
   /**
   * Pointer to the offsetCorrectedPressure pseudo of the Feedline.
   */
   RTC_FD* pOffsetCorrectedPressure_;

   /**
   * RCS Propellant Tank Pressure used in calculating the plumbing pressure.
   * @supplierCardinality 1 
   */
   RTC_FD* pPropTankPressureRO_;
   
   /**
   * Isolation valve state for the valve between the OmsFeedline and the tank
   * used in calculating the plumbing pressure.
   * @supplierCardinality 1 
   */
   RTC_FD* pTkIsoValveAStateRO_;
   
   /**
   * The parallel isolation valve state for the valve between the OmsFeedline
   * and the tank used in calculating the plumbing pressure.
   * @supplierCardinality 1 
   */
   RTC_FD* pTkIsoValveBStateRO_;
   
   /**
   * CrossfeedLine Pressure used in calculating the plumbing pressure.
   * @supplierCardinality 1 
   */
   RTC_FD* pXfdLinePressureRO_;
   
   /**
   * Isolation valve state for the valve between the OmsFeedline and the
   * crossfeedLine used in calculating the plumbing pressure.
   * @supplierCardinality 1 
   */
   RTC_FD* pXfdIsoValveAStateRO_;

   /**
   * The parallel isolation valve state for the valve between the OmsFeedline
   * and the crossfeedLine used in calculating the plumbing pressure.
   * @supplierCardinality 1 
   */
   RTC_FD* pXfdIsoValveBStateRO_;
   
   /** The OMS Engine flange state used in calculating the plumbing pressure.
   * @supplierCardinality 1
   */
   RTC_FD* pOmeFlangeStateRO_;
   
   /**
   * OmeInletLine Pressure used in calculating the plumbing pressure.
   * @supplierCardinality 1 
   */
   RTC_FD* pOmeInletLinePressureRO_;

};

#endif // OMS_OMSFEEDLINE_H
