library(R6)

#' Struct
#'
#' @description An R6 class to define some C primitives.
#'
Struct <- R6::R6Class(
  classname = "Struct",

  public = list(
    bitmap = list(
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

    bytemap = list(

    ),

    structs = list(
      PacketHeader = list(
        "uint16" = "m_packetFormat",                # 2021
        "uint8" = "m_gameMajorVersion",             # Game major version - "X.00"
        "uint8" = "m_gameMinorVersion",             # Game minor version - "1.XX"
        "uint8" = "m_packetVersion",                # Version of this packet type, all start from 1
        "uint8" = "m_packetId",                     # Identifier for the packet type, see below
        "uint64" = "m_sessionUID",                  # Unique identifier for the session
        "float" = "m_sessionTime",                  # Session timestamp
        "uint32" = "m_frameIdentifier",             # Identifier for the frame the data was retrieved on
        "uint8" = "m_playerCarIndex",               # Index of player's car in the array
        "uint8" = "m_secondaryPlayerCarIndex"       # Index of secondary player's car in the array (split-screen) 255 if no second player
      ),

      CarMotionData = list(
        "float" = "m_worldPositionX",               # World space X position
        "float" = "m_worldPositionY",               # World space Y position
        "float" = "m_worldPositionZ",               # World space Z position
        "float" = "m_worldVelocityX",               # Velocity in world space X
        "float" = "m_worldVelocityY",               # Velocity in world space Y
        "float" = "m_worldVelocityZ",               # Velocity in world space Z
        "int16" = "m_worldForwardDirX",             # World space forward X direction (normalised)
        "int16" = "m_worldForwardDirY",             # World space forward Y direction (normalised)
        "int16" = "m_worldForwardDirZ",             # World space forward Z direction (normalised)
        "int16" = "m_worldRightDirX",               # World space right X direction (normalised)
        "int16" = "m_worldRightDirY",               # World space right Y direction (normalised)
        "int16" = "m_worldRightDirZ",               # World space right Z direction (normalised)
        "float" = "m_gForceLateral",                # Lateral G-Force component
        "float" = "m_gForceLongitudinal",           # Longitudinal G-Force component
        "float" = "m_gForceVertical",               # Vertical G-Force component
        "float" = "m_yaw",                          # Yaw angle in radians
        "float" = "m_pitch",                        # Pitch angle in radians
        "float" = "m_roll"                          # Roll angle in radians
      ),

      MarshalZone = list(
        "float" = "m_zoneStart",                    # Fraction (0..1) of way through the lap the marshal zone starts
        "int8"  = "m_zoneFlag"                      # -1 = invalid/unknown, 0 = none, 1 = green, 2 = blue, 3 = yellow, 4 = red
      ),

      WeatherForecastSample = list(
        "uint8" = "m_sessionType",                  # 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P, 5 = Q1,
                                                    # 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ, 10 = R, 11 = R2,
                                                    # 12 = Time Trial
        "uint8" = "m_timeOffset",                   # Time in minutes the forecast is for
        "uint8" = "m_weather",                      # 0 = clear, 1 = light cloud, 2 = overcast,
                                                    # 3 = light rain, 4 = heavy rain, 5 = storm
        "int8" = "m_trackTemperature",              # Track temp. in degrees Celsius
        "int8" = "m_trackTemperatureChange",        # Track temp. change – 0 = up, 1 = down, 2 = no change
        "int8" = "m_airTemperature",                # Air temp. in degrees celsius
        "int8" = "m_airTemperatureChange",          # Air temp. change – 0 = up, 1 = down, 2 = no change
        "uint8" = "m_rainPercentage"                # Rain percentage (0-100)
      ),

      LapData = list(
        "uint32" = "m_lastLapTimeInMS",             # Last lap time in milliseconds
        "uint32" = "m_currentLapTimeInMS",          # Current time around the lap in milliseconds
        "uint16" = "m_sector1TimeInMS",             # Sector 1 time in milliseconds
        "uint16" = "m_sector2TimeInMS",             # Sector 2 time in milliseconds
        "float" = "m_lapDistance",                  # Distance vehicle is around current lap in metres – could be negative if line hasn’t been crossed yet
        "float" = "m_totalDistance",                # Total distance travelled in session in metres – could be negative if line hasn’t been crossed yet
        "float" = "m_safetyCarDelta",               # Delta in seconds for safety car
        "uint8" = "m_carPosition",                  # Car race position
        "uint8" = "m_currentLapNum",                # Current lap number
        "uint8" = "m_pitStatus",                    # 0 = none, 1 = pitting, 2 = in pit area
        "uint8" = "m_numPitStops",                  # Number of pit stops taken in this race
        "uint8" = "m_sector",                       # 0 = sector1, 1 = sector2, 2 = sector3
        "uint8" = "m_currentLapInvalid",            # Current lap invalid - 0 = valid, 1 = invalid
        "uint8" = "m_penalties",                    # Accumulated time penalties in seconds to be added
        "uint8" = "m_warnings",                     # Accumulated number of warnings issued
        "uint8" = "m_numUnservedDriveThroughPens",  # Num drive through pens left to serve
        "uint8" = "m_numUnservedStopGoPens",        # Num stop go pens left to serve
        "uint8" = "m_gridPosition",                 # Grid position the vehicle started the race in
        "uint8" = "m_driverStatus",                 # Status of driver - 0 = in garage, 1 = flying lap, 2 = in lap, 3 = out lap, 4 = on track
        "uint8" = "m_resultStatus",                 # Result status - 0 = invalid, 1 = inactive, 2 = active, 3 = finished, 4 = didnotfinish, 5 = disqualified, 6 = not classified, 7 = retired
        "uint8" = "m_pitLaneTimerActive",           # Pit lane timing, 0 = inactive, 1 = active
        "uint16" = "m_pitLaneTimeInLaneInMS",       # If active, the current time spent in the pit lane in ms
        "uint16" = "m_pitStopTimerInMS",            # Time of the actual pit stop in ms
        "uint8" = "m_pitStopShouldServePen"         # Whether the car should serve a penalty at this stop
      ),

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

      ParticipantData = list(
        "uint8" = "m_aiControlled",                 # Whether the vehicle is AI (1) or Human (0) controlled
        "uint8" = "m_driverId",                     # Driver id - see appendix, 255 if network human
        "uint8" = "m_networkId",                    # Network id – unique identifier for network players
        "uint8" = "m_teamId",                       # Team id - see appendix
        "uint8" = "m_myTeam",                       # My team flag – 1 = My Team, 0 = otherwise
        "uint8" = "m_raceNumber",                   # Race number of the car
        "uint8" = "m_nationality",                  # Nationality of the driver
        "char" = "m_name[48]",                      # Name of participant in UTF-8 format – null terminated. Will be truncated with … (U+2026) if too long
        "uint8" = "m_yourTelemetry"                 # The player's UDP setting, 0 = restricted, 1 = public
      ),

      CarSetupData = list(
        "uint8" = "m_frontWing",                    # Front wing aero
        "uint8" = "m_rearWing",                     # Rear wing aero
        "uint8" = "m_onThrottle",                   # Differential adjustment on throttle (percentage)
        "uint8" = "m_offThrottle",                  # Differential adjustment off throttle (percentage)
        "float" = "m_frontCamber",                  # Front camber angle (suspension geometry)
        "float" = "m_rearCamber",                   # Rear camber angle (suspension geometry)
        "float" = "m_frontToe",                     # Front toe angle (suspension geometry)
        "float" = "m_rearToe",                      # Rear toe angle (suspension geometry)
        "uint8" = "m_frontSuspension",              # Front suspension
        "uint8" = "m_rearSuspension",               # Rear suspension
        "uint8" = "m_frontAntiRollBar",             # Front anti-roll bar
        "uint8" = "m_rearAntiRollBar",              # Front anti-roll bar
        "uint8" = "m_frontSuspensionHeight",        # Front ride height
        "uint8" = "m_rearSuspensionHeight",         # Rear ride height
        "uint8" = "m_brakePressure",                # Brake pressure (percentage)
        "uint8" = "m_brakeBias",                    # Brake bias (percentage)
        "float" = "m_rearLeftTyrePressure",         # Rear left tyre pressure (PSI)
        "float" = "m_rearRightTyrePressure",        # Rear right tyre pressure (PSI)
        "float" = "m_frontLeftTyrePressure",        # Front left tyre pressure (PSI)
        "float" = "m_frontRightTyrePressure",       # Front right tyre pressure (PSI)
        "uint8" = "m_ballast",                      # Ballast
        "float" = "m_fuelLoad"                      #  Fuel load
      ),

      CarTelemetryData = list(
        "uint16" = "m_speed",                       # Speed of car in kilometres per hour
        "float" = "m_throttle",                     # Amount of throttle applied (0.0 to 1.0)
        "float" = "m_steer",                        # Steering (-1.0 (full lock left) to 1.0 (full lock right))
        "float" = "m_brake",                        # Amount of brake applied (0.0 to 1.0)
        "uint8" = "m_clutch",                       # Amount of clutch applied (0 to 100)
        "int8" = "m_gear",                          # Gear selected (1-8, N=0, R=-1)
        "uint16" = "m_engineRPM",                   # Engine RPM
        "uint8" = "m_drs",                          # 0 = off, 1 = on
        "uint8" = "m_revLightsPercent",             # Rev lights indicator (percentage)
        "uint16" = "m_revLightsBitValue",           # Rev lights (bit 0 = leftmost LED, bit 14 = rightmost LED)
        "uint16" = "m_brakesTemperature[4]",        # Brakes temperature (celsius)
        "uint8" = "m_tyresSurfaceTemperature[4]",   # Tyres surface temperature (celsius)
        "uint8" = "m_tyresInnerTemperature[4]",     # Tyres inner temperature (celsius)
        "uint16" = "m_engineTemperature",           # Engine temperature (celsius)
        "float" = "m_tyresPressure[4]",             # Tyres pressure (PSI)
        "uint8" = "m_surfaceType[4]"                # Driving surface, see appendices
      ),

      CarStatusData = list(
        "uint8" = "m_tractionControl",          # Traction control - 0 = off, 1 = medium, 2 = full
        "uint8" = "m_antiLockBrakes",           # 0 (off) - 1 (on)
        "uint8" = "m_fuelMix",                  # Fuel mix - 0 = lean, 1 = standard, 2 = rich, 3 = max
        "uint8" = "m_frontBrakeBias",           # Front brake bias (percentage)
        "uint8" = "m_pitLimiterStatus",         # Pit limiter status - 0 = off, 1 = on
        "float" = "m_fuelInTank",               # Current fuel mass
        "float" = "m_fuelCapacity",             # Fuel capacity
        "float" = "m_fuelRemainingLaps",        # Fuel remaining in terms of laps (value on MFD)
        "uint16" = "m_maxRPM",                   # Cars max RPM, point of rev limiter
        "uint16" = "m_idleRPM",                  # Cars idle RPM
        "uint8" = "m_maxGears",                 # Maximum number of gears
        "uint8" = "m_drsAllowed",               # 0 = not allowed, 1 = allowed
        "uint16" = "m_drsActivationDistance",    # 0 = DRS not available, non-zero - DRS will be available in [X] metres
        "uint8" = "m_actualTyreCompound",	  
                                                # F1 Modern - 16 = C5, 17 = C4, 18 = C3, 19 = C2, 20 = C1, 7 = inter, 8 = wet
                                                # F1 Classic - 9 = dry, 10 = wet
                                                # F2 – 11 = super soft, 12 = soft, 13 = medium, 14 = hard 15 = wet
        "uint8" = "m_visualTyreCompound",       # F1 visual (can be different from actual compound)
                                                # 16 = soft, 17 = medium, 18 = hard, 7 = inter, 8 = wet
                                                # F1 Classic – same as above
                                                # F2 ‘19, 15 = wet, 19 – super soft, 20 = soft
                                                # 21 = medium , 22 = hard
        "uint8" = "m_tyresAgeLaps",             # Age in laps of the current set of tyres
        "int8" = "m_vehicleFiaFlags",	        # -1 = invalid/unknown, 0 = none, 1 = green
                                                # 2 = blue, 3 = yellow, 4 = red
        "float" = "m_ersStoreEnergy",           # ERS energy store in Joules
        "uint8" = "m_ersDeployMode",            # ERS deployment mode, 0 = none, 1 = medium, 2 = hotlap, 3 = overtake
        "float" = "m_ersHarvestedThisLapMGUK",  # ERS energy harvested this lap by MGU-K
        "float" = "m_ersHarvestedThisLapMGUH",  # ERS energy harvested this lap by MGU-H
        "float" = "m_ersDeployedThisLap",       # ERS energy deployed this lap
        "uint8" = "m_networkPaused"            # Whether the car is paused in a network game
      )
    ),

    packets = list(
      PacketMotionData = list(
        "PacketHeader" = "m_header",                # Header

        "CarMotionData" = "m_carMotionData[22]",    #  Data for all cars on track, Extra player car ONLY data
        "float" = "m_suspensionPosition[4]",        #  Note: All wheel arrays have the following order:
        "float" = "m_suspensionVelocity[4]",        #  RL, RR, FL, FR
        "float" = "m_suspensionAcceleration[4]",    #  RL, RR, FL, FR
        "float" = "m_wheelSpeed[4]",                #  Speed of each wheel
        "float" = "m_wheelSlip[4]",                 #  Slip ratio for each wheel
        "float" = "m_localVelocityX",               #  Velocity in local space
        "float" = "m_localVelocityY",               #  Velocity in local space
        "float" = "m_localVelocityZ",               #  Velocity in local space
        "float" = "m_angularVelocityX",             #  Angular velocity x-component
        "float" = "m_angularVelocityY",             #  Angular velocity y-component
        "float" = "m_angularVelocityZ",             #  Angular velocity z-component
        "float" = "m_angularAccelerationX",         #  Angular velocity x-component
        "float" = "m_angularAccelerationY",         #  Angular velocity y-component
        "float" = "m_angularAccelerationZ",         #  Angular velocity z-component
        "float" = "m_frontWheelsAngle"              #  Current front wheels angle in radians
      ),

      PacketSessionData = list(
        "PacketHeader" = "m_header",                # Header

        "uint8" = "m_weather",                      # 0 = clear, 1 = light cloud, 2 = overcast, 3 = light rain, 4 = heavy rain, 5 = storm
        "int8" = "m_trackTemperature",              # Track temp. in degrees celsius
        "int8" = "m_airTemperature",                # Air temp. in degrees celsius
        "uint8" = "m_totalLaps",                    # Total number of laps in this race
        "uint16" = "m_trackLength",                 # Track length in metres
        "uint8" = "m_sessionType",                  # 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P, 5 = Q1, 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ, 10 = R, 11 = R2, 12 = R3, 13 = Time Trial
        "int8" = "m_trackId",                       # -1 for unknown, 0-21 for tracks, see appendix
        "uint8"  = "m_formula",                     # Formula, 0 = F1 Modern, 1 = F1 Classic, 2 = F2, 3 = F1 Generic
        "uint16" = "m_sessionTimeLeft",             # Time left in session in seconds
        "uint16" = "m_sessionDuration",             # Session duration in seconds
        "uint8" = "m_pitSpeedLimit",                # Pit speed limit in kilometres per hour
        "uint8" = "m_gamePaused",                   # Whether the game is paused
        "uint8" = "m_isSpectating",                 # Whether the player is spectating
        "uint8" = "m_spectatorCarIndex",            # Index of the car being spectated
        "uint8" = "m_sliProNativeSupport",          # SLI Pro support, 0 = inactive, 1 = active
        "uint8" = "m_numMarshalZones",              # Number of marshal zones to follow
        "MarshalZone" = "m_marshalZones[21]",       # List of marshal zones – max 21
        "uint8" = "m_safetyCarStatus",              # 0 = no safety car, 1 = full, 2 = virtual, 3 = formation lap
        "uint8" = "m_networkGame",                  # 0 = offline, 1 = online
        "uint8" = "m_numWeatherForecastSamples",    # Number of weather samples to follow
        "WeatherForecastSample" = "m_weatherForecastSamples[56]",    # Array of weather forecast samples
        "uint8" = "m_forecastAccuracy",             # 0 = Perfect, 1 = Approximate
        "uint8" = "m_aiDifficulty",                 # AI Difficulty rating – 0-110
        "uint32" = "m_seasonLinkIdentifier",        # Identifier for season - persists across saves
        "uint32" = "m_weekendLinkIdentifier",       # Identifier for weekend - persists across saves
        "uint32" = "m_sessionLinkIdentifier",       # Identifier for session - persists across saves
        "uint8" = "m_pitStopWindowIdealLap",        # Ideal lap to pit on for current strategy (player)
        "uint8" = "m_pitStopWindowLatestLap",       # Latest lap to pit on for current strategy (player)
        "uint8" = "m_pitStopRejoinPosition",        # Predicted position to rejoin at (player)
        "uint8" = "m_steeringAssist",               # 0 = off, 1 = on
        "uint8" = "m_brakingAssist",                # 0 = off, 1 = low, 2 = medium, 3 = high
        "uint8" = "m_gearboxAssist",                # 1 = manual, 2 = manual & suggested gear, 3 = auto
        "uint8" = "m_pitAssist",                    # 0 = off, 1 = on
        "uint8" = "m_pitReleaseAssist",             # 0 = off, 1 = on
        "uint8" = "m_ERSAssist",                    # 0 = off, 1 = on
        "uint8" = "m_DRSAssist",                    # 0 = off, 1 = on
        "uint8" = "m_dynamicRacingLine",            # 0 = off, 1 = corners only, 2 = full
        "uint8" = "m_dynamicRacingLineType"         # 0 = 2D, 1 = 3D
      ),

      PacketLapData = list(
        "PacketHeader" = "m_header",                #  Header
        "LapData" = "m_lapData[22]"                 # Lap data for all cars on track
      ),

      PacketEventData = list(
        "PacketHeader" = "m_header",                # Header
        "uint8" = "m_eventStringCode[4]",           # Event string code, see below
        "EventDataDetails" = "m_eventDetails"       # Event details - should be interpreted differently for each type
      ),

      PacketParticipantsData = list(
        "PacketHeader" = "m_header",                # Header
        "uint8" = "m_numActiveCars",                # Number of active cars in the data – should match number of cars on HUD
        "ParticipantData" = "m_participants[22]"
      ),

      PacketCarSetupData = list(
        "PacketHeader" = "m_header",                # Header
        "CarSetupData" = "m_carSetups[22]"
      ),
      
      PacketCarTelemetryData = list(
        "PacketHeader" = "m_header",                # Header

        "CarTelemetryData" = "m_carTelemetryData[22]",
        "uint8" = "m_mfdPanelIndex",                # Index of MFD panel open - 255 = MFD closed
                                                    # Single player, race – 0 = Car setup, 1 = Pits
                                                    # 2 = Damage, 3 =  Engine, 4 = Temperatures
                                                    # May vary depending on game mode
        "uint8" = "m_mfdPanelIndexSecondaryPlayer", # See above
        "int8" = "m_suggestedGear"                  # Suggested gear for the player (1-8), 0 if no gear suggested
      ),

      PacketCarStatusData = list(
        "PacketHeader" = "m_header",                # Header
        "CarStatusData" = "m_carStatusData[22]"
      )
    ),

    initialize = function(...) {
      args <- list(...)

      self$bytemap <- lapply(self$bitmap, function(x) x / 8L)

      return(self)
    },

    structToBits = function(name) {
      sset_names <- function(x, y) x[[which(names(x) == y)]]
      struct <- sset_names(self$structs, name)
      # self$structs[[which(names(self$structs) == name)]]
      return(
        setNames(
          lapply(
            names(struct),
            function(x) sset_names(self$bitmap, x)
            #function(x) self$bitmap[[which(names(self$bitmap) == x)]]
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
