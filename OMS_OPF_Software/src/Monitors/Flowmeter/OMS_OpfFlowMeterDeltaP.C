//=============================================================================
//
// NAME: OMS_OpfFlowMeterDeltaP
//
// OVERVIEW: The flowmeter is a device used to measure flow.  The flowmeter is 
//           actually a delta pressure transducer that bridges an orifice. The
//           relationship between the flowrate and the delta pressure is 
//           defined by equations for subsonic and sonic flow conditions. Each
//           OPF flowmeter (30 total) has an experimentally derived curve.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                      System Include Files
//=============================================================================
#include <RTC_AM.h>
#include <math.h>
#include <DELTAP_ENUM.h>
#include <OMS_DELTAP_MODE_ENUM.h>
#include <CAS_OPFBAYTYPE.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_OpfFlowMeterDeltaP.h"
#include "OMS_OpfFlowMeterDeltaP.h"


//=============================================================================
//                     Class Member Definitions
//=============================================================================
RTC_IMPL_CLASS(OMS_OpfFlowMeterDeltaP);


//-----------------------------------------------------------------------------
/**
* OMS_OpfFlowMeterDeltaP constructor
*
* @param rParentPath  specifies the path of the parent object that this 
*                     object is an aggregate of.
* @param rIdentifier  specifies an id which is concatenated to the 
*                     rParentPath to form a unique path for this object. 
*                     The path is used to retrieve instance data 
*                     from the Instance Map. 
*/   
//-----------------------------------------------------------------------------
OMS_OpfFlowMeterDeltaP::OMS_OpfFlowMeterDeltaP(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier ):
   OMS_Object(rParentPath,
              rIdentifier),
   RTC_INIT_ATTR(pMeasurement_),
   RTC_INIT_ATTR(pMode_),
   RTC_INIT_ATTR(pSampleRate_),
   RTC_INIT_ATTR(pOutput_),
   RTC_INIT_ATTR(pOpfTestSite_)
{
   RTC_TRACE_CTOR_ENTRY;

   // Map attributes from numbers listed in the instance table
   constant1_[0] = RTC_MAP_ATTR(constant1_0);
   constant1_[1] = RTC_MAP_ATTR(constant1_1);
   constant1_[2] = RTC_MAP_ATTR(constant1_2);
   constant1_[3] = RTC_MAP_ATTR(constant1_3);
   constant2_[0] = RTC_MAP_ATTR(constant2_0);
   constant2_[1] = RTC_MAP_ATTR(constant2_1);
   constant2_[2] = RTC_MAP_ATTR(constant2_2);
   constant2_[3] = RTC_MAP_ATTR(constant2_3);
   offset_[0] = RTC_MAP_ATTR(offset_0);
   offset_[1] = RTC_MAP_ATTR(offset_1);
   offset_[2] = RTC_MAP_ATTR(offset_2);
   offset_[3] = RTC_MAP_ATTR(offset_3);
   alpha_[0] = RTC_MAP_ATTR(alpha_0);
   alpha_[1] = RTC_MAP_ATTR(alpha_1);
   alpha_[2] = RTC_MAP_ATTR(alpha_2);
   alpha_[3] = RTC_MAP_ATTR(alpha_3);

   RTC_TRACE_CTOR_EXIT;

} // end OMS_OpfFlowMeterDeltaP::OMS_OpfFlowMeterDeltaP



//-----------------------------------------------------------------------------
/**
*
* OMS_OpfFlowMeterDeltaP destructor implementation.
*
*/
//-----------------------------------------------------------------------------
OMS_OpfFlowMeterDeltaP::~OMS_OpfFlowMeterDeltaP()
{
   RTC_TRACE_DTOR_ENTRY;

   RTC_TRACE_DTOR_EXIT;

} // end OMS_OpfFlowMeterDeltaP::~OMS_OpfFlowMeterDeltaP



//-----------------------------------------------------------------------------
/**
*
* OMS_OpfFlowMeterDeltaP initialize implementation.
*
*/
//-----------------------------------------------------------------------------
bool OMS_OpfFlowMeterDeltaP::initialize()
{
   RTC_TRACE_ENTRY(initialize);

   // Set pseudo health to good
   setPseudoHealthGood( pSampleRate_, "sampleRate", DELTAP_ENUM::LOW_RATE);
   setPseudoHealthGood( pMode_, "mode", OMS_DELTAP_MODE_ENUM::PSID);

   // Register FD monitor for calculateOutput
   When_Interrupt(
      RTC_list(pMode_, pMeasurement_),
      RTC_action(this, &OMS_OpfFlowMeterDeltaP::calculateOutput),
      true);

   // Register FD monitor for setConstants
   When_Interrupt(
      RTC_list(pOpfTestSite_),
      RTC_action(this, &OMS_OpfFlowMeterDeltaP::setConstants),
      true);

   RTC_TRACE_EXIT;

   // return initialize from the parent object
   return OMS_Object::initialize();

} // end OMS_OpfFlowMeterDeltaP::initialize



