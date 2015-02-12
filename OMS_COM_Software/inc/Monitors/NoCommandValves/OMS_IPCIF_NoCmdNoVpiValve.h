//=============================================================================
//
// NAME: OMS_IPCIF_NoCmdNoVpivalve
//
// OVERVIEW: Provides all IPC interfaces for OMS_NoCmdNoVpivalve.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_IPCIF_NOCMDNOVPIVALVE_H
#define OMS_IPCIF_NOCMDNOVPIVALVE_H

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_Object.h"
#include "OMS_NoCmdNoVpiValve.h"
#include "OMS_NoCommandValves_ObjAdaptor_s.hh"


//-----------------------------------------------------------------------------
/** 
* OMS_IPCIF_NoCmdNoVpiValve - This is the IPC interface used to bind to 
* a reference of the OMS_NoCmdNoVpiValve class.
* 
* @interface 
*/
//-----------------------------------------------------------------------------
class OMS_IPCIF_NoCmdNoVpiValve:
   public OMS_IPCIF_Object,
   public virtual POA_OMS_NoCommandValves_ObjAdaptor::NoCmdNoVpiValve
{
public:    
   //--------------------------------------------------------------------
   /**
   * OMS_IPCIF_NoCmdNoVpiValve - This is the IPC interface constructor
   * used to bind to a reference of the OMS_NoCmdNoVpiValve class.
   *
   * @param rImpl A reference to the OMS_NoCmdNoVpiValve instance which
   *              implements the interface methods.
   */
   //--------------------------------------------------------------------
   OMS_IPCIF_NoCmdNoVpiValve (OMS_NoCmdNoVpiValve& rImpl);   
 


   //--------------------------------------------------------------------
   /**
   * IPC Interface destructor
   */
   //--------------------------------------------------------------------
   ~OMS_IPCIF_NoCmdNoVpiValve();



   //--------------------------------------------------------------------
   /**
   * notInstalled - Invokes the setState function of the 
   * OMS_NoCmdNoVpiValve to set the QD state to NOT_INSTALLED
   *
   * @return OMS::PASS.
   */
   //--------------------------------------------------------------------
   virtual CORBA::Long notInstalled();
 


   //--------------------------------------------------------------------
   /**
   * notMated - Invokes the setState function of the 
   * OMS_NoCmdNoVpiValve to set the QD state to NOT_MATED
   *
   * @return OMS::PASS.
   */
   //--------------------------------------------------------------------
   virtual CORBA::Long notMated();
 


   //--------------------------------------------------------------------
   /**
   * matedToGseOpen - Invokes the setState function of the 
   * OMS_NoCmdNoVpiValve to set the QD state to MATED_TO_GSE_OPEN
   *
   * @return OMS::PASS.
   */
   //--------------------------------------------------------------------
   virtual CORBA::Long matedToGseOpen();
 


   //--------------------------------------------------------------------
   /**
   * matedToVehClosed - Invokes the setState function of the 
   * OMS_NoCmdNoVpiValve to set the QD state to MATED_TO_VEH_CLOSED
   *
   * @return OMS::PASS.
   */
   //--------------------------------------------------------------------
   virtual CORBA::Long matedToVehClosed();
 


   //--------------------------------------------------------------------
   /**
   * matedToVehPurge - Invokes the setState function of the 
   * OMS_NoCmdNoVpiValve to set the QD state to MATED_TO_VEH_PURGE
   *
   * @return OMS::PASS.
   */
   //--------------------------------------------------------------------
   virtual CORBA::Long matedToVehPurge();
 


   //--------------------------------------------------------------------
   /**
   * matedToVehOpen - Invokes the setState function of the 
   * OMS_NoCmdNoVpiValve to set the QD state to MATED_TO_VEH_OPEN
   *
   * @return OMS::PASS.
   */
   //--------------------------------------------------------------------
   virtual CORBA::Long matedToVehOpen();

   
private:

   /** @link dependency 
     * @stereotype use*/
   /**
   * The instance of OMS_NoCmdNoVpiValve or a derived class
   */
   OMS_NoCmdNoVpiValve& rImpl_;
   

};  


#endif  //OMS_IPCIF_NOCMDNOVPIVALVE_H
