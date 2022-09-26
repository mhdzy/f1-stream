
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

SLEEP_INTERVAL = 10;
while (TRUE) {
  telemetrydata <- read_f1data(
    track = "test",
    packets = "CarTelemetry"
  )

  motiondata <- read_f1data(
    track = "test",
    packets = "Motion"
  )

  res <- dplyr::left_join(
    motiondata$Motion,
    telemetrydata$CarTelemetry,
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

  Sys.sleep(SLEEP_INTERVAL);
}







### OTHER SMALL PLOTTING STUFF? IDK ###


if (FALSE) {

  # check out DRS deployment
  f1data$status |>
    dplyr::filter(m_carID %in% ids) |>
    dplyr::pull(m_drsActivationDistance) |>
    plot()

  # show engine RPM
  telemetrydata |>
    dplyr::filter(m_carID %in% ids) |>
    dplyr::pull(m_speed) |>
    plot()

  # car 3 vs 10
  f1data <- motiondata |>
    dplyr::filter(m_carID %in% ids) |>
    dplyr::mutate(
      m_gForceLateralIntegral = m_gForceLateral %>% cumsum()
    )

  f1data |>
    dplyr::filter(m_carID %in% ids) |>
    #dplyr::filter(m_gForceLongitudinal > -50) |>
    ggplot2::ggplot(
      ggplot2::aes(
        x = m_frameIdentifier,
        #y = m_gForceLateral,
        y = m_gForceLateralIntegral,
        color = m_frameIdentifier
      )
    ) +
    ggplot2::geom_point()

  p1data <- f1data |>
    dplyr::filter(m_carID %in% ids) |>
    dplyr::distinct()

  options(rgl.printRglwidget = TRUE)
  rgl::plot3d(
    x = p1data$m_worldPositionX/32767,
    y = -1L * p1data$m_worldPositionZ/32767,
    z = p1data$m_worldPositionY/32767
  )

  l2 <- p1data |>
    dplyr::arrange(dplyr::desc(m_frameIdentifier)) |>
    dplyr::pull() |>
    stringr::str_split("/") |>
    base::unique() |>
    lapply(function(x) c('rl' = x[1], 'rr' = x[2], 'fl' = x[3], 'fr' = x[4])) |>
    dplyr::bind_rows() |>
    dplyr::distinct() |>
    dplyr::mutate_if(
      is.character,
      function(x) as.numeric(x)
    )

  plot(
    l2$rr/32767,
    l2$rl/32767
  )

  plot(
    l2$fr/32767,
    l2$fl/32767
  )

}
