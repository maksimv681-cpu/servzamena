if(WIN32)
	add_definitions(
		-D_CRT_SECURE_NO_WARNINGS
		-D_WINSOCK_DEPRECATED_NO_WARNINGS
		-DWIN32_LEAN_AND_MEAN
	)
endif()

set(RAKNET_SOURCES
	Source/units/unit_f8445c5db1.cpp
	Source/units/unit_cbd71b5f7c.cpp
	Source/units/unit_1ac900aff4.cpp
	Source/units/unit_9e21cde4cc.cpp
	Source/units/unit_1f4c625522.cpp
	Source/units/unit_d1367e9be8.cpp
	Source/units/unit_0afb81ff97.cpp
	Source/units/unit_dc8b5c8649.cpp
	Source/units/unit_bb5a915b2b.cpp
	Source/units/unit_2a62b2f46f.cpp
	Source/units/unit_0b6d72dfc4.cpp
	Source/units/unit_554cb846be.cpp
	Source/units/unit_7ed702d592.cpp
	Source/units/unit_08fb70f9b4.cpp
	Source/units/unit_f3c2142dc1.cpp
	Source/units/unit_529d18f773.cpp
	Source/units/unit_5402bd0184.cpp
	Source/units/unit_c62e8dd2d6.cpp
	Source/units/unit_3a475c0fd0.cpp
	Source/units/unit_a18336a76c.cpp
	Source/units/unit_37cf50734f.cpp
	Source/units/unit_8a2439532b.cpp
	Source/units/unit_222e652ebd.cpp
	Source/units/unit_a4662af6b3.cpp
	Source/units/unit_5fc4b54d9a.cpp
	units/unit_938e4f4533.cpp
)

add_library(raknet STATIC ${RAKNET_SOURCES})

set_property(TARGET raknet PROPERTY POSITION_INDEPENDENT_CODE ON)

target_compile_definitions(raknet
	PUBLIC
		-DRAKNET_LEGACY
		-DPACKETS_PER_TICK=3
)
target_include_directories(raknet 
	INTERFACE Include
	PRIVATE Include/raknet
)

if (WIN32)
	target_link_libraries(raknet Ws2_32 OMP-SDK)
else()
	target_link_libraries(raknet OMP-SDK)
endif()
