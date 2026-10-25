/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

#include "../detail/unit_836e632273.hpp"
#include "../Query/detail/unit_33dc8b31a1.hpp"
#include "../../../../RakNet/detail/unit_c330cee1ca.hpp"
#include <sstream>
#include <string>
#include "../../../../Shared/NetCode/detail/unit_4c18dc97b3.hpp"
#include "../../../../RakNet/Include/raknet/PacketEnumerations.h"
#include "../../../../RakNet/Include/raknet/RakPeer.h"
#include <ttmath/ttmath.h>

#define RPCHOOK(id) rakNetServer.RegisterAsRemoteProcedureCall(id, &RakNetLegacyNetwork::RPCHook<id>, this)

RakNetLegacyNetwork::RakNetLegacyNetwork()
	: Network(256, 256)
	, core(nullptr)
	, rakNetServer(*RakNet::RakNetworkFactory::GetRakServerInterface())
{
	rakNetServer.SetMTUSize(512);
	playerRemoteSystem.fill(nullptr);

	RPCHOOK(0);
	RPCHOOK(1);
	RPCHOOK(2);
	RPCHOOK(3);
	RPCHOOK(4);
	RPCHOOK(5);
	RPCHOOK(6);
	RPCHOOK(7);
	RPCHOOK(8);
	RPCHOOK(9);
	RPCHOOK(10);
	RPCHOOK(11);
	RPCHOOK(12);
	RPCHOOK(13);
	RPCHOOK(14);
	RPCHOOK(15);
	RPCHOOK(16);
	RPCHOOK(17);
	RPCHOOK(18);
	RPCHOOK(19);
	RPCHOOK(20);
	RPCHOOK(21);
	RPCHOOK(22);
	RPCHOOK(23);
	RPCHOOK(24);
	rakNetServer.RegisterAsRemoteProcedureCall(static_cast<RakNet::RPCID>(NetCode::RPC::PlayerConnect::PacketID), &RakNetLegacyNetwork::OnPlayerConnect, this);
	RPCHOOK(26);
	RPCHOOK(27);
	RPCHOOK(28);
	RPCHOOK(29);
	RPCHOOK(30);
	RPCHOOK(31);
	RPCHOOK(32);
	RPCHOOK(33);
	RPCHOOK(34);
	RPCHOOK(35);
	RPCHOOK(36);
	RPCHOOK(37);
	RPCHOOK(38);
	RPCHOOK(39);
	RPCHOOK(40);
	RPCHOOK(41);
	RPCHOOK(42);
	RPCHOOK(43);
	RPCHOOK(44);
	RPCHOOK(45);
	RPCHOOK(46);
	RPCHOOK(47);
	RPCHOOK(48);
	RPCHOOK(49);
	RPCHOOK(50);
	RPCHOOK(51);
	RPCHOOK(52);
	RPCHOOK(53);
	rakNetServer.RegisterAsRemoteProcedureCall(static_cast<RakNet::RPCID>(NetCode::RPC::NPCConnect::PacketID), &RakNetLegacyNetwork::OnNPCConnect, this);
	RPCHOOK(55);
	RPCHOOK(56);
	RPCHOOK(57);
	RPCHOOK(58);
	RPCHOOK(59);
	RPCHOOK(60);
	RPCHOOK(61);
	RPCHOOK(62);
	RPCHOOK(63);
	RPCHOOK(64);
	RPCHOOK(65);
	RPCHOOK(66);
	RPCHOOK(67);
	RPCHOOK(68);
	RPCHOOK(69);
	RPCHOOK(70);
	RPCHOOK(71);
	RPCHOOK(72);
	RPCHOOK(73);
	RPCHOOK(74);
	RPCHOOK(75);
	RPCHOOK(76);
	RPCHOOK(77);
	RPCHOOK(78);
	RPCHOOK(79);
	RPCHOOK(80);
	RPCHOOK(81);
	RPCHOOK(82);
	RPCHOOK(83);
	RPCHOOK(84);
	RPCHOOK(85);
	RPCHOOK(86);
	RPCHOOK(87);
	RPCHOOK(88);
	RPCHOOK(89);
	RPCHOOK(90);
	RPCHOOK(91);
	RPCHOOK(92);
	RPCHOOK(93);
	RPCHOOK(94);
	RPCHOOK(95);
	RPCHOOK(96);
	RPCHOOK(97);
	RPCHOOK(98);
	RPCHOOK(99);
	RPCHOOK(100);
	RPCHOOK(101);
	RPCHOOK(102);
	RPCHOOK(103);
	RPCHOOK(104);
	RPCHOOK(105);
	RPCHOOK(106);
	RPCHOOK(107);
	RPCHOOK(108);
	RPCHOOK(109);
	RPCHOOK(110);
	RPCHOOK(111);
	RPCHOOK(112);
	RPCHOOK(113);
	RPCHOOK(114);
	RPCHOOK(115);
	RPCHOOK(116);
	RPCHOOK(117);
	RPCHOOK(118);
	RPCHOOK(119);
	RPCHOOK(120);
	RPCHOOK(121);
	RPCHOOK(122);
	RPCHOOK(123);
	RPCHOOK(124);
	RPCHOOK(125);
	RPCHOOK(126);
	RPCHOOK(127);
	RPCHOOK(128);
	RPCHOOK(129);
	RPCHOOK(130);
	RPCHOOK(131);
	RPCHOOK(132);
	RPCHOOK(133);
	RPCHOOK(134);
	RPCHOOK(135);
	RPCHOOK(136);
	RPCHOOK(137);
	RPCHOOK(138);
	RPCHOOK(139);
	RPCHOOK(140);
	RPCHOOK(141);
	RPCHOOK(142);
	RPCHOOK(143);
	RPCHOOK(144);
	RPCHOOK(145);
	RPCHOOK(146);
	RPCHOOK(147);
	RPCHOOK(148);
	RPCHOOK(149);
	RPCHOOK(150);
	RPCHOOK(151);
	RPCHOOK(152);
	RPCHOOK(153);
	RPCHOOK(154);
	RPCHOOK(155);
	RPCHOOK(156);
	RPCHOOK(157);
	RPCHOOK(158);
	RPCHOOK(159);
	RPCHOOK(160);
	RPCHOOK(161);
	RPCHOOK(162);
	RPCHOOK(163);
	RPCHOOK(164);
	RPCHOOK(165);
	RPCHOOK(166);
	RPCHOOK(167);
	RPCHOOK(168);
	RPCHOOK(169);
	RPCHOOK(170);
	RPCHOOK(171);
	RPCHOOK(172);
	RPCHOOK(173);
	RPCHOOK(174);
	RPCHOOK(175);
	RPCHOOK(176);
	RPCHOOK(177);
	RPCHOOK(178);
	RPCHOOK(179);
	RPCHOOK(180);
	RPCHOOK(181);
	RPCHOOK(182);
	RPCHOOK(183);
	RPCHOOK(184);
	RPCHOOK(185);
	RPCHOOK(186);
	RPCHOOK(188);
	RPCHOOK(189);
	RPCHOOK(190);
	RPCHOOK(191);
	RPCHOOK(192);
	RPCHOOK(193);
	RPCHOOK(194);
	RPCHOOK(195);
	RPCHOOK(196);
	RPCHOOK(197);
	RPCHOOK(198);
	RPCHOOK(199);
	RPCHOOK(200);
	RPCHOOK(201);
	RPCHOOK(202);
	RPCHOOK(203);
	RPCHOOK(204);
	RPCHOOK(205);
	RPCHOOK(206);
	RPCHOOK(207);
	RPCHOOK(208);
	RPCHOOK(209);
	RPCHOOK(210);
	RPCHOOK(211);
	RPCHOOK(212);
	RPCHOOK(213);
	RPCHOOK(214);
	RPCHOOK(215);
	RPCHOOK(216);
	RPCHOOK(217);
	RPCHOOK(218);
	RPCHOOK(219);
	RPCHOOK(220);
	RPCHOOK(221);
	RPCHOOK(222);
	RPCHOOK(223);
	RPCHOOK(224);
	RPCHOOK(225);
	RPCHOOK(226);
	RPCHOOK(227);
	RPCHOOK(228);
	RPCHOOK(229);
	RPCHOOK(230);
	RPCHOOK(231);
	RPCHOOK(232);
	RPCHOOK(233);
	RPCHOOK(234);
	RPCHOOK(235);
	RPCHOOK(236);
	RPCHOOK(237);
	RPCHOOK(238);
	RPCHOOK(239);
	RPCHOOK(240);
	RPCHOOK(241);
	RPCHOOK(242);
	RPCHOOK(243);
	RPCHOOK(244);
	RPCHOOK(245);
	RPCHOOK(246);
	RPCHOOK(247);
	RPCHOOK(248);
	RPCHOOK(249);
	RPCHOOK(250);
	RPCHOOK(251);
	RPCHOOK(252);
	RPCHOOK(253);
	}

