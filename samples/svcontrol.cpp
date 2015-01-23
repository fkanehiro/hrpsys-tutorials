// -*- C++ -*-
/*!
 * @file  svcontrol.cpp * @brief  * $Date$ 
 *
 * $Id$ 
 */
#include "svcontrol.h"

// Module specification
// <rtc-template block="module_spec">
static const char* svcontrol_spec[] =
  {
    "implementation_id", "svcontrol",
    "type_name",         "svcontrol",
    "description",       "",
    "version",           "1.0.0",
    "vendor",            "",
    "category",          "",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    ""
  };
// </rtc-template>

svcontrol::svcontrol(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_qOut("q", m_q)

    // </rtc-template>
{
}

svcontrol::~svcontrol()
{
}


RTC::ReturnCode_t svcontrol::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers

  // Set OutPort buffer
  addOutPort("q", m_qOut);

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable

  // </rtc-template>
  return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t svcontrol::onFinalize()
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t svcontrol::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t svcontrol::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t svcontrol::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t svcontrol::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
RTC::ReturnCode_t svcontrol::onExecute(RTC::UniqueId ec_id)
{
  m_q.data.length(1);
  m_q.data[0] = 10.0;
  m_qOut.write();
  return RTC::RTC_OK;
}
/*
RTC::ReturnCode_t svcontrol::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t svcontrol::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t svcontrol::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t svcontrol::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/
/*
RTC::ReturnCode_t svcontrol::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


extern "C"
{
 
  void svcontrolInit(RTC::Manager* manager)
  {
    coil::Properties profile(svcontrol_spec);
    manager->registerFactory(profile,
                             RTC::Create<svcontrol>,
                             RTC::Delete<svcontrol>);
  }
  
};



