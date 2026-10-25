/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

#pragma once

#include "../Query/detail/unit_33dc8b31a1.hpp"
#include <Impl/network_impl.hpp>
#include "../../../../Shared/Network/detail/unit_8743113f8b.hpp"
#include "../../../../Shared/NetCode/detail/unit_f6f1de6138.hpp"
#include "../../../../Shared/NetCode/detail/unit_4c18dc97b3.hpp"
#include <glm/glm.hpp>
#include <cstring>
#include <map>
#include <network.hpp>
#include "../../../../RakNet/Include/raknet/BitStream.h"
#include "../../../../RakNet/Include/raknet/GetTime.h"
#include "../../../../RakNet/Include/raknet/RakNetworkFactory.h"
#include "../../../../RakNet/Include/raknet/RakServerInterface.h"
#include "../../../../RakNet/Include/raknet/StringCompressor.h"
#include <Server/Components/NPCs/npcs.hpp>
#include <vector>

using namespace Impl;

#define MAGNITUDE_EPSILON 0.00001f

#define MAX_MTU_037 576
#define MAX_MTU_DL MAXIMUM_MTU_SIZE

static const StaticArray<StringView, 2> ProtectedRules = {
	"version", "allowed_clients"
};

class Core;

class RakNetLegacyNetwork final : public Network, public CoreEventHandler, public PlayerConnectEventHandler, public PlayerChangeEventHandler, public INetworkQueryExtension, public PoolEventHandler<INPC>
{
private:
	ICore* core = nullptr;
	Query query;
	RakNet::RakServerInterface& rakNetServer;
	StaticArray<IPlayer*, PLAYER_POOL_SIZE> playerFromRakIndex;
	StaticArray<RakNet::RakPeer::RemoteSystemStruct*, PLAYER_POOL_SIZE> playerRemoteSystem;
	Milliseconds cookieSeedTime;
	TimePoint lastCookieSeed;
	INPCComponent* npcComponent = nullptr;
	static constexpr size_t BazeVehicleSyncBodySize = 65;
	uint8_t bazeVehicleSyncRaw[PLAYER_POOL_SIZE][BazeVehicleSyncBodySize] {};
	bool bazeVehicleSyncRawValid[PLAYER_POOL_SIZE] {};

	static bool writeExactBazeVehicleSync(NetworkBitStream& out, uint16_t playerID, const uint8_t* body)
	{
		NetworkBitStream in(const_cast<uint8_t*>(body), BazeVehicleSyncBodySize, false);
		in.SetWriteOffset(BazeVehicleSyncBodySize * 8);
		uint16_t vehicleID = 0, leftRight = 0, upDown = 0, keys = 0;
		float qw = 1.0f, qx = 0.0f, qy = 0.0f, qz = 0.0f;
		Vector3 position {}, velocity {};
		float carHealth = 0.0f;
		uint16_t health = 0, armour = 0, trailerID = 0;
		uint8_t weapon = 0, siren = 0, landingGear = 0;
		int16_t rightLR = 0, rightUD = 0;
		if (!in.readUINT16(vehicleID) || !in.readUINT16(leftRight) ||
			!in.readUINT16(upDown) || !in.readUINT16(keys) ||
			!in.readFLOAT(qw) || !in.readFLOAT(qx) || !in.readFLOAT(qy) || !in.readFLOAT(qz) ||
			!in.readVEC3(position) || !in.readVEC3(velocity) || !in.readFLOAT(carHealth) ||
			!in.readUINT16(health) || !in.readUINT16(armour) || !in.readUINT8(weapon) ||
			!in.readUINT8(siren) || !in.readUINT8(landingGear) || !in.readUINT16(trailerID) ||
			!in.readINT16(rightLR) || !in.readINT16(rightUD))
			return false;

		const float norm2 = qw * qw + qx * qx + qy * qy + qz * qz;
		if (!std::isfinite(norm2) || norm2 < 0.00001f)
		{
			qw = 1.0f; qx = qy = qz = 0.0f;
		}
		else
		{
			const float invNorm = 1.0f / std::sqrt(norm2);
			qw *= invNorm; qx *= invNorm; qy *= invNorm; qz *= invNorm;
		}
		if (!std::isfinite(carHealth)) carHealth = 0.0f;
		carHealth = std::max(0.0f, std::min(65535.0f, carHealth));

		out.writeUINT8(0x03); // BR ID_VEHICLE_SYNC
		out.writeUINT16(playerID);
		out.writeUINT16(vehicleID);
		out.writeUINT16(leftRight);
		out.writeUINT16(upDown);
		out.writeUINT16(keys);
		out.writeGTAQuat(GTAQuat(qw, qx, qy, qz));
		out.writeVEC3(position);
		out.writeCompressedVEC3(velocity);
		out.writeUINT16(uint16_t(carHealth));
		out.writeUINT16(health);
		out.writeUINT16(armour);
		out.writeUINT8(weapon & 0x3F);
		out.writeBIT(siren != 0);
		out.writeBIT(landingGear != 0);
		const bool hasRightStick = rightLR != 0 || rightUD != 0;
		out.writeBIT(hasRightStick);
		if (hasRightStick)
		{
			out.writeINT16(rightLR);
			out.writeINT16(rightUD);
		}
		out.writeBIT(trailerID != 0);
		if (trailerID != 0) out.writeUINT16(trailerID);
		return true;
	}

