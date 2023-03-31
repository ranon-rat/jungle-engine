#include <vector>
#include <tuple>

#include "player.hpp"

enum LumpIndices
{
    THINGS = 1,
    LINEDEFS,
    SIDEDEFS,
    VERTEXES,
    SEGS,
    SSECTORS,
    NODES,
    SECTORS,
    REJECT,
    BLOCKMAP
};

// Offset	Size (bytes)	C99 type	Description
// 0	    2               int16_t     x position
// 2	    2	            int16_t     y position
// 4	    2	            int16_t     Angle facing
// 6 	    2               int16_t     DoomEd thing type
// 8	    2               int16_t     Flags
class Thing
{
    int16_t x;
    int16_t y;
    int16_t angle;
    int16_t type;
    int16_t flags;
}

// Offset	Size (bytes)	C99 type	Description
// 0	    2	            int16_t     Start Vertex
// 2	    2	            int16_t     End Vertex
// 4	    2	            int16_t     Flags
// 6	    2	            int16_t     Special type
// 8	    2	            int16_t     Sector tag
// 10	    2	            int16_t     Right sidedef
// 12	    2	            int16_t     Left sidedef
class LineDef
{
    int16_t start_vertex;
    int16_t end_vertex;
    int16_t flags;
    int16_t special_type;
    int16_t sector_tag;
    int16_t front_sidedef;
    int16_t back_sidedef;
}

// Offset	Size (bytes)	C99 type	Description
// 0	    2	            int16_t     X offset
// 2	    2	            int16_t     Y offset
// 4	    8	            int8_t [8]  Upper texture name
// 12	    8	            int8_t [8]  Lower texture name
// 20	    8   	        int8_t [8]  Middle texture name
// 28	    2	            int16_t     Sector number this sidedef faces

class SideDef
{
    int16_t x_offset;
    int16_t y_offset;
    int8_t upper_texture[8];
    int8_t lower_texture[8];
    int8_t middle_texture[8];
    int16_t sector;
}

// Offset	Size (bytes)	C99 type	Description
// 0	    2	            int16_t     X coordinate
// 2	    2	            int16_t     Y coordinate
class Vertex
{
    int16_t x;
    int16_t y;
}

// Offset	Size (bytes)	C99 type	Description
// 0	    2	            int16_t     Start Vertex
// 2	    2	            int16_t     End Vertex
// 4	    2	            int16_t     Angle, full circle is -32768 to 32767.
// 6	    2	            int16_t     Linedef number
// 8	    2	            int16_t     Direction: 0 (same as linedef) or 1 (opposite of linedef)
// 10	    2	            int16_t     Offset: distance along linedef to start of seg
class Seg
{
    int16_t start_vertex;
    int16_t end_vertex;
    int16_t angle;
    int16_t linedef;
    int16_t direction;
    int16_t offset;
}

// Offset	Size (bytes)	C99 type	Description
// 0	    2	            int16_t     Seg count
// 2	    2	            int16_t     First seg number
class SSector
{
    int16_t seg_count;
    int16_t first_seg;
}

// Offset	Size (bytes)	C99 type	Description
// 0	    2	            int16_t     X coordinate of partition line start
// 2	    2	            int16_t     Y coordinate of partition line start
// 4	    2	            int16_t     Change in x from start to end of partition line
// 6	    2	            int16_t     Change in y from start to end of partition line
// 8	    2	            int16_t [4]	Right bounding box
// 10	    2	            int16_t [4] Left bounding box
// 12	    2	            int16_t     Right child
// 14	    2	            int16_t     Left child
class Node
{
    int16_t x_start;
    int16_t y_start;
    int16_t x_end;
    int16_t y_end;
    int16_t right_bounding_box[4];
    int16_t left_bounding_box[4];
    int16_t right_child;
    int16_t left_child;
}

// Offset	Size (bytes)	C99 type	Description
// 0	    2	            int16_t     Sector floor height
// 2	    2	            int16_t     Sector ceiling height
// 4	    8	            int8_t [8]  Floor texture name
// 12	    8	            int8_t [8]  Ceiling texture name
// 20	    2	            int16_t     Light level
// 22	    2	            int16_t     Sector type
// 24	    2	            int16_t     Tag
class Sector
{
    int16_t floor_height;
    int16_t ceiling_height;
    int8_t floor_texture[8];
    int8_t ceiling_texture[8];
    int16_t light_level;
    int16_t sector_type;
    int16_t tag;
}

//      0	1	2	3	4
// 0	1	0	1	0	0
// 1	0	1	1	0	1
// 2	1	1	1	1	0
// 3	0	0	1	1	0
// 4	0	1	0	0	1
typedef uint8_t[5][5] Reject;

class BlockMap
{

}

class WadData
{
public:
    vector<Thing> things;
    vector<LineDef> linedefs;
    vector<SideDef> sidedefs;
    vector<Vertex> vertices;
    vector<Seg> segs;
    vector<SSector> ssectors;
    vector<Node> nodes;
    vector<Sector> sectors;
    Reject reject;
    BlockMap blockmap;
}

class BSP
{
public:
    BSP(player::Player& player, WadData wad);

public:
    void render_node(int id);
    void update();

private:
    Player player;
    WadData wad;
}
