/*
*
* Copyright 2016 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* iot_support at tid dot es
*
* Author: Ken Zangelin
*/
#include <string>
#include <vector>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/statistics.h"
#include "common/clockFunctions.h"
#include "common/tag.h"

#include "ngsi/ParseData.h"
#include "rest/ConnectionInfo.h"
#include "rest/OrionError.h"
#include "rest/uriParamNames.h"
#include "serviceRoutinesV2/semStateTreat.h"
#include "alarmMgr/alarmMgr.h"
#include "metricsMgr/metricsMgr.h"
#include "mongoBackend/mongoConnectionPool.h"



/* ****************************************************************************
*
* semRender - 
*
* NOTE: in the current implementation, 'toplevel' is always false.
*       When the operation "GET /admin/sem/<sem-name>" is implemented, 'toplevel' will
*       be set to true for the rendering of the response to that request.
*/
static const std::string semRender(const char* name, bool toplevel, const char* state)
{
  std::string out;

  if (!toplevel)
  {
    out = JSON_STR(name) + ":";
  }

  out += "{";
  out += JSON_STR("status") + ":" + JSON_STR(state);

  //
  // FIXME P4 Fill in more fields here in the future (as part of issue #2145):
  //
  // "owner":     in case 'taken': who took it
  // "purpose":   in case 'taken': for what purpose
  // "errors":    number of errors for this semaphore
  // "waitTime":  total waiting-time for this semaphore
  // "count":     number of times the semaphore has been taken
  // "taken":     number of taken semaphores (for connectionEndpoints only)
  //


  out += "}";

  return out;
}



/* ****************************************************************************
*
* semStateTreat -
*/
std::string semStateTreat
(
  ConnectionInfo*            ciP,
  int                        components,
  std::vector<std::string>&  compV,
  ParseData*                 parseDataP
)
{
  const char* dbConnectionPoolState      = mongoConnectionPoolSemGet();
  const char* dbConnectionState          = mongoConnectionSemGet();
  const char* requestState               = reqSemGet();
  const char* subCacheState              = cacheSemGet();
  const char* transactionState           = transSemGet();
  const char* timeStatState              = timeStatSemGet();
  const char* logMsgState                = lmSemGet();
  const char* alarmMgrState              = alarmMgr.semGet();
  const char* connectionContextState     = connectionContextSemGet();
  const char* connectionSubContextState  = connectionSubContextSemGet();
  const char* metricsMgrState            = metricsMgr.semStateGet();

  std::string out = "{";

  out += semRender("dbConnectionPool",     false, dbConnectionPoolState)     + ",";
  out += semRender("dbConnection",         false, dbConnectionState)         + ",";
  out += semRender("request",              false, requestState)              + ",";
  out += semRender("subCache",             false, subCacheState)             + ",";
  out += semRender("transaction",          false, transactionState)          + ",";
  out += semRender("timeStat",             false, timeStatState)             + ",";
  out += semRender("logMsg",               false, logMsgState)               + ",";
  out += semRender("alarmMgr",             false, alarmMgrState)             + ",";
  out += semRender("metricsMgr",           false, metricsMgrState)           + ",";
  out += semRender("connectionContext",    false, connectionContextState)    + ",";
  out += semRender("connectionEndpoints",  false, connectionSubContextState);

  out += "}";

  return out;
}
