//=============================================================================
//
// NAME: OMS_IPCIF_ManualValve
//
// OVERVIEW: Provides all IPC interfaces for OMS_ManualValve.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_IPCIF_MANUALVALVE_H
#define OMS_IPCIF_MANUALVALVE_H

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_Object.h"
#include "OMS_ManualValve.h"
#include "OMS_NoCommandValves_ObjAdaptor_s.hh"

//-----------------------------------------------------------------------------
/**
* OMS_IPCIF_ManualValve - This is the IPC interface used to bind to 
* a reference of the OMS_ManualValve class.
* 
* @interface
*/
//-----------------------------------------------------------------------------
class OMS_IPCIF_ManualValve:
   public OMS_IPCIF_Object,
   public virtual POA_OMS_NoCommandValves_ObjAdaptor::ManualValve
{
public:    

   //--------------------------------------------------------------------
   /**
   * OMS_IPCIF_ManualValve - This is the IPC interface constructor
   * used to bind to a reference of the OMS_ManualValve class.
   *
   * @param rImpl A reference to the OMS_ManualValve instance which
   *              implements the interface methods.
   */
   //--------------------------------------------------------------------
   OMS_IPCIF_ManualValve (OMS_ManualValve& rImpl);

   //--------------------------------------------------------------------
   /**
   * toggle - Invokes the toggle method of the OMS_ManualValve
   *          implementation.
   * 
   * @return OMS::PASS.
   */
   //--------------------------------------------------------------------
   virtual CORBA::Long toggle();

   
private:    

   /** @link dependency 
     * @stereotype use*/
   /**
   * The instance of OMS_ManualValve or a derived class
   */
   OMS_ManualValve& rImpl_;
   

};
#endif  // OMS_IPCIF_MANUALVALVE_H