	static inline char normalizeOrderingChannelForLegacyClient(int channel)
	{
		if (channel < 0)
		{
			return 0;
		}
		return static_cast<char>(channel & 0x0F);
	}

public:
	inline void setNPCComponent(INPCComponent* comp)
	{
		npcComponent = comp;

		if (npcComponent)
		{
			npcComponent->getPoolEventDispatcher().addEventHandler(this);
		}
	}

	inline INPCComponent* getNPCComponent()
	{
		return npcComponent;
	}

	inline void setQueryConsole(IConsoleComponent* console)
	{
		query.setConsole(console);
	}

	inline IConsoleComponent* getQueryConsole() const
	{
		return query.getConsole();
	}

	RakNetLegacyNetwork();
	~RakNetLegacyNetwork();

	IExtension* getExtension(UID id) override
	{
		if (id == INetworkQueryExtension::ExtensionIID)
		{
			return static_cast<INetworkQueryExtension*>(this);
		}
		return nullptr;
	}

	ENetworkType getNetworkType() const override
	{
		return ENetworkType_RakNetLegacy;
	}

	void disconnect(const IPlayer& peer) override
	{
		const PeerNetworkData& netData = peer.getNetworkData();
		if (netData.network != this)
		{
			return;
		}

		const PeerNetworkData::NetworkID& nid = netData.networkID;
		const RakNet::PlayerID rid { unsigned(nid.address.v4), nid.port };

		const int playerIndex = rakNetServer.GetIndexFromPlayerID(rid);
		if (playerIndex >= 0 && playerIndex < PLAYER_POOL_SIZE)
		{
			playerFromRakIndex[playerIndex] = nullptr;
		}
		playerRemoteSystem[peer.getID()] = nullptr;
		rakNetServer.Kick(rid);
	}

