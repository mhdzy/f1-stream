# F1 Stream

## F1 2022 UDP Specification

https://answers.ea.com/t5/General-Discussion/F1-22-UDP-Specification/td-p/11551274

## Dependencies

Requires `spdlog` from https://github.com/gabime/spdlog for logging. Place the `spdlog/include/spdlog` folder in your `/usr/local/include` directory.

## Configure

Run `ifconfig | pcre2grep -o "(?<=(inet ))([\d\.]*)(?=( netmask))"` to get your local IP and set this as the target IP in F1 2022's UDP Telemetry settings.

## Build

```sh
$ make
```

## Run

```sh
$ make run <tag> batch
```

This will collect F1 telemetry data and store it in `data/<tag>/raw`.

```sh
$ make run <tag> live
```

This will parse F1 telemetry data in real time to `data/<tag>/parsed`.

## Output

Parsed packet types have their own csv file which is continuously updated in both 'batch' and 'live' runtime modes.

### batch

raw input data
 - `data/<tag>/raw`

parsed output data
 - `data/<tag>/parsed`

### live

parsed output data
 - `data/<tag>/parsed`

### display

show track progress in real time
 - `make run <tag> live` in one window
 - `python3 python/graph.py --track <tag>`

