/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

#pragma once

#include <cstring>

#include <Server/Components/Vehicles/vehicles.hpp>
#include <network.hpp>
#include <player.hpp>
#include <types.hpp>

namespace NetCode
{
namespace RPC
{
	struct PutPlayerInVehicle : NetworkPacketBase<70, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		int SeatID;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(VehicleID);
			bs.writeUINT8(SeatID);
		}
	};

	struct SetVehicleHealth : NetworkPacketBase<147, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		float health;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(VehicleID);
			bs.writeFLOAT(health);
		}
	};

	struct LinkVehicleToInterior : NetworkPacketBase<65, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		int InteriorID;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(VehicleID);
			bs.writeUINT8(InteriorID);
		}
	};

	struct SetVehicleZAngle : NetworkPacketBase<160, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		float angle;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(VehicleID);
			bs.writeFLOAT(angle);
		}
	};

	struct RemovePlayerFromVehicle : NetworkPacketBase<71, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
		}
	};

	struct StreamInVehicle : NetworkPacketBase<164, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		int ModelID;
		Vector3 Position;
		float Angle;
		uint8_t Colour1;
		uint8_t Colour2;
		uint8_t Interior;
		uint8_t Paintjob;
		float Health;
		uint32_t DoorDamage;
		uint32_t PanelDamage;
		uint8_t LightDamage;
		uint8_t TyreDamage;
		uint8_t Siren;
		StaticArray<int, MAX_VEHICLE_COMPONENT_SLOT_IN_RPC> Mods;
		int32_t BodyColour1;
		int32_t BodyColour2;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			#pragma pack(push, 1)
			struct BRNewVehiclePackedCompat
			{
				uint16_t VehicleID;
				int32_t iVehicleType;
				float vecPos[3];
				float fRotation;
				uint8_t aColor1;
				uint8_t aColor2;
				float fHealth;
				uint8_t byteInterior;
				uint32_t dwDoorDamageStatus;
				uint32_t dwPanelDamageStatus;
				uint8_t byteLightDamageStatus;
				uint8_t byteTireDamageStatus;
				uint8_t byteAddSiren;
				uint16_t byteModSlots[2];
				int32_t cColor1;
				int32_t cColor2;
				uint32_t dwWindowsColor;
				uint32_t dwWindowsColor2;
				uint32_t dwWindowsColor3;
				uint32_t dwWindowsColor4;
				float fSuspensionForce;
				float fSuspensionCenter;
				float fWheelSize;
				float fMaxSpeed;
				float fEngineAcceleration;
				float fBrakeDeceleration;
				float fSteeringLock;
				uint32_t dwLightsColor;
				uint32_t dwNeonColor;
				uint32_t dwNeonColor2;
				uint32_t dwNeonColor3;
				float fWheelsAngle;
				float fWheelsAngleRear;
				uint32_t dwWheelsWidth;
				uint8_t bDriftMode;
				float fWheelsOffset;
				float fWheelsOffsetRear;
				float fWheelScale;
				float fWheelScaleRear;
				uint32_t dwColor[4];
				uint8_t bHornTon;
				uint32_t dwStrobesMode;
				uint32_t dwChipMode;
				uint8_t bHydauliks;
				uint8_t bFar;
				int16_t wExhaust;
				uint8_t bUseSiren;
				uint8_t bEnabledSiren;
			};
			#pragma pack(pop)
			static_assert(sizeof(BRNewVehiclePackedCompat) == 0xAC, "BRNewVehiclePackedCompat must be 172 bytes");

			BRNewVehiclePackedCompat payload {};
			payload.VehicleID = static_cast<uint16_t>(VehicleID);
			payload.iVehicleType = static_cast<int32_t>(ModelID);
			payload.vecPos[0] = Position.x;
			payload.vecPos[1] = Position.y;
			payload.vecPos[2] = Position.z;
			payload.fRotation = Angle;
			payload.aColor1 = Colour1;
			payload.aColor2 = Colour2;
			payload.fHealth = Health;
			payload.byteInterior = Interior;
			payload.dwDoorDamageStatus = DoorDamage;
			payload.dwPanelDamageStatus = PanelDamage;
			payload.byteLightDamageStatus = LightDamage;
			payload.byteTireDamageStatus = TyreDamage;
			payload.byteAddSiren = Siren;
			payload.cColor1 = BodyColour1;
			payload.cColor2 = BodyColour2;

			// Expanded BR tuning fields.
			payload.fSuspensionForce = 1.0f;
			// BR client applies this value directly; zero makes many vehicles nose-down on spawn.
			payload.fSuspensionCenter = 0.5f;
			payload.fWheelSize = 1.0f;
			payload.fWheelScale = 1.0f;
			payload.fWheelScaleRear = 1.0f;
			payload.fWheelsOffset = 0.0f;
			payload.fWheelsOffsetRear = 0.0f;
			payload.fWheelsAngle = 0.0f;
			payload.fWheelsAngleRear = 0.0f;
			payload.fMaxSpeed = 0.0f;
			// Client multiplies these values down; low numbers result in "sliding/no steering" behavior.
			payload.fEngineAcceleration = 0.0f;
			payload.fBrakeDeceleration = 3500.0f;
			payload.fSteeringLock = 35.0f;
			payload.dwWheelsWidth = 0x3F800000u; // float 1.0f in raw form
			payload.bDriftMode = 0;
			payload.bHornTon = 0;
			// In BR client, values < 5 force strobe logic on spawn.
			payload.dwStrobesMode = 5;
			payload.dwChipMode = 0;
			payload.bHydauliks = 0;
			payload.bFar = 0;
			payload.wExhaust = -1;
			payload.bUseSiren = 0;
			payload.bEnabledSiren = Siren ? 1 : 0;

			if (BodyColour1 >= 0)
				payload.dwColor[0] = static_cast<uint32_t>(BodyColour1);
			if (BodyColour2 >= 0)
			{
				payload.dwColor[1] = static_cast<uint32_t>(BodyColour2);
				payload.dwColor[2] = static_cast<uint32_t>(BodyColour2);
				payload.dwColor[3] = static_cast<uint32_t>(BodyColour2);
			}

			uint16_t components[MAX_VEHICLE_COMPONENT_SLOT_IN_RPC] {};
			uint8_t componentCount = 0;
			for (int mod : Mods)
			{
				if (mod <= 0)
					continue;
				if (componentCount < MAX_VEHICLE_COMPONENT_SLOT_IN_RPC)
					components[componentCount++] = static_cast<uint16_t>(mod);
			}
			if (componentCount > 0)
				payload.byteModSlots[0] = components[0];
			if (componentCount > 1)
				payload.byteModSlots[1] = components[1];

			const uint8_t* raw = reinterpret_cast<const uint8_t*>(&payload);
			for (size_t i = 0; i < sizeof(payload); ++i)
				bs.writeUINT8(raw[i]);

			// Exact working BR tail: componentCount, n_2, n_1.
			// Components already present in the packed compatibility fields above;
			// appending a variable list changes the payload size expected by this client.
			bs.writeUINT8(0);
			bs.writeUINT8(0);
			bs.writeUINT8(0);
		}
	};

	struct StreamOutVehicle : NetworkPacketBase<165, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(VehicleID);
		}
	};

	struct OnPlayerEnterVehicle : NetworkPacketBase<26, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		uint8_t Passenger;

		bool read(NetworkBitStream& bs)
		{
			bs.readUINT16(VehicleID);
			return bs.readUINT8(Passenger);
		}

		void write(NetworkBitStream& bs) const
		{
		}
	};

	struct EnterVehicle : NetworkPacketBase<26, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int PlayerID;
		int VehicleID;
		uint8_t Passenger;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(PlayerID);
			bs.writeUINT16(VehicleID);
			bs.writeUINT8(Passenger);
		}
	};

	struct OnPlayerExitVehicle : NetworkPacketBase<154, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;

		bool read(NetworkBitStream& bs)
		{
			return bs.readUINT16(VehicleID);
		}

		void write(NetworkBitStream& bs) const
		{
		}
	};

	struct ExitVehicle : NetworkPacketBase<154, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int PlayerID;
		int VehicleID;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(PlayerID);
			bs.writeUINT16(VehicleID);
		}
	};

	struct SetVehiclePlate : NetworkPacketBase<123, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		HybridString<16> plate;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(VehicleID);
			bs.writeDynStr8(StringView(plate));
		}
	};

	struct SetVehiclePosition : NetworkPacketBase<159, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		Vector3 position;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(VehicleID);
			bs.writeVEC3(position);
		}
	};

	struct SetVehicleDamageStatus : NetworkPacketBase<106, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		uint32_t DoorStatus;
		uint32_t PanelStatus;
		uint8_t LightStatus;
		uint8_t TyreStatus;

		bool read(NetworkBitStream& bs)
		{
			bs.readUINT16(VehicleID);
			bs.readUINT32(PanelStatus);
			bs.readUINT32(DoorStatus);
			bs.readUINT8(LightStatus);
			return bs.readUINT8(TyreStatus);
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(VehicleID);
			bs.writeUINT32(PanelStatus);
			bs.writeUINT32(DoorStatus);
			bs.writeUINT8(LightStatus);
			bs.writeUINT8(TyreStatus);
		}
	};

	struct RemoveVehicleComponent : NetworkPacketBase<57, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		int Component;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(VehicleID);
			bs.writeUINT16(Component);
		}
	};

	struct VehicleDeath : NetworkPacketBase<136, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		bool read(NetworkBitStream& bs)
		{
			return bs.readUINT16(VehicleID);
		}

		void write(NetworkBitStream& bs) const
		{
		}
	};

	struct AttachTrailer : NetworkPacketBase<148, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		int TrailerID;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(TrailerID);
			bs.writeUINT16(VehicleID);
		}
	};

	struct DetachTrailer : NetworkPacketBase<149, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(VehicleID);
		}
	};

	struct SetVehicleVelocity : NetworkPacketBase<91, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		uint8_t Type;
		Vector3 Velocity;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT8(Type);
			bs.writeVEC3(Velocity);
		}
	};

	struct SetVehicleParams : NetworkPacketBase<24, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{

		int VehicleID;
		VehicleParams params;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT16(VehicleID);
			bs.writeUINT8(params.engine);
			bs.writeUINT8(params.lights);
			bs.writeUINT8(params.alarm);
			bs.writeUINT8(params.doors);
			bs.writeUINT8(params.bonnet);
			bs.writeUINT8(params.boot);
			bs.writeUINT8(params.objective);
			bs.writeUINT8(params.siren);
			bs.writeUINT8(params.doorDriver);
			bs.writeUINT8(params.doorPassenger);
			bs.writeUINT8(params.doorBackLeft);
			bs.writeUINT8(params.doorBackRight);
			bs.writeUINT8(params.windowDriver);
			bs.writeUINT8(params.windowPassenger);
			bs.writeUINT8(params.windowBackLeft);
			bs.writeUINT8(params.windowBackRight);
		}
	};
}

