library(R6)

#' Struct
#'
#' @description An R6 class to define some C primitives.
#'
Struct <- R6::R6Class(
  classname = "Struct",

  public = list(
    bitmap = list(
      "uint8"  = 8L,
      "uint16" = 16L,
      "uint32" = 32L,
      "uint64" = 64L,
      "int8"   = 8L,
      "int16"  = 16L,
      "float"  = 32L
    ),

    bytemap = list(
    ),

    structs = list(
      PacketHeader = list(
        "uint16" = "m_packetFormat",
        "uint8"  = "m_gameMajorVersion",
        "uint8"  = "m_gameMinorVersion",
        "uint8"  = "m_packetVersion",
        "uint8"  = "m_packetId",
        "uint64" = "m_sessionUID",
        "float"  = "m_sessionTime",
        "uint32" = "m_frameIdentifier",
        "uint8"  = "m_playerCarIndex",
        "uint8"  = "m_secondaryPlayerCarIndex"
      )
    ),

    initialize = function(...) {
      args <- list(...)

      self$bytemap <- lapply(self$bitmap, function(x) x / 8L)

      return(self)
    },

    structToBits = function(name) {
      struct <- self$structs[[which(names(self$structs) == name)]]
      return(
        setNames(
          lapply(
            names(struct),
            function(x) self$bitmap[[which(names(self$bitmap) == x)]]
          ),
        as.vector(struct)
        )
      )
    },

    structToBytes = function(name) {
      return(
        lapply(self$structToBits(name), function(x) x / 8L)
      )
    }
  )
)
