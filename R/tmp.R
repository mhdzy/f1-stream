
library(dplyr)
library(readr)

scores <- readr::read_csv("data/dat.csv")

scoretbl <- scores %>%
  lapply(
  function(x) {
    unlist(
      lapply(
        x,
        function(y) {
          if (is.na(y) || y == "DNF" || y == "DNS") 0L else y
        }
      )
    )
  }
  ) %>%
    dplyr::bind_rows() %>%
    select(-Country, -(r9:r22))

means <- scoretbl %>%
  select(-Name, -total) %>%
  apply(1, function(x) mean(as.numeric(x), na.rm = TRUE))

sds <- scoretbl %>%
  select(-Name, -total) %>%
  apply(1, sd)

plotdf <-
  tibble::tibble(
    driver = scoretbl$Name,
    avg_place = means,
    avg_sd = sds
  ) %>%
  distinct() %>%
  arrange(avg_place) %>%
  mutate(id = seq(21))

plot()

plotdf

plot(plotdf$id, plotdf$avg_place,
    ylim=range(c(plotdf$avg_place-plotdf$avg_sd, plotdf$avg_place+plotdf$avg_sd)),
    pch=19, xlab="Measurements", ylab="Mean +/- SD",
    main="Scatter plot with std.dev error bars"
)
# hack: we draw arrows but with very special "arrowheads"
arrows(plotdf$id,plotdf$avg_place-plotdf$avg_sd, plotdf$id, plotdf$avg_place+plotdf$avg_sd, length=0.05, angle=90, code=3)

plotdf %>%
  ggplot2::ggplot(aes(x = avg_place, y = avg_sd)) + geom_point()


# show position (2d graph)
lapdata |>
  dplyr::filter(m_carID == 0) |>
  ggplot2::ggplot(
    ggplot2::aes(
      x = m_worldPositionX/32767L,
      y = -1L * m_worldPositionZ/32767L,
      color = m_frameIdentifier
    )
  ) +
  ggplot2::geom_point()

# linear graph of lap time
lapdata |>
  dplyr::filter(m_carID == 0) |>
  ggplot2::ggplot(
    ggplot2::aes(
      x = m_frameIdentifier,
      y = m_currentLapTimeInMS,
      #y = m_gForceLateral,
      color = m_frameIdentifier
    )
  ) +
  ggplot2::geom_point()

lapdata2 <- lapdata |> dplyr::filter(m_carID == 0) |> distinct()

options(rgl.printRglwidget = TRUE)
rgl::plot3d(
  x = lapdata2$m_worldPositionX/32767,
  y = -1L * lapdata2$m_worldPositionZ/32767,
  z = lapdata2$m_worldPositionY/32767
)

l2 <- lapdata |>
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