namespace Packet
{
	struct PlayerVehicleSync : NetworkPacketBase<200, NetworkPacketType::Packet, OrderingChannel_SyncPacket>, VehicleDriverSyncPacket
	{

		bool read(NetworkBitStream& bs)
		{
			bool siren = false;
			bool landingGear = false;
			bool hasHydra = false;
			bool hasTrailer = false;
			uint16_t health = 0;

			HydraThrustAngle = 0;
			TrailerID = 0;
			HasTrailer = false;

			bs.readUINT16(VehicleID);
			bs.readUINT16(LeftRight);
			bs.readUINT16(UpDown);
			bs.readUINT16(Keys);
			if (!bs.readGTAQuat(Rotation))
			{
				return false;
			}
			if (!bs.readPosVEC3(Position))
			{
				return false;
			}
			if (!bs.readCompressedVEC3(Velocity))
			{
				return false;
			}
			if (!bs.readUINT16(health))
			{
				return false;
			}
			if (!bs.readCompressedPercentPair(PlayerHealthArmour))
			{
				return false;
			}
			if (!bs.readUINT8(AdditionalKeyWeapon)
				|| !bs.readBIT(siren)
				|| !bs.readBIT(landingGear)
				|| !bs.readBIT(hasHydra))
			{
				return false;
			}

			if (hasHydra && !bs.readUINT32(HydraThrustAngle))
			{
				return false;
			}
			if (!bs.readBIT(hasTrailer))
			{
				return false;
			}
			if (hasTrailer && !bs.readUINT16(TrailerID))
			{
				return false;
			}

			Health = float(health);
			Siren = siren ? 1 : 0;
			LandingGear = landingGear ? 1 : 0;
			HasTrailer = hasTrailer;
			return true;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT8(PacketID);
			bs.writeUINT16(uint16_t(PlayerID));
			bs.writeUINT16(VehicleID);
			bs.writeUINT16(LeftRight);
			bs.writeUINT16(UpDown);
			bs.writeUINT16(Keys);
			bs.writeGTAQuat(Rotation);
			bs.writeVEC3(Position);
			bs.writeCompressedVEC3(Velocity);
			bs.writeUINT16(uint16_t(Health));
			bs.writeCompressedPercentPair(PlayerHealthArmour);
			bs.writeUINT8(AdditionalKeyWeapon);
			bs.writeBIT(Siren);
			bs.writeBIT(LandingGear);

			bs.writeBIT(HydraThrustAngle > 0);
			if (HydraThrustAngle)
			{
				bs.writeUINT32(HydraThrustAngle);
			}

			bs.writeBIT(HasTrailer);
			if (HasTrailer)
			{
				bs.writeUINT16(TrailerID);
			}
		}

