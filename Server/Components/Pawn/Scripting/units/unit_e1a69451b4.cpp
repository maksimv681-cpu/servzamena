/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

#include "../detail/unit_19fc6d4997.hpp"

#include "../Actor/detail/unit_d253ce685b.hpp"
#include "../Checkpoint/detail/unit_88d2573d75.hpp"
#include "../Class/detail/unit_077e4be7e0.hpp"
#include "../Core/detail/unit_f0ce6fd6bd.hpp"
#include "../Dialog/detail/unit_5fd27973bb.hpp"
#include "../Menu/detail/unit_980f9fb5d5.hpp"
#include "../Object/detail/unit_f75ac9b73c.hpp"
#include "../Pickup/detail/unit_5bf108b3ea.hpp"
#include "../Player/detail/unit_e6f01606bf.hpp"
#include "../TextDraw/detail/unit_8f8167efed.hpp"
#include "../Vehicle/detail/unit_bc6e53585b.hpp"
#include "../GangZone/detail/unit_a90868765a.hpp"
#include "../CustomModels/detail/unit_9dd7126b7e.hpp"
#include "../NPC/detail/unit_d1e6b0f490.hpp"

Scripting::~Scripting()
{
	PawnManager* mgr = PawnManager::Get();

	// remove event handlers
	if (mgr->players)
	{
		mgr->players->getPlayerSpawnDispatcher().removeEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerConnectDispatcher().removeEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerStreamDispatcher().removeEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerTextDispatcher().removeEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerShotDispatcher().removeEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerChangeDispatcher().removeEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerDamageDispatcher().removeEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerClickDispatcher().removeEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerCheckDispatcher().removeEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerUpdateDispatcher().removeEventHandler(PlayerEvents::Get());
	}
	if (mgr->actors)
	{
		mgr->actors->getEventDispatcher().removeEventHandler(ActorEvents::Get());
	}
	if (mgr->checkpoints)
	{
		mgr->checkpoints->getEventDispatcher().removeEventHandler(CheckpointEvents::Get());
	}
	if (mgr->classes)
	{
		mgr->classes->getEventDispatcher().removeEventHandler(ClassEvents::Get());
	}
	if (mgr->dialogs)
	{
		mgr->dialogs->getEventDispatcher().removeEventHandler(DialogEvents::Get());
	}
	if (mgr->menus)
	{
		mgr->menus->getEventDispatcher().removeEventHandler(MenuEvents::Get());
	}
	if (mgr->textdraws)
	{
		mgr->textdraws->getEventDispatcher().removeEventHandler(TextDrawEvents::Get());
	}
	if (mgr->pickups)
	{
		mgr->pickups->getEventDispatcher().removeEventHandler(PickupEvents::Get());
	}
	if (mgr->vehicles)
	{
		mgr->vehicles->getEventDispatcher().removeEventHandler(VehicleEvents::Get());
	}
	if (mgr->objects)
	{
		mgr->objects->getEventDispatcher().removeEventHandler(ObjectEvents::Get());
	}
	if (mgr->console)
	{
		mgr->console->getEventDispatcher().removeEventHandler(CoreEvents::Get());
	}
	if (mgr->gangzones)
	{
		mgr->gangzones->getEventDispatcher().removeEventHandler(GangZoneEvents::Get());
	}
	if (mgr->models)
	{
		mgr->models->getEventDispatcher().removeEventHandler(CustomModelsEvents::Get());
	}
	if (mgr->npcs)
	{
		mgr->npcs->getEventDispatcher().removeEventHandler(NPCEvents::Get());
	}
}

void Scripting::addEvents() const
{
	PawnManager* mgr = PawnManager::Get();

	// add event handlers
	if (mgr->players)
	{
		mgr->players->getPlayerSpawnDispatcher().addEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerConnectDispatcher().addEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerStreamDispatcher().addEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerTextDispatcher().addEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerShotDispatcher().addEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerChangeDispatcher().addEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerDamageDispatcher().addEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerClickDispatcher().addEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerCheckDispatcher().addEventHandler(PlayerEvents::Get());
		mgr->players->getPlayerUpdateDispatcher().addEventHandler(PlayerEvents::Get());
	}
	if (mgr->actors)
	{
		mgr->actors->getEventDispatcher().addEventHandler(ActorEvents::Get());
	}
	if (mgr->checkpoints)
	{
		mgr->checkpoints->getEventDispatcher().addEventHandler(CheckpointEvents::Get());
	}
	if (mgr->classes)
	{
		mgr->classes->getEventDispatcher().addEventHandler(ClassEvents::Get());
	}
	if (mgr->dialogs)
	{
		mgr->dialogs->getEventDispatcher().addEventHandler(DialogEvents::Get());
	}
	if (mgr->menus)
	{
		mgr->menus->getEventDispatcher().addEventHandler(MenuEvents::Get());
	}
	if (mgr->textdraws)
	{
		mgr->textdraws->getEventDispatcher().addEventHandler(TextDrawEvents::Get());
	}
	if (mgr->pickups)
	{
		mgr->pickups->getEventDispatcher().addEventHandler(PickupEvents::Get());
	}
	if (mgr->vehicles)
	{
		mgr->vehicles->getEventDispatcher().addEventHandler(VehicleEvents::Get());
	}
	if (mgr->objects)
	{
		mgr->objects->getEventDispatcher().addEventHandler(ObjectEvents::Get());
	}
	if (mgr->console)
	{
		mgr->console->getEventDispatcher().addEventHandler(CoreEvents::Get(), EventPriority_Lowest);
	}
	if (mgr->gangzones)
	{
		mgr->gangzones->getEventDispatcher().addEventHandler(GangZoneEvents::Get());
	}
	if (mgr->models)
	{
		mgr->models->getEventDispatcher().addEventHandler(CustomModelsEvents::Get());
	}
	if (mgr->npcs)
	{
		mgr->npcs->getEventDispatcher().addEventHandler(NPCEvents::Get());
	}
}
