# Makefile.am 
# RakNet configure script 
SUBDIRS=Autopatcher RakVoice .

lib_LTLIBRARIES=libRakNet.la


#RakNet headers 
libRakNet_ladir=$(includedir)/RakNet
libRakNet_la_HEADERS=\
	AES128.h\
	ArrayList.h\
	AsynchronousFileIO.h\
	BigTypes.h\
	BinarySearchTree.h\
	BitStream.h\
	CheckSum.h\
	ClientContextStruct.h\
	DataBlockEncryptor.h\
	DistributedNetworkObject.h\
	DistributedNetworkObjectHeader.h\
	DistributedNetworkObjectManager.h\
	DistributedNetworkObjectStub.h\
	EncodeClassName.h\
	ExtendedOverlappedPool.h\
	GetTime.h\
	HuffmanEncodingTree.h\
	HuffmanEncodingTreeFactory.h\
	HuffmanEncodingTreeNode.h\
	InternalPacket.h\
	InternalPacketPool.h\
	LinkedList.h\
	MTUSize.h\
	Multiplayer.h\
	NetworkObject.h\
	NetworkTypes.h\
	PacketEnumerations.h\
	PacketPool.h\
	PacketPriority.h\
	Queue.h\
	QueueLinkedList.h\
	RPCNode.h\
	RSACrypt.h\
	RakClient.h\
	RakClientInterface.h\
	RakNetStatistics.h\
	RakNetworkFactory.h\
	RakPeer.h\
	RakPeerInterface.h\
	RakServer.h\
	RakServerInterface.h\
	Rand.h\
	ReliabilityLayer.h\
	SHA1.h\
	SimpleMutex.h\
	SocketLayer.h\
	StringCompressor.h\
	Types.h
	
#RakNet sources files 
libRakNet_la_SOURCES=\
	AES128.cpp\
	AsynchronousFileIO.cpp\
	units/unit_f8445c5db1.cpp\
	units/unit_cbd71b5f7c.cpp\
	units/unit_1f4c625522.cpp\
	DistributedNetworkObject.cpp\
	DistributedNetworkObjectManager.cpp\
	DistributedNetworkObjectStub.cpp\
	EncodeClassName.cpp\
	ExtendedOverlappedPool.cpp\
	units/unit_0afb81ff97.cpp\
	HuffmanEncodingTree.cpp\
	HuffmanEncodingTreeFactory.cpp\
	units/unit_dc8b5c8649.cpp\
	NetworkObject.cpp\
	units/unit_bb5a915b2b.cpp\
	PacketPool.cpp\
	RPCNode.cpp\
	units/unit_2a62b2f46f.cpp\
	RakNetStatistics.cpp\
	units/unit_554cb846be.cpp\
	units/unit_7ed702d592.cpp\
	RakServer.cpp\
	units/unit_529d18f773.cpp\
	units/unit_5402bd0184.cpp\
	units/unit_a18336a76c.cpp\
	units/unit_37cf50734f.cpp\
	units/unit_8a2439532b.cpp\
	units/unit_222e652ebd.cpp

if BUILD_RAKVOICE 

if   BUILD_MONOLITHIC
libRakNet_la_LIBADD=\
	Autopatcher/libRakNet_autopatcher.la\
	RakVoice/libRakNet_voice.la
else 
libRakNet_la_LIBADD=\
	Autopatcher/libRakNet_autopatcher.la
endif 

else 
libRakNet_la_LIBADD=\
	Autopatcher/libRakNet_autopatcher.la
endif 
