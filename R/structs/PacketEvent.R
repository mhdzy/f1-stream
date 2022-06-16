library(R6)

Template <- R6::R6Class(
  classname = "Template",

  private = list(

  ),

  public = list(

    # only one of the below lists is parsed per data details event
    EventDataDetails = list(
      "FastestLap" = list(
        "uint8" = "vehicleIdx",                   # Vehicle index of car achieving fastest lap
        "float" = "lapTime"                       # Lap time is in seconds
      ),

      "Retirement" = list(
        "uint8" = "vehicleIdx"                    # Vehicle index of car retiring
      ),

      "TeamMateInPits" = list(
        "uint8" = "vehicleIdx"                    # Vehicle index of team mate
      ),

      "RaceWinner" = list(
        "uint8" = "vehicleIdx"                    # Vehicle index of the race winner
      ),
      "Penalty" = list(
        "uint8" = "penaltyType",                  # Penalty type – see Appendices
        "uint8" = "infringementType",             # Infringement type – see Appendices
        "uint8" = "vehicleIdx",                   # Vehicle index of the car the penalty is applied to
        "uint8" = "otherVehicleIdx",              # Vehicle index of the other car involved
        "uint8" = "time",                         # Time gained, or time spent doing action in seconds
        "uint8" = "lapNum",                       # Lap the penalty occurred on
        "uint8" = "placesGained"                  # Number of places gained by this
      ),

      "SpeedTrap" = list(
        "uint8" = "vehicleIdx",                   # Vehicle index of the vehicle triggering speed trap
        "float" = "speed",                        # Top speed achieved in kilometres per hour
        "uint8" = "overallFastestInSession",      # Overall fastest speed in session = 1, otherwise 0
        "uint8" = "driverFastestInSession"        # Fastest speed for driver in session = 1, otherwise 0
      ),
      
      "StartLights" = list(
        "uint8" = "numLights"                     # Number of lights showing
      ),
      "DriveThroughPenaltyServed" = list(
        "uint8" = "vehicleIdx"                    # Vehicle index of the vehicle serving drive through
      ),

      "StopGoPenaltyServed" = list(
        "uint8" = "vehicleIdx"                    # Vehicle index of the vehicle serving stop go
      ),
      "Flashback" = list(
        "uint32" = "flashbackFrameIdentifier",    # Frame identifier flashed back to
        "float" = "flashbackSessionTime"          # Session time flashed back to
      ),
      "Buttons" = list(
        "uint32" = "m_buttonStatus"               # Bit flags specifying which buttons are being pressed currently - see appendices
      )
    ),

    EventStringCodes = list(
      SSTA = c("Session Started" = "Sent when the session starts"),
      SEND = c("Session Ended" = "Sent when the session ends"),
      FTLP = c("Fastest Lap" = "When a driver achieves the fastest lap"),
      RTMT = c("Retirement" = "When a driver retires"),
      DRSE = c("DRS enabled" = "Race control have enabled DRS"),
      DRSD = c("DRS disabled" = "Race control have disabled DRS"),
      TMPT = c("Team mate in pits" = "Your team mate has entered the pits"),
      CHQF = c("Chequered flag" = "The chequered flag has been waved"),
      RCWN = c("Race Winner" = "The race winner is announced"),
      PENA = c("Penalty Issued" = "A penalty has been issued – details in event"),
      SPTP = c("Speed Trap Triggered" = "Speed trap has been triggered by fastest speed"),
      STLG = c("Start lights" = "Start lights – number shown"),
      LGOT = c("Lights out" = "Lights out"),
      DTSV = c("Drive through served" = "Drive through penalty served"),
      SGSV = c("Stop go served" = "Stop go penalty served"),
      FLBK = c("Flashback" = "Flashback activated"),
      BUTN = c("Button status" = "Button status changed")
    ),

    initialize = function(...) {
      args = list(...)

      invisible(self)
    }

  )
)
