# F1 Stream

## F1 2022 UDP Specification

https://answers.ea.com/t5/General-Discussion/F1-22-UDP-Specification/td-p/11551274

## Build

Requires raw telemetry output from an F1 2022 UDP stream to be present in the `data/` directory. This can be obtained by running the `python/server.py` script while streaming F1 2022 data.

```sh
$ make
$ make run
```

This will run the main program to parse the raw data.
