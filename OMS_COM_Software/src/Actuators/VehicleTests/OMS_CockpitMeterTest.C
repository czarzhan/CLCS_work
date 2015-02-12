//=============================================================================
//
// NAME: OMS_CockpitMeterTest
//
// OVERVIEW: This class captures the functionality to support the OMS/RCS
//           cockpit meter test by applying values to the RCS oxidizer, fuel
//           and lowest function designators and checking the corresponding 
//           measurements on the orbiter flight deck.
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
#include "OMS_IPCIF_CockpitMeterTest.h"
#include "OMS_CockpitMeterTest.h"

//=============================================================================
//                      Class Member Definitions
//=============================================================================


RTC_IMPL_CLASS(OMS_CockpitMeterTest);


//--------------------------------------------------------------------------
/**
* OMS_CockpitMeterTest constructor
*/   
//--------------------------------------------------------------------------
OMS_CockpitMeterTest::OMS_CockpitMeterTest( const RTC_String& rParentPath, 
                                            const RTC_String& rIdentifier ) :
   OMS_Object( rParentPath,
               rIdentifier ),
   RTC_INIT_ATTR (pFrcsOxidQty_ ),
   RTC_INIT_ATTR( pFrcsFuelQty_ ),
   RTC_INIT_ATTR( pFrcsLowest_ ),
   RTC_INIT_ATTR( pLrcsOxidQty_ ),
   RTC_INIT_ATTR( pLrcsFuelQty_ ),
   RTC_INIT_ATTR( pLrcsLowest_ ),
   RTC_INIT_ATTR( pRrcsOxidQty_ ),
   RTC_INIT_ATTR( pRrcsFuelQty_ ),
   RTC_INIT_ATTR( pRrcsLowest_ )
{
   RTC_TRACE_CTOR_ENTRY;
   
   RTC_TRACE_CTOR_EXIT;
   
}


//--------------------------------------------------------------------------
/**
* OMS_CockpitMeterTest destructor
*/
//--------------------------------------------------------------------------
OMS_CockpitMeterTest::~OMS_CockpitMeterTest()
{
   RTC_TRACE_DTOR_ENTRY;
   
   RTC_TRACE_DTOR_EXIT;
   
}

//--------------------------------------------------------------------------
/**
* applyFrcsOxid
*/
//--------------------------------------------------------------------------
void RTC_IMPL(OMS_CockpitMeterTest::applyFrcsOxid)(const Float32_t pctQty)
{
   RTC_TRACE_ENTRY_ARGS( applyFrcsOxid, METHOD_ARG( pctQty ) );

   Set( pFrcsOxidQty_, pctQty );

   RTC_TRACE_EXIT;
   
}

//--------------------------------------------------------------------------
/**
* applyFrcsFuel
*/
//--------------------------------------------------------------------------
void RTC_IMPL(OMS_CockpitMeterTest::applyFrcsFuel)(const Float32_t pctQty)
{
   RTC_TRACE_ENTRY_ARGS( applyFrcsFuel, METHOD_ARG( pctQty ) );
   
   Set( pFrcsFuelQty_, pctQty );

   RTC_TRACE_EXIT;
   
}

//--------------------------------------------------------------------------
/**
* applyFrcsLowest
*/
//--------------------------------------------------------------------------
void RTC_IMPL(OMS_CockpitMeterTest::applyFrcsLowest)(const Float32_t pctQty)
{
   RTC_TRACE_ENTRY_ARGS( applyFrcsLowest, METHOD_ARG( pctQty ) );
   
   Set( pFrcsLowest_, pctQty );
  
   RTC_TRACE_EXIT;
   
}

//--------------------------------------------------------------------------
/**
* applyLrcsOxid
*/
//--------------------------------------------------------------------------
void RTC_IMPL(OMS_CockpitMeterTest::applyLrcsOxid)(const Float32_t pctQty)
{
   RTC_TRACE_ENTRY_ARGS( applyLrcsOxid, METHOD_ARG( pctQty ) );
   
   Set( pLrcsOxidQty_, pctQty );
  
   RTC_TRACE_EXIT;
   
}

//--------------------------------------------------------------------------
/**
* applyLrcsFuel
*/
//--------------------------------------------------------------------------
void RTC_IMPL(OMS_CockpitMeterTest::applyLrcsFuel)(const Float32_t pctQty)
{
   RTC_TRACE_ENTRY_ARGS( applyLrcsFuel, METHOD_ARG( pctQty ) );
   
   Set( pLrcsFuelQty_, pctQty );
   
   RTC_TRACE_EXIT;
   
}