#undef RPCHOOK

RakNetLegacyNetwork::~RakNetLegacyNetwork()
{
	if (core)
	{
		core->getEventDispatcher().removeEventHandler(this);
		core->getPlayers().getPlayerChangeDispatcher().removeEventHandler(this);
		core->getPlayers().getPlayerConnectDispatcher().removeEventHandler(this);
	}

	if (npcComponent)
	{
		npcComponent->getPoolEventDispatcher().removeEventHandler(this);
	}

	rakNetServer.Disconnect(300);
	RakNet::RakNetworkFactory::DestroyRakServerInterface(&rakNetServer);
}

static NetworkBitStream GetBitStream(RakNet::RPCParameters& rpcParams)
{
	const unsigned int
		bits
		= rpcParams.numberOfBitsOfData;
	if (bits == 0)
		return NetworkBitStream();
	NetworkBitStream bs(rpcParams.input, bitsToBytes(bits), false /* copyData */);
	bs.SetWriteOffset(bits);
	return bs;
}

static uint8_t TranslateLegacyPacketID(uint8_t type)
{
	switch (type)
	{
	case RakNet::ID_UNOCCUPIED_SYNC:
		return NetCode::Packet::PlayerUnoccupiedSync::PacketID;
	case RakNet::ID_VEHICLE_SYNC:
		return NetCode::Packet::PlayerVehicleSync::PacketID;
	case RakNet::ID_PASSENGER_SYNC:
		return NetCode::Packet::PlayerPassengerSync::PacketID;
	case RakNet::ID_AIM_SYNC:
		return NetCode::Packet::PlayerAimSync::PacketID;
	case RakNet::ID_STATS_UPDATE:
		return NetCode::Packet::PlayerStatsSync::PacketID;
	case RakNet::ID_PLAYER_SYNC:
		return NetCode::Packet::PlayerFootSync::PacketID;
	case RakNet::ID_TRAILER_SYNC:
		return NetCode::Packet::PlayerTrailerSync::PacketID;
	case RakNet::ID_BULLET_SYNC:
		return NetCode::Packet::PlayerBulletSync::PacketID;
	case RakNet::ID_SPECTATOR_SYNC:
		return NetCode::Packet::PlayerSpectatorSync::PacketID;
	case RakNet::ID_WEAPONS_UPDATE:
		return NetCode::Packet::PlayerWeaponsUpdate::PacketID;
	default:
		return type;
	}
}


enum LegacyClientVersion
{
	LegacyClientVersion_037 = 4057,
	LegacyClientVersion_03DL = 4062,
	LegacyClientVersion_BazeClient = 1362,
	LegacyClientVersion_BazeClient_New = 1375
};

IPlayer* RakNetLegacyNetwork::OnPeerConnect(RakNet::RPCParameters* rpcParams, bool isNPC, StringView serial, uint32_t version, StringView versionName, uint32_t challenge, StringView name, bool isUsingOmp, bool isUsingOfficialClient)
{
	const RakNet::PlayerID rid = rpcParams->sender;

	if (playerFromRakIndex[rpcParams->senderIndex])
	{
		// Connection already exists
		return nullptr;
	}

	PeerNetworkData netData {};
	netData.networkID.address.ipv6 = false;
	netData.networkID.address.v4 = rid.binaryAddress;
	netData.networkID.port = rid.port;
	netData.network = this;

	Pair<NewConnectionResult, IPlayer*> newConnectionResult { NewConnectionResult_Ignore, nullptr };

	// Custom legacy clients don't always mirror the stock SA-MP version/challenge
	// rules, so accept the join here and let higher-level validation decide.
	PeerRequestParams params;
	params.version = (version == LegacyClientVersion_03DL) ? ClientVersion::ClientVersion_SAMP_03DL : ClientVersion::ClientVersion_SAMP_037;
	params.versionName = versionName;
	params.name = name;
	params.bot = isNPC;
	params.serial = serial;
	params.isUsingOfficialClient = isUsingOfficialClient;
	params.isUsingOmp = isUsingOmp;
	newConnectionResult = core->getPlayers().requestPlayer(netData, params);

	if (newConnectionResult.first != NewConnectionResult_Success)
	{
		if (newConnectionResult.first != NewConnectionResult_Ignore)
		{
			// Entry denied, send reason and disconnect
			core->logLn(LogLevel::Warning,
				"[OnPeerConnect] Connection rejected for %s (reason=%d, noPlayerSlot=%d, badName=%d, ignore=%d)",
				rid.ToString(),
				int(newConnectionResult.first),
				int(newConnectionResult.first == NewConnectionResult_NoPlayerSlot),
				int(newConnectionResult.first == NewConnectionResult_BadName),
				int(newConnectionResult.first == NewConnectionResult_Ignore));
			RakNet::BitStream bss;
			bss.Write(uint8_t(newConnectionResult.first));
			rakNetServer.RPC(130, &bss, RakNet::HIGH_PRIORITY, RakNet::UNRELIABLE, 0, rid, false, false, RakNet::UNASSIGNED_NETWORK_ID, nullptr);
		}
		return nullptr;
	}

	playerFromRakIndex[rpcParams->senderIndex] = newConnectionResult.second;

	return newConnectionResult.second;
}

