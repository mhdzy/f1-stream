library(R6)

Template <- R6::R6Class(
  classname = "Template",

  private = list(

  ),

  public = list(

    map = list(
      "Header"              = list(id = -1L, size = 192L), # Contains the packet id number
      "Motion"              = list(id = 0L, size = 1464L), # Contains all motion data for player’s car – only sent while player is in control
      "Session"             = list(id = 1L, size = 625L),  # Data about the session – track, time left
      "LapData"             = list(id = 2L, size = 970L),  # Data about all the lap times of cars in the session
      "Event"               = list(id = 3L, size = 36L),   # Various notable events that happen during a session
      "Participants"        = list(id = 4L, size = 1257L), # List of participants in the session, mostly relevant for multiplayer
      "CarSetups"           = list(id = 5L, size = 1102L), # Packet detailing car setups for cars in the race
      "CarTelemetry"        = list(id = 6L, size = 1347L), # Telemetry data for all cars
      "CarStatus"           = list(id = 7L, size = 1058L), # Status data for all cars
      "FinalClassification" = list(id = 8L, size = 839L),  # Final classification confirmation at the end of a race
      "LobbyInfo"           = list(id = 9L, size = 1191L), # Information about players in a multiplayer lobby
      "CarDamage"           = list(id = 10L, size = 882L), # Damage status for all cars
      "SessionHistory"      = list(id = 11L, size = 1155L) # Lap and tyre data for session
    ),

    initialize = function(...) {
      args = list(...)

      invisible(self)
    }

  )
)
