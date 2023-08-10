inherit CORE_COMMAND_D;

void create()
{
    add_alias(([
        "hp" : "score -s",
    ]));
    add_alias(([
        "sc" : "score",
    ]));
    add_alias(([
        "f" : "fight",
    ]));
}