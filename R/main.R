source("R/src/Queue.R")
source("R/src/RawByteParser.R")

source("R/src/Struct.R")
pstruct <- Struct$new()$structToBytes("PacketHeader")

files <- file.path("data", list.files("data"))
fresults <- setNames(
  vector("list", length(files)), 
  files |> gsub("data/", "", x=_) |> gsub(".raw", "", x=_)
)

for (nfile in seq_along(files)) {
  rbp <- RawByteParser$new(filename = files[[nfile]])
  results <- pstruct

  rbp$fOpen()
  for (i in seq_along(pstruct)) {
    results[[i]] <- rbp$readBytes(pstruct[[i]])
  }

  fresults[[nfile]] <- purrr::map2(
    results,
    pstruct,
    function(x, y) rbp$bytesToInteger(x, y)
  )

  p2struct <- Struct$new()$structToBytes("CarMotionData")
  results2 <- p2struct
  for (j in seq_along(p2struct)) {
    results2[[j]] <- rbp$readBytes(p2struct[[j]])
  }

  if (fresults[[nfile]]$m_packetId == 0) browser()
  rbp$fClose()
}

ftbls <- dplyr::bind_rows(lapply(fresults, function(x) tibble::as_tibble(x)))
