#include "mode_maze.h"
#include "union_find.h"
#include <cassert>
#include <FastLED.h>
#include "matrix.h"
#include "bluetooth.h"

#define MAZE_WALL_COLOR CRGB::Blue

struct MazeEdge {
  uint8_t x_1;
  uint8_t y_1;
  uint8_t x_2;
  uint8_t y_2;

  MazeEdge(uint8_t x_1, uint8_t y_1, uint8_t x_2, uint8_t y_2) : x_1(x_1), y_1(y_1), x_2(x_2), y_2(y_2) {}
  MazeEdge() {}
};

void MazeMode::initialize_walls() {

  int horizontal_wall_count = (maze_height + 1) * maze_width;
  horizontal_walls = new bool[horizontal_wall_count];
  std::fill(horizontal_walls, horizontal_walls + horizontal_wall_count, true);

  int vertical_wall_count = (maze_width + 1) * maze_height;
  vertical_walls = new bool[vertical_wall_count];
  std::fill(vertical_walls, vertical_walls + vertical_wall_count, true);

}

void MazeMode::set_horizontal_wall(int wall_y, int wall_x, bool value) {
  assert(wall_y >= 0 && wall_y <= maze_height);
  assert(wall_x >= 0 && wall_x < maze_width);
  horizontal_walls[wall_y * maze_width + wall_x] = value;
}

bool MazeMode::get_horizontal_wall(int wall_y, int wall_x) {
  assert(wall_y >= 0 && wall_y <= maze_height);
  assert(wall_x >= 0 && wall_x < maze_width);
  return horizontal_walls[wall_y * maze_width + wall_x];
}

void MazeMode::set_vertical_wall(int wall_y, int wall_x, bool value) {
  assert(wall_y >= 0 && wall_y < maze_height);
  assert(wall_x >= 0 && wall_x <= maze_width);
  vertical_walls[wall_y * (maze_width + 1) + wall_x] = value;
}

bool MazeMode::get_vertical_wall(int wall_y, int wall_x) {
  assert(wall_y >= 0 && wall_y < maze_height);
  assert(wall_x >= 0 && wall_x <= maze_width);
  return vertical_walls[wall_y * (maze_width + 1) + wall_x];
}

void MazeMode::generate_maze() {

  int horizontal_edge_count = (maze_width - 1) * maze_height;
  int vertical_edge_count = (maze_height - 1) * maze_width;
  int total_edge_count = horizontal_edge_count + vertical_edge_count;

  MazeEdge* edges = new MazeEdge[total_edge_count];
  size_t cur_edge = 0;

  // generate all possible edges between cells
  for (int y = 0; y < maze_height; y++) {
    for (int x = 0; x < maze_width; x++) {
      
      if (x + 1 < maze_width) {
        // add horizontal edge
        edges[cur_edge++] = MazeEdge(x, y, x + 1, y);
      }

      if (y + 1 < maze_height) {
        // add vertical edge
        edges[cur_edge++] = MazeEdge(x, y, x, y + 1);
      }
      
    }
  }

  assert(cur_edge == total_edge_count);

  // shuffle the edges array using the Fisher-Yates algorithm
  for (int i = total_edge_count - 1; i > 0; i--) {
    int j = random(0, i + 1);
    std::swap(edges[i], edges[j]);
  }

  // put every node in a disjoint set
  UnionFind<int> maze_node_classes = UnionFind<int>(maze_width * maze_height);

  // initialize all walls in the maze to exist
  initialize_walls();

  for (int i = 0; i < total_edge_count; i++) {

    MazeEdge edge = edges[i];

    int first_node = edge.y_1 * maze_width + edge.x_1;
    int second_node = edge.y_2 * maze_width + edge.x_2;

    if (maze_node_classes.in_same_set(first_node, second_node)) {
      // these nodes are already connected by a path
      continue;
    }

    // create a path between the nodes (in other words, remove the wall in the maze that corresponds to the edge in the graph)
    if (edge.x_1 == edge.x_2) {
      // the edge is aligned vertically (i.e., the corresponding wall would be drawn horizontally)
      assert(edge.y_1 + 1 == edge.y_2);
      set_horizontal_wall(edge.y_2, edge.x_1, false);
    }
    else if (edge.y_1 == edge.y_2) {
      // the edge is aligned horizontally (i.e., the corresponding wall would be drawn vertically)
      assert(edge.x_1 + 1 == edge.x_2);
      set_vertical_wall(edge.y_1, edge.x_2, false);
    }
    else {
      assert(false);
    }

    // place the nodes in the same node class
    maze_node_classes.merge(first_node, second_node);

  }

  delete[] edges;

}

