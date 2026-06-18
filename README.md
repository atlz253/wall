# Wall

![Скриншот игры](https://raw.githubusercontent.com/atlz253/wall/master/screenshots/1.png)

## Правила

Бросьте вызов своему противнику и одолейте его в честной схватке! Вызывайте своих доблестных бойцов клавишами Q для левого игрока и клавишу } для правого. Победитель получит всё!

## Windows portable build

Build the Docker image:

```sh
docker build -t wall-win-builder .
```

Build the Windows x64 portable package from this repository:

```sh
docker run --rm -v "%cd%:/src" wall-win-builder
```

The output is written to `dist/wall-windows-x64/` and `dist/wall-windows-x64.zip`.
The folder contains `wall.exe`, `engine.dll`, required SDL/MinGW DLLs, and `res/`, so SDL2 does not need to be installed on the target Windows machine.
Игра, вдохновленная серией игр «Эпоха войны». Была сдана в качестве курсовой работы на первом курсе по предмету «разработка на ЯВУ». Скачать сборку можно на [странице релизов](https://github.com/atlz253/wall/releases).