//--------------------------------------------------------------------------
/**
* applyLrcsLowest
*/
//--------------------------------------------------------------------------
void RTC_IMPL(OMS_CockpitMeterTest::applyLrcsLowest)(const Float32_t pctQty)
{
   RTC_TRACE_ENTRY_ARGS( applyLrcsLowest, METHOD_ARG( pctQty ) );
   
   Set( pLrcsLowest_, pctQty );
   
   RTC_TRACE_EXIT;
   
}

//--------------------------------------------------------------------------
/**
* applyRrcsOxid
*/
//--------------------------------------------------------------------------
void RTC_IMPL(OMS_CockpitMeterTest::applyRrcsOxid)(const Float32_t pctQty)
{
   RTC_TRACE_ENTRY_ARGS( applyRrcsOxid, METHOD_ARG( pctQty ) );
   
   Set( pRrcsOxidQty_, pctQty );
  
   RTC_TRACE_EXIT;
   
}

//--------------------------------------------------------------------------
/**
* applyRrcsFuel
*/
//--------------------------------------------------------------------------
void RTC_IMPL(OMS_CockpitMeterTest::applyRrcsFuel)(const Float32_t pctQty)
{
   RTC_TRACE_ENTRY_ARGS( applyRrcsFuel, METHOD_ARG( pctQty ) );
   
   Set( pRrcsFuelQty_, pctQty );
   
   RTC_TRACE_EXIT;
   
}

//--------------------------------------------------------------------------
/**
* applyRrcsLowest
*/
//--------------------------------------------------------------------------
void RTC_IMPL(OMS_CockpitMeterTest::applyRrcsLowest)(const Float32_t pctQty)
{
   RTC_TRACE_ENTRY_ARGS( applyRrcsLowest, METHOD_ARG( pctQty ) );
   
   Set( pRrcsLowest_, pctQty );

   RTC_TRACE_EXIT;
   
}



//-------------------------------------------------------------------------
/**
* listMethods - This method adds class methods to the methods
* list to be displayed by the TADD.
*/
//-------------------------------------------------------------------------
void OMS_CockpitMeterTest::listMethods(
   RTC_IPCInterface::DisplayObj::List_t& rMethods ) 
{
   
   RTC_TRACE_ENTRY( listMethods );

   RTC_String text;
   Float64_t quantity = 0.0;
   
   readAnalog( pFrcsOxidQty_, quantity );
   text.format( "applyFrcsOxid(d frcsOxidQty:0.0:100.0:%.2f)", quantity );
   rMethods.addField( text.c_str() );

   readAnalog( pFrcsFuelQty_, quantity );
   text.format( "applyFrcsFuel(d frcsFuelQty:0.0:100.0:%.2f)", quantity );
   rMethods.addField( text.c_str() );

   readAnalog (pFrcsLowest_, quantity );
   text.format( "applyFrcsLowest(d frcsLowest:0.0:100.0:%.2f)", quantity );
   rMethods.addField( text.c_str() );

   readAnalog( pLrcsOxidQty_, quantity );
   text.format( "applyLrcsOxid(d lrcsOxidQty:0.0:100.0:%.2f)", quantity );
   rMethods.addField( text.c_str() );

   readAnalog( pLrcsFuelQty_, quantity );
   text.format( "applyLrcsFuel(d lrcsFuelQty:0.0:100.0:%.2f)", quantity );
   rMethods.addField( text.c_str() );

   readAnalog( pLrcsLowest_, quantity );
   text.format( "applyLrcsLowest(d lrcsLowest:0.0:100.0:%.2f)", quantity );
   rMethods.addField( text.c_str() );

   readAnalog( pRrcsOxidQty_, quantity );
   text.format( "applyRrcsOxid(d rrcsOxidQty:0.0:100.0:%.2f)", quantity );
   rMethods.addField( text.c_str() );

   readAnalog( pRrcsFuelQty_, quantity );
   text.format( "applyRrcsFuel(d rrcsFuelQty:0.0:100.0:%.2f)", quantity );
   rMethods.addField( text.c_str() );

   readAnalog(pRrcsLowest_, quantity);
   text.format("applyRrcsLowest(d rrcsLowest:0.0:100.0:%.2f)", quantity);
   rMethods.addField( text.c_str() );

   
   OMS_Object::listMethods( rMethods );
   
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
RTC_IPCMan::ObjInterface_t OMS_CockpitMeterTest::createIPCInterface()
{
   RTC_TRACE_ENTRY( createIPCInterface );

   OMS_IPCIF_CockpitMeterTest* pIpcIf;
   RTC_NEW( pIpcIf, OMS_IPCIF_CockpitMeterTest( *this ) );

   RTC_TRACE_EXIT;

   return pIpcIf;
} // end createIPCInterface
