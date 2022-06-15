library(R6)

#' Stack
#'
#' @description An R6 class to define a stack equipped with push, pop, and 
#' flush.
#'
Stack <- R6::R6Class(
  classname = "Stack",

  public = list(
    stack = list(),

    initialize = function() {

    },

    flush = function() {
      stack <- self$stack
      self$stack <- list()
      return(stack)
    },

    push = function(el) {
      self$stack <- c(list(el), self$stack)
      return(self)
    },

    pop = function() {
      el <- self$stack[[1]]
      self$stack <- self$stack[[2:length(self$stack)]]
      return(el)
    },

    size = function() {
      return(length(self$stack))
    }
  )
)
