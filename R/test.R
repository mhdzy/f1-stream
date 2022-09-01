
## f1 stuff

library(dplyr)
library(readr)

track <- "multiplayer"

{
  motiondata <- paste0("~/prog/f1/data/", track, "/parsed/Motion.csv") |>
    readr::read_csv() |>
    dplyr::arrange(m_frameIdentifier)

  sessiondata <- paste0("~/prog/f1/data/", track, "/parsed/Session.csv") |>
    readr::read_csv() |>
    dplyr::arrange(m_frameIdentifier)

  lapdata <- paste0("~/prog/f1/data/", track, "/parsed/LapData.csv") |>
    readr::read_csv() |>
    dplyr::arrange(m_frameIdentifier)

  eventdata <-paste0("~/prog/f1/data/", track, "/parsed/Event.csv") |>
    readr::read_csv() |>
    dplyr::arrange(m_frameIdentifier)

  setupdata <- paste0("~/prog/f1/data/", track, "/parsed/CarSetups.csv") |>
    readr::read_csv() |>
    dplyr::arrange(m_frameIdentifier)

  telemetrydata <- paste0("~/prog/f1/data/", track, "/parsed/CarTelemetry.csv") |>
    readr::read_csv() |>
    dplyr::arrange(m_frameIdentifier)

  participantdata <- paste0("~/prog/f1/data/", track, "/parsed/Participants.csv") |>
    readr::read_csv()

  statusdata <- paste0("~/prog/f1/data/", track, "/parsed/CarStatus.csv") |>
    readr::read_csv() |>
    dplyr::arrange(m_frameIdentifier)
}

if (FALSE) {
  pd <- participantdata |>
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

  fani_id <- pd |>
    dplyr::filter(m_name != "Sumosusa") |>
    dplyr::pull(m_carID)

  matej_id <- pd |>
    dplyr::filter(m_name == "Sumosusa") |>
    dplyr::pull(m_carID)
}

# check out ERS deployment
statusdata |>
  dplyr::filter(m_carID %in% ids) |>
  dplyr::pull(m_drsActivationDistance) |>
  plot()

# show engine RPM
telemetrydata |>
  dplyr::filter(m_carID %in% ids) |>
  dplyr::pull(m_speed) |>
  plot()

res <- dplyr::left_join(
  motiondata,
  telemetrydata,
  by = c("m_carID", "m_frameIdentifier")
) |> dplyr::filter(m_carID %in% 16)

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