	bool broadcastPacket(Span<uint8_t> data, int channel, const IPlayer* exceptPeer, bool dispatchEvents) override
	{
		// We want exact bits - set the write offset with bit granularity
		NetworkBitStream bs(data.data(), bitsToBytes(data.size()), false /* copyData */);
		bs.SetWriteOffset(data.size());

		if (dispatchEvents)
		{
			uint8_t type;
			if (bs.readUINT8(type))
			{
				if (!outEventDispatcher.stopAtFalse([type, &bs](NetworkOutEventHandler* handler)
						{
							bs.SetReadOffset(8); // Ignore packet ID
							return handler->onSendPacket(nullptr, type, bs);
						}))
				{
					return false;
				}

				if (!packetOutEventDispatcher.stopAtFalse(type, [&bs](SingleNetworkOutEventHandler* handler)
						{
							bs.SetReadOffset(8); // Ignore packet ID
							return handler->onSend(nullptr, bs);
						}))
				{
					return false;
				}
			}
		}

		const char rakOrderingChannel = normalizeOrderingChannelForLegacyClient(channel);
		const RakNet::PacketReliability reliability = RakNet::RELIABLE;
		if (exceptPeer)
		{
			const PeerNetworkData& netData = exceptPeer->getNetworkData();
			if (netData.network == this)
			{
				const PeerNetworkData::NetworkID& nid = netData.networkID;
				const RakNet::PlayerID rid { unsigned(nid.address.v4), nid.port };
				return rakNetServer.Send((const char*)bs.GetData(), bs.GetNumberOfBitsUsed(), RakNet::HIGH_PRIORITY, reliability, rakOrderingChannel, rid, true);
			}
		}

		return rakNetServer.Send((const char*)bs.GetData(), bs.GetNumberOfBitsUsed(), RakNet::HIGH_PRIORITY, reliability, rakOrderingChannel, RakNet::UNASSIGNED_PLAYER_ID, true);
	}

	bool sendPacket(IPlayer& peer, Span<uint8_t> data, int channel, bool dispatchEvents) override
	{
		const PeerNetworkData& netData = peer.getNetworkData();
		if (netData.network != this)
		{
			return false;
		}

		// We want exact bits - set the write offset with bit granularity
		NetworkBitStream bs(data.data(), bitsToBytes(data.size()), false /* copyData */);
		bs.SetWriteOffset(data.size());

		if (dispatchEvents)
		{
			uint8_t type;
			if (bs.readUINT8(type))
			{
				if (!outEventDispatcher.stopAtFalse([&peer, type, &bs](NetworkOutEventHandler* handler)
						{
							bs.SetReadOffset(8); // Ignore packet ID
							return handler->onSendPacket(&peer, type, bs);
						}))
				{
					return false;
				}

				if (!packetOutEventDispatcher.stopAtFalse(type, [&peer, &bs](SingleNetworkOutEventHandler* handler)
						{
							bs.SetReadOffset(8); // Ignore packet ID
							return handler->onSend(&peer, bs);
						}))
				{
					return false;
				}
			}
		}

		const PeerNetworkData::NetworkID& nid = netData.networkID;
		const RakNet::PlayerID rid { unsigned(nid.address.v4), nid.port };
		const char rakOrderingChannel = normalizeOrderingChannelForLegacyClient(channel);
		const RakNet::PacketReliability reliability = (channel == OrderingChannel_Reliable) ? RakNet::RELIABLE : RakNet::UNRELIABLE;

		if (peer.getClientVersionName() == StringView("baze"))
		{
			NetworkBitStream compatBS;
			NetworkBitStream readBS(data.data(), bitsToBytes(data.size()), false /* copyData */);
			readBS.SetWriteOffset(data.size());

			uint8_t packetID = 0;
			if (readBS.readUINT8(packetID))
			{
				bool converted = false;
				switch (packetID)
				{
				case NetCode::Packet::PlayerFootSync::PacketID:
				{
					NetCode::Packet::PlayerFootSync packet;
					if (readBS.readUINT16(packet.PlayerID) && packet.read(readBS))
					{
						packet.writeLegacyBazeCompat(compatBS);
						compatBS.GetData()[0] = translateLegacyOutgoingPacketIDForPeer(peer, packetID);
						converted = true;
					}
					break;
				}
				case NetCode::Packet::PlayerVehicleSync::PacketID:
				{
					NetCode::Packet::PlayerVehicleSync packet;
					if (readBS.readUINT16(packet.PlayerID))
					{
						const int sourceID = packet.PlayerID;
						if (sourceID >= 0 && sourceID < PLAYER_POOL_SIZE && bazeVehicleSyncRawValid[sourceID])
						{
							converted = writeExactBazeVehicleSync(compatBS, uint16_t(sourceID), bazeVehicleSyncRaw[sourceID]);
						}
						else if (packet.read(readBS))
						{
							packet.writeLegacyBazeCompat(compatBS);
							compatBS.GetData()[0] = translateLegacyOutgoingPacketIDForPeer(peer, packetID);
							converted = true;
						}
					}
					break;
				}
				case NetCode::Packet::PlayerPassengerSync::PacketID:
				{
					NetCode::Packet::PlayerPassengerSync packet;
					if (readBS.readUINT16(packet.PlayerID) && packet.read(readBS))
					{
						packet.writeLegacyBazeCompat(compatBS);
						compatBS.GetData()[0] = translateLegacyOutgoingPacketIDForPeer(peer, packetID);
						converted = true;
					}
					break;
				}
				case NetCode::Packet::PlayerAimSync::PacketID:
				case NetCode::Packet::PlayerBulletSync::PacketID:
				case NetCode::Packet::PlayerUnoccupiedSync::PacketID:
				case NetCode::Packet::PlayerTrailerSync::PacketID:
				case NetCode::Packet::PlayerStatsSync::PacketID:
				case NetCode::Packet::PlayerSpectatorSync::PacketID:
				case NetCode::Packet::PlayerWeaponsUpdate::PacketID:
				case NetCode::Packet::PlayerMarkersSync::PacketID:
				{
					// These BR channels use the same raw body as open.mp; only the
					// one-byte packet ID differs. Preserve the exact bit count.
					compatBS.WriteBits(data.data(), data.size(), false);
					if (compatBS.GetNumberOfBitsUsed() >= 8)
					{
						compatBS.GetData()[0] = translateLegacyOutgoingPacketIDForPeer(peer, packetID);
						converted = true;
					}
					break;
				}
				default:
					break;
				}

				if (converted)
				{
					return rakNetServer.Send((const char*)compatBS.GetData(), compatBS.GetNumberOfBitsUsed(), RakNet::HIGH_PRIORITY, reliability, rakOrderingChannel, rid, false);
				}
			}

		}

		return rakNetServer.Send((const char*)bs.GetData(), bs.GetNumberOfBitsUsed(), RakNet::HIGH_PRIORITY, reliability, rakOrderingChannel, rid, false);
	}

