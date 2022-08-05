
## f1 stuff

library(dplyr)
library(readr)

track <- "singapore"

{
  testdata <- paste0("~/prog/f1/data/test-", track, "-lap-data-parsed.csv") |>
    readr::read_csv()

  lapdata <- paste0("~/prog/f1/data/", track, "-lap-data-parsed.csv") |>
    readr::read_csv() |>
    dplyr::arrange(m_frameIdentifier)

  # sessiondata <- paste0("~/prog/f1/data/", track, "-session-data-parsed.csv") |>
  #  readr::read_csv()

  f1data <- testdata
}

f1data |>
  dplyr::filter(m_carID == 0) |>
  ggplot2::ggplot(
    ggplot2::aes(
      x = m_worldPositionX/32767L,
      y = -1L * m_worldPositionZ/32767L,
      color = m_frameIdentifier
    )
  ) +
  ggplot2::geom_point()

f1data |>
  dplyr::filter(m_carID == 0) |>
  ggplot2::ggplot(
    ggplot2::aes(
      x = m_frameIdentifier,
      y = m_gForceLongitudinal,
      #y = m_gForceLateral,
      color = m_frameIdentifier
    )
  ) +
  ggplot2::geom_point()

p1data <- f1data |>
  dplyr::filter(m_carID == 0) |>
  dplyr::distinct()

options(rgl.printRglwidget = TRUE)
rgl::plot3d(
  x = p1data$m_worldPositionX/32767,
  y = -1L * p1data$m_worldPositionZ/32767,
  z = p1data$m_worldPositionY/32767
)

l2 <- p1data |>
  dplyr::arrange(dplyr::desc(m_frameIdentifier)) |>
  dplyr::pull(m_wheelSlip) |>
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
