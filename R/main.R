source("R/Queue.R")
source("R/RawByteParser.R")

source("R/Struct.R")
pstruct <- Struct$new()$structToBytes("PacketHeader")

files <- file.path("data", list.files("data"))
fresults <- setNames(vector("list", length(files)), files)

for (nfile in seq_along(files)) {
  rbp <- RawByteParser$new(filename = files[[nfile]])
  results <- pstruct

  rbp$fOpen()
  for (i in seq_along(pstruct)) {
    results[[i]] <- rbp$readBytes(pstruct[[i]])
  }
  rbp$fClose()

  fresults[[nfile]] <- purrr::map2(
    results,
    pstruct,
    function(x, y) rbp$bytesToInteger(x, y)
  )
}

ftbls <- dplyr::bind_rows(lapply(fresults, function(x) tibble::as_tibble(x)))