		void writeLegacyBazeCompat(NetworkBitStream& bs) const
		{
			// Exact server -> BR VehicleSync layout.  Full u16 player health and
			// armour are required; the old packed byte shifted all presence bits.
			bs.writeUINT8(PacketID);
			bs.writeUINT16(uint16_t(PlayerID));
			bs.writeUINT16(VehicleID);
			bs.writeUINT16(LeftRight);
			bs.writeUINT16(UpDown);
			bs.writeUINT16(Keys);
			bs.writeGTAQuat(Rotation);
			bs.writeVEC3(Position);
			bs.writeCompressedVEC3(Velocity);
			bs.writeUINT16(uint16_t(Health));
			bs.writeUINT16(uint16_t(PlayerHealthArmour.x));
			bs.writeUINT16(uint16_t(PlayerHealthArmour.y));
			bs.writeUINT8(WeaponID & 0x3F);
			bs.writeBIT(Siren != 0);
			bs.writeBIT(LandingGear != 0);
			// BR right-stick block is not represented in open.mp sync state.
			bs.writeBIT(false);
			bs.writeBIT(HasTrailer && TrailerID != 0);
			if (HasTrailer && TrailerID != 0) bs.writeUINT16(TrailerID);
		}
	};

	struct PlayerPassengerSync : NetworkPacketBase<211, NetworkPacketType::Packet, OrderingChannel_SyncPacket>, VehiclePassengerSyncPacket
	{

