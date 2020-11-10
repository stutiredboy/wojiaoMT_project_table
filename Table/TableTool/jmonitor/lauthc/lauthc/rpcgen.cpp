
// GENERATE BY RPCGEN. DO NOT EDIT THIS FILE.

#include "rpcgen.hpp"
#include "protocols.hpp"

// include managers
#include "InfoServer.hpp"
#include "LinkClient.hpp"

// protocol stubs
static gnet::AddictionControl gnet_AddictionControl((void*)0);
static gnet::AnnounceForbidInfo gnet_AnnounceForbidInfo((void*)0);
static gnet::Challenge gnet_Challenge((void*)0);
static gnet::CouponExchangeRep gnet_CouponExchangeRep((void*)0);
static gnet::CouponExchangeReq gnet_CouponExchangeReq((void*)0);
static gnet::ErrorInfo gnet_ErrorInfo((void*)0);
static gnet::GetUserCouponRep gnet_GetUserCouponRep((void*)0);
static gnet::GetUserCouponReq gnet_GetUserCouponReq((void*)0);
static gnet::InstantAddCashRep gnet_InstantAddCashRep((void*)0);
static gnet::InstantAddCashReq gnet_InstantAddCashReq((void*)0);
static gnet::KeepAlive gnet_KeepAlive((void*)0);
static gnet::KeyExchange gnet_KeyExchange((void*)0);
static gnet::MatrixChallenge gnet_MatrixChallenge((void*)0);
static gnet::MatrixResponse gnet_MatrixResponse((void*)0);
static gnet::OnlineAnnounce gnet_OnlineAnnounce((void*)0);
static gnet::PortForward gnet_PortForward((void*)0);
static gnet::Response gnet_Response((void*)0);
static infoserver::CGetServerInfo infoserver_CGetServerInfo((void*)0);
static infoserver::SGetServerInfo infoserver_SGetServerInfo((void*)0);

// state stubs
namespace lauthc { 
namespace state { 
static GNET::Protocol::Type _Client[] = {
	gnet::AddictionControl::PROTOCOL_TYPE,
	gnet::AnnounceForbidInfo::PROTOCOL_TYPE,
	gnet::Challenge::PROTOCOL_TYPE,
	gnet::CouponExchangeRep::PROTOCOL_TYPE,
	gnet::CouponExchangeReq::PROTOCOL_TYPE,
	gnet::ErrorInfo::PROTOCOL_TYPE,
	gnet::GetUserCouponRep::PROTOCOL_TYPE,
	gnet::GetUserCouponReq::PROTOCOL_TYPE,
	gnet::InstantAddCashRep::PROTOCOL_TYPE,
	gnet::InstantAddCashReq::PROTOCOL_TYPE,
	gnet::KeepAlive::PROTOCOL_TYPE,
	gnet::KeyExchange::PROTOCOL_TYPE,
	gnet::MatrixChallenge::PROTOCOL_TYPE,
	gnet::MatrixResponse::PROTOCOL_TYPE,
	gnet::OnlineAnnounce::PROTOCOL_TYPE,
	gnet::PortForward::PROTOCOL_TYPE,
	gnet::Response::PROTOCOL_TYPE,
};
GNET::Protocol::Manager::Session::State Client(_Client, sizeof(_Client)/sizeof(GNET::Protocol::Type), -1);

} 
} 
namespace lauthc { 
namespace state { 
static GNET::Protocol::Type _InfoServer[] = {
	infoserver::CGetServerInfo::PROTOCOL_TYPE,
	infoserver::SGetServerInfo::PROTOCOL_TYPE,
};
GNET::Protocol::Manager::Session::State InfoServer(_InfoServer, sizeof(_InfoServer)/sizeof(GNET::Protocol::Type), -1);

} 
} 