	bool broadcastRPC(int id, Span<uint8_t> data, int channel, const IPlayer* exceptPeer, bool dispatchEvents) override
	{
		if (id == INVALID_PACKET_ID)
		{
			return false;
		}

		// We want exact bits - set the write offset with bit granularity
		NetworkBitStream bs(data.data(), bitsToBytes(data.size()), false /* copyData */);
		bs.SetWriteOffset(data.size());

		if (dispatchEvents)
		{
			if (!outEventDispatcher.stopAtFalse([id, &bs](NetworkOutEventHandler* handler)
					{
						bs.resetReadPointer();
						return handler->onSendRPC(nullptr, id, bs);
					}))
			{
				return false;
			}

			if (!rpcOutEventDispatcher.stopAtFalse(id, [&bs](SingleNetworkOutEventHandler* handler)
					{
						bs.resetReadPointer();
						return handler->onSend(nullptr, bs);
					}))
			{
				return false;
			}
		}

		bool sent = false;
		for (IPlayer* target : core->getPlayers().entries())
		{
			if (!target || (exceptPeer && target == exceptPeer) || target->getNetworkData().network != this)
			{
				continue;
			}

			sent = sendRPC(*target, id, data, channel, false) || sent;
		}

		return sent;
	}

	bool sendRPC(IPlayer& peer, int id, Span<uint8_t> data, int channel, bool dispatchEvents) override
	{
		if (id == INVALID_PACKET_ID)
		{
			return false;
		}

		const PeerNetworkData& netData = peer.getNetworkData();
		if (netData.network != this)
		{
			return false;
		}

		// We want exact bits - set the write offset with bit granularity
		NetworkBitStream bs(data.data(), bitsToBytes(data.size()), false /* copyData */);
		bs.SetWriteOffset(data.size());

		if (dispatchEvents)
		{
			if (!outEventDispatcher.stopAtFalse([&peer, id, &bs](NetworkOutEventHandler* handler)
					{
						bs.resetReadPointer();
						return handler->onSendRPC(&peer, id, bs);
					}))
			{
				return false;
			}

			if (!rpcOutEventDispatcher.stopAtFalse(id, [&peer, &bs](SingleNetworkOutEventHandler* handler)
					{
						bs.resetReadPointer();
						return handler->onSend(&peer, bs);
					}))
			{
				return false;
			}
		}

		const PeerNetworkData::NetworkID& nid = netData.networkID;
		const RakNet::PlayerID rid { unsigned(nid.address.v4), nid.port };
		const char rakOrderingChannel = normalizeOrderingChannelForLegacyClient(channel);
		const RakNet::PacketReliability reliability = RakNet::RELIABLE;
		const int translatedID = translateLegacyOutgoingRPCIDForPeer(peer, id);
		if (translatedID == INVALID_PACKET_ID)
		{
			if (core)
			{
				if (false) core->printLn(
					"[LegacyNetwork::sendRPC] drop unknown outgoing rpc peer=%.*s netcodeId=%d",
					PRINT_VIEW(peer.getName()),
					id);
			}
			return false;
		}

		return rakNetServer.RPC(translatedID, (const char*)bs.GetData(), bs.GetNumberOfBitsUsed(), RakNet::HIGH_PRIORITY, reliability, rakOrderingChannel, rid, false, false, RakNet::UNASSIGNED_NETWORK_ID, nullptr);
	}