void MazeMode::enter(int logical_width, int logical_height) {
  
  set_render_interval(500);

  generate_maze();

  // place the player at a random position inside the maze
  player_x = random8(maze_width);
  player_y = random8(maze_height);

}

void MazeMode::leave() {
  delete[] horizontal_walls;
  delete[] vertical_walls;
}

void MazeMode::render_frame(int offset_x, int offset_y, int viewport_width, int viewport_height) {

  // calculate the coordinates of the player on the screen
  int player_screen_x = viewport_width >> 1;
  int player_screen_y = viewport_height >> 1;

  // ----------- Step 1 -----------
  // calculate the position in the maze that corresponds to the top left corner of the screen
  // more precisely: leftmost and topmost position in the maze that will be visible on the screen
  
  // how many maze positions will be visible to the left of the player
  int visible_maze_positions_before_player_x = player_screen_x >> 1;
  // how many maze positions will be visible above the player
  int visible_maze_positions_before_player_y = player_screen_y >> 1;

  int leftmost_maze_position = player_x - visible_maze_positions_before_player_x;
  if (leftmost_maze_position < 0) {
    leftmost_maze_position = 0;
  }

  int topmost_maze_position = player_y - visible_maze_positions_before_player_y;
  if (topmost_maze_position < 0) {
    topmost_maze_position = 0;
  }

  // ----------- Step 2 -----------
  // calculate the position in the maze that corresponds to the bottom right corner of the screen
  // more precisely: rightmost and bottommost position in the maze that will be visible on the screen

  // how many maze positions will be visible to the right of the player
  int visible_maze_positions_after_player_x = (viewport_width - 1 - player_screen_x) >> 1;
  // how many maze positions will be visible below the player
  int visible_maze_positions_after_player_y = (viewport_height - 1 - player_screen_y) >> 1;

  int rightmost_maze_position = player_x + visible_maze_positions_after_player_x;
  if (rightmost_maze_position >= maze_width) {
    rightmost_maze_position = maze_width - 1;
  }

  int bottommost_maze_position = player_y + visible_maze_positions_after_player_y;
  if (bottommost_maze_position >= maze_height) {
    bottommost_maze_position = maze_height - 1;
  }

  // ----------- Step 3 -----------
  // translate (leftmost_maze_position, topmost_maze_position) in maze coordinates to corresponding screen coordinates
  int leftmost_maze_position_screen = player_screen_x - (visible_maze_positions_before_player_x << 1);
  int topmost_maze_position_screen = player_screen_y - (visible_maze_positions_before_player_y << 1);

  assert(leftmost_maze_position_screen >= 0);
  assert(topmost_maze_position_screen >= 0);
  
  // ----------- Step 4 -----------
  // loop through all relevant maze positions and render them
  
  for (int maze_y = topmost_maze_position; maze_y <= bottommost_maze_position; maze_y++) {
    for (int maze_x = leftmost_maze_position; maze_x <= rightmost_maze_position; maze_x++) {

      // translate the maze coordinates back into screen coordinates
      int screen_x = leftmost_maze_position_screen + ((maze_x - leftmost_maze_position) << 1);
      int screen_y = topmost_maze_position_screen + ((maze_y - topmost_maze_position) << 1);

      assert(screen_x >= 0 && screen_y >= 0);
      assert(screen_x < viewport_width);
      assert(screen_y < viewport_height);

      // check the horizontal wall above (maze_x, maze_y)
      bool wall_above = get_horizontal_wall(maze_y, maze_x);
      if (wall_above) {
        // draw it if it's visible
        if (screen_y != 0) {
          matrix_setLedColor(
            offset_y + screen_y - 1,
            offset_x + screen_x,
            MAZE_WALL_COLOR
          );
        }
      }

      // check the vertical wall to the left of (maze_x, maze_y)
      bool wall_left = get_vertical_wall(maze_y, maze_x);
      if (wall_left) {
        // draw it if it's visible  
        if (screen_x != 0) {
          matrix_setLedColor(
            offset_y + screen_y,
            offset_x + screen_x - 1,
            MAZE_WALL_COLOR
          ); 
        }
      }

      // check whether we need to draw a corner wall between the wall to the left and the wall to the above
      if (screen_x != 0 && screen_y != 0) {
        bool wall_above_left;
        if (wall_above || wall_left) {
          wall_above_left = true;
        }
        else if (maze_x == 0 || maze_y == 0) {
          // we always draw corners at the borders of the maze
          wall_above_left = true;
        }
        else {
          // more complicated, here we need to check whether some walls connect to the corner we are currently considering
          wall_above_left = get_horizontal_wall(maze_y, maze_x - 1) || get_vertical_wall(maze_y - 1, maze_x);
        }

        if (wall_above_left) {
          matrix_setLedColor(
            offset_y + screen_y - 1,
            offset_x + screen_x - 1,
            MAZE_WALL_COLOR
          );
        }
      }

    }
  }

  // ----------- Step 4 -----------
  // draw player
  matrix_setLedColor(
    offset_y + player_screen_y,
    offset_x + player_screen_x,
    CRGB::Yellow
  );

}