void RakNetLegacyNetwork::OnPlayerConnect(RakNet::RPCParameters* rpcParams, void* extra)
{
	if (!rpcParams)
	{
		return;
	}

	RakNetLegacyNetwork* network = reinterpret_cast<RakNetLegacyNetwork*>(extra);
	if (!network)
	{
		return;
	}

	RakNet::RakPeer::RemoteSystemStruct* remoteSystem = network->rakNetServer.GetRemoteSystemFromPlayerID(rpcParams->sender);
	const int rawBytes = rpcParams->numberOfBitsOfData > 0 ? int((rpcParams->numberOfBitsOfData + 7) / 8) : 0;

	if (false) network->core->printLn(
		"[LegacyNetwork::OnPlayerConnect] rpc=295 sender=%s length=%d remoteSystem=%p connectMode=%d authType=%d",
		rpcParams->sender.ToString(),
		rawBytes,
		static_cast<void*>(remoteSystem),
		remoteSystem ? int(remoteSystem->connectMode) : -1,
		remoteSystem ? int(remoteSystem->sampData.authType) : -1);

	if (!remoteSystem || remoteSystem->connectMode != RakNet::RakPeer::RemoteSystemStruct::ConnectMode::CONNECTED)
	{
		if (false) network->core->printLn(
			"[LegacyNetwork::OnPlayerConnect] Ignoring sender=%s because remote system is null or not CONNECTED",
			rpcParams->sender.ToString());
		return;
	}

	if (remoteSystem->sampData.authType != SAMPRakNet::AuthType_Player)
	{
		if (false) network->core->printLn(
			"[LegacyNetwork::OnPlayerConnect] Kicking sender=%s due to authType=%d",
			rpcParams->sender.ToString(),
			int(remoteSystem->sampData.authType));
		network->rakNetServer.Kick(rpcParams->sender);
		return;
	}

	NetworkBitStream bs = GetBitStream(*rpcParams);
	uint32_t challengeResponse = 0;
	uint32_t clientVersion = 0;
	String serial;
	StringView versionName = "";
	StringView playerName = "";
	bool useBazeCompatJoin = false;
	char bazeName[MAX_PLAYER_NAME + 1] = {};

	{
		NetworkBitStream compatBs = GetBitStream(*rpcParams);
		uint32_t compatChallengeResponse = 0;
		uint8_t compatAndroidVersion = 0;
		int compatClientVersion = 0;
		uint8_t compatFingerprint = 0;
		uint8_t compatNameLen = 0;

		if (compatBs.GetNumberOfUnreadBits() >= int((sizeof(uint32_t) + sizeof(uint8_t) + sizeof(int) + sizeof(uint8_t) + sizeof(uint8_t)) * 8)
			&& compatBs.readUINT32(compatChallengeResponse)
			&& compatBs.readUINT8(compatAndroidVersion)
			&& compatBs.readINT32(compatClientVersion)
			&& compatBs.readUINT8(compatFingerprint)
			&& compatBs.readUINT8(compatNameLen)
			&& compatNameLen >= MIN_PLAYER_NAME
			&& compatNameLen <= MAX_PLAYER_NAME
			&& compatBs.GetNumberOfUnreadBits() == compatNameLen * 8
			&& compatBs.readArray(Span<char>(bazeName, compatNameLen))
			)
		{
			bazeName[compatNameLen] = '\0';
			challengeResponse = compatChallengeResponse;
			clientVersion = static_cast<uint32_t>(compatClientVersion);
			serial = "0";
			versionName = "baze";
			playerName = StringView(bazeName, compatNameLen);
			useBazeCompatJoin = true;

			if (false) network->core->printLn(
				"[LegacyNetwork::OnPlayerConnect] Compat join matched sender=%s challenge=%u androidVer=%u clientVer=%d fingerprint=%u nameLen=%u name=%.*s",
				rpcParams->sender.ToString(),
				compatChallengeResponse,
				unsigned(compatAndroidVersion),
				compatClientVersion,
				unsigned(compatFingerprint),
				unsigned(compatNameLen),
				int(compatNameLen),
				bazeName);

			if (false) network->core->printLn("[LegacyNetwork::OnPlayerConnect] Client version Baze Compat (clientVer=%d)",
				compatClientVersion);
		}
	}

	if (!useBazeCompatJoin)
	{
		NetCode::RPC::PlayerConnect playerConnectRPC;
		if (!playerConnectRPC.read(bs))
		{
			if (false) network->core->printLn(
				"[LegacyNetwork::OnPlayerConnect] PlayerConnect read failed sender=%s length=%d",
				rpcParams->sender.ToString(),
				rawBytes);
			network->rakNetServer.Kick(rpcParams->sender);
			return;
		}

		if (false) network->core->printLn(
			"[LegacyNetwork::OnPlayerConnect] Standard join parsed sender=%s challenge=%u clientVer=%u name=%.*s",
			rpcParams->sender.ToString(),
			playerConnectRPC.ChallengeResponse,
			playerConnectRPC.VersionNumber,
			int(playerConnectRPC.Name.length()),
			playerConnectRPC.Name.data());


		const bool knownVersion =
			playerConnectRPC.VersionNumber == LegacyClientVersion_037 ||
			playerConnectRPC.VersionNumber == LegacyClientVersion_03DL ||
			playerConnectRPC.VersionNumber == LegacyClientVersion_BazeClient ||
			playerConnectRPC.VersionNumber == LegacyClientVersion_BazeClient_New;
		if (!knownVersion || playerConnectRPC.Name.length() < MIN_PLAYER_NAME ||
			playerConnectRPC.Name.length() > MAX_PLAYER_NAME)
		{
			if (false) network->core->printLn(
				"[LegacyNetwork::OnPlayerConnect] Dropping malformed join sender=%s version=%u nameLen=%u",
				rpcParams->sender.ToString(), playerConnectRPC.VersionNumber,
				unsigned(playerConnectRPC.Name.length()));
			network->rakNetServer.Kick(rpcParams->sender);
			return;
		}

		serial = "0";
		challengeResponse = playerConnectRPC.ChallengeResponse;
		clientVersion = playerConnectRPC.VersionNumber;
		playerName = playerConnectRPC.Name;
		if (clientVersion == LegacyClientVersion_BazeClient || clientVersion == LegacyClientVersion_BazeClient_New)
		{
			versionName = "baze";
		}
	}

	if (false) network->core->printLn(
		"[LegacyNetwork::OnPlayerConnect] Final join sender=%s compat=%d challenge=%u clientVer=%u version=%.*s serial=%.*s player=%.*s",
		rpcParams->sender.ToString(),
		useBazeCompatJoin ? 1 : 0,
		challengeResponse,
		clientVersion,
		int(versionName.length()),
		versionName.data(),
		int(serial.length()),
		serial.data(),
		int(playerName.length()),
		playerName.data());

	bool isUsingOmp = SAMPRakNet::IsPlayerUsingOmp(rpcParams->sender);
	if (isUsingOmp)
	{
		if (false) network->core->printLn("[LegacyNetwork::OnPlayerConnect] sender=%s marked as omp, resetting omp version", rpcParams->sender.ToString());
		SAMPRakNet::SetPlayerOmpVersion(rpcParams->sender, 0);
	}

	IPlayer* newPeer = network->OnPeerConnect(rpcParams, false, serial, clientVersion, versionName, challengeResponse, playerName, false, true);
	if (!newPeer)
	{
		if (false) network->core->printLn("[LegacyNetwork::OnPlayerConnect] OnPeerConnect failed for sender=%s (RPC rejection already sent)", rpcParams->sender.ToString());
		return;
	}

	if (!network->inEventDispatcher.stopAtFalse(
			[newPeer, &bs](NetworkInEventHandler* handler)
			{
				bs.resetReadPointer();
				return handler->onReceiveRPC(*newPeer, NetCode::RPC::PlayerConnect::PacketID, bs);
			}))
	{
		return;
	}

	if (!network->rpcInEventDispatcher.stopAtFalse(
			NetCode::RPC::PlayerConnect::PacketID,
			[newPeer, &bs](SingleNetworkInEventHandler* handler)
			{
				bs.resetReadPointer();
				return handler->onReceive(*newPeer, bs);
			}))
	{
		return;
	}

	if (false) network->core->printLn(
		"[LegacyNetwork::OnPlayerConnect] Join complete sender=%s playerId=%d name=%.*s",
		rpcParams->sender.ToString(),
		newPeer->getID(),
		int(playerName.length()),
		playerName.data());
	network->networkEventDispatcher.dispatch(&NetworkEventHandler::onPeerConnect, *newPeer);
	network->playerRemoteSystem[newPeer->getID()] = remoteSystem;
	remoteSystem->isLogon = true;
}

