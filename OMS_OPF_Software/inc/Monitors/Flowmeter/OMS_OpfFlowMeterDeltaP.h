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
#ifndef OMS_OPFFLOWMETERDELTAP_H
#define OMS_OPFFLOWMETERDELTAP_H

//=============================================================================
//                      System Include Files
//=============================================================================
#include <RTC_FD.h>
#include <RTC_Event.h>

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_Object.h"

//=============================================================================
//                      Class Declarations
//=============================================================================


//----------------------------------------------------------------------------
/**
* The flowmeter is a device used to measure flow.  The flowmeter is 
* actually a delta pressure transducer that bridges an orifice. This 
* component runs in two modes: PSID and SCFM. In SCFM mode, the measurement
* data is processed through formulas based on whether the flow is above or
* below the sonic threshold, otherwise the raw measurement is presented.
*/
//----------------------------------------------------------------------------
class OMS_OpfFlowMeterDeltaP : public OMS_Object {

   RTC_DECL_CLASS(OMS_OpfFlowMeterDeltaP);

public:
   //-------------------------------------------------------------------------
   /**
   * changeMode
   *
   * Provides the operator access to toggle the mode between PSID and SCFM.  
   * If the mode is PSID, set mode to SCFM; otherwise set it to PSID. 
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(RETURNS_VOID,
               NAME (changeMode),
               NO_PARMS,
               NEVER_REJECT);
   
   //-------------------------------------------------------------------------
   /**
   * startHighRate
   * 
   * Sets FD sample rate to 100 Hz. 
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(RETURNS_VOID,
               NAME (startHighRate),
               NO_PARMS,
               NEVER_REJECT);
   
   //-------------------------------------------------------------------------
   /**
   * stopHighRate
   * 
   * Sets FD sample rate to 1 Hz. 
   */
   //-------------------------------------------------------------------------
   RTC_PROXY(RETURNS_VOID,
               NAME (stopHighRate),
               NO_PARMS,
               NEVER_REJECT);
   
   
public:    
   
   //-------------------------------------------------------------------------
   /**
   * OMS_OpfFlowMeterDeltaP constructor
   *
   * @param rParentPath  specifies the path of the parent object that this 
   *                    object is an aggregate of.
   * @param rIdentifier  specifies an id which is concatenated to the 
   *                    rParentPath to form a unique path for this object. 
   *                    The path is used to retrieve instance data 
   *                    from the Instance Map. 
   */   
   //-------------------------------------------------------------------------
   OMS_OpfFlowMeterDeltaP(
      const RTC_String& rParentPath, 
      const RTC_String& rIdentifier);
   
   //-------------------------------------------------------------------------
   /**
   *
   * OMS_OpfFlowMeterDeltaP destructor.
   *
   */
   //-------------------------------------------------------------------------
   virtual ~OMS_OpfFlowMeterDeltaP();

   //-------------------------------------------------------------------------
   /**
   * initialize - This method sets the health of the pseudos to good, and
   *              calls the parent class method.
   *
   * @return bool - Results of call to parent class method.
   */
   //-------------------------------------------------------------------------
   virtual bool initialize();
   
   //-------------------------------------------------------------------------
   /**
   * terminate - This method calls the parent class method, and stops change
   * data on the flowmeter FDs.
   */
   //-------------------------------------------------------------------------
   virtual void terminate();

   //-------------------------------------------------------------------------
   /**
   * listMethods - This method adds class methods to the methods
   * list to be displayed by the TADD.
   */
   //-------------------------------------------------------------------------
   void listMethods(RTC_IPCInterface::DisplayObj::List_t& rMethods); 

   //-------------------------------------------------------------------------
   /**
   * listAttributes - This method adds class attributes to the attribute
   * list to be displayed by the TADD.
   *
   * @param   rAttributes - A reference to the attribute list
   */
   //-------------------------------------------------------------------------
   virtual void listAttributes( 
      RTC_IPCInterface::DisplayObj::List_t& rAttributes);

protected:    

   //-------------------------------------------------------------------------
   /**
   * createIPCInterface instantiates an interprocess communication interface.
   *
   * This method is called from this base class to instantiate an
   * interprocess communication interface for the object during 
   * initialization.
   *
   * @return newly instantiated interprocess communication interface for the 
   *         object
   */
   //-------------------------------------------------------------------------
   RTC_IPCMan::ObjInterface_t createIPCInterface();
   
   
   //-------------------------------------------------------------------------
   /**
   * calculateOutput is called on changeData
   * 
   * The flowrate output is calculated upon change of the mode or measurements.
   * The output is either (in PSID mode) the raw pressure meansurement received
   * from the component, or (in SCFM mode) a value based on a set of 
   * two different calculations, depending whether the flow is in the sonic or
   * subsonic range.
   *
   * @param   FDs - The list of fds monitored for changes in flow:
   *                                                         pMeasurement_
   *                                                         pMode_
   */
   //-------------------------------------------------------------------------
   RTC_EVENT_HANDLER (NAME(calculateOutput),
                      PARMS1(const RTC_Event::FDInfo_t, FDs));
   
   //-------------------------------------------------------------------------
   /**
   * setConstants
   * 
   * The method setConstants is called when the opfTestSite changes. This can
   * occur on either EIM initialization or changeData from the control room.
   * On a change, this method sets the constants for the component, which vary
   * by OPF bay.
   *
   * @param   FDs - The list of fds monitored for change in OPF: pOpfTestSite_
   */
   //-------------------------------------------------------------------------
   RTC_EVENT_HANDLER (NAME(setConstants),
                      PARMS1(const RTC_Event::FDInfo_t, FDs));
   
private:

   /**
   * The raw analog measurement. 
   */
   RTC_FD* pMeasurement_;
   
   /**
   * The mode determines how the output is published, either presenting the 
   * raw measurement data or data processed through formulas (given in 
   * calculateOutput())
   */
   RTC_FD* pMode_;
   
   /**
   * If sampleRate is LOW_RATE then the measurement sample rate is 1 Hz, 
   * else measurement sample rate is 100 Hz. 
   */
   RTC_FD* pSampleRate_;
   
   /**
   * Defined by mode, and calculated from on the measurement and the constants.
   */
   RTC_FD* pOutput_;
   
   /**
   * Current OPF test site. 
   */
   RTC_FD* pOpfTestSite_;
   
   /**
   * In the subsonic region, is multiplied by the square root of the raw 
   * analog measurement.  There are 3 different values, one for each OPF bay,
   * and a zero value used for error conditions. 
   */
   Float64_t constant1_[4];
   
   /**
   * The slope of the line in the supersonic region.  There are 3 different 
   * values, one for each OPF bay, and a zero value used for error conditions.
   */
   Float64_t constant2_[4];
   
   /**
   * The y-intercept of the line in the supersonic region.  There are 3 
   * different values, one for each OPF bay, and a zero value used for error
   * conditions. 
   */
   Float64_t offset_[4];
   
   /**
   * The point at which the flow transistions from subsonic to sonic.  There
   * are three different values, one for each OPF bay, and a zero value used
   * for error conditions.
   */
   Float64_t alpha_[4];
   
   /**
   * An index to the OPF bay, setConstants() sets this. It is used as an index
   * for the four above arrays.
   */
   UInt8_t opfIndex_;
   
};
#endif //OMS_OPFFLOWMETERDELTAP_H