		bool read(NetworkBitStream& bs)
		{
			uint8_t health = 0;
			uint8_t armour = 0;

			bs.readUINT16(VehicleID);
			bs.readUINT16(DriveBySeatAdditionalKeyWeapon);
			if (!bs.readUINT8(health) || !bs.readUINT8(armour))
			{
				return false;
			}
			bs.readUINT16(LeftRight);
			bs.readUINT16(UpDown);
			bs.readUINT16(Keys);
			HealthArmour = Vector2(health, armour);
			return bs.readPosVEC3(Position);
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT8(PacketID);
			bs.writeUINT16(PlayerID);
			bs.writeUINT16(VehicleID);
			bs.writeUINT16(DriveBySeatAdditionalKeyWeapon);
			bs.writeUINT8(int(HealthArmour.x));
			bs.writeUINT8(int(HealthArmour.y));
			bs.writeUINT16(LeftRight);
			bs.writeUINT16(UpDown);
			bs.writeUINT16(Keys);
			bs.writeVEC3(Position);
		}

		void writeLegacyBazeCompat(NetworkBitStream& bs) const
		{
			const uint8_t seatDriveBy = uint8_t((SeatID & 0x7F) | ((DriveBy ? 1 : 0) << 7));

			bs.writeUINT8(PacketID);
			bs.writeUINT16(uint16_t(PlayerID));
			bs.writeUINT16(VehicleID);
			bs.writeUINT8(seatDriveBy);
			bs.writeUINT8(WeaponID);
			bs.writeUINT16(uint16_t(HealthArmour.x));
			bs.writeUINT16(uint16_t(HealthArmour.y));
			bs.writeUINT16(LeftRight);
			bs.writeUINT16(UpDown);
			bs.writeUINT16(Keys);
			bs.writeVEC3(Position);
		}
	};

	struct PlayerUnoccupiedSync : NetworkPacketBase<209, NetworkPacketType::Packet, OrderingChannel_SyncPacket>, VehicleUnoccupiedSyncPacket
	{

		bool read(NetworkBitStream& bs)
		{
			bs.readUINT16(VehicleID);
			bs.readUINT8(SeatID);
			if (!bs.readVEC3(Roll))
			{
				return false;
			}
			if (!bs.readVEC3(Rotation))
			{
				return false;
			}
			if (!bs.readPosVEC3(Position))
			{
				return false;
			}
			if (!bs.readVelVEC3(Velocity))
			{
				return false;
			}
			if (!bs.readVEC3(AngularVelocity))
			{
				return false;
			}
			return bs.readFLOAT(Health);
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT8(PacketID);
			bs.writeUINT16(PlayerID);
			bs.writeUINT16(VehicleID);
			bs.writeUINT8(SeatID);
			bs.writeVEC3(Roll);
			bs.writeVEC3(Rotation);
			bs.writeVEC3(Position);
			bs.writeVEC3(Velocity);
			bs.writeVEC3(AngularVelocity);
			bs.writeFLOAT(Health);
		}
	};

	struct PlayerTrailerSync : NetworkPacketBase<210, NetworkPacketType::Packet, OrderingChannel_SyncPacket>, VehicleTrailerSyncPacket
	{

		bool read(NetworkBitStream& bs)
		{
			bs.readUINT16(VehicleID);
			if (!bs.readPosVEC3(Position))
			{
				return false;
			}
			if (!bs.readVEC4(Quat))
			{
				return false;
			}
			if (!bs.readVelVEC3(Velocity))
			{
				return false;
			}
			return bs.readVEC3(TurnVelocity);
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeUINT8(PacketID);
			bs.writeUINT16(PlayerID);
			bs.writeUINT16(VehicleID);
			bs.writeVEC3(Position);
			bs.writeVEC4(Quat);
			bs.writeVEC3(Velocity);
			bs.writeVEC3(TurnVelocity);
		}
	};
}
}