CommandHandleResult MazeMode::handle_command(String command) {

  if (command.equalsIgnoreCase("w")) {
    // player tries to move up
    bool wall_above = get_horizontal_wall(player_y, player_x);

    if (wall_above) {
      bluetooth_serial()->println("Can't move up, there is a wall!");
    }
    else if (player_y == 0) {
      bluetooth_serial()->println("Can't move up, you have reached the border of the maze!");
    }
    else {
      player_y--;
      bluetooth_serial()->println("Moved up.");
    }
    
    return CommandHandleResult::HANDLED;
  }

  if (command.equalsIgnoreCase("s")) {
    // player tries to move down
    bool wall_below = get_horizontal_wall(player_y + 1, player_x);

    if (wall_below) {
      bluetooth_serial()->println("Can't move down, there is a wall!");
    }
    else if (player_y == maze_height - 1) {
      bluetooth_serial()->println("Can't move down, you have reached the border of the maze!");
    }
    else {
      player_y++;
      bluetooth_serial()->println("Moved down.");
    }
    
    return CommandHandleResult::HANDLED;
  }

  if (command.equalsIgnoreCase("a")) {
    // player tries to move left
    bool wall_left = get_vertical_wall(player_y, player_x);

    if (wall_left) {
      bluetooth_serial()->println("Can't move left, there is a wall!");
    }
    else if (player_x == 0) {
      bluetooth_serial()->println("Can't move left, you have reached the border of the maze!");
    }
    else {
      player_x--;
      bluetooth_serial()->println("Moved left.");
    }
    
    return CommandHandleResult::HANDLED;
  }

  if (command.equalsIgnoreCase("d")) {
    // player tries to move right
    bool wall_right = get_vertical_wall(player_y, player_x + 1);

    if (wall_right) {
      bluetooth_serial()->println("Can't move right, there is a wall!");
    }
    else if (player_x == maze_width - 1) {
      bluetooth_serial()->println("Can't move right, you have reached the border of the maze!");
    }
    else {
      player_x++;
      bluetooth_serial()->println("Moved right.");
    }
    
    return CommandHandleResult::HANDLED;
  }

  return CommandHandleResult::NOT_HANDLED;
}