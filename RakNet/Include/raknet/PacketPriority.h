/// \file
/// \brief This file contains enumerations for packet priority and reliability enumerations.
///
/// This file is part of RakNet Copyright 2003 Kevin Jenkins.
///
/// Usage of RakNet is subject to the appropriate license agreement.
/// Creative Commons Licensees are subject to the
/// license found at
/// http://creativecommons.org/licenses/by-nc/2.5/
/// Single application licensees are subject to the license found at
/// http://www.rakkarsoft.com/SingleApplicationLicense.html
/// Custom license users are subject to the terms therein.
/// GPL license users are subject to the GNU General Public
/// License as published by the Free
/// Software Foundation; either version 2 of the License, or (at your
/// option) any later version.

#ifndef __PACKET_PRIORITY_H
#define __PACKET_PRIORITY_H 

namespace RakNet
{
	/// These enumerations are used to describe when packets are delivered.
	enum PacketPriority
	{
		SYSTEM_PRIORITY,   /// \internal Used by RakNet to send above-high priority messages.
		HIGH_PRIORITY,   /// High priority messages are send before medium priority messages.
		MEDIUM_PRIORITY,   /// Medium priority messages are send before low priority messages.
		LOW_PRIORITY,   /// Low priority messages are only sent when no other messages are waiting.
		NUMBER_OF_PRIORITIES
	};

	/// These enumerations are used to describe how packets are delivered.
	/// \note  Note to self: I write this with 3/4 bits in the stream.  If I add more remember to change that
	enum PacketReliability
{
    UNRELIABLE = 0,
    UNRELIABLE_SEQUENCED = 1,
    RELIABLE = 2,
    RELIABLE_ORDERED = 3,
    RELIABLE_SEQUENCED = 4
};
}

#endif
