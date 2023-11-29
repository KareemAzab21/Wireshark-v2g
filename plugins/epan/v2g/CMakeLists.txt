# CMakeLists.txt
#
# Wireshark - Network traffic analyzer
# By Gerald Combs <gerald@wireshark.org>
# Copyright 1998 Gerald Combs
#
# SPDX-License-Identifier: GPL-2.0-or-later
#

include(WiresharkPlugin)

# Plugin name and version info (major minor micro extra)
set_module_info(v2gtp 0 0 4 0)

set(DISSECTOR_SRC
	packet-v2gexi.c
	packet-v2gtp.c
	#V2G_Facilities/iso2EXIDatatypes.c
	#V2G_Facilities/appHandEXIDatatypes.c
	#V2G_Facilities/appHandEXIDatatypesDecoder.c
	#V2G_Facilities/iso2EXIDatatypesDecoder.c
	#V2G_Facilities/EXIHeaderDecoder.c
	#V2G_Facilities/DecoderChannel.c
	#V2G_Facilities/BitInputStream.c
	#V2G_Facilities/Fac.c
	#V2G_Facilities/MethodsBag.c
)

set(PLUGIN_FILES
	plugin.c
	${DISSECTOR_SRC}
)

set_source_files_properties(
	${PLUGIN_FILES}
	PROPERTIES
	# COMPILE_FLAGS "${WERROR_COMMON_FLAGS}"
)

register_plugin_files(plugin.c
	plugin
	${DISSECTOR_SRC}
)

add_wireshark_plugin_library(v2gtp epan)

target_link_libraries(v2gtp epan)

install_plugin(v2gtp epan)

file(GLOB DISSECTOR_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h")
file(GLOB DISSECTOR_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "V2G_Facilities/*.h")
CHECKAPI(
	NAME
	  v2gtp
	SWITCHES
	  --group dissectors-prohibited
	  --group dissectors-restricted
	SOURCES
	  ${DISSECTOR_SRC}
	  ${DISSECTOR_HEADERS}
)

#
# Editor modelines  -  https://www.wireshark.org/tools/modelines.html
#
# Local variables:
# c-basic-offset: 8
# tab-width: 8
# indent-tabs-mode: t
# End:
#
# vi: set shiftwidth=8 tabstop=8 noexpandtab:
# :indentSize=8:tabSize=8:noTabs=false:
#
