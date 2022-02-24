# tic-tac-totally-scuffed

Tic-Tac-Toe with its 3x3 playing area can get pretty boring. So, this version of it can be configured to use different field sizes.

## Building

The project can simply be built with `make`. The resulting binary can be found in `./out/`.

## Configuration

The size of the playing field can be configured when calling the program by passing `s` and the desired dimension as program arguments. So for example:

`./out/main s 32` will generate a game of Tic-Tac-Toe which uses a 32x32 playing field. This kind of game can still be won but may be a bit tedious.

## Game end

The game ends once a player has completed a row, column or diagonal of the playing field OR no cells are left to fill in (thus causing a draw).

## Why

I don't know.

## Fun stuff

Since the program reads its player input from stdin, one could generate a file with all moves preconfigured (and pipe it to the binary) and use a fairly big playing area to generate some pixelart.
