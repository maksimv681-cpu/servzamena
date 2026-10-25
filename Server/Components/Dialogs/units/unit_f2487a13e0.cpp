/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

#include <Impl/events_impl.hpp>
#include <Server/Components/Dialogs/dialogs.hpp>
#include "../../../../Shared/NetCode/detail/unit_4c18dc97b3.hpp"
#include <cctype>
#include <cstdlib>

using namespace Impl;

String emptyString = " ";
StringView emptyStringView = emptyString;

static const NetCode::RPC::ShowDialog hideDialog = {
	{},
	INVALID_DIALOG_ID,
	static_cast<uint8_t>(DialogStyle_MSGBOX),
	emptyStringView,
	emptyStringView,
	emptyStringView,
	emptyStringView
};

class PlayerDialogData final : public IPlayerDialogData
{
private:
	int activeId = INVALID_DIALOG_ID;

	String title_ = "";
	String body_ = "";
	String button1_ = "";
	String button2_ = "";
	DialogStyle style_ = DialogStyle_MSGBOX;

	friend class DialogsComponent;

public:
	void hide(IPlayer& player) override
	{
		if (activeId != INVALID_DIALOG_ID)
		{
			PacketHelper::send(hideDialog, player);
			activeId = INVALID_DIALOG_ID;
		}
	}

	void show(IPlayer& player, int id, DialogStyle style, StringView title, StringView body, StringView button1, StringView button2) override
	{
		// We can enforce this more strictly in the component.  The legacy IDs
		// should only be in Pawn.
		if (id <= INVALID_DIALOG_ID || id >= MAX_DIALOG)
		{
			return;
		}

		// Limit list item length to prevent client from crashing
		if (style == DialogStyle_LIST)
		{
			auto pos = body.find("\n");
			if (pos == body.npos)
			{
				if (body.length() > 130)
				{
					return;
				}
			}
			else
			{
				if (pos > 130)
				{
					return;
				}
			}
		}

		style_ = style;
		title_ = String(title);
		body_ = String(body);
		button1_ = String(button1);
		button2_ = String(button2);

		NetCode::RPC::ShowDialog showDialog;
		showDialog.ID = id;
		showDialog.Style = static_cast<uint8_t>(style);
		// We don't have to truncate title to be less than 64 client sided size limit.
		// Client won't crash or show any undefined behavior, it simply doesn't render.
		// 64 char limit is without counting embedded colors, let client handle then.
		showDialog.Title = title_;
		showDialog.Body = body;
		showDialog.FirstButton = button1;
		showDialog.SecondButton = button2;
		PacketHelper::send(showDialog, player);

		// set player's active dialog id to keep track of its validity later on response
		activeId = id;
	}

	void get(int& id, DialogStyle& style, StringView& title, StringView& body, StringView& button1, StringView& button2) override
	{
		id = activeId;
		style = style_;
		title = title_;
		body = body_;
		button1 = button1_;
		button2 = button2_;
	}

	int getActiveID() const override
	{
		return activeId;
	}

	void freeExtension() override
	{
		delete this;
	}

	void reset() override
	{
		// Could call `hide()` here, but then we'd have to store the player ID.
		activeId = INVALID_DIALOG_ID;
	}
};

class DialogsComponent final : public IDialogsComponent, public PoolEventHandler<IPlayer>
{
private:
	ICore* core = nullptr;
	DefaultEventDispatcher<PlayerDialogEventHandler> eventDispatcher;

	struct DialogResponseHandler : public SingleNetworkInEventHandler
	{
		DialogsComponent& self;
		DialogResponseHandler(DialogsComponent& self)
			: self(self)
		{
		}

		bool onReceive(IPlayer& peer, NetworkBitStream& bs) override
		{
			NetCode::RPC::OnPlayerDialogResponse sendDialogResponse;
			if (!sendDialogResponse.read(bs))
			{
				return false;
			}

			// If the dialog id doesn't match what the server is expecting, ignore it
			PlayerDialogData* data = queryExtension<PlayerDialogData>(peer);
			if (!data || data->getActiveID() == INVALID_DIALOG_ID || data->getActiveID() != sendDialogResponse.ID)
			{
				return false;
			}

			if (sendDialogResponse.Response < 0 || sendDialogResponse.Response > 1)
			{
				return false;
			}

			if ((data->style_ == DialogStyle_PASSWORD || data->style_ == DialogStyle_INPUT || data->style_ == DialogStyle_MSGBOX) && sendDialogResponse.ListItem != -1)
			{
				return false;
			}

			if ((data->style_ == DialogStyle_LIST || data->style_ == DialogStyle_TABLIST || data->style_ == DialogStyle_TABLIST_HEADERS) && data->body_.length() > 0)
			{
				unsigned int lines = 0;

				for (unsigned int i = 0; i < data->body_.length() - 1; i++)
				{
					if (data->body_[i] == '\n')
					{
						lines++;
					}
				}

				if (data->style_ == DialogStyle_TABLIST_HEADERS && lines > 0)
				{
					lines--;
				}

				if (sendDialogResponse.ListItem < 0 || sendDialogResponse.ListItem > lines)
				{
					return false;
				}
			}

			data->activeId = INVALID_DIALOG_ID;

			self.eventDispatcher.dispatch(
				&PlayerDialogEventHandler::onDialogResponse,
				peer,
				sendDialogResponse.ID,
				static_cast<DialogResponse>(sendDialogResponse.Response),
				sendDialogResponse.ListItem,
				sendDialogResponse.Text);

			return true;
		}
	} dialogResponseHandler;

