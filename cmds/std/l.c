#include <ansi.h>

int look_living(object me, object ob);
int look_room(object me, object env);
int look_item(object me, object ob);
string desc_of_objects(object *obs);
string list_all_inventory_of_object(object me, object env);

int main(object me, string arg)
{
    object ob;

    if(!arg)
    {
        look_room(me, environment(me));
    }
    else if(arg=="item"){
        ob =find_object(ITEM_DIR + arg);
        look_item(me, ob);
    }
    else if(ob = present(arg, environment(me))){
        look_living(me, ob);
    }
    else{
        printf("找不到你想看的對象。\n");
    }        
    return 1;
}

int look_living(object me, object ob)
{
    string msg, race = ob->query("race");
    string line = repeat_string("-*-", 12) + "\n";

    if (ob != this_player())
    {
        msg = "$ME看了看$YOU，好像对$YOU很感兴趣对样子。";
        msg("vision", msg, me, ob);
    }
    if(race=="魔物"){
        msg = sprintf("%s 是隻 %d 级的魔物。\n", ob->short(), ob->query("lv"));
        tell_object(me, msg);
        return 1;   
    }
    msg = sprintf("%s 是一位 %d 级的%s性生物。\n", ob->short(), ob->query("lv"), ob->query("gender") || "??");
    msg += line;
    msg += sprintf("  %-36s\n", "ＨＰ：" + ob->query("hp") + " / " + ob->query("max_hp"));
    msg += sprintf("  %-12s%-12s%-12s\n", "力量：" + ob->query("str"), "敏捷：" + ob->query("agi"), "防御：" + ob->query("def"));
    msg += line;
    tell_object(me, msg);

    return 1;
}


int look_room(object me, object env)
{
    string str, *dirs;
    mapping exits;

    if (env->is_area())
    {
        return env->do_look(me);
    }

    str = sprintf(HIC + "%s" + NOR + "%s\n    %s" + NOR,
                  env->short(), wizardp(me) ? " - " + env : env->coordinate(),
                  sort_string(env->long(), 72, 4));
    // env->long());

    if (mapp(exits = env->query("exits")))
    {
        dirs = keys(exits);

        if (sizeof(dirs) == 0)
            str += "    这里没有任何明显的出路。\n";
        else if (sizeof(dirs) == 1)
            str += "    这里唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
        else
            str += sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR + "。\n",
                           implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs) - 1]);
    }
    else
    {
        str += "    这里没有任何出路。\n";
    }
    str += list_all_inventory_of_object(me, env);
    tell_object(me, str);
    return 1;
}

int look_item(object me, object ob){
    string msg;
    msg = sprintf("你有兩個怪物硬幣。\n");
    tell_object(me, msg);
    return 1;
}

string desc_of_objects(object *obs)
{
    int i;
    string str;
    mapping list, unit;
    string short_name;
    string *ob;

    if (obs && sizeof(obs) > 0)
    {
        str = "";
        list = ([]);
        unit = ([]);

        for (i = 0; i < sizeof(obs); i++)
        {
            short_name = obs[i]->short();

            list[short_name] += obs[i]->query_temp("amount") ? obs[i]->query_temp("amount") : 1;
            unit[short_name] = obs[i]->query("unit") ? obs[i]->query("unit") : "个";
        }

        ob = sort_array(keys(list), 1);
        for (i = 0; i < sizeof(ob); i++)
        {
            str += "  ";
            if (list[ob[i]] > 1)
                str += list[ob[i]] + unit[ob[i]] + ob[i] + "\n";
            else
                str += ob[i] + "\n";
        }
        return str;
    }

    return "";
}

string list_all_inventory_of_object(object me, object env)
{
    object *inv;
    object *obs;
    string str = "";

    if (!env || !me)
        return "";

    inv = all_inventory(env);
    if (!sizeof(inv))
        return str;

    obs = filter_array(inv, (: $(me) != $1 :));
    str += desc_of_objects(obs);

    return str;
}