void RakNetLegacyNetwork::OnNPCConnect(RakNet::RPCParameters* rpcParams, void* extra)
{
	RakNetLegacyNetwork* network = reinterpret_cast<RakNetLegacyNetwork*>(extra);
	RakNet::RakPeer::RemoteSystemStruct* remoteSystem = network->rakNetServer.GetRemoteSystemFromPlayerID(rpcParams->sender);

	if (!remoteSystem || remoteSystem->connectMode != RakNet::RakPeer::RemoteSystemStruct::ConnectMode::CONNECTED)
	{
		return;
	}

	if (remoteSystem->sampData.authType == SAMPRakNet::AuthType_NPC)
	{
		NetworkBitStream bs = GetBitStream(*rpcParams);
		NetCode::RPC::NPCConnect NPCConnectRPC;
		if (NPCConnectRPC.read(bs))
		{
			IPlayer* newPeer = network->OnPeerConnect(rpcParams, true, "", NPCConnectRPC.VersionNumber, "npc", NPCConnectRPC.ChallengeResponse, NPCConnectRPC.Name, false);
			if (newPeer)
			{
				if (!network->inEventDispatcher.stopAtFalse(
						[newPeer, &bs](NetworkInEventHandler* handler)
						{
							bs.resetReadPointer();
							return handler->onReceiveRPC(*newPeer, NetCode::RPC::NPCConnect::PacketID, bs);
						}))
				{
					return;
				}

				if (!network->rpcInEventDispatcher.stopAtFalse(
						NetCode::RPC::NPCConnect::PacketID,
						[newPeer, &bs](SingleNetworkInEventHandler* handler)
						{
							bs.resetReadPointer();
							return handler->onReceive(*newPeer, bs);
						}))
				{
					return;
				}

				network->networkEventDispatcher.dispatch(&NetworkEventHandler::onPeerConnect, *newPeer);
				remoteSystem->isLogon = true;
			}
		}
	}
}

void RakNetLegacyNetwork::OnRakNetDisconnect(RakNet::PlayerIndex rid, PeerDisconnectReason reason)
{
	IPlayer* player = playerFromRakIndex[rid];

	if (!player)
	{
		return;
	}

	playerFromRakIndex[rid] = nullptr;
	playerRemoteSystem[player->getID()] = nullptr;
	networkEventDispatcher.dispatch(&NetworkEventHandler::onPeerDisconnect, *player, reason);
}

void RakNetLegacyNetwork::OnRPC313(RakNet::RPCParameters* rpcParams, void* extra)
{
	RakNetLegacyNetwork* network = reinterpret_cast<RakNetLegacyNetwork*>(extra);
	if (network)
	{
		if (false) network->core->printLn(
			"[LegacyNetwork::OnRPC313] sender=%s senderIndex=%u bits=%u extra=%p",
			rpcParams ? rpcParams->sender.ToString() : "<null>",
			rpcParams ? unsigned(rpcParams->senderIndex) : 0u,
			rpcParams ? unsigned(rpcParams->numberOfBitsOfData) : 0u,
			extra);
		network->DispatchRPCById(313, rpcParams, extra);
	}
}

void RakNetLegacyNetwork::OnRPC321(RakNet::RPCParameters* rpcParams, void* extra)
{
	RakNetLegacyNetwork* network = reinterpret_cast<RakNetLegacyNetwork*>(extra);
	if (network)
	{
		if (false) network->core->printLn(
			"[LegacyNetwork::OnRPC321] sender=%s senderIndex=%u bits=%u extra=%p",
			rpcParams ? rpcParams->sender.ToString() : "<null>",
			rpcParams ? unsigned(rpcParams->senderIndex) : 0u,
			rpcParams ? unsigned(rpcParams->numberOfBitsOfData) : 0u,
			extra);
		network->DispatchRPCById(321, rpcParams, extra);
	}
}

