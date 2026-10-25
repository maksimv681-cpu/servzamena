/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

#pragma once

#include <network.hpp>
#include <player.hpp>
#include <types.hpp>

namespace NetCode
{
namespace Packet
{
	// BR GUI channel: u16 guiId, u32 jsonLength, char json[jsonLength].
	struct BazeUserInterfaceSync : NetworkPacketBase<1, NetworkPacketType::Packet, OrderingChannel_SyncPacket>
	{
	};
}

namespace RPC
{
	struct ShowDialog : NetworkPacketBase<61, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{
		int ID;
		uint8_t Style;
		HybridString<163> Title;
		HybridString<127> FirstButton;
		HybridString<127> SecondButton;
		HybridString<4096> Body;

		bool read(NetworkBitStream& bs)
		{
			return false;
		}

		void write(NetworkBitStream& bs) const
		{
			bs.writeINT16(ID);
			bs.writeUINT8(Style);
			bs.writeDynStr8(Title);
			bs.writeDynStr8(FirstButton);
			bs.writeDynStr8(SecondButton);
			bs.WriteCompressedStr(Body);
		}
	};

	struct OnPlayerDialogResponse : NetworkPacketBase<62, NetworkPacketType::RPC, OrderingChannel_SyncRPC>
	{
		int ID;
		uint8_t Response;
		int ListItem;
		HybridString<256> Text;

		bool read(NetworkBitStream& bs)
		{
			bs.readINT16(ID);
			bs.readUINT8(Response);
			bs.readINT16(ListItem);
			return bs.readDynStr8(Text);
		}

		void write(NetworkBitStream& bs) const
		{
		}
	};
}
}
