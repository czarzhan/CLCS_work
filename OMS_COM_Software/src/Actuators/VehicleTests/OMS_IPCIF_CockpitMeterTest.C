//=============================================================================
//
// NAME:  OMS_IPCIF_CockpitMeterTest
//
// OVERVIEW: Provides all IPC interfaces for OMS_CockpitMeterTest.
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_CockpitMeterTest.h"
#include "OMS_CockpitMeterTest.h"

//=============================================================================
//                      Class Member Definitions
//=============================================================================


//--------------------------------------------------------------------------
/**
* OMS_IPCIF_CockpitMeterTest - This is the IPC interface constructor used to
* bind to a reference of the OMS_CockpitMeterTest class
*/
//--------------------------------------------------------------------------
OMS_IPCIF_CockpitMeterTest::OMS_IPCIF_CockpitMeterTest(
   OMS_CockpitMeterTest& rImpl ) :
   OMS_IPCIF_Object ( rImpl ),
   rImpl_( rImpl )
{
} // end constructor

 
//--------------------------------------------------------------------------
/**
* OMS_IPCIF_CockpitMeterTest destructor
*/
//--------------------------------------------------------------------------
OMS_IPCIF_CockpitMeterTest::~OMS_IPCIF_CockpitMeterTest()
{

} // end destructor


//--------------------------------------------------------------------------
/**
*  applyFrcsOxid
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CockpitMeterTest::applyFrcsOxid( double pctQty )
{
   rImpl_.applyFrcsOxid( pctQty );

   return OMS::PASS;
}


//--------------------------------------------------------------------------
/**
* applyFrcsFuel
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CockpitMeterTest::applyFrcsFuel( double pctQty )
{
   rImpl_.applyFrcsFuel( pctQty );

   return OMS::PASS;
}


//--------------------------------------------------------------------------
/**
* applyFrcsLowest
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CockpitMeterTest::applyFrcsLowest( double pctQty )
{
   rImpl_.applyFrcsLowest( pctQty );
   
   return OMS::PASS;
}

//--------------------------------------------------------------------------
/**
* applyLrcsOxid
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CockpitMeterTest::applyLrcsOxid( double pctQty )
{
   rImpl_.applyLrcsOxid( pctQty );
   
   return OMS::PASS;
}

//--------------------------------------------------------------------------
/**
* applyLrcsFuel
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CockpitMeterTest::applyLrcsFuel( double pctQty )
{
   rImpl_.applyLrcsFuel( pctQty );
   
   return OMS::PASS;
}

//--------------------------------------------------------------------------
/**
* applyLrcsLowest
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CockpitMeterTest::applyLrcsLowest( double pctQty )
{
   rImpl_.applyLrcsLowest( pctQty );
   
   return OMS::PASS;
}

//--------------------------------------------------------------------------
/**
* applyRrcsOxid
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CockpitMeterTest::applyRrcsOxid( double pctQty )
{
   rImpl_.applyRrcsOxid( pctQty );
   
   return OMS::PASS;
}

//--------------------------------------------------------------------------
/**
* applyRrcsFuel
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CockpitMeterTest::applyRrcsFuel( double pctQty )
{
   rImpl_.applyRrcsFuel( pctQty );
   
   return OMS::PASS;
}

//--------------------------------------------------------------------------
/**
* applyRrcsLowest
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CockpitMeterTest::applyRrcsLowest( double pctQty )
{
   rImpl_.applyRrcsLowest( pctQty );
   
   return OMS::PASS;
}