void RakNetLegacyNetwork::OnRPC371(RakNet::RPCParameters* rpcParams, void* extra)
{
	RakNetLegacyNetwork* network = reinterpret_cast<RakNetLegacyNetwork*>(extra);
	if (network)
	{
		if (false) network->core->printLn(
			"[LegacyNetwork::OnRPC371] sender=%s senderIndex=%u bits=%u extra=%p",
			rpcParams ? rpcParams->sender.ToString() : "<null>",
			rpcParams ? unsigned(rpcParams->senderIndex) : 0u,
			rpcParams ? unsigned(rpcParams->numberOfBitsOfData) : 0u,
			extra);
		network->DispatchRPCById(371, rpcParams, extra);
	}
}

void RakNetLegacyNetwork::DispatchRPCById(size_t id, RakNet::RPCParameters* rpcParams, void* extra)
{
	RakNetLegacyNetwork* network = reinterpret_cast<RakNetLegacyNetwork*>(extra);
	if (!network || !rpcParams)
	{
		return;
	}

	const RakNet::PlayerIndex senderId = rpcParams->senderIndex;
	if (false) network->core->printLn(
		"[LegacyNetwork::DispatchRPCById] enter rpc=%zu sender=%s senderIndex=%u bits=%u extra=%p playerMapSize=%u",
		id,
		rpcParams->sender.ToString(),
		unsigned(senderId),
		unsigned(rpcParams->numberOfBitsOfData),
		extra,
		unsigned(network->playerFromRakIndex.size()));

	if (senderId >= network->playerFromRakIndex.size())
	{
		if (false) network->core->printLn(
			"[LegacyNetwork::DispatchRPCById] drop rpc=%zu sender=%s reason=senderIndex_out_of_range senderIndex=%u playerMapSize=%u",
			id,
			rpcParams->sender.ToString(),
			unsigned(senderId),
			unsigned(network->playerFromRakIndex.size()));
		return;
	}

	IPlayer* player = network->playerFromRakIndex[senderId];
	if (player == nullptr)
	{
		if (false) network->core->printLn(
			"[LegacyNetwork::DispatchRPCById] drop rpc=%zu sender=%s reason=null_player_mapping senderIndex=%u",
			id,
			rpcParams->sender.ToString(),
			unsigned(senderId));
		return;
	}

	NetworkBitStream bs = GetBitStream(*rpcParams);
	if (false) network->core->printLn(
		"[LegacyNetwork::DispatchRPCById] rpc=%zu peer=%.*s unreadBits=%d readOffset=%d globalHandlers=%u rpcHandlers=%u",
		id,
		PRINT_VIEW(player->getName()),
		bs.GetNumberOfUnreadBits(),
		bs.GetReadOffset(),
		unsigned(network->inEventDispatcher.count()),
		unsigned(network->rpcInEventDispatcher.count(int(id))));

	const bool globalRes = network->inEventDispatcher.stopAtFalse(
		[&player, &bs, id](NetworkInEventHandler* handler)
		{
			bs.resetReadPointer();
			return handler->onReceiveRPC(*player, int(id), bs);
		});
	if (false) network->core->printLn(
		"[LegacyNetwork::DispatchRPCById] rpc=%zu afterGlobal result=%d unreadBits=%d readOffset=%d",
		id,
		int(globalRes),
		bs.GetNumberOfUnreadBits(),
		bs.GetReadOffset());
	if (!globalRes)
	{
		return;
	}

	const bool rpcRes = network->rpcInEventDispatcher.stopAtFalse(
		int(id),
		[&player, &bs](SingleNetworkInEventHandler* handler)
		{
			bs.resetReadPointer();
			return handler->onReceive(*player, bs);
		});
	if (false) network->core->printLn(
		"[LegacyNetwork::DispatchRPCById] rpc=%zu afterPerRpc result=%d unreadBits=%d readOffset=%d",
		id,
		int(rpcRes),
		bs.GetNumberOfUnreadBits(),
		bs.GetReadOffset());
}

template <size_t ID>
void RakNetLegacyNetwork::RPCHook(RakNet::RPCParameters* rpcParams, void* extra)
{
	RakNetLegacyNetwork* network = reinterpret_cast<RakNetLegacyNetwork*>(extra);
	const RakNet::PlayerIndex senderId = rpcParams->senderIndex;

	if constexpr (ID == 50 || ID == 101)
	{
		if (false) network->core->printLn(
			"[LegacyNetwork::RPCHook] enter rpc=%zu sender=%s senderIndex=%u bits=%u extra=%p playerMapSize=%u",
			size_t(ID),
			rpcParams->sender.ToString(),
			unsigned(senderId),
			unsigned(rpcParams->numberOfBitsOfData),
			extra,
			unsigned(network->playerFromRakIndex.size()));
	}

	if (senderId >= network->playerFromRakIndex.size())
	{
		if constexpr (ID == 50 || ID == 101)
		{
			if (false) network->core->printLn(
				"[LegacyNetwork::RPCHook] drop rpc=%zu sender=%s reason=senderIndex_out_of_range senderIndex=%u playerMapSize=%u",
				size_t(ID),
				rpcParams->sender.ToString(),
				unsigned(senderId),
				unsigned(network->playerFromRakIndex.size()));
		}
		return;
	}

	IPlayer* player = network->playerFromRakIndex[senderId];

	if (player == nullptr)
	{
		if constexpr (ID == 50 || ID == 101)
		{
			if (false) network->core->printLn(
				"[LegacyNetwork::RPCHook] drop rpc=%zu sender=%s reason=null_player_mapping senderIndex=%u",
				size_t(ID),
				rpcParams->sender.ToString(),
				unsigned(senderId));
		}
		return;
	}

	NetworkBitStream bs = GetBitStream(*rpcParams);
	// RakPeer has already converted the BR 9-bit wire ID to the standard
	// open.mp/SA-MP 8-bit RPC ID.  Translating it a second time produced IDs
	// such as 394 and indexed the 256-entry dispatcher out of bounds.
	const int translatedID = int(ID);

	if constexpr (ID == 50 || ID == 101)
	{
		if (false) network->core->printLn(
			"[LegacyNetwork::RPCHook] rpc=%zu peer=%.*s unreadBits=%d readOffset=%d globalHandlers=%u rpcHandlers=%u",
			size_t(ID),
			PRINT_VIEW(player->getName()),
			bs.GetNumberOfUnreadBits(),
			bs.GetReadOffset(),
			unsigned(network->inEventDispatcher.count()),
			unsigned(network->rpcInEventDispatcher.count(ID)));
	}

	const bool globalRes = network->inEventDispatcher.stopAtFalse(
			[&player, &bs, translatedID](NetworkInEventHandler* handler)
			{
				bs.resetReadPointer();
				return handler->onReceiveRPC(*player, translatedID, bs);
			});
	if constexpr (ID == 50 || ID == 101)
	{
		if (false) network->core->printLn(
			"[LegacyNetwork::RPCHook] rpc=%zu afterGlobal result=%d unreadBits=%d readOffset=%d",
			size_t(ID),
			int(globalRes),
			bs.GetNumberOfUnreadBits(),
			bs.GetReadOffset());
	}
	if (!globalRes)
	{
		return;
	}

	const bool rpcRes = network->rpcInEventDispatcher.stopAtFalse(
			translatedID,
			[&player, &bs](SingleNetworkInEventHandler* handler)
			{
				bs.resetReadPointer();
				return handler->onReceive(*player, bs);
			});
	if constexpr (ID == 50 || ID == 101)
	{
		if (false) network->core->printLn(
			"[LegacyNetwork::RPCHook] rpc=%zu afterPerRpc result=%d unreadBits=%d readOffset=%d",
			size_t(ID),
			int(rpcRes),
			bs.GetNumberOfUnreadBits(),
			bs.GetReadOffset());
	}
	if (!rpcRes)
	{
		return;
	}
#ifdef _DEBUG
	if (network->inEventDispatcher.count() == 0 && network->rpcInEventDispatcher.count(ID) == 0)
	{
		network->core->logLn(LogLevel::Debug, "Received unprocessed RPC %zu", ID);
	}
#endif
}

