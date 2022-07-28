library(R6)

#' Queue
#'
#' @description An R6 class to define a FIFO queue equipped with push, pop, and
#' flush.
#'
Queue <- R6::R6Class(
  classname = "Queue",

  private = list(
    priorities = c(
      "FIFO",
      "LIFO"
    )
  ),

  public = list(
    priority = "FIFO",
    queue = list(),

    initialize = function(priority = NA_character_) {
      if (!is.na(priority) && self$isValidPriority(priority))
        self$priority <- priority
      invisible(self)
    },

    flush = function() {
      queue <- self$queue
      self$queue <- list()
      return(queue)
    },

    push = function(val) {
      if (self$isFIFO()) self$queue <- c(self$queue, list(val))
      if (self$isLIFO()) self$queue <- c(list(val), self$queue)
      invisible(self)
    },

    pop = function() {
      val <- self$queue[[1]]
      self$queue <- self$queue[[seq(2, self$size())]]
      return(val)
    },

    peek = function() {
      if (self$isEmpty()) stop("empty")
      return(self$queue[[1]])
    },

    size = function() {
      return(length(self$queue))
    },

    view = function() {
      return(self$queue)
    },

    vview = function() {
      return(unlist(self$view()))
    },

    isEmpty = function() {
      self$bifelse({
        !self$size()
      })
    },

    isFIFO = function() {
      self$bifelse({
        self$priority == "FIFO"
      })
    },

    isLIFO = function() {
      self$bifelse({
        self$priority == "LIFO"
      })
    },

    isValidPriority = function(string) {
      self$bifelse({
        eval(string) %in% private$priorities
      })
    },

    bifelse = function(expr) {
      return(ifelse(expr, TRUE, FALSE))
    }
  )
)