	static int translateLegacyOutgoingRPCIDForPeer(const IPlayer& peer, int id)
	{
		if (peer.getClientVersionName() != StringView("baze"))
		{
			return id;
		}

		// Return the legacy 8-bit RPC ID here.
		// RakPeer applies the legacy->wire translation for this client itself.
		switch (id)
		{
		case NetCode::RPC::PlayerJoin::PacketID: return 137;
		case NetCode::RPC::PlayerQuit::PacketID: return 138;
		case NetCode::RPC::PlayerInit::PacketID: return 139;
		case NetCode::RPC::PlayerDeath::PacketID: return 53;
		case NetCode::RPC::PlayerStreamIn::PacketID: return 32;
		case NetCode::RPC::PlayerStreamOut::PacketID: return 163;
		case NetCode::RPC::StreamInVehicle::PacketID: return 164;
		case NetCode::RPC::StreamOutVehicle::PacketID: return 165;
		case NetCode::RPC::SendPlayerScoresAndPings::PacketID: return 155;
		case NetCode::RPC::ShowDialog::PacketID: return 61;
		case NetCode::RPC::SetPlayerName::PacketID: return 11;
		case NetCode::RPC::EnterVehicle::PacketID: return 26;
		case NetCode::RPC::ExitVehicle::PacketID: return 154;
		case NetCode::RPC::PutPlayerInVehicle::PacketID: return 70;
		case NetCode::RPC::RemovePlayerFromVehicle::PacketID: return 71;
		case NetCode::RPC::SetVehicleHealth::PacketID: return 147;
		case NetCode::RPC::LinkVehicleToInterior::PacketID: return 65;
		case NetCode::RPC::SetVehicleZAngle::PacketID: return 160;
		case NetCode::RPC::SetVehiclePosition::PacketID: return 159;
		case NetCode::RPC::SetVehicleVelocity::PacketID: return 91;
		case NetCode::RPC::SetVehicleParams::PacketID: return 24;
		case NetCode::RPC::SetPlayerSkin::PacketID: return 153;
		case NetCode::RPC::SetPlayerPosition::PacketID: return 12;
		case NetCode::RPC::SetPlayerPositionFindZ::PacketID: return 13;
		case NetCode::RPC::SetPlayerHealth::PacketID: return 14;
		case NetCode::RPC::PlayerPlaySound::PacketID: return 16;
		case NetCode::RPC::SetPlayerArmour::PacketID: return 66;
		case NetCode::RPC::SetPlayerTeam::PacketID: return 69;
		case NetCode::RPC::SetPlayerColor::PacketID: return 72;
		case NetCode::RPC::SetPlayerFacingAngle::PacketID: return 19;
		case NetCode::RPC::OnPlayerInteriorChange::PacketID: return 118;
		case NetCode::RPC::SetPlayerInterior::PacketID: return 156;
		case NetCode::RPC::SetPlayerCameraPosition::PacketID: return 157;
		case NetCode::RPC::SetPlayerCameraLookAt::PacketID: return 158;
		case NetCode::RPC::SetPlayerCameraBehindPlayer::PacketID: return 162;
		case NetCode::RPC::TogglePlayerControllable::PacketID: return 15;
		case NetCode::RPC::ResetPlayerWeapons::PacketID: return 21;
		case NetCode::RPC::GivePlayerWeapon::PacketID: return 22;
		case NetCode::RPC::SetPlayerAmmo::PacketID: return 145;
		case NetCode::RPC::SetPlayerArmedWeapon::PacketID: return 145;
		case NetCode::RPC::SetPlayerGravity::PacketID: return 146;
		case NetCode::RPC::CreateObject::PacketID: return 44;
		case NetCode::RPC::DestroyObject::PacketID: return 47;
		case NetCode::RPC::SetObjectPosition::PacketID: return 45;
		case NetCode::RPC::SetObjectRotation::PacketID: return 46;
		case NetCode::RPC::MoveObject::PacketID: return 99;
		case NetCode::RPC::StopObject::PacketID: return 122;
		case NetCode::RPC::AttachObjectToPlayer::PacketID: return 75;
		case NetCode::RPC::ApplyPlayerAnimation::PacketID: return 86;
		case NetCode::RPC::ClearPlayerTasks::PacketID: return 87;
		case NetCode::RPC::SetPlayerSpecialAction::PacketID: return 88;
		case NetCode::RPC::SetPlayerVelocity::PacketID: return 90;
		case NetCode::RPC::SendClientMessage::PacketID: return 93;
		case NetCode::RPC::SetPlayerWorldTime::PacketID: return 94;
		case NetCode::RPC::SetPlayerWeather::PacketID: return 152;
		case NetCode::RPC::SetPlayerTime::PacketID: return 29;
		case NetCode::RPC::TogglePlayerClock::PacketID: return 30;
		case NetCode::RPC::PlayerCreatePickup::PacketID: return 95;
		case NetCode::RPC::PlayerDestroyPickup::PacketID: return 63;
		case NetCode::RPC::PlayerClose::PacketID: return 40;
		case NetCode::RPC::SendDeathMessage::PacketID: return 55;
		case NetCode::RPC::PlayerTextDrawSetString::PacketID: return 105;
		case NetCode::RPC::ShowGangZone::PacketID: return 108;
		case NetCode::RPC::HideGangZone::PacketID: return 120;
		case NetCode::RPC::FlashGangZone::PacketID: return 121;
		case NetCode::RPC::SetVehiclePlate::PacketID: return 123;
		case NetCode::RPC::PlayerShowTextDraw::PacketID: return 134;
		case NetCode::RPC::PlayerHideTextDraw::PacketID: return 135;
		case NetCode::RPC::AttachTrailer::PacketID: return 148;
		case NetCode::RPC::DetachTrailer::PacketID: return 149;
		case NetCode::RPC::DisableRemoteVehicleCollisions::PacketID: return 167;
		case NetCode::RPC::OnPlayerCameraTarget::PacketID: return 168;
		case 169: return 169; // BR create waypoint / custom standard RPC
		case NetCode::RPC::SetPlayerCameraTargeting::PacketID: return 170;
		case NetCode::RPC::ShowActorForPlayer::PacketID: return 171;
		case NetCode::RPC::HideActorForPlayer::PacketID: return 172;
		case NetCode::RPC::SetActorFacingAngleForPlayer::PacketID: return 175;
		case NetCode::RPC::SetActorPosForPlayer::PacketID: return 176;
		case NetCode::RPC::SetActorHealthForPlayer::PacketID: return 178;
		case NetCode::RPC::PlayerShowTextLabel::PacketID: return 36;
		case NetCode::RPC::SetCheckpoint::PacketID: return 107;
		case NetCode::RPC::DisableCheckpoint::PacketID: return 37;
		case NetCode::RPC::SetRaceCheckpoint::PacketID: return 38;
		case NetCode::RPC::DisableRaceCheckpoint::PacketID: return 39;
		case NetCode::RPC::PlayAudioStreamForPlayer::PacketID: return 41;
		case NetCode::RPC::SendGameText::PacketID: return 73;
		case NetCode::RPC::SetWorldBounds::PacketID: return 17;
		case NetCode::RPC::GivePlayerMoney::PacketID: return 18;
		case NetCode::RPC::ResetPlayerMoney::PacketID: return 20;
		case NetCode::RPC::SetPlayerMapIcon::PacketID: return 56;
		case NetCode::RPC::RemovePlayerMapIcon::PacketID: return 144;
		case NetCode::RPC::CreateExplosion::PacketID: return 79;
		case NetCode::RPC::ShowPlayerNameTagForPlayer::PacketID: return 80;
		case NetCode::RPC::TogglePlayerSpectating::PacketID: return 124;
		case NetCode::RPC::PlayerSpectatePlayer::PacketID: return 126;
		case NetCode::RPC::PlayerSpectateVehicle::PacketID: return 127;
		case NetCode::RPC::RemoveVehicleComponent::PacketID: return 57;
		case NetCode::RPC::SendGameTimeUpdate::PacketID: return 60;
		case NetCode::RPC::SetSpawnInfo::PacketID: return 68;
		case NetCode::RPC::PlayerRequestClassResponse::PacketID: return 128;
		case NetCode::RPC::PlayerRequestSpawnResponse::PacketID: return 129;
		case NetCode::RPC::PlayerChatMessage::PacketID: return 101;
		case NetCode::RPC::ForcePlayerClassSelection::PacketID: return 74;
		case NetCode::RPC::SetPlayerWantedLevel::PacketID: return 133;
		case NetCode::RPC::SetPlayerFightingStyle::PacketID: return 89;
		case NetCode::RPC::SetPlayerDrunkLevel::PacketID: return 35;
		default:
			return INVALID_PACKET_ID;
		}
	}