void RakNetLegacyNetwork::synchronizeBans()
{
	char addr[22] = { 0 };
	unsigned short port;
	for (IPlayer* player : core->getPlayers().entries())
	{
		const PeerNetworkData& netData = player->getNetworkData();
		if (netData.network != this)
		{
			continue;
		}

		const PeerNetworkData::NetworkID& nid = netData.networkID;
		const RakNet::PlayerID rid { unsigned(nid.address.v4), nid.port };
		rakNetServer.GetPlayerIPFromID(rid, addr, &port);
		if (rakNetServer.IsBanned(addr))
		{
			player->kick();
		}
	}
}

void RakNetLegacyNetwork::ban(const BanEntry& entry, Milliseconds expire)
{
	// Only support ipv4
	if (entry.address != StringView("127.0.0.1"))
	{
		rakNetServer.AddToBanList(entry.address.data(), expire.count());
		synchronizeBans();
	}
}

void RakNetLegacyNetwork::unban(const BanEntry& entry)
{
	rakNetServer.RemoveFromBanList(entry.address.data());
}

NetworkStats RakNetLegacyNetwork::getStatistics(IPlayer* player)
{
	NetworkStats stats = { 0 };
	RakNet::PlayerID playerID;

	if (player == nullptr)
	{
		playerID = RakNet::UNASSIGNED_PLAYER_ID;
	}
	else
	{
		const PeerNetworkData& netData = player->getNetworkData();

		// Return empty statistics structure if player is not connected to this network
		if (netData.network != this)
		{
			return stats;
		}
		else
		{
			const PeerNetworkData::NetworkID& nid = netData.networkID;
			playerID = { unsigned(nid.address.v4), nid.port };
		}
	}

	RakNet::RakNetStatisticsStruct* raknetStats = rakNetServer.GetStatistics(playerID);

	// Return empty statistics structure if raknet failed to provide statistics
	if (raknetStats == nullptr)
	{
		return stats;
	}

	RakNet::RakNetTime time = RakNet::GetTime();

	stats.connectionStartTime = raknetStats->connectionStartTime;
	stats.connectionElapsedTime = time - raknetStats->connectionStartTime;

	double elapsedTime = stats.connectionElapsedTime / 1000.0f;

	stats.messageSendBuffer
		= raknetStats->messageSendBuffer[RakNet::SYSTEM_PRIORITY] + raknetStats->messageSendBuffer[RakNet::HIGH_PRIORITY] + raknetStats->messageSendBuffer[RakNet::MEDIUM_PRIORITY] + raknetStats->messageSendBuffer[RakNet::LOW_PRIORITY];

	stats.messagesSent
		= raknetStats->messagesSent[RakNet::SYSTEM_PRIORITY] + raknetStats->messagesSent[RakNet::HIGH_PRIORITY] + raknetStats->messagesSent[RakNet::MEDIUM_PRIORITY] + raknetStats->messagesSent[RakNet::LOW_PRIORITY];

	stats.totalBytesSent = BITS_TO_BYTES(raknetStats->totalBitsSent);
	stats.acknowlegementsSent = raknetStats->acknowlegementsSent;
	stats.acknowlegementsPending = raknetStats->acknowlegementsPending;
	stats.messagesOnResendQueue = raknetStats->messagesOnResendQueue;
	stats.messageResends = raknetStats->messageResends;
	stats.messagesTotalBytesResent = BITS_TO_BYTES(raknetStats->messagesTotalBitsResent);

	if (raknetStats->totalBitsSent)
		stats.packetloss = 100.0f * raknetStats->messagesTotalBitsResent / raknetStats->totalBitsSent;
	else
		stats.packetloss = 0.0f;

	stats.messagesReceived
		= raknetStats->duplicateMessagesReceived + raknetStats->invalidMessagesReceived + raknetStats->messagesReceived;

	stats.messagesReceivedPerSecond = stats.messagesReceived - raknetStats->perSecondReceivedMsgCount;
	stats.bytesReceived = BITS_TO_BYTES(raknetStats->bitsReceived + raknetStats->bitsWithBadCRCReceived);
	stats.acknowlegementsReceived = raknetStats->acknowlegementsReceived;
	stats.duplicateAcknowlegementsReceived = raknetStats->duplicateAcknowlegementsReceived;
	stats.bitsPerSecond = raknetStats->bitsPerSecond;
	stats.bpsSent = static_cast<double>(raknetStats->totalBitsSent) / elapsedTime;
	stats.bpsReceived = static_cast<double>(raknetStats->bitsReceived) / elapsedTime;

	stats.isActive = false;
	stats.connectMode = 0;

	if (playerID != RakNet::UNASSIGNED_PLAYER_ID)
	{
		RakNet::RakPeer::RemoteSystemStruct* remoteSystem = rakNetServer.GetRemoteSystemFromPlayerID(playerID);

		if (remoteSystem)
		{
			stats.isActive = remoteSystem->isActive;
			stats.connectMode = remoteSystem->connectMode;
		}
	}

	return stats;
}