//-----------------------------------------------------------------------------
/**
* terminate - This method calls the parent class method, and sets the stale
*             bit on the flowmeters.
*
*/
//-----------------------------------------------------------------------------
void OMS_OpfFlowMeterDeltaP::terminate()
{
   RTC_TRACE_ENTRY(terminate);

   // Call parent method
   OMS_Object::terminate();

   // Set pseudo health to inactive
   setPseudoHealthInactive( pSampleRate_, "sampleRate" );
   setPseudoHealthInactive( pMode_, "mode" );

   RTC_TRACE_EXIT;

} // end OMS_OpfFlowMeterDeltaP::terminate



//-----------------------------------------------------------------------------
/**
* listMethods - This method adds class methods to the methods
* list to be displayed by the TADD.
*
*/
//-----------------------------------------------------------------------------
void OMS_OpfFlowMeterDeltaP::listMethods(
   RTC_IPCInterface::DisplayObj::List_t& rMethods)
{

   RTC_TRACE_ENTRY(listMethods);

   rMethods.addField("changeMode");
   rMethods.addField("startHighRate");
   rMethods.addField("stopHighRate");

   OMS_Object::listMethods(rMethods);

   RTC_TRACE_EXIT;

} //end OMS_OpfFlowMeterDeltaP::listMethods



//-----------------------------------------------------------------------------
/**
* listAttributes - This method adds class attributes to the attribute
* list to be displayed by the TADD.
*
* @param   rAttributes - A reference to the attribute list
* @return  void
*/
//-----------------------------------------------------------------------------
void OMS_OpfFlowMeterDeltaP::listAttributes( 
   RTC_IPCInterface::DisplayObj::List_t& rAttributes)
{
   RTC_TRACE_ENTRY(listAttributes);

   RTC_String text;

   // -------- constant1
   text.format( "constant1 : %.1f", constant1_[opfIndex_] );
   rAttributes.addField( text.c_str() );


   // -------- constant2
   text.format( "constant2 : %.1f", constant2_[opfIndex_] );
   rAttributes.addField( text.c_str() );


   // -------- offset
   text.format( "offset    : %.1f", offset_[opfIndex_] );
   rAttributes.addField( text.c_str() );


   // -------- alpha
   text.format( "alpha     : %.1f", alpha_[opfIndex_] );
   rAttributes.addField( text.c_str() );

   RTC_TRACE_EXIT;

} // end OMS_OpfFlowMeterDeltaP::listAttributes



//-----------------------------------------------------------------------------
/**
* changeMode
*
* Provides the operator access to toggle the mode between PSID and SCFM.  
* If the mode is PSID, set mode to SCFM; otherwise set it to PSID. 
* 
*/
//-----------------------------------------------------------------------------
void RTC_IMPL(OMS_OpfFlowMeterDeltaP::changeMode) ()
{

   RTC_TRACE_ENTRY(changeMode);

   Int32_t deltaPMode;

   readEnum(pMode_, "mode", "changeMode", deltaPMode );
   
   if(OMS_DELTAP_MODE_ENUM::PSID is_eq deltaPMode)
   {
      Set(pMode_, OMS_DELTAP_MODE_ENUM::SCFM);
   }
   else
   {
      Set(pMode_, OMS_DELTAP_MODE_ENUM::PSID);
   }

   RTC_TRACE_EXIT;

} // end OMS_OpfFlowMeterDeltaP::changeMode
  


//-----------------------------------------------------------------------------
/**
* startHighRate
* 
* Sets FD sample rate to 100 Hz. 
*  
*/
//-----------------------------------------------------------------------------
void RTC_IMPL(OMS_OpfFlowMeterDeltaP::startHighRate)()
{

   RTC_TRACE_ENTRY(startHighRate);

   // Dynamic cast pMeasurement_ to the RTC_AM FD type, to 
   // allow changeRate
   RTC_AM* pMeasurementFD = RTC_DYNAMIC_CAST(RTC_AM*, pMeasurement_);

   // Change the sampling rate to 100 Hz (100 per second)
   pMeasurementFD->changeRate(100);

   // Set the pSampleRate_ enum to HIGH_RATE
   Set(pSampleRate_, DELTAP_ENUM::HIGH_RATE);

   RTC_TRACE_EXIT;

} // end OMS_OpfFlowMeterDeltaP::startHighRate