	static uint8_t translateLegacyOutgoingPacketIDForPeer(const IPlayer& peer, uint8_t id)
	{
		if (peer.getClientVersionName() != StringView("baze"))
		{
			return id;
		}

		switch (id)
		{
		case NetCode::Packet::PlayerFootSync::PacketID:
			return 0x09;
		case NetCode::Packet::PlayerVehicleSync::PacketID:
			return 0x03;
		case NetCode::Packet::PlayerPassengerSync::PacketID:
			return 0x05;
		case NetCode::Packet::PlayerUnoccupiedSync::PacketID:
			return 0x02;
		case NetCode::Packet::PlayerTrailerSync::PacketID:
			return 0x0A;
		case NetCode::Packet::PlayerAimSync::PacketID:
			return 0x06;
		case NetCode::Packet::PlayerBulletSync::PacketID:
			return 0x0C;
		case NetCode::Packet::PlayerStatsSync::PacketID:
			return 0x08;
		case NetCode::Packet::PlayerSpectatorSync::PacketID:
			return 0x07;
		case NetCode::Packet::PlayerWeaponsUpdate::PacketID:
			return 0x0B;
		case NetCode::Packet::PlayerMarkersSync::PacketID:
			return 0xD0;
		default:
			return id;
		}
	}

	static void OnPlayerConnect(RakNet::RPCParameters* rpcParams, void* extra);
	static void OnNPCConnect(RakNet::RPCParameters* rpcParams, void* extra);
	static void OnRPC313(RakNet::RPCParameters* rpcParams, void* extra);
	static void OnRPC321(RakNet::RPCParameters* rpcParams, void* extra);
	static void OnRPC371(RakNet::RPCParameters* rpcParams, void* extra);

