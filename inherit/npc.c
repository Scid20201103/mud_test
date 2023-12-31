/*****************************************************************************
Copyright: 2019, Mud.Ren
File name: npc.c
Description: 非玩家角色公共接口：NPC/魔物等
Author: xuefeng
Version: v1.0
Date: 2019-03-14
History:
*****************************************************************************/
inherit _CLEAN_UP;
inherit _LIVING;

int is_npc() { return 1; }

/**
 * reset时回到起始环境
 */
int return_home(object home)
{
    if (!environment() || environment() == home)
        return 1;

    if (!living(this_object()) || !mapp(environment()->query("exits")))
        return 0;

    message("vision", this_object()->name() + "急急忙忙地离开了。\n",
            environment(), this_object());

    return move(home);
}

/**
 * 非战斗状态的行为
 */
// 说话
void chat(string msg)
{
    command("say " + msg);
}
// 随机移动
void random_move()
{
    mapping exits;
    string *dirs;

    if (!mapp(exits = environment()->query("exits")) || !sizeof(exits))
        return 0;
    dirs = keys(exits);
    command("go " + dirs[element_of(dirs)]);
}
/**
 * 战斗状态的行为
 */
// 使用咒文
void cast_spell(string spell)
{
    command("cast " + spell);
}
// 使用特技
void exert_skill(string skill)
{
    command("exert " + skill);
}
/**
 * NPC行为控制
 */
void action()
{
    // todo 行为控制，如战斗行为
}

// 触发任务提示
varargs void greeting(object ob, object me)
{
    ob = ob || this_player();
    me = me || this_object();
    if ((environment(me)->is_area() && !area_environment(ob, me)) || environment(ob) != environment(me))
        return;
    msg("info", "$ME对$YOU说到：你好呀，旅行者，我这里需要你的帮助。(提示：ask " + me->query("id") + ")", me, ob);
}

void init()
{
    object ob = this_player(), me = this_object();
    // debug_message(sprintf("init: %O -> %O", ob, me));
    if (interactive(ob) && QUEST_D->hasQuest(ob, me))
    {
        remove_call_out("greeting");
        call_out("greeting", 1, ob, me);
    }
}