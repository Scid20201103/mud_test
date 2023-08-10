#include <ansi.h>
inherit _LIVING;


varargs void create(int index, int lv)
{
    mixed info = MONSTER_D->info(index);
    string id, name, family, desc;
    int hp, mp, str, vit, agi, exp, gold;

    id = info[0];
    name = info[1];
    family = info[2];
    hp = info[3];
    mp = info[4];
    str = info[5];
    vit = info[6];
    agi = info[7];
    exp = info[8];
    gold = info[9];

    desc = MONSTER_D->desc(id);

    switch (family)
    {
    case "Slime":
        desc = CYN + desc + NOR;
        break;
    case "Beast":
        desc = BLU + desc + NOR;
        break;
    case "Dragon":
        desc = HIY + desc + NOR;
        break;
    case "Bug":
        desc = MAG + desc + NOR;
        break;
    case "Bird":
        desc = HIC + desc + NOR;
        break;
    case "Plant":
        desc = HIG + desc + NOR;
        break;
    case "Material":
        desc = WHT + desc + NOR;
        break;
    case "Machine":
        desc = HIW + desc + NOR;
        break;
    case "Zombie":
        desc = RED + desc + NOR;
        break;
    case "Demon":
        desc = HIM + desc + NOR;
        break;
    case "Elemental":
        desc = HIR + desc + NOR;
        break;
    case "Humanoid":
        desc = YEL + desc + NOR;
        break;
    case "Aquatic":
        desc = HIB + desc + NOR;
        break;

    default:
        break;
    }

    lv=lv||1;
    set_heart_beat(1);
    set("lv", 1);
    set_name(name, ({id}));
    set("long", desc);
    set_attrs(hp, mp, str, vit, agi);
    set("family", family);
    set("uuid", index);
    set("exp", exp);
    set("coin", gold);
    set("race", "魔物");
    set("unit", "只");
    set("no_get", "你想找死啊？\n");
    set("drop_item", ([
        /* 掉落物品 : 机率 */
    ]));
    set("action", ([
        /* 魔物技能行为 */
    ]));

    setup();
}




