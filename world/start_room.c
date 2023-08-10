#include <ansi.h>

inherit STD_ROOM;

varargs private void create(int x, int y, int z)
{
    set("short", "史萊姆王國");
    set("long", HIW "这里是位于地下某處的史萊姆王國，有很多很多史萊姆。\n" NOR);
    set("no_fight", 1);
    set("exits", ([
        "up" : __DIR__ "start_room/" + x + "," + y + "," + (z + 1),
        "north" : __DIR__ "start_room/" + x + "," + (y + 1) + "," + z,
        "south" : __DIR__ "start_room/" + x + "," + (y - 1) + "," + z,
        "west" : __DIR__ "start_room/" + (x - 1) + "," + y + "," + z,
        "east" : __DIR__ "start_room/" + (x + 1) + "," + y + "," + z,
    ]));
    if (z > 0)
    {
        set("exits/down", __DIR__ "start_room/" + x + "," + y + "," + (z - 1));
    }
    if (z == 99)
    {
        removeExit("up");
    }

    setArea(0, x, y, z);
}

void virtual_start()
{   
    if(1){
        for(int i=0; i<random(4); i++){
            object ob = new ("/world/npc/mob", 1, 1+random(3));
            ob->move(this_object());
        }
    }
}