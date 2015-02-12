//=============================================================================
//
// NAME: OMS_VernierManifold
//
// OVERVIEW: The Vernier Manifolds provide a propellant path from the manifold
//           isolation valves to the vernier thruster valves. There is one 
//           vernier manifold for each of the fuel and oxidizer legs. These 
//           are identical in function to the primary manifolds except for 
//           the logic used to determine the manifold pressure.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_VERNIERMANIFOLD_H
#define OMS_VERNIERMANIFOLD_H
 
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


//----------------------------------------------------------------------------
/**
* The Vernier Manifolds provide a propellant path from the manifold isolation
* valves to the vernier thruster valves. There is one vernier manifold for 
* each of the fuel and oxidizer legs. These are identical in function to the
* primary manifolds except for the logic used to determine the manifold 
* pressure.
*/
//----------------------------------------------------------------------------
class OMS_VernierManifold : public OMS_VehiclePlumbing 
{
   RTC_DECL_CLASS(OMS_VernierManifold);

   //-------------------------------------------------------------------------
   /**
   * calcPressure - calculated upon changes in any of the following:
   * pManifoldLegPressure_ or the pManifoldIsoState_ (of the valve).
   * 
   * @param FDs - function designators that pressure is based on:
   *              pManifoldLegPressureRO_
   *              pManifoldIsoStateRO_ (of the valve)
   */
   //-------------------------------------------------------------------------
   RTC_EVENT_HANDLER ( NAME( calcPressure ),
                       PARMS1( const RTC_Event::FDInfo_t, FDs ) );

public:
   //-------------------------------------------------------------------------
   /**
   * OMS_VernierManifold constructor
   *
   * @param rParentPath  specifies the path of the parent object that this 
   *                     object is an aggregate of.
   * @param rIdentifier  specifies an id which is concatenated to the 
   *                     rParentPath to form a unique path for this object. 
   *                     The path is used to retrieve instance data 
   *                     from the Instance Map. 
   */
   //-------------------------------------------------------------------------
   OMS_VernierManifold(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier );
   
   
   //-------------------------------------------------------------------------
   /**
   * OMS_VernierManifold destructor
   */
   //-------------------------------------------------------------------------
   virtual ~OMS_VernierManifold();
   
   
   //--------------------------------------------------------------------------
   /**
   * initialize - This method initializes the manifold, registers calcPressure,
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
   * Pointer to the offsetCorrectedPressure pseudo of the respective plumbing
   * piece.
   */
   RTC_FD* pOffsetCorrectedPressure_;
   
   /**
   * Isolation valve between the vernier manifold and the manifoldLeg used in
   * calculating the plumbing pressure. 
   */
   RTC_FD* pManifoldIsoStateRO_;
   
   /**
   * ManifoldLeg Pressure used in calculating the plumbing pressure.
   * @link association
   * @supplierCardinality 1 
   */
   RTC_FD* pManifoldLegPressureRO_;
};

#endif // OMS_VERNIERMANIFOLD_H