void RakNetLegacyNetwork::update()
{
	IConfig& config = core->getConfig();

	cookieSeedTime = Milliseconds(*config.getInt("network.cookie_reseed_time"));

	SAMPRakNet::SetTimeout(*config.getInt("network.player_timeout"));
	SAMPRakNet::SetMinConnectionTime(*config.getInt("network.minimum_connection_time"));
	SAMPRakNet::SetMessagesLimit(*config.getInt("network.messages_limit"));
	SAMPRakNet::SetMessageHoleLimit(*config.getInt("network.message_hole_limit"));
	SAMPRakNet::SetAcksLimit(*config.getInt("network.acks_limit"));
	SAMPRakNet::SetNetworkLimitsBanTime(*config.getInt("network.limits_ban_time"));

	SAMPRakNet::SetLogCookies(*config.getBool("logging.log_cookies"));

	query.setLogQueries(*config.getBool("logging.log_queries"));
	if (*config.getBool("enable_query"))
	{
		SAMPRakNet::SetQuery(&query);
	}

	StringView hostName = config.getString("name");
	if (!hostName.empty())
	{
		query.setServerName(hostName);
	}

	query.setRuleValue<false>("lagcomp", (*config.getInt("game.lag_compensation_mode") != LagCompMode_Disabled) ? "On" : "Off");

	StringView language = config.getString("language");
	if (!language.empty())
	{
		query.setLanguage(String(language));
	}

	StringView modeName = config.getString("game.mode");
	if (!modeName.empty())
	{
		query.setGameModeName(modeName);
	}

	StringView mapName = config.getString("game.map");
	if (!mapName.empty())
	{
		query.setRuleValue<false>("mapname", String(mapName));
	}
	else
	{
		query.setRuleValue<false>("mapname", "San Andreas");
	}

	query.setRuleValue<false>("weather", std::to_string(*config.getInt("game.weather")));

	StringView website = config.getString("website");
	if (!website.empty())
	{
		query.setRuleValue<false>("weburl", String(website));
	}

	StringView discordLink = config.getString("discord.invite");
	if (!discordLink.empty())
	{
		query.setDiscordLink(discordLink);
	}

	StringView bannerUrl = config.getString("banners.light");
	if (!bannerUrl.empty())
	{
		query.setLightBannerUrl(bannerUrl);
	}

	bannerUrl = config.getString("banners.dark");
	if (!bannerUrl.empty())
	{
		query.setDarkBannerUrl(bannerUrl);
	}

	StringView logoUrl = config.getString("logo");
	if (!logoUrl.empty())
	{
		query.setLogoUrl(logoUrl);
	}

	query.setRuleValue<false>("worldtime", String(std::to_string(*config.getInt("game.time")) + ":00"));

	StringView rconPassword = config.getString("rcon.password");
	query.setRconPassword(rconPassword);
	query.setRconEnabled(*config.getBool("rcon.enable"));

	StringView password = config.getString("password");
	query.setPassworded(!password.empty());
	rakNetServer.SetPassword(password.empty() ? 0 : password.data());

	query.buildConfigDependentBuffers();

	int mtu = *config.getInt("network.mtu");

	static const auto maxMTU = *core->getConfig().getBool("network.allow_037_clients") ? MAX_MTU_037 : MAX_MTU_DL;

	// Check if provided MTU is larger than the maximum allowed size for current targeted client(s).
	// Example: 0.3.7 clients have a maximum MTU of 576 bytes, while 0.3DL clients have a maximum MTU of 1500 bytes.
	// If that is the case, we will log a warning and set the MTU to the maximum allowed size so client won't experience packet loss/disconnects.
	if (mtu > maxMTU)
	{
		core->logLn(LogLevel::Warning, "MTU %d is larger than the maximum allowed size %d for current targeted client(s).", mtu, maxMTU);
		mtu = maxMTU;
	}

	rakNetServer.SetMTUSize(mtu);
}

void RakNetLegacyNetwork::init(ICore* c)
{
	core = c;

	core->getEventDispatcher().addEventHandler(this);
	core->getPlayers().getPlayerChangeDispatcher().addEventHandler(this);
	core->getPlayers().getPlayerConnectDispatcher().addEventHandler(this, EventPriority_Lowest);
}

void RakNetLegacyNetwork::start()
{
	SAMPRakNet::Init(core);
	SAMPRakNet::SeedToken();
	lastCookieSeed = Time::now();
	SAMPRakNet::SeedCookie();

	playerFromRakIndex.fill(nullptr);

	IConfig& config = core->getConfig();
	int maxPlayers = *config.getInt("max_players");
	int minimumSendBPS = *config.getFloat("network.minimum_send_bits_per_second");

	int port = *config.getInt("network.port");
	int sleep = static_cast<int>(*config.getFloat("sleep"));
	StringView bind = config.getString("network.bind");

	bool* artwork_config = config.getBool("artwork.enable");
	bool artwork = !artwork_config ? false : *artwork_config;
	bool allow037 = *config.getBool("network.allow_037_clients");

	SAMPRakNet::SetMinimumSendBitsPerSecond(minimumSendBPS); // Default: 96 kbps  (~12 KB/s)

	query.setCore(core);

	std::stringstream version;
	version << "omp " << OMP_VERSION_MAJOR << "." << OMP_VERSION_MINOR << "." << OMP_VERSION_PATCH << "." << BUILD_NUMBER;
	query.setRuleValue<false>("version", version.str());
	// Send as a rule to announce which clients are allowed to join
	query.setRuleValue<false>("allowed_clients", !allow037 ? "0.3.DL" : "0.3.7, 0.3.DL");

	query.setRuleValue<false>("artwork", artwork ? "Yes" : "No");

	query.setMaxPlayers(maxPlayers);
	query.buildPlayerDependentBuffers();

	update();

	for (size_t i = 0; i < config.getBansCount(); ++i)
	{
		ban(config.getBan(i));
	}

	if (!rakNetServer.Start(maxPlayers, 0, sleep, port, bind.data()))
	{
		if (!bind.empty())
		{
			core->logLn(LogLevel::Error, "Unable to start legacy network on %.*s:%d. Port in use?", PRINT_VIEW(bind), port);
		}
		else
		{
			core->logLn(LogLevel::Error, "Unable to start legacy network on port %d. Port in use?", port);
		}
	}
	else
	{
		if (!bind.empty())
		{
			core->logLn(LogLevel::Message, "Legacy Network started on %.*s:%d.", PRINT_VIEW(bind), port);
		}
		else
		{
			core->logLn(LogLevel::Message, "Legacy Network started on port %d", port);
		}

		// Do the request after network is started.
		if (*config.getBool("announce"))
		{
			const String get = "https://api.open.mp/0.3.7/announce/" + std::to_string(port);
			core->requestHTTP4(new AnnounceHTTPResponseHandler(core), HTTPRequestType::HTTPRequestType_Get, get.data());
		}
	}

	rakNetServer.StartOccasionalPing();
	SAMPRakNet::SetPort(port);

	int* gracePeriod = config.getInt("network.grace_period");

	if (gracePeriod)
	{
		SAMPRakNet::SetGracePeriod(*gracePeriod);
	}

	// Set reserved slots based on NPC count once more because slots reserved
	// Before RakServer::Start are reset because RakPeer::Start calls RakPeer::Disconnect
	// As well which resets the value for RakPeer::reservedSlots class member.
	// Note: this behavior does not affect slots reserved in next executions.
	if (npcComponent)
	{
		rakNetServer.ReserveSlots(npcComponent->count());
	}
}

