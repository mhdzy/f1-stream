library(R6)

PacketHeader <- R6::R6Class(
  classname = "PacketHeader",

  private = list(

  ),

  public = list(

    PacketHeader = list(
      "uint16" = "m_packetFormat",                 # 2021
      "uint8"  = "m_gameMajorVersion",             # Game major version - "X.00"
      "uint8"  = "m_gameMinorVersion",             # Game minor version - "1.XX"
      "uint8"  = "m_packetVersion",                # Version of this packet type, all start from 1
      "uint8"  = "m_packetId",                     # Identifier for the packet type, see below
      "uint64" = "m_sessionUID",                   # Unique identifier for the session
      "float"  = "m_sessionTime",                  # Session timestamp
      "uint32" = "m_frameIdentifier",              # Identifier for the frame the data was retrieved on
      "uint8"  = "m_playerCarIndex",               # Index of player's car in the array
      "uint8"  = "m_secondaryPlayerCarIndex"       # Index of secondary player's car in the array (split-screen) 255 if no second player
    ),

    initialize = function(...) {
      args = list(...)

      invisible(self)
    }

  )
)
