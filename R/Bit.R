library(R6)

Bit <- R6::R6Class(
  classname = "Bit",

  private = list(

  ),

  public = list(

    map = list(
      "int8"   = 8L,
      "uint8"  = 8L,
      "int16"  = 16L,
      "uint16" = 16L,
      "int32"  = 32L,
      "uint32" = 32L,
      "int64"  = 64L,
      "uint64" = 64L,
      "float"  = 32L
    ),

    initialize = function(...) {
      args = list(...)

      invisible(self)
    }

  )
)
