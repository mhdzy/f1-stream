source("R/Stack.R")
source("R/RawByteParser.R")
rbp <- RawByteParser$new(filename = "data/data.raw")

source("R/Struct.R")
pstruct <- Struct$new()$structToBytes("PacketHeader")

results <- pstruct

rbp$file_open()
for (i in seq_along(pstruct)) {
  results[[i]] <- rbp$read_bytes(pstruct[[i]])
}
rbp$file_close()
