//=============================================================================
//
// NAME: OMS_IPCIF_OpfFlowMeterDeltaP
//
// OVERVIEW: Provides all IPC interfaces for OMS_OpfFlowMeterDeltaP.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_IPCIF_OPFFLOWMETERDELTAP_H
#define OMS_IPCIF_OPFFLOWMETERDELTAP_H

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_Object.h"
#include "OMS_Flowmeter_ObjAdaptor_s.hh"

//-----------------------------------------------------------------------------
/**
* Forward declaration of the component class.
*/
//-----------------------------------------------------------------------------
class OMS_OpfFlowMeterDeltaP;

//-----------------------------------------------------------------------------
/**
* Provides all IPC interfaces for OMS_OpfFlowMeterDeltaP.
* 
* @interface 
*/
//-----------------------------------------------------------------------------
class OMS_IPCIF_OpfFlowMeterDeltaP:
   public OMS_IPCIF_Object,
   public virtual POA_OMS_Flowmeter_ObjAdaptor::OpfFlowMeterDeltaP
{
public:   
   //--------------------------------------------------------------------------
   /**
   * OMS_IPCIF_OpfFlowMeterDeltaP - This is the IPC interface constructor
   * used to bind to a reference of the OMS_OpfFlowMeterDeltaP class.
   *
   * @param rImpl A reference to the OMS_OpfFlowMeterDeltaP instance which
   *              implements the interface methods.
   */
   //--------------------------------------------------------------------------
   OMS_IPCIF_OpfFlowMeterDeltaP(OMS_OpfFlowMeterDeltaP& rImpl);
   


   //--------------------------------------------------------------------------
   /**
   * IPC Interface destructor
   */ 
   //--------------------------------------------------------------------------
   virtual ~OMS_IPCIF_OpfFlowMeterDeltaP();
   


   //--------------------------------------------------------------------------
   /**
   * changeMode - Invokes the changeMode method of the 
   * OMS_OpfFlowMeterDeltaP implementation. 
   * 
   * @return OMS::PASS.
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long changeMode();


   
   //--------------------------------------------------------------------------
   /**
   * startHighRate - Invokes the startHighRate method of the 
   * OMS_OpfFlowMeterDeltaP implementation. 
   * 
   * @return OMS::PASS.
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long startHighRate();


   
   //--------------------------------------------------------------------------
   /**
   * stopHighRate - Invokes the stopHighRate method of the 
   * OMS_OpfFlowMeterDeltaP implementation. 
   * 
   * @return OMS::PASS.
   */
   //--------------------------------------------------------------------------
   virtual CORBA::Long stopHighRate();

protected:

   //--------------------------------------------------------------------------
   /**
   * listAttributes - Invokes the listAttributes method of the 
   * OMS_OpfFlowMeterDeltaP implementation.
   *
   * @param   rAttributes - A reference to the attributes list
   * @return void
   */
   //--------------------------------------------------------------------------
   virtual void listAttributes(List_t& rAttributes) ;

private:   

   /** @link dependency 
     * @stereotype use*/
   /* 
   * The instance of OMS_OpfFlowMeterDeltaP.
   */
   OMS_OpfFlowMeterDeltaP& rImpl_;
};

#endif  // OMS_IPCIF_OPFFLOWMETERDELTAP_H
