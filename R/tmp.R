
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
