library(R6)

Template <- R6::R6Class(
  classname = "Template",

  private = list(

  ),

  public = list(

    initialize = function(...) {
      args = list(...)

      invisible(self)
    }

  )
)
