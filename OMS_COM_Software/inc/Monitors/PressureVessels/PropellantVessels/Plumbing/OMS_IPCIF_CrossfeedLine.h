//=============================================================================
//
// NAME: OMS_IPCIF_CrossfeedLine
//
// OVERVIEW: This is the IPC interface used to bind a reference of the 
//           OMS_CrossfeedLine class.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================
#ifndef OMS_IPCIF_CROSSFEEDLINE_H
#define OMS_IPCIF_CROSSFEEDLINE_H
 
//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_VehiclePlumbing.h"


//-----------------------------------------------------------------------------
/**
* Forward declaration of the component class
*/
//-----------------------------------------------------------------------------
class OMS_CrossfeedLine;

//-----------------------------------------------------------------------------
/**
* OMS_IPCIF_CrossfeedLine - This is the IPC interface used to bind a 
* reference of the OMS_CrossfeedLine class.
*
* @interface 
*/
//-----------------------------------------------------------------------------
class OMS_IPCIF_CrossfeedLine : 
   public OMS_IPCIF_VehiclePlumbing, 
   public virtual POA_OMS_Plumbing_ObjAdaptor::CrossfeedLine
{
public:  

   //--------------------------------------------------------------------
   /**
   * OMS_IPCIF_CrossfeedLine - This is the IPC constructor used to bind
   * to a reference of the OMS_CrossfeedLine class
   * 
   * @param rImpl A reference to the OMS_CrossfeedLine instance which
   *              implements the interface methods.
   */
   //--------------------------------------------------------------------
   OMS_IPCIF_CrossfeedLine(OMS_CrossfeedLine& rImpl);

   //--------------------------------------------------------------------
   /**
   * IPC Interface destructor
   */
   //--------------------------------------------------------------------
   ~OMS_IPCIF_CrossfeedLine();

   //--------------------------------------------------------------------
   /**
   * toggleLeftFlangeState - Invokes the toggleLeftFlangeState method in
   * the OMS_CrossfeedLine class.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------
   virtual CORBA::Long toggleLeftFlangeState();

   //--------------------------------------------------------------------
   /**
   * toggleLeftFlangeState - Invokes the toggleRightFlangeState method in
   * the OMS_CrossfeedLine class.
   * 
   * @return OMS::PASS
   */
   //--------------------------------------------------------------------
   virtual CORBA::Long toggleRightFlangeState();

private:    

   /** @link dependency 
   * @stereotype use*/
   OMS_CrossfeedLine& rImpl_;
};

#endif // OMS_IPCIF_CROSSFEEDLINE_H