	IPlayer* OnPeerConnect(RakNet::RPCParameters* rpcParams, bool isNPC, StringView serial, uint32_t version, StringView versionName, uint32_t challenge, StringView name, bool isUsingOmp, bool isUsingOfficialClient = false);
	void DispatchRPCById(size_t id, RakNet::RPCParameters* rpcParams, void* extra);
	template <size_t ID>
	static void RPCHook(RakNet::RPCParameters* rpcParams, void* extra);
	void onTick(Microseconds elapsed, TimePoint now) override;
	void init(ICore* core);
	void start();

	void OnRakNetDisconnect(RakNet::PlayerIndex rid, PeerDisconnectReason reason);

	void onPlayerScoreChange(IPlayer& player, int score) override
	{
		query.buildPlayerDependentBuffers();
	}

	void onPlayerNameChange(IPlayer& player, StringView oldName) override
	{
		query.buildPlayerDependentBuffers();
	}

	void update() override;

	void onPlayerConnect(IPlayer& player) override
	{
		query.buildPlayerDependentBuffers();
	}

	void onPlayerDisconnect(IPlayer& player, PeerDisconnectReason reason) override
	{
		query.buildPlayerDependentBuffers(&player);
	}

	void onPoolEntryCreated(INPC& npc) override
	{
		if (npcComponent)
		{
			rakNetServer.ReserveSlots(npcComponent->count());
		}
	}

