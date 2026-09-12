# cub3D

A first-person view of a maze, drawn one vertical stripe at a time with the
technique Wolfenstein 3D used in 1992: there is no 3D scene and no polygon,
only a 2D grid and one ray cast per screen column. Each ray reports how far it
travelled before hitting a wall, and that single number decides how tall the
stripe is and which slice of texture goes into it.

The map is a text file the program has to accept or refuse before a window is
ever opened: any arrangement of rooms is legal as long as the walkable area is
fully enclosed, which cannot be checked by looking at the borders alone.

## How it works

### One ray per column

The renderer walks the screen from left to right. For each column it computes
the angle of the ray that passes through it and calls the DDA, which returns
the distance to the first wall met. Stripe height is inversely proportional to
that distance, so a wall twice as far is drawn half as tall, which is all the
perspective there is.

The distance used is **perpendicular to the camera plane**, not the length of
the ray. Using the ray length would make walls bulge in the middle of the
screen, because rays towards the edges travel further to reach the same flat
surface; the perpendicular distance removes that fisheye without any special
case.

### DDA, and why it beats sampling

The obvious way to find a wall is to advance the ray in small steps and check
the grid at every step. That is either slow or wrong: large steps jump over
thin walls, small steps waste work in open space.

The Digital Differential Analyzer jumps straight from one grid line to the
next. Before stepping it computes, for each axis, how far the ray travels when
crossing exactly one cell:

```c
delta_dist_x = fabs(1 / ray_dir_x);
delta_dist_y = fabs(1 / ray_dir_y);
```

Then at every iteration it compares the distance to the next vertical boundary
with the distance to the next horizontal one, and crosses the closer:

```c
if (side_dist_x < side_dist_y)
{
    side_dist_x += delta_dist_x;
    map_x += step_x;
    side = 0;
}
else
{
    side_dist_y += delta_dist_y;
    map_y += step_y;
    side = 1;
}
```

Every iteration lands exactly on a cell boundary, so no wall can be missed and
no step is wasted, and the number of iterations is the number of cells crossed
rather than a function of a step size that has to be guessed.

A ray parallel to an axis never crosses boundaries on the other one. Rather
than special-casing it, `delta_dist` becomes `1e30`: a number so large that the
comparison always picks the other axis, which is the same thing as infinity
without a branch.

The `side` flag records which kind of boundary was crossed last, and it is what
tells a north-facing wall from an east-facing one when it comes to choosing the
texture.

### Reading the scene file

The six elements — four texture paths and two colours — may appear in any order
and be separated by any number of blank lines, but the map always comes last.
The file is read once from top to bottom: element lines are consumed until all
six are found, then the descriptor is handed over, still open, positioned on
the first row of the map.

Map rows are written ragged and the grid has to be rectangular, so every row is
padded with spaces to the length of the longest. Spaces are part of the map, so
the padding is not a trick: a walkable cell that ends up touching one is
rejected by the same rule that rejects a hole in a wall.

### Proving the map is closed

The interesting check is stated backwards. Instead of looking for gaps, a flood
fill starts from the player and tries to escape: it spreads through every
walkable cell and fails the moment it reaches the edge of the grid or a
character that is not walkable. An enclosed area can never do either.

Cells are overwritten as they are visited, which is what stops the recursion
from looping — and also why the fill runs on a copy: by the time it returns,
that copy is solid wall.

A second, cheaper check runs before it, and catches a different mistake: no
walkable cell may sit on the border or have a missing neighbour. A map can pass
one and fail the other.

## Build and run

Requirements: **Linux with X11**, which on Debian and Ubuntu means
`libx11-dev`, `libxext-dev` and `libbsd-dev`. The Makefile clones MiniLibX
from 42Paris and builds it, then the bundled `libft`, then the project. There
is no macOS build: MiniLibX here is the Linux one, and it links against Xlib.

```bash
make          # cub3D
make debug    # the same, with debug symbols
make fclean   # removes the binary, both libraries and the objects
make remove   # also deletes the MiniLibX checkout
```

```bash
./cub3D maps/map.cub
```

| Key | |
|---|---|
| `W` `A` `S` `D` | move |
| `←` `→` | turn |
| `SPACE` | open or close a door |
| `M` | toggle mouse look |
| `ESC` | quit |

