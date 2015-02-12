//=============================================================================
//
// NAME: OMS_IPCIF_VehiclePlumbing
//
// OVERVIEW: Provides IPC interfaces for all OMS_VehiclePlumbing subcomponents.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_IPCIF_VEHICLEPLUMBING_H
#define OMS_IPCIF_VEHICLEPLUMBING_H
 
//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_Object.h"
#include "OMS_Plumbing_ObjAdaptor_s.hh"

//-----------------------------------------------------------------------------
/**
* Forward declaration of the component class
*/
//-----------------------------------------------------------------------------
class OMS_VehiclePlumbing;

//-----------------------------------------------------------------------------
/**
* OMS_IPCIF_VehiclePlumbing - This is the IPC interface used to bind a 
* reference of the OMS_VehiclePlumbing class and its derived classes.
*
* @interface 
*/
//-----------------------------------------------------------------------------
class OMS_IPCIF_VehiclePlumbing:
   public OMS_IPCIF_Object,
   public virtual POA_OMS_Plumbing_ObjAdaptor::VehiclePlumbing
{
public:

   //--------------------------------------------------------------------
   /**
   * OMS_IPCIF_VehiclePlumbing - This is the IPC constructor used to bind
   * to a reference of the OMS_VehiclePlumbing class, and many of its 
   * subclasses.
   * 
   * @param rImpl A reference to the OMS_VehiclePlumbing instance which
   *              implements the interface methods.
   */
   //--------------------------------------------------------------------
   OMS_IPCIF_VehiclePlumbing (OMS_VehiclePlumbing& rImpl);

   //--------------------------------------------------------------------
   /**
   * IPC Interface destructor
   */
   //--------------------------------------------------------------------
   ~OMS_IPCIF_VehiclePlumbing();

   //--------------------------------------------------------------------
   /**
   * toggleContaminationState - Invokes the toggle method of the 
   * OMS_VehiclePlumbing class to rotate its contaminationState to the 
   * next state (FULL, DRAINED, DECONTAMINATED)
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------
   virtual CORBA::Long toggleContaminationState();

private:   

   //--------------------------------------------------------------------
   // TOGETHER LINKS. DO NOT REMOVE
   //--------------------------------------------------------------------
    /** @link dependency 
     * @stereotype use*/
    /*#  OMS_OmsFeedline lnkOMS_OmsFeedLine; */

    /** @link dependency 
     * @stereotype use*/
    /*#  OMS_VernierManifold lnkOMS_VernierManifold; */

    /** @link dependency 
     * @stereotype use*/
    /*#  OMS_PrimaryManifold lnkOMS_PrimaryManifold; */

    /** @link dependency 
     * @stereotype use*/
    /*#  OMS_ArcsManifoldLeg lnkOMS_ArcsManifoldLeg; */

    /** @link dependency 
     * @stereotype use*/
    /*#  OMS_ManifoldLeg lnkOMS_ManifoldLeg; */

   OMS_VehiclePlumbing& rImpl_;
};
#endif // OMS_IPCIF_VEHICLEPLUMBING_H
