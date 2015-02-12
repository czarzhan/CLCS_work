//=============================================================================
//
// NAME: OMS_CautionAndWarningTest
//
// OVERVIEW: This class captures the functionality to support the testing of
//           the OMS and RCS caution and warning parameters.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                      System Include Files
//=============================================================================

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_CautionAndWarningTest.h"
#include "OMS_CautionAndWarningTest.h"

//=============================================================================
//                      Class Member Definitions
//=============================================================================


RTC_IMPL_CLASS(OMS_CautionAndWarningTest);

//--------------------------------------------------------------------------
/**
* OMS_CautionAndWarningTest implementation
*/   
//--------------------------------------------------------------------------
OMS_CautionAndWarningTest::OMS_CautionAndWarningTest(
   const RTC_String& rParentPath, 
   const RTC_String& rIdentifier ) :
   OMS_Object( rParentPath,
               rIdentifier ),
   RTC_INIT_ATTR( pFwdRcsFd_ ),
   RTC_INIT_ATTR( pLeftRcsFd_ ),
   RTC_INIT_ATTR( pLeftOmsFd_ ),
   RTC_INIT_ATTR( pRightRcsFd_ ),
   RTC_INIT_ATTR( pRightOmsFd_ )
{
   RTC_TRACE_CTOR_ENTRY;

   RTC_TRACE_CTOR_EXIT;

} // end constructor

//--------------------------------------------------------------------------
/**
* OMS_CautionAndWarningTest destructor
*/
//--------------------------------------------------------------------------
OMS_CautionAndWarningTest::~OMS_CautionAndWarningTest()
{
   RTC_TRACE_DTOR_ENTRY;

   RTC_TRACE_DTOR_EXIT;

} // end destructor

//-------------------------------------------------------------------------
/**
* listMethods - This method adds class methods to the methods
* list to be displayed by the TADD.
*/
//-------------------------------------------------------------------------
void OMS_CautionAndWarningTest::listMethods(
   RTC_IPCInterface::DisplayObj::List_t& rMethods )
{

   RTC_TRACE_ENTRY(listMethods);

   rMethods.addField( "turnOffFwdRcsFd" );
   rMethods.addField( "turnOnFwdRcsFd" );
   rMethods.addField( "turnOffLeftRcsFd" );
   rMethods.addField( "turnOnLeftRcsFd" );
   rMethods.addField( "turnOffRightRcsFd" );
   rMethods.addField( "turnOnRightRcsFd" );
   rMethods.addField( "turnOffLeftOmsFd" );
   rMethods.addField( "turnOnLeftOmsFd" );
   rMethods.addField( "turnOffRightOmsFd" );
   rMethods.addField( "turnOnRightOmsFd" );

   OMS_Object::listMethods( rMethods );

   RTC_TRACE_EXIT;

}


//--------------------------------------------------------------------------
/**
* turnOffFwdRcs
*/
//--------------------------------------------------------------------------
void RTC_IMPL( OMS_CautionAndWarningTest::turnOffFwdRcs )()
{
   RTC_TRACE_ENTRY( turnOffFwdRcs );

   Set( pFwdRcsFd_, Discrete::Off );

   RTC_TRACE_EXIT;

}

   
//--------------------------------------------------------------------------
/**
* turnOnFwdRcs
*/
//--------------------------------------------------------------------------
void RTC_IMPL( OMS_CautionAndWarningTest::turnOnFwdRcs )()
{
   RTC_TRACE_ENTRY( turnOnFwdRcs );

   Set( pFwdRcsFd_, Discrete::On );

   RTC_TRACE_EXIT;

}


//--------------------------------------------------------------------------
/**
* turnOffLeftRcs
*/
//--------------------------------------------------------------------------
void RTC_IMPL( OMS_CautionAndWarningTest::turnOffLeftRcs )()
{
   RTC_TRACE_ENTRY( turnOffLeftRcs );

   Set( pLeftRcsFd_, Discrete::Off );

   RTC_TRACE_EXIT;

}

   
//--------------------------------------------------------------------------
/**
* turnOnLeftRcs
*/
//--------------------------------------------------------------------------
void RTC_IMPL( OMS_CautionAndWarningTest::turnOnLeftRcs )()
{
   RTC_TRACE_ENTRY( turnOnLeftRcs );

   Set( pLeftRcsFd_, Discrete::On );

   RTC_TRACE_EXIT;

}


//--------------------------------------------------------------------------
/**
* turnOffRightRcs
*/
//--------------------------------------------------------------------------
void RTC_IMPL( OMS_CautionAndWarningTest::turnOffRightRcs )()
{
   RTC_TRACE_ENTRY( turnOffRightRcs );

   Set( pRightRcsFd_, Discrete::Off );

   RTC_TRACE_EXIT;

}


//--------------------------------------------------------------------------
/**
* turnOnRightRcs
*/
//--------------------------------------------------------------------------
void RTC_IMPL( OMS_CautionAndWarningTest::turnOnRightRcs )()
{
   RTC_TRACE_ENTRY( turnOnRightRcs );

   Set( pRightRcsFd_, Discrete::On );

   RTC_TRACE_EXIT;

}


//--------------------------------------------------------------------------
/**
* turnOffLeftOms
*/
//--------------------------------------------------------------------------
void RTC_IMPL( OMS_CautionAndWarningTest::turnOffLeftOms )()
{
   RTC_TRACE_ENTRY( turnOffLeftOms );

   Set( pLeftOmsFd_, Discrete::Off );

   RTC_TRACE_EXIT;

}

   
//--------------------------------------------------------------------------
/**
* turnOnLeftOms
*/
//--------------------------------------------------------------------------
void RTC_IMPL( OMS_CautionAndWarningTest::turnOnLeftOms )()
{
   RTC_TRACE_ENTRY( turnOnLeftOms );

   Set( pLeftOmsFd_, Discrete::On );

   RTC_TRACE_EXIT;

}

   
//--------------------------------------------------------------------------
/**
* turnOffRightOms
*/
//--------------------------------------------------------------------------
void RTC_IMPL( OMS_CautionAndWarningTest::turnOffRightOms )()
{
   RTC_TRACE_ENTRY( turnOffRightOms );

   Set( pRightOmsFd_, Discrete::Off );

   RTC_TRACE_EXIT;

}

   
//--------------------------------------------------------------------------
/**
* turnOnRightOms
*/
//--------------------------------------------------------------------------
void RTC_IMPL( OMS_CautionAndWarningTest::turnOnRightOms )()
{
   RTC_TRACE_ENTRY( turnOnRightOms );

   Set( pRightOmsFd_, Discrete::On );

   RTC_TRACE_EXIT;

}

//--------------------------------------------------------------------------
/**
* createIPCInterface instantiates an interprocess communication interface.
*
* This method is called from this base class to instantiate an
* interprocess communication interface for the object during 
* initialization.
*/
//--------------------------------------------------------------------------
RTC_IPCMan::ObjInterface_t OMS_CautionAndWarningTest::createIPCInterface()
{
   RTC_TRACE_ENTRY( createIPCInterface );

   OMS_IPCIF_CautionAndWarningTest* pIpcIf;
   RTC_NEW( pIpcIf, OMS_IPCIF_CautionAndWarningTest( *this ) );

   RTC_TRACE_EXIT;

   return pIpcIf;
} // end createIPCInterface
