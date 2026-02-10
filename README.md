# samp-helpdev
A small program developed to make life easier for SAMP server developers. Well... in other words, I was tired of having to open the SAMP server, then the SAMP launcher, and only then being able to actually access the server to test the latest modification. I simplified this with just one command, so... I hope this helps.

Cut through this entire procedure using just one command.

# config.json
```json
{
  "textdraw": { "nome": "Textdraw Editor", "caminho": "Your directory.../samp-server.exe" },
  "map": { "nome": "Map Editor", "caminho": "Your directory.../samp-server.exe" },
  "server": { "nome": "Servidor SA-MP", "caminho": "Your directory.../samp-server.exe" }
}
```

# Examples

![Alt Text](https://github.com/mateus-bsod/samp-helpdev/blob/main/example.gif)


```diff
+  Textdraw
samp-helpdev.exe -td -r
                 |   |
                 |   ◟ Start SAMP on IP 127.0.0.1:7777 (default: 7777, but you can configure it)
                 ◟ This starts the "samp-server.exe" file, which is responsible for the gamemode of you textdraw-editor (config.json).

+  Server
samp-helpdev.exe -sv -r
                 |   |
                 |   ◟ Start SAMP on IP 127.0.0.1:7777 (default: 7777, but you can configure it)
                 ◟ This starts the "samp-server.exe" file, which is responsible for the gamemode of you server (config.json).

+  Map
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