Movement keys set a flag that the render loop reads, instead of moving the
player on the key event itself: holding a key produces continuous motion, and
two keys held together compose, which is not the case if each event moves.

A scene file looks like this, identifiers first and map last:

```
NO ./images/Brick_1.xpm
SO ./images/Brick_2.xpm
WE ./images/Brick_3.xpm
EA ./images/Brick_4.xpm
F 220,100,0
C 225,30,0

1111111111
1000000001
10N0001101
1000000001
1111111111
```

Anything wrong with it is reported on standard error as `Error` followed by a
line saying what: a missing or unreadable file, a wrong extension, an unknown
character, more than one spawn point, colours outside 0-255, an open map.

Compiled without warnings with gcc 12 on Debian bookworm. Checked under
valgrind on the parsing paths, including the failing ones: no leaks, no invalid
reads.

## Repository layout

```
.
├── include/
│   ├── cub3D.h              # rendering, events and the game state
│   └── parsing.h            # the scene structures, and the parser prototypes
├── srcs/
│   ├── main.c               # opens the window and starts the loop
│   ├── init.c               # MLX context, image buffer, minimap geometry
│   ├── dda.c                # the ray casting itself
│   ├── drawing.c            # walks the columns, draws floor and ceiling
│   ├── drawing_3d.c         # one textured stripe per column
│   ├── drawing_3d_utils.c   # stripe bounds, and where a ray lands on a texture
│   ├── drawing_minimap.c    # the overhead view and the field-of-view cone
│   ├── render_textures.c    # picks the texture from the wall side that was hit
│   ├── texture_utils.c      # pixel access into an XPM image
│   ├── load_textures.c      # loads the XPM files, frees them on teardown
│   ├── events.c             # key press and release, the movement flags
│   ├── mouse_events.c       # mouse look, toggled with M
│   ├── movement.c           # applies the flags, one step per frame
│   ├── collision.c          # refuses a step that would end inside a wall
│   ├── doors.c              # the D tile, opened and closed with SPACE
│   └── parsing/
│       ├── parsing.c        # entry point of the parser, and the error printer
│       ├── get_elements.c   # reads the six elements in any order
│       ├── get_texture.c    # one texture path, checked with access()
│       ├── get_colors.c     # R,G,B into a single packed integer
│       ├── create_map_line.c  # the map, read into one string
│       ├── ft_split_len.c   # splits it into rows, padded to equal length
│       ├── get_map.c        # builds the grid and runs the checks in order
│       ├── check_all_characters_are_present.c   # census: walls, one spawn
│       ├── check_surrounded_by_wall.c           # no walkable cell on the border
│       ├── validate_map.c   # flood fill, spawn position and starting angle
│       ├── ft_strjoin_m.c   # join that treats NULL as an empty string
│       └── free_utils.c     # teardown of the map and of the scene elements
├── images/                  # wall, door and torch textures, XPM
├── maps/                    # a scene file to run
└── libft/                   # the library, as published in redei-ma/libft
```

## Notes

The bonus part is implemented and not separated into `_bonus` files, because it
is woven into the renderer: wall collisions, the minimap, doors that open and
close, animated torches, and mouse look.

`ft_strjoin_m` and `ft_strlen_m` are kept instead of the library versions on
purpose. The map is built by joining rows onto a string that starts as `NULL`,
and `ft_strjoin` refuses a `NULL` argument: swapping them in would mean no map
is ever read.

A square map is a valid map here, and so is any shape, as long as it is
enclosed. What is refused is a walkable cell that can reach the outside.

The window is fixed size, set at compile time.

## Resources

- Lode Vandevenne, *Raycasting* — https://lodev.org/cgtutor/raycasting.html —
  the reference for the DDA loop, the perpendicular distance and the side flag.
- Amanatides and Woo, *A Fast Voxel Traversal Algorithm for Ray Tracing* (1987),
  which is the same traversal in its general form.
- MiniLibX documentation — https://harm-smits.github.io/42docs/libs/minilibx

## Credit

Built with [Alessandro De Rossi](https://github.com/cacatuacommander).