static bool ValidateBazeSyncBody(uint8_t type, unsigned int unreadBits)
{
	// Exact client -> server bodies from samp_server.cpp / BR structs.
	switch (type)
	{
	case RakNet::ID_PLAYER_SYNC:
		return unreadBits == 70u * 8u || // base BR on-foot body
			unreadBits == 71u * 8u ||    // 0x07 marker + base body (1271)
			unreadBits == 72u * 8u;      // base body + 2 state bytes (1362)
	case RakNet::ID_VEHICLE_SYNC: return unreadBits == 65u * 8u;
	case RakNet::ID_PASSENGER_SYNC: return unreadBits == 26u * 8u;
	case RakNet::ID_AIM_SYNC: return unreadBits == 31u * 8u;
	case RakNet::ID_BULLET_SYNC: return unreadBits == 40u * 8u;
	case RakNet::ID_UNOCCUPIED_SYNC: return unreadBits == 67u * 8u;
	case RakNet::ID_TRAILER_SYNC: return unreadBits == 54u * 8u;
	case RakNet::ID_SPECTATOR_SYNC: return unreadBits == 18u * 8u;
	case RakNet::ID_STATS_UPDATE:
		return unreadBits == 8u * 8u || unreadBits == 12u * 8u;
	case RakNet::ID_WEAPONS_UPDATE: return unreadBits >= 4u * 8u && unreadBits <= 49u * 8u;
	default: return true;
	}
}

void RakNetLegacyNetwork::onTick(Microseconds elapsed, TimePoint now)
{
	for (RakNet::Packet* pkt = rakNetServer.Receive(); pkt; pkt = rakNetServer.Receive())
	{
		if (pkt->playerIndex >= playerFromRakIndex.size())
		{
			rakNetServer.DeallocatePacket(pkt);
			continue;
		}

		IPlayer* player = playerFromRakIndex[pkt->playerIndex];

		// We shouldn't be needing this, it's only here IF somehow this is happening again
		// So users can report it to us
		if (player && player->getID() == -1)
		{
			rakNetServer.Kick(pkt->playerId);
			playerFromRakIndex[pkt->playerIndex] = nullptr;
			core->logLn(LogLevel::Warning, "RakNet player %d with open.mp player pool id -1  was found and deleted. Packet ID: %d", pkt->playerIndex, pkt->data[0]);
			core->logLn(LogLevel::Warning, "Please contact us by creating an issue in our repository at https://github.com/openmultiplayer/open.mp");
			rakNetServer.DeallocatePacket(pkt);
			continue;
		}

		if (player)
		{
			const unsigned int bits = pkt->bitSize;
			NetworkBitStream bs(pkt->data, bitsToBytes(bits), false);
			bs.SetWriteOffset(bits);
			uint8_t type;
			if (bs.readUINT8(type))
			{
				if (player->getClientVersionName() == StringView("baze") &&
					!ValidateBazeSyncBody(type, unsigned(bs.GetNumberOfUnreadBits())))
				{
					if (false) core->logLn(LogLevel::Warning,
						"[LegacyNetwork] Dropped malformed BR sync id=%u bits=%u player=%.*s",
						unsigned(type), unsigned(bs.GetNumberOfUnreadBits()), PRINT_VIEW(player->getName()));
					rakNetServer.DeallocatePacket(pkt);
					continue;
				}
				if (type == RakNet::ID_VEHICLE_SYNC &&
					bs.GetNumberOfUnreadBits() == BazeVehicleSyncBodySize * 8 &&
					player->getID() >= 0 && player->getID() < PLAYER_POOL_SIZE)
				{
					std::memcpy(bazeVehicleSyncRaw[player->getID()], pkt->data + 1, BazeVehicleSyncBodySize);
					bazeVehicleSyncRawValid[player->getID()] = true;
				}
				const uint8_t translatedType = TranslateLegacyPacketID(type);

				// Call event handlers for packet receive
				const bool isBazeGUI = player->getClientVersionName() == StringView("baze") &&
					type == RakNet::ID_USER_INTERFACE_SYNC;

				// Always invoke the normal global packet handlers first. Pawn IPacket:1
				// depends on receiving this packet. For BR GUI packets, continue to the
				// dedicated Dialogs handler even when a Pawn/global handler returns 0.
				const bool globalRes = inEventDispatcher.stopAtFalse([&player, translatedType, &bs](NetworkInEventHandler* handler)
					{
						bs.SetReadOffset(8); // Ignore packet ID
						return handler->onReceivePacket(*player, translatedType, bs);
					});
				const bool res = globalRes || isBazeGUI;

				if (res)
				{
					packetInEventDispatcher.stopAtFalse(translatedType, [&player, &bs](SingleNetworkInEventHandler* handler)
						{
							bs.SetReadOffset(8); // Ignore packet ID
							return handler->onReceive(*player, bs);
						});
				}

				if (type == RakNet::ID_DISCONNECTION_NOTIFICATION)
				{
					OnRakNetDisconnect(pkt->playerIndex, PeerDisconnectReason_Quit);
				}
				else if (type == RakNet::ID_CONNECTION_LOST)
				{
					OnRakNetDisconnect(pkt->playerIndex, PeerDisconnectReason_Timeout);
				}
			}
		}

		rakNetServer.DeallocatePacket(pkt);
	}

	if (now - lastCookieSeed > cookieSeedTime)
	{
		SAMPRakNet::SeedCookie();
		lastCookieSeed = now;
	}
}
