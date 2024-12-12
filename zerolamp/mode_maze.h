#ifndef ZB_MODE_MAZE_H
#define ZB_MODE_MAZE_H

#include "mode.h"

class MazeMode : public LampMode {

private:
  int maze_width;
  int maze_height;

  bool* horizontal_walls;
  bool* vertical_walls;

  // player's coordinates inside the maze
  int player_x;
  int player_y;

public:
  MazeMode(int maze_width, int maze_height) : maze_width(maze_width), maze_height(maze_height) {}

  void enter(int logical_width, int logical_height);
  void leave();
  void render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height);
  CommandHandleResult handle_command(String command);

private:
  void initialize_walls();

  void set_horizontal_wall(int wall_y, int wall_x, bool value);
  bool get_horizontal_wall(int wall_y, int wall_x);

  void set_vertical_wall(int wall_y, int wall_x, bool value);
  bool get_vertical_wall(int wall_y, int wall_x);

  void generate_maze();

};

#endif