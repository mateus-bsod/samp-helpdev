# samp-helpdev
A small program designed to make life easier for server developers (SAMP). In other words, I was tired of having to open the SAMP server, open the SAMP initializer, and only then log into the server to test every time I compiled... so I simplified my work and I'm sharing it to see if I can help someone else.

Cut through this entire procedure using just one command.

# Examples

![Alt Text](https://github.com/mateus-bsod/samp-helpdev/blob/main/example.gif)

#### Textdraw
```
samp-helpdev.exe -td -r
                 |   |
                 |   ◟ Start SAMP on IP 127.0.0.1:7777 (default: 7777, but you can configure it)
                 ◟ This starts the "samp-server.exe" file, which is responsible for the gamemode of you textdraw-editor (config.json).
```

#### Server
```
samp-helpdev.exe -sv -r
                 |   |
                 |   ◟ Start SAMP on IP 127.0.0.1:7777 (default: 7777, but you can configure it)
                 ◟ This starts the "samp-server.exe" file, which is responsible for the gamemode of you server (config.json).
```


#### Map
```
samp-helpdev.exe -map -r
                 |    |
                 |    ◟ Start SAMP on IP 127.0.0.1:7777 (default: 7777, but you can configure it)
                 ◟ This starts the "samp-server.exe" file, which is responsible for the gamemode of you map-editor (config.json).
```

# Help (-h, --help)

```cmd
Usage:
  -td           : Run textdraw mode (Configure it in the JSON file.)
  -sv           : Run server mode (Configure it in the JSON file.)
  -map          : Run map-editor mode (Configure it in the JSON file.)
  -v            : Ignore port verification being used.
  -r            : Open GTA along with the server.
  --pass <num>  : Set server password
  --port <num>  : Set server port
  -h, --help    : Show this help message
```
