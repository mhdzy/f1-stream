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

      invisible(self)
    },

    isOpen = function() {
      tryCatch({
        isOpen(self$fptr)
      }, error = function(e) {
        FALSE
      })
    },

    fOpen = function(filename = NULL) {
      if (is.null(filename)) filename <- self$filename
      if (!self$isOpen()) self$file <- file(filename, "rb")
      invisible(self)
    },

    fClose = function() {
      if (self$isOpen()) close(self$file)
      invisible(self)
    },

    readByte = function() {
      return(readBin(self$file, raw(), 1L))
    },

    readBytes = function(width = 1L) {
      queue <- Queue$new()
      for (i in seq(width)) {
        queue$push(self$readByte())
      }
      bytes <- queue$flush()
      return(bytes)
    },

    bytesToInteger = function(bytes, width = 1L) {
      return(readBin(unlist(bytes), integer(), size = width))
    },

    rawListToInt = function(bytes) {
      result <- 0L
      for (i in seq_along(bytes)) {
        browser()
        result <- result + bitwShiftL(bytes[[i]], length(bytes) - i)
      }
      return(result)
    }
  )
)
