//=============================================================================
//
// NAME: OMS_NoCmdNoVpiValve 
//
// OVERVIEW: Class object providing functionality for the NoCmdNoVpiValve
//           (Quick Disconnects)
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_NoCmdNoVpiValve.h"

//=============================================================================
//                     Class Member Definitions
//=============================================================================

RTC_IMPL_CLASS(OMS_NoCmdNoVpiValve);



//-------------------------------------------------------------------------
/**
*
* OMS_NoCmdNoVpiValve constructor implementation.
*
*/
//-------------------------------------------------------------------------
OMS_NoCmdNoVpiValve::OMS_NoCmdNoVpiValve(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier,
   OMS::QdType_t qdType): 
   OMS_Object(rParentPath,
              rIdentifier),
   qdType_(qdType),
   RTC_INIT_ATTR(pState_),
   RTC_IMPL_ATTRIBUTE_DEF(persistentState_, 
                          state, 
                          OMS_OPF_QD_ENUM::NOT_INSTALLED)
{
   RTC_TRACE_CTOR_ENTRY;

   RTC_TRACE_CTOR_EXIT;
  
} // end OMS_NoCmdNoVpiValve::OMS_NoCmdNoVpiValve



//-------------------------------------------------------------------------
/**
*
* OMS_NoCmdNoVpiValve destructor implementation.
*
*/
//-------------------------------------------------------------------------
OMS_NoCmdNoVpiValve::~OMS_NoCmdNoVpiValve()
{
   RTC_TRACE_DTOR_ENTRY;

   RTC_TRACE_DTOR_EXIT;

} // end OMS_NoCmdNoVpiValve::~OMS_NoCmdNoVpiValve



//-------------------------------------------------------------------------
/**
*
* OMS_NoCmdNoVpiValve initialize implementation.
*
* NOTES: None.
*
*/
//-------------------------------------------------------------------------
bool OMS_NoCmdNoVpiValve::initialize()
{
   RTC_TRACE_ENTRY(initialize);

   // Initialize persistence for OMS_NoCmdNoVpiValve
   initializePersistence();

   // Set pseudo health good
   setPseudoHealthGood(pState_, "state", persistentState_);

   // return initialize from the parent object
   return OMS_Object::initialize();

   RTC_TRACE_EXIT;

} // end OMS_NoCmdNoVpiValve::initialize



//-------------------------------------------------------------------------
/**
* 
* setState - Set the state to the operator selected state.
* 
*/
//-------------------------------------------------------------------------
void RTC_IMPL( OMS_NoCmdNoVpiValve::setState ) 
   (OMS_OPF_QD_ENUM::OMS_OPF_QD_ENUM_t state)
{   
   RTC_TRACE_ENTRY(setState);

   // Set the state of the FD
   Set(pState_, state);
   
   // Record the state in the persistent member attribute
   persistentState_ = state;

   RTC_TRACE_EXIT;
      
} // end OMS_NoCmdNoVpiValve::setState



//-------------------------------------------------------------------------
/**
*
* listMethods - This method adds class methods to the methods
* list to be displayed by the TADD. The different types of quick 
* disconnects require different lists of methods.
*
*/
//-------------------------------------------------------------------------
void OMS_NoCmdNoVpiValve::listMethods(
   RTC_IPCInterface::DisplayObj::List_t& rMethods) 
{

   // Determine type of NoCmdNoVpiValve, and list methods based
   // on its type.
   switch(qdType_)
   {
      case OMS::TEST_POINT:
         rMethods.addField("notInstalled");
         rMethods.addField("notMated");
         rMethods.addField("matedToVehOpen");
         break;
         
      case OMS::TEST_PORT:
         rMethods.addField("notInstalled");
         rMethods.addField("matedToVehOpen");
         break;
         
      case OMS::FAIRCHILD_HELIUM:
         rMethods.addField("notInstalled");
         rMethods.addField("notMated");
         rMethods.addField("matedToGseOpen");
         rMethods.addField("matedToVehClosed");
         rMethods.addField("matedToVehOpen");
         break;
         
      case OMS::FAIRCHILD_PROP:
         rMethods.addField("notInstalled");
         rMethods.addField("notMated");
         rMethods.addField("matedToGseOpen");
         rMethods.addField("matedToVehClosed");
         rMethods.addField("matedToVehPurge");
         rMethods.addField("matedToVehOpen");
         break;

      default:
         RTC_TRACE_METHOD(
            listMethods,
            "Quick Disconnect is of an invalid qdType.",
            RTC_Log::TRACE_ERROR);
         
   }
   
} // end OMS_NoCmdNoVpiValve::listMethods



//-------------------------------------------------------------------------
/**
* createIPCInterface instantiates an interprocess communication interface.
*
* This method is called from this base class to instantiate an
* interprocess communication interface for the object during 
* initialization.
*
*/
//-------------------------------------------------------------------------
RTC_IPCMan::ObjInterface_t OMS_NoCmdNoVpiValve::createIPCInterface( )
{
   OMS_IPCIF_NoCmdNoVpiValve* pIpcIf;
   RTC_NEW( pIpcIf, OMS_IPCIF_NoCmdNoVpiValve( *this ) );
   
   return pIpcIf;
} // end createIPCInterface



//-------------------------------------------------------------------------
/**
* terminate - This method calls the parent class method, and stops change
* data on the analog and offset FDs.
*
*/
//-------------------------------------------------------------------------
void OMS_NoCmdNoVpiValve::terminate( )
{
   RTC_TRACE_ENTRY(terminate);

   // Call parent method
   OMS_Object::terminate();

   // Set pseudo health to Inactive
   setPseudoHealthInactive(pState_, "state");

   RTC_TRACE_EXIT;

} // end OMS_NoCmdNoVpiValve::terminate