	struct BazeDialogJSONHandler : public SingleNetworkInEventHandler
	{
		DialogsComponent& self;
		BazeDialogJSONHandler(DialogsComponent& self)
			: self(self)
		{
		}

		static bool readInt(const String& json, const char* key, int& value)
		{
			String needle = String("\"") + key + "\"";
			size_t pos = json.find(needle);
			if (pos == String::npos || (pos = json.find(':', pos + needle.length())) == String::npos)
				return false;
			++pos;
			while (pos < json.length() && std::isspace(static_cast<unsigned char>(json[pos]))) ++pos;
			char* end = nullptr;
			const long parsed = std::strtol(json.c_str() + pos, &end, 10);
			if (end == json.c_str() + pos)
				return false;
			value = int(parsed);
			return true;
		}

		static String readString(const String& json, const char* key)
		{
			String needle = String("\"") + key + "\"";
			size_t pos = json.find(needle);
			if (pos == String::npos || (pos = json.find(':', pos + needle.length())) == String::npos)
				return String();
			++pos;
			while (pos < json.length() && std::isspace(static_cast<unsigned char>(json[pos]))) ++pos;
			if (pos >= json.length() || json[pos] != '"')
				return String();
			++pos;
			String output;
			while (pos < json.length())
			{
				const char ch = json[pos++];
				if (ch == '"') break;
				if (ch == '\\' && pos < json.length())
				{
					const char escaped = json[pos++];
					if (escaped == 'n') output.push_back('\n');
					else if (escaped == 'r') output.push_back('\r');
					else if (escaped == 't') output.push_back('\t');
					else output.push_back(escaped);
				}
				else output.push_back(ch);
			}
			return output;
		}

		bool onReceive(IPlayer& peer, NetworkBitStream& bs) override
		{
			if (peer.getClientVersionName() != StringView("baze"))
				return false;

			uint16_t guiID = 0;
			uint32_t jsonLength = 0;
			if (!bs.readUINT16(guiID) || !bs.readUINT32(jsonLength) || guiID != 10 ||
				jsonLength > 65536 || jsonLength * 8u > unsigned(bs.GetNumberOfUnreadBits()))
				return false;

			String json(jsonLength, '\0');
			if (jsonLength != 0 && !bs.readArray(Span<char>(json.data(), jsonLength)))
				return false;

			int response = 0;
			int listItem = -1;
			if (!readInt(json, "r", response) || !readInt(json, "l", listItem))
				return false;
			String input = readString(json, "i");
			if (input.length() > 255)
				input.resize(255);

			PlayerDialogData* data = queryExtension<PlayerDialogData>(peer);
			if (!data || data->getActiveID() == INVALID_DIALOG_ID)
				return false;

			// BR sends l=0 for input-like dialogs, while stock open.mp requires -1.
			if (data->style_ == DialogStyle_PASSWORD || data->style_ == DialogStyle_INPUT ||
				data->style_ == DialogStyle_MSGBOX)
				listItem = -1;

			// Convert {r,l,i} into stock RPC 62 and reuse normal validation/Pawn dispatch.
			NetworkBitStream standard;
			standard.writeINT16(int16_t(data->getActiveID()));
			standard.writeUINT8(uint8_t(response));
			standard.writeINT16(int16_t(listItem));
			standard.writeDynStr8(StringView(input));
			standard.SetReadOffset(0);
			return self.dialogResponseHandler.onReceive(peer, standard);
		}
	} bazeDialogJSONHandler;

public:
	void onPoolEntryCreated(IPlayer& player) override
	{
		player.addExtension(new PlayerDialogData(), true);
	}

	StringView componentName() const override
	{
		return "Dialogs";
	}

	SemanticVersion componentVersion() const override
	{
		return SemanticVersion(OMP_VERSION_MAJOR, OMP_VERSION_MINOR, OMP_VERSION_PATCH, BUILD_NUMBER);
	}

	DialogsComponent()
		: dialogResponseHandler(*this)
		, bazeDialogJSONHandler(*this)
	{
	}

	void onLoad(ICore* c) override
	{
		core = c;
		core->getPlayers().getPoolEventDispatcher().addEventHandler(this);
		NetCode::RPC::OnPlayerDialogResponse::addEventHandler(*core, &dialogResponseHandler);
		// Pawn.RakNet's IPacket:1 commonly returns 0. The per-packet dispatcher
		// stops at the first false handler, so process the BR dialog JSON before
		// Pawn's packet callback; Pawn still receives the packet afterwards.
		NetCode::Packet::BazeUserInterfaceSync::addEventHandler(
			*core,
			&bazeDialogJSONHandler,
			EventPriority_Highest + 1);
	}

	void reset() override
	{
		for (IPlayer* player : core->getPlayers().entries())
		{
			auto data = queryExtension<IPlayerDialogData>(player);
			if (data)
			{
				data->hide(*player);
			}
		}
	}

	void free() override
	{
		delete this;
	}

	~DialogsComponent()
	{
		if (core)
		{
			core->getPlayers().getPoolEventDispatcher().removeEventHandler(this);
			NetCode::RPC::OnPlayerDialogResponse::removeEventHandler(*core, &dialogResponseHandler);
			NetCode::Packet::BazeUserInterfaceSync::removeEventHandler(*core, &bazeDialogJSONHandler);
		}
	}

	IEventDispatcher<PlayerDialogEventHandler>& getEventDispatcher() override
	{
		return eventDispatcher;
	}
};

COMPONENT_ENTRY_POINT()
{
	return new DialogsComponent();
}
