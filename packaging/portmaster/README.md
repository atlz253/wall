## Notes

Wall is an open-source SDL2 strategy game. This package contains an aarch64 PortMaster build.

## Controls

| Button | Action |
|--|--|
|L1|Create unit for the left player|
|R1|Create unit for the right player|
|Start + Select|Exit through PortMaster hotkey handling|

Keyboard fallback is still available in the game: Q for the left player and ] for the right player.

## Compile

```shell
docker build -f Dockerfile.portmaster -t wall-portmaster-builder .
docker run --rm -v "$PWD:/src" wall-portmaster-builder
```
