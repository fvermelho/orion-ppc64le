/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
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

#include "ngsi/ParseData.h"
#include "rest/ConnectionInfo.h"
#include "serviceRoutines/postUnsubscribeContextAvailability.h"
#include "serviceRoutines/deleteAvailabilitySubscriptionConvOp.h"



/* ****************************************************************************
*
* deleteAvailabilitySubscriptionConvOp - 
*
* DELETE /v1/registry/contextAvailabilitySubscriptions/{subscriptionId}
* DELETE /ngsi9/contextAvailabilitySubscriptions/{subscriptionId}
*
* Payload In:  None
* Payload Out: UnsubscribeContextAvailabilityResponse
*
* 1. Fill in UnsubscribeContextAvailabilityRequest using 'subscriptionId'
* 2. Call the Standard operation for UnsubscribeContextAvailabilityRequest
*/
std::string deleteAvailabilitySubscriptionConvOp
(
  ConnectionInfo*            ciP,
  int                        components,
  std::vector<std::string>&  compV,
  ParseData*                 parseDataP
)
{
  std::string  subscriptionId = (compV.size() == 4)? compV[3] : compV[2];

  parseDataP->ucar.res.fill(subscriptionId);

  return postUnsubscribeContextAvailability(ciP, components, compV, parseDataP);
}
