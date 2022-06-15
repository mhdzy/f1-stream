library(R6)

#' RawByteParser
#'
#' @description An R6 class to parse raw bytes in a file.
#'
RawByteParser <- R6::R6Class(
  classname = "RawByteParser",

  public = list(
    file = NULL,
    filename = NA_character_,

    initialize = function(...) {
      args <- list(...)

      if ("filename" %in% names(args)) self$filename <- args$filename

      return(self)
    },

    file_is_open = function() {
      tryCatch({
        isOpen(self$fptr)
      }, error = function(e) {
        FALSE
      })
    },

    file_open = function(filename = NULL) {
      if (is.null(filename)) filename <- self$filename
      print(filename)
      if (!self$file_is_open()) self$file <- file(filename, "rb")
      return(self)
    },

    file_close = function() {
      if (self$file_is_open()) close(self$file)
      return(self)
    },

    read_byte = function() {
      return(readBin(self$file, raw(), 1L))
    },

    read_bytes = function(width = 1L) {
      stack <- Stack$new()
      for (i in seq(width)) {
        stack$push(self$read_byte())
      }
      bytes <- stack$flush()
      return(bytes)
    }
  )
)