	void onPoolEntryDestroyed(INPC& npc) override
	{
		if (npcComponent)
		{
			rakNetServer.ReserveSlots(npcComponent->count());
		}
	}

	bool addRule(StringView rule, StringView value) override
	{
		if (isRuleProtected(rule))
		{
			return false;
		}

		query.setRuleValue<true>(String(rule), String(value));
		query.buildRulesBuffer();
		return true;
	}

	bool removeRule(StringView rule) override
	{
		if (isRuleProtected(rule))
		{
			return false;
		}

		query.removeRule(rule);
		query.buildRulesBuffer();
		return true;
	}

	bool isValidRule(StringView rule) override
	{
		return query.isValidRule(rule);
	}

	bool isRuleProtected(StringView rule)
	{
		for (StringView r : ProtectedRules)
		{
			if (r == rule)
			{
				return true;
			}
		}
		return false;
	}

	/// Synchronize players after banning an IP, kicking any that match the banned IP
	void synchronizeBans();

	NetworkStats getStatistics(IPlayer* player = nullptr) override;

	unsigned getPing(const IPlayer& peer) override
	{
		auto remoteSystem = playerRemoteSystem[peer.getID()];
		if (remoteSystem == nullptr)
		{
			return -1;
		}

		if (remoteSystem->pingAndClockDifferentialWriteIndex == 0)
		{
			return remoteSystem->pingAndClockDifferential[RakNet::PING_TIMES_ARRAY_SIZE - 1].pingTime;
		}
		else
		{
			return remoteSystem->pingAndClockDifferential[remoteSystem->pingAndClockDifferentialWriteIndex - 1].pingTime;
		}
	}

	void ban(const BanEntry& entry, Milliseconds expire = Milliseconds(0)) override;
	void unban(const BanEntry& entry) override;

	void reset() override
	{
	}
};

struct AnnounceHTTPResponseHandler final : HTTPResponseHandler
{
	ICore* core;

	AnnounceHTTPResponseHandler(ICore* core)
		: core(core)
	{
	}

	void onHTTPResponse(int status, StringView body) override
	{
		if (status != 200)
		{
			core->logLn(LogLevel::Warning, "Couldn't announce legacy network to open.mp list.");
			core->logLn(LogLevel::Warning, "\t Status: %d", status);
			core->logLn(LogLevel::Warning, "\t Message: %.*s", PRINT_VIEW(body));
			core->logLn(LogLevel::Warning, "This won't affect the server's behaviour.");
		}
		delete this;
	}
};