//-----------------------------------------------------------------------------
/**
* stopHighRate
* 
* Sets FD sample rate to 1 Hz. 
*  
*/
//-----------------------------------------------------------------------------
void RTC_IMPL(OMS_OpfFlowMeterDeltaP::stopHighRate)()
{

   RTC_TRACE_ENTRY(stopHighRate);

   // Dynamic cast pMeasurement_ to the RTC_AM FD type, to 
   // allow changeRate
   RTC_AM* pMeasurementFD = RTC_DYNAMIC_CAST(RTC_AM*, pMeasurement_);

   // Change the sampling rate to 1 Hz (1 per second)
   pMeasurementFD->changeRate(1);

   // Set the pSampleRate_ enum to LOW_RATE
   Set(pSampleRate_, DELTAP_ENUM::LOW_RATE);

   RTC_TRACE_EXIT;

} // end OMS_OpfFlowMeterDeltaP::stopHighRate
   


//-----------------------------------------------------------------------------
/**
* calculateOutput is called upon changeData  
* 
* FD changes that will cause this method to be accessed: pMeasurement_, pMode_
*/
//-----------------------------------------------------------------------------
void RTC_IMPL(OMS_OpfFlowMeterDeltaP::calculateOutput)
   (const RTC_Event::FDInfo_t FDs)
{

   UInt8_t deltaPMode = (int) RTC_FD_STATE(pMode_);
   Float64_t measurement = (RTC_FD_STATE(pMeasurement_));
   Float64_t output;

   bool modeFailBit = RTC_FD_STATE(pMode_).fail;
   bool modeStaleBit = RTC_FD_STATE(pMode_).stale;

   // Check for bad health
   if( modeFailBit or modeStaleBit )
   {
      // Set pseudo health to bad
      setPseudoHealthBad( pOutput_, "output" );

   }
   else
   {

      // If the flowmeter mode is SCFM...
      if( OMS_DELTAP_MODE_ENUM::SCFM is_eq deltaPMode )
      {

         // ... and if the measurement is less than the alpha constant
         //     for that OPF.
         if(alpha_[opfIndex_] > measurement)
         {
            output = constant1_[opfIndex_] * sqrt(measurement);
         }
         else    // ... if, however, the measurement is greater than
                 //     the alpha constant for that OPF.
         {
            output = constant2_[opfIndex_] * measurement 
               + offset_[opfIndex_];
         }  
      }
      else   // If the flowmeter mode is not SCFM
      {
         output = measurement;
      }

      // Set the pOutput_ FD to the amount calculated above.
      Set(pOutput_, output);
   }

} // end OMS_OpfFlowMeterDeltaP::calculateOutput
   


//-----------------------------------------------------------------------------
/**
* setConstants is called on changeData when the opfTestSite changes. 
* 
* FD changes that will cause this method to be accessed: pOpfTestSite_
*/
//-----------------------------------------------------------------------------
void RTC_IMPL(OMS_OpfFlowMeterDeltaP::setConstants)
   (const RTC_Event::FDInfo_t FDs)
{

   UInt8_t testSite = (int) RTC_FD_STATE(pOpfTestSite_);
   bool siteFailBit = RTC_FD_STATE(pOpfTestSite_).fail;
   bool siteStaleBit = RTC_FD_STATE(pOpfTestSite_).stale;

   if ( siteFailBit or siteStaleBit )
   {
      // Set opfIndex_ to 0
      opfIndex_ = 0;

   }
   else
   {
      switch(testSite)
      {
         case (CAS_OPFBAYTYPE::OPF1):
            opfIndex_ = 1;
            break;

         case (CAS_OPFBAYTYPE::OPF2):
            opfIndex_ = 2;
            break;

         case (CAS_OPFBAYTYPE::OPF3):
            opfIndex_ = 3;
            break;

         default:
            opfIndex_ = 0;
            RTC_TRACE_METHOD(
               setConstants,
               "Invalid OPF test site. Flow meter constants not set.",
               RTC_Log::TRACE_ERROR);
      }
   }

} // end OMS_OpfFlowMeterDeltaP::setConstants



//-----------------------------------------------------------------------------
/**
* createIPCInterface instantiates an interprocess communication interface.
*
* This method is called from this base class to instantiate an
* interprocess communication interface for the object during 
* initialization.
*
*/
//-----------------------------------------------------------------------------
RTC_IPCMan::ObjInterface_t OMS_OpfFlowMeterDeltaP::createIPCInterface()
{
   OMS_IPCIF_OpfFlowMeterDeltaP* pIpcIf;
   RTC_NEW( pIpcIf, OMS_IPCIF_OpfFlowMeterDeltaP ( *this ) );

   return pIpcIf;

} // end OMS_OpfFlowMeterDeltaP::createIPCInterface
   

