
## f1 stuff

library(dplyr)
library(readr)

track <- "test"

packet_names <- list(
  "Motion",
  "Session",
  "LapData",
  "Event",
  "Participants",
  "CarSetups",
  "CarTelemetry",
  "CarStatus",
  "FinalClassification",
  "LobbyInfo",
  "CarDamage",
  "SessionHistory"
)

read_f1data <- function(
    dir = "~/prog/f1/data/",
    track = "spa",
    packets = list()
) {
  read_packet <- function(packet, ext = "csv") {
    paste0(dir, track, "/parsed/", packet, ".", ext) |>
      readr::read_csv()
  }

  arrange_packet_frameId <- function(packet) {
    if (!("m_frameIdentifier" %in% names(packet))) return(packet)
    packet |> dplyr::arrange(m_frameIdentifier)
  }

  p_tbls <- packets |>
    lapply(function(x) read_packet(x) |> arrange_packet_frameId()) |>
    setNames(packets)

  return(p_tbls)
}

f1data <- read_f1data(
  track = "test",
  packets = packet_names
)

{
  pd <- f1data$Participants |>
    dplyr::filter(
      m_nationality == 83,
      m_raceNumber %in% c(15, 69),
      m_yourTelemetry == 1
    ) |>
    dplyr::select(
      m_carID,
      m_name,
      m_networkId,
      m_teamId,
      m_nationality,
      m_raceNumber,
      m_yourTelemetry
    ) |>
    dplyr::distinct()

  ids <- pd |> dplyr::pull(m_carID)

  matej_id <- pd |>
    dplyr::filter(m_name == "Sumosusa") |>
    dplyr::pull(m_carID)

  fani_id <- pd |>
    dplyr::filter(m_name != "Sumosusa") |>
    dplyr::pull(m_carID)
}

library(magrittr)
library(shiny)
# library(promises)
# library(future)
# future::plan(multisession)

ui <- shiny::fluidPage(
  shiny::h4("hello!"),
  shiny::br(),
  shiny::plotOutput("graph")
)

server <- function(input, output, session) {
  TIMER_DELAY = 12L # seconds

  output$graph <- shiny::renderPlot({
    message("running")
    shiny::invalidateLater(TIMER_DELAY * 1000L) # translate seconds to millis

    vals <- list(
      motion = read_f1data(
        track = "test",
        packets = "Motion"
      ),
      telemetry = read_f1data(
        track = "test",
        packets = "CarTelemetry"
      )
    )

    pvals <- vals %>%
      {
        dplyr::left_join(
          .$motion$Motion,
          .$telemetry$CarTelemetry,
          by = c("m_carID", "m_frameIdentifier")
        )
      } |>
      dplyr::filter(m_carID %in% ids)

    pvals |>
      ggplot2::ggplot() +
      ggplot2::geom_point(
        ggplot2::aes(
          x = m_worldPositionX/32767L,
          y = -1L * m_worldPositionZ/32767L,
          fill = m_speed
        ),
        pch = 21,
        stroke = NA,
        size = 5
      ) +
      ggplot2::scale_color_gradient(
        low = "#c20c00",
        high = "#00c26d",
        aesthetics = "fill"
      ) +
      ggplot2::labs(
        x = "x",
        y = "y",
        title = "Multiplayer Lap Data"
      ) +
      ggplot2::facet_wrap(
        ~m_carID
      )
  })
}

shiny::shinyApp(ui, server)

while (TRUE) {

  res <- dplyr::left_join(
    f1data$Motion,
    f1data$CarTelemetry,
    by = c("m_carID", "m_frameIdentifier")
  ) |> dplyr::filter(m_carID %in% ids)

  # colored plot of spa laptime
  res |>
    ggplot2::ggplot() +
    ggplot2::geom_point(
      ggplot2::aes(
        x = m_worldPositionX/32767L,
        y = -1L * m_worldPositionZ/32767L,
        fill = m_speed
      ),
      pch = 21,
      stroke = NA,
      size = 5
    ) +
    ggplot2::scale_color_gradient(
      low = "#c20c00",
      high = "#00c26d",
      aesthetics = "fill"
    ) +
    ggplot2::labs(
      x = "x",
      y = "y",
      title = "Multiplayer Lap Data"
    ) + ggplot2::facet_wrap(~m_carID)

  Sys.sleep(SLEEP_INTERVAL)
}
