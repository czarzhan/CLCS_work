//=============================================================================
//
// NAME:  OMS_IPCIF_CautionAndWarningTest
//
// OVERVIEW: Provides all IPC interfaces for OMS_CautionAndWarningTest
//
// RESPONSIBLE ENGINEER: Craig Roth
//
//=============================================================================

//=============================================================================
//                      System Include Files
//=============================================================================
// This section is not applicable


//=============================================================================
//                Application Specific Include Files
//=============================================================================
#include "OMS_IPCIF_CautionAndWarningTest.h"
#include "OMS_CautionAndWarningTest.h"


//=============================================================================
//                      Class Member Definitions
//=============================================================================

//--------------------------------------------------------------------------
/**
* OMS_IPCIF_CautionAndWarningTest constructor
*/
//--------------------------------------------------------------------------
OMS_IPCIF_CautionAndWarningTest::OMS_IPCIF_CautionAndWarningTest(
   OMS_CautionAndWarningTest& rImpl):
   OMS_IPCIF_Object (rImpl),
   rImpl_(rImpl)
{
} // end constructor

//--------------------------------------------------------------------------
/**
* OMS_IPCIF_CautionAndWarningTest destructor
*/
//--------------------------------------------------------------------------
OMS_IPCIF_CautionAndWarningTest::~OMS_IPCIF_CautionAndWarningTest()
{

} // end destructor


//--------------------------------------------------------------------------
/**
* turnOffFwdRcsFd
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CautionAndWarningTest::turnOffFwdRcsFd()
{
   rImpl_.turnOffFwdRcs();

   return OMS::PASS;
}
   
//--------------------------------------------------------------------------
/**
*  turnOnFwdRcsFd
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CautionAndWarningTest::turnOnFwdRcsFd()
{
   rImpl_.turnOnFwdRcs();

   return OMS::PASS;
}
   
//--------------------------------------------------------------------------
/**
* turnOffLeftRcsFd
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CautionAndWarningTest::turnOffLeftRcsFd()
{
   rImpl_.turnOffLeftRcs();

   return OMS::PASS;
}
   
//--------------------------------------------------------------------------
/**
* turnOnLeftRcsFd
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CautionAndWarningTest::turnOnLeftRcsFd()
{
   rImpl_.turnOnLeftRcs();

   return OMS::PASS;
}
   
//--------------------------------------------------------------------------
/**
* turnOffRightRcsFd
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CautionAndWarningTest::turnOffRightRcsFd()
{
   rImpl_.turnOffRightRcs();

   return OMS::PASS;
}

//--------------------------------------------------------------------------
/**
* turnOnRightRcsFd
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CautionAndWarningTest::turnOnRightRcsFd()
{
   rImpl_.turnOnRightRcs();

   return OMS::PASS;
}

//--------------------------------------------------------------------------
/**
* turnOffLeftOmsFd
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CautionAndWarningTest::turnOffLeftOmsFd()
{
   rImpl_.turnOffLeftOms();

   return OMS::PASS;
}

//--------------------------------------------------------------------------
/**
* turnOnLeftOmsFd
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CautionAndWarningTest::turnOnLeftOmsFd()
{
   rImpl_.turnOnLeftOms();

   return OMS::PASS;
}

//--------------------------------------------------------------------------
/**
* turnOffRightOmsFd
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CautionAndWarningTest::turnOffRightOmsFd()
{
   rImpl_.turnOffRightOms();

   return OMS::PASS;
}

//--------------------------------------------------------------------------
/**
* turnOnRightOmsFd
*/
//--------------------------------------------------------------------------
CORBA::Long OMS_IPCIF_CautionAndWarningTest::turnOnRightOmsFd()
{
   rImpl_.turnOnRightOms();

   return OMS::PASS;
}
